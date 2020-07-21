; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPdp_viewerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "pdp_viewer.h"

ClassCount=2
Class1=CPdp_viewerApp
Class2=CPdp_viewerDlg

ResourceCount=4
Resource2=IDR_MAINFRAME
Resource3=IDD_PDP_VIEWER_DIALOG
Resource4=IDR_MENU_MAIN

[CLS:CPdp_viewerApp]
Type=0
HeaderFile=pdp_viewer.h
ImplementationFile=pdp_viewer.cpp
Filter=N
LastObject=CPdp_viewerApp

[CLS:CPdp_viewerDlg]
Type=0
HeaderFile=pdp_viewerDlg.h
ImplementationFile=pdp_viewerDlg.cpp
Filter=D
LastObject=CPdp_viewerDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_PDP_VIEWER_DIALOG]
Type=1
Class=CPdp_viewerDlg
ControlCount=0

[MNU:IDR_MENU_MAIN]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_MOVIE_PLAY
Command3=ID_MOVIE_PAUSE
Command4=ID_MOVIE_STOP
Command5=ID_QUIT_APP
CommandCount=5

