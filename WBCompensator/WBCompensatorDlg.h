// WBCompensatorDlg.h : header file
//

#if !defined(AFX_WBCOMPENSATORDLG_H__E0D6500F_2803_44BE_A670_F688BD91E71E__INCLUDED_)
#define AFX_WBCOMPENSATORDLG_H__E0D6500F_2803_44BE_A670_F688BD91E71E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWBCompensatorDlg dialog

#include "VideoWnd.h"
#include "GlobalFunc.h"
#include "BaseImage.h"

class CWBCompensatorDlg : public CDialog
{
// Construction
public:
	CBaseImage *m_pImage;
	int Width,Height;
	int wWidth,wHeight;
	bool Toggle;
	int count;

	int RGBtableR[256];
	int RGBtableG[256];
	int RGBtableB[256];

	int chr2num(char *str);
	void LoadFigure(int FigureNum);
	void CompensateFigure(int FigureNum);
	CWBCompensatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWBCompensatorDlg)
	enum { IDD = IDD_WBCOMPENSATOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWBCompensatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWBCompensatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnUpdateCompensation(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateShowFigures(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WBCOMPENSATORDLG_H__E0D6500F_2803_44BE_A670_F688BD91E71E__INCLUDED_)
