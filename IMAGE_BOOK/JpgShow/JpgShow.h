// JpgShow.h : main header file for the JPGSHOW application
//

#if !defined(AFX_JPGSHOW_H__73AF2705_515E_11D2_BE06_006097ADB880__INCLUDED_)
#define AFX_JPGSHOW_H__73AF2705_515E_11D2_BE06_006097ADB880__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CJpgShowApp:
// See JpgShow.cpp for the implementation of this class
//

class CJpgShowApp : public CWinApp
{
public:
	CJpgShowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJpgShowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CJpgShowApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JPGSHOW_H__73AF2705_515E_11D2_BE06_006097ADB880__INCLUDED_)
