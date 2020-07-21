// ShiftPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShiftPlayer.h"
#include "ShiftPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TimeDepth 20
#define shift 8
#define nImage 852/shift

CDC dcBuffer[nImage];

char FigurePath[50] = "d:\\project\\images\\a1.bmp";

/////////////////////////////////////////////////////////////////////////////
// CShiftPlayerDlg dialog

CShiftPlayerDlg::CShiftPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShiftPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShiftPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShiftPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShiftPlayerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShiftPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CShiftPlayerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_PLAY, OnUpdatePlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShiftPlayerDlg message handlers

BOOL CShiftPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	SetTimer(0,1000/TimeDepth,NULL);
	Toggle = 0;
	
	m_pImage=new CBaseImage;
	m_pImage->LoadBmp(FigurePath);

	// Control windows size
	SIZE size;
	size=m_pImage->GetSize();
	Width=size.cx, Height=size.cy; // Picture Window
	wWidth=852, wHeight=480;

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

	LoadFigure();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShiftPlayerDlg::OnPaint() 
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
HCURSOR CShiftPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShiftPlayerDlg::ShowFigure()
{
	CWindowDC dc(this);	

	dc.BitBlt(0,0,Width,Height,&dcBuffer[count],0,0,SRCCOPY);
}

void CShiftPlayerDlg::LoadFigure()
{
	int i=0,m=0,n=0,t=0;

	m_pImage->LoadBmp(FigurePath);

	CWindowDC dc(this);	
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc,Width,Height);
	CBitmap *pOldBitmap = dcMem.SelectObject(&bitmap);

	// Print the original Image
	m_pImage->PaintImage(0,0,dcMem);
	dc.BitBlt(0,0,Width,Height,&dcMem,0,0,SRCCOPY);

	B = (int **)malloc(sizeof(int)*Height);
	if(B==NULL) exit(-1);
	for(i=0;i<Height;i++) {
		B[i] = (int *)malloc(sizeof(int)*Width);
		if(B[i]==NULL) exit(-1);
	}
	G = (int **)malloc(sizeof(int)*Height);
	if(G==NULL) exit(-1);
	for(i=0;i<Height;i++) {
		G[i] = (int *)malloc(sizeof(int)*Width);
		if(G[i]==NULL) exit(-1);
	}
	R = (int **)malloc(sizeof(int)*Height);
	if(R==NULL) exit(-1);
	for(i=0;i<Height;i++) {
		R[i] = (int *)malloc(sizeof(int)*Width);
		if(R[i]==NULL) exit(-1);
	}
	// buffer for B,G,R
	Bt = (int **)malloc(sizeof(int)*Height);
	if(Bt==NULL) exit(-1);
	for(i=0;i<Height;i++) {
		Bt[i] = (int *)malloc(sizeof(int)*Width);
		if(Bt[i]==NULL) exit(-1);
	}
	Gt = (int **)malloc(sizeof(int)*Height);
	if(Gt==NULL) exit(-1);
	for(i=0;i<Height;i++) {
		Gt[i] = (int *)malloc(sizeof(int)*Width);
		if(Gt[i]==NULL) exit(-1);
	}
	Rt = (int **)malloc(sizeof(int)*Height);
	if(Rt==NULL) exit(-1);
	for(i=0;i<Height;i++) {
		Rt[i] = (int *)malloc(sizeof(int)*Width);
		if(Rt[i]==NULL) exit(-1);
	}

	COLORREF pcolor;
	i=0;
	for(m=0;m<Height;m++) {
		for(n=0;n<Width;n++) {
			pcolor = dcMem.GetPixel(n,Height-1-m);

			B[m][n]=GetBValue(pcolor);
			G[m][n]=GetGValue(pcolor);
			R[m][n]=GetRValue(pcolor);
		}
	} 

	dcMem.SelectObject(pOldBitmap);
	ReleaseDC(&dcMem);

	m_pImage->m_pDib = new char[(Width*Height)*3];
	memset(m_pImage->m_pDib, 0, (Width*Height)*3); 

	for(t=0;t<nImage;t++)
		dcBuffer[t].CreateCompatibleDC(&dc);

	CBitmap bitmap_buffer[nImage];

	for(t=0;t<nImage;t++) {
		for(m=0;m<Height;m++)
			for(n=0;n<Width;n++)  {
				Bt[m][n] = B[m][n];
				Gt[m][n] = G[m][n];
				Rt[m][n] = R[m][n];
			}

		for(m=0;m<Height;m++)
			for(n=0;n<Width-shift;n++) {
				B[m][n+shift] = Bt[m][n];
				G[m][n+shift] = Gt[m][n];
				R[m][n+shift] = Rt[m][n];
			} 
	
		for(m=0;m<Height;m++)
			for(n=0;n<shift;n++) {
				B[m][n] = Bt[m][n+Width-shift];
				G[m][n] = Gt[m][n+Width-shift];
				R[m][n] = Rt[m][n+Width-shift];
			}

		i=0;
		for(m=0;m<Height;m++) 
			for(n=0;n<Width;n++) {
				m_pImage->m_pDib[i++]=B[m][n];
				m_pImage->m_pDib[i++]=G[m][n];
				m_pImage->m_pDib[i++]=R[m][n]; 
			}

		bitmap_buffer[t].CreateCompatibleBitmap(&dc,Width,Height);
		dcBuffer[t].SelectObject(&bitmap_buffer[t]);

		//	BITMAPINFOHEADER 
		SIZE size;
		size.cx=Width,size.cy=Height;

		int Colornum=0;  // no Palette
		m_pImage->AllocBmpInfo(Colornum);
		m_pImage->SetBmpInfo(size,Colornum);  // no palette in True Color

		// BITMAPFILEHEADER 
		m_pImage->SetBmpHeader(size,Colornum); 

		SetStretchBltMode(dcBuffer[t], COLORONCOLOR);
		SetDIBitsToDevice(
				dcBuffer[t],                 // hDC
				0,				// DestX 출력할 DC 의 시작 X 좌표
				0,				// DestY 출력할 DC 의 시작 Y 좌표
				Width,			// nDestWidth DIB 의 가로 크기
				Height,			// nDestHeight DIB 의 세로 크기
				0,				// SrcX  DIB 의 출력 시작 X 좌표
				0,				// SrcY  DIB 의 출력 시작 Y 좌표
				0,               // nStartScan 배열에서 처음 스캔할 위치
				Height,			// nNumScans
				m_pImage->m_pDib,          // lpBits 
				m_pImage->pBitmapInfo,     // lpBitsInfo
				DIB_RGB_COLORS); // wUsage

		dc.BitBlt(0,0,Width,Height,&dcBuffer[t],0,0,SRCCOPY);
	} 

	dcMem.SelectObject(pOldBitmap);
	ReleaseDC(&dcMem);
}

void CShiftPlayerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	for(int t=0;t<nImage;t++) {
		ReleaseDC(&dcBuffer[t]);
	}

	KillTimer(0);
	delete m_pImage->m_pDib;	
	for(int i=0;i<Height;i++) free(R[i]),free(G[i]),free(B[i]);
	free(R),free(G),free(B);
	for(i=0;i<Height;i++) free(Rt[i]),free(Gt[i]),free(Bt[i]);
	free(Rt),free(Gt),free(Bt);
}

void CShiftPlayerDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==0 && Toggle==1) {
		ShowFigure();
		count++;
		if(count==nImage) count=0;
	}
	CDialog::OnTimer(nIDEvent);
}

void CShiftPlayerDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU_MAIN);

	CMenu* pSubMenu = menu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,pt.x,pt.y,this);
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CShiftPlayerDlg::OnUpdatePlay(CCmdUI* pCmdUI) 
{
	Toggle=1;
	count=0;
}
