; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWBCompensatorDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WBCompensator.h"

ClassCount=2
Class1=CWBCompensatorApp
Class2=CWBCompensatorDlg

ResourceCount=6
Resource2=IDR_MAINFRAME
Resource3=IDR_MENU_MAIN (Korean)
Resource4=IDD_WBCOMPENSATOR_DIALOG
Resource5=IDD_WBCOMPENSATOR_DIALOG (Korean)
Resource6=IDR_MENU_MAIN

[CLS:CWBCompensatorApp]
Type=0
HeaderFile=WBCompensator.h
ImplementationFile=WBCompensator.cpp
Filter=N

[CLS:CWBCompensatorDlg]
Type=0
HeaderFile=WBCompensatorDlg.h
ImplementationFile=WBCompensatorDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_SHOW_FIGURES



[DLG:IDD_WBCOMPENSATOR_DIALOG]
Type=1
Class=CWBCompensatorDlg
ControlCount=0

[MNU:IDR_MENU_MAIN]
Type=1
Class=CWBCompensatorDlg
Command1=ID_COMPENSATION
Command2=ID_SHOW_FIGURES
CommandCount=2

[DLG:IDD_WBCOMPENSATOR_DIALOG (Korean)]
Type=1
Class=?
ControlCount=0

[MNU:IDR_MENU_MAIN (Korean)]
Type=1
Class=?
Command1=ID_COMPENSATION
Command2=ID_SHOW_FIGURES
CommandCount=2

