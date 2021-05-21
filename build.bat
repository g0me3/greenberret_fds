@echo off

cd nas

echo assemble...

rem to draw dasm output
dasm bank0.nas -f3 -obank0.bin
rem to generate lst and err filrs
dasm bank1.nas -f3 -l!bank1.lst -obank1.bin >> !err.log

call :dodasm bank2.nas > NUL
call :dodasm bank3.nas > NUL
call :dodasm bank4.nas > NUL
call :dodasm bank5.nas > NUL
call :dodasm bank6.nas > NUL
call :dodasm bank7.nas > NUL
call :dodasm hdr.nas > NUL

goto :build

:dodasm
dasm %1 -f3 -o%~n1.bin
goto :eof

dasm hdr.nas -f3 -ohdr.bin > NUL

:build
echo build...

rename hdr.bin !greenb.hdr > NUL
copy /b bank0.bin+bank1.bin+bank2.bin+bank3.bin+bank4.bin+bank5.bin+bank6.bin+bank7.bin !greenb.prg > NUL
nesimage j !greenb > NUL

echo cleanup...
for %%f in (*.bin) do del %%f > NUL
del !greenb.hdr > NUL
del !greenb.prg > NUL

copy /b !greenb.nes ..\!greenb.nes > NUL

del !greenb.nes > NUL

cd ..

echo done.
