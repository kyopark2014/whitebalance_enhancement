// ShiftPlayer.h : main header file for the SHIFTPLAYER application
//

#if !defined(AFX_SHIFTPLAYER_H__629F0A3A_DBED_400C_A97A_34AA00B0506C__INCLUDED_)
#define AFX_SHIFTPLAYER_H__629F0A3A_DBED_400C_A97A_34AA00B0506C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShiftPlayerApp:
// See ShiftPlayer.cpp for the implementation of this class
//

class CShiftPlayerApp : public CWinApp
{
public:
	CShiftPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShiftPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShiftPlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHIFTPLAYER_H__629F0A3A_DBED_400C_A97A_34AA00B0506C__INCLUDED_)
