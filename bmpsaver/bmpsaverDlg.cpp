// bmpsaverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bmpsaver.h"
#include "bmpsaverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpsaverDlg dialog

CBmpsaverDlg::CBmpsaverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBmpsaverDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBmpsaverDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBmpsaverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBmpsaverDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBmpsaverDlg, CDialog)
	//{{AFX_MSG_MAP(CBmpsaverDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpsaverDlg message handlers

BOOL CBmpsaverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_pImage=new CBaseImage;
	
	Width=640,Height=480;
	// TODO: Add extra initialization here
	SetWindowPos(NULL,0,0,Width,Height,SWP_NOMOVE|SWP_SHOWWINDOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBmpsaverDlg::OnPaint() 
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

		Drawing(Width,Height,&dc);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBmpsaverDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBmpsaverDlg::Drawing(int Width,int Height,CDC* dc)
{
	CBrush brush(RGB(255,0,0));
	CBrush* pOldBrush = dc->SelectObject(&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID,5,RGB(255,0,0));
	CPen* pOldPen = dc->SelectObject(&pen);

	//dc->Rectangle(10,10,Width-10,Height-10);
	dc->Rectangle(0,0,Width,Height);

	dc->SelectObject(pOldBrush);
	dc->SelectObject(pOldPen);


	CBrush brush1(RGB(0,255,0));
	CBrush* pOldBrush1 = dc->SelectObject(&brush1);

	CPen pen1;
	pen1.CreatePen(PS_SOLID,5,RGB(0,255,0));
	CPen* pOldPen1 = dc->SelectObject(&pen1);

	dc->Rectangle(100,100,Width-100,Height-100);

	dc->SelectObject(pOldBrush1);
	dc->SelectObject(pOldPen1);
}

void CBmpsaverDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int rWidth;
	int b,g,r,i,m,n;

	if(nChar=='1')	{
		CWindowDC dc(this);

		// Load m_pDid from DC 
		LPSTR m_Dib;
		rWidth=(Width+3)/4*4;
		m_Dib = new char[(rWidth*Height)*3];
		memset(m_Dib, 0, (rWidth*Height)*3);
	
		COLORREF pcolor;
		i=0;
		for(m=0;m<Height;m++) {
			for(n=0;n<rWidth;n++) {
				pcolor = dc.GetPixel(n,Height-1-m);
			
				b=GetBValue(pcolor);
				m_Dib[i]=b;i++;
				g=GetGValue(pcolor);
				m_Dib[i]=g;i++;
				r=GetRValue(pcolor);
				m_Dib[i]=r;i++; 
			}
		}

		SIZE size;
		size.cx=rWidth, size.cy=Height;
		if(m_pImage)
			m_pImage->ImageToDC(size,m_Dib); 
		
		delete m_Dib;
	}

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}
