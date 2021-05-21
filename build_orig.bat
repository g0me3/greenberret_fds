@echo off

cd nas

echo assemble...

rem to generate lst and err filrs
dasm FC_MAIN.nas -f3 -l!FC_MAIN.lst -oFC_MAIN.bin >> !err.log
rem to draw dasm output
dasm FC_MAIN.nas -f3 -oFC_MAIN.bin

for %%f in (*.nas) do call :dodasm %%f > NUL

goto :build

:dodasm
dasm %1 -f3 -o%~n1.bin
goto :eof

:build
echo build...

cd ..

echo done.
