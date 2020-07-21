// Gif.h: interface for the CGif class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GIF_H__B20DF556_3F92_11D2_B315_444553540000__INCLUDED_)
#define AFX_GIF_H__B20DF556_3F92_11D2_B315_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

struct GIFHEADER
{
	BYTE Signature[3]; 
	BYTE Version[3];
	WORD ScreenWidth;
	WORD ScreenHeight;
	BYTE Packed;
	BYTE BackgroundColor;
	BYTE AspectRatio;
};

struct GIFDESCRIPTOR
{
	BYTE Separator;
	WORD Left;
	WORD Top;
	WORD Width;
	WORD Height;
	BYTE Packed;
};

class CGif  
{
public:		
	
	// GIF Load Rountines //
	void LoadGIF(LPSTR FileName); // Gif�� �о���δ�.
	void LoadHeader(BYTE *p); // Header�� �о���δ�.
	void LoadPalette(BYTE *p); // Palette�� �о���δ�.
	void LoadDescriptor(BYTE *p); // Descriptor�� �о���δ�.
	int Skip(BYTE *p); // ��Ÿ �κ��� �پ�Ѵ´�.
	void LZW_Decode(BYTE *p); // LZW Decoding Rountine
	BYTE GetNextByte(); // ���ۿ��� ���� �� ����Ʈ�� �о�´�.
	BYTE GetNextBit(); // ���ۿ��� ���� �� ��Ʈ�� �о�´�.
	WORD GetNextCode(); // ���ۿ��� ������ ������ �ڵ带 �о�´�.	
	void OutToCharStream(int idx); // idx��° StringTable ������ ���
	void ProcessInterlaced(); // Interlaced mode�� ��� ��迭�Ѵ�.
	
	// GIF Save Rountines //	
	void SaveGIF(LPSTR FileName, int Width, int Height, COLORREF *pPal, BYTE *pData); // GIF������ �����Ѵ�(�ȷ�Ʈ ����).
	void SaveGIF(LPSTR FileName); // GIF������ �����Ѵ�.
	void SaveHeader(HFILE hFile); // Header�� �����Ѵ�.
	void SavePalette(HFILE hFile); // Palette�� �����Ѵ�.
	void SaveDescriptor(HFILE hFile); // Descriptor�� �����Ѵ�.
	void LZW_Encode(HFILE hFile); // LZW Encoding Routine
	WORD GetCode(BYTE *p, int Length); // �־��� ��Ʈ���� ���̺��� ã�� index�� ��ȯ�Ѵ�.
	void SetNextByte(BYTE Buf); // �� ����Ʈ�� ����ϴ� �Լ�.
	void SetNextBit(BYTE Bit); // �� ��Ʈ�� ����ϴ� �Լ�.
	void OutToCodeStream(WORD Code); // Code�� ��Ʈ��Ʈ������ ����ϴ� �Լ�.
	
	// Decode/Encode ���� �Լ��� //
	void OnClearCode();	 // ClearCode�� ������ ���� ó��
	void InitStringTable();	 // String Table�� �ʱ�ȭ
	void ClearData(); // ImageData �ʱ�ȭ	
	
	// Image ���� �Լ��� //
	int GetHeight(); // �̹����� ���̸� ���Ѵ�.
	int GetWidth();	 // �̹����� ���̸� ���Ѵ�.
	
	GIFHEADER m_Header; // GIF Header ���� ����ü
	GIFDESCRIPTOR m_Descriptor; // GIF Descriptor ���� ����ü

	CString m_FileName; // GIF FileName
	
	COLORREF m_Pal[256]; // Palette

	BYTE * m_pData; // Image Data
	BYTE * m_pBuf; // Buffer
	
	int m_BitCount; // GetNextBit���� ����
	WORD m_threshold; // Compression Size�� ������Ű�� ������ �ڵ����
	int m_BlockByteCount; // SubBlockSize Counting�� ���� ����

	BYTE ** m_pTable; // String Table
	int * m_pTableLength; // String Table
	int m_CharIndex; // Character Stream Index
	int m_TableIndex; // String Table Index
	int m_CodeSize; // ���� �ڵ��Ǵ� �ڵ������

	HFILE m_hFile;

	
	CGif();
	virtual ~CGif();

};

#endif // !defined(AFX_GIF_H__B20DF556_3F92_11D2_B315_444553540000__INCLUDED_)
