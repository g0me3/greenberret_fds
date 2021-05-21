
		ORG $8000

		BANK_START $06

		SECTION_START
		FAR_PTR _ending_data
		INCLUDE "..\FC_E.inc"
		SECTION_END "ENDING data (FC_E)"

		SECTION_START
		FAR_PTR _title_data
		INCLUDE "..\FC_S.inc"
		SECTION_END "TITLE data (FC_S)"

		SECTION_START
_screen_lib0_blank:
		.WORD _scr0_01
		.WORD _scr0_01
		.WORD _scr0_23
		.WORD _scr0_23
_scr0_01:
		.BYTE $34,$C0,$00,$34,$C0,$00,$34,$C0,$00,$34,$E0,$00,$34,$E0,$00
_scr0_23:
		.BYTE $39
_screen_lib4_regular_stage_complete:
		.WORD _scr4_0
		.WORD _scr4_1
		.WORD _scr4_2
		.WORD _scr4_3
_scr4_0:
		.BYTE $34,$80,$00,$34,$C0,$00,$30,$34,$07,$31,$34,$18,$00,$40,$00,$32
		.BYTE $33,$27,$35,$36,$34,$1A,$00,$41,$42,$43,$44,$45,$46,$34,$14,$00
		.BYTE $4F,$34,$04,$00,$50,$34,$07,$51,$34,$12,$00,$5C,$5F,$34,$04,$00
		.BYTE $30,$34,$07,$31,$34,$11,$00,$5C,$4E,$6F,$34,$04,$00,$39
_scr4_1:
		.BYTE $40,$00,$32,$00,$00,$00,$32,$34,$0B,$00,$2E,$2F,$34,$04,$00,$5C
		.BYTE $4E,$5E,$6F,$34,$05,$00,$41,$42,$52,$53,$54,$42,$34,$0B,$00,$3E
		.BYTE $3F,$00,$00,$00,$5F,$4E,$4C,$4C,$6F,$34,$05,$00,$41,$42,$62,$63
		.BYTE $64,$42,$34,$04,$00,$37,$38,$38,$28,$28,$38,$38,$38,$28,$38,$28
		.BYTE $5C,$6C,$5E,$5E,$5E,$6F,$34,$05,$00,$41,$42,$52,$53,$54,$42,$34
		.BYTE $04,$00,$47,$34,$09,$48,$3B,$4E,$6C,$4C,$4C,$4C,$6F,$34,$05,$00
		.BYTE $41,$42,$62,$63,$64,$42,$34,$04,$00,$57,$34,$04,$58,$2A,$2A,$58
		.BYTE $59,$58,$5A,$5E,$6C,$5E,$5E,$5E,$6F,$34,$05,$00,$41,$42,$52,$53
		.BYTE $54,$42,$00,$55,$56,$55,$56,$58,$58,$2B,$2B,$67,$68,$69,$5A,$78
		.BYTE $5A,$4C,$6C,$4C,$4C,$4C,$6F,$34,$05,$00,$61,$42,$62,$63,$64,$42
		.BYTE $00,$65,$66,$65,$66,$58,$58,$2B,$2B,$77,$00,$79,$58,$58,$5A,$5E
		.BYTE $6C,$5E,$5E,$5E,$6F,$34,$05,$00,$39
_scr4_2:
		.BYTE $61,$42,$00,$00,$61,$42,$00,$65,$66,$65,$66,$58,$49,$58,$58,$77
		.BYTE $00,$55,$56,$55,$56,$4C,$6C,$4C,$4C,$4C,$6F,$6A,$3C,$6A,$3D,$29
		.BYTE $60,$42,$29,$29,$60,$42,$29,$75,$76,$75,$76,$4D,$58,$58,$4A,$77
		.BYTE $00,$65,$66,$65,$66,$6D,$6C,$6D,$6D,$6D,$6F,$4B,$4B,$5B,$4B,$29
		.BYTE $70,$71,$29,$29,$70,$71,$34,$05,$29,$34,$04,$3A,$29,$29,$65,$66
		.BYTE $65,$66,$6D,$6C,$6D,$6D,$6D,$6F,$4D,$4B,$4B,$5B,$34,$12,$29,$75
		.BYTE $76,$75,$76,$6E,$6C,$6D,$6D,$6D,$6F,$29,$4D,$4B,$4B,$34,$16,$29
		.BYTE $70,$71,$5D,$6E,$6E,$6F,$29,$29,$4D,$4B,$34,$1A,$29,$5D,$6F,$29
		.BYTE $29,$29,$4D,$39
_scr4_3:
		.BYTE $34,$34,$23,$C8,$34,$08,$00,$50,$5C,$34,$06,$00,$55,$55,$00,$00
		.BYTE $40,$00,$54,$00,$55,$55,$44,$34,$04,$55,$00,$55,$55,$AA,$51,$95
		.BYTE $65,$55,$50,$34,$04,$55,$59,$56,$55,$55,$39
		SECTION_END "EXTRA"

		SECTION_START
; =============== S U B	R O U T	I N E =======================================
_spr_insert:
		LDY		#$00
		LDA		(byte_8),Y
		BNE		loc_9B45
		RTS
; ---------------------------------------------------------------------------
loc_9B45:
		STA		byte_3
		INY
		LDA		(byte_8),Y
		STA		byte_7
		INY
		LDA		(byte_8),Y
		STA		byte_F
		INY
		LDX		word_4
loc_9B54:
		LDA		(byte_8),Y
		CLC
		ADC		word_0+1
		CLC
		ADC		byte_F
		ADC		#$0A
		STA		_spr_buf,X
		INY
		LDA		byte_14
		BNE		loc_9B7E
		LDA		_1p_stage
		CMP		#$04
		BNE		loc_9B7E
		LDA		(byte_8),Y
		CMP		#$53
		BEQ		loc_9BDA
		CMP		#$55
		BEQ		loc_9BDE
		CMP		#$0E
		BCS		loc_9B7E
		CMP		#$03
		BCS		loc_9BE2
loc_9B7E:
		LDA		(byte_8),Y
loc_9B80:
		STA		_spr_buf+1,X
		INY
		STX		byte_E
		LDX		word_4+1
		LDA		byte_300,X
		LDX		byte_E
		CMP		#$06
		BEQ		loc_9B99
		CMP		#$07
		BEQ		loc_9B99
		LDA		byte_6
		BNE		loc_9BEF
loc_9B99:
		LDA		(byte_8),Y
loc_9B9B:
		ORA		word_0
		STA		_spr_buf+2,X
		INY
		STX		byte_E
		LDX		word_4+1
		LDA		byte_300,X
		LDX		byte_E
		CMP		#$06
		BEQ		loc_9BB6
		CMP		#$07
		BEQ		loc_9BB6
		LDA		byte_6
		BNE		loc_9BF6
loc_9BB6:
		LDA		(byte_8),Y
loc_9BB8:
		CLC
		ADC		byte_2
		STA		_spr_buf+3,X
		CMP		#$10
		BCS		loc_9BC6
		LDA		byte_2
		BMI		locret_9BD6
loc_9BC6:
		DEC		byte_10
		BEQ		loc_9BEC
		INY
		TXA
		CLC
		ADC		#$C4
		TAX
		DEC		byte_3
		BNE		loc_9BD7
		STX		word_4
locret_9BD6:
		RTS
; ---------------------------------------------------------------------------
loc_9BD7:
		JMP		loc_9B54
; ---------------------------------------------------------------------------
loc_9BDA:
		LDA		#$F1
		BNE		loc_9B80
loc_9BDE:
		LDA		#$F3
		BNE		loc_9B80
loc_9BE2:
		STA		byte_16
		LDA		#$E2
		CLC
		ADC		byte_16
		JMP		loc_9B80
; ---------------------------------------------------------------------------
loc_9BEC:
		PLA
		PLA
		RTS
; ---------------------------------------------------------------------------
loc_9BEF:
		LDA		(byte_8),Y
		EOR		#$40
		JMP		loc_9B9B
; ---------------------------------------------------------------------------
loc_9BF6:
		LDA		(byte_8),Y
		EOR		#$FF
		CLC
		ADC		#$01
		CLC
		ADC		byte_7
		JMP		loc_9BB8

; =============== S U B	R O U T	I N E =======================================
_sprite_manager:
		LDA		#$40
		STA		byte_10
		LDA		#$00
		STA		word_4+1
		LDA		byte_59
		CLC
		ADC		#$44
		STA		byte_59
		STA		word_4
loc_9C14:
		LDX		word_4+1
		CPX		#$10
		BCS		loc_9C86
		LDA		#$00
		STA		byte_14
		CPX		#$02
		BCS		loc_9C26
		LDA		#$01
		STA		byte_14
loc_9C26:
		LDA		byte_310,X
		STA		word_0
		LDA		byte_320,X
		STA		word_0+1
		LDA		byte_330,X
		STA		byte_2
		LDA		byte_340,X
		STA		byte_6
		LDA		byte_300,X
		CMP		#$3E
		BCS		loc_9C49
		CMP		#$3A
		BCC		loc_9C49
		LDA		#$01
		STA		byte_14
loc_9C49:
		LDA		byte_300,X
		CMP		#$34
		BEQ		loc_9C54
		CMP		#$35
		BNE		loc_9C71
loc_9C54:
		LDA		_1p_stage
		BEQ		loc_9C6E
		CMP		#$04
		BEQ		loc_9C65
		LDA		byte_300,X
		CLC
		ADC		#$0F
		JMP		loc_9C71
; ---------------------------------------------------------------------------
loc_9C65:
		LDA		byte_300,X
		CLC
		ADC		#$6F
		JMP		loc_9C71
; ---------------------------------------------------------------------------
loc_9C6E:
		LDA		byte_300,X
loc_9C71:
		ASL
		TAY
		BCS		loc_9C97
		LDA		_spr_libA,Y
		STA		byte_8
		LDA		_spr_libA+1,Y
loc_9C7D:
		STA		byte_9
		JSR		_spr_insert
		INC		word_4+1
		BNE		loc_9C14
loc_9C86:
		LDX		word_4
loc_9C88:
		LDA		#$F4
		STA		_spr_buf,X
		TXA
		CLC
		ADC		#$C4
		TAX
		DEC		byte_10
		BNE		loc_9C88
		RTS
; ---------------------------------------------------------------------------
loc_9C97:
		LDA		_spr_libB,Y
		STA		byte_8
		LDA		_spr_libB+1,Y
		JMP		loc_9C7D
; ---------------------------------------------------------------------------
_spr_libA:
		.WORD _spr00_dummy
		.WORD _spr01
		.WORD _spr02
		.WORD _spr03
		.WORD _spr02
		.WORD _spr05
		.WORD _spr06
		.WORD _spr07
		.WORD _spr02
		.WORD _spr08
		.WORD _spr09
		.WORD _spr05
		.WORD _spr0B
		.WORD _spr0C
		.WORD _spr0D
		.WORD _spr0E
		.WORD _spr0F
		.WORD _spr10
		.WORD _spr0F
		.WORD _spr12
		.WORD _spr13
		.WORD _spr00_dummy
		.WORD _spr15
		.WORD _spr16
		.WORD _spr17
		.WORD _spr16
		.WORD _spr19
		.WORD _spr1A
		.WORD _spr1B
		.WORD _spr1C
		.WORD _spr1D
		.WORD _spr00_dummy
		.WORD _spr1F
		.WORD _spr20
		.WORD _spr21
		.WORD _spr20
		.WORD _spr23
		.WORD _spr24
		.WORD _spr25
		.WORD _spr26
		.WORD _spr25
		.WORD _spr28
		.WORD _spr29
		.WORD _spr2A
		.WORD _spr2B
		.WORD _spr2C
		.WORD _spr2D
		.WORD _spr2E
		.WORD _spr2F
		.WORD _spr30
		.WORD _spr2F
		.WORD _spr32
		.WORD _spr33
		.WORD _spr34
		.WORD _spr35
		.WORD _spr36
		.WORD _spr37
		.WORD _spr38
		.WORD _spr01
		.WORD _spr02
		.WORD _spr03
		.WORD _spr02
		.WORD _spr3D
		.WORD _spr3E
		.WORD _spr3F
		.WORD _spr3E
		.WORD _spr3F
		.WORD _spr33
		.WORD _spr43
		.WORD _spr44
		.WORD _spr45
		.WORD _spr46
		.WORD _spr47
		.WORD _spr48
		.WORD _spr49
		.WORD _spr4A
		.WORD _spr4B
		.WORD _spr4C
		.WORD _spr4D
		.WORD _spr4E
		.WORD _spr4F
		.WORD _spr50
		.WORD _spr51
		.WORD _spr52
		.WORD _spr53
		.WORD _spr54
		.WORD _spr55
		.WORD _spr56
		.WORD _spr57
		.WORD _spr58
		.WORD _spr59
		.WORD _spr5A
		.WORD _spr5B
		.WORD _spr5C
		.WORD _spr5D
		.WORD _spr00_dummy
		.WORD _spr01
		.WORD _spr02
		.WORD _spr03
		.WORD _spr62
		.WORD _spr63
		.WORD _spr64
		.WORD _spr65
		.WORD _spr66
		.WORD _spr67
		.WORD _spr68
		.WORD _spr67
		.WORD _spr6A
		.WORD _spr6B
		.WORD _spr6C
		.WORD _spr6D
		.WORD _spr6E
		.WORD _spr6F
		.WORD _spr70
		.WORD _spr71
		.WORD _spr72
		.WORD _spr73
		.WORD _spr74
		.WORD _spr75
		.WORD _spr76
		.WORD _spr77
		.WORD _spr78
		.WORD _spr79
		.WORD _spr7A
		.WORD _spr7B
		.WORD _spr7C
		.WORD _spr7D
		.WORD _spr7E
_spr_libB:
		.WORD _spr80
		.WORD _spr81
		.WORD _spr82
		.WORD _spr83
		.WORD _spr84
		.WORD _spr85
		.WORD _spr86
		.WORD _spr87
		.WORD _spr88
		.WORD _spr89
		.WORD _spr8A
		.WORD _spr8B
		.WORD _spr8C
		.WORD _spr8B
		.WORD _spr8E
		.WORD _spr8F
		.WORD _spr90
		.WORD _spr8F
		.WORD _spr92
		.WORD _spr93
		.WORD _spr94
		.WORD _spr95
		.WORD _spr96
		.WORD _spr97
		.WORD _spr98
		.WORD _spr99
		.WORD _spr9A
		.WORD _spr9B
		.WORD _spr9C
		.WORD _spr9D
		.WORD _spr9E
		.WORD _spr01
		.WORD _spr02
		.WORD _spr03
		.WORD _spr02
		.WORD _sprA3
		.WORD _sprA4
_spr01:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$0F,$00,$00
		.BYTE $10,$03,$00,$00
		.BYTE $00,$11,$00,$08
		.BYTE $10,$05,$00,$08
_spr02:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$13,$00,$00
		.BYTE $10,$07,$00,$00
		.BYTE $00,$15,$00,$08
		.BYTE $10,$09,$00,$08
_spr03:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$17,$00,$00
		.BYTE $10,$0B,$00,$00
		.BYTE $00,$19,$00,$08
		.BYTE $10,$0D,$00,$08
_spr05:
		.BYTE $04
		.WORD $1008
		.BYTE $00,$29,$00,$F8
		.BYTE $00,$2B,$00,$00
		.BYTE $00,$2D,$00,$08
		.BYTE $00,$2F,$00,$10
_spr06:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$4F,$00,$00
		.BYTE $10,$53,$00,$00
		.BYTE $00,$51,$00,$08
		.BYTE $10,$55,$00,$08
_spr07:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$51,$40,$00
		.BYTE $10,$55,$40,$00
		.BYTE $00,$4F,$40,$08
		.BYTE $10,$53,$40,$08
_spr08:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$0F,$00,$00
		.BYTE $10,$03,$00,$00
		.BYTE $00,$11,$00,$08
		.BYTE $10,$05,$00,$08
_spr09:
		.BYTE $07
		.WORD $0008
		.BYTE $00,$1B,$00,$F8
		.BYTE $10,$1F,$00,$F8
		.BYTE $00,$1D,$00,$00
		.BYTE $10,$21,$00,$00
		.BYTE $00,$23,$00,$08
		.BYTE $10,$27,$00,$08
		.BYTE $00,$25,$00,$10
_spr0B:
		.BYTE $05
		.WORD $1008
		.BYTE $00,$31,$00,$F8
		.BYTE $00,$33,$00,$00
		.BYTE $00,$35,$00,$08
		.BYTE $00,$37,$00,$10
		.BYTE $00,$39,$00,$18
_spr0C:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$57,$00,$00
		.BYTE $10,$5B,$00,$00
		.BYTE $00,$59,$00,$08
		.BYTE $10,$5D,$00,$08
_spr0D:
		.BYTE $04
		.WORD $1008
		.BYTE $00,$29,$00,$F8
		.BYTE $00,$5F,$00,$00
		.BYTE $00,$61,$00,$08
		.BYTE $00,$63,$00,$10
_spr0E:
		.BYTE $06
		.WORD $0008
		.BYTE $00,$3B,$01,$F8
		.BYTE $00,$3F,$00,$00
		.BYTE $10,$03,$00,$00
		.BYTE $00,$41,$00,$08
		.BYTE $10,$05,$00,$08
		.BYTE $00,$3D,$01,$10
_spr0F:
		.BYTE $06
		.WORD $0008
		.BYTE $00,$3B,$01,$F8
		.BYTE $00,$43,$00,$00
		.BYTE $10,$07,$00,$00
		.BYTE $00,$45,$00,$08
		.BYTE $10,$09,$00,$08
		.BYTE $00,$3D,$01,$10
_spr10:
		.BYTE $06
		.WORD $0008
		.BYTE $00,$3B,$01,$F8
		.BYTE $00,$3F,$00,$00
		.BYTE $10,$0B,$00,$00
		.BYTE $00,$41,$00,$08
		.BYTE $10,$0D,$00,$08
		.BYTE $00,$3D,$01,$10
_spr12:
		.BYTE $04
		.WORD $1008
		.BYTE $00,$47,$01,$F8
		.BYTE $00,$49,$00,$00
		.BYTE $00,$4B,$00,$08
		.BYTE $00,$4D,$00,$10
_spr13:
		.BYTE $07
		.WORD $0008
		.BYTE $00,$65,$01,$F8
		.BYTE $10,$69,$00,$F8
		.BYTE $00,$67,$00,$00
		.BYTE $10,$6B,$00,$00
		.BYTE $00,$6D,$00,$08
		.BYTE $10,$71,$00,$08
		.BYTE $00,$6F,$01,$10
_spr15:
		.BYTE $05
		.WORD $0008
		.BYTE $00,$0F,$00,$00
		.BYTE $10,$03,$00,$00
		.BYTE $00,$C0,$00,$08
		.BYTE $10,$05,$00,$08
		.BYTE $00,$C2,$00,$10
_spr16:
		.BYTE $05
		.WORD $0008
		.BYTE $00,$13,$00,$00
		.BYTE $10,$07,$00,$00
		.BYTE $00,$C4,$00,$08
		.BYTE $10,$09,$00,$08
		.BYTE $00,$C6,$00,$10
_spr17:
		.BYTE $05
		.WORD $0008
		.BYTE $00,$C8,$00,$00
		.BYTE $10,$0B,$00,$00
		.BYTE $00,$CA,$00,$08
		.BYTE $10,$0D,$00,$08
		.BYTE $00,$CC,$00,$10
_spr19:
		.BYTE $05
		.WORD $1008
		.BYTE $00,$29,$00,$F8
		.BYTE $00,$2B,$00,$00
		.BYTE $00,$B0,$00,$08
		.BYTE $00,$6E,$00,$10
		.BYTE $00,$56,$00,$18
_spr1A:
		.BYTE $02
		.WORD $0808
		.BYTE $00,$7B,$00,$F8
		.BYTE $00,$7D,$00,$00
_spr1B:
		.BYTE $02
		.WORD $0808
		.BYTE $00,$7F,$00,$F8
		.BYTE $00,$81,$00,$00
_spr1C:
		.BYTE $08
		.WORD $0008
		.BYTE $00,$D7,$00,$F0
		.BYTE $10,$D9,$00,$F0
		.BYTE $00,$DB,$00,$F8
		.BYTE $10,$DD,$00,$F8
		.BYTE $00,$DF,$00,$00
		.BYTE $10,$E1,$00,$00
		.BYTE $00,$E3,$00,$08
		.BYTE $10,$F5,$00,$08
_spr1D:
		.BYTE $02
		.WORD $0008
		.BYTE $08,$EB,$00,$00
		.BYTE $08,$ED,$00,$08
_spr1F:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$8F,$00,$00
		.BYTE $10,$03,$00,$00
		.BYTE $00,$91,$00,$08
		.BYTE $10,$05,$00,$08
_spr20:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$93,$00,$00
		.BYTE $10,$07,$00,$00
		.BYTE $00,$95,$00,$08
		.BYTE $10,$09,$00,$08
_spr21:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$97,$00,$00
		.BYTE $10,$0B,$00,$00
		.BYTE $00,$99,$00,$08
		.BYTE $10,$0D,$00,$08
_spr23:
		.BYTE $05
		.WORD $0A08
		.BYTE $00,$9B,$00,$00
		.BYTE $10,$9F,$00,$00
		.BYTE $00,$9D,$00,$08
		.BYTE $10,$A1,$00,$08
		.BYTE $10,$A3,$00,$10
_spr24:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$8F,$00,$00
		.BYTE $10,$03,$00,$00
		.BYTE $00,$91,$00,$08
		.BYTE $10,$05,$00,$08
_spr25:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$93,$00,$00
		.BYTE $10,$07,$00,$00
		.BYTE $00,$95,$00,$08
		.BYTE $10,$09,$00,$08
_spr26:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$97,$00,$00
		.BYTE $10,$0B,$00,$00
		.BYTE $00,$99,$00,$08
		.BYTE $10,$0D,$00,$08
_spr28:
		.BYTE $07
		.WORD $0000
		.BYTE $00,$B1,$00,$F8
		.BYTE $10,$B5,$00,$F8
		.BYTE $00,$B3,$00,$00
		.BYTE $10,$B7,$00,$00
		.BYTE $00,$B9,$00,$08
		.BYTE $10,$BB,$00,$08
		.BYTE $10,$BD,$00,$10
_spr29:
		.BYTE $02
		.WORD $0008
		.BYTE $08,$F7,$00,$00
		.BYTE $08,$F9,$00,$08
_spr2A:
		.BYTE $01
		.WORD $0000
		.BYTE $00,$77,$00,$00
_spr2B:
		.BYTE $02
		.WORD $2008
		.BYTE $00,$73,$00,$00
		.BYTE $00,$75,$00,$08
_spr2C:
		.BYTE $02
		.WORD $0008
		.BYTE $00,$7B,$00,$00
		.BYTE $00,$7D,$00,$08
_spr2D:
		.BYTE $02
		.WORD $0008
		.BYTE $00,$7F,$00,$00
		.BYTE $00,$81,$00,$08
_spr2E:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$8F,$00,$00
		.BYTE $10,$03,$00,$00
		.BYTE $00,$91,$00,$08
		.BYTE $10,$05,$00,$08
_spr2F:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$93,$00,$00
		.BYTE $10,$07,$00,$00
		.BYTE $00,$95,$00,$08
		.BYTE $10,$09,$00,$08
_spr30:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$97,$00,$00
		.BYTE $10,$0B,$00,$00
		.BYTE $00,$99,$00,$08
		.BYTE $10,$0D,$00,$08
_spr32:
		.BYTE $06
		.WORD $0008
		.BYTE $00,$A5,$00,$00
		.BYTE $10,$AB,$00,$00
		.BYTE $00,$A7,$00,$08
		.BYTE $10,$AD,$00,$08
		.BYTE $00,$A9,$00,$10
		.BYTE $10,$AF,$00,$10
_spr33:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$BF,$00,$00
		.BYTE $10,$53,$00,$00
		.BYTE $00,$C1,$00,$08
		.BYTE $10,$55,$00,$08
_spr34:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$F5,$00,$00
		.BYTE $10,$55,$40,$00
		.BYTE $00,$F7,$00,$08
		.BYTE $10,$53,$40,$08
_spr35:
		.BYTE $01
		.WORD $0000
		.BYTE $00,$FD,$00,$00
_spr36:
		.BYTE $04
		.WORD $1008
		.BYTE $F8,$83,$00,$F8
		.BYTE $F8,$85,$00,$00
		.BYTE $F8,$87,$00,$08
		.BYTE $F8,$89,$00,$10
_spr37:
		.BYTE $01
		.WORD $0000
		.BYTE $08,$8D,$00,$00
_spr38:
		.BYTE $04
		.WORD $1008
		.BYTE $00,$29,$00,$F8
		.BYTE $00,$2B,$00,$00
		.BYTE $00,$2D,$00,$08
		.BYTE $00,$2F,$00,$10
_spr3D:
		.BYTE $01
		.WORD $0000
		.BYTE $08,$8B,$00,$00
_spr43:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$C1,$40,$00
		.BYTE $10,$55,$40,$00
		.BYTE $00,$BF,$40,$08
		.BYTE $10,$53,$40,$08
_spr49:
		.BYTE $12
		.WORD $0008
		.BYTE $D0,$C3,$02,$F0
		.BYTE $E0,$C9,$02,$F0
		.BYTE $D0,$C5,$02,$F8
		.BYTE $E0,$CB,$02,$F8
		.BYTE $F0,$CD,$02,$F8
		.BYTE $D0,$C7,$02,$00
		.BYTE $F0,$CF,$02,$00
		.BYTE $00,$D1,$02,$00
		.BYTE $10,$D5,$02,$00
		.BYTE $D0,$C7,$42,$08
		.BYTE $F0,$CF,$42,$08
		.BYTE $00,$D3,$02,$08
		.BYTE $10,$D7,$02,$08
		.BYTE $D0,$C5,$42,$10
		.BYTE $E0,$CB,$42,$10
		.BYTE $F0,$CD,$42,$10
		.BYTE $D0,$C3,$42,$18
		.BYTE $E0,$C9,$42,$18
_spr4A:
		.BYTE $01
		.WORD $0000
		.BYTE $00,$79,$00,$00
_spr53:
		.BYTE $02
		.WORD $0008
		.BYTE $08,$F9,$00,$00
		.BYTE $08,$FB,$00,$08
_spr54:
		.BYTE $02
		.WORD $0008
		.BYTE $08,$E4,$00,$00
		.BYTE $08,$28,$00,$08
_spr55:
		.BYTE $01
		.WORD $0000
		.BYTE $00,$79,$00,$00
_spr5C:
		.BYTE $02
		.WORD $0008
		.BYTE $08,$F5,$00,$00
		.BYTE $08,$F7,$00,$08
_spr5D:
		.BYTE $02
		.WORD $0008
		.BYTE $08,$E1,$00,$00
		.BYTE $08,$E3,$00,$08
_spr62:
		.BYTE $06
		.WORD $0008
		.BYTE $00,$1B,$00,$F8
		.BYTE $10,$21,$00,$F8
		.BYTE $00,$1D,$00,$00
		.BYTE $10,$23,$00,$00
		.BYTE $00,$1F,$00,$08
		.BYTE $10,$25,$00,$08
_spr63:
		.BYTE $06
		.WORD $0008
		.BYTE $F0,$27,$00,$00
		.BYTE $00,$29,$00,$00
		.BYTE $10,$2B,$00,$00
		.BYTE $F0,$2D,$00,$08
		.BYTE $00,$2F,$00,$08
		.BYTE $10,$31,$00,$08
_spr64:
		.BYTE $06
		.WORD $0008
		.BYTE $F0,$33,$00,$00
		.BYTE $00,$35,$00,$00
		.BYTE $10,$37,$00,$00
		.BYTE $F0,$39,$00,$08
		.BYTE $00,$3B,$00,$08
		.BYTE $10,$3D,$00,$08
_spr65:
		.BYTE $05
		.WORD $0008
		.BYTE $10,$43,$00,$F8
		.BYTE $00,$3F,$00,$00
		.BYTE $10,$45,$00,$00
		.BYTE $00,$41,$00,$08
		.BYTE $10,$47,$00,$08
_spr66:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$8F,$00,$00
		.BYTE $10,$E5,$00,$00
		.BYTE $00,$91,$00,$08
		.BYTE $10,$E7,$00,$08
_spr67:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$93,$00,$00
		.BYTE $10,$E9,$00,$00
		.BYTE $00,$95,$00,$08
		.BYTE $10,$EB,$00,$08
_spr68:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$97,$00,$00
		.BYTE $10,$ED,$00,$00
		.BYTE $00,$99,$00,$08
		.BYTE $10,$EF,$00,$08
_spr6A:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$BF,$00,$00
		.BYTE $10,$F1,$00,$00
		.BYTE $00,$C1,$00,$08
		.BYTE $10,$F3,$00,$08
_spr6B:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$C1,$40,$00
		.BYTE $10,$F3,$40,$00
		.BYTE $00,$BF,$40,$08
		.BYTE $10,$F1,$40,$08
_sprA3:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$BF,$00,$00
		.BYTE $10,$F1,$00,$00
		.BYTE $00,$C1,$00,$08
		.BYTE $10,$F3,$00,$08
_sprA4:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$D9,$00,$00
		.BYTE $10,$F3,$40,$00
		.BYTE $00,$DB,$00,$08
		.BYTE $10,$F1,$40,$08
_spr00_dummy:
		.BYTE $00
_spr87:
		.BYTE $01
		.WORD $1000
		.BYTE $00,$49,$00,$04
_spr88:
		.BYTE $01
		.WORD $1000
		.BYTE $00,$4B,$00,$04
_spr89:
		.BYTE $01
		.WORD $1000
		.BYTE $00,$4D,$00,$04
		SECTION_END "SPRITES"

		SECTION_START
; =============== S U B	R O U T	I N E =======================================
_tlm_lib_load:
		PHA
		LDA		#$02
		STA		byte_3
		LDA		#$01
		JSR		_ppu_queue_byte_insert
		PLA
		STA		byte_2
		ASL
		TAX
		LDA		_tlm_lib,X
		STA		word_0
		LDA		_tlm_lib+1,X
		STA		word_0+1
		LDX		_ppu_queue_pos
		LDY		#$00
loc_9622:
		LDA		(word_0),Y
		INY
		CMP		#$FF
		BEQ		_ppu_queue_pos_set
		CMP		#$FE
		BEQ		loc_9646
		CMP		#$FD
		BEQ		loc_964A
		STA		_ppu_queue_buf,X
		LDA		byte_2
		BPL		loc_9643
		LDA		byte_3
		BNE		loc_9641
		STA		_ppu_queue_buf,X
		BEQ		loc_9643
loc_9641:
		DEC		byte_3
loc_9643:
		INX
		BNE		loc_9622
loc_9646:
		LDA		#$FF
		BNE		_ppu_queue_byte_insert_ex
loc_964A:
		LDA		#$FF
		JSR		_ppu_queue_byte_insert_ex
		LDA		#$02
		STA		byte_3
		LDA		#$01
		JSR		_ppu_queue_byte_insert_ex
		BNE		loc_9622
		LDA		#$FF
		BNE		_ppu_queue_byte_insert

; =============== S U B	R O U T	I N E =======================================
_ppu_queue_byte00_insert:
		LDA		#$00
		BEQ		_ppu_queue_byte_insert

; =============== S U B	R O U T	I N E =======================================
_ppu_queue_byte_insert:
		LDX		_ppu_queue_pos

; =============== S U B	R O U T	I N E =======================================
_ppu_queue_byte_insert_ex:
		STA		_ppu_queue_buf,X
		INX
		PHA
		LDA		#$00
		STA		_ppu_queue_buf,X
		PLA

; =============== S U B	R O U T	I N E =======================================
_ppu_queue_pos_set:
		STX		_ppu_queue_pos
		RTS

; ---------------------------------------------------------------------------
_tlm_lib:
		.WORD _tlm01_1_player
		.WORD _tlm01_1_player
		.WORD _tlm02_2_players
		.WORD _tlm03_play_select
		.WORD _tlm04_konami_1897
		.WORD _tlm05_dummy
		.WORD _tlm06_pal
		.WORD _tlm07_blank
		.WORD _tlm08_ab
		.WORD _tlm09_1p
		.WORD _tlm0A_2p
		.WORD _tlm0B_please_set
		.WORD _tlm0C_err
		.WORD _tlm0D_blank
		.WORD _tlm0E_d0fe
		.WORD _tlm0F_d0fe
		.WORD _tlm10_game_over
		.WORD _tlm11_blank
		.WORD _tlm12_blank
		.WORD _tlm13_pal
		.WORD _tlm14_continue
		.WORD _tlm17_yes
		.WORD _tlm16_no
		.WORD _tlm17_yes
		.WORD _tlm18_pal
		.WORD _tlm19_bg_pal
		.WORD _tlm1A_bg_pal
		.WORD _tlm1B_bg_pal
		.WORD _tlm1C_pal
		.WORD _tlm1D_staff
		.WORD _tlm1E_blank
		.WORD _tlm1F_blank
		.WORD _tlm20_please_push_start_button
		.WORD _tlm21_blank
		.WORD _tlm22_bg_pal
		.WORD _tlm23_bg_pal
		.WORD _tlm24_bg_pal
		.WORD _tlm25_bg_pal
		.WORD _tlm26_ending
		.WORD _tlm27_ending
		.WORD _tlm28_ending
		.WORD _tlm29_ending
		.WORD _tlm2A_ending
		.WORD _tlm2B_ending
		.WORD _tlm2C_ending
		.WORD _tlm2D_ending
		.WORD _tlm2E_ending
		.WORD _tlm2F_ending
		.WORD _tlm30_ending
		.WORD _tlm31_ending
		.WORD _tlm32_ending
		.WORD _tlm33_ending
		.WORD _tlm34_ending
		.WORD _tlm35_ending
		.WORD _tlm36_ending
		.WORD _tlm37_ending
		.WORD _tlm38_ending
		.WORD _tlm39_ending
		.WORD _tlm3A_ending
		.WORD _tlm3B_ending
		.WORD _tlm3C_ending
		.WORD _tlm3D_ending
		.WORD _tlm3E_ending
		.WORD _tlm3F_ending
		.WORD _tlm40_ending
		.WORD _tlm41_ending
		.WORD _tlm42_ending
		.WORD _tlm43_ending
		.WORD _tlm44_ending
		.WORD _tlm45_ending
		.WORD _tlm46_ending
		.WORD _tlm47_ending
		.WORD _tlm48_ending
		.WORD _tlm49_ending
		.WORD _tlm4A_pal
		.WORD _tlm4B_loading
		.WORD _tlm4C_pal
		.WORD _tlm4D_pal
		.WORD _tlm4E_pal
		.WORD _tlm4F_pal
		.WORD _tlm50_pal
		.WORD _tlm51_pal
		.WORD _tlm52_pal
		.WORD _tlm53_bg_pal
		.WORD _tlm54_your_mission
		.WORD _tlm55_bg_pal
		.WORD _tlm56_bg_pal
_tlm54_your_mission:
		.WORD $A520
		.BYTE $23,$19,$1F,$1C,$00,$17,$13,$1D,$1D,$13,$19,$18
		.BYTE $FD
		.WORD $E820
		.BYTE $0E,$0F,$1D,$1E,$1C,$19,$23,$00,$0F,$18,$0F,$17,$23
		.BYTE $FD
		.WORD $2721
		.BYTE $1D,$0F,$0D,$1C,$0F,$1E,$00,$21,$0F,$0B,$1A,$19,$18,$26
		.BYTE $FD
		.WORD $8A21
		.BYTE $11,$19,$19,$0E,$00,$16,$1F,$0D,$15,$26
		.BYTE $FE
_tlm0B_please_set:
		.WORD	$E921
		.BYTE $1A,$16,$0F,$0B,$1D,$0F,$00,$1D,$0F,$1E,$00,$00
		.BYTE $FE
_tlm0C_err:
		.WORD $ED21
		.BYTE $0F,$1C,$1C,$00,$00,$00
		.BYTE $FE
_tlm4B_loading:
		.WORD $ED21
		.BYTE $16,$19,$0B,$0E,$13,$18,$11,$00,$00
		.BYTE $FE
_tlm4C_pal:
		.BYTE $3F,$00,$0F,$0F,$0F,$20,$0F,$0F,$0F,$20,$0F,$0F,$0F,$20,$0F,$0F
		.BYTE $0F,$20,$FE
_tlm03_play_select:
		.WORD $AB22
		.BYTE $1A,$16,$0B,$23,$00,$1D,$0F,$16,$0F,$0D,$1E
		.BYTE $FE
_tlm04_konami_1897:
		.WORD $4A22
		.BYTE $F9
		.BYTE $00,$15,$19,$18,$0B,$17,$13,$00,$02,$0A,$09,$08
		.BYTE $FE
_tlm01_1_player:
		.WORD $EE22
		.BYTE $02,$00,$1A,$16,$0B,$23,$0F,$1C
		.BYTE $FE
_tlm02_2_players:
		.WORD $0E23
		.BYTE $03,$00,$1A,$16,$0B,$23,$0F,$1C,$1D
		.BYTE $FE
_tlm14_continue:
		.WORD $0B22
		.BYTE $0D,$19,$18,$1E,$13,$18,$1F,$0F
		.BYTE $FE
_tlm17_yes:
		.WORD $4E22
		.BYTE $23,$0F,$1D
		.BYTE $FE
_tlm16_no:
		.WORD $8E22
		.BYTE $18,$19
		.BYTE $FE
_tlm07_blank:
		.WORD $6020
		.BYTE $00
		.BYTE $FF
_tlm0D_blank:
		.WORD $7920
		.BYTE $00
		.BYTE $FF
_tlm08_ab:
		.WORD $4B20
		.BYTE $0B,$0C,$00
		.BYTE $FF
_tlm09_1p:
		.WORD $4020
		.BYTE $02,$0E,$00
		.BYTE $FF
_tlm0A_2p:
		.WORD $5620
		.BYTE $03,$0E,$00
		.BYTE $FF
_tlm0E_d0fe:
		.WORD $6820
		.BYTE $0E,$01,$10,$0F
		.BYTE $FF
_tlm0F_d0fe:
		.WORD $7320
		.BYTE $0E,$01,$10,$0F
		.BYTE $FF
_tlm06_pal:
		.BYTE $3F,$00,$0F,$00,$10,$30,$0F,$19,$27,$15,$0F,$15,$26,$10,$0F,$27
		.BYTE $16,$21,$0F,$0C,$26,$30,$0F,$0C,$2C,$30,$0F,$12,$26,$30,$0F,$06
		.BYTE $30,$30,$FE
_tlm05_dummy:
		.WORD $0020
		.BYTE $FE
_tlm4D_pal:
		.BYTE $3F,$00,$0F,$3B,$00,$30,$0F,$10,$00,$30,$0F,$19,$00,$09,$0F,$3B
		.BYTE $17,$07,$0F,$12,$0F,$27,$0F,$16,$0F,$38,$0F,$27,$0F,$38,$0F,$20
		.BYTE $0F,$17,$FE
_tlm4E_pal:
		.BYTE $3F,$00,$0F,$00,$10,$30,$0F,$00,$18,$20,$0F,$1A,$18,$28,$0F,$32
		.BYTE $1A,$22,$0F,$12,$0F,$27,$0F,$16,$0F,$38,$0F,$27,$0F,$38,$0F,$07
		.BYTE $0F,$20,$FE
_tlm4F_pal:
		.BYTE $3F,$00,$0F,$01,$00,$30,$0F,$10,$00,$30,$0F,$19,$00,$09,$0F,$31
		.BYTE $00,$30,$0F,$12,$0F,$27,$0F,$16,$0F,$38,$0F,$27,$0F,$38,$0F,$20
		.BYTE $0F,$07,$FE
_tlm50_pal:
		.BYTE $3F,$00,$0F,$3B,$00,$30,$0F,$10,$00,$30,$0F,$19,$00,$09,$0F,$3B
		.BYTE $17,$06,$0F,$12,$0F,$27,$0F,$16,$0F,$38,$0F,$27,$0F,$38,$0F,$07
		.BYTE $0F,$20,$FE
_tlm51_pal:
		.BYTE $3F,$00,$0F,$17,$00,$30,$0F,$10,$00,$30,$0F,$08,$00,$30,$0F,$2B
		.BYTE $06,$07,$0F,$12,$0F,$27,$0F,$16,$0F,$38,$0F,$27,$0F,$38,$0F,$07
		.BYTE $0F,$20,$FE
_tlm52_pal:
		.BYTE $3F,$00,$0F,$0B,$00,$30,$0F,$0B,$09,$37,$0F,$0B,$18,$3A,$0F,$0B
		.BYTE $17,$27,$0F,$12,$0F,$27,$0F,$16,$0F,$38,$0F,$27,$0F,$38,$0F,$08
		.BYTE $0F,$30,$FE
_tlm53_bg_pal:
		.BYTE $3F,$00,$0F,$00,$10,$30,$0F,$10,$06,$07,$0F,$18,$08,$0F,$0F,$10
		.BYTE $00,$0F,$FE
_tlm55_bg_pal:
		.BYTE $3F,$00,$0F,$00,$10,$30,$0F,$10,$06,$07,$0F,$17,$07,$0F,$0F,$10
		.BYTE $00,$0F,$FE
_tlm56_bg_pal:
		.BYTE $3F,$00,$0F,$00,$10,$30,$0F,$10,$06,$07,$0F,$10,$00,$0F,$0F,$10
		.BYTE $00,$0F,$FE
_tlm10_game_over:
		.WORD $8B21
		.BYTE $11,$0B,$17,$0F,$00,$19,$20,$0F,$1C
		.BYTE $FE
_tlm11_blank:
		.WORD $6020
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
		.BYTE $FE
_tlm12_blank:
		.WORD $7320
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
		.BYTE $FE
_tlm13_pal:
		.BYTE $3F,$00,$0F,$1B,$00,$30,$0F,$10,$00,$30,$0F,$19,$00,$09,$0F,$1B
		.BYTE $17,$07,$0F,$12,$0F,$27,$0F,$16,$0F,$38,$0F,$00,$06,$16,$0F,$27
		.BYTE $0F,$38,$FE
_tlm18_pal:
		.BYTE $3F,$00,$0F,$10,$00,$20,$0F,$0B,$00,$19,$0F,$02,$28,$30,$0F,$16
		.BYTE $28,$20,$0F,$12,$0F,$27,$0F,$16,$0F,$37,$0F,$38,$1B,$0A,$0F,$27
		.BYTE $0F,$37,$FE
_tlm19_bg_pal:
		.BYTE $3F,$00,$0F,$10,$00,$20,$0F,$0B,$00,$19,$0F,$12,$28,$20,$0F,$16
		.BYTE $28,$20,$FE
_tlm1A_bg_pal:
		.BYTE $3F,$00,$0F,$10,$00,$20,$0F,$0B,$00,$19,$0F,$22,$28,$10,$0F,$16
		.BYTE $28,$20,$FE
_tlm1B_bg_pal:
		.BYTE $3F,$00,$0F,$10,$00,$20,$0F,$0B,$00,$19,$0F,$12,$28,$20,$0F,$16
		.BYTE $28,$20,$FE
_tlm1C_pal:
		.BYTE $3F,$00,$0F,$16,$06,$30,$0F,$08,$18,$30,$0F,$27,$16,$21,$0F,$27
		.BYTE $16,$21,$0F,$12,$0F,$27,$0F,$16,$0F,$38,$0F,$2A,$0F,$38,$0F,$16
		.BYTE $0F,$27,$FE
_tlm1D_staff:
		.WORD $ED20
		.BYTE $1D,$1E,$0B,$10,$10
		.BYTE $FE
_tlm1E_blank:
		.WORD $6021
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
		.BYTE $00,$00,$00,$00,$00
		.BYTE $FE
_tlm1F_blank:
		.WORD $A021
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
		.BYTE $FE
_tlm20_please_push_start_button:
		.WORD $A321
		.BYTE $1A,$16,$0F,$0B,$1D,$0F,$00,$1A,$1F,$1D,$12,$00,$1D,$1E,$0B,$1C
		.BYTE $1E,$00,$0C,$1F,$1E,$1E,$19,$18
		.BYTE $FE
_tlm21_blank:
		.WORD $ED20
		.BYTE $00,$00,$00,$00,$00
		.BYTE $FE
_tlm22_bg_pal:
		.BYTE $3F,$00,$0F,$0B,$00,$30,$0F,$0B,$09,$37,$0F,$0B,$01,$3A,$0F,$0B
		.BYTE $17,$27,$FE
_tlm23_bg_pal:
		.BYTE $3F,$00,$0F,$06,$00,$30,$0F,$0B,$09,$37,$0F,$0B,$11,$3A,$0F,$0B
		.BYTE $17,$27,$FE
_tlm24_bg_pal:
		.BYTE $3F,$00,$0F,$16,$00,$30,$0F,$0B,$09,$37,$0F,$0B,$21,$3A,$0F,$0B
		.BYTE $17,$27,$FE
_tlm25_bg_pal:
		.BYTE $3F,$00,$30,$16,$06,$30,$30,$08,$18,$30,$30,$27,$16,$21,$30,$27
		.BYTE $16,$21,$FE
_tlm4A_pal:
		.BYTE $3F,$00,$0F,$16,$06,$30,$0F,$08,$18,$30,$0F,$27,$16,$21,$0F,$27
		.BYTE $16,$21,$0F,$12,$01,$27,$0F,$16,$07,$38,$0F,$20,$0F,$38,$0F,$1A
		.BYTE $09,$27
byte_9ADB:
		.BYTE $FE
_ppu_unpack_flags_list:
		.BYTE $00,$04
		SECTION_END "TLM LIB"

		BANK_END 6,$C000
