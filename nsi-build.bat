@echo off

set ProjectPath=%~dp0
set NsisPath=%ProjectPath%\..\NSIS
set NsisCompiler=%NsisPath%\Bin\makensis.exe

echo %ProjectPath%

REM 判断dll是否编译完成
if not exist %ProjectPath%\build\bin\Release\NsisPluginsDemo.dll echo [error] %ProjectPath%\build\Release\NsisPluginsDemo.dll not find. && exit /b 1

REM 拷贝dll文件到NSIS编译器插件库
copy /y %ProjectPath%\build\bin\Release\NsisPluginsDemo.dll %NsisPath%\Plugins\x86-unicode

REM 开始编译
%NsisCompiler% %ProjectPath%\nsi\main.nsi


pause