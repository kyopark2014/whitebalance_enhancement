// pdp_viewerDlg.h : header file
//

#if !defined(AFX_PDP_VIEWERDLG_H__E8699717_9C68_4C00_86DE_640CF55D928B__INCLUDED_)
#define AFX_PDP_VIEWERDLG_H__E8699717_9C68_4C00_86DE_640CF55D928B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VideoWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CPdp_viewerDlg dialog

class CPdp_viewerDlg : public CDialog
{
// Construction
public:
	BOOL createVideoWnd();
	CVideoWnd m_pdp;
	
	CPdp_viewerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPdp_viewerDlg)
	enum { IDD = IDD_PDP_VIEWER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPdp_viewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPdp_viewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFileOpen();
	afx_msg void OnMoviePause();
	afx_msg void OnMoviePlay();
	afx_msg void OnMovieStop();
	afx_msg void OnQuitApp();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDP_VIEWERDLG_H__E8699717_9C68_4C00_86DE_640CF55D928B__INCLUDED_)
