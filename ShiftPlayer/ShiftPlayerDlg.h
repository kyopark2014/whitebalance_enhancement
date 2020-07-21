// ShiftPlayerDlg.h : header file
//

#if !defined(AFX_SHIFTPLAYERDLG_H__57BC4AE0_D71C_4B70_BA86_650BCD3C5B29__INCLUDED_)
#define AFX_SHIFTPLAYERDLG_H__57BC4AE0_D71C_4B70_BA86_650BCD3C5B29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseImage.h"
#include "GlobalFunc.h"
#include "BaseImage.h"

/////////////////////////////////////////////////////////////////////////////
// CShiftPlayerDlg dialog

class CShiftPlayerDlg : public CDialog
{
// Construction
public:
	void LoadFigure();
	void ShowFigure();
	CBaseImage *m_pImage;
	int Width,Height;
	int wWidth,wHeight;
	bool Toggle;
	int **R,**G,**B;
	int **Rt,**Gt,**Bt;
	int count;

	CShiftPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShiftPlayerDlg)
	enum { IDD = IDD_SHIFTPLAYER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShiftPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShiftPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdatePlay(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHIFTPLAYERDLG_H__57BC4AE0_D71C_4B70_BA86_650BCD3C5B29__INCLUDED_)
