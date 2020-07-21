// GifShowView.h : interface of the CGifShowView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GIFSHOWVIEW_H__91B52127_5186_11D2_BE06_006097ADB880__INCLUDED_)
#define AFX_GIFSHOWVIEW_H__91B52127_5186_11D2_BE06_006097ADB880__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGifShowView : public CScrollView
{
protected: // create from serialization only
	CGifShowView();
	DECLARE_DYNCREATE(CGifShowView)

// Attributes
public:
	CGifShowDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGifShowView)
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
	virtual ~CGifShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGifShowView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GifShowView.cpp
inline CGifShowDoc* CGifShowView::GetDocument()
   { return (CGifShowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIFSHOWVIEW_H__91B52127_5186_11D2_BE06_006097ADB880__INCLUDED_)
