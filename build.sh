cd nas

echo assemble...

for f in *.nas; do ./dasm $f -f3 -o"${f%.nas}.bin"; done

echo build...

mv hdr.bin !greenb.hdr

cat bank0.bin bank1.bin bank2.bin bank3.bin bank4.bin bank5.bin bank6.bin bank7.bin > !greenb.prg
cat !greenb.hdr !greenb.prg > !greenb.nes

echo cleanup...

rm *.bin
rm !greenb.hdr !greenb.prg

cp !greenb.nes ../!greenb.nes

rm !greenb.nes

cd ..

echo done.
