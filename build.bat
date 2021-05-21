@echo off

cd nas

echo assemble...

rem to generate lst and err filrs
dasm bank0.nas -f3 -l!bank0.lst -obank0.bin >> !err.log
rem to draw dasm output
dasm bank1.nas -f3 -obank1.bin

for %%f in (*.nas) do call :dodasm %%f > NUL

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
