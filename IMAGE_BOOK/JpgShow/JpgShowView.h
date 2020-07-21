// JpgShowView.h : interface of the CJpgShowView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JPGSHOWVIEW_H__73AF270F_515E_11D2_BE06_006097ADB880__INCLUDED_)
#define AFX_JPGSHOWVIEW_H__73AF270F_515E_11D2_BE06_006097ADB880__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CJpgShowView : public CScrollView
{
protected: // create from serialization only
	CJpgShowView();
	DECLARE_DYNCREATE(CJpgShowView)

// Attributes
public:
	CJpgShowDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJpgShowView)
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
	virtual ~CJpgShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJpgShowView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in JpgShowView.cpp
inline CJpgShowDoc* CJpgShowView::GetDocument()
   { return (CJpgShowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JPGSHOWVIEW_H__73AF270F_515E_11D2_BE06_006097ADB880__INCLUDED_)
