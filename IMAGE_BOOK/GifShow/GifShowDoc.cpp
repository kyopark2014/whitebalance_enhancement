// GifShowDoc.cpp : implementation of the CGifShowDoc class
//

#include "stdafx.h"
#include "GifShow.h"

#include "GifShowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGifShowDoc

IMPLEMENT_DYNCREATE(CGifShowDoc, CDocument)

BEGIN_MESSAGE_MAP(CGifShowDoc, CDocument)
	//{{AFX_MSG_MAP(CGifShowDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGifShowDoc construction/destruction

CGifShowDoc::CGifShowDoc()
{
	// TODO: add one-time construction code here

}

CGifShowDoc::~CGifShowDoc()
{
}

BOOL CGifShowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_pImage=NULL;
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGifShowDoc serialization

void CGifShowDoc::Serialize(CArchive& ar)
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
// CGifShowDoc diagnostics

#ifdef _DEBUG
void CGifShowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGifShowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGifShowDoc commands

BOOL CGifShowDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	m_pImage= new CBaseImage();
	m_pImage->LoadGif(lpszPathName);
	return TRUE;
}

BOOL CGifShowDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pImage)
		m_pImage->SaveGif(lpszPathName);
	return TRUE;
//	return CDocument::OnSaveDocument(lpszPathName);
}
