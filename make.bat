@echo off

start "" "D:\work\tools\TextPad\TextPad.exe" "ram.inc" "macroses.inc" "bank0.inc" "bank1.inc" "bank2.inc" "bank3.inc" "bank4.inc" "bank5.inc" "bank6.inc" "bank7.inc"

pause 0

:again

call build.bat

pause 0

goto :again

:eof
