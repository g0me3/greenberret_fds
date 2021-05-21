		ORG $6000
byte_16000:
		.BYTE $E2,$07,$01,$51,$85,$05,$0B,$E3,$FF
byte_16009:
		.BYTE $E2,$87,$81,$E1,$01,$55,$E2,$85,$FF
byte_16012:
		.BYTE $D4,$75,$27,$E3,$85,$A5,$E2,$05,$E3,$A5,$D4,$74,$24,$E2,$81,$71
		.BYTE $85,$A1,$E1,$01,$FF
byte_16027:
		.BYTE $E3,$81,$E2,$31,$51,$71,$51,$31,$E3,$81,$E2,$01,$E3,$81,$E2,$C5
		.BYTE $51,$81,$E1,$01,$11,$01,$E2,$A1,$81,$A1,$81,$71,$31,$FF
byte_16045:
		.BYTE $01,$21,$31,$51,$31,$21,$01,$FF
byte_1604D:
		.BYTE $01,$31,$01,$01,$01,$21,$31,$51,$31,$21,$01,$FF
byte_16059:
		.BYTE $E2,$05,$25,$35,$25,$D4,$74,$24,$E1,$01,$E2,$A1,$E1,$05,$21,$31
		.BYTE $FF
byte_1606A:
		.BYTE $55,$35,$25,$05,$D4,$74,$22,$FF
byte_16072:
		.BYTE $51,$71,$81,$A1,$81,$71,$51,$31,$51,$C5,$81,$E1,$01,$31,$51,$31
		.BYTE $11,$01,$11,$01,$E2,$A1,$71,$FF
byte_1608A:
		.BYTE $E2,$EA,$51,$EA,$81,$E1,$EA,$01,$E2,$E9,$51,$EA,$81,$E1,$EA,$01
		.BYTE $FF
byte_1609B:
		.BYTE $E2,$E9,$81,$E9,$81,$E9,$81,$E9,$01,$E9,$01,$E9,$01,$FF
byte_160A9:
		.BYTE $EA,$51,$EA,$51,$EA,$51,$E9,$51,$EA,$51,$EA,$51,$FF
byte_160B6:
		.BYTE $EA,$11,$EA,$11,$EA,$11,$E9,$11,$EA,$11,$EA,$11,$FF
byte_160C3:
		.BYTE $EA,$31,$EA,$31,$EA,$31,$E9,$31,$EA,$31,$EA,$31,$FF
byte_160D0:
		.BYTE $E2,$EA,$81,$EA,$81,$EA,$81,$E9,$81,$EA,$81,$EA,$81,$E9,$31,$E9
		.BYTE $31,$E9,$31,$E9,$31,$E9,$31,$E9,$31,$FF
byte_160EA:
		.BYTE $E3,$EA,$A1,$E2,$EA,$21,$EA,$51,$E3,$E9,$A1,$E2,$EA,$21,$EA,$51
		.BYTE $E3,$EA,$A1,$E2
		.BYTE $FF
_apu2C:
		.BYTE $D4,$35,$44,$E3,$81,$A1,$E2,$01,$21,$01,$E3,$A1,$81,$71,$81,$E2
		.BYTE $01,$E3,$81,$81,$81,$A1,$E2,$01,$21,$01,$E3,$A1,$81,$71,$81,$81
		.BYTE $A1,$E2,$01,$81,$A1,$E1,$01,$21,$01,$E2,$A1,$81,$71,$81,$E1,$01
		.BYTE $E2,$81,$81,$81,$A1,$E1,$01,$21,$01,$E2,$A1,$81,$71,$81,$E1,$01
		.BYTE $21,$31
_apu2F:
		.BYTE $E8,$D4,$B4,$32
		.BYTE $FD
		.WORD byte_16000
		.BYTE $A5,$E2,$35
		.BYTE $FD
		.WORD byte_16000
		.BYTE $AB,$D4,$74,$23
		.BYTE $FD
		.WORD byte_16009
		.BYTE $8B,$75,$A5
		.BYTE $FD
		.WORD byte_16009
		.BYTE $E1,$1B,$3B
		.BYTE $FD
		.WORD byte_16012
		.BYTE $E2,$A1,$85,$71
		.BYTE $FD
		.WORD byte_16012
		.BYTE $21,$35,$01,$D4,$75,$37,$E2,$25,$05,$E3,$A5,$85,$D4,$74,$22,$E2
		.BYTE $01,$E3,$C1,$A1,$A7,$D4,$B3,$22,$E3,$A1,$E2,$21,$E3,$A1,$E2,$21
		.BYTE $51,$D4,$75,$37,$E1,$25,$05,$E2,$A5,$85,$D4,$74,$22,$E1,$31,$C1
		.BYTE $21,$29,$C7
byte_1619B:
		.BYTE $D4,$B5,$23,$E3,$55,$51,$81,$E2,$01,$E3,$55,$51,$81,$E2,$01,$3B
		.BYTE $05,$E3,$35
		.WORD $02FE
		.WORD byte_1619B
		.BYTE $D4,$75,$44
		.BYTE $FD
		.WORD byte_16027
		.BYTE $01
		.BYTE $FD
		.WORD byte_16027
		.BYTE $71
		.WORD $FFFE
		.WORD _apu2F
_apu2D:
		.BYTE $D4,$35,$44,$E2
		.BYTE $FD
		.WORD byte_16045
		.BYTE $E3,$A1,$E2
		.BYTE $FD
		.WORD byte_1604D
		.BYTE $E3,$A1,$E2,$01,$01,$21,$31,$E1
		.BYTE $FD
		.WORD byte_16045
		.BYTE $E2,$A1,$E1
		.BYTE $FD
		.WORD byte_1604D
		.BYTE $E2,$A1,$E1,$01,$31,$51,$71
_apu30:
		.BYTE $D4,$B5,$33
		.BYTE $FD
		.WORD byte_16000
		.BYTE $A5,$E2,$35
		.BYTE $FD
		.WORD byte_16000
		.BYTE $AB,$D4,$74,$23,$E1,$07,$01,$51,$85,$05,$0B,$E2,$A5,$E1,$35,$07
		.BYTE $01,$51,$85,$05,$5B,$7B,$D4,$75,$27
		.BYTE $FD
		.WORD byte_16059
		.BYTE $21,$05,$E2,$A1,$D4,$75,$27
		.BYTE $FD
		.WORD byte_16059
		.BYTE $51,$75,$31,$D4,$75,$37,$E2
		.BYTE $FD
		.WORD byte_1606A
		.BYTE $31,$C1,$21,$27,$D4,$B3,$22,$21,$51,$21,$51,$A1,$D4,$75,$37,$E1
		.BYTE $FD
		.WORD byte_1606A
		.BYTE $71,$C1,$51,$59,$C7
byte_1623A:
		.BYTE $D4,$B5,$23,$E3,$55,$51,$81,$E2,$01,$E3,$55,$51,$81,$E2,$01,$3B
		.BYTE $05,$E3,$35
		.WORD $02FE
		.WORD byte_1623A
		.BYTE $D4,$75,$44,$E2
		.BYTE $FD
		.WORD byte_16072
		.BYTE $31
		.BYTE $FD
		.WORD byte_16072
		.BYTE $A1
		.WORD $FFFE
		.WORD _apu30
_apu2E:
		.BYTE $D4,$10,$E2
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_1609B
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_1609B
_apu31:
		.BYTE $D4,$10,$E2
		.BYTE $FD
		.WORD byte_160A9
		.BYTE $FD
		.WORD byte_160A9
		.BYTE $FD
		.WORD byte_160B6
		.BYTE $FD
		.WORD byte_160C3
		.BYTE $FD
		.WORD byte_160A9
		.BYTE $FD
		.WORD byte_160A9
		.BYTE $FD
		.WORD byte_160B6
		.BYTE $FD
		.WORD byte_160C3
		.BYTE $FD
		.WORD byte_160A9
		.BYTE $FD
		.WORD byte_160A9
		.BYTE $FD
		.WORD byte_160B6
		.BYTE $FD
		.WORD byte_160C3
		.BYTE $FD
		.WORD byte_160A9
		.BYTE $FD
		.WORD byte_160A9
		.BYTE $EA,$11,$EA,$51,$EA,$81,$E9,$11,$EA,$51,$EA,$81,$EA,$31,$E9,$71
		.BYTE $E9,$A1,$E9,$31,$E9,$71,$E9,$A1
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_160D0
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_160D0
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_160EA
		.BYTE $EA,$21,$EA,$51,$E3,$E9,$A1,$E2,$EA,$21,$EA,$51
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_1608A
		.BYTE $FD
		.WORD byte_160EA
		.BYTE $E9,$21,$E9,$51,$E3,$E9,$A1,$E2,$E9,$21,$E9,$51
byte_162FD:
		.BYTE $D4,$03,$E1,$EA,$01,$EA,$51,$EA,$81,$E9,$01,$EA,$51,$EA,$81,$EA
		.BYTE $01,$EA,$51,$EA,$81,$E9,$01,$EA,$51,$EA,$81,$EA,$01,$EA,$31,$EA
		.BYTE $81,$E9,$01,$EA,$31,$EA,$81,$E9,$31,$E9,$71,$E9,$A1,$E9,$31,$EA
		.BYTE $71,$EA,$A1
		.WORD $02FE
		.WORD byte_162FD
byte_16334:
		.BYTE $D4,$10,$E2,$EA,$51,$EA,$51,$EA,$51,$E9,$51,$EA,$51,$EA,$51,$E2
		.BYTE $EA,$51,$EA,$51,$EA,$51,$E9,$51,$EA,$51,$EA,$51,$EA,$81,$EA,$81
		.BYTE $EA,$81,$E9,$81,$EA,$81,$EA,$81,$E9,$31,$E9,$31,$E9,$31,$E9,$31
		.BYTE $E9,$31,$E9,$31
		.WORD $02FE
		.WORD byte_16334
		.WORD $FFFE
		.WORD _apu31
_apu55:
		.BYTE $D5,$B5,$29,$C4,$E1,$43,$43,$D5,$B5,$22,$75,$D5,$B5,$25,$50,$70
		.BYTE $D5,$B5,$22,$91,$71,$51,$41,$53,$23,$D5,$B5,$27,$E2,$93,$92,$90
		.BYTE $D5,$B5,$22,$E1,$51,$41,$21,$01,$77,$D5,$B6,$42,$23,$D5,$B5,$26
		.BYTE $E2,$B2,$B0,$D5,$B5,$22,$E2,$91,$E1,$01,$51,$01,$E2,$B1,$E1,$21
		.BYTE $71,$21,$D5,$B4,$24,$4F,$FF
_apu56:
		.BYTE $D5,$B5,$29,$C4,$E1,$03,$03,$D5,$B5,$22,$45,$D5,$B5,$24,$20,$40
		.BYTE $D5,$B5,$22,$51,$41,$21,$01,$23,$E2,$73,$D5,$B5,$26,$53,$52,$50
		.BYTE $D5,$B5,$22,$E1,$21,$01,$E2,$B1,$91,$E1,$27,$D5,$B6,$42,$E2,$B3
		.BYTE $D5,$B5,$26,$72,$70,$D5,$B5,$22,$51,$91,$E1,$01,$E2,$91,$71,$B1
		.BYTE $E1,$21,$E2,$B1,$D5,$B6,$24,$E1,$0F,$FF
_apu57:
		.BYTE $D5,$40,$C4,$E2,$E9,$03,$E3,$E9,$73,$E2,$E9,$01,$EA,$00,$EA,$00
		.BYTE $E3,$EA,$71,$EA,$71,$E2,$E9,$03,$E3,$E9,$73,$E2,$E9,$21,$EA,$20
		.BYTE $EA,$20,$E3,$E9,$71,$EA,$71,$E2,$E9,$53,$E9,$03,$E9,$51,$EA,$50
		.BYTE $EA,$50,$EA,$61,$EA,$61,$E9,$73,$E9,$23,$E9,$71,$EA,$70,$EA,$70
		.BYTE $E3,$EA,$71,$EA,$71,$E9,$51,$EA,$50,$EA,$50,$EA,$53,$E9,$71,$EA
		.BYTE $70,$EA,$70,$EA,$73,$D5,$50,$E2,$E9,$03,$E3,$E9,$71,$E9,$70,$E9
		.BYTE $70,$D5,$90,$E2,$E9,$06,$FF
_apu5B:
		.BYTE $D6,$B7,$60,$C4,$D8,$B7,$60,$E2,$71,$D8,$B5,$24,$70,$E1,$03,$E2
		.BYTE $70,$E1,$00,$40,$00,$40,$72,$42,$D8,$B7,$60,$41,$D8,$B5,$24,$40
		.BYTE $52,$D8,$B7,$60,$01,$D8,$B5,$24,$00,$D8,$B5,$22,$50,$40,$20,$02
		.BYTE $E2,$B2,$D8,$B5,$24,$70,$70,$70,$E1,$02,$D8,$B7,$60,$E2,$71,$D8
		.BYTE $B5,$24,$E1,$00,$D8,$B5,$22,$40,$20,$00,$72,$42,$D8,$B7,$60,$51
		.BYTE $D8,$B5,$25,$50,$72,$D8,$B7,$60,$E2,$71,$D8,$B5,$24,$E1,$20,$70
		.BYTE $70,$70,$07,$FF
_apu5C:
		.BYTE $D6,$B7,$60,$C4,$D8,$B7,$60,$E2,$21,$D8,$B5,$24,$20,$73,$00,$70
		.BYTE $E1,$00,$E2,$70,$E1,$00,$02,$E2,$72,$D8,$B7,$60,$E1,$01,$D8,$B5
		.BYTE $24,$00,$E2,$92,$D8,$B7,$60,$51,$D8,$B5,$24,$50,$D8,$B5,$22,$E1
		.BYTE $20,$00,$E2,$B0,$92,$72,$D8,$B5,$24,$20,$20,$20,$72,$D8,$B7,$60
		.BYTE $01,$D8,$B5,$24,$70,$D8,$B5,$22,$E1,$00,$E2,$B0,$90,$E1,$42,$E1
		.BYTE $02,$D8,$B7,$60,$E2,$91,$D8,$B5,$25,$90,$E1,$22,$D8,$B7,$60,$E2
		.BYTE $21,$D8,$B5,$24,$70,$B0,$B0,$B0,$47,$FF
_apu5D:
		.BYTE $D6,$50,$C4,$D8,$50,$E2,$E9,$C0,$E9,$C0,$E9,$C0,$E9,$02,$D8,$10
		.BYTE $EA,$00,$EA,$00,$EA,$00,$D8,$50,$EA,$02,$E9,$02,$EA,$02,$E3,$EA
		.BYTE $92,$E9,$52,$EA,$52,$EA,$62,$D8,$18,$E9,$71,$EA,$20,$D8,$50,$E9
		.BYTE $72,$E9,$B2,$E2,$E9,$02,$D8,$10,$EA,$00,$EA,$00,$EA,$00,$D8,$50
		.BYTE $EA,$02,$E9,$02,$EA,$02,$E3,$EA,$52,$E9,$72,$E9,$C1,$E9,$C0,$E9
		.BYTE $70,$E9,$C0,$E9,$C0,$E2,$E9,$01,$E3,$E9,$70,$D8,$90,$E2,$E9,$04
		.BYTE $FF
_apu62:
		.BYTE $D2,$B7,$26,$E2,$CE,$77,$43,$D6,$B7,$26,$03,$43,$73,$E1,$07,$D2
		.BYTE $B7,$26,$47,$23,$D6,$B7,$26,$03,$E2,$43,$63,$77,$D2,$B7,$26,$77
		.BYTE $73,$D6,$B7,$26,$E1,$45,$21,$03,$E2,$B7,$D2,$B7,$26,$97,$B3,$D6
		.BYTE $B7,$26,$E1,$03,$03,$E2,$73,$43,$07,$FF
_apu61:
		.BYTE $D2,$B7,$26,$E3,$CE,$77,$43,$D6,$F6,$25,$73,$E2,$03,$23,$47,$73
		.BYTE $43,$03,$23,$E3,$B7,$D2,$B6,$25,$E3,$77,$73,$D6,$F6,$25,$E2,$75
		.BYTE $71,$43,$77,$D2,$F6,$25,$57,$73,$D6,$F6,$25,$43,$73,$43,$D6,$B6
		.BYTE $26,$E3,$73,$47,$FF
_apu63:
		.BYTE $D6,$33,$E3,$C4,$C3,$E2,$03,$03,$E3,$B3,$D6,$66,$97,$D6,$33,$43
		.BYTE $93,$93,$E2,$23,$E3,$73,$E2,$53,$D2,$24,$47,$23,$D6,$33,$03,$03
		.BYTE $E3,$93,$73,$73,$E2,$53,$03,$43,$03,$E3,$73,$D6,$99,$E2,$07,$FF
_apu03:
		.BYTE $21,$B0,$10,$82,$50,$90,$80,$98,$B0,$A1,$90,$B3,$70,$C6,$60,$DA
		.BYTE $50,$EE,$51,$04,$41,$04,$41,$1B,$31,$33,$31,$4C
		.WORD $03FE
		.WORD _apu03
		.BYTE $FF
_apu53:
		.BYTE $D2,$10,$EB,$C8,$EB,$C5,$EB,$C4,$EB,$C5,$EB,$C4,$EB,$C9,$EB,$C5
		.BYTE $EB,$C4,$EB,$C6,$EB,$C5,$EB,$C6,$EB,$C4,$EB,$C7
		.WORD $02FE
		.WORD _apu53
		.BYTE $FF
_apu54:
		.BYTE $D2,$10,$EB,$C2,$EB,$C7,$EB,$C2,$EB,$C5,$EB,$C4,$EB,$C6,$EB,$C7
		.BYTE $EB,$C3,$EB,$C3,$EB,$C6,$EB,$C4,$EB,$C5,$EB,$C3,$EB,$C5,$EB,$C0
		.WORD $02FE
		.WORD _apu54
		.BYTE $FF
