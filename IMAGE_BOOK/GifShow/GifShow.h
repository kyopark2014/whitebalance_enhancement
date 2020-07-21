// GifShow.h : main header file for the GIFSHOW application
//

#if !defined(AFX_GIFSHOW_H__257CFD95_5143_11D2_A13E_006097AEB8A7__INCLUDED_)
#define AFX_GIFSHOW_H__257CFD95_5143_11D2_A13E_006097AEB8A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGifShowApp:
// See GifShow.cpp for the implementation of this class
//

class CGifShowApp : public CWinApp
{
public:
	CGifShowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGifShowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGifShowApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIFSHOW_H__257CFD95_5143_11D2_A13E_006097AEB8A7__INCLUDED_)
