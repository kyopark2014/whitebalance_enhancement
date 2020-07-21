// GifShowDoc.h : interface of the CGifShowDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GIFSHOWDOC_H__91B5210D_5186_11D2_BE06_006097ADB880__INCLUDED_)
#define AFX_GIFSHOWDOC_H__91B5210D_5186_11D2_BE06_006097ADB880__INCLUDED_

#include "BaseImage.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CGifShowDoc : public CDocument
{
protected: // create from serialization only
	CGifShowDoc();
	DECLARE_DYNCREATE(CGifShowDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGifShowDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CBaseImage *m_pImage;
	virtual ~CGifShowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGifShowDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIFSHOWDOC_H__91B5210D_5186_11D2_BE06_006097ADB880__INCLUDED_)
