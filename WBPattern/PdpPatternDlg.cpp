// PdpPatternDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PdpPattern.h"
#include "PdpPatternDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MaxR 254
#define MaxG 254
#define MaxB 254
#define MinR 1
#define MinG 1
#define MinB 1

/////////////////////////////////////////////////////////////////////////////
// CPdpPatternDlg dialog

CPdpPatternDlg::CPdpPatternDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPdpPatternDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPdpPatternDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bIsWindow=FALSE;
}

void CPdpPatternDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPdpPatternDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPdpPatternDlg, CDialog)
	//{{AFX_MSG_MAP(CPdpPatternDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPdpPatternDlg message handlers
BOOL CPdpPatternDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_bIsWindow = TRUE;
	pp.maxx = 852;
	pp.maxy = 480;

	if(m_bIsWindow) {  // 윈도우생성후에 크기조정
		SetWindowPos(NULL,0,0,pp.maxx,pp.maxy,SWP_NOMOVE|SWP_SHOWWINDOW);
	}

	InitializeParameter();  // Set the Parameters
	pp.GetAPL(Tp);			// Get APL
	pp.ReadRGBTableForTestPattern();
	pp.ReadRGBTable();  	// Get RGB Gain Table
	SetTimer(0,50,NULL);

	// Additional Gamma Trans. 
/*	double gamma;
	gamma = 2.2;

	double gtcolor,gtbcolor;

	gtcolor = pow((double)pp.Ar/255.,gamma);
	pp.Ar=(int)gtcolor*255;
	pp.Ag=(int)gtcolor*255;
	pp.Ab=(int)gtcolor*255;

	gtbcolor = pow((double)pp.Br/255.,gamma);
	pp.Br=(int)gtbcolor*255;
	pp.Bg=(int)gtbcolor*255;
	pp.Bb=(int)gtbcolor*255; */

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPdpPatternDlg::OnPaint() 
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
		Draw(Tp);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPdpPatternDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPdpPatternDlg::Draw(int Tp)
{
	CWindowDC dc(this);

	if(Tp==1)
		pp.Drawing_P1(&dc);
	else if(Tp==2)
		pp.Drawing_P2(&dc);
}

void CPdpPatternDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar=='5') {
		Tp=1;
	}
	else if(nChar=='6') {
		Tp=2;
	}
	if(nChar=='A' || nChar=='a') {
		pp.toggle1=1;
		pp.Br=MaxR, pp.Bg=MaxG, pp.Bb=MaxB;
	}
	if(nChar=='D' || nChar=='d') {
		pp.DisplayText=!pp.DisplayText;
	}
	if(nChar=='T' || nChar=='t') {
		pp.toggle2 = !pp.toggle2;
	}
	if(nChar=='I' || nChar=='i') {
		InitializeParameter();
	}

	if(Tp==1) {
		if(nChar=='9') {
			pp.Br+=pp.dr;
			if(pp.Br>MaxR) pp.Br=MaxR;
			pp.Bg+=pp.dg;
			if(pp.Bg>MaxG) pp.Bg=MaxG;
			pp.Bb+=pp.db;
			if(pp.Bb>MaxB) pp.Bb=MaxB; 
		}
		if(nChar=='0') {
			pp.Br-=pp.dr;
			if(pp.Br<MinR) pp.Br=MinR;
			pp.Bg-=pp.dg;
			if(pp.Bg<MinG) pp.Bg=MinG;
			pp.Bb-=pp.db;
			if(pp.Bb<MinB) pp.Bb=MinB; 
		}	
		if(nChar=='r' || nChar=='R') {
			pp.dr=4, pp.dg=0, pp.db=0;
		}
		if(nChar=='g' || nChar=='G') {
			pp.dr=0, pp.dg=4, pp.db=0;
		}
		if(nChar=='b' || nChar=='B') {
			pp.dr=0, pp.dg=0, pp.db=4;
		}
	}
	else if(Tp==2) {
	   // Area A
		if(nChar=='1') {
			pp.Ar+=pp.dr;
			if(pp.Ar>MaxR) pp.Ar=MaxR;
			pp.Ag+=pp.dg;
			if(pp.Ag>MaxG) pp.Ag=MaxG;
			pp.Ab+=pp.db;
			if(pp.Ab>MaxB) pp.Ab=MaxB; 
		}
		if(nChar=='2') {
			pp.Ar-=pp.dr;
			if(pp.Ar<MinR) pp.Ar=MinR;
			pp.Ag-=pp.dg;
			if(pp.Ag<MinG) pp.Ag=MinG;
			pp.Ab-=pp.db;
			if(pp.Ab<MinB) pp.Ab=MinB; 
		}	

		// Area B
		if(nChar=='9') {
			pp.Br+=pp.dr;
			if(pp.Br>MaxR) pp.Br=MaxR;
			pp.Bg+=pp.dg;
			if(pp.Bg>MaxG) pp.Bg=MaxG;
			pp.Bb+=pp.db;
			if(pp.Bb>MaxB) pp.Bb=MaxB; 
		}
		if(nChar=='0') {
			pp.Br-=pp.dr;
			if(pp.Br<MinR) pp.Br=MinR;
			pp.Bg-=pp.dg;
			if(pp.Bg<MinG) pp.Bg=MinG;
			pp.Bb-=pp.db;
			if(pp.Bb<MinB) pp.Bb=MinB; 
		}	

		if(nChar=='r' || nChar=='R') {
			pp.dr=4, pp.dg=0, pp.db=0;
		}
		if(nChar=='g' || nChar=='G') {
			pp.dr=0, pp.dg=4, pp.db=0;
		}
		if(nChar=='b' || nChar=='B') {
			pp.dr=0, pp.dg=0, pp.db=4;
		}
	}

	pp.GetAPL(Tp);
	pp.ReadRGBTableForTestPattern();
	pp.ReadRGBTable();
	Draw(Tp);

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPdpPatternDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==0 && pp.toggle1==1 && Tp==2) {
		FILE *fp;
		char str[30]={0,};
		sprintf(str,"apl%d.txt",pp.Ar);
		fp = fopen(str,"a+");
		fprintf(fp,"%d,%d,%3.2lf\n",pp.Ar,pp.Br,pp.APL);
		fclose(fp);

		Draw(Tp);

		if(pp.Br==MinR) {
			pp.toggle1=0;
		}
		else pp.Br--, pp.Bg--, pp.Bb--;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CPdpPatternDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(0);	
}

void CPdpPatternDlg::InitializeParameter()
{
	Tp=2;
	pp.DisplayText=1;

	pp.dr=8, pp.dg=8, pp.db=8;
	pp.Br=MaxR, pp.Bg=MaxG, pp.Bb=MaxB;
	pp.Ar=MinR, pp.Ag=MinG, pp.Ab=MinB;

	pp.toggle1=0;
	pp.toggle2=0;
}