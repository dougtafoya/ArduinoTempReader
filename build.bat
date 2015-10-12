@echo off
cls

if not defined frameworkdir (echo VCVARSALL not loaded, loading...& set compilerset=1&set compilerv=x64&call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall".bat x64)

setlocal

set builddir=debug_x64
if not exist %builddir% (echo Build directory: %builddir% does not exist, creating&mkdir %builddir%)


set CompilerFlags= -MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -wd4702 -wd4127 -FC -Z7
set LinkerFlags= -SUBSYSTEM:CONSOLE -incremental:no -opt:ref User32.lib Shell32.lib 


echo.
echo BUILDING ArduinoReader\%builddir%
echo ----------------------------------
pushd %builddir%

cl %CompilerFlags% ..\src\ArduinoReader.cpp ..\src\ArduinoSerial.cpp -FmArduinoReader.map /link %LinkerFlags%

echo ----------------------------------
echo COMPILING FINISHED AT %date% %time%
popd

:ending
endlocal
