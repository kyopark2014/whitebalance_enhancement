// VideoWnd.cpp : implementation file
//

#include "stdafx.h"

#include <mmsystem.h>
#include <mmstream.h>	    // Multimedia stream interfaces
#include <mmreg.h>
#include <amstream.h>	    // DirectShow multimedia stream interfaces
#include <initguid.h>     // Defines DEFINE_GUID macro and enables GUID initialization
#include <evcode.h>

#include <atlbase.h>
CComModule _Module;

#include <atlcom.h>
#include <atlimpl.cpp>

#include "VideoWnd.h"
#include "globalfunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment( lib, "amstrmid.lib" )
#pragma comment( lib, "quartz.lib" )
#pragma comment( lib, "strmbase.lib" )
#pragma comment( lib, "ddraw.lib" )
#pragma comment( lib, "winmm.lib" )

#define CHECK_ERROR(x)    if( FAILED(x) ) { goto Error; }
#define CHECK_FAIL(x)	    if( FAILED(x) ) { return E_FAIL; }
#define CHECK_FALSE(x)    if( FAILED(x) ) { return FALSE; }

#define HELPER_RELEASE(x) { if(x) x->Release(); x = NULL; }

#define WM_GRAPHNOTIFY    WM_USER + 1

/////////////////////////////////////////////////////////////////////////////
// CVideoWnd

CVideoWnd::CVideoWnd()
{
  m_hCursor = NULL;

  //DirectDrawEx interfaces
	m_pDD               = NULL;
	m_pDD3              = NULL;
	m_pDDF              = NULL;
	m_pPrimarySurface   = NULL;
	m_pDDSOffscreen     = NULL;
	m_pDDSOffscreen2    = NULL;
	m_pDDClipper        = NULL;

	//MultiMedia streaming interfaces
	m_pMMStream         = NULL;
	m_pPrimaryVidStream = NULL;    
	m_pDDStream         = NULL;
	m_pSample           = NULL;

  m_pGraphBuilder     = NULL;
  m_pMediaEventEx     = NULL;

  VERIFY(m_fntCaption.CreateFont(
     12,                        // nHeight
     0,                         // nWidth
     0,                         // nEscapement
     0,                         // nOrientation
     FW_NORMAL,                 // nWeight
     FALSE,                     // bItalic
     FALSE,                     // bUnderline
     0,                         // cStrikeOut
     ANSI_CHARSET,              // nCharSet
     OUT_DEFAULT_PRECIS,        // nOutPrecision
     CLIP_DEFAULT_PRECIS,       // nClipPrecision
     DEFAULT_QUALITY,           // nQuality
     DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
     "굴림"));                  // lpszFacename

  initVariables();
}

CVideoWnd::~CVideoWnd()
{
  deleteContents();

  if( m_fntCaption.m_hObject )
    m_fntCaption.DeleteObject();
}

BEGIN_MESSAGE_MAP(CVideoWnd, CWnd)
	//{{AFX_MSG_MAP(CVideoWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
  ON_MESSAGE( WM_GRAPHNOTIFY, onGraphNotify )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoWnd message handlers

void CVideoWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if( !m_bFileLoaded )
	{
		CRect rcClient;
		GetClientRect( &rcClient );

		dc.FillSolidRect( &rcClient, RGB(0, 0, 0) );
	}
	else
	{
		if( m_bPaused )
		renderToSurface();
	}
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CVideoWnd::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
	
//	return CWnd::OnEraseBkgnd(pDC);
}

void CVideoWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);

	if( point.x >= m_rcClient.right - 10 && point.y >= m_rcClient.bottom - 10 )
	{
		if( !m_hCursor )
		{
			m_hCursor = LoadCursor( NULL, IDC_SIZENWSE );
			SetCursor( m_hCursor );
		}
	}
	else
		m_hCursor = NULL;
}

void CVideoWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);

	CWnd* pParent = GetParent();
	ASSERT( pParent != NULL );

	LPARAM lParam = MAKELPARAM( point.x, point.y );
	pParent->PostMessage( WM_LBUTTONDOWN, (WPARAM) nFlags, lParam );

	if( point.x >= m_rcClient.right - 10 && point.y >= m_rcClient.bottom - 10 )
		pParent->PostMessage( WM_NCLBUTTONDOWN, HTBOTTOMRIGHT, lParam );
	else
		pParent->PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, lParam );
}

void CVideoWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnRButtonDown(nFlags, point);

	CWnd* pParent = GetParent();
		ASSERT( pParent != NULL );

	pParent->PostMessage( WM_RBUTTONDOWN, (WPARAM) nFlags, MAKELPARAM(point.x, point.y) ); 
}

BOOL CVideoWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if( m_hCursor )	
		return TRUE;
	
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CVideoWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	GetClientRect( &m_rcClient );
}

/////////////////////////////////////////////////////////////////////////////
// CVideoWnd user functions

// initVariables
void CVideoWnd::initVariables( void )
{
	m_strFileName       = _T("");

	m_bFileLoaded       = FALSE;
	m_bPaused           = FALSE;

	m_strCaption        = _T("");

	m_streamTime        = 0;
	m_nTimer            = NULL;

	m_hRenderingThread  = NULL;

	m_rcClient.SetRect( 0, 0, 0, 0 );
	m_sizeVideo.cx = m_sizeVideo.cy = 0;
}

// deleteContents
void CVideoWnd::deleteContents( void )
{
  // Release MultiMedia streaming Objects
  HELPER_RELEASE( m_pMMStream );
  HELPER_RELEASE( m_pSample );
  HELPER_RELEASE( m_pDDStream );
  HELPER_RELEASE( m_pPrimaryVidStream );

  // Release DirectDrawEx interfaces
  HELPER_RELEASE( m_pDDSOffscreen );
  HELPER_RELEASE( m_pDDSOffscreen2 );
  HELPER_RELEASE( m_pDDClipper );
  HELPER_RELEASE( m_pPrimarySurface );
  HELPER_RELEASE( m_pDD3 );
  HELPER_RELEASE( m_pDD );
  HELPER_RELEASE( m_pDDF );

  HELPER_RELEASE( m_pGraphBuilder );
  HELPER_RELEASE( m_pMediaEventEx );

  // Initialize variables
  initVariables();

  CoUninitialize();
}

// initDDrawEx
HRESULT CVideoWnd::initDDrawEx( void )
{
  CoInitialize( NULL );

  HRESULT       hr = NOERROR;
  DDSURFACEDESC ddsd, ddsd2, ddsd3;

  // Create a DirectDrawFactory object
  hr = CoCreateInstance( CLSID_DirectDrawFactory, NULL, CLSCTX_INPROC_SERVER,
                         IID_IDirectDrawFactory, (void**) &m_pDDF );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Couldn't create DirectDrawFactory.") );
    return E_FAIL;
  }

	// Call the IDirectDrawFactory::CreateDirectDraw method to create the 
	// DirectDraw object, set the cooperative level, and get the address 
	// of an IDirectDraw interface pointer
  hr = m_pDDF->CreateDirectDraw( NULL, m_hWnd /*::GetDesktopWindow()*/, DDSCL_NORMAL,
                                 NULL, NULL, &m_pDD );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Couldn't create DirectDraw object.") );
    return E_FAIL;
  }

  // Now query for the new IDirectDraw3 interface
  hr = m_pDD->QueryInterface( IID_IDirectDraw3, (void**) &m_pDD3 );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Couldn't get IDirectDraw3.") );
    return E_FAIL;
  }

  // Initialize the DDSURFACEDESC structure for the primary surface
  ZeroMemory( &ddsd, sizeof(ddsd) );
  ddsd.dwSize         = sizeof(ddsd);
  ddsd.dwFlags        = DDSD_CAPS;
  ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

  hr = m_pDD3->CreateSurface( &ddsd, &m_pPrimarySurface, NULL );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Couldn't create Primary Surface.") );
    return E_FAIL;
  }

  // Now, do the same for the offscreen surface.
  // The offscreen surface needs to use the same pixel format as the primary.
  // Query the primary surface to for its pixel foramt.
  hr = m_pPrimarySurface->GetSurfaceDesc( &ddsd );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Couldn't GetSurfaceDesc.") );
    return E_FAIL;
  }

  // Now, set the info for the offscreen surface #1, using the primary's pixel format.
  ZeroMemory( &ddsd2, sizeof(ddsd2) );
  ddsd2.dwSize          = sizeof(ddsd2);
  ddsd2.dwFlags         = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
  ddsd2.ddsCaps.dwCaps  = DDSCAPS_OFFSCREENPLAIN;
  ddsd2.dwHeight        = ddsd.dwHeight;
  ddsd2.dwWidth         = ddsd.dwWidth;
  ddsd2.ddpfPixelFormat = ddsd.ddpfPixelFormat;

  // Now, create the offscreen surface #1 and query for the latest interface.
  hr = m_pDD3->CreateSurface( &ddsd2, &m_pDDSOffscreen, NULL );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Couldn't create Offscreen Surface.") );
    return E_FAIL;
  }

  // Now, set the info for the offscreen surface #2, using the primary's pixel format.
  ZeroMemory( &ddsd3, sizeof(ddsd3) );
  ddsd3.dwSize          = sizeof(ddsd3);
  ddsd3.dwFlags         = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
  ddsd3.ddsCaps.dwCaps  = DDSCAPS_OFFSCREENPLAIN;
  ddsd3.dwHeight        = ddsd.dwHeight;
  ddsd3.dwWidth         = ddsd.dwWidth;
  ddsd3.ddpfPixelFormat = ddsd.ddpfPixelFormat;

  // Now, create the offscreen suface #2 and query for the latest interface.
  hr = m_pDD3->CreateSurface( &ddsd3, &m_pDDSOffscreen2, NULL );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Couldn't create Offscreen Surface2.") );
    return E_FAIL;
  }

  // Add code for clipper
  hr = m_pDD3->CreateClipper( 0, &m_pDDClipper, NULL );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Couldn't create Clipper.") );
    return E_FAIL;
  }

  hr = m_pPrimarySurface->SetClipper( m_pDDClipper );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Call to SetClipper failed.") );
    return E_FAIL;
  }

  hr = m_pDDClipper->SetHWnd( 0, m_hWnd );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Call to SetHWnd failed.") );
    return E_FAIL;
  }

  return NOERROR;
}

// renderFileToMMStream
HRESULT CVideoWnd::renderFileToMMStream( LPCTSTR lpszFileName )
{
  HRESULT hr;
  CComPtr<IAMMultiMediaStream> pAMStream;

  // Convert filename to Unicode
  WCHAR wFile[MAX_PATH];
  MultiByteToWideChar( CP_ACP, 0, lpszFileName, -1, wFile,
                       sizeof(wFile) / sizeof(wFile[0]) );

  // Create the AMMultiMediaStream object
  hr = CoCreateInstance( CLSID_AMMultiMediaStream, NULL, CLSCTX_INPROC_SERVER,
                         IID_IAMMultiMediaStream, (void**) &pAMStream );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Couldn't create a CLSID_MultiMediaStream object.") );
    return E_FAIL;
  }

  // Initialize Stream
  hr = pAMStream->Initialize( STREAMTYPE_READ, 0, NULL );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Initialize failed.") );
    return E_FAIL;
  }

  // Add primary video stream
  hr = pAMStream->AddMediaStream( m_pDD3, &MSPID_PrimaryVideo, 0, NULL );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("AddMediaStream failed.") );
    return E_FAIL;
  }

  // Add primary audio stream
  hr = pAMStream->AddMediaStream( NULL, &MSPID_PrimaryAudio, AMMSF_ADDDEFAULTRENDERER, NULL );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("AddMediaStream failed.") );
    return E_FAIL;
  }

  // Opens and automatically creates a filter graph for the specified media file
  hr = pAMStream->OpenFile( wFile, 0 );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("File format not supported.") );
    return E_FAIL;
  }

  // save the local stream to the global variable
  m_pMMStream = pAMStream;

  // Add a reference to the file
  (*pAMStream).AddRef();

  hr = pAMStream->GetFilterGraph( &m_pGraphBuilder );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("GetFilterGraph failed.") );
    return E_FAIL;
  }

  hr = m_pGraphBuilder->QueryInterface( IID_IMediaEventEx, (void**) &m_pMediaEventEx );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("Couldn't get MediaEventEx interface.") );
    return E_FAIL;
  }

  hr = m_pMediaEventEx->SetNotifyFlags( 0x00 );
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("SetNotifyFlags failed.") );
    return E_FAIL;
  }

  hr = m_pMediaEventEx->SetNotifyWindow( (OAHWND) m_hWnd, WM_GRAPHNOTIFY, 0);
  if( FAILED(hr) )
  {
    AfxMessageBox( _T("SetNotifyWindow failed") );
    return E_FAIL;
  }

  return NOERROR;
}

// initRenderToSurface
HRESULT CVideoWnd::initRenderToSurface( void )
{
  DDSURFACEDESC ddsd;

  // Use the multimedia stream to get the primary video media stream
  CHECK_ERROR( m_pMMStream->GetMediaStream(MSPID_PrimaryVideo, &m_pPrimaryVidStream) );

  // Use the media stream to get the IDirectDrawMediaStream
  CHECK_ERROR( m_pPrimaryVidStream->QueryInterface(IID_IDirectDrawMediaStream, (void**) &m_pDDStream) );

  // Must set dwSize before calling GetFormat
  ddsd.dwSize = sizeof(ddsd);
  CHECK_ERROR( m_pDDStream->GetFormat(&ddsd, NULL, NULL, NULL) );

  m_sizeVideo.cx = ddsd.dwWidth;
  m_sizeVideo.cy = ddsd.dwHeight;

  // Create the stream sample in offscreen surface #2 (attachment)
  CHECK_ERROR( m_pDDStream->CreateSample(m_pDDSOffscreen2, &CRect(0, 0, m_sizeVideo.cx, m_sizeVideo.cy), 
                                         0, &m_pSample) );

  return NOERROR;

Error:
  AfxMessageBox( _T("Initialize failure in InitRenderToSurface.") );

  return E_FAIL;
}

// renderToSurface
HRESULT CVideoWnd::renderToSurface( void )
{
  if( !m_bFileLoaded ) 
    return E_FAIL;

  // update each frame
  if( !m_bPaused )
    CHECK_FAIL( m_pSample->Update(0, NULL, NULL, 0) );

  // blit from offscreen surface #2 (video sample-backbuffer)
  // to the offscreen surface #1 (copy-backbuffer)
  CRect rcVideo( 0, 0, m_sizeVideo.cx, m_sizeVideo.cy );
  CHECK_FAIL( m_pDDSOffscreen->BltFast( 0, 0, m_pDDSOffscreen2, &rcVideo, DDBLTFAST_WAIT) );

  // start GDI operations to perform overlay on top of offscreen#1
  HDC hOffscreenDC;
  m_pDDSOffscreen->GetDC( &hOffscreenDC );

  CDC* pDC = CDC::FromHandle( hOffscreenDC );
  ASSERT( pDC != NULL );

  int nSavedDC = pDC->SaveDC();
  pDC->SetBkMode( TRANSPARENT );

  if( m_strCaption.GetLength() > 0 )
    drawCaption( pDC );

  pDC->RestoreDC( nSavedDC );
  m_pDDSOffscreen->ReleaseDC( hOffscreenDC );

  CRect rcWnd( m_rcClient );
  ClientToScreen( &rcWnd );

  // stretchblit from offscreen #1 to the primary surface
  CHECK_FAIL( m_pPrimarySurface->Blt(&rcWnd, m_pDDSOffscreen, &rcVideo, DDBLT_WAIT, NULL) );

  return NOERROR;
}

// drawCaption
void CVideoWnd::drawCaption( CDC* pDC )
{
  pDC->SelectObject( &m_fntCaption );

  CRect rcVideo( 0, 0, m_sizeVideo.cx, m_sizeVideo.cy );
  CRect rcCaption( 0, 0, rcVideo.right, 0 );

  pDC->DrawText( m_strCaption, rcCaption, DT_CALCRECT | DT_CENTER | DT_WORDBREAK );
  rcCaption.SetRect( 0, rcVideo.bottom - rcCaption.Height() - 5, rcVideo.right, rcVideo.bottom );

  pDC->SetTextColor( RGB(0, 0, 0) );

  for( int i = -1; i <= 1; i++ )
  {
    for( int j = -1; j <= 1; j++ )
      pDC->DrawText( m_strCaption, &(rcCaption + CPoint(i, j)), DT_CENTER | DT_WORDBREAK );
  }

  pDC->SetTextColor( RGB(255, 255, 255) );
  pDC->DrawText( m_strCaption, &rcCaption, DT_CENTER | DT_WORDBREAK );
}

// onGraphNotify
void CVideoWnd::onGraphNotify( WPARAM wParam, LPARAM lParam )
{
  long lEventCode, lParam1, lParam2;

  if( SUCCEEDED(m_pMediaEventEx->GetEvent(&lEventCode, &lParam1, &lParam2, 0)) ) 
  {
    if( lEventCode == EC_OLE_EVENT ) 
    {
      m_strCaption = CString((BSTR)lParam2);
      parseCaption();
    }

    m_pMediaEventEx->FreeEventParams(lEventCode, lParam1, lParam2);

    switch( lEventCode )
    {
    case EC_COMPLETE:
    case EC_ERRORABORT:
    case EC_USERABORT:
      stop();
      break;
    }
  }
}

// parseCaption
void CVideoWnd::parseCaption( void )
{
  int len = m_strCaption.GetLength();
  int pos = m_strCaption.Find( _T('>') );

  m_strCaption = m_strCaption.Right( len - pos - 1 );

  m_strCaption.Replace( _T("nbsp;"), _T(" ") );
  m_strCaption.Replace( _T("<br>"), _T("\n") );
  m_strCaption.Replace( _T("<BR>"), _T("\n") );

  int pos1 = -1, pos2 = -1;
  while( (pos1 = m_strCaption.Find( _T('<'), 0)) != -1 )
  {
    if( (pos2 = m_strCaption.Find( _T('>'), 0)) != -1 )
      m_strCaption.Delete( pos1, pos2 - pos1 + 1 );
  }
}

// open
BOOL CVideoWnd::open( LPCTSTR lpszFileName )
{
  // If a file is already open - call STOP first
	if(m_bFileLoaded)  close();

	CHECK_ERROR( initDDrawEx() );
	CHECK_ERROR( renderFileToMMStream(lpszFileName) );
	CHECK_ERROR( initRenderToSurface() );

	openSMIFile( lpszFileName );

	m_strFileName = lpszFileName;

	m_bFileLoaded = TRUE;
	m_bPaused     = TRUE;

	GetClientRect( &m_rcClient );

	DWORD dwThreadID;
	m_hRenderingThread = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)(CVideoWnd::renderingThread), 
                                     this, 0, &dwThreadID );
	return TRUE; 

Error:
	deleteContents();
	return FALSE; 
	return TRUE;
}

// openSMIFile
BOOL CVideoWnd::openSMIFile( LPCTSTR lpszFileName )
{
	CString strSMIFile;

	TCHAR drive[_MAX_DRIVE] = _T(""), dir[_MAX_DIR] = _T("");
	TCHAR fname[_MAX_FNAME] = _T(""), ext[_MAX_EXT] = _T("");

	_tsplitpath( lpszFileName, drive, dir, fname, ext );
	strSMIFile.Format( "%s%s%s.smi", drive, dir, fname );

	if( !__isFileExist(strSMIFile) )
		return FALSE;

	WCHAR wFile[MAX_PATH];
	MultiByteToWideChar( CP_ACP, 0, strSMIFile, -1, wFile,
                       sizeof(wFile) / sizeof(wFile[0]) );

	CHECK_FALSE( m_pGraphBuilder->RenderFile(wFile, 0) );

	return TRUE;
}

// play
BOOL CVideoWnd::play( void )
{
	if( !m_bFileLoaded )
		return FALSE;

	CHECK_FALSE( m_pMMStream->Seek(m_streamTime) );
	CHECK_FALSE( m_pMMStream->SetState(STREAMSTATE_RUN) );

	m_bPaused = FALSE;
	setTimer();

	return TRUE;
}

// stop
BOOL CVideoWnd::stop( void )
{
	if( !m_bFileLoaded )
		return FALSE;

	CHECK_FALSE( m_pMMStream->SetState(STREAMSTATE_STOP) );

	killTimer();
	m_bPaused = TRUE;
	m_streamTime = 0;

	CHECK_FALSE( m_pMMStream->Seek(m_streamTime) );
	CHECK_FALSE( m_pMMStream->SetState(STREAMSTATE_RUN) );
	CHECK_FALSE( m_pMMStream->SetState(STREAMSTATE_STOP) );

	m_streamTime = 0;

	return TRUE;
}

// pause
BOOL CVideoWnd::pause( void )
{
	if( !m_bFileLoaded )
		return FALSE;

	CHECK_FALSE( m_pMMStream->GetTime(&m_streamTime) );
	CHECK_FALSE( m_pMMStream->SetState(STREAMSTATE_STOP) );

	killTimer();
	m_bPaused = TRUE;

	return TRUE;
}

// close
void CVideoWnd::close( void )
{
	if( m_bFileLoaded )
	{
		killTimer();

		if( m_hRenderingThread )
		{
			m_bFileLoaded = FALSE;
			if( m_bPaused ) TerminateThread( m_hRenderingThread, 0 );
			else 			WaitForSingleObject( m_hRenderingThread, INFINITE );        
			CloseHandle( m_hRenderingThread );
		}
		deleteContents();
	}
}

// setTimer
void CVideoWnd::setTimer( void )
{
	killTimer();
	m_nTimer = timeSetEvent( 125, 0, CVideoWnd::timerProc, (DWORD)this, TIME_PERIODIC );
}

// killTimer
void CVideoWnd::killTimer( void )
{
	if( m_nTimer != NULL )
		timeKillEvent( m_nTimer );

	m_nTimer = NULL;
}

// timerProc
void CALLBACK CVideoWnd::timerProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	CVideoWnd* pWnd = (CVideoWnd*) dwUser;
	ASSERT( pWnd != NULL );

	ASSERT( pWnd->m_pMMStream != NULL );

	STREAM_TIME streamTime;
	if( FAILED(pWnd->m_pMMStream->GetTime(&streamTime)) )
		return;

  // 미구현, 시간표시 용으로 사용
}

// renderingThread
DWORD WINAPI CVideoWnd::renderingThread( LPVOID lParam )
{
	CVideoWnd* pWnd = (CVideoWnd*) lParam;
	ASSERT( pWnd != NULL );

	while( pWnd->m_bFileLoaded )
	{
		if( !pWnd->m_bPaused )
			pWnd->renderToSurface();
	}

	return 0;
}
