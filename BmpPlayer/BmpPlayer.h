// BmpPlayer.h : main header file for the BMPPLAYER application
//

#if !defined(AFX_BMPPLAYER_H__921F926D_DF2D_4388_975F_15146EC027B9__INCLUDED_)
#define AFX_BMPPLAYER_H__921F926D_DF2D_4388_975F_15146EC027B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBmpPlayerApp:
// See BmpPlayer.cpp for the implementation of this class
//

class CBmpPlayerApp : public CWinApp
{
public:
	CBmpPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBmpPlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPPLAYER_H__921F926D_DF2D_4388_975F_15146EC027B9__INCLUDED_)
