# Microsoft Developer Studio Project File - Name="WinCalc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WinCalc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WinCalc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinCalc.mak" CFG="WinCalc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinCalc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WinCalc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "WinCalc"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinCalc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "lib" /I "resource" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "WinCalc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "lib" /I "resource" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "WinCalc - Win32 Release"
# Name "WinCalc - Win32 Debug"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Resource\main.ico
# End Source File
# Begin Source File

SOURCE=.\Resource\resource.h
# End Source File
# Begin Source File

SOURCE=.\Resource\Script.rc
# End Source File
# End Group
# Begin Group "Lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Lib\auto_vector.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Button.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Canvas.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Class.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Class.h
# End Source File
# Begin Source File

SOURCE=.\Lib\ComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\ComboBox.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Command.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Controller.h
# End Source File
# Begin Source File

SOURCE=.\Lib\controls.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Dialog.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Edit.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Edit.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Exception.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Exception.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Icon.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Icon.h
# End Source File
# Begin Source File

SOURCE=.\Lib\ListBox.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Maker.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Maker.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Menu.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Menu.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Mouse.h
# End Source File
# Begin Source File

SOURCE=.\Lib\MsgLoop.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\MsgLoop.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Procedure.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Procedure.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Static.h
# End Source File
# Begin Source File

SOURCE=.\Lib\StatusBar.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Tools.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Tools.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Util.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Util.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Win.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Win.h
# End Source File
# End Group
# Begin Group "documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# End Group
# Begin Group "Model"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Model\AVLtree.h
# End Source File
# Begin Source File

SOURCE=.\Model\AVLtreeIMP.h
# End Source File
# Begin Source File

SOURCE=.\Model\database.cpp
# End Source File
# Begin Source File

SOURCE=.\Model\database.h
# End Source File
# Begin Source File

SOURCE=.\Model\datafile.cpp
# End Source File
# Begin Source File

SOURCE=.\Model\datafile.h
# End Source File
# Begin Source File

SOURCE=.\Model\record.cpp
# End Source File
# Begin Source File

SOURCE=.\Model\record.h
# End Source File
# Begin Source File

SOURCE=.\Model\RecordStruct.cpp
# End Source File
# Begin Source File

SOURCE=.\Model\RecordStruct.h
# End Source File
# Begin Source File

SOURCE=.\Model\SearchObject.cpp
# End Source File
# Begin Source File

SOURCE=.\Model\SearchObject.h
# End Source File
# Begin Source File

SOURCE=.\Model\SearchStruct.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChildControl.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildControl.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\ChildWin.h
# End Source File
# Begin Source File

SOURCE=.\Commander.cpp
# End Source File
# Begin Source File

SOURCE=.\Commander.h
# End Source File
# Begin Source File

SOURCE=.\ContextCommander.cpp
# End Source File
# Begin Source File

SOURCE=.\ContextCommander.h
# End Source File
# Begin Source File

SOURCE=.\ContextMenuTable.h
# End Source File
# Begin Source File

SOURCE=.\Control.cpp
# End Source File
# Begin Source File

SOURCE=.\Control.h
# End Source File
# Begin Source File

SOURCE=.\DisplayDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DisplayDlg.h
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuTable.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuTable.h
# End Source File
# Begin Source File

SOURCE=.\NewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NewDlg.h
# End Source File
# Begin Source File

SOURCE=.\Params.h
# End Source File
# Begin Source File

SOURCE=.\RemoveDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RemoveDlg.h
# End Source File
# Begin Source File

SOURCE=.\SearchDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchDlg.h
# End Source File
# Begin Source File

SOURCE=.\Status.cpp
# End Source File
# Begin Source File

SOURCE=.\status.h
# End Source File
# Begin Source File

SOURCE=.\View.cpp
# End Source File
# Begin Source File

SOURCE=.\View.h
# End Source File
# End Target
# End Project
