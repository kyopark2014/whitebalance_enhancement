// Gif.cpp: implementation of the CGif class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Gif.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGif::CGif()
{
	int i;
	m_pData = NULL;
	m_BitCount = 0;	
	m_pTable = new BYTE*[4096];

	for(i=0; i<4096; i++)
		m_pTable[i] = NULL;
	m_pTableLength = new int[4096];
}

CGif::~CGif()
{	
	ClearData();

	int i;
	for(i=0; i<4096; i++)
		if(m_pTable[i] != NULL)
			delete [] m_pTable[i];
	delete [] m_pTable;
	delete [] m_pTableLength;
}

void CGif::LoadGIF(LPSTR FileName)
{	
	BYTE *pos;
	int FileSize;
	int Index = 13+256*3;
	int Increment;

	// 멤버의 파일이름에 데이터 셋팅 //
	m_FileName.Format("%s", FileName);
	
	// 파일 개방 //
	HFILE hFile = _lopen(FileName, OF_READ);
	FileSize = GetFileSize((HANDLE)hFile, NULL);
	
	// 파일 데이터 읽어드림 //
	pos = new BYTE[FileSize];
	_lread(hFile, pos, FileSize);

	// 헤더 정보 읽어드림 //
	LoadHeader(&pos[0]);

	// 팔레트 정보 읽어드림 //
	LoadPalette(&pos[13]);


	// 이미지 데이터가 출력될 버퍼를 마련 //
	ClearData();
	m_pData = new BYTE[GetWidth() * GetHeight()];

	while(Index < FileSize)
	{
		if(pos[Index] == 0x2C)
		{
			LoadDescriptor(&pos[Index]);
			Index += 10;
			LZW_Decode(&pos[Index]);
			break;
		}
		else if(pos[Index] == 0x21)
		{
			Increment = Skip(&pos[Index]);
			Index += Increment;
		}
		else
			Index++;		
	}

	_lclose(hFile);

	delete [] pos;

	if(m_Descriptor.Packed == 64) // Interlaced mode
		ProcessInterlaced();	
}

void CGif::LoadHeader(BYTE * p)
{
	memcpy(m_Header.Signature, &p[0], 3);
	memcpy(m_Header.Version, &p[3], 3);
	m_Header.ScreenWidth = (p[7]<<8)|p[6];
	m_Header.ScreenHeight = (p[9]<<8)|p[8];
	m_Header.Packed = p[10];
	m_Header.BackgroundColor = p[11];
	m_Header.AspectRatio = p[12];
}

int CGif::GetWidth()
{
	return m_Header.ScreenWidth;
}

int CGif::GetHeight()
{
	return m_Header.ScreenHeight;
}

void CGif::LoadPalette(BYTE * p)
{
	int i;	

	for(i=0; i<256; i++)	
	{
		m_Pal[i] = RGB(*p, *(p+1), *(p+2));
		p += 3;
	}
}

void CGif::LoadDescriptor(BYTE * p)
{
	m_Descriptor.Separator = p[0];
	m_Descriptor.Left = (p[2]<<8)|p[1];
	m_Descriptor.Top = (p[4]<<8)|p[3];
	m_Descriptor.Width = (p[6]<<8)|p[5];
	m_Descriptor.Height = (p[8]<<8)|p[7];
	m_Descriptor.Packed = p[9];
}

int CGif::Skip(BYTE * p)
{
	BYTE FCode = p[1];
	int Increment;
	switch(FCode)
	{
	case 0xF9:
		Increment = 8;
		break;
	case 0x01:
		Increment = 17;
		break;
	case 0xFF:
		Increment = 16;
		break;
	case 0xFE:
		Increment = 4;
		break;
	default :
		Increment = 0;
		break;
	}
	
	return Increment;
}

void CGif::LZW_Encode(HFILE hFile)
{
	BYTE c;
	
	m_hFile = hFile;

	m_BitCount = 0;
	m_BlockByteCount = 0;
	m_CodeSize = 9;

	int idx = 0;

	int Size = GetWidth() * GetHeight();

	BYTE K;

	WORD Code, bCode;

	BYTE *strPrefix = NULL, *strTemp;

	int PrefixLength, TempLength = 0;

	c = 8; _lwrite(hFile, (LPSTR)&c, 1); // CodeSize = 8 Setting	
	
	OutToCodeStream(256); // ClearCode 출력
	OnClearCode();

	PrefixLength = 0; //[2]//
	
	while(idx<Size)
	{
		K = m_pData[idx]; //[3]//
		idx++;
		
		TempLength = PrefixLength + 1;
		
		strTemp = new BYTE[TempLength];
		memcpy(strTemp, strPrefix, PrefixLength);
		strTemp[TempLength - 1] = K;

		Code = GetCode(strTemp, TempLength);		

		if(Code != 65535) // 테이블에 있음
		{
			if(strPrefix != NULL)
				delete [] strPrefix;
			strPrefix = new BYTE[TempLength];
			memcpy(strPrefix, strTemp, TempLength);
			PrefixLength = TempLength;
		}
		else // 테이블에 없음
		{
			if(m_TableIndex < 4095)
			{
				m_pTable[m_TableIndex] = new BYTE[TempLength];
				memcpy(m_pTable[m_TableIndex], strTemp, TempLength);
				m_pTableLength[m_TableIndex] = TempLength;				

				bCode = GetCode(strPrefix, PrefixLength);
				OutToCodeStream(bCode);				
				
				if(m_TableIndex - 1 == m_threshold)
				{
					m_CodeSize++;
					m_threshold = ((1<<m_CodeSize) - 1);		
				}				
				
				if(strPrefix != NULL)
					delete [] strPrefix;
				strPrefix = new BYTE[1];
				PrefixLength = 1;
				strPrefix[0] = K;
				m_TableIndex++;
			}
			else
			{
				m_pTable[m_TableIndex] = new BYTE[TempLength];
				memcpy(m_pTable[m_TableIndex], strTemp, TempLength);
				m_pTableLength[m_TableIndex] = TempLength;
				bCode = GetCode(strPrefix, PrefixLength);
				OutToCodeStream(bCode);				
				PrefixLength = 0;
				OutToCodeStream(256); // ClearCode 출력
				OnClearCode();
				idx--;
			}			
		}		
		delete [] strTemp;
	}


	if(strPrefix != NULL) // 뒷처리
	{
		bCode = GetCode(strPrefix, PrefixLength);
		OutToCodeStream(bCode);				
		delete [] strPrefix;
	}

	OutToCodeStream(257); // EOI 출력
	
	while(m_BitCount != 0)
		SetNextBit(0);

	m_pBuf[0] = m_BlockByteCount;
	_lwrite(m_hFile, (LPSTR)m_pBuf, m_BlockByteCount+1);
	m_BlockByteCount = 0;	
	
	c = 0; _lwrite(m_hFile, (LPSTR)&c, 1); // 데이터의 끝 알림

}

void CGif::LZW_Decode(BYTE * p)
{	
	BYTE * strPrefix;
	WORD wCode;
	WORD wOldCode;
	int PrefixLength;
	int Size = GetWidth() * GetHeight();

	m_CodeSize = 9;
	m_pBuf = &p[1]; // 이미지데이터 포인터를 셋팅한다. //
	m_CharIndex = 0; // Character Stream Index 를 리셋 //

	m_BitCount = 0; // GetNextBit()함수의 비트카운트를 리셋 //
	m_BlockByteCount = 0; // GetNextByte()에서 처리하는 BlockByteCount 를 리셋 //
	
	m_threshold = ((1<<m_CodeSize) - 1); // Variable Length를 위한 한계치 //

	wCode = GetNextCode(); // 처음의 Clear Code 처리
	if(wCode == 256)
		OnClearCode();	
	
	while(TRUE)
	{
		if(m_CharIndex >= Size)
			break;
		wCode = GetNextCode();
		OutToCharStream(wCode);
		wOldCode = wCode;
		while(TRUE)
		{
			if(m_CharIndex >= Size)
				break;
			wCode = GetNextCode();
			
			if(wCode == 256) // 두번째 이후의 Clear Code와 만남
			{				
				OnClearCode();
				break;
			}			
			else if(wCode == 257)
				break;
			else
			{			
				if(m_pTableLength[wCode] == 0) // Table에 없을 때
				{
					PrefixLength = m_pTableLength[wOldCode] + 1;
					strPrefix = new BYTE[PrefixLength];

					memcpy(strPrefix, m_pTable[wOldCode], PrefixLength - 1);
					strPrefix[PrefixLength - 1] = m_pTable[wOldCode][0];
					
					m_pTable[m_TableIndex] = new BYTE[PrefixLength];
					memcpy(m_pTable[m_TableIndex], strPrefix, PrefixLength);
					m_pTableLength[m_TableIndex] = PrefixLength;

					if(m_TableIndex == m_threshold)
					{
						m_CodeSize++;
						m_threshold = ((1<<m_CodeSize) - 1);
					}

					OutToCharStream(m_TableIndex);
					m_TableIndex++;
					wOldCode = wCode;

					delete [] strPrefix;
				}		
				else // Table에 있을 때
				{
					OutToCharStream(wCode);

					PrefixLength = m_pTableLength[wOldCode] + 1;
					strPrefix = new BYTE[PrefixLength];

					memcpy(strPrefix, m_pTable[wOldCode], PrefixLength - 1);
					strPrefix[PrefixLength - 1] = m_pTable[wCode][0];

					m_pTable[m_TableIndex] = new BYTE[PrefixLength];
					memcpy(m_pTable[m_TableIndex], strPrefix, PrefixLength);
					m_pTableLength[m_TableIndex] = PrefixLength;

					if(m_TableIndex == m_threshold)
					{
						m_CodeSize++;
						m_threshold = ((1<<m_CodeSize) - 1);
					}
					m_TableIndex++;

					wOldCode = wCode;

					delete [] strPrefix;
				}		
			}
		}
		
		if(wCode == 257)
			break;
	}
}

void CGif::ClearData()
{
	if(m_pData != NULL)
		delete [] m_pData;
}

BYTE CGif::GetNextByte()
{	
	if(m_BlockByteCount == 0)
		m_BlockByteCount = *(m_pBuf++);		
	m_BlockByteCount--;	
	return *(m_pBuf++);
}

WORD CGif::GetNextCode()
{
	WORD Code = 0;
	BYTE Bit;
	int i;

	for(i=0; i<m_CodeSize; i++)
	{
		Bit = GetNextBit();
		Code = Code|(Bit << i);
	}

	return Code;
}

BYTE CGif::GetNextBit()
{
	static BYTE Buf;
	BYTE OutBit;

	if(m_BitCount == 0)
	{
		Buf = GetNextByte();
		m_BitCount = 8;
	}

	m_BitCount--;
	OutBit = (Buf & 0x01);
	Buf = Buf >> 1;
	
	return OutBit;
}

void CGif::InitStringTable()
{
	int i;
	m_TableIndex = 258;
	
	for(i=0; i<4096; i++)
		if(m_pTable[i] != NULL)
		{
			delete [] m_pTable[i];
			m_pTable[i] = NULL;
		}

	for(i=0; i<4096; i++)
	{
		if(i<256)
		{
			m_pTable[i] = new BYTE[1];
			m_pTable[i][0] = (BYTE)i;
			m_pTableLength[i] = 1;
		}
		else
		{
			m_pTableLength[i] = 0;
		}
	}		
}


void CGif::OutToCharStream(int idx)
{
	int Length = m_pTableLength[idx];
	memcpy(&m_pData[m_CharIndex], m_pTable[idx], Length);
	m_CharIndex += Length;	
}

void CGif::OnClearCode()
{
	// Initialize Decompressor //
	m_CodeSize = 9;
	m_threshold = ((1<<m_CodeSize) - 1);
	InitStringTable();
}

void CGif::SaveGIF(LPSTR FileName)
{
	m_FileName.Format("%s", FileName);

	HFILE hFile = _lcreat(FileName, 0);
	
	// Header 정보를 저장한다 //
	SaveHeader(hFile);

	// Palette 정보를 저장한다 //
	SavePalette(hFile);

	// Image Descriptor 정보를 저장한다 //
	SaveDescriptor(hFile);

	// Packet Buffer 생성 //
	m_pBuf = new BYTE[255];
	
	// 실질적인 Encoding을 한다 //
	LZW_Encode(hFile);

	// Packet Buffer 제거 //
	delete [] m_pBuf;
		
	_lclose(hFile);
}

void CGif::SaveHeader(HFILE hFile)
{
	// 사전에 이미지 넓이와 높이를 지정해주어야함 //

	m_Header.Packed = 247;
	m_Header.BackgroundColor = 0;
	m_Header.AspectRatio = 0;

	_lwrite(hFile, "GIF", 3);
	_lwrite(hFile, "87a", 3);
	_lwrite(hFile, (LPSTR)&m_Header.ScreenWidth, sizeof(WORD));
	_lwrite(hFile, (LPSTR)&m_Header.ScreenHeight, sizeof(WORD));
	_lwrite(hFile, (LPSTR)&m_Header.Packed, 1);
	_lwrite(hFile, (LPSTR)&m_Header.BackgroundColor, 1);
	_lwrite(hFile, (LPSTR)&m_Header.AspectRatio, 1);

}

void CGif::SavePalette(HFILE hFile)
{
	int i;		
	BYTE RGB[3];

	for(i=0; i<256; i++)	
	{
		RGB[0] = GetRValue(m_Pal[i]);
		RGB[1] = GetGValue(m_Pal[i]);
		RGB[2] = GetBValue(m_Pal[i]);
		_lwrite(hFile, (LPSTR)RGB, 3);
	}
}

void CGif::SaveDescriptor(HFILE hFile)
{	
	m_Descriptor.Separator = 44;
	m_Descriptor.Left = 0;
	m_Descriptor.Top = 0;
	m_Descriptor.Width = GetWidth();
	m_Descriptor.Height = GetHeight();
	m_Descriptor.Packed = 0;

	_lwrite(hFile, (LPSTR)&m_Descriptor.Separator, 1);
	_lwrite(hFile, (LPSTR)&m_Descriptor.Left, sizeof(WORD));
	_lwrite(hFile, (LPSTR)&m_Descriptor.Top, sizeof(WORD));
	_lwrite(hFile, (LPSTR)&m_Descriptor.Width, sizeof(WORD));
	_lwrite(hFile, (LPSTR)&m_Descriptor.Height, sizeof(WORD));
	_lwrite(hFile, (LPSTR)&m_Descriptor.Packed, 1);
}

void CGif::OutToCodeStream(WORD Code)
{	
	WORD tCode = Code;
	int i;
	BYTE Bit;
	for(i=0; i<m_CodeSize; i++)
	{
		Bit = tCode & 0x01;
		SetNextBit(Bit);
		tCode = tCode >> 1;
	}	
}

void CGif::SetNextBit(BYTE Bit)
{
	static BYTE Buf = 0;	
	if(m_BitCount == 0)
		Buf = 0;
	
	Buf = Buf|(Bit << m_BitCount);
	m_BitCount++;

	if(m_BitCount == 8)
	{
		SetNextByte(Buf);
		m_BitCount = 0;	
	}
}

void CGif::SetNextByte(BYTE Buf)
{		
	m_BlockByteCount++;
	m_pBuf[m_BlockByteCount] = Buf;

	if(m_BlockByteCount == 254)
	{
		m_pBuf[0] = m_BlockByteCount;
		_lwrite(m_hFile, (LPSTR)m_pBuf, m_BlockByteCount+1);
		m_BlockByteCount = 0;
	}	
}

WORD CGif::GetCode(BYTE * p, int Length)
{
	WORD i, j;
	BOOL Flag;
	WORD Code = 65535;

	for(i=0; i<4096; i++)
	{
		if(Length == m_pTableLength[i])
		{
			Flag = TRUE;
			for(j=0; j<Length; j++)
			{
				if(p[j] != m_pTable[i][j])
				{
					Flag = FALSE;
					break;
				}
			}
			if(Flag == TRUE)
			{
				Code = i;
				break;
			}
		}
	}

	return Code;
}

void CGif::SaveGIF(LPSTR FileName, int Width, int Height, COLORREF * pPal, BYTE *pData)
{	
	int i;

	// pData는 BMP형식의 버퍼
	// BMP의 실제 버퍼 넓이 //

	int rWidth = (Width + 3)/4*4;

	if(m_pData != NULL)
		delete [] m_pData;

	m_pData = new BYTE[Width * Height];
	
	for(i=0; i<Height; i++)
		memcpy(&m_pData[i * Width], &pData[(Height - 1 - i) * rWidth], Width);	

	m_Header.ScreenWidth = Width;
	m_Header.ScreenHeight = Height;

	memcpy(m_Pal, pPal, 256 * sizeof(COLORREF));

	SaveGIF(FileName);	
}

void CGif::ProcessInterlaced()
{
	int Width = GetWidth();
	int Height = GetHeight();
	int i, line = 0;
	BYTE *p = new BYTE[Width * Height];
	BOOL *pFlag = new BOOL[Height];

	memcpy(p, m_pData, Width * Height);
	memset(m_pData, 0, Width * Height);
	memset(pFlag, 0, sizeof(BOOL) * Height);

	// First pass //
	for(i=0; i<Height; i+=8)
	{
		memcpy(&m_pData[i*Width], &p[line * Width], Width);
		line++;
		pFlag[i] = TRUE;
	}

	// Second pass //
	for(i=4; i<Height; i+=8)
	{
		memcpy(&m_pData[i*Width], &p[line * Width], Width);
		line++;
		pFlag[i] = TRUE;
	}

	// third pass //
	for(i=2; i<Height; i+=4)
	{
		memcpy(&m_pData[i*Width], &p[line * Width], Width);
		line++;
		pFlag[i] = TRUE;
	}

	// fourth pass //
	for(i=1; i<Height; i++)
	{
		if(!pFlag[i])
		{
			memcpy(&m_pData[i*Width], &p[line * Width], Width);
			line++;
		}
	}

	delete [] p;
	delete [] pFlag;
}
