//
// File : GlobalFunc.h
// Desc : �������� ���� �Լ��� ����
//
// Copyright(c) 2002 Hanyang Univ. Artificial Life Lab.
//

#ifndef __GLOBAL_FUNC_H__
#define __GLOBAL_FUNC_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// �޽��� ����
void    __wait( DWORD dwMilliSec = 100 );
void    __doEvents( void );

// ��� ����
BOOL    __getRelativePath( CString strBasePath, CString& strAbsPath );
void    __getAbsolutePath( CString strBasePath, CString& strRelPath );

CString __getExePath( void );

// ���� ����
BOOL    __createFolder( CString strDir );
BOOL    __copyFolder( CString strSrcDir, CString strDstDir, LPCTSTR lpszFilter = _T("*.*"), 
				            BOOL bIncSubFolder = TRUE );
BOOL    __deleteFolder( CString strDelDir, BOOL bRecycle = TRUE );

// ���� ����
CString __getPath( LPCTSTR lpszFileName );
CString __getName( LPCTSTR lpszFileName );
CString __getFileExt( LPCTSTR lpszFileName );

BOOL    __isFileExist( LPCTSTR lpszFileName );
BOOL    __deleteFile( CString strFilePath, BOOL bRecycle );

// INI ���� ����
CString __getINIfileValue( LPCTSTR lpszIniFile, LPCTSTR lpszSection, LPCTSTR lpszKey );

#endif