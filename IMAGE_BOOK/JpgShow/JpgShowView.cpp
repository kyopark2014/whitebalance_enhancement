// JpgShowView.cpp : implementation of the CJpgShowView class
//

#include "stdafx.h"
#include "JpgShow.h"

#include "JpgShowDoc.h"
#include "JpgShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJpgShowView

IMPLEMENT_DYNCREATE(CJpgShowView, CScrollView)

BEGIN_MESSAGE_MAP(CJpgShowView, CScrollView)
	//{{AFX_MSG_MAP(CJpgShowView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJpgShowView construction/destruction

CJpgShowView::CJpgShowView()
{
	// TODO: add construction code here

}

CJpgShowView::~CJpgShowView()
{
}

BOOL CJpgShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CJpgShowView drawing

void CJpgShowView::OnDraw(CDC* pDC)
{
	CJpgShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_pImage)
		pDoc->m_pImage->PaintImage(0,0,pDC->m_hDC);
}

void CJpgShowView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	CJpgShowDoc* pDoc = GetDocument();
	if(pDoc->m_pImage)
	{
		sizeTotal.cx=pDoc->m_pImage->GetSize().cx;
		sizeTotal.cy=pDoc->m_pImage->GetSize().cy;
	}
	
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CJpgShowView printing

BOOL CJpgShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CJpgShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CJpgShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CJpgShowView diagnostics

#ifdef _DEBUG
void CJpgShowView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CJpgShowView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CJpgShowDoc* CJpgShowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJpgShowDoc)));
	return (CJpgShowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJpgShowView message handlers
