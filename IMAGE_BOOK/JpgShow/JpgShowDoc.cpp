// JpgShowDoc.cpp : implementation of the CJpgShowDoc class
//

#include "stdafx.h"
#include "JpgShow.h"

#include "JpgShowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJpgShowDoc

IMPLEMENT_DYNCREATE(CJpgShowDoc, CDocument)

BEGIN_MESSAGE_MAP(CJpgShowDoc, CDocument)
	//{{AFX_MSG_MAP(CJpgShowDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJpgShowDoc construction/destruction

CJpgShowDoc::CJpgShowDoc()
{
	// TODO: add one-time construction code here

}

CJpgShowDoc::~CJpgShowDoc()
{
}

BOOL CJpgShowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_pImage=NULL;
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CJpgShowDoc serialization

void CJpgShowDoc::Serialize(CArchive& ar)
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
// CJpgShowDoc diagnostics

#ifdef _DEBUG
void CJpgShowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJpgShowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJpgShowDoc commands

BOOL CJpgShowDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	m_pImage=new CBaseImage;
	m_pImage->LoadJpg(lpszPathName);
	
	return TRUE;
}

BOOL CJpgShowDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pImage)
		m_pImage->SaveJpg(lpszPathName);
	return TRUE;
//	return CDocument::OnSaveDocument(lpszPathName);
}
