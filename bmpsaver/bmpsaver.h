// bmpsaver.h : main header file for the BMPSAVER application
//

#if !defined(AFX_BMPSAVER_H__B375C88C_BC23_4B01_8A97_E78C58764662__INCLUDED_)
#define AFX_BMPSAVER_H__B375C88C_BC23_4B01_8A97_E78C58764662__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBmpsaverApp:
// See bmpsaver.cpp for the implementation of this class
//

class CBmpsaverApp : public CWinApp
{
public:
	CBmpsaverApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpsaverApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBmpsaverApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPSAVER_H__B375C88C_BC23_4B01_8A97_E78C58764662__INCLUDED_)
