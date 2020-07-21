// BmpShowView.cpp : implementation of the CBmpShowView class
//

#include "stdafx.h"
#include "BmpShow.h"

#include "BmpShowDoc.h"
#include "BmpShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpShowView

IMPLEMENT_DYNCREATE(CBmpShowView, CScrollView)

BEGIN_MESSAGE_MAP(CBmpShowView, CScrollView)
	//{{AFX_MSG_MAP(CBmpShowView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpShowView construction/destruction

CBmpShowView::CBmpShowView()
{
	// TODO: add construction code here

}

CBmpShowView::~CBmpShowView()
{
}

BOOL CBmpShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBmpShowView drawing

void CBmpShowView::OnDraw(CDC* pDC)
{
	CBmpShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_pImage)
		pDoc->m_pImage->PaintImage(0,0,pDC->m_hDC);
}

void CBmpShowView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	CBmpShowDoc* pDoc = GetDocument();
	if(pDoc->m_pImage)
	{
		sizeTotal.cx=pDoc->m_pImage->GetSize().cx;
		sizeTotal.cy=pDoc->m_pImage->GetSize().cy;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CBmpShowView printing

BOOL CBmpShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBmpShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBmpShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBmpShowView diagnostics

#ifdef _DEBUG
void CBmpShowView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CBmpShowView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CBmpShowDoc* CBmpShowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpShowDoc)));
	return (CBmpShowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmpShowView message handlers
