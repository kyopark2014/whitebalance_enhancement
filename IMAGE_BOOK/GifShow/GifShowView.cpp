// GifShowView.cpp : implementation of the CGifShowView class
//

#include "stdafx.h"
#include "GifShow.h"

#include "GifShowDoc.h"
#include "GifShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGifShowView

IMPLEMENT_DYNCREATE(CGifShowView, CScrollView)

BEGIN_MESSAGE_MAP(CGifShowView, CScrollView)
	//{{AFX_MSG_MAP(CGifShowView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGifShowView construction/destruction

CGifShowView::CGifShowView()
{
	// TODO: add construction code here

}

CGifShowView::~CGifShowView()
{
}

BOOL CGifShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGifShowView drawing

void CGifShowView::OnDraw(CDC* pDC)
{
	CGifShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_pImage)
		pDoc->m_pImage->PaintImage(0,0,pDC->m_hDC);

}

void CGifShowView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	CGifShowDoc* pDoc = GetDocument();
	if(pDoc->m_pImage)
	{
		sizeTotal.cx=pDoc->m_pImage->GetSize().cx;
		sizeTotal.cy=pDoc->m_pImage->GetSize().cy;
	}
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CGifShowView printing

BOOL CGifShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGifShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGifShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGifShowView diagnostics

#ifdef _DEBUG
void CGifShowView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGifShowView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGifShowDoc* CGifShowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGifShowDoc)));
	return (CGifShowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGifShowView message handlers
