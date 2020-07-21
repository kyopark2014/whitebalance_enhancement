// BmpPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BmpPlayer.h"
#include "BmpPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpPlayerDlg dialog

CBmpPlayerDlg::CBmpPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBmpPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBmpPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	count = 0;
}

void CBmpPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBmpPlayerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBmpPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CBmpPlayerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpPlayerDlg message handlers

BOOL CBmpPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// Image 
	m_pImage=new CBaseImage;
	m_pImage->LoadBmp("d:\\hyper\\fig01.bmp");

	// Control windows size
	SIZE size;
	size = m_pImage->GetSize();
	SetWindowPos(NULL,0,0,size.cx,size.cy,SWP_NOMOVE|SWP_SHOWWINDOW);
	
	SetTimer(0,200,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBmpPlayerDlg::OnPaint() 
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
		CWindowDC dc(this);	
		m_pImage->PaintImage(0,0,dc);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBmpPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBmpPlayerDlg::OnTimer(UINT nIDEvent) 
{
	char str[20]={0,};
    if(nIDEvent==0) {
			count++;
			if(count==31) count = 0;
			m_pImage=new CBaseImage;
			sprintf(str,"d:\\hyper\\fig%2d.BMP",count);  //PDVD_000.BMP
			m_pImage->LoadBmp(str);

			CWindowDC dc(this);	
			m_pImage->PaintImage(0,0,dc);
	}
	CDialog::OnTimer(nIDEvent);
}

void CBmpPlayerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(0);	
}
