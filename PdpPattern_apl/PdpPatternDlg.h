// PdpPatternDlg.h : header file
//

#if !defined(AFX_PDPPATTERNDLG_H__95217B9A_90A6_4D99_93CD_B9E1D49E5807__INCLUDED_)
#define AFX_PDPPATTERNDLG_H__95217B9A_90A6_4D99_93CD_B9E1D49E5807__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPdpPatternDlg dialog

#include "PdpTp.h"

class CPdpPatternDlg : public CDialog
{
// Construction
public:
	void Draw(int Tp);
	CPdpPatternDlg(CWnd* pParent = NULL);	// standard constructor

	CPdpTP pp;
	BOOL m_bIsWindow;
	int Tp;

// Dialog Data
	//{{AFX_DATA(CPdpPatternDlg)
	enum { IDD = IDD_PDPPATTERN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPdpPatternDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPdpPatternDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDPPATTERNDLG_H__95217B9A_90A6_4D99_93CD_B9E1D49E5807__INCLUDED_)
