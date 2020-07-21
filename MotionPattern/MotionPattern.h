// MotionPattern.h : main header file for the MOTIONPATTERN application
//

#if !defined(AFX_MOTIONPATTERN_H__8CB680FA_EAC1_46F9_B313_D3E1CF7DFAE6__INCLUDED_)
#define AFX_MOTIONPATTERN_H__8CB680FA_EAC1_46F9_B313_D3E1CF7DFAE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMotionPatternApp:
// See MotionPattern.cpp for the implementation of this class
//

class CMotionPatternApp : public CWinApp
{
public:
	CMotionPatternApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotionPatternApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMotionPatternApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTIONPATTERN_H__8CB680FA_EAC1_46F9_B313_D3E1CF7DFAE6__INCLUDED_)
