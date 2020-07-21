// PdpTP.cpp : implementation file
//

#include "stdafx.h"
#include "PdpPattern.h"
#include "PdpTP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPdpTP

CPdpTP::CPdpTP()
{
}

CPdpTP::~CPdpTP()
{
}


BEGIN_MESSAGE_MAP(CPdpTP, CView)
	//{{AFX_MSG_MAP(CPdpTP)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPdpTP drawing

void CPdpTP::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPdpTP diagnostics

#ifdef _DEBUG
void CPdpTP::AssertValid() const
{
	CView::AssertValid();
}

void CPdpTP::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPdpTP message handlers

void CPdpTP::Drawing_P1(int maxx,int maxy,CClientDC* dc)
{
	int dep,p10;

	dep = maxx/256+1;
	p10 = maxy/10;

	// 화면 DC와 호환성 있는 메모리 DC를 만듦
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(dc);

	// 화면 DC와 호환성 있는 메모리 비트맵을 만듦
	CBitmap bmpBuffer;
	bmpBuffer.CreateCompatibleBitmap(dc,maxx,maxy);
	CBitmap *pOldBitmap = (CBitmap *)BufferDC.SelectObject(&bmpBuffer);

	for(int i=0;i<256;i++) {
		CBrush brush(RGB(i*Ar,i*Ag,i*Ab));
		CBrush* pOldBrush = BufferDC.SelectObject(&brush);

		CPen pen;
		pen.CreatePen(PS_SOLID,0,RGB(i*Ar,i*Ag,i*Ab));
		CPen* pOldPen = BufferDC.SelectObject(&pen);

		BufferDC.Rectangle(i*dep,0,(i+1)*dep,p10);

		BufferDC.SelectObject(pOldBrush);
		BufferDC.SelectObject(pOldPen);
	}

	CBrush brush(RGB(Br,Bg,Bb));
	CBrush* pOldBrush = BufferDC.SelectObject(&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID,5,RGB(Br,Bg,Bb));
	CPen* pOldPen = BufferDC.SelectObject(&pen);

	BufferDC.Rectangle(0,p10+1,maxx,maxy);

	BufferDC.SelectObject(pOldBrush);
	BufferDC.SelectObject(pOldPen);

	dc->BitBlt(0,0,maxx,maxy,&BufferDC,0,0,SRCCOPY);

	BufferDC.SelectObject(pOldBitmap);
}

void CPdpTP::Drawing_P2(int maxx,int maxy,CClientDC* dc)
{
	int p10x,p10y,dep;

	dep = maxx/256+1;
	p10x = maxx/10;
	p10y = maxy/10;

	// 화면 DC와 호환성 있는 메모리 DC를 만듦
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(dc);

	// 화면 DC와 호환성 있는 메모리 비트맵을 만듦
	CBitmap bmpBuffer;
	bmpBuffer.CreateCompatibleBitmap(dc,maxx,maxy);
	CBitmap *pOldBitmap = (CBitmap *)BufferDC.SelectObject(&bmpBuffer);

	/* large rectangular */
	CBrush brushA(RGB(Ar,Ag,Ab));
	CBrush* pOldBrushA = BufferDC.SelectObject(&brushA);

	CPen penA;
	penA.CreatePen(PS_SOLID,0,RGB(Ar,Ag,Ab));
	CPen* pOldPenA = BufferDC.SelectObject(&penA);

	BufferDC.Rectangle(0,0,maxx,maxy);
	
	BufferDC.SelectObject(pOldBrushA);
	BufferDC.SelectObject(pOldPenA);

	/* small rectangular */
	CBrush brushB(RGB(Br,Bg,Bb));
	CBrush* pOldBrushB = BufferDC.SelectObject(&brushB);

	CPen penB;
	penB.CreatePen(PS_SOLID,5,RGB(Br,Bg,Bb));
	CPen* pOldPenB = BufferDC.SelectObject(&penB);

	BufferDC.Rectangle(maxx/2-p10x/2,maxy/2-p10y/2,maxx/2+p10x/2,maxy/2+p10y/2);

	BufferDC.SelectObject(pOldBrushB);
	BufferDC.SelectObject(pOldPenB);

	dc->BitBlt(0,0,maxx,maxy,&BufferDC,0,0,SRCCOPY);
	BufferDC.SelectObject(pOldBitmap);
	
}

// Calculte the value of APL (Automatic Picture Level)
float CPdpTP::CalAPL(CClientDC* dc)
{
	COLORREF pcolor;
	float apl=0,sum_apl=0;
	float maxx,maxy;

//	CRect rect;
//	GetClientRect(&rect);

//	maxx = rect.Width();
//	maxy = rect.Height();
	maxx = 1024;
	maxy = 768;

	sum_apl=0;
	for(int i=0;i<maxx;i++) 
		for(int j=0;j<maxy;j++) {
			pcolor = dc->GetPixel(i,j);
			sum_apl += GetRValue(pcolor)*0.8+GetGValue(pcolor)+GetBValue(pcolor)*1.2;
		}
	apl = sum_apl/(maxx*maxy*256*3)*100;  // Percentage

	return apl;
}
