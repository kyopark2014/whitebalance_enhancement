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

int dep[256]={  // In case of 852*489 
	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,4,4,4, //54

	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,4,4,4, //54

	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,4,4,4, //54

	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,3,4,4, //53
	3,3,3,4,3,3,3,4,3,3,3,4,3,4,4,4  //54
};

void CPdpTP::Drawing_P1(CWindowDC* dc)
{
	int p10;
	int r,g,b;

	p10 = (maxy+1)/10;

	// 화면 DC와 호환성 있는 메모리 DC를 만듦
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(dc);

	// 화면 DC와 호환성 있는 메모리 비트맵을 만듦
	CBitmap bmpBuffer;
	bmpBuffer.CreateCompatibleBitmap(dc,maxx,maxy);
	CBitmap *pOldBitmap = (CBitmap *)BufferDC.SelectObject(&bmpBuffer);

	int px1=0, px2=0;

	ReadRGBTableForTestPattern();  // for rp,gp,bp
	for(int i=0;i<256;i++) {
		r=i,g=i,b=i;

		if(toggle2 == 0) {
			rp = r;
			gp = g;
			bp = b;
		}
		else if(toggle2==1) {
			rp = RGBtableR[r];
			gp = RGBtableG[g];
			bp = RGBtableB[b];
		}

		CBrush brush(RGB(rp,gp,bp));
		CBrush* pOldBrush = BufferDC.SelectObject(&brush);

		CPen pen;
		pen.CreatePen(PS_SOLID,0,RGB(rp,gp,bp));
		CPen* pOldPen = BufferDC.SelectObject(&pen);

		px1 = px2;
		px2 += dep[i];

		BufferDC.Rectangle(px1,0,px2,p10);

		BufferDC.SelectObject(pOldBrush);
		BufferDC.SelectObject(pOldPen);
	}

	CBrush brush(RGB(cBr,cBg,cBb));
	CBrush* pOldBrush = BufferDC.SelectObject(&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID,5,RGB(cBr,cBg,cBb));
	CPen* pOldPen = BufferDC.SelectObject(&pen);

	BufferDC.Rectangle(0,p10+1,maxx,maxy);

	BufferDC.SelectObject(pOldBrush);
	BufferDC.SelectObject(pOldPen);

	dc->BitBlt(0,0,maxx,maxy,&BufferDC,0,0,SRCCOPY);

	// Display parameter value
	if(DisplayText==1) {
		char strAPL[30]={0,};
		sprintf(strAPL,"APL : %3.2lf",APL);
		dc->SetTextAlign(TA_LEFT||TA_TOP);
		dc->TextOut(50,maxy-(50+16),strAPL);

		char str[50]={0,};
		sprintf(str,"R=%d G=%d B=%d (R=%d G=%d B=%d)",Br,Bg,Bb,cBr,cBg,cBb);
		dc->SetTextAlign(TA_LEFT||TA_TOP);
		dc->TextOut(50,maxy-50,str);
	}

	BufferDC.SelectObject(pOldBitmap);
}

void CPdpTP::Drawing_P2(CWindowDC* dc)
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
	CBrush brushA(RGB(cAr,cAg,cAb));
	CBrush* pOldBrushA = BufferDC.SelectObject(&brushA);

	CPen penA;
	penA.CreatePen(PS_SOLID,0,RGB(cAr,cAg,cAb));
	CPen* pOldPenA = BufferDC.SelectObject(&penA);

	BufferDC.Rectangle(0,0,maxx,maxy);
	
	BufferDC.SelectObject(pOldBrushA);
	BufferDC.SelectObject(pOldPenA);

	/* small rectangular */
	CBrush brushB(RGB(cBr,cBg,cBb));
	CBrush* pOldBrushB = BufferDC.SelectObject(&brushB);

	CPen penB;
	penB.CreatePen(PS_SOLID,5,RGB(cBr,cBg,cBb));
	CPen* pOldPenB = BufferDC.SelectObject(&penB);

	BufferDC.Rectangle(maxx/2-p10x/2,maxy/2-p10y/2,maxx/2+p10x/2,maxy/2+p10y/2);

	BufferDC.SelectObject(pOldBrushB);
	BufferDC.SelectObject(pOldPenB);

	dc->BitBlt(0,0,maxx,maxy,&BufferDC,0,0,SRCCOPY);
	BufferDC.SelectObject(pOldBitmap);

	if(DisplayText==1) {
		char strAPL[30]={0,};
		sprintf(strAPL,"APL : %3.2lf",APL);
		dc->SetTextAlign(TA_LEFT||TA_TOP);
		dc->TextOut(50,maxy-(50+16),strAPL);

	// 영역 A,B의 RGB값 출력
		char strA[50]={0,};
		sprintf(strA,"Region B : R=%d G=%d B=%d (R=%d G=%d B=%d)",Ar,Ag,Ab,cAr,cAg,cAb);
		dc->TextOut(50,maxy-(50-16),strA);

		char strB[50]={0,};
		sprintf(strB,"Region A : R=%d G=%d B=%d (R=%d G=%d B=%d)",Br,Bg,Bb,cBr,cBg,cBb);
		dc->TextOut(50,maxy-50,strB);
	}
}

void CPdpTP::ReadRGBTable()
{/*
	FILE *fp;
	char strr[5],strg[5],strb[5];
	int i;

	char filename[30]={0,};
	int fn;
	if(APL>=0 && APL<12.04)	fn=0;
	else if(APL>=12.04 && APL<24.47) fn=1;
	else if(APL>=24.47 && APL<36.89) fn=2;
	else if(APL>=36.89 && APL<49.32) fn=3;
	else if(APL>=49.32 && APL<61.74) fn=4;
	else if(APL>=49.32 && APL<61.74) fn=5;
	else if(APL>=61.74 && APL<86.59) fn=6;
	else if(APL>=86.59 && APL<99.02) fn=7;
	else if(APL>=99.02 && APL<=100)  fn=8;
	sprintf(filename,"stage%d.txt",fn);
	fp = fopen(filename,"r");
	if(fp==NULL) exit(-1);

	for(i=255;i>=0;i--) {
		fscanf(fp,"%s	%s	%s\n",strr,strg,strb);
		RGBtableR[i]=chr2num(strr);
		RGBtableG[i]=chr2num(strg);
		RGBtableB[i]=chr2num(strb);
	}
		
	fclose(fp); */

	if(toggle2==1) {
		cAr = RGBtableR[Ar];
		cAg = RGBtableG[Ag];
		cAb = RGBtableB[Ab];
		cBr = RGBtableR[Br];
		cBg = RGBtableG[Bg];
		cBb = RGBtableB[Bb]; 
	}

	else if(toggle2==0) {
		cAr = Ar;
		cAg = Ag;
		cAb = Ab;
		cBr = Br;
		cBg = Bg;
		cBb = Bb; 
	}
}

void CPdpTP::ReadRGBTableForTestPattern()
{
/*	FILE *fp;
	char strr[5],strg[5],strb[5];
	int i;

	char filename[30]={0,};
	int fn;
	if(APL>=0 && APL<12.04)	fn=0;
	else if(APL>=12.04 && APL<24.47) fn=1;
	else if(APL>=24.47 && APL<36.89) fn=2;
	else if(APL>=36.89 && APL<49.32) fn=3;
	else if(APL>=49.32 && APL<61.74) fn=4;
	else if(APL>=49.32 && APL<61.74) fn=5;
	else if(APL>=61.74 && APL<86.59) fn=6;
	else if(APL>=86.59 && APL<99.02) fn=7;
	else if(APL>=99.02 && APL<=100)  fn=8;
	sprintf(filename,"stage%d.txt",fn);
	fp = fopen(filename,"r");
	if(fp==NULL) exit(-1);

	for(i=255;i>=0;i--) {
		fscanf(fp,"%s	%s	%s\n",strr,strg,strb);
		RGBtableR[i]=chr2num(strr);
		RGBtableG[i]=chr2num(strg);
		RGBtableB[i]=chr2num(strb);
	}	
	fclose(fp); */

	double **APLTableAPL;
	int **APLTableR;
	int **APLTableG;
	int **APLTableB;

	APLTableR = (int **)malloc(sizeof(int)*9);
	if(APLTableR==NULL) exit(-1);
	for(int t=0;t<9;t++) {
		APLTableR[t] = (int *)malloc(sizeof(int)*256);
		if(APLTableR[t]==NULL) exit(-1);
	}
	APLTableG = (int **)malloc(sizeof(int)*9);
	if(APLTableG==NULL) exit(-1);
	for(t=0;t<9;t++) {
		APLTableG[t] = (int *)malloc(sizeof(int)*256);
		if(APLTableG[t]==NULL) exit(-1);
	}
	APLTableB = (int **)malloc(sizeof(int)*9);
	if(APLTableB==NULL) exit(-1);
	for(t=0;t<9;t++) {
		APLTableB[t] = (int *)malloc(sizeof(int)*256);
		if(APLTableB[t]==NULL) exit(-1);
	}
	APLTableAPL = (double **)malloc(sizeof(double)*9);
	if(APLTableAPL==NULL) exit(-1);
	for(t=0;t<9;t++) {
		APLTableAPL[t] = (double *)malloc(sizeof(double)*256);
		if(APLTableAPL[t]==NULL) exit(-1);
	}
	
	char fname[30]={0,};
	char strr[5],strg[5],strb[5];
	for(t=0;t<9;t++) {
		sprintf(fname,"stage%d.txt",t);
		FILE *fp;
		fp = fopen(fname,"r");
		if(fp==NULL) exit(-1);

		for(int i=255;i>=0;i--) {
			fscanf(fp,"%lf	%s	%s	%s\n",&APLTableAPL[t][i],strr,strg,strb);

			APLTableR[t][i]=chr2num(strr);
			APLTableG[t][i]=chr2num(strg);
			APLTableB[t][i]=chr2num(strb); 
		}
		
		fclose(fp);
	} 

	// Lagrange Interpolation Method
	double mulv;
	double Rt,Gt,Bt;
	for(int i=0;i<256;i++) {
		Rt=0,Gt=0,Bt=0;
		for(t=0;t<9;t++) {
			mulv = 1;
			for(int k=0;k<9;k++) {
				if(k!=t) {
					mulv *= (APL-APLTableAPL[k][i]*1.0)/(APLTableAPL[t][i]*1.0-APLTableAPL[k][i]*1.0);
				}
			}
			Rt += APLTableR[t][i]*mulv;
			Gt += APLTableG[t][i]*mulv;
			Bt += APLTableB[t][i]*mulv;
		}
		RGBtableR[i] = (int)Rt;
		if(RGBtableR[i]>=256) RGBtableR[i] = 255;
		else if(RGBtableR[i]<0) RGBtableR[i] = 0;
		RGBtableG[i] = (int)Gt;
		if(RGBtableG[i]>=256) RGBtableG[i] = 255;
		else if(RGBtableG[i]<0) RGBtableG[i] = 0;
		RGBtableB[i] = (int)Bt;
		if(RGBtableB[i]>=256) RGBtableB[i] = 255;
		else if(RGBtableB[i]<0) RGBtableB[i] = 0;
	} 

/*	FILE *fp;
	fp = fopen("rgb.txt","w");
	for(i=0;i<256;i++) {
		fprintf(fp,"%d %d %d\n",RGBtableR[i],RGBtableG[i],RGBtableB[i]);
	}
	fclose(fp); */

	for(i=0;i<9;i++) {
		free(APLTableR[i]), free(APLTableG[i]), free(APLTableB[i]), free(APLTableAPL[i]);
	}
	free(APLTableR), free(APLTableG), free(APLTableB), free(APLTableAPL);
}

int CPdpTP::chr2num(char *str)
{
	#define    EOS   ('\0')
	/* Returns 0 <= x <= 29999 normally.
     Returns -1 if input is illegal. */
	char c;
	int n=0,pos=0;

	while((c=str[pos])!=EOS){
		if(!isdigit(c)) return -1;
		n = n*10 + c - '0';
		pos++;
	}
	if(pos>5 || (pos==5 && str[0]>'2'))  return -1;
	else                                 return n;
}

void CPdpTP::GetAPL(int Tp)
{
	// APL값 계산
/*	COLORREF color;   // DC로부터 직접 받을 경우
	double sum=0;
	for(int i=0;i<maxx;i++)
		for(int j=0;j<maxy;j++) {
			color = dc->GetPixel(i,j);
			sum += (GetRValue(color)*0.8+GetGValue(color)+GetBValue(color)*1.2);
		} */

		// Calculate APL
	double sum=0;
	int i,j;

	if(Tp==1) {
		int r,g,b;
		int p10 = (maxy+1)/10;

		for(i=0;i<256;i++) {
			r=i,g=i,b=i;
			for(j=0;j<dep[i];j++) {
				sum += (r+g+b);
			}
		}
		for(i=0;i<maxx;i++)
			for(j=p10+1;j<maxy;j++)	{
				sum -= (Ar+Ag+Ab);
				sum += (Br+Bg+Bb);
			}
	}
	else if(Tp==2) {
		int p10x = (maxx+1)/10;
		int p10y = (maxy+1)/10;
		
		for(i=0;i<maxx;i++)
			for(j=0;j<maxy;j++) sum += (Ar+Ag+Ab);

		for(i=0;i<p10x;i++)
			for(j=0;j<p10y;j++)	{
				sum -= (Ar+Ag+Ab);
				sum += (Br+Bg+Bb);
			}
	}

	APL = sum/(maxx*maxy*255*3)*100;  
}

