// bmpviewerDlg.h : header file
//

#if !defined(AFX_BMPVIEWERDLG_H__8E3323CC_1ECE_4297_A061_A8BBDF6E4ED7__INCLUDED_)
#define AFX_BMPVIEWERDLG_H__8E3323CC_1ECE_4297_A061_A8BBDF6E4ED7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBmpviewerDlg dialog
#include "BaseImage.h"

class CBmpviewerDlg : public CDialog
{
// Construction
public:
	CBaseImage *m_pImage;

	CBmpviewerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBmpviewerDlg)
	enum { IDD = IDD_BMPVIEWER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpviewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBmpviewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPVIEWERDLG_H__8E3323CC_1ECE_4297_A061_A8BBDF6E4ED7__INCLUDED_)
