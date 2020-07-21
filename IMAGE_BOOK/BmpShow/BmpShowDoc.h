// BmpShowDoc.h : interface of the CBmpShowDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPSHOWDOC_H__BF378A6C_5199_11D2_B086_006097AD928B__INCLUDED_)
#define AFX_BMPSHOWDOC_H__BF378A6C_5199_11D2_B086_006097AD928B__INCLUDED_

#include "BaseImage.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBmpShowDoc : public CDocument
{
protected: // create from serialization only
	CBmpShowDoc();
	DECLARE_DYNCREATE(CBmpShowDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpShowDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CBaseImage *m_pImage;
	virtual ~CBmpShowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBmpShowDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPSHOWDOC_H__BF378A6C_5199_11D2_B086_006097AD928B__INCLUDED_)
