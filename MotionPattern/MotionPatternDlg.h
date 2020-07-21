// MotionPatternDlg.h : header file
//

#if !defined(AFX_MOTIONPATTERNDLG_H__7FA4E53A_F5B5_4723_9381_DAE0FEB8EB85__INCLUDED_)
#define AFX_MOTIONPATTERNDLG_H__7FA4E53A_F5B5_4723_9381_DAE0FEB8EB85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMotionPatternDlg dialog

#include "VideoWnd.h"
#include "GlobalFunc.h"
#include "BaseImage.h"

class CMotionPatternDlg : public CDialog
{
// Construction
public:
	BOOL createVideoWnd();
	CVideoWnd m_pdp;
	int Width,Height;
	CBaseImage *m_pImage;
	bool Toggle;

	CMotionPatternDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMotionPatternDlg)
	enum { IDD = IDD_MOTIONPATTERN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotionPatternDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMotionPatternDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuCapture(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMoviePause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMoviePlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMovieStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateQuitApp(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTIONPATTERNDLG_H__7FA4E53A_F5B5_4723_9381_DAE0FEB8EB85__INCLUDED_)
