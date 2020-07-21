// pdp_viewer.h : main header file for the PDP_VIEWER application
//

#if !defined(AFX_PDP_VIEWER_H__FA92B111_24F7_404E_9CCD_1989AF4D0917__INCLUDED_)
#define AFX_PDP_VIEWER_H__FA92B111_24F7_404E_9CCD_1989AF4D0917__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPdp_viewerApp:
// See pdp_viewer.cpp for the implementation of this class
//

class CPdp_viewerApp : public CWinApp
{
public:
	CPdp_viewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPdp_viewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPdp_viewerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDP_VIEWER_H__FA92B111_24F7_404E_9CCD_1989AF4D0917__INCLUDED_)
