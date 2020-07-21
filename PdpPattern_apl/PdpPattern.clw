; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPdpPatternDlg
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PdpPattern.h"

ClassCount=3
Class1=CPdpPatternApp
Class2=CPdpPatternDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Class3=CPdpTP
Resource2=IDD_PDPPATTERN_DIALOG
Resource3=IDR_MENU_MAIN

[CLS:CPdpPatternApp]
Type=0
HeaderFile=PdpPattern.h
ImplementationFile=PdpPattern.cpp
Filter=N

[CLS:CPdpPatternDlg]
Type=0
HeaderFile=PdpPatternDlg.h
ImplementationFile=PdpPatternDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CPdpPatternDlg



[DLG:IDD_PDPPATTERN_DIALOG]
Type=1
Class=CPdpPatternDlg
ControlCount=0

[CLS:CPdpTP]
Type=0
HeaderFile=PdpTP.h
ImplementationFile=PdpTP.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CPdpTP

[MNU:IDR_MENU_MAIN]
Type=1
Class=?
Command1=ID_PATTERN_A
Command2=ID_Pattern_B
Command3=ID_PRG_QUIT
CommandCount=3

