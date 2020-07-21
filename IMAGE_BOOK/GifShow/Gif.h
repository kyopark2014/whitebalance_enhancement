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
	void LoadGIF(LPSTR FileName); // Gif를 읽어들인다.
	void LoadHeader(BYTE *p); // Header를 읽어들인다.
	void LoadPalette(BYTE *p); // Palette를 읽어들인다.
	void LoadDescriptor(BYTE *p); // Descriptor를 읽어들인다.
	int Skip(BYTE *p); // 기타 부분을 뛰어넘는다.
	void LZW_Decode(BYTE *p); // LZW Decoding Rountine
	BYTE GetNextByte(); // 버퍼에서 다음 한 바이트를 읽어온다.
	BYTE GetNextBit(); // 버퍼에서 다음 한 비트를 읽어온다.
	WORD GetNextCode(); // 버퍼에서 지정된 길이의 코드를 읽어온다.	
	void OutToCharStream(int idx); // idx번째 StringTable 내용을 출력
	void ProcessInterlaced(); // Interlaced mode일 경우 재배열한다.
	
	// GIF Save Rountines //	
	void SaveGIF(LPSTR FileName, int Width, int Height, COLORREF *pPal, BYTE *pData); // GIF파일을 저장한다(팔레트 지정).
	void SaveGIF(LPSTR FileName); // GIF파일을 저장한다.
	void SaveHeader(HFILE hFile); // Header를 저장한다.
	void SavePalette(HFILE hFile); // Palette를 저장한다.
	void SaveDescriptor(HFILE hFile); // Descriptor를 저장한다.
	void LZW_Encode(HFILE hFile); // LZW Encoding Routine
	WORD GetCode(BYTE *p, int Length); // 주어진 스트링을 테이블에서 찾아 index를 반환한다.
	void SetNextByte(BYTE Buf); // 한 바이트를 출력하는 함수.
	void SetNextBit(BYTE Bit); // 한 비트를 출력하는 함수.
	void OutToCodeStream(WORD Code); // Code를 비트스트림으로 출력하는 함수.
	
	// Decode/Encode 공용 함수들 //
	void OnClearCode();	 // ClearCode를 만났을 때의 처리
	void InitStringTable();	 // String Table을 초기화
	void ClearData(); // ImageData 초기화	
	
	// Image 관련 함수들 //
	int GetHeight(); // 이미지의 높이를 구한다.
	int GetWidth();	 // 이미지의 넓이를 구한다.
	
	GIFHEADER m_Header; // GIF Header 정보 구조체
	GIFDESCRIPTOR m_Descriptor; // GIF Descriptor 정보 구조체

	CString m_FileName; // GIF FileName
	
	COLORREF m_Pal[256]; // Palette

	BYTE * m_pData; // Image Data
	BYTE * m_pBuf; // Buffer
	
	int m_BitCount; // GetNextBit에서 쓰임
	WORD m_threshold; // Compression Size를 증가시키기 직전의 코드길이
	int m_BlockByteCount; // SubBlockSize Counting을 위해 쓰임

	BYTE ** m_pTable; // String Table
	int * m_pTableLength; // String Table
	int m_CharIndex; // Character Stream Index
	int m_TableIndex; // String Table Index
	int m_CodeSize; // 현재 코딩되는 코드사이즈

	HFILE m_hFile;

	
	CGif();
	virtual ~CGif();

};

#endif // !defined(AFX_GIF_H__B20DF556_3F92_11D2_B315_444553540000__INCLUDED_)
