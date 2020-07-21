// PdpPatternDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PdpPattern.h"
#include "PdpPatternDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	Tp=1;
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
	ON_WM_DESTROY()
	ON_WM_TIMER()
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

	if(m_bIsWindow) {  // 윈도우생성후에 크기조정
		SetWindowPos(NULL,0,0,1024,768,SWP_NOMOVE|SWP_SHOWWINDOW);
	}
	pp.dr=4, pp.dg=4, pp.db=4;
	pp.Br=100, pp.Bg=100, pp.Bb=100;
	pp.Ar=1, pp.Ag=1, pp.Ab=1;

	SetTimer(0,100,NULL);
	
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
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	if(Tp==1)
		pp.Drawing_P1(rect.Width(),rect.Height(),&dc);
	else if(Tp==2)
		pp.Drawing_P2(rect.Width(),rect.Height(),&dc);
}

void CPdpPatternDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar=='5')	Tp=1;
	else if(nChar=='6') Tp=2;

	if(Tp==1) {
		if(nChar=='9') {
			pp.Br+=pp.dr;
			if(pp.Br>255) pp.Br=255;
			pp.Bg+=pp.dg;
			if(pp.Bg>255) pp.Bg=255;
			pp.Bb+=pp.db;
			if(pp.Bb>255) pp.Bb=255; 
		}
		if(nChar=='0') {
			pp.Br-=pp.dr;
			if(pp.Br<0) pp.Br=0;
			pp.Bg-=pp.dg;
			if(pp.Bg<0) pp.Bg=0;
			pp.Bb-=pp.db;
			if(pp.Bb<0) pp.Bb=0; 
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
		if(nChar=='s' || nChar=='S') {
			pp.dr=4, pp.dg=4, pp.db=4;
			pp.Br=100, pp.Bg=100, pp.Bb=100;
			pp.Ar=1, pp.Ag=1, pp.Ab=1;
		}
	}
	else if(Tp==2) {
	   // Area A
		if(nChar=='1') {
			pp.Ar+=pp.dr;
			if(pp.Ar>255) pp.Ar=255;
			pp.Ag+=pp.dg;
			if(pp.Ag>255) pp.Ag=255;
			pp.Ab+=pp.db;
			if(pp.Ab>255) pp.Ab=255; 
		}
		if(nChar=='2') {
			pp.Ar-=pp.dr;
			if(pp.Ar<0) pp.Ar=0;
			pp.Ag-=pp.dg;
			if(pp.Ag<0) pp.Ag=0;
			pp.Ab-=pp.db;
			if(pp.Ab<0) pp.Ab=0; 
		}	

		// Area B
		if(nChar=='9') {
			pp.Br+=pp.dr;
			if(pp.Br>255) pp.Br=255;
			pp.Bg+=pp.dg;
			if(pp.Bg>255) pp.Bg=255;
			pp.Bb+=pp.db;
			if(pp.Bb>255) pp.Bb=255; 
		}
		if(nChar=='0') {
			pp.Br-=pp.dr;
			if(pp.Br<0) pp.Br=0;
			pp.Bg-=pp.dg;
			if(pp.Bg<0) pp.Bg=0;
			pp.Bb-=pp.db;
			if(pp.Bb<0) pp.Bb=0; 
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
		if(nChar=='s' || nChar=='S') {
			pp.dr=4, pp.dg=4, pp.db=4;
			pp.Br=100, pp.Bg=100, pp.Bb=100;
			pp.Ar=1, pp.Ag=1, pp.Ab=1;
		}
	}

	Draw(Tp);

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPdpPatternDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(0);	
}

void CPdpPatternDlg::OnTimer(UINT nIDEvent) 
{
	CClientDC dc(this);
	float apl=0;

	FILE *fp;
	if(nIDEvent==0) {
		fp = fopen("apl.txt","a");
		
		apl=pp.CalAPL(&dc);

		fprintf(fp,"%4.2f\n",apl);
		fclose(fp);
	}
	
	CDialog::OnTimer(nIDEvent);
}
