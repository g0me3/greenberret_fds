@echo off

start "" "D:\work\tools\TextPad\TextPad.exe" "F:\nes\fds\green_beret_fds\ram.inc" "F:\nes\fds\green_beret_fds\macroses.inc" "F:\nes\fds\green_beret_fds\bank0.inc" "F:\nes\fds\green_beret_fds\bank1.inc" "F:\nes\fds\green_beret_fds\bank2.inc" "F:\nes\fds\green_beret_fds\bank3.inc" "F:\nes\fds\green_beret_fds\bank4.inc" "F:\nes\fds\green_beret_fds\bank5.inc" "F:\nes\fds\green_beret_fds\bank6.inc" "F:\nes\fds\green_beret_fds\bank7.inc" "F:\nes\fds\green_beret_fds\FC_4.inc" "F:\nes\fds\green_beret_fds\FC_5.inc" "F:\nes\fds\green_beret_fds\FC_6.inc" "F:\nes\fds\green_beret_fds\FC_E.inc" "F:\nes\fds\green_beret_fds\FC_MAIN.inc" "F:\nes\fds\green_beret_fds\FC_S.inc" "F:\nes\fds\green_beret_fds\PO_COME.inc" "F:\nes\fds\green_beret_fds\PO1D.inc" "F:\nes\fds\green_beret_fds\PO2D.inc" "F:\nes\fds\green_beret_fds\PO3D.inc" "F:\nes\fds\green_beret_fds\PO4D.inc" "F:\nes\fds\green_beret_fds\PO5D.inc" "F:\nes\fds\green_beret_fds\PO6D.inc" "F:\nes\fds\green_beret_fds\POED1.inc" "F:\nes\fds\green_beret_fds\POPD.inc" "F:\nes\fds\green_beret_fds\PTCD.inc" "F:\nes\fds\green_beret_fds\BGM1.inc" "F:\nes\fds\green_beret_fds\BGM2.inc" "F:\nes\fds\green_beret_fds\BIOS.inc" "F:\nes\fds\green_beret_fds\FC_1.inc" "F:\nes\fds\green_beret_fds\FC_2.inc" "F:\nes\fds\green_beret_fds\FC_3.inc"

pause 0

:again

call build.bat

pause 0

goto :again

:eof
