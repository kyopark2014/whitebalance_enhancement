// WBCompensatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WBCompensator.h"
#include "WBCompensatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TimeDepth 20
//#define TotalFigure 884
#define TotalFigure 250

/////////////////////////////////////////////////////////////////////////////
// CWBCompensatorDlg dialog

CWBCompensatorDlg::CWBCompensatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWBCompensatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWBCompensatorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWBCompensatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWBCompensatorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWBCompensatorDlg, CDialog)
	//{{AFX_MSG_MAP(CWBCompensatorDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_UPDATE_COMMAND_UI(ID_COMPENSATION, OnUpdateCompensation)
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_SHOW_FIGURES, OnUpdateShowFigures)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWBCompensatorDlg message handlers

BOOL CWBCompensatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	SetTimer(0,1000/TimeDepth,NULL);
	Toggle = 0;
	
	m_pImage=new CBaseImage;
	m_pImage->LoadBmp("d:\\project\\images\a1.bmp");

	// Control windows size
	SIZE size;
	size=m_pImage->GetSize();
	Width=size.cx, Height=size.cy; // Picture Window
	wWidth=852, wHeight=480;
	count=0;

//	Resizing
	SetWindowPos(NULL,0,0,Width,Height,SWP_NOMOVE|SWP_SHOWWINDOW);

	// Initialize the window which color is Black;
	CWindowDC dc(this);
	CRect rect;
	GetWindowRect(&rect);

	CBrush brush(RGB(0,0,0));
	CBrush* pOldBrush = dc.SelectObject(&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID,0,RGB(0,0,0));
	CPen* pOldPen = dc.SelectObject(&pen);

	dc.Rectangle(0,0,rect.Width(),rect.Height());
	
	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWBCompensatorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWBCompensatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWBCompensatorDlg::LoadFigure(int FigureNum)
{
	char str[50]={0,};
	sprintf(str,"d:\\project\\images\a1.bmp",FigureNum);  //PDVD_000.BMP
	m_pImage->LoadBmp(str);

	CWindowDC dc(this);	
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc,Width,Height);
	CBitmap *pOldBitmap = dcMem.SelectObject(&bitmap);

	m_pImage->PaintImage(0,0,dcMem);

	dc.BitBlt(0,0,Width,Height,&dcMem,0,0,SRCCOPY);

	dcMem.SelectObject(pOldBitmap);
	ReleaseDC(&dcMem);
}

void CWBCompensatorDlg::CompensateFigure(int FigureNum)
{
	int rWidth;

	CWindowDC dc(this);

	rWidth=(Width+3)/4*4;
	SIZE size;
	size.cx=rWidth,size.cy=Height;

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc,rWidth,Height);

	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);

	CBitmap *pOldBitmap = dcMem.SelectObject(&bitmap);
	dcMem.BitBlt(0,0,rWidth,Height,&dc,0,0,SRCCOPY);

//	BITMAPINFOHEADER 
	int Colornum=0;  // no Palette
	m_pImage->AllocBmpInfo(Colornum);
	m_pImage->SetBmpInfo(size,Colornum);  // no palette in True Color

// BITMAPFILEHEADER 
	m_pImage->SetBmpHeader(size,Colornum); 

	int **B,**G,**R;
	int i,m,n;
	B = (int **)malloc(sizeof(int)*Height);
	if(B==NULL) exit(-1);
	for(i=0;i<Height;i++) {
		B[i] = (int *)malloc(sizeof(int)*rWidth);
		if(B[i]==NULL) exit(-1);
	}
	G = (int **)malloc(sizeof(int)*Height);
	if(G==NULL) exit(-1);
	for(i=0;i<Height;i++) {
		G[i] = (int *)malloc(sizeof(int)*rWidth);
		if(G[i]==NULL) exit(-1);
	}
	R = (int **)malloc(sizeof(int)*Height);
	if(R==NULL) exit(-1);
	for(i=0;i<Height;i++) {
		R[i] = (int *)malloc(sizeof(int)*rWidth);
		if(R[i]==NULL) exit(-1);
	}

	COLORREF pcolor;
	i=0;
	double sum=0,APL=0;
	for(m=0;m<Height;m++) {
		for(n=0;n<rWidth;n++) {
			pcolor = dcMem.GetPixel(n,Height-1-m);

			B[m][n]=GetBValue(pcolor);
			G[m][n]=GetGValue(pcolor);
			R[m][n]=GetRValue(pcolor);
			// for Getting APL
			sum += (B[m][n]+G[m][n]+R[m][n]);
		}
	}

	// Get APL
	APL = sum/(rWidth*Height*255*3)*100; 

	char strAPL[50]={0,};
	sprintf(strAPL,"APL : %3.2lf (%d/%d)",APL,count,TotalFigure);
	dc.SetTextAlign(TA_LEFT||TA_TOP);
	dc.TextOut(50,Height-50,strAPL);

/*	char filename[30]={0,};
	char strr[5],strg[5],strb[5];
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
	FILE *fp;
	fp = fopen(filename,"r");
	if(fp==NULL) exit(-1);

	for(i=255;i>=0;i--) {
		fscanf(fp,"%lf	%s	%s	%s\n",&APLData[i],strr,strg,strb);

		RGBtableR[i]=chr2num(strr);
		RGBtableG[i]=chr2num(strg);
		RGBtableB[i]=chr2num(strb);
	}	*/

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

		for(i=255;i>=0;i--) {
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
	for(i=0;i<256;i++) {
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
		RGBtableG[i] = (int)Gt;
		RGBtableB[i] = (int)Bt;
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

// Get RGB data 
	m_pImage->m_pDib= new char [m_pImage->pBitmapInfo->bmiHeader.biSizeImage];

	i=0;
	for(m=0;m<Height;m++) {
		for(n=0;n<rWidth;n++) {
			m_pImage->m_pDib[i++]=RGBtableB[B[m][n]];
			m_pImage->m_pDib[i++]=RGBtableG[G[m][n]];
			m_pImage->m_pDib[i++]=RGBtableR[R[m][n]]; 
		}
	}
	
// Write RGB image to BMP
	char str[40]={0,};
	sprintf(str,"d:\\capture\\cFrame_%03d.BMP",FigureNum);
	m_pImage->SaveImage(str); 

	delete m_pImage->m_pDib;  
	dcMem.SelectObject(pOldBitmap);
	ReleaseDC(&dcMem);

	for(i=0;i<Height;i++) free(R[i]),free(G[i]),free(B[i]);
	free(R),free(G),free(B);
}

int CWBCompensatorDlg::chr2num(char *str)
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
	else  return n;
}

void CWBCompensatorDlg::OnUpdateCompensation(CCmdUI* pCmdUI) 
{
	for(int i=0;i<TotalFigure;i++) {
		LoadFigure(i);
		CompensateFigure(i);	
	}
}

void CWBCompensatorDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU_MAIN);

	CMenu* pSubMenu = menu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,pt.x,pt.y,this);
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CWBCompensatorDlg::OnTimer(UINT nIDEvent) 
{
	char str[40]={0,};
    if(nIDEvent==0 && Toggle==1) {
		//	Resizing
		SetWindowPos(NULL,0,0,wWidth,wHeight,SWP_NOMOVE|SWP_SHOWWINDOW);

		sprintf(str,"d:\\capture\\cFrame_%03d.BMP",count++);  //PDVD_000.BMP
		m_pImage->LoadBmp(str);

		CWindowDC dc(this);	
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);

		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc,Width,Height);
		CBitmap *pOldBitmap = dcMem.SelectObject(&bitmap);

		m_pImage->PaintImage(0,0,dcMem);

		//dc.BitBlt(0,0,mWidth,mHeight,&dcMem,0,0,SRCCOPY);
		// Resizing
		dc.StretchBlt(0,0,wWidth,wHeight,&dcMem,0,0,Width,Height,SRCCOPY);

		dcMem.SelectObject(pOldBitmap);
		ReleaseDC(&dcMem);
	}
	CDialog::OnTimer(nIDEvent);
}

void CWBCompensatorDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(0);		
}

void CWBCompensatorDlg::OnUpdateShowFigures(CCmdUI* pCmdUI) 
{
	Toggle = 1;	
	count = 0;
}
