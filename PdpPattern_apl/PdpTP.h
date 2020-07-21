#if !defined(AFX_PDPTP_H__256A3839_50FB_4212_938C_D5F1D069B942__INCLUDED_)
#define AFX_PDPTP_H__256A3839_50FB_4212_938C_D5F1D069B942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PdpTP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPdpTP view

class CPdpTP : public CView
{
public:
	int Ar,Ag,Ab,Br,Bg,Bb;
	int dr,dg,db;

	CPdpTP();           // protected constructor used by dynamic creation
	virtual ~CPdpTP();

// Attributes
public:

// Operations
public:
	float CalAPL(CClientDC* dc);
	void Drawing_P1(int maxx,int maxy,CClientDC* dc);
	void Drawing_P2(int maxx,int maxy,CClientDC* dc);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPdpTP)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPdpTP)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDPTP_H__256A3839_50FB_4212_938C_D5F1D069B942__INCLUDED_)
