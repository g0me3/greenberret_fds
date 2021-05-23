
		ORG $8000

		BANK_START $06

		SECTION_START

; =============== S U B	R O U T	I N E =======================================
_stage_object_manager:
		LDX		#$00
loc_C03E:
		LDA		byte_540,X
		BEQ		loc_C04D
		TXA
		CLC
		ADC		#$20
		TAX
		BNE		loc_C03E
		JMP		sub_B941
; ---------------------------------------------------------------------------
loc_C04D:
		LDA		#$00
		STA		byte_458
		LDA		byte_465
		BEQ		loc_C066
		LDA		_1p_stage
		ASL
		TAY
		LDA		_substage_obj_lib,Y
		STA		byte_10
		LDA		_substage_obj_lib+1,Y
		JMP		loc_C072
; ---------------------------------------------------------------------------
loc_C066:
		LDA		_1p_stage
		ASL
		TAY
		LDA		_stage_obj_lib,Y
		STA		byte_10
		LDA		_stage_obj_lib+1,Y
loc_C072:
		STA		byte_11
		LDA		byte_48
		ASL
		TAY
		LDA		(byte_10),Y
		STA		byte_8
		INY
		LDA		(byte_10),Y
		STA		byte_9
		LDY		#$00
loc_C083:
		LDA		(byte_8),Y
		CMP		#$FF
		BEQ		loc_C0AF
		CMP		_game_vat49
		BEQ		loc_C093
		INY
		INY
		INY
		JMP		loc_C083
; ---------------------------------------------------------------------------
loc_C093:
		LDA		#$01
		STA		byte_540,X
		LDA		#$00
		STA		byte_550,X
		STA		byte_551,X
		INY
		LDA		(byte_8),Y
		STA		byte_545,X
		INY
		LDA		(byte_8),Y
		STA		byte_541,X
		JSR		sub_C0B2
loc_C0AF:
		JMP		sub_B941

; =============== S U B	R O U T	I N E =======================================
sub_C0B2:
		TXA
		TAY
		LDA		byte_541,Y
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD _obj_hndl01
		.WORD _obj_hndl02
		.WORD _obj_hndl03
		.WORD _obj_hndl04
		.WORD _obj_hndl05
		.WORD _obj_hndl06
		.WORD _obj_hndl07
		.WORD _obj_hndl08
		.WORD _obj_hndl09
		.WORD _obj_hndl0A
		.WORD _obj_hndl0B
		.WORD _obj_hndl0C
		.WORD _obj_hndl0D
		.WORD _obj_hndl0E
		.WORD _obj_hndl0F
		.WORD _obj_hndl10
		.WORD _obj_hndl11

; =============== S U B	R O U T	I N E =======================================
_obj_hndl01:
		JSR		sub_C240
		LDA		#$02
		STA		byte_559,Y
		LDA		#$00
		JSR		sub_C24C
		LDA		#$03
		STA		byte_54E,Y
		LDA		#$00
		JMP		sub_C4F9

; =============== S U B	R O U T	I N E =======================================
_obj_hndl02:
		JSR		sub_C240
		LDA		#$03
		STA		byte_559,Y
		LDA		#$08
		JSR		sub_C24C
		LDA		#$03
		STA		byte_54E,Y
		LDA		#$01
		JMP		sub_C4F9

; =============== S U B	R O U T	I N E =======================================
_obj_hndl03:
		JSR		sub_C240
		LDA		_2p_stage
		CMP		#$04
		BCS		loc_C118
		LDA		#$20
		STA		byte_45E
loc_C118:
		LDA		#$10
		STA		byte_559,Y
		LDA		#$10
		JSR		sub_C24C
		LDA		#$01
		STA		byte_54E,Y
		LDA		#$03
		JMP		sub_C4F9

; =============== S U B	R O U T	I N E =======================================
_obj_hndl04:
		LDA		#$02
		STA		byte_559,Y
		JSR		sub_C2BB
		LDA		#$FF
		STA		byte_543,Y
		LDA		#$01
		STA		byte_54B,Y
		LDA		#$03
		STA		byte_54E,Y
		LDA		#$18
		STA		byte_55D,Y
		LDA		#$05
		JSR		sub_C4F9
		LDA		_1p_stage
		CMP		#$01
		BNE		locret_C15E
		LDA		#$1E
		STA		byte_555,Y
		STA		byte_554,Y
		STA		byte_54F,Y
locret_C15E:
		RTS

; =============== S U B	R O U T	I N E =======================================
_obj_hndl05:
		JSR		sub_C240
		LDA		byte_465
		BNE		loc_C178
		LDA		_1p_stage
		BEQ		loc_C178
		CMP		#$02
		BEQ		loc_C178
		CMP		#$05
		BEQ		loc_C178

; =============== S U B	R O U T	I N E =======================================
sub_C173:
		LDA		#$01
		STA		byte_557,Y
loc_C178:
		LDA		#$05
		STA		byte_559,Y
		JSR		sub_C2BB
		LDA		#$FF
		STA		byte_543,Y
		LDA		#$00
		STA		byte_54B,Y
		LDA		#$01
		STA		byte_54E,Y
		LDA		#$06
		JMP		sub_C4F9

; =============== S U B	R O U T	I N E =======================================
_obj_hndl11:
		JSR		sub_C240
		JSR		sub_C173
		LDA		#$00
		STA		byte_54F,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
_obj_hndl06:
		JSR		sub_C240
		LDA		#$C0
		STA		byte_54D,Y

; =============== S U B	R O U T	I N E =======================================
sub_C1A8:
		LDA		#$05
		STA		byte_559,Y
		LDA		#$18
		JSR		sub_C24C
		LDA		#$02
		STA		byte_54E,Y
		LDA		#$10
		STA		byte_55D,Y
		LDA		#$08
		JMP		sub_C4F9

; =============== S U B	R O U T	I N E =======================================
_obj_hndl07:
		LDA		#$0B

; =============== S U B	R O U T	I N E =======================================
sub_C1C3:
		STA		byte_541,Y
		STA		byte_55E,Y
		JSR		sub_C240
		LDA		#$01
		STA		byte_559,Y
		JSR		sub_C2CA
		LDA		#$FF
		STA		byte_543,Y
		LDA		#$03
		LDX		byte_460
		BNE		loc_C1E2
		LDA		#$C0
loc_C1E2:
		STA		byte_55F,Y
		LDA		#$01
		STA		byte_54B,Y
		LDA		#$02
		STA		byte_54E,Y
		JSR		sub_C2BB
		RTS

; =============== S U B	R O U T	I N E =======================================
_obj_hndl08:
		LDA		#$0C
		BNE		sub_C1C3

; =============== S U B	R O U T	I N E =======================================
_obj_hndl0D:
		LDA		#$19
		BNE		sub_C1C3

; =============== S U B	R O U T	I N E =======================================
_obj_hndl0E:
		LDA		#$1A
		BNE		sub_C1C3

; =============== S U B	R O U T	I N E =======================================
_obj_hndl0B:
		JSR		sub_C240
		LDA		#$30
		STA		byte_559,Y
		LDA		#$38
		JSR		sub_C24C
		LDA		#$02
		STA		byte_54E,Y
		LDA		#$00
		STA		byte_549,Y
		LDA		#$A0
		STA		byte_54A,Y
		LDA		#$10
		STA		byte_55D,Y
		LDA		#$01
		LDX		byte_500
		BEQ		loc_C238
		LDA		#$00
		LDX		byte_520
		BEQ		loc_C238
		LDA		byte_500+3
		ADC		byte_523
		ADC		_frames_counter
		AND		#$01
loc_C238:
		STA		byte_54C,Y
		LDA		#$16
		JMP		sub_C4F9

; =============== S U B	R O U T	I N E =======================================
sub_C240:
		LDA		#$00
		STA		byte_550,Y
		STA		byte_551,Y
		STA		byte_557,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_C24C:
		PHA
		JSR		sub_C2BB
		PLA
		LDX		byte_541,Y
		BPL		loc_C259
		CLC
		ADC		#$04
loc_C259:
		TAX
		LDA		byte_C273,X
		STA		byte_543,Y
		LDA		byte_C273+1,X
		STA		byte_54B,Y
		LDA		byte_C273+2,X
		STA		byte_547,Y
		LDA		byte_C273+3,X
		STA		byte_548,Y
		RTS
; ---------------------------------------------------------------------------
byte_C273:
		.BYTE $FF,$01,$FF,$80
		.BYTE $01,$00,$01,$10
		.BYTE $FF,$01,$FF,$00
		.BYTE $01,$00,$01,$20
		.BYTE $FF,$01,$FF,$10
		.BYTE $01,$00,$01,$30
		.BYTE $FF,$01,$FE,$F0
		.BYTE $01,$00,$01,$10
		.BYTE $FF,$01,$FF,$80
		.BYTE $01,$00,$00,$80
		.BYTE $FF,$01,$FE,$00
		.BYTE $01,$00,$02,$00
		.BYTE $FF,$01,$FD,$C0
		.BYTE $01,$00,$02,$40
		.BYTE $FF,$01,$FE,$00
		.BYTE $01,$00,$02,$00
		.BYTE $FF,$01,$FF,$00
		.BYTE $01,$00,$01,$00

; =============== S U B	R O U T	I N E =======================================
sub_C2BB:
		LDA		#$00
		STA		byte_547,Y
		STA		byte_548,Y
		STA		byte_549,Y
		STA		byte_54A,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_C2CA:
		LDX		byte_541,Y
		LDA		byte_C358,X
		STA		byte_554,Y
		STA		byte_54F,Y
		SEC
		SBC		#$20
		TAX
		LDA		byte_C39E,X
		STA		byte_552,Y
		LDX		byte_541,Y
		LDA		byte_C37B,X
		STA		byte_555,Y
		LDA		#$F0
		STA		byte_553,Y
		LDA		_1p_stage
		CMP		#$05
		BNE		locret_C323
		LDA		byte_554,Y
		CMP		#$20
		BEQ		loc_C316
		CMP		#$25
		BEQ		loc_C316
		CMP		#$2F
		BEQ		loc_C316
		CMP		#$34
		BNE		locret_C323
		LDA		#$6B
		STA		byte_54F,Y
		STA		byte_554,Y
		LDA		#$6C
		STA		byte_555,Y
		BNE		locret_C323
loc_C316:
		LDA		#$67
		STA		byte_54F,Y
		STA		byte_554,Y
		LDA		#$6A
		STA		byte_555,Y
locret_C323:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_C324:
		LDA		byte_552,Y
		CLC
		ADC		byte_553,Y
		STA		byte_553,Y
		BCC		locret_C34E
		LDA		byte_54F,Y
		CMP		byte_555,Y
		BEQ		loc_C34F
		LDA		byte_54F,Y
		CLC
		ADC		#$01
		STA		byte_54F,Y
loc_C341:
		LDA		byte_54F,Y
		SEC
		SBC		#$20
		TAX
		LDA		byte_C39E,X
		STA		byte_552,Y
locret_C34E:
		RTS
; ---------------------------------------------------------------------------
loc_C34F:
		LDA		byte_554,Y
		STA		byte_54F,Y
		JMP		loc_C341
; ---------------------------------------------------------------------------
byte_C358:
		.BYTE $20,$20,$24,$25,$29,$2A,$2C,$2D,$2F,$34,$33,$39,$39,$3A,$3A,$20
		.BYTE $20,$3F,$41,$41,$45,$49,$4A,$4C,$50,$39,$39,$3A,$3A,$8E,$92,$94
		.BYTE $98,$8A,$9F
byte_C37B:
		.BYTE $23,$23,$24,$28,$29,$2A,$2C,$2E,$32,$35,$33,$39,$39,$3D,$3D,$20
		.BYTE $20,$40,$42,$42,$48,$49,$4A,$4F,$53,$39,$39,$3D,$3D,$91,$93,$95
		.BYTE $98,$8D,$A2
byte_C39E:
		.BYTE $20,$30,$20,$30,$00,$20,$30,$20,$30,$00,$00,$00,$00,$38,$00,$18
		.BYTE $28,$18,$28,$00,$20,$20,$00,$00,$00,$00,$1A,$22,$1A,$22,$00,$20
		.BYTE $30,$20,$30,$20,$20,$30,$30,$30,$30,$00,$00,$00,$6A,$6A,$6A,$6A
		.BYTE $6A,$6A,$6A,$6A,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
		.BYTE $00,$00,$00,$00,$00,$00,$00,$20,$30,$20,$30,$20,$20,$00,$00,$00
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$0E,$26,$0E,$26,$0E,$26
		.BYTE $0E,$26,$0C,$00,$10,$10,$00,$00,$00,$00,$00,$00,$00,$00,$00,$20
		.BYTE $30,$20,$30,$00,$00,$00,$00,$00

; =============== S U B	R O U T	I N E =======================================
sub_C426:
		LDA		byte_20
		BNE		loc_C434
		LDA		byte_45E
		BEQ		loc_C434
		DEC		byte_45E
		BNE		locret_C46A
loc_C434:
		LDA		_2p_stage
		CMP		#$06
		BCS		loc_C43F
		LDA		byte_465
		BNE		locret_C46A
loc_C43F:
		LDA		_frames_counter
		AND		#$01
		BNE		locret_C46A
		INC		byte_459
		INC		byte_45A
		JSR		sub_C4E3
		BEQ		locret_C46A
		TXA
		TAY
		LDA		byte_459
		CMP		#$10
		BEQ		loc_C47B
		LDA		byte_45A
		CMP		#$80
		BEQ		loc_C46B
		LDX		_2p_stage
		CPX		#$05
		BCC		locret_C46A
		CMP		#$C0
		BEQ		loc_C48F
locret_C46A:
		RTS
; ---------------------------------------------------------------------------
loc_C46B:
		LDA		#$00
loc_C46D:
		STA		byte_541,Y
		LDA		#$01
		STA		byte_540,Y
		JSR		_obj_hndl01
		JMP		loc_C493
; ---------------------------------------------------------------------------
loc_C47B:
		LDA		#$01
loc_C47D:
		STA		byte_541,Y
		LDA		#$01
		STA		byte_540,Y
		JSR		_obj_hndl02
		JMP		loc_C493
; ---------------------------------------------------------------------------
		LDA		#$80
		BNE		loc_C46D
loc_C48F:
		LDA		#$81
		BNE		loc_C47D
loc_C493:
		LDA		byte_500
		BEQ		loc_C4C5
		BMI		loc_C4D6
		LDA		byte_520
		BEQ		loc_C4AB
		BMI		loc_C4D6
		LDA		byte_500+3
		ADC		byte_523
		AND		#$01
		BEQ		loc_C4C5
loc_C4AB:
		LDA		byte_500+$11
		BEQ		loc_C4B6
		LDA		#$00
		STA		byte_540,Y
		RTS
; ---------------------------------------------------------------------------
loc_C4B6:
		LDA		byte_500+5
loc_C4B9:
		CMP		#$40
		BCC		loc_C4D6
		CMP		#$AF
		BCS		loc_C4D6
loc_C4C1:
		STA		byte_545,Y
		RTS
; ---------------------------------------------------------------------------
loc_C4C5:
		LDA		byte_531
		BEQ		loc_C4D0
		LDA		#$00
		STA		byte_540,Y
		RTS
; ---------------------------------------------------------------------------
loc_C4D0:
		LDA		byte_525
		JMP		loc_C4B9
; ---------------------------------------------------------------------------
loc_C4D6:
		LDA		byte_465
		BEQ		loc_C4DF
		LDA		#$9E
		BNE		loc_C4C1
loc_C4DF:
		LDA		#$AE
		BNE		loc_C4C1

; =============== S U B	R O U T	I N E =======================================
sub_C4E3:
		LDX		#$00
loc_C4E5:
		LDA		byte_540,X
		BEQ		loc_C4F6
		TXA
		CLC
		ADC		#$20
		TAX
		CMP		#$60
		BCC		loc_C4E5
		LDA		#$00
		RTS
; ---------------------------------------------------------------------------
loc_C4F6:
		LDA		#$01
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_C4F9:
		STA		byte_541,Y
		STA		byte_55E,Y
		JSR		sub_C2CA
		RTS
; ---------------------------------------------------------------------------
_stage_obj_lib:
		.WORD _stage1_objs
		.WORD _stage2_objs
		.WORD _stage3_objs
		.WORD _stage4_objs
		.WORD _stage5_objs
		.WORD _stage6_objs
_substage_obj_lib:
		.WORD $0000
		.WORD _substage2_objs
		.WORD $0000
		.WORD _substage4_objs
		.WORD _substage5_objs
		.WORD $0000
_stage1_objs:
		.WORD _stage1_obj00
		.WORD _stage1_obj01
		.WORD _stage1_obj02
		.WORD _stage1_obj03
		.WORD _stage1_obj04
		.WORD _stage1_obj05
		.WORD _stage1_obj06
		.WORD _stage1_obj07
		.WORD _stage1_obj08
		.WORD _stage1_obj09
		.WORD _stage1_obj0A
_stage1_obj00:
		.BYTE $10,$AE,$01
		.BYTE $60,$46,$06
		.BYTE $FF
_stage1_obj01:
		.BYTE $60,$46,$06
		.BYTE $90,$AE,$01
		.BYTE $91,$76,$01
		.BYTE $FF
_stage1_obj02:
		.BYTE $10,$AE,$06
		.BYTE $FF
_stage1_obj03:
		.BYTE $20,$AE,$04
		.BYTE $50,$AE,$04
		.BYTE $80,$AE,$04
		.BYTE $FF
_stage1_obj04:
		.BYTE $80,$7E,$02
		.BYTE $FF
_stage1_obj05:
		.BYTE $50,$7E,$02
		.BYTE $E0,$7E,$06
		.BYTE $FF
_stage1_obj06:
		.BYTE $10,$AE,$06
		.BYTE $61,$AE,$02
		.BYTE $C1,$7E,$02
		.BYTE $FF
_stage1_obj07:
		.BYTE $C0,$AE,$01
		.BYTE $A0,$AE,$04
		.BYTE $FF
_stage1_obj08:
		.BYTE $80,$AE,$01
		.BYTE $FF
_stage1_obj09:
		.BYTE $46,$AE,$02
		.BYTE $90,$AE,$02
		.BYTE $FE,$AE,$02
_stage1_obj0A:
		.BYTE $FF
_stage2_objs:
		.WORD _stage2_obj00
		.WORD _stage2_obj01
		.WORD _stage2_obj02
		.WORD _stage2_obj03
		.WORD _stage2_obj04
		.WORD _stage2_obj05
		.WORD _stage2_obj06
		.WORD _stage2_obj07
		.WORD _stage2_obj08
		.WORD _stage2_obj09
		.WORD _stage2_obj0A
		.WORD _stage2_obj0B
		.WORD _stage2_obj0C
		.WORD _stage2_obj0D
		.WORD _stage2_obj0D
_stage2_obj00:
		.BYTE $4D,$AE,$10
		.BYTE $9F,$AE,$01
		.BYTE $C0,$AE,$06
		.BYTE $FE,$AE,$07
		.BYTE $FF
_stage2_obj01:
		.BYTE $68,$AE,$02
		.BYTE $BE,$AE,$10
		.BYTE $FF
_stage2_obj02:
		.BYTE $6D,$AE,$10
		.BYTE $76,$46,$03
		.BYTE $BA,$AE,$02
		.BYTE $FF
_stage2_obj03:
		.BYTE $10,$AE,$02
		.BYTE $40,$AE,$05
		.BYTE $C0,$6E,$06
		.BYTE $FF
_stage2_obj04:
		.BYTE $00,$AE,$02
		.BYTE $70,$6E,$07
		.BYTE $FF
_stage2_obj05:
		.BYTE $30,$AE,$04
		.BYTE $60,$AE,$04
		.BYTE $70,$AE,$05
		.BYTE $FF
_stage2_obj06:
		.BYTE $95,$46,$03
		.BYTE $78,$AE,$01
		.BYTE $90,$AE,$85
		.BYTE $AA,$AE,$01
		.BYTE $FF
_stage2_obj07:
		.BYTE $10,$AE,$04
		.BYTE $50,$AE,$04
		.BYTE $60,$AE,$02
		.BYTE $90,$AE,$04
		.BYTE $98,$AE,$02
		.BYTE $D0,$AE,$04
		.BYTE $FF
_stage2_obj08:
		.BYTE $10,$AE,$04
		.BYTE $60,$AE,$02
		.BYTE $90,$AE,$04
		.BYTE $98,$AE,$02
		.BYTE $D0,$AE,$04
		.BYTE $E7,$AE,$02
		.BYTE $FE,$AE,$82
		.BYTE $FF
_stage2_obj09:
		.BYTE $13,$AE,$02
		.BYTE $40,$6E,$07
		.BYTE $56,$AE,$02
		.BYTE $BB,$AE,$02
		.BYTE $F2,$AE,$02
		.BYTE $FF
_stage2_obj0A:
		.BYTE $FF
_stage2_obj0B:
		.BYTE $18,$46,$03
		.BYTE $28,$AE,$01
		.BYTE $58,$AE,$05
		.BYTE $78,$46,$03
		.BYTE $D5,$46,$03
		.BYTE $E5,$AE,$01
		.BYTE $FF
_stage2_obj0C:
		.BYTE $05,$AE,$00
		.BYTE $35,$46,$03
		.BYTE $3E,$AE,$10
		.BYTE $58,$AE,$01
		.BYTE $95,$46,$03
		.BYTE $C8,$AE,$02
		.BYTE $FE,$AE,$01
_stage2_obj0D:
		.BYTE $FF
_substage2_objs:
		.WORD _substage2_obj00
		.WORD _substage2_obj01
		.WORD _substage2_obj02
		.WORD _substage2_obj03
		.WORD _substage2_obj04
		.WORD _substage2_obj05
		.WORD _substage2_obj06
		.WORD _substage2_obj07
		.WORD _substage2_obj08
		.WORD _substage2_obj09
		.WORD _substage2_obj0A
		.WORD _substage2_obj0B
		.WORD _substage2_obj0C
		.WORD _substage2_obj0D
		.WORD _substage2_obj0E
_substage2_obj00:
		.BYTE $FF
_substage2_obj01:
		.BYTE $58,$9E,$06
		.BYTE $70,$5E,$07
		.BYTE $B0,$9E,$07
		.BYTE $FF
_substage2_obj02:
		.BYTE $60,$9E,$06
		.BYTE $70,$5E,$06
		.BYTE $FF
_substage2_obj03:
		.BYTE $40,$5E,$07
		.BYTE $80,$5E,$06
		.BYTE $C0,$9E,$07
		.BYTE $F0,$9E,$07
		.BYTE $FF
_substage2_obj04:
		.BYTE $C0,$9E,$02
		.BYTE $D0,$9E,$01
		.BYTE $E0,$9E,$02
		.BYTE $F0,$9E,$01
		.BYTE $FF
_substage2_obj05:
		.BYTE $01,$9E,$00
		.BYTE $20,$9E,$02
		.BYTE $B9,$9E,$04
		.BYTE $F0,$9E,$01
		.BYTE $FF
_substage2_obj06:
		.BYTE $01,$5E,$01
		.BYTE $11,$5E,$02
		.BYTE $25,$5E,$82
		.BYTE $44,$5E,$05
		.BYTE $FF
_substage2_obj07:
		.BYTE $10,$9E,$00
		.BYTE $11,$9E,$81
		.BYTE $23,$9E,$10
		.BYTE $F0,$9E,$02
		.BYTE $80,$9E,$04
		.BYTE $90,$9E,$04
		.BYTE $D0,$9E,$04
		.BYTE $03,$9E,$06
		.BYTE $FF
_substage2_obj08:
		.BYTE $03,$5E,$02
		.BYTE $20,$5E,$02
		.BYTE $35,$5E,$02
		.BYTE $90,$5E,$81
		.BYTE $60,$5E,$01
		.BYTE $FF
_substage2_obj09:
		.BYTE $FF
_substage2_obj0A:
		.BYTE $19,$9E,$01
		.BYTE $19,$5E,$82
		.BYTE $30,$5E,$00
		.BYTE $32,$9E,$82
		.BYTE $40,$5E,$02
		.BYTE $59,$9E,$02
		.BYTE $52,$5E,$02
		.BYTE $70,$5E,$02
		.BYTE $FF
_substage2_obj0B:
		.BYTE $01,$5E,$81
		.BYTE $A0,$9E,$01
		.BYTE $B2,$9E,$01
		.BYTE $FF
_substage2_obj0C:
		.BYTE $FF
_substage2_obj0D:
		.BYTE $71,$9E,$07
		.BYTE $70,$5E,$06
		.BYTE $A1,$5E,$07
		.BYTE $A0,$9E,$06
_substage2_obj0E:
		.BYTE $FF
_stage3_objs:
		.WORD _stage3_objs00
		.WORD _stage3_objs01
		.WORD _stage3_objs02
		.WORD _stage3_objs03
		.WORD _stage3_objs04
		.WORD _stage3_objs05
		.WORD _stage3_objs06
		.WORD _stage3_objs07
		.WORD _stage3_objs08
		.WORD _stage3_objs09
		.WORD _stage3_objs0A
		.WORD _stage3_objs0B
		.WORD _stage3_objs0C
		.WORD _stage3_objs0D
_stage3_objs00:
		.BYTE $20,$AE,$01
		.BYTE $32,$AE,$02
		.BYTE $80,$4E,$06
		.BYTE $42,$AE,$01
		.BYTE $B0,$7E,$05
		.BYTE $E0,$7E,$0C
		.BYTE $FF
_stage3_objs01:
		.BYTE $80,$4E,$07
		.BYTE $B0,$7E,$02
		.BYTE $B1,$AE,$02
		.BYTE $FF
_stage3_objs02:
		.BYTE $B9,$7E,$02
		.BYTE $BA,$AE,$05
		.BYTE $FF
_stage3_objs03:
		.BYTE $60,$AE,$07
		.BYTE $81,$7E,$06
		.BYTE $E0,$7E,$07
		.BYTE $B0,$AE,$04
		.BYTE $E8,$AE,$02
		.BYTE $FF
_stage3_objs04:
		.BYTE $08,$7E,$0D
		.BYTE $20,$AE,$04
		.BYTE $60,$AE,$04
		.BYTE $60,$7E,$02
		.BYTE $70,$7E,$02
		.BYTE $90,$AE,$04
		.BYTE $A0,$7E,$02
		.BYTE $B0,$7E,$02
		.BYTE $FF
_stage3_objs05:
		.BYTE $20,$7E,$02
		.BYTE $30,$7E,$82
		.BYTE $40,$AE,$04
		.BYTE $80,$AE,$04
		.BYTE $B8,$AE,$04
		.BYTE $E8,$AE,$04
		.BYTE $FF
_stage3_objs06:
		.BYTE $10,$AE,$07
		.BYTE $50,$AE,$04
		.BYTE $78,$4E,$05
		.BYTE $90,$7E,$02
		.BYTE $91,$AE,$02
		.BYTE $EF,$4E,$02
		.BYTE $D0,$7E,$02
		.BYTE $D1,$AE,$04
		.BYTE $FF
_stage3_objs07:
		.BYTE $10,$AE,$04
		.BYTE $80,$AE,$02
		.BYTE $90,$AE,$02
		.BYTE $98,$AE,$82
		.BYTE $FF
_stage3_objs08:
		.BYTE $30,$AE,$04
		.BYTE $31,$7E,$02
		.BYTE $40,$4E,$06
		.BYTE $51,$AE,$02
		.BYTE $70,$AE,$04
		.BYTE $71,$7E,$02
		.BYTE $90,$AE,$02
		.BYTE $B0,$AE,$04
		.BYTE $B1,$7E,$02
		.BYTE $D0,$AE,$02
		.BYTE $FF
_stage3_objs09:
		.BYTE $A2,$7E,$07
		.BYTE $88,$AE,$06
		.BYTE $B0,$7E,$05
		.BYTE $B1,$AE,$05
		.BYTE $FF
_stage3_objs0A:
		.BYTE $40,$4E,$02
		.BYTE $41,$7E,$02
		.BYTE $42,$AE,$02
		.BYTE $C0,$4E,$02
		.BYTE $C1,$7E,$02
		.BYTE $C2,$AE,$02
		.BYTE $D0,$4E,$02
		.BYTE $D2,$AE,$02
		.BYTE $FF
_stage3_objs0B:
		.BYTE $A0,$AE,$02
		.BYTE $C0,$AE,$02
		.BYTE $FF
_stage3_objs0C:
		.BYTE $60,$AE,$02
		.BYTE $90,$AE,$02
		.BYTE $A0,$AE,$02
		.BYTE $B0,$AE,$02
		.BYTE $B8,$AE,$82
		.BYTE $F0,$AE,$02
		.BYTE $F8,$AE,$82
_stage3_objs0D:
		.BYTE $FF
_stage4_objs:
		.WORD _stage4_obj00
		.WORD _stage4_obj01
		.WORD _stage4_obj02
		.WORD _stage4_obj03
off_3C0B6:
		.WORD _stage4_obj04
		.WORD _stage4_obj05
		.WORD _stage4_obj06
		.WORD _stage4_obj07
		.WORD _stage4_obj08
		.WORD _stage4_obj09
		.WORD _stage4_obj0A
		.WORD _stage4_obj0B
		.WORD _stage4_obj0C
		.WORD _stage4_obj0D
		.WORD _stage4_obj0E
_stage4_obj00:
		.BYTE $07,$AE,$10
		.BYTE $08,$96,$03
		.BYTE $40,$7E,$06
		.BYTE $5F,$AE,$05
		.BYTE $FE,$38,$0A
		.BYTE $FF
_stage4_obj01:
		.BYTE $70,$7E,$02
		.BYTE $71,$AE,$02
		.BYTE $C0,$AE,$82
		.BYTE $E0,$AE,$82
		.BYTE $E1,$7E,$82
		.BYTE $FF
_stage4_obj02:
		.BYTE $08,$AE,$82
		.BYTE $10,$7E,$02
		.BYTE $09,$96,$03
		.BYTE $30,$7E,$82
		.BYTE $40,$7E,$02
		.BYTE $91,$7E,$05
		.BYTE $FF
_stage4_obj03:
		.BYTE $50,$AE,$02
		.BYTE $51,$7E,$02
		.BYTE $88,$96,$03
		.BYTE $D0,$7E,$02
		.BYTE $D1,$AE,$02
		.BYTE $FF
_stage4_obj04:
		.BYTE $10,$AE,$07
		.BYTE $11,$7E,$06
		.BYTE $08,$96,$03
		.BYTE $60,$AE,$85
		.BYTE $68,$AE,$05
		.BYTE $88,$96,$03
		.BYTE $A0,$AE,$02
		.BYTE $B0,$AE,$02
		.BYTE $FF
_stage4_obj05:
		.BYTE $08,$96,$03
		.BYTE $60,$7E,$02
		.BYTE $80,$AE,$04
		.BYTE $FF
_stage4_obj06:
		.BYTE $20,$4E,$07
		.BYTE $21,$AE,$06
		.BYTE $30,$AE,$04
		.BYTE $60,$AE,$04
		.BYTE $98,$AE,$04
		.BYTE $80,$AE,$02
		.BYTE $98,$AE,$02
		.BYTE $A0,$AE,$10
		.BYTE $B0,$AE,$02
		.BYTE $40,$4E,$02
		.BYTE $50,$4E,$02
		.BYTE $60,$4E,$02
		.BYTE $FF
_stage4_obj07:
		.BYTE $70,$4E,$05
		.BYTE $71,$AE,$05
		.BYTE $A0,$4E,$02
		.BYTE $A1,$AE,$82
		.BYTE $B1,$AE,$02
_stage4_obj08:
		.BYTE $FF
_stage4_obj09:
		.BYTE $30,$AE,$04
		.BYTE $60,$AE,$04
		.BYTE $B0,$AE,$02
		.BYTE $C0,$AE,$02
		.BYTE $D0,$AE,$02
		.BYTE $FF
_stage4_obj0A:
		.BYTE $70,$7E,$05
		.BYTE $71,$AE,$02
		.BYTE $80,$7E,$02
		.BYTE $D0,$AE,$02
		.BYTE $FF
_stage4_obj0B:
		.BYTE $33,$AE,$05
		.BYTE $46,$AE,$02
		.BYTE $CB,$7E,$05
		.BYTE $DB,$7E,$02
		.BYTE $E0,$AE,$10
		.BYTE $FF
_stage4_obj0C:
		.BYTE $50,$7E,$02
		.BYTE $60,$7E,$02
		.BYTE $7B,$7E,$02
		.BYTE $61,$AE,$02
		.BYTE $FF
_stage4_obj0D:
		.BYTE $EE,$AE,$05
		.BYTE $EF,$AE,$85
_stage4_obj0E:
		.BYTE $FF
_substage4_objs:
		.WORD _substage4_obj00
		.WORD _substage4_obj01
		.WORD _substage4_obj02
		.WORD _substage4_obj03
		.WORD _substage4_obj04
		.WORD _substage4_obj05
		.WORD _substage4_obj06
		.WORD _substage4_obj07
		.WORD _substage4_obj08
		.WORD _substage4_obj09
		.WORD _substage4_obj0A
		.WORD _substage4_obj0B
		.WORD _substage4_obj0C
		.WORD _substage4_obj0D
		.WORD _substage4_obj0D
_substage4_obj00:
		.BYTE $D4,$9E,$05
		.BYTE $C8,$5E,$06
		.BYTE $70,$5E,$06
		.BYTE $A0,$9E,$07
		.BYTE $E0,$9E,$07
		.BYTE $FF
_substage4_obj01:
		.BYTE $20,$9E,$82
		.BYTE $80,$9E,$02
		.BYTE $90,$9E,$01
		.BYTE $A0,$9E,$02
		.BYTE $14,$5E,$02
		.BYTE $45,$5E,$02
		.BYTE $50,$5E,$07
		.BYTE $B0,$5E,$02
		.BYTE $FF
_substage4_obj02:
		.BYTE $3F,$5E,$02
		.BYTE $7F,$5E,$02
		.BYTE $BB,$5E,$02
		.BYTE $F0,$5E,$06
		.BYTE $65,$9E,$05
		.BYTE $75,$9E,$02
		.BYTE $98,$9E,$02
		.BYTE $B3,$9E,$02
		.BYTE $FF
_substage4_obj03:
		.BYTE $30,$9E,$07
		.BYTE $70,$5E,$02
		.BYTE $90,$9E,$01
		.BYTE $88,$5E,$02
		.BYTE $E0,$9E,$05
		.BYTE $A0,$5E,$02
		.BYTE $B8,$5E,$01
		.BYTE $E0,$9E,$06
		.BYTE $FF
_substage4_obj04:
		.BYTE $08,$9E,$01
		.BYTE $20,$9E,$01
		.BYTE $25,$9E,$04
		.BYTE $30,$9E,$02
		.BYTE $3B,$9E,$02
		.BYTE $45,$9E,$02
		.BYTE $60,$9E,$04
		.BYTE $60,$9E,$85
		.BYTE $FF
_substage4_obj05:
		.BYTE $08,$5E,$02
		.BYTE $18,$5E,$02
		.BYTE $28,$5E,$02
		.BYTE $38,$5E,$02
		.BYTE $48,$5E,$02
		.BYTE $58,$5E,$02
		.BYTE $68,$5E,$02
		.BYTE $FF
_substage4_obj06:
		.BYTE $50,$5E,$02
		.BYTE $58,$5E,$02
		.BYTE $66,$5E,$02
		.BYTE $74,$5E,$02
		.BYTE $82,$5E,$02
		.BYTE $90,$5E,$02
		.BYTE $98,$5E,$02
		.BYTE $A6,$5E,$02
		.BYTE $FF
_substage4_obj07:
		.BYTE $01,$5E,$07
		.BYTE $05,$9E,$81
		.BYTE $20,$9E,$05
		.BYTE $40,$9E,$06
		.BYTE $90,$9E,$02
		.BYTE $80,$9E,$07
		.BYTE $D0,$9E,$04
		.BYTE $F0,$9E,$04
		.BYTE $FF
_substage4_obj08:
		.BYTE $48,$5E,$02
		.BYTE $60,$5E,$02
		.BYTE $78,$5E,$02
		.BYTE $60,$5E,$00
		.BYTE $80,$9E,$01
		.BYTE $D0,$5E,$02
		.BYTE $E0,$5E,$02
		.BYTE $F0,$5E,$02
		.BYTE $FF
_substage4_obj09:
		.BYTE $01,$5E,$02
		.BYTE $11,$5E,$02
		.BYTE $9B,$5E,$02
		.BYTE $D0,$5E,$02
		.BYTE $FF
_substage4_obj0A:
		.BYTE $1B,$9E,$02
		.BYTE $40,$9E,$01
		.BYTE $40,$5E,$01
		.BYTE $D0,$5E,$05
		.BYTE $80,$9E,$02
		.BYTE $B0,$9E,$02
		.BYTE $20,$5E,$06
		.BYTE $FF
_substage4_obj0B:
		.BYTE $3B,$5E,$02
		.BYTE $7B,$5E,$02
		.BYTE $50,$9E,$04
		.BYTE $BB,$5E,$02
		.BYTE $EB,$5E,$02
		.BYTE $80,$9E,$04
		.BYTE $B0,$9E,$04
		.BYTE $E0,$9E,$04
		.BYTE $FF
_substage4_obj0C:
		.BYTE $10,$9E,$01
		.BYTE $20,$9E,$00
		.BYTE $5B,$5E,$02
		.BYTE $80,$9E,$02
		.BYTE $80,$5E,$07
_substage4_obj0D:
		.BYTE $FF
_stage5_objs:
		.WORD _stage5_objs00
		.WORD _stage5_objs01
		.WORD _stage5_objs02
		.WORD _stage5_objs03
		.WORD _stage5_objs04
		.WORD _stage5_objs05
		.WORD _stage5_objs06
		.WORD _stage5_objs07
		.WORD _stage5_objs08
		.WORD _stage5_objs09
		.WORD _stage5_objs0A
		.WORD _stage5_objs0B
		.WORD _stage5_objs0C
		.WORD _stage5_objs0D
		.WORD _stage5_objs0E
		.WORD _stage5_objs0F
		.WORD _stage5_objs10
_stage5_objs00:
		.BYTE $30,$7E,$05
		.BYTE $3F,$AE,$10
		.BYTE $48,$4E,$06
		.BYTE $70,$AE,$02
		.BYTE $C8,$7E,$06
		.BYTE $E0,$AE,$02
		.BYTE $F0,$AE,$82
		.BYTE $FF
_stage5_objs01:
		.BYTE $48,$4E,$07
		.BYTE $40,$7E,$05
		.BYTE $60,$AE,$02
		.BYTE $B8,$AE,$10
		.BYTE $E0,$AE,$02
		.BYTE $F0,$AE,$82
		.BYTE $FF
_stage5_objs02:
		.BYTE $60,$AE,$05
		.BYTE $C0,$AE,$07
		.BYTE $C1,$AE,$07
		.BYTE $C2,$AE,$06
		.BYTE $FE,$AE,$05
		.BYTE $FF
_stage5_objs03:
		.BYTE $B8,$AE,$10
		.BYTE $70,$AE,$02
		.BYTE $FF
_stage5_objs04:
		.BYTE $C0,$AE,$05
		.BYTE $FF
_stage5_objs05:
		.BYTE $40,$AE,$10
		.BYTE $C0,$7E,$07
		.BYTE $FF
_stage5_objs06:
		.BYTE $50,$AE,$02
		.BYTE $A0,$AE,$04
		.BYTE $D0,$AE,$04
		.BYTE $F0,$AE,$02
		.BYTE $FF
_stage5_objs07:
		.BYTE $00,$AE,$04
		.BYTE $40,$AE,$04
		.BYTE $80,$AE,$04
		.BYTE $C0,$AE,$04
		.BYTE $20,$AE,$02
		.BYTE $50,$AE,$02
		.BYTE $90,$AE,$05
		.BYTE $D0,$AE,$02
		.BYTE $FE,$AE,$02
		.BYTE $FF
_stage5_objs08:
		.BYTE $00,$AE,$04
		.BYTE $40,$AE,$04
		.BYTE $80,$AE,$04
		.BYTE $C0,$AE,$04
		.BYTE $40,$AE,$05
		.BYTE $50,$AE,$02
		.BYTE $90,$AE,$02
		.BYTE $D0,$AE,$02
		.BYTE $FE,$AE,$01
		.BYTE $FF
_stage5_objs09:
		.BYTE $10,$AE,$07
		.BYTE $00,$AE,$04
		.BYTE $40,$AE,$04
		.BYTE $80,$AE,$04
		.BYTE $C0,$AE,$04
		.BYTE $38,$AE,$02
		.BYTE $A8,$AE,$02
		.BYTE $D0,$AE,$02
		.BYTE $E0,$AE,$02
		.BYTE $F0,$7E,$05
_stage5_objs0A:
		.BYTE $E0,$AE,$10
		.BYTE $FF
_stage5_objs0B:
		.BYTE $A0,$AE,$05
		.BYTE $B0,$AE,$02
		.BYTE $C0,$AE,$01
		.BYTE $D2,$AE,$02
_stage5_objs0C:
		.BYTE $FF
_stage5_objs0D:
		.BYTE $A0,$AE,$05
		.BYTE $D8,$AE,$10
		.BYTE $FF
_stage5_objs0E:
		.BYTE $80,$AE,$02
		.BYTE $8E,$AE,$02
		.BYTE $9C,$AE,$02
		.BYTE $D0,$AE,$02
		.BYTE $E2,$AE,$02
		.BYTE $F4,$AE,$02
		.BYTE $FF
_stage5_objs0F:
		.BYTE $40,$AE,$02
		.BYTE $60,$AE,$02
		.BYTE $A0,$AE,$82
		.BYTE $E3,$AE,$02
		.BYTE $F3,$AE,$82
_stage5_objs10:
		.BYTE $FF
_substage5_objs:
		.WORD _substage5_obj00
		.WORD _substage5_obj01
		.WORD _substage5_obj02
		.WORD _substage5_obj03
		.WORD _substage5_obj04
		.WORD _substage5_obj05
		.WORD _substage5_obj06
		.WORD _substage5_obj07
		.WORD _substage5_obj08
		.WORD _substage5_obj09
		.WORD _substage5_obj0A
		.WORD _substage5_obj0B
		.WORD _substage5_obj0C
		.WORD _substage5_obj0D
		.WORD _substage5_obj0E
off_441B0:
		.WORD _substage5_obj0F
		.WORD _substage5_obj0F
_substage5_obj00:
		.BYTE $B0,$5E,$07
		.BYTE $FF
_substage5_obj01:
		.BYTE $20,$9E,$06
		.BYTE $80,$9E,$06
		.BYTE $D0,$9E,$06
		.BYTE $03,$5E,$07
		.BYTE $63,$5E,$07
		.BYTE $B3,$5E,$07
		.BYTE $FF
_substage5_obj02:
		.BYTE $80,$9E,$01
		.BYTE $A0,$9E,$01
		.BYTE $70,$9E,$05
		.BYTE $F1,$5E,$02
		.BYTE $90,$5E,$01
		.BYTE $FF
_substage5_obj03:
		.BYTE $41,$9E,$02
		.BYTE $01,$5E,$02
		.BYTE $11,$5E,$02
		.BYTE $21,$5E,$02
		.BYTE $31,$5E,$02
		.BYTE $51,$5E,$02
		.BYTE $70,$9E,$02
		.BYTE $A0,$9E,$02
		.BYTE $FF
_substage5_obj04:
		.BYTE $00,$9E,$04
		.BYTE $30,$9E,$04
		.BYTE $01,$9E,$82
		.BYTE $32,$9E,$82
		.BYTE $C0,$5E,$00
		.BYTE $D0,$5E,$02
		.BYTE $F0,$5E,$01
		.BYTE $FF
_substage5_obj05:
		.BYTE $20,$9E,$05
		.BYTE $40,$9E,$04
		.BYTE $70,$9E,$02
		.BYTE $A0,$9E,$04
		.BYTE $80,$9E,$06
		.BYTE $60,$9E,$02
		.BYTE $90,$9E,$02
		.BYTE $FF
_substage5_obj06:
		.BYTE $00,$9E,$07
		.BYTE $10,$9E,$00
		.BYTE $90,$5E,$00
		.BYTE $A0,$5E,$01
		.BYTE $B0,$5E,$02
		.BYTE $FF
_substage5_obj07:
		.BYTE $28,$9E,$04
		.BYTE $55,$9E,$02
		.BYTE $90,$9E,$02
		.BYTE $68,$9E,$04
		.BYTE $D0,$9E,$02
		.BYTE $A8,$9E,$04
		.BYTE $FF
_substage5_obj08:
		.BYTE $30,$5E,$02
		.BYTE $38,$5E,$02
		.BYTE $46,$5E,$02
		.BYTE $54,$5E,$02
		.BYTE $62,$5E,$02
		.BYTE $70,$5E,$02
		.BYTE $78,$5E,$02
		.BYTE $20,$9E,$06
		.BYTE $FF
_substage5_obj09:
		.BYTE $40,$5E,$01
		.BYTE $50,$5E,$01
		.BYTE $60,$5E,$01
		.BYTE $70,$5E,$01
		.BYTE $80,$5E,$01
		.BYTE $90,$5E,$01
		.BYTE $A0,$5E,$01
		.BYTE $B0,$5E,$01
		.BYTE $FF
_substage5_obj0A:
		.BYTE $40,$9E,$01
		.BYTE $50,$9E,$01
		.BYTE $60,$9E,$01
		.BYTE $70,$9E,$01
		.BYTE $80,$9E,$02
		.BYTE $90,$9E,$02
		.BYTE $A2,$9E,$01
		.BYTE $B0,$5E,$01
		.BYTE $FF
_substage5_obj0B:
		.BYTE $20,$9E,$04
		.BYTE $47,$9E,$02
		.BYTE $50,$9E,$04
		.BYTE $80,$9E,$04
		.BYTE $B0,$9E,$04
		.BYTE $70,$9E,$02
		.BYTE $A0,$9E,$02
		.BYTE $01,$5E,$06
		.BYTE $FF
_substage5_obj0C:
		.BYTE $01,$9E,$07
		.BYTE $40,$9E,$04
		.BYTE $70,$9E,$04
		.BYTE $A0,$9E,$04
		.BYTE $C0,$9E,$02
		.BYTE $D0,$9E,$04
		.BYTE $90,$9E,$02
		.BYTE $F0,$9E,$02
		.BYTE $FF
_substage5_obj0D:
		.BYTE $F0,$5E,$02
		.BYTE $80,$5E,$02
		.BYTE $90,$5E,$02
		.BYTE $C0,$5E,$02
		.BYTE $E0,$5E,$02
		.BYTE $60,$9E,$04
		.BYTE $A0,$9E,$04
		.BYTE $C0,$9E,$04
		.BYTE $FF
_substage5_obj0E:
		.BYTE $25,$9E,$85
		.BYTE $20,$9E,$02
		.BYTE $40,$9E,$82
		.BYTE $3E,$9E,$07
		.BYTE $60,$9E,$02
		.BYTE $70,$9E,$01
_substage5_obj0F:
		.BYTE $FF
_stage6_objs:
		.WORD _stage6_obj00
		.WORD _stage6_obj01
		.WORD _stage6_obj02
		.WORD _stage6_obj03
		.WORD _stage6_obj04
		.WORD _stage6_obj05
		.WORD _stage6_obj06
		.WORD _stage6_obj07
		.WORD _stage6_obj08
		.WORD _stage6_obj09
		.WORD _stage6_obj0A
		.WORD _stage6_obj0B
		.WORD _stage6_obj0C
		.WORD _stage6_obj0D
		.WORD _stage6_obj0E
		.WORD _stage6_obj0F
		.WORD _stage6_obj10
		.WORD _stage6_obj11
		.WORD _stage6_obj12
_stage6_obj00:
		.BYTE $80,$AE,$02
		.BYTE $A0,$AE,$02
		.BYTE $C0,$AE,$02
		.BYTE $FE,$4E,$02
		.BYTE $FF
_stage6_obj01:
		.BYTE $1E,$4E,$01
		.BYTE $3E,$4E,$02
		.BYTE $F0,$AE,$01
		.BYTE $FF
_stage6_obj02:
		.BYTE $20,$AE,$01
		.BYTE $50,$AE,$02
		.BYTE $80,$AE,$02
		.BYTE $90,$4E,$02
		.BYTE $B0,$4E,$02
		.BYTE $D0,$4E,$02
		.BYTE $FF
_stage6_obj03:
		.BYTE $20,$AE,$01
		.BYTE $40,$AE,$02
		.BYTE $69,$AE,$02
		.BYTE $70,$4E,$05
		.BYTE $89,$AE,$01
		.BYTE $FF
_stage6_obj04:
		.BYTE $FF
_stage6_obj05:
		.BYTE $30,$AE,$04
		.BYTE $40,$4E,$02
		.BYTE $50,$AE,$82
		.BYTE $60,$AE,$04
		.BYTE $68,$4E,$05
		.BYTE $90,$AE,$04
		.BYTE $A0,$4E,$02
		.BYTE $B0,$AE,$82
		.BYTE $C0,$AE,$04
		.BYTE $F0,$AE,$04
		.BYTE $FF
_stage6_obj06:
		.BYTE $20,$AE,$04
		.BYTE $30,$4E,$02
		.BYTE $58,$4E,$02
		.BYTE $80,$4E,$01
		.BYTE $A8,$4E,$02
		.BYTE $E0,$AE,$02
		.BYTE $FF
_stage6_obj07:
		.BYTE $FF
_stage6_obj08:
		.BYTE $10,$4E,$05
		.BYTE $40,$4E,$02
		.BYTE $80,$4E,$01
		.BYTE $81,$AE,$05
		.BYTE $98,$AE,$02
		.BYTE $F0,$AE,$82
		.BYTE $FF
_stage6_obj09:
		.BYTE $50,$AE,$01
		.BYTE $51,$4E,$02
		.BYTE $52,$4E,$82
		.BYTE $82,$4E,$82
		.BYTE $D2,$AE,$01
		.BYTE $FF
_stage6_obj0A:
		.BYTE $00,$4E,$02
		.BYTE $60,$4E,$05
		.BYTE $61,$AE,$05
		.BYTE $FF
_stage6_obj0B:
		.BYTE $40,$AE,$01
		.BYTE $80,$AE,$01
		.BYTE $C0,$4E,$01
		.BYTE $FE,$4E,$01
		.BYTE $FF
_stage6_obj0C:
		.BYTE $80,$AE,$05
		.BYTE $FF
_stage6_obj0D:
		.BYTE $00,$4E,$02
		.BYTE $08,$4E,$82
		.BYTE $50,$AE,$02
		.BYTE $58,$AE,$82
		.BYTE $E0,$AE,$01
		.BYTE $FF
_stage6_obj0E:
		.BYTE $20,$AE,$01
		.BYTE $50,$AE,$01
		.BYTE $70,$AE,$01
		.BYTE $90,$4E,$02
		.BYTE $B0,$4E,$01
		.BYTE $D0,$4E,$02
		.BYTE $FF
_stage6_obj0F:
		.BYTE $20,$4E,$01
		.BYTE $50,$4E,$01
		.BYTE $51,$AE,$02
		.BYTE $60,$AE,$82
		.BYTE $C0,$AE,$82
		.BYTE $E0,$AE,$02
		.BYTE $FF
_stage6_obj10:
		.BYTE $88,$AE,$01
		.BYTE $A8,$AE,$01
		.BYTE $D8,$AE,$02
		.BYTE $C0,$1D,$0E
		.BYTE $98,$AE,$82
		.BYTE $F8,$1D,$0E
		.BYTE $FF
_stage6_obj11:
		.BYTE $18,$AE,$01
		.BYTE $30,$1D,$0E
		.BYTE $38,$AE,$00
		.BYTE $68,$1D,$0E
		.BYTE $69,$AE,$81
		.BYTE $88,$AE,$82
		.BYTE $A0,$1D,$0E
		.BYTE $A1,$AE,$00
		.BYTE $B8,$AE,$01
		.BYTE $D8,$1D,$0E
		.BYTE $FF
_stage6_obj12:
		.BYTE $FE,$AE,$0F
		.BYTE $FF

; =============== S U B	R O U T	I N E =======================================
sub_2BD41:
		LDA		byte_55D,Y
		SEC
		SBC		#$01
		STA		byte_55D,Y
		BNE		loc_2BD59
		LDA		#$30
		STA		byte_55D,Y
		LDA		#$09
		JSR		_apu_load_safe
		JSR		sub_C523
loc_2BD59:
		LDA		byte_543,Y
		CMP		#$E0
		BCS		loc_2BDB3
		CMP		#$10
		BCC		loc_2BDBC
loc_2BD64:
		LDA		_frames_counter
		CMP		#$48
		BCC		loc_2BDB0
		JSR		sub_BE3A
		LDA		byte_543,Y
		LDX		byte_8
		CLC
		SBC		byte_500+3,X
		BCS		loc_2BD7D
		EOR		#$FF
		CLC
		ADC		#$01
loc_2BD7D:
		CMP		#$02
		BCS		loc_2BDB0
		LDA		#$08
		JSR		_apu_load_safe
		LDA		#$13
		STA		byte_541,Y
		STA		byte_55E,Y
		JSR		sub_C2CA
		LDA		byte_45B
		BEQ		loc_2BDC9
		LDA		#$00
		STA		byte_45B
		LDA		#$02
		LDX		#$00
loc_2BD9F:
		STA		byte_547,Y
		TXA
		STA		byte_548,Y
		LDA		#$04
		STA		byte_549,Y
		LDA		#$80
		STA		byte_54A,Y
loc_2BDB0:
		JMP		sub_BFEA
; ---------------------------------------------------------------------------
loc_2BDB3:
		LDA		#$01
		STA		byte_54B,Y
		LDA		#$FE
		BNE		loc_2BDC3
loc_2BDBC:
		LDA		#$00
		STA		byte_54B,Y
		LDA		#$02
loc_2BDC3:
		STA		byte_547,Y
		JMP		loc_2BD64
; ---------------------------------------------------------------------------
loc_2BDC9:
		LDA		#$01
		STA		byte_45B
		LDA		#$FE
		LDX		#$00
		BEQ		loc_2BD9F

; =============== S U B	R O U T	I N E =======================================
sub_2BDD4:
		LDA		byte_55C,Y
		BEQ		loc_2BDE8
		SEC
		SBC		#$01
		STA		byte_55C,Y
		BNE		loc_2BDB0
		LDA		#$FC
		STA		byte_549,Y
		BNE		loc_2BDB0
loc_2BDE8:
		LDA		byte_545,Y
		CMP		#$40
		BCS		loc_2BDB0
		LDA		#$11
		STA		byte_541,Y
		STA		byte_55E,Y
		JSR		sub_C2CA
		JSR		sub_C2BB
		LDA		_frames_counter
		AND		#$01
		BEQ		loc_2BE07
		LDA		#$FE
		BNE		loc_2BE09
loc_2BE07:
		LDA		#$02
loc_2BE09:
		STA		byte_547,Y
		BNE		loc_2BDB0

; =============== S U B	R O U T	I N E =======================================
sub_2BE0E:
		LDA		byte_545,Y
		CMP		#$90
		BCC		loc_2BDB0
		JSR		sub_C2BB
		LDA		#$12
		STA		byte_541,Y
		STA		byte_55E,Y
		JSR		sub_C2CA
		LDA		_frames_counter
		ORA		#$1F
		AND		#$7F
		CMP		#$50
		BCC		loc_2BE2F
		LDA		#$50
loc_2BE2F:
		STA		byte_55C,Y
		JMP		loc_2BDB0

; =============== S U B	R O U T	I N E =======================================
_obj_hndl09:
		JSR		sub_C240
		LDA		#$20
		STA		byte_559,Y
		JSR		sub_C2BB
		STA		byte_54E,Y
		LDA		#$28
		JSR		sub_C24C
		LDA		#$48
		STA		byte_545,Y
		LDA		#$30
		STA		byte_55D,Y
		LDA		#$11
		JMP		sub_C4F9

; =============== S U B	R O U T	I N E =======================================
sub_34386:
		JSR		sub_BE99
		CMP		#$00
		BEQ		loc_34390
		JMP		sub_BFEA
; ---------------------------------------------------------------------------
loc_34390:
		LDA		byte_541,Y
		STA		byte_55E,Y
		LDA		#$00
		STA		byte_552,Y
		JSR		sub_BEC0
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
_obj_hndl0A:
		JSR		sub_C240
		LDA		#$10
		STA		byte_559,Y
		LDA		#$30
		JSR		sub_C24C
		LDA		#$14
		JSR		sub_C4F9
		LDA		#$03
		STA		byte_54E,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_3BFAF:
		LDA		_frames_counter
		AND		#$03
		BNE		loc_3BFBA
		LDA		#$04
		JSR		_apu_load_safe
loc_3BFBA:
		LDA		byte_55D,Y
		SEC
		SBC		#$01
		STA		byte_55D,Y
		BNE		loc_3BFD2
		LDA		#$40
		STA		byte_55D,Y
		LDA		#$09
		JSR		_apu_load_safe
		JSR		sub_C523
loc_3BFD2:
		LDA		byte_547,Y
		BPL		loc_3BFE0
		LDA		byte_543,Y
		CMP		#$10
		BCC		loc_3BFEA
		BCS		loc_3BFE7
loc_3BFE0:
		LDA		byte_543,Y
		CMP		#$E0
		BCS		loc_3BFEE
loc_3BFE7:
		JMP		sub_BFEA
; ---------------------------------------------------------------------------
loc_3BFEA:
		LDA		#$01
		BNE		loc_3BFF0
loc_3BFEE:
		LDA		#$FF
loc_3BFF0:
		STA		byte_55A,Y
		LDA		#$18
		STA		byte_541,Y
		STA		byte_55E,Y
		JSR		sub_C2BB
		LDA		byte_55C,Y
		BNE		loc_3C00F
		LDA		#$48
loc_3C005:
		STA		byte_54A,Y
		LDA		#$01
		STA		byte_55B,Y
		BNE		loc_3BFE7
loc_3C00F:
		LDA		#$FF
loc_3C011:
		STA		byte_549,Y
		LDA		#$B4
		BNE		loc_3C005

; =============== S U B	R O U T	I N E =======================================
sub_3C018:
		LDA		_frames_counter
		AND		#$03
		BNE		loc_3C023
		LDA		#$04
		JSR		_apu_load_safe
loc_3C023:
		LDX		byte_545,Y
		LDA		byte_55C,Y
		BEQ		loc_3C036
		CPX		#$58
		BCS		loc_3C042
		JSR		sub_C2BB
		LDA		#$00
		BEQ		loc_3C03F
loc_3C036:
		CPX		#$A0
		BCC		loc_3C042
		JSR		sub_C2BB
		LDA		#$01
loc_3C03F:
		STA		byte_55C,Y
loc_3C042:
		LDA		#$01
		CLC
		ADC		byte_55B,Y
		STA		byte_55B,Y
		CMP		#$10
		BEQ		loc_3C05A
		CMP		#$30
		BEQ		loc_3C060
		CMP		#$50
		BEQ		loc_3C06F
loc_3C057:
		JMP		sub_BFEA
; ---------------------------------------------------------------------------
loc_3C05A:
		JSR		sub_C2CA
		JMP		loc_3C057
; ---------------------------------------------------------------------------
loc_3C060:
		LDA		#$00
		LDX		byte_54B,Y
		BNE		loc_3C069
		LDA		#$01
loc_3C069:
		STA		byte_54B,Y
		JMP		loc_3C057
; ---------------------------------------------------------------------------
loc_3C06F:
		LDA		#$17
		STA		byte_541,Y
		STA		byte_55E,Y
		JSR		sub_C2CA
		JSR		sub_C2BB
		LDA		byte_55A,Y
		STA		byte_547,Y
		JMP		loc_3C057

; =============== S U B	R O U T	I N E =======================================
_obj_hndl0C:
		JSR		sub_C240
		LDA		#$80
		STA		byte_559,Y
		LDA		#$40
		JSR		sub_C24C
		LDA		#$00
		STA		byte_54E,Y
		STA		byte_55B,Y
		STA		byte_55C,Y
		STA		byte_549
		STA		byte_54A
		LDA		#$38
		STA		byte_55D,Y
		LDA		#$17
		JMP		sub_C4F9

; =============== S U B	R O U T	I N E =======================================
sub_4C23D:
		LDX		#$00
		LDA		byte_54C,Y
		BEQ		loc_4C246
		LDX		#$20
loc_4C246:
		LDA		byte_500+3,X
		SEC
loc_4C24A:
		SBC		byte_543,Y
		BCS		loc_4C254
		EOR		#$FF
		CLC
		ADC		#$01
loc_4C254:
		CMP		#$40
		BCS		loc_4C276
		LDA		byte_55D,Y
		SEC
		SBC		#$01
		STA		byte_55D,Y
		BNE		loc_4C276
		LDA		#$58
loc_4C265:
		STA		byte_54F,Y
		LDA		#$10
		STA		byte_55D,Y
loc_4C26D:
		LDA		byte_541,Y
		CLC
		ADC		#$01
		STA		byte_541,Y
loc_4C276:
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_4C279:
		LDA		byte_55D,Y
		SEC
		SBC		#$01
		STA		byte_55D,Y
		BNE		loc_4C276
		LDA		#$59
		BNE		loc_4C265

; =============== S U B	R O U T	I N E =======================================
sub_4C288:
		LDA		byte_55D,Y
		SEC
		SBC		#$01
		STA		byte_55D,Y
		BNE		loc_4C276
		LDA		#$20
		STA		byte_55D,Y
		JSR		sub_4C2FC
		BNE		loc_4C26D
		LDA		#$0A
		JSR		_apu_load_safe
		LDX		#$00
		LDA		byte_54C,Y
		BEQ		loc_4C2AB
		LDX		#$20
loc_4C2AB:
		LDA		byte_500+3,X
		SEC
		SBC		byte_543,Y
		BCS		loc_4C2B9
		EOR		#$FF
		CLC
		ADC		#$01
loc_4C2B9:
		CMP		#$0E
		BCC		loc_4C2D8
		CMP		#$24
		BCC		loc_4C2E9
		LDX		byte_14
		LDA		#$01
		STA		byte_647,X
		LDA		#$00
		STA		byte_648,X
		JSR		sub_4C342
		LDA		#$5C
loc_4C2D2:
		JSR		sub_4C317
		JMP		loc_4C26D
; ---------------------------------------------------------------------------
loc_4C2D8:
		LDX		byte_14
		LDA		#$00
		STA		byte_647,X
		STA		byte_648,X
		JSR		sub_4C342
		LDA		#$5A
		BNE		loc_4C2D2
loc_4C2E9:
		LDX		byte_14
loc_4C2EB:
		LDA		#$00
		STA		byte_647,X
		LDA		#$80
		STA		byte_648,X
		JSR		sub_4C342
		LDA		#$5B
		BNE		loc_4C2D2

; =============== S U B	R O U T	I N E =======================================
sub_4C2FC:
		LDX		#$00
loc_4C2FE:
		LDA		byte_640,X
		BEQ		loc_4C30F
		CPX		#$60
		BEQ		loc_4C314
		TXA
		CLC
		ADC		#$20
		TAX
		JMP		loc_4C2FE
; ---------------------------------------------------------------------------
loc_4C30F:
		STX		byte_14
		LDA		#$00
		RTS
; ---------------------------------------------------------------------------
loc_4C314:
		LDA		#$01
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_4C317:
		LDX		byte_14
		STA		byte_64F,X
		LDA		#$01
		STA		byte_640,X
		LDA		#$05
		STA		byte_641,X
		LDA		#$00
		STA		byte_64E,X
		LDA		byte_543,Y
		STA		byte_643,X
		LDA		byte_545,Y
		STA		byte_645,X
		LDA		#$03
		STA		byte_649,X
		LDA		#$80
		STA		byte_64A,X
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_4C342:
		LDX		byte_14
		LDA		#$00
		STA		byte_64B,X
		LDX		#$00
		LDA		byte_54C,Y
		BEQ		loc_4C352
		LDX		#$20
loc_4C352:
		LDA		byte_500+3,X
		SEC
		CMP		byte_543,Y
		BCS		locret_4C37E
		LDX		byte_14
		LDA		byte_648,X
		EOR		#$FF
		CLC
		ADC		#$01
		STA		byte_648,X
		LDA		byte_647,X
		EOR		#$FF
		CLC
		STA		byte_647,X
		LDA		byte_648,X
		BNE		loc_4C379
		INC		byte_647,X
loc_4C379:
		LDA		#$01
		STA		byte_64B,X
locret_4C37E:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_4C37F:
		LDA		byte_55D,Y
		SEC
		SBC		#$01
		STA		byte_55D,Y
		BNE		loc_4C399
		LDA		#$10
		STA		byte_55D,Y
		LDA		#$1F
		STA		byte_541,Y
		LDA		#$57
		STA		byte_54F,Y
loc_4C399:
		JMP		loc_4C276

; =============== S U B	R O U T	I N E =======================================
sub_4C39C:
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
_obj_hndl0F:
		LDA		#$02
		STA		byte_559,Y
		JSR		sub_C2BB
		LDA		#$FF
		STA		byte_543,Y
		LDA		#$03
		STA		byte_55D,Y
		LDA		#$02
		STA		byte_54E,Y
		LDA		#$00
		STA		byte_54B,Y
		STA		byte_552,Y
		STA		byte_553,Y
		LDA		#$57
		STA		byte_54F,Y
		LDA		#$1F
		STA		byte_541,Y
		STA		byte_55E,Y
		LDA		_1p_lives
		BEQ		sub_4C3DE
		LDA		_2p_lives
		BEQ		sub_4C3E2
		LDA		_frames_counter
		AND		#$01

; =============== S U B	R O U T	I N E =======================================
sub_4C3DA:
		STA		byte_54C,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_4C3DE:
		LDA		#$01
		BNE		sub_4C3DA

; =============== S U B	R O U T	I N E =======================================
sub_4C3E2:
		LDA		#$00
		BEQ		sub_4C3DA

; =============== S U B	R O U T	I N E =======================================
_obj_hndl10:
		LDA		#$23
		STA		byte_541,Y
		LDA		#$0C
		STA		byte_556,Y
		LDA		#$00
		STA		byte_54F,Y
		JSR		sub_C2BB
		LDA		#$FF
		STA		byte_543,Y
		RTS
; ---------------------------------------------------------------------------
		SECTION_END "STAGE object managerA"

		SECTION_START
; =============== S U B	R O U T	I N E =======================================
_ending00:
		JSR		_obj_bufs_reset
		LDA		#$00
		STA		byte_540
		INC		_sub_sub_idx
		LDA		#$B0
		STA		byte_6C4
		JSR		_type_msg_ending_fetch
		RTS

; =============== S U B	R O U T	I N E =======================================
_ending01:
		JSR		_type_msg_handler
		LDA		_frames_counter
		AND		#$03
		BNE		locret_53EC1
		DEC		byte_6C4
		BNE		locret_53EC1
		LDA		_2p_stage
		CMP		#$08
		BCC		loc_53EBF
		JMP		sub_8A5D
; ---------------------------------------------------------------------------
loc_53EBF:
		INC		_sub_sub_idx
locret_53EC1:
		RTS

; =============== S U B	R O U T	I N E =======================================
_ending04:
		LDX		#$00

; =============== S U B	R O U T	I N E =======================================
sub_53EC4:
		LDA		byte_55F,X
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD sub_53ED8
		.WORD sub_53FCE
		.WORD sub_53FF2
		.WORD sub_5402E
		.WORD sub_54049
		.WORD sub_54074
		.WORD sub_54078

; =============== S U B	R O U T	I N E =======================================
sub_53ED8:
		CPX		#$60
		BCC		loc_53EDF
		JMP		loc_53FB9
; ---------------------------------------------------------------------------
loc_53EDF:
		LDA		_frames_counter
		AND		#$3F
		BNE		loc_53F24
		DEC		byte_55D,X
		BNE		loc_53F24
		LDA		#$06
		STA		byte_5A0+$1F
		STA		byte_5C0+$1F
		LDA		_1p_lives
		BEQ		loc_53F03
		LDA		#$01
		STA		byte_5A0
		LDA		_players_num
		BEQ		loc_53F0B
		LDA		_2p_lives
		BEQ		loc_53F0B
loc_53F03:
		LDA		#$01
		STA		byte_5C0
		STA		byte_5C0+$B
loc_53F0B:
		LDA		#$04
		STA		byte_55F,X
		LDA		#$99
		CPX		#$00
		BEQ		loc_53F18
		LDA		#$9B
loc_53F18:
		STA		byte_54F,X
		LDA		#$FF
loc_53F1D:
		STA		byte_55E,X
		TXA
		JMP		loc_53FC0
; ---------------------------------------------------------------------------
loc_53F24:
		LDA		_frames_counter
		AND		#$0F
		BNE		loc_53F8E
		CPX		#$40
		BNE		loc_53F8E
		DEC		byte_55E,X
		LDA		byte_55E,X
		CMP		#$65
		BEQ		loc_53F72
		CMP		#$00
		BNE		loc_53F8E
		LDA		#$1E
		STA		byte_541,X
		JSR		sub_89FB
		LDA		#$00
		STA		byte_553,X
		INC		byte_55F,X
		LDA		#$50
		STA		byte_55E,X
		LDY		#$A0
loc_53F53:
		LDA		#$01
		STA		byte_540,Y
		LDA		byte_543,X
		SEC
		SBC		#$10
		STA		byte_543,Y
		LDA		byte_545,X
		SEC
		SBC		#$20
		STA		byte_545,Y
		LDA		#$24
		STA		byte_55E,Y
		JMP		loc_53FB9
; ---------------------------------------------------------------------------
loc_53F72:
		LDA		#$1F
		STA		byte_541,X
		JSR		sub_89FB
		LDA		#$00
		STA		byte_553,X
		INC		byte_55F,X
		INC		byte_55F,X
		LDA		#$D8
		STA		byte_55E,X
		LDY		#$C0
		BNE		loc_53F53
loc_53F8E:
		TXA
		BEQ		loc_53FA6
		LDA		byte_543
		SEC
		SBC		byte_543,X
		CPX		#$20
		BEQ		loc_53FA2
		CMP		#$80
		BCS		loc_53FAC
		BCC		loc_53FA6
loc_53FA2:
		CMP		#$40
		BCS		loc_53FAC
loc_53FA6:
		LDA		_frames_counter
		AND		#$01
		BNE		loc_53FB9
loc_53FAC:
		INC		byte_543,X
		LDA		byte_543,X
		BNE		loc_53FB9
		LDA		#$01
		STA		byte_540,X
loc_53FB9:
		TXA
		TAY
		JSR		sub_C324
		TYA
		TAX
loc_53FC0:
		CLC
		ADC		#$20
		TAX
		CPX		#$A0
		BCS		loc_53FCB
		JMP		sub_53EC4
; ---------------------------------------------------------------------------
loc_53FCB:
		JMP		sub_8A04

; =============== S U B	R O U T	I N E =======================================
sub_53FCE:
		DEC		byte_5E0+$1E
		BNE		loc_53FD8
		LDA		#$00
		STA		byte_5E0
loc_53FD8:
		DEC		byte_55E,X
		BNE		loc_53FB9
		LDA		#$20
		STA		byte_541,X
		JSR		sub_89FB
		LDA		#$18
		STA		byte_55E,X
		LDA		#$03
loc_53FEC:
		STA		byte_55F,X
		JMP		loc_53FB9

; =============== S U B	R O U T	I N E =======================================
sub_53FF2:
		LDY		#$01
		LDA		byte_54F,X
		CMP		#$94
		BEQ		loc_53FFD
		LDY		#$00
loc_53FFD:
		STY		byte_600
		LDA		byte_543,X
		SEC
		SBC		#$10
		STA		byte_600+3
		LDA		_frames_counter
		AND		#$01
		BEQ		loc_54012
		INC		byte_543,X
loc_54012:
		DEC		byte_55E,X
		BNE		loc_53FB9
		LDA		#$00
		STA		byte_600
		LDA		#$1D
		STA		byte_541,X
		LDA		byte_55D
		STA		byte_55D,X
		JSR		sub_89FB
		LDA		#$00
		BEQ		loc_53FEC

; =============== S U B	R O U T	I N E =======================================
sub_5402E:
		DEC		byte_55E,X
		BNE		loc_53FB9
		LDA		#$1D
		STA		byte_541,X
		JSR		sub_89FB
		LDA		#$00
		STA		byte_55F,X
		LDA		byte_55D
		STA		byte_55D,X
		JMP		loc_53FB9

; =============== S U B	R O U T	I N E =======================================
sub_54049:
		LDA		_frames_counter
		AND		#$01
		TAY
		TXA
		CPY		#$01
		BNE		loc_5406D
		DEC		byte_55E,X
		BNE		loc_5406D
		LDA		#$05
		STA		byte_55F,X
		LDA		#$9A
		CPX		#$60
		BCS		loc_54070
		CPX		#$00
		BEQ		loc_54069
		LDA		#$9C
loc_54069:
		STA		byte_54F,X
		TXA
loc_5406D:
		JMP		loc_53FC0
; ---------------------------------------------------------------------------
loc_54070:
		LDA		#$9E
		BNE		loc_54069

; =============== S U B	R O U T	I N E =======================================
sub_54074:
		TXA
		JMP		loc_53FC0

; =============== S U B	R O U T	I N E =======================================
sub_54078:
		INC		byte_543,X
		CPX		#$60
		BEQ		loc_5408F
		DEC		byte_543,X
		DEC		byte_543,X
		LDA		byte_543,X
		CMP		#$98
		BCC		loc_54096
loc_5408C:
		JMP		loc_53FB9
; ---------------------------------------------------------------------------
loc_5408F:
		LDA		byte_543,X
		CMP		#$50
		BCC		loc_5408C
loc_54096:
		LDA		#$50
		STA		byte_5A0+3
		LDA		#$98
		STA		byte_5C0+3
		LDA		#$04
		STA		byte_55F,X
		LDA		#$D8
		STA		byte_55E,X
		LDA		#$00
		STA		byte_54B,X
		LDA		#$9D
		STA		byte_54F,X
		JMP		loc_5408C
; ---------------------------------------------------------------------------
		SECTION_END "ENDING"

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
_spr3E:
		.BYTE $06
		.WORD $0008
		.BYTE $10,$E3,$01,$F8
		.BYTE $00,$D9,$01,$00
		.BYTE $10,$DF,$01,$00
		.BYTE $00,$DB,$03,$08
		.BYTE $10,$E1,$03,$08
		.BYTE $00,$DD,$03,$10
_spr3F:
		.BYTE $06
		.WORD $0008
		.BYTE $10,$E5,$01,$F8
		.BYTE $00,$D9,$01,$00
		.BYTE $10,$DF,$01,$00
		.BYTE $00,$DB,$03,$08
		.BYTE $10,$E1,$03,$08
		.BYTE $00,$DD,$03,$10
_spr44:
		.BYTE $04
		.WORD $1008
		.BYTE $00,$D9,$00,$F8
		.BYTE $00,$DB,$00,$00
		.BYTE $00,$DD,$00,$08
		.BYTE $00,$DF,$00,$10
_spr45:
		.BYTE $04
		.WORD $1008
		.BYTE $00,$E1,$00,$F8
		.BYTE $00,$E3,$00,$00
		.BYTE $00,$E5,$00,$08
		.BYTE $00,$E7,$00,$10
_spr46:
		.BYTE $04
		.WORD $1008
		.BYTE $00,$E9,$00,$F8
		.BYTE $00,$EB,$00,$00
		.BYTE $00,$ED,$00,$08
		.BYTE $00,$EF,$00,$10
_spr47:
		.BYTE $04
		.WORD $1008
		.BYTE $00,$F1,$00,$F8
		.BYTE $00,$F3,$00,$00
		.BYTE $00,$F5,$00,$08
		.BYTE $00,$F7,$00,$10
_spr48:
		.BYTE $04
		.WORD $1008
		.BYTE $00,$D9,$80,$F8
		.BYTE $00,$DB,$80,$00
		.BYTE $00,$DD,$80,$08
		.BYTE $00,$DF,$80,$10
_spr4B:
		.BYTE $0B
		.WORD $0008
		.BYTE $00,$D9,$03,$F0
		.BYTE $00,$DB,$03,$F8
		.BYTE $10,$E1,$03,$F8
		.BYTE $00,$DD,$03,$00
		.BYTE $10,$E3,$03,$00
		.BYTE $00,$DF,$03,$08
		.BYTE $10,$E5,$03,$08
		.BYTE $00,$D9,$03,$10
		.BYTE $10,$E7,$03,$10
		.BYTE $00,$D9,$03,$18
		.BYTE $10,$E9,$03,$18
_spr4C:
		.BYTE $09
		.WORD $0008
		.BYTE $00,$D9,$03,$F0
		.BYTE $00,$DB,$03,$F8
		.BYTE $10,$E1,$03,$F8
		.BYTE $00,$DD,$03,$00
		.BYTE $10,$E3,$03,$00
		.BYTE $00,$DF,$03,$08
		.BYTE $10,$E5,$03,$08
		.BYTE $10,$E7,$03,$10
		.BYTE $10,$E9,$03,$18
_spr4D:
		.BYTE $08
		.WORD $0008
		.BYTE $00,$F5,$03,$F8
		.BYTE $10,$E1,$03,$F8
		.BYTE $00,$DD,$03,$00
		.BYTE $10,$E3,$03,$00
		.BYTE $00,$DF,$03,$08
		.BYTE $10,$E5,$03,$08
		.BYTE $10,$E7,$03,$10
		.BYTE $10,$E9,$03,$18
_spr4E:
		.BYTE $0A
		.WORD $0008
		.BYTE $00,$F5,$03,$F8
		.BYTE $10,$E1,$03,$F8
		.BYTE $00,$DD,$03,$00
		.BYTE $10,$E3,$03,$00
		.BYTE $00,$DF,$03,$08
		.BYTE $10,$E5,$03,$08
		.BYTE $00,$D9,$03,$10
		.BYTE $10,$E7,$03,$10
		.BYTE $00,$D9,$03,$18
		.BYTE $10,$E9,$03,$18
_spr4F:
		.BYTE $09
		.WORD $0008
		.BYTE $00,$D9,$03,$F0
		.BYTE $00,$D9,$03,$F8
		.BYTE $00,$EB,$03,$00
		.BYTE $10,$EF,$03,$00
		.BYTE $00,$ED,$03,$08
		.BYTE $10,$F1,$03,$08
		.BYTE $00,$D9,$03,$10
		.BYTE $10,$F3,$03,$10
		.BYTE $00,$D9,$03,$18
_spr50:
		.BYTE $07
		.WORD $0008
		.BYTE $00,$D9,$03,$F0
		.BYTE $00,$D9,$03,$F8
		.BYTE $00,$EB,$03,$00
		.BYTE $10,$EF,$03,$00
		.BYTE $00,$ED,$03,$08
		.BYTE $10,$F1,$03,$08
		.BYTE $10,$F3,$03,$10
_spr51:
		.BYTE $05
		.WORD $0008
		.BYTE $00,$EB,$03,$00
		.BYTE $10,$EF,$03,$00
		.BYTE $00,$ED,$03,$08
		.BYTE $10,$F1,$03,$08
		.BYTE $10,$F3,$03,$10
_spr52:
		.BYTE $07
		.WORD $0008
		.BYTE $00,$EB,$03,$00
		.BYTE $10,$EF,$03,$00
		.BYTE $00,$ED,$03,$08
		.BYTE $10,$F1,$03,$08
		.BYTE $00,$D9,$03,$10
		.BYTE $10,$F3,$03,$10
		.BYTE $00,$D9,$03,$18
_spr56:
		.BYTE $02
		.WORD $0008
		.BYTE $08,$C3,$00,$00
		.BYTE $08,$C5,$00,$08
_spr57:
		.BYTE $02
		.WORD $0008
		.BYTE $08,$C7,$00,$00
		.BYTE $08,$C9,$00,$08
_spr58:
		.BYTE $02
		.WORD $0008
		.BYTE $08,$CB,$00,$00
		.BYTE $08,$CD,$00,$08
_spr59:
		.BYTE $01
		.WORD $0000
		.BYTE $00,$D5,$00,$00
_spr5A:
		.BYTE $01
		.WORD $0000
		.BYTE $00,$D3,$00,$00
_spr5B:
		.BYTE $02
		.WORD $0008
		.BYTE $08,$CF,$00,$00
		.BYTE $08,$D1,$00,$08
_spr73:
		.BYTE $01
		.WORD $1000
		.BYTE $00,$03,$00,$04
_spr74:
		.BYTE $02
		.WORD $1008
		.BYTE $00,$05,$00,$00
		.BYTE $00,$07,$00,$08
_spr75:
		.BYTE $02
		.WORD $1008
		.BYTE $00,$09,$00,$00
		.BYTE $00,$0B,$00,$08
_spr76:
		.BYTE $02
		.WORD $1008
		.BYTE $00,$0D,$00,$00
		.BYTE $00,$0F,$00,$08
_spr77:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$11,$00,$00
		.BYTE $10,$13,$00,$00
		.BYTE $00,$15,$00,$08
		.BYTE $10,$17,$00,$08
_spr78:
		.BYTE $05
		.WORD $0008
		.BYTE $00,$19,$00,$00
		.BYTE $10,$1B,$00,$00
		.BYTE $00,$1D,$00,$08
		.BYTE $10,$1F,$00,$08
		.BYTE $00,$21,$00,$10
_spr79:
		.BYTE $05
		.WORD $0008
		.BYTE $00,$23,$00,$F8
		.BYTE $00,$25,$00,$00
		.BYTE $10,$27,$00,$00
		.BYTE $00,$29,$00,$08
		.BYTE $10,$2B,$00,$08
_spr7A:
		.BYTE $08
		.WORD $FB08
		.BYTE $00,$2D,$00,$F8
		.BYTE $F0,$2F,$00,$00
		.BYTE $00,$31,$00,$00
		.BYTE $10,$33,$00,$00
		.BYTE $F0,$35,$00,$08
		.BYTE $00,$37,$00,$08
		.BYTE $10,$39,$00,$08
		.BYTE $00,$3B,$00,$10
_spr7B:
		.BYTE $07
		.WORD $0008
		.BYTE $F8,$3D,$00,$F0
		.BYTE $F0,$3F,$00,$F8
		.BYTE $00,$41,$00,$F8
		.BYTE $F0,$43,$00,$00
		.BYTE $00,$45,$00,$00
		.BYTE $10,$47,$00,$00
		.BYTE $F0,$49,$00,$08
_spr80:
		.BYTE $02
		.WORD $0008
		.BYTE $00,$4D,$00,$00
		.BYTE $00,$4F,$00,$08
_spr81:
		.BYTE $08
		.WORD $F808
		.BYTE $00,$51,$00,$F8
		.BYTE $10,$59,$00,$F8
		.BYTE $00,$53,$00,$00
		.BYTE $10,$5B,$00,$00
		.BYTE $00,$55,$00,$08
		.BYTE $10,$5D,$00,$08
		.BYTE $00,$57,$00,$10
		.BYTE $10,$5F,$00,$10
_spr82:
		.BYTE $12
		.WORD $F008
		.BYTE $00,$61,$00,$F0
		.BYTE $10,$6D,$00,$F0
		.BYTE $20,$79,$00,$F0
		.BYTE $00,$63,$00,$F8
		.BYTE $10,$6F,$00,$F8
		.BYTE $20,$7B,$00,$F8
		.BYTE $00,$65,$00,$00
		.BYTE $10,$71,$00,$00
		.BYTE $20,$7D,$00,$00
		.BYTE $00,$67,$00,$08
		.BYTE $10,$73,$00,$08
		.BYTE $20,$7F,$00,$08
		.BYTE $00,$69,$00,$10
		.BYTE $10,$75,$00,$10
		.BYTE $20,$81,$00,$10
		.BYTE $00,$6B,$00,$18
		.BYTE $10,$77,$00,$18
		.BYTE $20,$83,$00,$18
_spr83:
		.BYTE $12
		.WORD $F008
		.BYTE $00,$85,$00,$F0
		.BYTE $10,$91,$00,$F0
		.BYTE $20,$9D,$00,$F0
		.BYTE $00,$87,$00,$F8
		.BYTE $10,$93,$00,$F8
		.BYTE $20,$9F,$00,$F8
		.BYTE $00,$89,$00,$00
		.BYTE $10,$95,$00,$00
		.BYTE $20,$A1,$00,$00
		.BYTE $00,$8B,$00,$08
		.BYTE $10,$97,$00,$08
		.BYTE $20,$A3,$00,$08
		.BYTE $00,$8D,$00,$10
		.BYTE $10,$99,$00,$10
		.BYTE $20,$A5,$00,$10
		.BYTE $00,$8F,$00,$18
		.BYTE $10,$9B,$00,$18
		.BYTE $20,$A7,$00,$18
_spr84:
		.BYTE $1D
		.WORD $E008
		.BYTE $00,$A9,$00,$E8
		.BYTE $10,$B7,$00,$E8
		.BYTE $30,$D3,$00,$E8
		.BYTE $00,$AB,$00,$F0
		.BYTE $10,$B9,$00,$F0
		.BYTE $20,$C7,$00,$F0
		.BYTE $30,$D5,$00,$F0
		.BYTE $00,$AD,$00,$F8
		.BYTE $10,$BB,$00,$F8
		.BYTE $20,$C9,$00,$F8
		.BYTE $30,$D7,$00,$F8
		.BYTE $00,$AF,$00,$00
		.BYTE $10,$BD,$00,$00
		.BYTE $20,$CB,$00,$00
		.BYTE $30,$D9,$00,$00
		.BYTE $00,$B1,$00,$08
		.BYTE $10,$BF,$00,$08
		.BYTE $20,$CD,$00,$08
		.BYTE $30,$DB,$00,$08
		.BYTE $00,$B3,$00,$10
		.BYTE $10,$C1,$00,$10
		.BYTE $20,$CF,$00,$10
		.BYTE $30,$DD,$00,$10
		.BYTE $00,$B5,$00,$18
		.BYTE $10,$C3,$00,$18
		.BYTE $20,$D1,$00,$18
		.BYTE $30,$DF,$00,$18
		.BYTE $10,$C5,$00,$20
		.BYTE $30,$E1,$00,$20
_spr85:
		.BYTE $1A
		.WORD $E008
		.BYTE $30,$C8,$00,$E8
		.BYTE $00,$E3,$00,$F0
		.BYTE $10,$EF,$00,$F0
		.BYTE $20,$FD,$00,$F0
		.BYTE $30,$D0,$00,$F0
		.BYTE $00,$E5,$00,$F8
		.BYTE $10,$F1,$00,$F8
		.BYTE $20,$FF,$00,$F8
		.BYTE $30,$D2,$00,$F8
		.BYTE $00,$E7,$00,$00
		.BYTE $10,$F3,$00,$00
		.BYTE $20,$DC,$00,$00
		.BYTE $30,$D4,$00,$00
		.BYTE $00,$E9,$00,$08
		.BYTE $10,$F5,$00,$08
		.BYTE $20,$C2,$00,$08
		.BYTE $30,$D6,$00,$08
		.BYTE $00,$EB,$00,$10
		.BYTE $10,$F7,$00,$10
		.BYTE $20,$C4,$00,$10
		.BYTE $30,$D8,$00,$10
		.BYTE $10,$F9,$00,$18
		.BYTE $20,$C6,$00,$18
		.BYTE $30,$E0,$00,$18
		.BYTE $10,$FB,$00,$20
		.BYTE $30,$E2,$00,$20
_spr86:
		.BYTE $13
		.WORD $F008
		.BYTE $20,$FA,$00,$E8
		.BYTE $00,$E4,$00,$F0
		.BYTE $10,$F0,$00,$F0
		.BYTE $20,$FC,$00,$F0
		.BYTE $00,$E6,$00,$F8
		.BYTE $10,$F2,$00,$F8
		.BYTE $20,$CA,$00,$F8
		.BYTE $00,$E8,$00,$00
		.BYTE $10,$C2,$00,$00
		.BYTE $20,$CC,$00,$00
		.BYTE $00,$EA,$00,$08
		.BYTE $10,$F4,$00,$08
		.BYTE $20,$DA,$00,$08
		.BYTE $00,$EC,$00,$10
		.BYTE $10,$F6,$00,$10
		.BYTE $20,$CE,$00,$10
		.BYTE $00,$EE,$00,$18
		.BYTE $10,$F8,$00,$18
		.BYTE $20,$DE,$00,$18
_spr8A:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$1B,$00,$00
		.BYTE $10,$1D,$00,$00
		.BYTE $00,$1F,$00,$08
		.BYTE $10,$21,$00,$08
_spr8B:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$23,$00,$00
		.BYTE $10,$25,$00,$00
		.BYTE $00,$27,$00,$08
		.BYTE $10,$29,$00,$08
_spr8C:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$2B,$00,$00
		.BYTE $10,$2D,$00,$00
		.BYTE $00,$2F,$00,$08
		.BYTE $10,$31,$00,$08
_spr8E:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$33,$00,$00
		.BYTE $10,$35,$00,$00
		.BYTE $00,$37,$00,$08
		.BYTE $10,$21,$00,$08
_spr8F:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$39,$00,$00
		.BYTE $10,$3B,$00,$00
		.BYTE $00,$3D,$00,$08
		.BYTE $10,$3F,$00,$08
_spr90:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$41,$00,$00
		.BYTE $10,$43,$00,$00
		.BYTE $00,$45,$00,$08
		.BYTE $10,$47,$00,$08
_spr92:
		.BYTE $07
		.WORD $0008
		.BYTE $00,$49,$00,$F8
		.BYTE $10,$51,$00,$F8
		.BYTE $00,$4B,$00,$00
		.BYTE $10,$53,$00,$00
		.BYTE $00,$4D,$00,$08
		.BYTE $10,$55,$00,$08
		.BYTE $00,$4F,$00,$10
_spr93:
		.BYTE $04
		.WORD $0008
		.BYTE $10,$57,$00,$F8
		.BYTE $10,$59,$00,$00
		.BYTE $10,$5B,$00,$08
		.BYTE $10,$5D,$00,$10
_spr94:
		.BYTE $07
		.WORD $0008
		.BYTE $00,$73,$00,$F8
		.BYTE $10,$7B,$00,$F8
		.BYTE $00,$75,$00,$00
		.BYTE $10,$7D,$00,$00
		.BYTE $00,$77,$00,$08
		.BYTE $10,$7F,$00,$08
		.BYTE $00,$79,$00,$10
_spr95:
		.BYTE $06
		.WORD $0008
		.BYTE $10,$87,$00,$F8
		.BYTE $00,$81,$00,$00
		.BYTE $10,$89,$00,$00
		.BYTE $00,$83,$00,$08
		.BYTE $10,$8B,$00,$08
		.BYTE $00,$85,$00,$10
_spr96:
		.BYTE $08
		.WORD $0008
		.BYTE $00,$5F,$00,$F8
		.BYTE $10,$67,$00,$F8
		.BYTE $00,$61,$00,$00
byte_53DD1:
		.BYTE $10,$69,$00,$00
		.BYTE $00,$63,$00,$08
		.BYTE $10,$6B,$00,$08
		.BYTE $00,$65,$00,$10
		.BYTE $10,$6D,$00,$10
_spr97:
		.BYTE $08
		.WORD $0008
		.BYTE $00,$6F,$00,$F8
		.BYTE $10,$67,$00,$F8
		.BYTE $00,$71,$00,$00
		.BYTE $10,$69,$00,$00
		.BYTE $00,$63,$00,$08
		.BYTE $10,$6B,$00,$08
		.BYTE $00,$65,$00,$10
		.BYTE $10,$6D,$00,$10
_spr98:
		.BYTE $06
		.WORD $0008
		.BYTE $10,$91,$00,$F8
		.BYTE $00,$8D,$00,$00
		.BYTE $10,$93,$00,$00
		.BYTE $00,$8F,$00,$08
		.BYTE $10,$95,$00,$08
		.BYTE $10,$97,$00,$10
_spr99:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$A7,$00,$00
		.BYTE $10,$99,$00,$00
		.BYTE $00,$A9,$00,$08
		.BYTE $10,$9B,$00,$08
_spr9A:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$AB,$00,$00
		.BYTE $10,$99,$00,$00
		.BYTE $00,$AD,$00,$08
		.BYTE $10,$9D,$00,$08
_spr9B:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$AF,$00,$00
		.BYTE $10,$99,$00,$00
		.BYTE $00,$B1,$00,$08
		.BYTE $10,$B7,$00,$08
_spr9C:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$B3,$00,$00
		.BYTE $10,$99,$00,$00
		.BYTE $00,$B5,$00,$08
		.BYTE $10,$B7,$00,$08
_spr9D:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$A7,$00,$00
		.BYTE $10,$99,$00,$00
		.BYTE $00,$A9,$00,$08
		.BYTE $10,$9B,$00,$08
_spr9E:
		.BYTE $04
		.WORD $0008
		.BYTE $00,$AB,$00,$00
		.BYTE $10,$99,$00,$00
		.BYTE $00,$AD,$00,$08
		.BYTE $10,$9D,$00,$08
_spr6C:
		.BYTE $02
		.WORD $0008
		.BYTE $00,$1B,$00,$00
		.BYTE $00,$1D,$00,$08
_spr6D:
		.BYTE $04
		.WORD $0308
		.BYTE $00,$1F,$00,$00
		.BYTE $10,$21,$00,$00
		.BYTE $00,$23,$00,$08
		.BYTE $10,$25,$00,$08
_spr6E:
		.BYTE $04
		.WORD $0308
		.BYTE $00,$27,$03,$00
		.BYTE $10,$29,$00,$00
		.BYTE $00,$2B,$03,$08
		.BYTE $10,$2D,$00,$08
_spr6F:
		.BYTE $0A
		.WORD $0308
		.BYTE $F0,$2F,$03,$F8
		.BYTE $00,$33,$03,$F8
		.BYTE $F0,$31,$03,$00
		.BYTE $00,$35,$03,$00
		.BYTE $10,$37,$00,$00
		.BYTE $F0,$31,$43,$08
		.BYTE $00,$35,$43,$08
		.BYTE $10,$39,$00,$08
		.BYTE $F0,$2F,$43,$10
		.BYTE $00,$33,$43,$10
_spr70:
		.BYTE $0C
		.WORD $0408
		.BYTE $E0,$3B,$03,$F8
		.BYTE $F0,$3F,$03,$F8
		.BYTE $E0,$3D,$03,$00
		.BYTE $F0,$41,$03,$00
		.BYTE $00,$43,$00,$00
		.BYTE $10,$47,$00,$00
		.BYTE $E0,$3D,$43,$08
		.BYTE $F0,$41,$43,$08
		.BYTE $00,$45,$00,$08
		.BYTE $10,$49,$00,$08
		.BYTE $E0,$3B,$43,$10
		.BYTE $F0,$3F,$43,$10
_spr71:
		.BYTE $12
		.WORD $0008
		.BYTE $D0,$4B,$03,$F0
		.BYTE $E0,$51,$03,$F0
		.BYTE $D0,$4D,$03,$F8
		.BYTE $E0,$53,$03,$F8
		.BYTE $F0,$55,$03,$F8
		.BYTE $D0,$4F,$03,$00
		.BYTE $F0,$57,$03,$00
		.BYTE $00,$59,$00,$00
		.BYTE $10,$5D,$00,$00
		.BYTE $D0,$4F,$43,$08
		.BYTE $F0,$57,$43,$08
		.BYTE $00,$5B,$00,$08
		.BYTE $10,$5F,$00,$08
		.BYTE $D0,$4D,$43,$10
		.BYTE $E0,$53,$43,$10
		.BYTE $F0,$55,$43,$10
		.BYTE $D0,$4B,$43,$18
		.BYTE $E0,$51,$43,$18
_spr72:
		.BYTE $10
		.WORD $0000
		.BYTE $00,$61,$02,$00
		.BYTE $10,$71,$02,$00
		.BYTE $00,$63,$02,$08
		.BYTE $10,$73,$02,$08
		.BYTE $00,$65,$02,$10
		.BYTE $10,$75,$02,$10
		.BYTE $00,$67,$02,$18
		.BYTE $10,$77,$02,$18
		.BYTE $00,$69,$02,$20
		.BYTE $10,$79,$02,$20
		.BYTE $00,$6B,$02,$28
		.BYTE $10,$7B,$02,$28
		.BYTE $00,$6D,$02,$30
		.BYTE $10,$7D,$02,$30
		.BYTE $00,$6F,$02,$38
		.BYTE $10,$7F,$02,$38
_spr7C:
		.BYTE $10
		.WORD $0000
		.BYTE $00,$61,$02,$00
		.BYTE $10,$71,$02,$00
		.BYTE $00,$63,$02,$08
		.BYTE $10,$73,$02,$08
		.BYTE $00,$65,$02,$10
		.BYTE $10,$75,$02,$10
		.BYTE $00,$81,$02,$18
		.BYTE $10,$77,$02,$18
		.BYTE $00,$83,$02,$20
		.BYTE $10,$79,$02,$20
		.BYTE $00,$85,$02,$28
		.BYTE $10,$7B,$02,$28
		.BYTE $00,$6D,$02,$30
		.BYTE $10,$7D,$02,$30
		.BYTE $00,$87,$02,$38
		.BYTE $10,$7F,$02,$38
_spr7D:
		.BYTE $10
		.WORD $0000
		.BYTE $00,$01,$02,$00
		.BYTE $10,$71,$02,$00
		.BYTE $00,$89,$02,$08
		.BYTE $10,$73,$02,$08
		.BYTE $00,$8B,$02,$10
		.BYTE $10,$75,$02,$10
		.BYTE $00,$8D,$02,$18
		.BYTE $10,$77,$02,$18
		.BYTE $00,$83,$02,$20
		.BYTE $10,$79,$02,$20
		.BYTE $00,$85,$02,$28
		.BYTE $10,$7B,$02,$28
		.BYTE $00,$6D,$02,$30
		.BYTE $10,$7D,$02,$30
		.BYTE $00,$6F,$02,$38
		.BYTE $10,$7F,$02,$38
_spr7E:
		.BYTE $10
		.WORD $0000
		.BYTE $00,$01,$02,$00
		.BYTE $10,$71,$02,$00
		.BYTE $00,$8F,$02,$08
		.BYTE $10,$73,$02,$08
		.BYTE $00,$91,$02,$10
		.BYTE $10,$75,$02,$10
		.BYTE $00,$67,$02,$18
		.BYTE $10,$77,$02,$18
		.BYTE $00,$69,$02,$20
		.BYTE $10,$79,$02,$20
		.BYTE $00,$6B,$02,$28
		.BYTE $10,$7B,$02,$28
		.BYTE $00,$6D,$02,$30
		.BYTE $10,$7D,$02,$30
		.BYTE $00,$87,$02,$38
		.BYTE $10,$7F,$02,$38
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
		.WORD $FFFF
		.WORD _tlm01_1_player
		.WORD _tlm02_2_players
		.WORD _tlm03_play_select
		.WORD _tlm04_konami_1897
		.WORD $FFFF
		.WORD _tlm06_pal
		.WORD _tlm07_blank
		.WORD _tlm08_hi
		.WORD _tlm09_1p
		.WORD _tlm0A_2p
		.WORD $FFFF
		.WORD $FFFF
		.WORD _tlm0D_blank
		.WORD _tlm0E_1p_pow
		.WORD _tlm0F_2p_pow
		.WORD _tlm10_game_over
		.WORD _tlm11_blank
		.WORD _tlm12_blank
		.WORD _tlm13_pal
		.WORD _tlm14_continue
		.WORD _tlm15_yes
		.WORD _tlm16_no
		.WORD $FFFF
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
		.WORD $FFFF
		.WORD $FFFF
		.WORD _tlm4D_pal
		.WORD _tlm4E_pal
		.WORD _tlm4F_pal
		.WORD _tlm50_pal
		.WORD _tlm51_pal
		.WORD _tlm52_pal
		.WORD _tlm53_bg_pal
		.WORD $FFFF
		.WORD _tlm55_bg_pal
		.WORD _tlm56_bg_pal
_tlm01_1_player:
		.WORD $EE22
		.BYTE _1,__,_P,_L,_A,_Y,_E,_R
		.BYTE $FE
_tlm02_2_players:
		.WORD $0E23
		.BYTE _2,__,_P,_L,_A,_Y,_E,_R,_S
		.BYTE $FE
_tlm03_play_select:
		.WORD $AB22
		.BYTE _P,_L,_A,_Y,__,_S,_E,_L,_E,_C,_T
		.BYTE $FE
_tlm04_konami_1897:
		.WORD $4A22
		.BYTE $F9
		.BYTE __,_K,_0,_N,_A,_M,_I,__,_1,_9,_8,_9
		.BYTE $FE
_tlm07_blank:
		.WORD $6020
		.BYTE __
		.BYTE $FF
_tlm08_hi:
		.WORD $4B20
		.BYTE $0B,$0C,__
		.BYTE $FF
_tlm09_1p:
		.WORD $4020
		.BYTE _1,$0E,__
		.BYTE $FF
_tlm0A_2p:
		.WORD $5620
		.BYTE _2,$0E,__
		.BYTE $FF
_tlm0D_blank:
		.WORD $7920
		.BYTE __
		.BYTE $FF
_tlm0E_1p_pow:
		.WORD $6820
		.BYTE $0E,$01,$10,$0F
		.BYTE $FF
_tlm0F_2p_pow:
		.WORD $7320
		.BYTE $0E,$01,$10,$0F
		.BYTE $FF
_tlm10_game_over:
		.WORD $8B21
		.BYTE _G,_A,_M,_E,__,_0,_V,_E,_R
		.BYTE $FE
_tlm11_blank:
		.WORD $6020
		.BYTE __,__,__,__,__,__,__,__,__,__,__,__,__,__
		.BYTE $FE
_tlm12_blank:
		.WORD $7320
		.BYTE __,__,__,__,__,__,__,__,__,__,__,__,__
		.BYTE $FE
_tlm14_continue:
		.WORD $0B22
		.BYTE _C,_0,_N,_T,_I,_N,_U,_E
		.BYTE $FE
_tlm15_yes:
		.WORD $4E22
		.BYTE _Y,_E,_S
		.BYTE $FE
_tlm16_no:
		.WORD $8E22
		.BYTE _N,_0
		.BYTE $FE
_tlm1D_staff:
		.WORD $ED20
		.BYTE _S,_T,_A,_F,_F
		.BYTE $FE
_tlm1E_blank:
		.WORD $6021
		.BYTE __,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__
		.BYTE __,__,__,__,__
		.BYTE $FE
_tlm1F_blank:
		.WORD $A021
		.BYTE __,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__
		.BYTE __,__,__,__,__,__,__,__,__,__,__,__,__,__,__,__
		.BYTE $FE
_tlm20_please_push_start_button:
		.WORD $A321
		.BYTE _P,_L,_E,_A,_S,_E,__,_P,_U,_S,_H,__,_S,_T,_A,_R,_T,__,_B,_U,_T,_T,_0,_N
		.BYTE $FE
_tlm21_blank:
		.WORD $ED20
		.BYTE __,__,__,__,__
		.BYTE $FE

_tlm06_pal:
		.BYTE $3F,$00,$0F,$00,$10,$30,$0F,$19,$27,$15,$0F,$15,$26,$10,$0F,$27
		.BYTE $16,$21,$0F,$0C,$26,$30,$0F,$0C,$2C,$30,$0F,$12,$26,$30,$0F,$06
		.BYTE $30,$30,$FE
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
		.BYTE $09,$27,$FE

_tlm26_ending:
		.BYTE $21,$0C,$2F,$28,$28,$28,$28,$28,$28,$3F,$FE
_tlm27_ending:
		.BYTE $21,$2C,$3D,$28,$28,$9C,$9D,$00,$9E,$28,$FE
_tlm28_ending:
		.BYTE $21,$4C,$28,$28,$64,$5F,$8B,$8B,$56,$28,$FE
_tlm29_ending:
		.BYTE $21,$6C,$28,$28,$62,$7F,$8A,$8A,$63,$28,$FE
_tlm2A_ending:
		.BYTE $21,$8C,$48,$66,$4A,$4B,$00,$8B,$00,$BC,$FE
_tlm2B_ending:
		.BYTE $21,$AC,$27,$89,$5A,$5B,$00,$8A,$8A,$BB,$FE
_tlm2C_ending:
		.BYTE $21,$CC,$68,$69,$6A,$6B,$AA,$8B,$AA,$BA,$FE
_tlm2D_ending:
		.BYTE $21,$EC,$78,$79,$7A,$6B,$00,$8A,$8A,$B9,$FE
_tlm2E_ending:
		.BYTE $21,$0C,$2F,$28,$28,$28,$28,$28,$28,$3F,$FE
_tlm2F_ending:
		.BYTE $21,$2C,$3D,$28,$28,$28,$28,$28,$28,$28,$FE
_tlm30_ending:
		.BYTE $21,$4C,$28,$28,$28,$9C,$9D,$00,$8F,$28,$FE
_tlm31_ending:
		.BYTE $21,$6C,$28,$28,$64,$5F,$8B,$8B,$56,$28,$FE
_tlm32_ending:
		.BYTE $21,$8C,$48,$96,$65,$4B,$00,$8B,$9B,$7B,$FE
_tlm33_ending:
		.BYTE $21,$AC,$27,$89,$5A,$5B,$00,$8A,$8A,$BB,$FE
_tlm34_ending:
		.BYTE $21,$CC,$68,$69,$6A,$6B,$AA,$8B,$AA,$BA,$FE
_tlm35_ending:
		.BYTE $21,$EC,$78,$79,$7A,$6B,$00,$8A,$8A,$B9,$FE
_tlm36_ending:
		.BYTE $21,$0C,$2F,$28,$28,$28,$28,$28,$28,$3F,$FE
_tlm37_ending:
		.BYTE $21,$2C,$3D,$28,$28,$28,$28,$28,$28,$28,$FE
_tlm38_ending:
		.BYTE $21,$4C,$28,$28,$28,$28,$AD,$28,$28,$28,$FE
_tlm39_ending:
		.BYTE $21,$6C,$28,$28,$28,$AC,$AE,$AF,$9F,$28,$FE
_tlm3A_ending:
		.BYTE $21,$8C,$48,$8D,$7C,$A3,$00,$8B,$9B,$7B,$FE
_tlm3B_ending:
		.BYTE $21,$AC,$27,$97,$7D,$5B,$00,$8A,$8A,$BB,$FE
_tlm3C_ending:
		.BYTE $21,$CC,$68,$69,$6A,$6B,$AA,$8B,$AA,$BA,$FE
_tlm3D_ending:
		.BYTE $21,$EC,$78,$79,$7A,$6B,$00,$8A,$8A,$B9,$FE
_tlm3E_ending:
		.BYTE $21,$0C,$2F,$28,$28,$28,$28,$28,$28,$3F,$FE
_tlm3F_ending:
		.BYTE $21,$2C,$3D,$28,$28,$28,$28,$28,$28,$28,$FE
_tlm40_ending:
		.BYTE $21,$4C,$28,$28,$28,$28,$28,$28,$28,$28,$FE
_tlm41_ending:
		.BYTE $21,$6C,$28,$28,$28,$28,$28,$28,$28,$28,$FE
_tlm42_ending:
		.BYTE $21,$84,$3E,$3B,$3E,$3A,$3E,$3B,$3A,$3E,$48,$3A,$3E,$35,$3B,$3A
		.BYTE $48,$3A,$3B,$27,$3E,$35,$FE
_tlm43_ending:
		.BYTE $21,$A4,$27,$27,$4C,$4D,$27,$27,$27,$27,$27,$27,$27,$27,$37,$27
		.BYTE $27,$27,$2B,$2B,$2C,$27,$FE
_tlm44_ending:
		.BYTE $21,$C4,$27,$27,$5C,$5D,$27,$27,$27,$27,$27,$27,$27,$27,$27,$27
		.BYTE $27,$27,$27,$3A,$27,$27,$FE
_tlm45_ending:
		.BYTE $21,$E4,$27,$27,$50,$27,$27,$27,$27,$27,$27,$27,$27,$27,$55,$6C
		.BYTE $6D,$4E,$27,$27,$27,$27,$FE
_tlm46_ending:
		.BYTE $22,$04,$27,$27,$76,$27,$27,$27,$27,$27,$27,$27,$54,$51,$8A,$00
		.BYTE $00,$47,$55,$58,$52,$4E,$27,$27,$27,$53,$A8,$27,$27,$27,$FE
_tlm47_ending:
		.BYTE $22,$24,$33,$75,$76,$44,$51,$52,$53,$54,$52,$51,$00,$00,$00,$00
		.BYTE $00,$00,$00,$00,$00,$47,$58,$52,$4E,$57,$B8,$44,$33,$75,$FE
_tlm48_ending:
		.BYTE $22,$44,$84,$85,$95,$95,$86,$94,$86,$86,$00,$95,$86,$00,$00,$00
		.BYTE $95,$94,$95,$95,$00,$00,$95,$95,$86,$86,$86,$94,$84,$85,$FE
_tlm49_ending:
		.BYTE $22,$64,$94,$94,$95,$94,$95,$94,$27,$94,$95,$94,$95,$94,$95,$94
		.BYTE $94,$95,$94,$94,$95,$94,$94,$27,$94,$95,$95,$A4,$B6,$A4,$FE
		SECTION_END "TLM LIB"

		SECTION_START
; =============== S U B	R O U T	I N E =======================================
_type_msg_ptr_fetch:
		LDA		#$00
		STA		byte_656
		LDA		_type_msg_lib,Y
		STA		byte_652
		STA		byte_10
		LDA		_type_msg_lib+1,Y
		STA		byte_653
		STA		byte_11
		LDY		#$00
		LDA		(byte_10),Y
		STA		byte_650
		INY
		LDA		(byte_10),Y
		STA		byte_651
		LDA		#$50
		STA		byte_654
		INY
		STY		byte_655

; =============== S U B	R O U T	I N E =======================================
nullsub_11:
		RTS

; =============== S U B	R O U T	I N E =======================================
_type_msg_handler:
		LDA		byte_656
		BNE		nullsub_11
		DEC		byte_654
		BNE		nullsub_11
		LDY		byte_655
		LDA		byte_652
		STA		byte_10
		LDA		byte_653
		STA		byte_11
		LDA		(byte_10),Y
		PHA
		LDX		_ppu_queue_pos
		LDA		#$01
		STA		_ppu_queue_buf,X
		INX
		LDA		byte_650
		STA		_ppu_queue_buf,X
		INX
		LDA		byte_651
		STA		_ppu_queue_buf,X
		INC		byte_651
		INX
		PLA
		STA		_ppu_queue_buf,X
		LDA		_main_sub_idx
		CMP		#$09
		BNE		loc_8B1B
		LDA		_sub_sub_idx
		CMP		#$02
		BCS		loc_8B20
loc_8B1B:
		LDA		#$06
		JSR		_apu_load_safe
loc_8B20:
		INX
		LDA		#$FF
		STA		_ppu_queue_buf,X
		INX
		LDA		#$00
		STA		_ppu_queue_buf,X
		STX		_ppu_queue_pos
		INY
		LDA		(byte_10),Y
		CMP		#$40
		BEQ		loc_8B53
		CMP		#$41
		BNE		loc_8B4A
		INY
		LDA		(byte_10),Y
		STA		byte_650
		INY
		LDA		(byte_10),Y
		STA		byte_651
		INY
		LDA		#$18
		BNE		loc_8B4C
loc_8B4A:
		LDA		#$06
loc_8B4C:
		STA		byte_654
		STY		byte_655
		RTS
; ---------------------------------------------------------------------------
loc_8B53:
		LDA		#$01
		STA		byte_656
		RTS
; ---------------------------------------------------------------------------
_type_msg_lib:
		.WORD _type_msg00_your_mission_is
		.WORD _type_msg02_1st_target_overcome
		.WORD _type_msg04_2nd_target_overcome
		.WORD _type_msg06_3rd_target_overcome
		.WORD _type_msg08_4th_target_overcome
		.WORD _type_msg0A_5th_last_target_overcome
		.WORD _type_msg0C_ending
		.WORD _type_msg0E
		.WORD _type_msg10
		.WORD _type_msg12
		.WORD _type_msg14
		.WORD _type_msg16
		.WORD _type_msg18
		.WORD _type_msg1A
		.WORD _type_msg1C
		.WORD _type_msg1E
		.WORD _type_msg20
		.WORD _type_msg22
		.WORD _type_msg24
#if LANGUAGE=LANG_JP
_type_msg00_your_mission_is:
		.WORD $A520
		.BYTE _Y,_0,_U,_R,__,_M,_I,_S,_S,_I,_0,_N
		.BYTE $41
		.WORD $C820
		.BYTE _D,_E,_S,_T,_R,_0,_Y,__,_E,_N,_E,_M,_Y
		.BYTE $41
		.WORD $E720
		.BYTE _S,_E,_C,_R,_E,_T,__,_W,_E,_A,_P,_0,_N,_dt
		.BYTE $41
		.WORD $EA21
		.BYTE _G,_0,_0,_D,__,_L,_U,_C,_K,_dt
		.BYTE $40
_type_msg02_1st_target_overcome:
		.WORD $CE20
		.BYTE _W,_E,_L,_L,__,_D,_0,_N,_E
		.BYTE $41
		.WORD $2B21
		.BYTE _1,_S,_T,__,_T,_A,_R,_G,_E,_T,__,_0,_V,_E,_R,_C,_0,_M,_E
		.BYTE $40
_type_msg04_2nd_target_overcome:
		.WORD $CE20
		.BYTE _W,_E,_L,_L,__,_D,_0,_N,_E
		.BYTE $41
		.WORD $2B21
		.BYTE _2,_N,_D,__,_T,_A,_R,_G,_E,_T,__,_0,_V,_E,_R,_C,_0,_M,_E
		.BYTE $40
_type_msg06_3rd_target_overcome:
		.WORD $CE20
		.BYTE _W,_E,_L,_L,__,_D,_0,_N,_E
		.BYTE $41
		.WORD $2B21
		.BYTE _3,_R,_D,__,_T,_A,_R,_G,_E,_T,__,_0,_V,_E,_R,_C,_0,_M,_E
		.BYTE $40
_type_msg08_4th_target_overcome:
		.WORD $CE20
		.BYTE _W,_E,_L,_L,__,_D,_0,_N,_E
		.BYTE $41
		.WORD $2B21
		.BYTE _4,_T,_H,__,_T,_A,_R,_G,_E,_T,__,_0,_V,_E,_R,_C,_0,_M,_E
		.BYTE $40
_type_msg0A_5th_last_target_overcome:
		.WORD $CE20
		.BYTE _W,_E,_L,_L,__,_D,_0,_N,_E
		.BYTE $41
		.WORD $0B21
		.BYTE _5,_T,_H,__,_T,_A,_R,_G,_E,_T,__,_0,_V,_E,_R,_C,_0,_M,_E
		.BYTE $41
		.WORD $4921
		.BYTE _K,_E,_E,_P,__,_F,_I,_G,_H,_T,_I,_N,_G,__,__,_Y,_0,_U,__,_A,_R,_E
		.BYTE $41
		.WORD $6C21
		.BYTE _A,_L,_M,_0,_S,_T,__,_T,_H,_E,_R,_E
		.BYTE $40
_type_msg0C_ending:
		.WORD $8420
		.BYTE _Y,_0,_U,_sp,_H,_A,_V,_E,_sp,_S,_A,_V,_E,_D,_sp,_T,_H,_E,_sp,_W,_0,_R,_L,_D
		.BYTE $41
		.WORD $C820
		.BYTE _C,_0,_N,_G,_R,_A,_T,_U,_L,_A,_T,_I,_0,_N,_S
		.BYTE $41
		.WORD $0421
		.BYTE _P,_E,_A,_C,_E,_sp,_H,_A,_S,_sp,_A,_R,_R,_I,_V,_E,_D,_sp,_A,_T,_sp,_L,_A,_S,_T
		.BYTE $40
_type_msg0E:
		.WORD $6421
		.BYTE _P,_R,_0,_G,_R,_A,_M,_M,_E,_D,__,_B,_Y
		.BYTE $41
		.WORD $A921
		.BYTE _N,_A,_N,_I,_W,_A,__,_N,_0,__,_H,_I,_D,_E,_0
		.BYTE $40
_type_msg10:
		.WORD $6421
		.BYTE _C,_H,_A,_R,_A,_C,_T,_E,_R,__,_D,_E,_S,_I,_G,_N
		.BYTE $41
		.WORD $A921
		.BYTE _K,_E,_I,_K,_0,__,_A,_N,_D,__,_H,_A,_R,_A,_C,_H
		.BYTE _A,_N
		.BYTE $40
_type_msg12:
		.WORD $6421
		.BYTE _C,_H,_A,_R,_A,_C,_T,_E,_R,__,_D,_E,_S,_I,_G,_N
		.BYTE $41
		.WORD $A821
		.BYTE _G,_0,_K,_I,_G,_E,_N,__,_Y,_0,_S,_H,_I,_M,_0,_T
		.BYTE _0
		.BYTE $40
_type_msg14:
		.WORD $6421
		.BYTE _S,_0,_U,_N,_D,__,_D,_E,_S,_I,_G,_N
		.BYTE $41
		.WORD $A821
		.BYTE _C,_H,_A,_R,_Y,__,_S,_A,_D,_A,_K,_I,_C,_H,_I
		.BYTE $40
_type_msg16:
		.WORD $6421
		.BYTE _D,_I,_R,_E,_C,_T,_E,_D,__,_B,_Y
		.BYTE $41
		.WORD $AA21
		.BYTE _P,_H,_A,_Z,_E,_R,__,_A,_T,_S,_U,_K,_0
		.BYTE $40
_type_msg18:
		.WORD $6421
		.BYTE _V,_I,_S,_U,_A,_L,__,_D,_E,_S,_I,_G,_N
		.BYTE $41
		.WORD $A821
		.BYTE _S,_H,_I,_M,_0,_N,_E,_T,_A,__,_K,_E,_N,_C,_H,_A
		.BYTE _N
		.BYTE $40
_type_msg1A:
		.WORD $6421
		.BYTE _V,_I,_S,_U,_A,_L,__,_D,_E,_S,_I,_G,_N
		.BYTE $41
		.WORD $AA21
		.BYTE _D,_A,_I,_B,_U,_T,_S,_U,__,_M,_A,_R,_I
		.BYTE $40
_type_msg1C:
		.WORD $6421
		.BYTE _M,_U,_S,_I,_C,__,_B,_Y
		.BYTE $41
		.WORD $A721
		.BYTE _R,_U,_S,_H,_E,_R,__,_S,_A,_K,_A,_M,_0,_T,_0
		.BYTE $40
_type_msg1E:
		.WORD $6421
		.BYTE _M,_U,_S,_I,_C,__,_B,_Y
		.BYTE $41
		.WORD $A721
		.BYTE _I,_K,_U,__,_I,_K,_U,__,_M,_I,_Z,_U,_T,_A,_N,_I
		.BYTE $40
_type_msg20:
		.WORD $6421
		.BYTE _M,_U,_S,_I,_C,__,_B,_Y
		.BYTE $41
		.WORD $A921
		.BYTE _H,_E,_V,_I,_M,_E,_T,_A,__,_S,_A,_T,_0,_E
		.BYTE $40
_type_msg22:
		.WORD $6421
		.BYTE _M,_U,_S,_I,_C,__,_B,_Y
		.BYTE $41
		.WORD $A921
		.BYTE _N,_A,_N,_D,_A,__,_A,_D,_A,_C,_H,_I
		.BYTE $40
_type_msg24:
		.WORD $6421
		.BYTE _S,_P,_E,_C,_I,_A,_L,__,_T,_H,_A,_N,_K,_S
		.BYTE $41
		.WORD $A721
		.BYTE _H,_A,_S,_H,_I,_B,_0,_U,__,_A,_N,_D,__,_S,_H,_I,_N,_0,_B,_U
		.BYTE $40
#endif
#if LANGUAGE=LANG_EN

_type_msg00_your_mission_is:
		.WORD $A520
		.BYTE _Y,_0,_U,_R,__,_M,_I,_S,_S,_I,_0,_N,_dd
		.BYTE $41
		.WORD $C820
		.BYTE _D,_E,_S,_T,_R,_0,_Y,__,_T,_H,_E,__,_E,_N,_E,_M,_Y,_ap,_S
		.BYTE $41
		.WORD $E720
		.BYTE _S,_E,_C,_R,_E,_T,__,_W,_E,_A,_P,_0,_N,_dt
		.BYTE $41
		.WORD $EA21
		.BYTE _G,_0,_0,_D,__,_L,_U,_C,_K,_ex
		.BYTE $40
_type_msg02_1st_target_overcome:
		.WORD $CE20
		.BYTE _W,_E,_L,_L,__,_D,_0,_N,_E,_eX
		.BYTE $41
		.WORD $2B21
		.BYTE _1,_S,_T,__,_T,_A,_R,_G,_E,_T,__,_0,_V,_E,_R,_C,_0,_M,_E
		.BYTE $40
_type_msg04_2nd_target_overcome:
		.WORD $CE20
		.BYTE _W,_E,_L,_L,__,_D,_0,_N,_E,_eX
		.BYTE $41
		.WORD $2B21
		.BYTE _2,_N,_D,__,_T,_A,_R,_G,_E,_T,__,_0,_V,_E,_R,_C, _0,_M,_E
		.BYTE $40
_type_msg06_3rd_target_overcome:
		.WORD $CE20
		.BYTE _W,_E,_L,_L,__,_D,_0,_N,_E,_eX
		.BYTE $41
		.WORD $2B21
		.BYTE _3,_R,_D,__,_T,_A,_R,_G,_E,_T,__,_0,_V,_E,_R,_C,_0,_M,_E
		.BYTE $40
_type_msg08_4th_target_overcome:
		.WORD $CE20
		.BYTE _W,_E,_L,_L,__,_D,_0,_N,_E,_eX
		.BYTE $41
		.WORD $2B21
		.BYTE _4,_T,_H,__,_T,_A,_R,_G,_E,_T,__,_0,_V,_E,_R,_C,_0,_M,_E
		.BYTE $40
_type_msg0A_5th_last_target_overcome:
		.WORD $CE20
		.BYTE _W,_E,_L,_L,__,_D,_0,_N,_E,_eX
		.BYTE $41
		.WORD $0B21
		.BYTE _5,_T,_H,__,_T,_A,_R,_G,_E,_T,__,_0,_V,_E,_R,_C,_0,_M,_E
		.BYTE $41
		.WORD $4921
		.BYTE _K,_E,_E,_P,__,_F,_I,_G,_H,_T,_I,_N,_G,_eX,__,_Y,_0,_U,_ap,_R,_E
		.BYTE $41
		.WORD $6C21
		.BYTE _A,_L,_M,_0,_S,_T,__,_T,_H,_E,_R,_E,_dt
		.BYTE $40
_type_msg0C_ending:
		.WORD $8420
		.BYTE _Y,_0,_U,_sp,_H,_A,_V,_E,_sp,_S,_A,_V,_E,_D,_sp,_T,_H,_E,_sp,_W,_0,_R,_L,_D,_eX
		.BYTE $41
		.WORD $C820
		.BYTE _C,_0,_N,_G,_R,_A,_T,_U,_L,_A,_T,_I,_0,_N,_S,_eX
		.BYTE $41
		.WORD $0421
		.BYTE _P,_E,_A,_C,_E,_sp,_H,_A,_S,_sp,_A,_R,_R,_I,_V,_E,_D,_sp,_A,_T,_sp,_L,_A,_S,_T,_dt
		.BYTE $40
_type_msg0E:
		.WORD $6421
		.BYTE _P,_R,_0,_G,_R,_A,_M,_M,_E,_D,__,_B,_Y
		.BYTE $41
		.WORD $A921
		.BYTE _N,_A,_N,_I,_W,_A,__,_N,_0,__,_H,_I,_D,_E,_0
		.BYTE $40
_type_msg10:
		.WORD $6421
		.BYTE _C,_H,_A,_R,_A,_C,_T,_E,_R,__,_D,_E,_S,_I,_G,_N
		.BYTE $41
		.WORD $A921
		.BYTE _M,_A,_D,_A,_M,_U,__,_K,_E,_I,_K,_0
		.BYTE $40
_type_msg12:
		.WORD $6421
		.BYTE _C,_H,_A,_R,_A,_C,_T,_E,_R,__,_D,_E,_S,_I,_G,_N
		.BYTE $41
		.WORD $A821
		.BYTE _G,_0,_K,_I,_G,_E,_N,__,_Y,_0,_S,_H,_I,_M,_0,_T,_0
		.BYTE $40
_type_msg14:
		.WORD $6421
		.BYTE _S,_0,_U,_N,_D,__,_D,_E,_S,_I,_G,_N
		.BYTE $41
		.WORD $A821
		.BYTE _C,_H,_A,_R,_Y,__,_S,_A,_D,_A,_K,_I,_C,_H,_I
		.BYTE $40
_type_msg16:
		.WORD $6421
		.BYTE _D,_I,_R,_E,_C,_T,_E,_D,__,_B,_Y
		.BYTE $41
		.WORD $AA21
		.BYTE _P,_H,_A,_Z,_E,_R,__,_A,_T,_S,_U,_K,_0
		.BYTE $40
_type_msg18:
		.WORD $6421
		.BYTE _V,_I,_S,_U,_A,_L,__,_D,_E,_S,_I,_G,_N
		.BYTE $41
		.WORD $A921
		.BYTE _K,_E,_N,_j,_I,__,_S,_H,_I,_M,_0,_N,_E,_T,_A
		.BYTE $40
_type_msg1A:
		.WORD $6421
		.BYTE _V,_I,_S,_U,_A,_L,__,_D,_E,_S,_I,_G,_N
		.BYTE $41
		.WORD $AA21
		.BYTE _D,_A,_I,_B,_U,_T,_S,_U,__,_M,_A,_R,_I
		.BYTE $40
_type_msg1C:
		.WORD $6421
		.BYTE _M,_U,_S,_I,_C,__,_B,_Y
		.BYTE $41
		.WORD $A721
		.BYTE _R,_U,_S,_H,_E,_R,__,_S,_A,_K,_A,_M,_0,_T,_0
		.BYTE $40
_type_msg1E:
		.WORD $6421
		.BYTE _M,_U,_S,_I,_C,__,_B,_Y
		.BYTE $41
		.WORD $A721
		.BYTE _I,_K,_U,__,_I,_K,_U,__,_M,_I,_Z,_U,_T,_A,_N,_I
		.BYTE $40
_type_msg20:
		.WORD $6421
		.BYTE _M,_U,_S,_I,_C,__,_B,_Y
		.BYTE $41
		.WORD $A921
		.BYTE _H,_E,_V,_I,_M,_E,_T,_A,__,_S,_A,_T,_0,_E
		.BYTE $40
_type_msg22:
		.WORD $6421
		.BYTE _M,_U,_S,_I,_C,__,_B,_Y
		.BYTE $41
		.WORD $A921
		.BYTE _N,_A,_N,_D,_A,__,_A,_D,_A,_C,_H,_I
		.BYTE $40
_type_msg24:
		.WORD $6421
		.BYTE _S,_P,_E,_C,_I,_A,_L,__,_T,_H,_A,_N,_K,_S
		.BYTE $41
		.WORD $A721
		.BYTE _0,_N,_I,_Y,_A,_N,_K,_0,__,_S,_H,_I,_N,_0,_B,_U
		.BYTE $40
#endif

		SECTION_END "TYPE MSG LIB"

		SECTION_START
		FAR_PTR	_screen_libs

_screen_lib0_blank:
		.WORD _scr0_01
		.WORD _scr0_01
		.WORD _scr0_23
		.WORD _scr0_23
_scr0_01:
		.BYTE $34,$C0,$00,$34,$C0,$00,$34,$C0,$00,$34,$E0,$00,$34,$E0,$00
_scr0_23:
		.BYTE $39
_screen_lib2_title:
		.WORD _scr2_0
		.WORD _scr2_1
		.WORD _scr2_2
		.WORD _scr2_3
_scr2_0:
		.BYTE $34,$8B,$00,$31,$32,$27,$28,$29,$2A,$2B,$2C,$2D,$2E,$2F,$34,$14
		.BYTE $00,$40,$35,$36,$37,$38,$BF,$3A,$3B,$3C,$3D,$3E,$3F,$34,$14,$00
		.BYTE $33,$30,$39
_scr2_1:
		.BYTE $34,$39,$00,$41,$42,$43,$44,$45,$46,$47,$48,$49,$4A,$4B,$4C,$4D
		.BYTE $4E,$4F,$C0,$C1,$C2,$C3,$C4,$C5,$C6,$C7,$EB,$34,$07,$00,$50,$51
		.BYTE $52,$53,$54,$55,$56,$57,$58,$59,$5A,$5B,$5C,$5D,$5E,$5F,$D0,$D1
		.BYTE $D2,$D3,$D4,$D5,$D6,$D7,$34,$08,$00,$60,$61,$62,$63,$64,$65,$66
		.BYTE $67,$68,$69,$6A,$6B,$6C,$6D,$6E,$6F,$E0,$E1,$E2,$E3,$E4,$E5,$E6
		.BYTE $34,$09,$00,$70,$71,$72,$73,$74,$75,$76,$77,$78,$79,$7A,$7B,$7C
		.BYTE $7D,$7E,$7F,$F0,$F1,$F2,$F3,$F4,$F5,$34,$2B,$00,$81,$82,$83,$84
		.BYTE $85,$86,$87,$88,$89,$8A,$8B,$8C,$8D,$8E,$8F,$C8,$C9,$CA,$CB,$CC
		.BYTE $CD,$CE,$CF,$EE,$34,$08,$00,$91,$92,$93,$94,$95,$96,$97,$98,$99
		.BYTE $9A,$9B,$9C,$9D,$9E,$9F,$D8,$D9,$DA,$DB,$DC,$DD,$DE,$DF,$EF,$34
		.BYTE $08,$00,$A1,$A2,$00,$A4,$A5,$A6,$A7,$A8,$A9,$AA,$AB,$AC,$AD,$AE
		.BYTE $AF,$E8,$E9,$EA,$00,$EC,$ED,$39
_scr2_2:
		.BYTE $34,$0A,$00,$B0,$B1,$B2,$B3,$B4,$B5,$B6,$B7,$B8,$B9,$BA,$BB,$BC
		.BYTE $BD,$BE,$87,$F6,$F7,$F8,$80,$90,$A0,$00,$1E,$17,$34,$2D,$00,$F9
		.BYTE $00,$15,$01,$18,$0B,$17,$13,$00,$02,$0A,$09,$08,$34,$54,$00,$1A
		.BYTE $16,$0B,$23,$00,$1D,$0F,$16,$0F,$0D,$1E,$34,$38,$00,$02,$00,$1A
		.BYTE $16,$0B,$23,$0F,$1C,$34,$18,$00,$03,$00,$1A,$16,$0B,$23,$0F,$1C
		.BYTE $1D,$34,$B3,$00,$88,$0A,$0A,$02,$00,$00,$00,$34,$06,$55,$01,$00
		.BYTE $34,$06,$55,$11,$00,$34,$05,$05,$09,$02,$34,$18,$00
_scr2_3:
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
_screen_lib6_intro:
		.WORD _scr6_0
		.WORD _scr6_1
		.WORD _scr6_2
		.WORD _scr6_3
_scr6_0:
		.BYTE $34,$35,$00,$E4,$34,$06,$00,$9E,$00,$00,$00,$34,$05,$00,$9E,$34
		.BYTE $1A,$00,$00,$E3,$34,$08,$00,$E4,$00,$00,$9F,$34,$0C,$00,$D8,$34
		.BYTE $05,$00,$34,$20,$00,$00,$00,$9E,$34,$1D,$00,$34,$40,$00,$39
_scr6_1:
		.BYTE $00,$00,$00,$9F,$34,$05,$00,$89,$8A,$34,$09,$00,$30,$35,$36,$37
		.BYTE $38,$31,$3A,$34,$05,$00,$34,$06,$00,$96,$97,$98,$99,$9A,$9B,$9C
		.BYTE $9D,$9E,$00,$00,$00,$42,$43,$44,$45,$46,$47,$48,$49,$4A,$4B,$34
		.BYTE $04,$00,$A0,$A1,$00,$A3,$A4,$A5,$A6,$A7,$A8,$A9,$AA,$AB,$AC,$AD
		.BYTE $AE,$AF,$50,$51,$52,$53,$54,$55,$56,$57,$58,$59,$5A,$5B,$5C,$5D
		.BYTE $5E,$5F,$B0,$B1,$B2,$B3,$B4,$B5,$B6,$B7,$B8,$B9,$BA,$BB,$BC,$BD
		.BYTE $BE,$BF,$60,$61,$62,$63,$64,$65,$66,$67,$68,$69,$6A,$6B,$6C,$6D
		.BYTE $6E,$6F,$C0,$C1,$C2,$C3,$C4,$C5,$C6,$C7,$C8,$C9,$CA,$CB,$CC,$CD
		.BYTE $CE,$CF,$70,$71,$72,$73,$74,$75,$76,$77,$78,$79,$7A,$7B,$7C,$7D
		.BYTE $7E,$7F,$D0,$D1,$D2,$D3,$D4,$D5,$D6,$00,$D8,$D9,$DA,$DB,$DC,$DD
		.BYTE $DE,$8F,$8E,$34,$0A,$00,$8B,$8C,$8D,$8E,$8F,$34,$20,$00,$34,$16
		.BYTE $00,$D8,$34,$09,$00,$39
_scr6_2:
		.BYTE $00,$E3,$34,$17,$00,$9E,$34,$06,$00,$E2,$E6,$00,$EF,$E4,$F8,$F0
		.BYTE $E6,$E0,$E1,$E2,$FF,$EF,$D8,$F7,$D8,$00,$00,$EB,$00,$9E,$9F,$00
		.BYTE $D8,$00,$00,$9E,$ED,$00,$00,$00,$F9,$34,$08,$00,$9F,$00,$00,$41
		.BYTE $00,$00,$00,$F7,$F0,$E5,$E5,$EF,$00,$EE,$F1,$E2,$E3,$EE,$3B,$EF
		.BYTE $FF,$40,$41,$EF,$00,$00,$00,$9F,$34,$10,$00,$D7,$EA,$EB,$EC,$ED
		.BYTE $ED,$F0,$F3,$00,$E6,$00,$9E,$00,$00,$00,$F9,$D8,$EB,$88,$00,$00
		.BYTE $9F,$34,$05,$00,$9E,$E7,$F9,$00,$00,$F1,$33,$FB,$FC,$FD,$E5,$F1
		.BYTE $88,$00,$00,$00,$9F,$34,$0B,$00,$D8,$00,$EF,$EA,$E6,$E5,$EA,$ED
		.BYTE $E5,$F3,$D7,$00,$D8,$FB,$FE,$F7,$9E,$D8,$EF,$9E,$00,$34,$09,$00
		.BYTE $85,$86,$00,$9E,$E3,$00,$00,$00,$88,$E5,$F8,$E1,$00,$D8,$34,$07
		.BYTE $00,$9F,$00,$34,$04,$00,$2A,$2B,$2C,$2D,$2E,$95,$87,$E3,$00,$00
		.BYTE $00,$F9,$00,$40,$F3,$34,$05,$00,$2A,$2B,$2F,$2D,$2A,$2B,$2F,$2D
		.BYTE $39
_scr6_3:
		.BYTE $3C,$3D,$3C,$3D,$3C,$29,$82,$83,$80,$81,$84,$D9,$E0,$E5,$EE,$EF
		.BYTE $80,$83,$82,$81,$3C,$3D,$3C,$3D,$3C,$3D,$3C,$3D,$3C,$3D,$3C,$3D
		.BYTE $4C,$4D,$4C,$4D,$27,$28,$92,$93,$90,$91,$94,$9F,$F1,$E1,$FE,$FF
		.BYTE $90,$93,$92,$91,$4E,$4F,$4E,$4F,$4C,$4D,$4C,$4D,$4C,$4D,$4C,$4D
		.BYTE $34,$20,$3F,$34,$20,$3E,$34,$40,$00,$30,$20,$C0,$20,$00,$03,$C0
		.BYTE $02,$08,$34,$07,$00,$08,$34,$0C,$00,$C0,$00,$00,$8B,$0F,$EF,$CF
		.BYTE $FC,$FE,$EF,$EC,$0C,$0F,$0E,$FF,$FE,$FF,$0B,$0B,$05,$01,$00,$0E
		.BYTE $00,$05,$05,$05,$34,$04,$0F,$34,$04,$00,$39
_screen_lib8_final_stage_complete:
		.WORD _scr8_0
		.WORD _scr8_1
		.WORD _scr8_2
		.WORD _scr8_3
_scr8_0:
		.BYTE $34,$D8,$27,$37,$27,$2B,$2B,$2C,$27,$37,$27,$27,$27,$29,$27,$27
		.BYTE $27,$2B,$2C,$27,$29,$2B,$2B,$2C,$2B,$2E,$2C,$2E,$2C,$38,$2C,$2A
		.BYTE $2D,$2C,$34,$04,$27,$36,$27,$2B,$2C,$27,$39
_scr8_1:
		.BYTE $27,$27,$2A,$2D,$2E,$2E,$2C,$28,$2E,$2C,$2E,$2C,$2F,$28,$28,$4F
		.BYTE $00,$00,$46,$3F,$2E,$2C,$3D,$2E,$2E,$2C,$38,$3F,$2E,$36,$27,$27
		.BYTE $27,$27,$27,$2B,$2F,$3F,$34,$04,$28,$3D,$3C,$3D,$28,$5E,$5F,$8B
		.BYTE $8B,$56,$28,$28,$3D,$2F,$2F,$36,$2F,$34,$04,$28,$2E,$2C,$27,$29
		.BYTE $27,$27,$3E,$2F,$3D,$2F,$3F,$3C,$2F,$28,$28,$28,$6E,$6F,$99,$9A
		.BYTE $9B,$34,$06,$28,$2F,$3D,$3D,$2F,$2F,$36,$36,$27,$27,$27,$2A,$2F
		.BYTE $34,$09,$28,$7E,$7F,$8A,$8A,$AB,$34,$04,$28,$2F,$2F,$34,$04,$28
		.BYTE $3F,$35,$3B,$34,$04,$27,$3E,$3B,$3E,$3A,$3E,$3B,$3A,$3E,$48,$49
		.BYTE $4A,$4B,$00,$8B,$00,$BC,$3B,$27,$3E,$35,$3B,$36,$3A,$43,$37,$27
		.BYTE $27,$27,$34,$06,$27,$30,$31,$32,$34,$04,$27,$59,$5A,$5B,$00,$8A
		.BYTE $8A,$BB,$2B,$2B,$2C,$34,$09,$27,$34,$06,$27,$40,$41,$42,$27,$88
		.BYTE $67,$68,$69,$E2,$6B,$AA,$8B,$AA,$BA,$27,$3A,$34,$0A,$27,$34,$06
		.BYTE $27,$50,$27,$27,$27,$8B,$8A,$78,$79,$7A,$6B,$00,$8A,$8A,$B9,$87
		.BYTE $88,$87,$67,$34,$08,$27,$39
_scr8_2:
		.BYTE $60,$61,$34,$04,$27,$76,$27,$88,$69,$8A,$8B,$8C,$79,$00,$00,$8A
		.BYTE $00,$00,$00,$79,$A9,$79,$8A,$27,$27,$67,$A8,$A8,$27,$27,$27,$70
		.BYTE $71,$72,$73,$74,$75,$76,$77,$98,$79,$00,$8A,$34,$0C,$00,$A9,$A9
		.BYTE $00,$B8,$B8,$77,$74,$75,$80,$81,$82,$83,$84,$85,$95,$95,$86,$94
		.BYTE $86,$86,$00,$95,$86,$00,$00,$00,$95,$94,$95,$95,$00,$00,$95,$95
		.BYTE $86,$86,$86,$94,$84,$85,$90,$91,$92,$93,$94,$94,$95,$94,$95,$94
		.BYTE $27,$94,$27,$94,$95,$94,$95,$94,$94,$95,$94,$94,$95,$94,$94,$27
		.BYTE $94,$95,$95,$A4,$B6,$A4,$A0,$A1,$A2,$34,$05,$27,$A4,$A5,$A6,$A5
		.BYTE $B6,$A5,$B6,$A4,$A6,$27,$27,$A7,$A7,$A5,$A6,$B5,$B6,$A5,$B6,$A5
		.BYTE $B5,$A5,$27,$27,$B0,$B1,$B2,$B3,$A4,$A4,$A5,$A4,$A6,$A4,$A6,$A4
		.BYTE $27,$A4,$A7,$A6,$A5,$A6,$B5,$27,$27,$27,$A4,$B6,$B5,$27,$27,$A4
		.BYTE $B5,$A4,$B5,$A4,$27,$A4,$A5,$A6,$B3,$34,$05,$27,$A4,$B5,$A6,$A4
		.BYTE $A7,$A5,$27,$27,$27,$A4,$A5,$A4,$B5,$27,$27,$27,$A4,$A5,$27,$27
		.BYTE $27,$B3,$27,$27,$B4,$27,$A4,$A7,$A5,$A6,$34,$15,$27,$B3,$27,$B4
		.BYTE $39
_scr8_3:
		.BYTE $27,$B3,$34,$1D,$27,$B3,$27,$27,$27,$B7,$27,$B4,$27,$27,$B4,$27
		.BYTE $27,$B3,$34,$0B,$27,$B4,$34,$06,$27,$B7,$27,$B4,$27,$27,$27,$B3
		.BYTE $34,$0E,$27,$B4,$34,$08,$27,$B3,$27,$27,$27,$27,$27,$B3,$34,$05
		.BYTE $27,$B3,$34,$05,$27,$B4,$34,$05,$27,$B3,$34,$04,$27,$B3,$34,$05
		.BYTE $27,$B4,$34,$04,$00,$34,$04,$C0,$34,$1C,$00,$34,$04,$C0,$34,$18
		.BYTE $00,$34,$34,$23,$C0,$34,$20,$00,$34,$08,$50,$34,$10,$55,$00,$05
		.BYTE $00,$0F,$0C,$03,$03,$0F,$39

		SECTION_END "SCREEN LIB"

		BANK_END 6,$C000
