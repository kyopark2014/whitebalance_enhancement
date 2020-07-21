// pdp_viewerDlg.cpp : implementation file

#include "stdafx.h"
#include "pdp_viewer.h"
#include "pdp_viewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPdp_viewerDlg dialog

CPdp_viewerDlg::CPdp_viewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPdp_viewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPdp_viewerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPdp_viewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPdp_viewerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPdp_viewerDlg, CDialog)
	//{{AFX_MSG_MAP(CPdp_viewerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_MOVIE_PAUSE, OnMoviePause)
	ON_COMMAND(ID_MOVIE_PLAY, OnMoviePlay)
	ON_COMMAND(ID_MOVIE_STOP, OnMovieStop)
	ON_COMMAND(ID_QUIT_APP, OnQuitApp)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPdp_viewerDlg message handlers

BOOL CPdp_viewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	ModifyStyle( 0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS );

	if(!createVideoWnd())
	{
		AfxMessageBox( "Can't create video window" );
		PostQuitMessage( 0 );
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPdp_viewerDlg::OnPaint() 
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
HCURSOR CPdp_viewerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPdp_viewerDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CDialog::OnRButtonDown(nFlags, point);

	CMenu menu;
	menu.LoadMenu(IDR_MENU_MAIN);

	CMenu* pSubMenu = menu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,pt.x,pt.y,this);
}

void CPdp_viewerDlg::OnFileOpen() 
{
	CFileDialog dlgFile(TRUE);
  
	if(dlgFile.DoModal()==IDOK)
	{
		UpdateWindow(); 

		if(m_pdp.open(dlgFile.GetPathName()))
		{
			CRect rcWnd(CPoint(0,0),m_pdp.getVideoSize());
			CalcWindowRect(&rcWnd,CWnd::adjustBorder );
			SetWindowPos(NULL,0,0,rcWnd.Width(),rcWnd.Height(),SWP_NOMOVE|SWP_SHOWWINDOW);
			m_pdp.play();
		}
	} 
}

void CPdp_viewerDlg::OnMoviePause() 
{
	m_pdp.pause();
}

void CPdp_viewerDlg::OnMoviePlay() 
{
	m_pdp.play();
}

void CPdp_viewerDlg::OnMovieStop() 
{
	m_pdp.stop();
}

void CPdp_viewerDlg::OnQuitApp() 
{
	m_pdp.close();
	PostQuitMessage(0);
}

BOOL CPdp_viewerDlg::createVideoWnd()
{
	CRect rcWnd;
	GetClientRect( &rcWnd );

	if(!m_pdp.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
                         rcWnd,this,999,NULL))
	{
		return FALSE;
	}

	m_pdp.ShowWindow( SW_SHOW );
	m_pdp.UpdateWindow();

	return TRUE;
}

void CPdp_viewerDlg::OnSize(UINT nType, int cx, int cy) 
{	
	CDialog::OnSize(nType,cx,cy);
	
	if(m_pdp.m_hWnd)
    m_pdp.SetWindowPos(NULL,0,0,cx,cy,SWP_SHOWWINDOW);	
}

