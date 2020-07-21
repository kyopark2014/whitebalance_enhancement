// bmpsaverDlg.h : header file
//

#if !defined(AFX_BMPSAVERDLG_H__D97A041A_098B_4D14_86E8_A82DA493189D__INCLUDED_)
#define AFX_BMPSAVERDLG_H__D97A041A_098B_4D14_86E8_A82DA493189D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseImage.h"

/////////////////////////////////////////////////////////////////////////////
// CBmpsaverDlg dialog

class CBmpsaverDlg : public CDialog
{
// Construction
public:
	CBaseImage *m_pImage;
	int Width,Height;
	void Drawing(int Width,int Height,CDC* dc);
	CBmpsaverDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBmpsaverDlg)
	enum { IDD = IDD_BMPSAVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpsaverDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBmpsaverDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPSAVERDLG_H__D97A041A_098B_4D14_86E8_A82DA493189D__INCLUDED_)
