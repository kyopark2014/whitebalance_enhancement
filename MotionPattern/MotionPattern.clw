; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMotionPatternDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MotionPattern.h"

ClassCount=2
Class1=CMotionPatternApp
Class2=CMotionPatternDlg

ResourceCount=5
Resource2=IDR_MAINFRAME
Resource3=IDD_MOTIONPATTERN_DIALOG
Resource4=IDD_MOTIONPATTERN_DIALOG (English (U.S.))
Resource5=IDR_MENU_MAIN (English (U.S.))

[CLS:CMotionPatternApp]
Type=0
HeaderFile=MotionPattern.h
ImplementationFile=MotionPattern.cpp
Filter=N

[CLS:CMotionPatternDlg]
Type=0
HeaderFile=MotionPatternDlg.h
ImplementationFile=MotionPatternDlg.cpp
Filter=D
LastObject=CMotionPatternDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_MOTIONPATTERN_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CMotionPatternDlg

[DLG:IDD_MOTIONPATTERN_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=0

[MNU:IDR_MENU_MAIN (English (U.S.))]
Type=1
Class=CMotionPatternDlg
Command1=ID_FILE_OPEN
Command2=ID_MOVIE_PLAY
Command3=ID_MOVIE_PAUSE
Command4=ID_MOVIE_STOP
Command5=ID_QUIT_APP
Command6=ID_MENU_CAPTURE
CommandCount=6

