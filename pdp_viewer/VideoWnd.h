#ifndef __VIDEOWND_H__
#define __VIDEOWND_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoWnd.h : header file
//

#include <strmif.h>			// IGraphBuilder
#include <control.h>		// IMediaControl
#include <uuids.h>			// CLSID_FilterGraph

#include <ddstream.h>	  // DirectDraw multimedia stream interfaces
#include <ddrawex.h>	  // DirectDrawEx interfaces

/////////////////////////////////////////////////////////////////////////////
// CVideoWnd window

class CVideoWnd : public CWnd
{
public:
	CVideoWnd();
	virtual ~CVideoWnd();

// Attributes
protected:
  HCURSOR     m_hCursor;
  CFont       m_fntCaption;

	// DirectDrawEx interfaces
	IDirectDraw*          m_pDD;
	IDirectDraw3*         m_pDD3;
	IDirectDrawFactory*   m_pDDF;
	IDirectDrawSurface*   m_pPrimarySurface;
	IDirectDrawSurface*   m_pDDSOffscreen;
	IDirectDrawSurface*   m_pDDSOffscreen2;
	IDirectDrawClipper*   m_pDDClipper;

	// MultiMedia streaming interfaces
	IMultiMediaStream*        m_pMMStream;
	IMediaStream*             m_pPrimaryVidStream;    
	IDirectDrawMediaStream*   m_pDDStream;
	IDirectDrawStreamSample*  m_pSample;

public:
  IGraphBuilder*         m_pGraphBuilder;
  IMediaEventEx*         m_pMediaEventEx;

  STREAM_TIME m_streamTime;

  CRect       m_rcClient;
  CSize       m_sizeVideo;

  CString     m_strFileName;

  BOOL        m_bFileLoaded;
  BOOL        m_bPaused;

  CString     m_strCaption;

  HANDLE      m_hRenderingThread;

  UINT        m_nTimer;

// Operations
protected:
  HRESULT     initDDrawEx( void );
  HRESULT     renderFileToMMStream( LPCTSTR lpszFileName );
  HRESULT     initRenderToSurface( void );
  HRESULT     renderToSurface( void );

  BOOL        openSMIFile( LPCTSTR lpszFileName );
  void        parseCaption( void );
  void        drawCaption( CDC* pDC );

  void        initVariables( void );
  void        deleteContents( void );

  void        setTimer( void );
  void        killTimer( void );

  void        onGraphNotify( WPARAM wParam, LPARAM lParam );

  static DWORD WINAPI   renderingThread( LPVOID lParam );
  static void CALLBACK  timerProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

public:
  BOOL        open( LPCTSTR lpszFileName );
  void        close( void );

  BOOL        play( void );
  BOOL        stop( void );
  BOOL        pause( void );

  inline const CSize& getVideoSize( void );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoWnd)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CVideoWnd)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline const CSize& CVideoWnd::getVideoSize( void )
{
  return (const CSize&) m_sizeVideo;
}

#endif
