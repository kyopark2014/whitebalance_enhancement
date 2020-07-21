// MotionPatternDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MotionPattern.h"
#include "MotionPatternDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMotionPatternDlg dialog

CMotionPatternDlg::CMotionPatternDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMotionPatternDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMotionPatternDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMotionPatternDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMotionPatternDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMotionPatternDlg, CDialog)
	//{{AFX_MSG_MAP(CMotionPatternDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_MENU_CAPTURE, OnUpdateMenuCapture)
	ON_UPDATE_COMMAND_UI(ID_MOVIE_PAUSE, OnUpdateMoviePause)
	ON_UPDATE_COMMAND_UI(ID_MOVIE_PLAY, OnUpdateMoviePlay)
	ON_UPDATE_COMMAND_UI(ID_MOVIE_STOP, OnUpdateMovieStop)
	ON_UPDATE_COMMAND_UI(ID_QUIT_APP, OnUpdateQuitApp)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMotionPatternDlg message handlers

BOOL CMotionPatternDlg::OnInitDialog()
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

	m_pImage=new CBaseImage;
	Toggle = 0;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMotionPatternDlg::OnPaint() 
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
HCURSOR CMotionPatternDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMotionPatternDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU_MAIN);

	CMenu* pSubMenu = menu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,pt.x,pt.y,this);

	if(nFlags=='q' || nFlags=='Q')	{
		Toggle=0;
		m_pdp.close();
		PostQuitMessage(0);	
	}
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CMotionPatternDlg::OnUpdateFileOpen(CCmdUI* pCmdUI) 
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
			Width=rcWnd.Width(), Height=rcWnd.Height();
			m_pdp.play();
		}
	} 	
}

void CMotionPatternDlg::OnUpdateMenuCapture(CCmdUI* pCmdUI) 
{
	SetTimer(0,50,NULL);
	Toggle = !Toggle;	
}

void CMotionPatternDlg::OnUpdateMoviePause(CCmdUI* pCmdUI) 
{
	m_pdp.pause();	
	Toggle=0;
}

void CMotionPatternDlg::OnUpdateMoviePlay(CCmdUI* pCmdUI) 
{
	m_pdp.play();
}

void CMotionPatternDlg::OnUpdateMovieStop(CCmdUI* pCmdUI) 
{
	m_pdp.stop();
	Toggle=0;
}

void CMotionPatternDlg::OnUpdateQuitApp(CCmdUI* pCmdUI) 
{
	m_pdp.close();
	PostQuitMessage(0);	
}

BOOL CMotionPatternDlg::createVideoWnd()
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

void CMotionPatternDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if(m_pdp.m_hWnd)
    m_pdp.SetWindowPos(NULL,0,0,cx,cy,SWP_SHOWWINDOW);		
}

void CMotionPatternDlg::OnTimer(UINT nIDEvent) 
{
	int rWidth;

	if(nIDEvent==0 && Toggle==1) {
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

// Get RGB data 
		m_pImage->m_pDib = new char [m_pImage->pBitmapInfo->bmiHeader.biSizeImage];
		GetDIBits(
			(HDC)dcMem,				// Handle to DC
			(HBITMAP)bitmap,		// Handle to bitmap
			0,                      // first Scan line to set
			Height,					// number of scan lines to copy
			m_pImage->m_pDib,       // array for bitmap bits
			m_pImage->pBitmapInfo,	// bitmap data buffer
			DIB_RGB_COLORS			// RGB index
		);
	
// Write RGB image to BMP
		char str[40]={0,};
		sprintf(str,"d:\\capture\\Frame_%03d.BMP",m_pImage->count++);
		m_pImage->SaveImage(str); 

		delete m_pImage->m_pDib;  
		dcMem.SelectObject(pOldBitmap);
		ReleaseDC(&dcMem);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CMotionPatternDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(0);	
}
