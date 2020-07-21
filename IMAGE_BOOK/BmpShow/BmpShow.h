// BmpShow.h : main header file for the BMPSHOW application
//

#if !defined(AFX_BMPSHOW_H__BF378A64_5199_11D2_B086_006097AD928B__INCLUDED_)
#define AFX_BMPSHOW_H__BF378A64_5199_11D2_B086_006097AD928B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBmpShowApp:
// See BmpShow.cpp for the implementation of this class
//

class CBmpShowApp : public CWinApp
{
public:
	CBmpShowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpShowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBmpShowApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPSHOW_H__BF378A64_5199_11D2_B086_006097AD928B__INCLUDED_)
