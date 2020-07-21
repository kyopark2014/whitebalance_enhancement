// JpgShowDoc.h : interface of the CJpgShowDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JPGSHOWDOC_H__73AF270D_515E_11D2_BE06_006097ADB880__INCLUDED_)
#define AFX_JPGSHOWDOC_H__73AF270D_515E_11D2_BE06_006097ADB880__INCLUDED_

#include "BaseImage.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CJpgShowDoc : public CDocument
{
protected: // create from serialization only
	CJpgShowDoc();
	DECLARE_DYNCREATE(CJpgShowDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJpgShowDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CBaseImage *m_pImage;
	virtual ~CJpgShowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJpgShowDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JPGSHOWDOC_H__73AF270D_515E_11D2_BE06_006097ADB880__INCLUDED_)
