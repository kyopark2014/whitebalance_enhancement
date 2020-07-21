//
// File : GlobalFunc.h
// Desc : 전역으로 쓰는 함수덜 모음
//
// Copyright(c) 2002 Hanyang Univ. Artificial Life Lab.
//

#ifndef __GLOBAL_FUNC_H__
#define __GLOBAL_FUNC_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 메시지 관련
void    __wait( DWORD dwMilliSec = 100 );
void    __doEvents( void );

// 경로 관련
BOOL    __getRelativePath( CString strBasePath, CString& strAbsPath );
void    __getAbsolutePath( CString strBasePath, CString& strRelPath );

CString __getExePath( void );

// 폴더 관련
BOOL    __createFolder( CString strDir );
BOOL    __copyFolder( CString strSrcDir, CString strDstDir, LPCTSTR lpszFilter = _T("*.*"), 
				            BOOL bIncSubFolder = TRUE );
BOOL    __deleteFolder( CString strDelDir, BOOL bRecycle = TRUE );

// 파일 관련
CString __getPath( LPCTSTR lpszFileName );
CString __getName( LPCTSTR lpszFileName );
CString __getFileExt( LPCTSTR lpszFileName );

BOOL    __isFileExist( LPCTSTR lpszFileName );
BOOL    __deleteFile( CString strFilePath, BOOL bRecycle );

// INI 파일 관련
CString __getINIfileValue( LPCTSTR lpszIniFile, LPCTSTR lpszSection, LPCTSTR lpszKey );

#endif