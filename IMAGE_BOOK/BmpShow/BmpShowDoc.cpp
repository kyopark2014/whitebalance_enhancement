// BmpShowDoc.cpp : implementation of the CBmpShowDoc class
//

#include "stdafx.h"
#include "BmpShow.h"

#include "BmpShowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpShowDoc

IMPLEMENT_DYNCREATE(CBmpShowDoc, CDocument)

BEGIN_MESSAGE_MAP(CBmpShowDoc, CDocument)
	//{{AFX_MSG_MAP(CBmpShowDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpShowDoc construction/destruction

CBmpShowDoc::CBmpShowDoc()
{
	// TODO: add one-time construction code here

}

CBmpShowDoc::~CBmpShowDoc()
{
}

BOOL CBmpShowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_pImage=NULL;
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBmpShowDoc serialization

void CBmpShowDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBmpShowDoc diagnostics

#ifdef _DEBUG
void CBmpShowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBmpShowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmpShowDoc commands

BOOL CBmpShowDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	m_pImage=new CBaseImage;
	m_pImage->LoadBmp(lpszPathName);
	return TRUE;
}

BOOL CBmpShowDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pImage)
		m_pImage->SaveImage(lpszPathName);
	return CDocument::OnSaveDocument(lpszPathName);
}
