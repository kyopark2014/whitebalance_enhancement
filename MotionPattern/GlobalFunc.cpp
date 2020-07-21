//
// File       : GlobalFunc.cpp
// Desc       : 전역으로 쓰는 함수덜 모음
//
// Copyright(c) 2002 Hanyang Univ. Artificial Life Lab.
//

#include "stdafx.h"
#include "shlwapi.h"
#include "GlobalFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "shlwapi.lib")
#pragma comment(linker, "/opt:noref")

//////////////////////////////////////////////////////////////////////
// 메시지 관련

// 잠시 대기
void __wait( DWORD dwMilliSec ) 
{
	MSG msg;
	DWORD dwStart = GetTickCount();
	while( GetTickCount() - dwStart < dwMilliSec ) 
	{
		while( ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) 
		{
			::TranslateMessage( &msg );
			::DispatchMessage( &msg );
		}
	}
}

// 남은 메시지 전부 처리
void __doEvents( void )
{
	MSG msg;
	while( ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) 
	{
		::TranslateMessage( &msg );
		::DispatchMessage( &msg );
	}
}

//////////////////////////////////////////////////////////////////////
// 경로 관련

// 상대 경로 추출
BOOL __getRelativePath( CString strBasePath, CString& strAbsPath )
{
	BOOL  bRet;
	TCHAR szPath[MAX_PATH] = _T("");

	if( strBasePath.GetAt(strBasePath.GetLength() - 1) != '\\' )
		strBasePath += "\\";

	if( ::PathRelativePathTo(szPath, (LPCTSTR) strBasePath, FILE_ATTRIBUTE_NORMAL,
		                       (LPCTSTR) strAbsPath, FILE_ATTRIBUTE_NORMAL) != TRUE ) 
	{
		bRet = ::PathIsRelative( (LPCTSTR) strAbsPath );
	}
	else 
	{
		strAbsPath = szPath;
		if( strAbsPath.Left(2) == ".\\" )
			strAbsPath.Delete( 0, 2 );

		bRet = ::PathIsRelative( strAbsPath );
	}

	return bRet;
}

// 절대 경로 추출
void __getAbsolutePath( CString strBasePath, CString& strRelPath )
{
	if( ::PathIsRelative((LPCTSTR) strRelPath) )
	{
		if( strBasePath.GetAt(strBasePath.GetLength() - 1) == '\\' )
			strBasePath.Delete( strBasePath.GetLength() - 1 );

		int pos, pos2;
		while( (pos = strRelPath.Find("..", 0)) != -1 )
		{
			strRelPath.Delete( 0, 3 );

			pos2 = strBasePath.ReverseFind( '\\' );
			if( pos2 >= 0 )
				strBasePath.Delete( pos2, strBasePath.GetLength() - pos2 );
		}
		strRelPath = strBasePath + "\\" + strRelPath;
	}
}

// 실행 파일 경로 추출
CString __getExePath( void )
{
	CString strExePath      = _T("");

	TCHAR exefile[_MAX_DIR] = _T("");
	TCHAR drive[_MAX_DRIVE] = _T(""), dir[_MAX_DIR] = _T("");
  TCHAR fname[_MAX_FNAME] = _T(""), ext[_MAX_EXT] = _T("");

	::GetModuleFileName( NULL, exefile, _MAX_DIR );
	_tsplitpath( exefile, drive, dir, fname, ext );

	strExePath.Format( "%s%s", drive, dir );

	return strExePath;
}

// 폴더 생성
BOOL __createFolder( CString strDir )
{
	HANDLE  hFile;						  // File Handle
	BOOL    bSuccess;						// BOOL used to test if Create Directory was successful
	int     cnt = 0;						// Counter
	CString strTmp = _T("");		// Temporary CString Object

  CStringArray    aPath;			// CString Array to hold Directory Structures
	WIN32_FIND_DATA fi;		      // File Information Structure

	// Before we go to a lot of work.  
	// Does the file exist
	hFile = FindFirstFile( strDir, &fi );

	// if the file exists and it is a directory
	if( fi.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY )
	{
		// Directory Exists close file and return
		FindClose( hFile );
		return TRUE;
	}

	aPath.RemoveAll();					                      // Not really necessary - Just habit
	for( cnt = 0; cnt < strDir.GetLength(); cnt++ )   // Parse the supplied CString Directory String
	{									
		if( strDir.GetAt(cnt) != _T('\\') )	            // if the Charachter is not a \ 
			strTmp += strDir.GetAt( cnt );		            // else astrDir character to Temp String
		else
		{
			aPath.Add( strTmp );				                  // if the Character is a \ AstrDir the Temp String to the CString Array
			strTmp += _T("\\");			                      // Now astrDir the \ to the strTmpp string
		}
		if( cnt == strDir.GetLength() - 1 )		          // If we reached the end of the file astrDir the remaining string
			aPath.Add( strTmp );
	}

	// Close the file
	FindClose( hFile );
	
	// Now lets cycle through the String Array and create each directory in turn
	for( cnt = 1; cnt < aPath.GetSize(); cnt++ )
	{
		strTmp = aPath.GetAt( cnt );

		// If the Directory exists it will return a false
    bSuccess  = CreateDirectory( strTmp, NULL );

		// If we were successful we set the abSuccessributes to normal
		if( bSuccess )
			SetFileAttributes( strTmp, FILE_ATTRIBUTE_NORMAL );
	}
	aPath.RemoveAll();

	// Now lets see if the directory was successfully created
	hFile = FindFirstFile( strDir, &fi );

	// if the file exists and it is a directory
	if( fi.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY )
	{
		// Directory Exists close file and return
		FindClose( hFile );
		return TRUE;
	}
	else
	{
		FindClose( hFile );
		return FALSE;
	}
}

// 폴더 복사
BOOL __copyFolder( CString strSrcDir, CString strDstDir, LPCTSTR lpszFilter,
				         BOOL bIncSubFolder )
{
	if( strSrcDir.Right(1) != _T("\\") )
		strSrcDir += _T("\\");

	if( strDstDir.Right(1) == _T("\\") )
		strDstDir = strDstDir.Left( strDstDir.GetLength() - 1 );

	CFileFind ff;
	if( !ff.FindFile(strDstDir) )
		__createFolder( strDstDir );

	CString strFilter = lpszFilter;
	strFilter = strSrcDir + strFilter;

	CString strSourceFile, strTargetFile;
	BOOL bSuccess = TRUE;

	if( ff.FindFile(strFilter) )
	{
		BOOL bFlag = TRUE;
		while( bFlag )
		{
			bFlag = ff.FindNextFile();

			if( ff.IsDots() ) continue;

			if( ff.IsDirectory() && bIncSubFolder )
			{
				strSourceFile = strSrcDir + ff.GetFileName();
				strTargetFile = strDstDir + _T("\\") + ff.GetFileName();

				__copyFolder( strSourceFile, strTargetFile, lpszFilter, bIncSubFolder );
			}
			else
			{
				strSourceFile = ff.GetFilePath();
				strTargetFile = strDstDir + _T("\\") + ff.GetFileName();

				if( !::CopyFile(strSourceFile, strTargetFile, FALSE) )
					bSuccess = FALSE;
			}
		}
	}

	ff.Close();

	return bSuccess;
}

BOOL __deleteFolder( CString strDelDir, BOOL bRecycle )
{
	CFileFind   ff;
	CFileStatus fs;

	if( strDelDir.Right(1) != _T("\\") )
		strDelDir += _T("\\");

	CString strFilter = strDelDir + _T("*.*");
	
	if( ff.FindFile(strFilter) )
	{
		BOOL bFlag = TRUE;
		while( bFlag )
		{
			bFlag = ff.FindNextFile();

			if( ff.IsDots() ) continue;

			if( ff.IsDirectory() )
			{
				CString strFolder = strDelDir + ff.GetFileName();

				if( !__deleteFolder(strFolder, bRecycle) )
				{
					ff.Close();
					return FALSE;
				}

				if( ::RemoveDirectory(strFolder) == 0 )
				{
					ff.Close();
					return FALSE;
				}
			}
			
			CString strDelFile = strDelDir + ff.GetFileName(); 
			__deleteFile( strDelFile, bRecycle );
		}
	}

	ff.Close();

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 파일 관련

// 파일 경로 추출
CString __getPath( LPCTSTR lpszFileName )
{
	TCHAR drive[_MAX_DRIVE] = _T(""), dir[_MAX_DIR] = _T("");
  TCHAR fname[_MAX_FNAME] = _T(""), ext[_MAX_EXT] = _T("");

	_tsplitpath( lpszFileName, drive, dir, fname, ext );

	CString strPath = _T("");
	strPath.Format( "%s%s", drive, dir );
	
	return strPath;
}

// 파일명 추출
CString __getName( LPCTSTR lpszFileName )
{
	TCHAR drive[_MAX_DRIVE] = _T(""), dir[_MAX_DIR] = _T("");
  TCHAR fname[_MAX_FNAME] = _T(""), ext[_MAX_EXT] = _T("");

	_tsplitpath( lpszFileName, drive, dir, fname, ext );

	CString strName = _T("");
	strName.Format( "%s", fname );
	
	return strName;
}

// 파일 확장자 추출
CString __getFileExt( LPCTSTR lpszFileName )
{
	TCHAR drive[_MAX_DRIVE] = _T(""), dir[_MAX_DIR] = _T("");
  TCHAR fname[_MAX_FNAME] = _T(""), ext[_MAX_EXT] = _T("");

	_tsplitpath( lpszFileName, drive, dir, fname, ext );

	CString strExt = _T("");
	strExt.Format( "%s", ext );
	
	return strExt;
}

// 파일 존재 여부
BOOL __isFileExist( LPCTSTR lpszFileName )
{
	CFileFind ff;
	BOOL bFind = ff.FindFile( lpszFileName );
	ff.Close();

	return bFind;
}

// 파일 삭제
BOOL __deleteFile( CString strFilePath, BOOL bRecycle )
{
	if( bRecycle )
	{
		SHFILEOPSTRUCT DelOption;

		int nSize   = strFilePath.GetLength();
		TCHAR *pBuf = new TCHAR[nSize + 2];

		_tcscpy( pBuf, strFilePath.GetBuffer(nSize) );

		pBuf[nSize]     = '\0';
		pBuf[nSize + 1] = '\0';

		memset( &DelOption, 0, sizeof(SHFILEOPSTRUCT) );
		DelOption.wFunc   = FO_DELETE;
		DelOption.pFrom   = pBuf;
		DelOption.fFlags  = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | 
                        FOF_ALLOWUNDO | FOF_NOERRORUI ;

		nSize = ::SHFileOperation( &DelOption );
		delete[] pBuf;

		if( nSize != 0 ) return FALSE;
	}
	else
	{
		::DeleteFile( strFilePath );
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// INI 파일 관련

CString __getINIfileValue( LPCTSTR lpszIniFile, LPCTSTR lpszSection, LPCTSTR lpszKey )
{
	LPCTSTR pszDefaultVal = _T("");
	TCHAR   szVal[255]    = _T("");

	GetPrivateProfileString( lpszSection, lpszKey, pszDefaultVal, szVal, 
							             sizeof(TCHAR) * 255, lpszIniFile );

	return CString( szVal );
}
