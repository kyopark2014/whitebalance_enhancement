// bmpviewer.h : main header file for the BMPVIEWER application
//

#if !defined(AFX_BMPVIEWER_H__586D1C37_0DB7_4238_A8C2_481CDCD9FCBD__INCLUDED_)
#define AFX_BMPVIEWER_H__586D1C37_0DB7_4238_A8C2_481CDCD9FCBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBmpviewerApp:
// See bmpviewer.cpp for the implementation of this class
//

class CBmpviewerApp : public CWinApp
{
public:
	CBmpviewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpviewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBmpviewerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPVIEWER_H__586D1C37_0DB7_4238_A8C2_481CDCD9FCBD__INCLUDED_)
