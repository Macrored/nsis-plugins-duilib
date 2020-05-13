Unicode true
RequestExecutionLevel user 

!include "LogicLib.nsh"

Page custom MainGui
Page instfiles

Var Count1
Var Count2
Var Count3

Function "MainGui"
    LogSet on
    StrCpy $INSTDIR $EXEDIR
    InitPluginsDir
    SetOutPath $PLUGINSDIR
    File "..\build\bin\Release\duilib.dll"
    File "360SafeRes.zip"

    NsisPluginsDemo::Frame360
    # your code here
    Quit
FunctionEnd

# Ê×ÒªÇø¶Î
Section "MainSlient"
    LogSet on
    StrCpy $INSTDIR $EXEDIR
    InitPluginsDir
    SetOutPath $PLUGINSDIR
    File "360SafeRes.zip"
    MessageBox MB_OK "PLUGINSDIR:$PLUGINSDIR" 

    Intop $Count1 0 + 0
    Intop $Count2 0 + 0
    Intop $Count3 0 + 0

    GetFunctionAddress $R0 BgWorkTest1
    GetFunctionAddress $R1 BgWorkTest2
    GetFunctionAddress $R2 BgWorkTest3
    MessageBox MB_OK "BgWorkTest addr: $R0"
    NsisPluginsDemo::Exec

    MessageBox MB_OK "Count1:$Count1"
    MessageBox MB_OK "Count1:$Count2"
    MessageBox MB_OK "Count1:$Count3"

    NsisPluginsDemo::Frame360
    Quit
SectionEnd

Function BgWorkTest1
    ${While} $Count1 < 50
        Intop $Count1 $Count1 + 1
    ${EndWhile}
FunctionEnd

Function BgWorkTest2
    ${While} $Count2 < 60
        Intop $Count2 $Count2 + 1
    ${EndWhile}
FunctionEnd

Function BgWorkTest3
    ${While} $Count3 < 70
        Intop $Count3 $Count3 + 1
    ${EndWhile}
FunctionEnd