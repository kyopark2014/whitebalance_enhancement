; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShiftPlayerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ShiftPlayer.h"

ClassCount=2
Class1=CShiftPlayerApp
Class2=CShiftPlayerDlg

ResourceCount=4
Resource2=IDR_MAINFRAME
Resource3=IDD_SHIFTPLAYER_DIALOG
Resource4=IDR_MENU_MAIN

[CLS:CShiftPlayerApp]
Type=0
HeaderFile=ShiftPlayer.h
ImplementationFile=ShiftPlayer.cpp
Filter=N

[CLS:CShiftPlayerDlg]
Type=0
HeaderFile=ShiftPlayerDlg.h
ImplementationFile=ShiftPlayerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_PLAY



[DLG:IDD_SHIFTPLAYER_DIALOG]
Type=1
Class=CShiftPlayerDlg
ControlCount=0

[MNU:IDR_MENU_MAIN]
Type=1
Class=?
Command1=ID_PLAY
CommandCount=1

