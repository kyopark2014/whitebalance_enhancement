// BmpShowView.h : interface of the CBmpShowView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPSHOWVIEW_H__BF378A6E_5199_11D2_B086_006097AD928B__INCLUDED_)
#define AFX_BMPSHOWVIEW_H__BF378A6E_5199_11D2_B086_006097AD928B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBmpShowView : public CScrollView
{
protected: // create from serialization only
	CBmpShowView();
	DECLARE_DYNCREATE(CBmpShowView)

// Attributes
public:
	CBmpShowDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpShowView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBmpShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBmpShowView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BmpShowView.cpp
inline CBmpShowDoc* CBmpShowView::GetDocument()
   { return (CBmpShowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPSHOWVIEW_H__BF378A6E_5199_11D2_B086_006097AD928B__INCLUDED_)
