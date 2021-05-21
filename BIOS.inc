		ORG $E000
		.BYTE $00
_BIOS_chr_fonts_data:
		.BYTE $38,$4C,$C6,$C6,$C6,$64,$38,$00
		.BYTE $18,$38,$18,$18,$18,$18,$7E,$00
		.BYTE $7C,$C6,$0E,$3C,$78,$E0,$FE,$00
		.BYTE $7E,$0C,$18,$3C,$06,$C6,$7C,$00
		.BYTE $1C,$3C,$6C,$CC,$FE,$0C,$0C,$00
		.BYTE $FC,$C0,$FC,$06,$06,$C6,$7C,$00
		.BYTE $3C,$60,$C0,$FC,$C6,$C6,$7C,$00
		.BYTE $FE,$C6,$0C,$18,$30,$30,$30,$00
		.BYTE $7C,$C6,$C6,$7C,$C6,$C6,$7C,$00
		.BYTE $7C,$C6,$C6,$7E,$06,$0C,$78,$00
		.BYTE $38,$6C,$C6,$C6,$FE,$C6,$C6,$00
		.BYTE $FC,$C6,$C6,$FC,$C6,$C6,$FC,$00
		.BYTE $3C,$66,$C0,$C0,$C0,$66,$3C,$00
		.BYTE $F8,$CC,$C6,$C6,$C6,$CC,$F8,$00
		.BYTE $FE,$C0,$C0,$FC,$C0,$C0,$FE,$00
		.BYTE $FE,$C0,$C0,$FC,$C0,$C0,$C0,$00
		.BYTE $3E,$60,$C0,$DE,$C6,$66,$7E,$00
		.BYTE $C6,$C6,$C6,$FE,$C6,$C6,$C6,$00
		.BYTE $7E,$18,$18,$18,$18,$18,$7E,$00
		.BYTE $1E,$06,$06,$06,$C6,$C6,$7C,$00
		.BYTE $C6,$CC,$D8,$F0,$F8,$DC,$CE,$00
		.BYTE $60,$60,$60,$60,$60,$60,$7E,$00
		.BYTE $C6,$EE,$FE,$FE,$D6,$C6,$C6,$00
		.BYTE $C6,$E6,$F6,$FE,$DE,$CE,$C6,$00
		.BYTE $7C,$C6,$C6,$C6,$C6,$C6,$7C,$00
		.BYTE $FC,$C6,$C6,$C6,$FC,$C0,$C0,$00
		.BYTE $7C,$C6,$C6,$C6,$DE,$CC,$7A,$00
		.BYTE $FC,$C6,$C6,$CE,$F8,$DC,$CE,$00
		.BYTE $78,$CC,$C0,$7C,$06,$C6,$7C,$00
		.BYTE $7E,$18,$18,$18,$18,$18,$18,$00
		.BYTE $C6,$C6,$C6,$C6,$C6,$C6,$7C,$00
		.BYTE $C6,$C6,$C6,$EE,$7C,$38,$10,$00
		.BYTE $C6,$C6,$D6,$FE,$FE,$EE,$C6,$00
		.BYTE $C6,$EE,$7C,$38,$7C,$EE,$C6,$00
		.BYTE $66,$66,$66,$3C,$18,$18,$18,$00
		.BYTE $FE,$0E,$1C,$38,$70,$E0,$FE,$00
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00
		.BYTE $00,$00,$00,$00,$30,$30,$20,$00
		.BYTE $00,$00,$00,$00,$30,$30,$00,$00
		.BYTE $00,$00,$00,$00,$6C,$6C,$08,$00
		.BYTE $38,$44,$BA,$AA,$B2,$AA,$44,$38

; =============== S U B	R O U T	I N E =======================================
_BIOS_sub_E149:
		PHA
		LDA		#$16
		SEC
loc_E14D:
		SBC		#$01
		BCS		loc_E14D
		PLA
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_sub_E153:
		LDX		word_0
		LDX		#$FE
loc_E157:
		NOP
		DEX
		BNE		loc_E157
		CMP		word_0
		DEY
		BNE		_BIOS_sub_E153
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_sub_E161:
		LDA		_ppu_mask_shadow
		AND		#$E7

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_mask_set:
		STA		_ppu_mask_shadow
		STA		_PPU_MASK
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_render_on:
		LDA		_ppu_mask_shadow
		ORA		#$18
		BNE		_BIOS_ppu_mask_set

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_sprites_off:
		LDA		_ppu_mask_shadow
		AND		#$EF
		JMP		_BIOS_ppu_mask_set

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_sprites_on:
		LDA		_ppu_mask_shadow
		ORA		#$10
		BNE		_BIOS_ppu_mask_set

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_bg_off:
		LDA		_ppu_mask_shadow
		AND		#$F7
		JMP		_BIOS_ppu_mask_set

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_bg_on:
		LDA		_ppu_mask_shadow
		ORA		#$08
		BNE		_BIOS_ppu_mask_set

; =============== S U B	R O U T	I N E =======================================
_BIOS_NMI:
		BIT		byte_100
		BPL		loc_E198
		BVC		loc_E195
		JMP		(off_DFFA)
; ---------------------------------------------------------------------------
loc_E195:
		JMP		(off_DFF8)
; ---------------------------------------------------------------------------
loc_E198:
		BVC		loc_E19D
		JMP		(off_DFF6)
; ---------------------------------------------------------------------------
loc_E19D:
		LDA		_ppu_ctrl_shadow
		AND		#$7F
		STA		_ppu_ctrl_shadow
		STA		_PPU_CTRL
		LDA		_PPU_STATUS
		PLA
		PLA
		PLA
		PLA
		STA		byte_100
		PLA
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_wait_for_nmi_mode00:
		PHA
		LDA		byte_100
		PHA
		LDA		#$00
		STA		byte_100
		LDA		_ppu_ctrl_shadow
		ORA		#$80
		STA		_ppu_ctrl_shadow
		STA		_PPU_CTRL
loc_E1C5:
		BNE		loc_E1C5

; =============== S U B	R O U T	I N E =======================================
_BIOS_IRQ:
		BIT		byte_101
		BMI		loc_E1EA
		BVC		loc_E1D9
		LDX		_FDS_REG31
		STA		_FDS_REG24
		PLA
		PLA
		PLA
		TXA
		RTS
; ---------------------------------------------------------------------------
loc_E1D9:
		PHA
		LDA		byte_101
		SEC
		SBC		#$01
		BCC		loc_E1E8
		STA		byte_101
		LDA		_FDS_REG31
loc_E1E8:
		PLA
		RTI
; ---------------------------------------------------------------------------
loc_E1EA:
		BVC		loc_E1EF
		JMP		(off_DFFE)
; ---------------------------------------------------------------------------
loc_E1EF:
		PHA
		LDA		_FDS_REG30
		JSR		_BIOS_sub_E149
		PLA
		RTI

; =============== S U B	R O U T	I N E =======================================
_BIOS_load_files_by_idx:
		LDA		#$00
		STA		byte_E
		LDA		#$FF
		JSR		sub_E3E7
		LDA		byte_101
		PHA
		LDA		#$02
		STA		word_4+1
loc_E209:
		JSR		sub_E21A
		BEQ		loc_E212
		DEC		word_4+1
		BNE		loc_E209
loc_E212:
		PLA
		STA		byte_101
		LDY		byte_E
		TXA
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E21A:
		JSR		_BIOS_check_disk_header
		JSR		_BIOS_get_files_count
		LDA		byte_6
		BEQ		loc_E233
loc_E224:
		LDA		#$03
		JSR		sub_E68F
		JSR		_BIOS_file_match_test
		JSR		sub_E4F9
		DEC		byte_6
		BNE		loc_E224
loc_E233:
		JSR		_BIOS_end_of_irq_break_if_no_zero_exit_code0
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_append_file:
		LDA		#$FF

; =============== S U B	R O U T	I N E =======================================
_BIOS_write_file:
		STA		byte_E
		LDA		#$FF
		JSR		loc_E3EA
		LDA		byte_101
		PHA
		LDA		#$03
		STA		word_4+1
loc_E248:
		DEC		word_4+1
		BEQ		loc_E265
		JSR		sub_E26B
		BNE		loc_E248
		LDA		#$02
		STA		word_4+1
loc_E255:
		JSR		sub_E290
		BEQ		loc_E265
		DEC		word_4+1
		BNE		loc_E255
		STX		word_4+1
		JSR		sub_E2AB
		LDX		word_4+1
loc_E265:
		PLA
		STA		byte_101
		TXA
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E26B:
		JSR		_BIOS_check_disk_header
		LDA		byte_E
		CMP		#$FF
		BNE		loc_E288
		JSR		_BIOS_get_files_count
loc_E277:
		JSR		_BIOS_skip_files
		LDA		#$03
		JSR		sub_E6B0
		LDA		#$00
		JSR		sub_E5B5
		JSR		_BIOS_end_of_irq_break_if_no_zero_exit_code0
		RTS
; ---------------------------------------------------------------------------
loc_E288:
		STA		byte_6
		JSR		_BIOS_set_files_num
		JMP		loc_E277

; =============== S U B	R O U T	I N E =======================================
sub_E290:
		JSR		_BIOS_check_disk_header
		LDX		byte_6
		INX
		TXA
		JSR		_BIOS_set_files_num
		JSR		_BIOS_skip_files
		LDA		#$03
		JSR		sub_E68F
		LDA		#$FF
		JSR		sub_E5B5
		JSR		_BIOS_end_of_irq_break_if_no_zero_exit_code0
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E2AB:
		JSR		_BIOS_check_disk_header
		LDA		byte_6
		JSR		_BIOS_set_files_num
		JSR		_BIOS_end_of_irq_break_if_no_zero_exit_code0
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_check_file_count:
		LDX		#$FF
		BNE		_BIOS_get_file_count
_BIOS_adjust_file_count:
		LDX		#$00

; =============== S U B	R O U T	I N E =======================================
_BIOS_get_file_count:
		STX		byte_9
		JSR		loc_E3EA
		LDA		byte_101
		PHA
		LDA		#$03
		STA		word_4+1
loc_E2CA:
		DEC		word_4+1
		BEQ		loc_E2F1
		JSR		sub_E2F7
		BNE		loc_E2CA
		LDA		byte_6
		SEC
loc_E2D6:
		SBC		byte_2
		LDX		byte_9
		BEQ		loc_E2DE
		LDA		byte_2
loc_E2DE:
		LDX		#$31
		BCC		loc_E2F1
		STA		byte_6
		LDA		#$02
		STA		word_4+1
loc_E2E8:
		JSR		sub_E2AB
		BEQ		loc_E2F1
		DEC		word_4+1
		BNE		loc_E2E8
loc_E2F1:
		PLA
		STA		byte_101
		TXA
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E2F7:
		JSR		_BIOS_check_disk_header
		JSR		_BIOS_get_files_count
loc_E2FD:
		JSR		_BIOS_end_of_irq_break_if_no_zero_exit_code0
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_set_file_count1:
		LDX		#$01
		BNE		_BIOS_set_file_count_ex
_BIOS_set_file_count0:
		LDX		#$00

; =============== S U B	R O U T	I N E =======================================
_BIOS_set_file_count_ex:
		STX		byte_7
		JSR		loc_E3EA
		LDA		byte_101
		PHA
		CLC
		LDA		byte_2
		ADC		byte_7
		STA		byte_6
		LDA		#$02
		STA		word_4+1
loc_E31B:
		JSR		sub_E2AB
		BEQ		loc_E324
		DEC		word_4+1
		BNE		loc_E31B
loc_E324:
		PLA
		STA		byte_101
		TXA
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_get_disk_info:
		LDA		#$00
		JSR		sub_E3E7
		LDA		byte_101
		PHA
		LDA		#$02
		STA		word_4+1
loc_E337:
		JSR		sub_E346
		BEQ		loc_E340
		DEC		word_4+1
		BNE		loc_E337
loc_E340:
		PLA
		STA		byte_101
		TXA
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E346:
		JSR		_BIOS_disk_signature_check
		LDA		word_0
		STA		byte_A
		LDA		word_0+1
		STA		byte_B
		LDY		#$00
		STY		byte_2
		STY		byte_3
loc_E357:
		JSR		_BIOS_wait_for_disk_irq
		STA		(byte_A),Y
		INY
		CPY		#$0A
		BNE		loc_E357
		JSR		_BIOS_disk_data_ptr_add
		LDY		#$1F
loc_E366:
		JSR		_BIOS_wait_for_disk_irq
		DEY
		BNE		loc_E366
		JSR		sub_E706
		JSR		_BIOS_get_files_count
		LDY		#$00
		LDA		byte_6
		STA		(byte_A),Y
		BEQ		loc_E3CB
loc_E37A:
		LDA		#$03
		JSR		sub_E68F
		JSR		_BIOS_wait_for_disk_irq
		JSR		_BIOS_wait_for_disk_irq
		LDY		#$01
		STA		(byte_A),Y
loc_E389:
		INY
		JSR		_BIOS_wait_for_disk_irq
		STA		(byte_A),Y
		CPY		#$09
		BNE		loc_E389
		JSR		_BIOS_disk_data_ptr_add
		JSR		_BIOS_wait_for_disk_irq
		JSR		_BIOS_wait_for_disk_irq
		CLC
		LDA		#$05
		ADC		byte_2
		STA		byte_2
		LDA		#$01
		ADC		byte_3
		STA		byte_3
		JSR		_BIOS_wait_for_disk_irq
		STA		byte_C
		JSR		_BIOS_wait_for_disk_irq
		STA		byte_D
		CLC
		LDA		byte_C
		ADC		byte_2
		STA		byte_2
		LDA		byte_D
		ADC		byte_3
		STA		byte_3
		LDA		#$FF
		STA		byte_9
		JSR		loc_E506
		DEC		byte_6
		BNE		loc_E37A
loc_E3CB:
		LDA		byte_3
		LDY		#$01
		STA		(byte_A),Y
		LDA		byte_2
		INY
		STA		(byte_A),Y
		JSR		_BIOS_end_of_irq_break_if_no_zero_exit_code0
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_disk_data_ptr_add:
		TYA
		CLC
		ADC		byte_A
		STA		byte_A
		LDA		#$00
		ADC		byte_B
		STA		byte_B
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E3E7:
		SEC
		BCS		loc_E3EB
loc_E3EA:
		CLC
loc_E3EB:
		TSX
		DEX
		STX		word_4
		PHP
		STA		byte_2
		LDY		byte_104,X
		STY		word_4+1
		LDY		byte_105,X
		STY		byte_6
		TAX
		LDY		#$01
		LDA		(word_4+1),Y
		STA		word_0
		INY
		LDA		(word_4+1),Y
		STA		word_0+1
		LDA		#$02
		CPX		#$FF
		BNE		loc_E41A
		INY
		LDA		(word_4+1),Y
		STA		byte_2
		INY
		LDA		(word_4+1),Y
		STA		byte_3
		LDA		#$04
loc_E41A:
		LDX		word_4
		CLC
		ADC		word_4+1
		STA		byte_104,X
		LDA		#$00
		ADC		byte_6
		STA		byte_105,X
		PLP
		LDX		#$01
		LDA		_FDS_REG32
		AND		#$01
		BNE		loc_E43E
		BCS		locret_E444
		LDX		#$03
		LDA		_FDS_REG32
		AND		#$04
		BEQ		locret_E444
loc_E43E:
		PLA
		PLA
		LDY		byte_E
		TXA
		CLI
locret_E444:
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_check_disk_header:
		JSR		_BIOS_disk_signature_check
		LDX		#$04
		STX		byte_8
		LDY		#$00
loc_E44E:
		JSR		_BIOS_wait_for_disk_irq
		CMP		(word_0),Y
		BEQ		loc_E464
		LDX		byte_8
		CPX		#$0A
		BNE		loc_E45D
		LDX		#$10
loc_E45D:
		LDA		(word_0),Y
		CMP		#$FF
		JSR		_BIOS_end_of_irq_break_if_no_zero
loc_E464:
		INY
		CPY		#$01
		BEQ		loc_E46D
		CPY		#$05
		BCC		loc_E46F
loc_E46D:
		INC		byte_8
loc_E46F:
		CPY		#$0A
		BNE		loc_E44E
		JSR		_BIOS_wait_for_disk_irq
		STA		byte_8
		LDY		#$1E
loc_E47A:
		JSR		_BIOS_wait_for_disk_irq
		DEY
		BNE		loc_E47A
		JSR		sub_E706
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_get_files_count:
		LDA		#$02
		JSR		sub_E68F
		JSR		_BIOS_wait_for_disk_irq
		STA		byte_6
		JSR		sub_E706
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_set_files_num:
		PHA
		LDA		#$02
		JSR		sub_E6B0
		PLA
		JSR		_BIOS_wait_for_disk_irq
		JSR		sub_E729
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_file_match_test:
		JSR		_BIOS_wait_for_disk_irq
		JSR		_BIOS_wait_for_disk_irq
		LDA		#$08
		STA		byte_101
		CLI
		LDY		#$00
		LDA		(byte_2),Y
		CMP		#$FF
		BEQ		loc_E4C8
loc_E4B4:
		TXA
		CMP		(byte_2),Y
		BEQ		loc_E4CE
		INY
		CPY		#$14
		BEQ		loc_E4C4
		LDA		(byte_2),Y
		CMP		#$FF
		BNE		loc_E4B4
loc_E4C4:
		LDA		#$FF
		BNE		loc_E4D2
loc_E4C8:
		CPX		byte_8
		BEQ		loc_E4CE
		BCS		loc_E4D2
loc_E4CE:
		LDA		#$00
		INC		byte_E
loc_E4D2:
		STA		byte_9
loc_E4D4:
		LDA		byte_101
		BNE		loc_E4D4
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_skip_files:
		LDA		byte_6
		STA		byte_8
		BEQ		locret_E4F8
loc_E4E0:
		LDA		#$03
		JSR		sub_E68F
		LDY		#$0A
loc_E4E7:
		JSR		_BIOS_wait_for_disk_irq
		DEY
		BNE		loc_E4E7
		LDA		#$FF
		STA		byte_9
		JSR		sub_E4F9
		DEC		byte_8
		BNE		loc_E4E0
locret_E4F8:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E4F9:
		LDY		#$00
loc_E4FB:
		JSR		_BIOS_wait_for_disk_irq_mode40
		STA		byte_A,Y
		INY
		CPY		#$04
		BNE		loc_E4FB
loc_E506:
		JSR		_BIOS_dec_data_size
		JSR		_BIOS_wait_for_disk_irq
		PHA
		JSR		sub_E706
		LDA		#$04
		JSR		sub_E68F
		LDY		byte_9
		PLA
		BNE		loc_E549
		CLC
		LDA		byte_A
		ADC		byte_C
		LDA		byte_B
		ADC		byte_D
		BCS		loc_E531
		LDA		byte_B
		CMP		#$20
		BCS		loc_E533
		AND		#$07
		CMP		#$02
		BCS		loc_E533
loc_E531:
		LDY		#$FF
loc_E533:
		JSR		_BIOS_wait_for_disk_irq
		CPY		#$00
		BNE		loc_E542
		STA		(byte_A),Y
		INC		byte_A
		BNE		loc_E542
		INC		byte_B
loc_E542:
		JSR		_BIOS_dec_data_size
		BCS		loc_E533
		BCC		loc_E572
loc_E549:
		CPY		#$00
		BNE		loc_E563
		LDA		_ppu_mask_shadow
		AND		#$E7
		STA		_ppu_mask_shadow
		STA		_PPU_MASK
		LDA		_PPU_STATUS
		LDA		byte_B
		STA		_PPU_ADDR
		LDA		byte_A
		STA		_PPU_ADDR
loc_E563:
		JSR		_BIOS_wait_for_disk_irq
		CPY		#$00
		BNE		loc_E56D
		STA		_PPU_DATA
loc_E56D:
		JSR		_BIOS_dec_data_size
		BCS		loc_E563
loc_E572:
		LDA		byte_9
		BNE		loc_E57A
		JSR		sub_E706
		RTS
; ---------------------------------------------------------------------------
loc_E57A:
		JSR		_BIOS_wait_for_disk_irq
		JSR		_BIOS_wait_for_disk_irq
		JMP		sub_E74C

; =============== S U B	R O U T	I N E =======================================
sub_E583:
		LDY		#$0B
		LDA		(byte_2),Y
		STA		byte_C
		INY
		LDA		(byte_2),Y
		STA		byte_D
		LDY		#$0E
		LDA		(byte_2),Y
		STA		byte_A
		INY
		LDA		(byte_2),Y
		STA		byte_B
		INY
		LDA		(byte_2),Y
		BEQ		loc_E5B1
		JSR		_BIOS_sub_E161
		LDA		_PPU_STATUS
		LDA		byte_B
		STA		_PPU_ADDR
		LDA		byte_A
		STA		_PPU_ADDR
		LDA		_PPU_DATA
loc_E5B1:
		JSR		_BIOS_dec_data_size
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E5B5:
		STA		byte_9
		LDA		byte_6
		JSR		_BIOS_wait_for_disk_irq
		LDX		byte_9
		BEQ		loc_E5C7
		LDX		#$26
		CMP		byte_6
		JSR		_BIOS_end_of_irq_break_if_no_zero
loc_E5C7:
		LDY		#$00
loc_E5C9:
		LDA		(byte_2),Y
		JSR		_BIOS_wait_for_disk_irq
		LDX		byte_9
		BEQ		loc_E5D9
		LDX		#$26
		CMP		(byte_2),Y
		JSR		_BIOS_end_of_irq_break_if_no_zero
loc_E5D9:
		INY
		CPY		#$0E
		BNE		loc_E5C9
		LDX		byte_9
		BEQ		loc_E616
		JSR		sub_E706
		JSR		sub_E583
		LDA		#$04
		JSR		sub_E68F
loc_E5ED:
		LDY		#$10
		LDA		(byte_2),Y
		BNE		loc_E624
		LDY		#$00
		LDX		byte_9
		BEQ		loc_E60A
loc_E5F9:
		JSR		_BIOS_wait_for_disk_irq
		LDX		#$26
		CMP		(byte_A),Y
		JSR		_BIOS_end_of_irq_break_if_no_zero
		JSR		_BIOS_inc_data_ptr
		BCS		loc_E5F9
		BCC		loc_E638
loc_E60A:
		LDA		(byte_A),Y
		JSR		_BIOS_wait_for_disk_irq
		JSR		_BIOS_inc_data_ptr
		BCS		loc_E60A
		BCC		loc_E638
loc_E616:
		JSR		sub_E729
		JSR		sub_E583
		LDA		#$04
		JSR		sub_E6B0
		JMP		loc_E5ED
; ---------------------------------------------------------------------------
loc_E624:
		LDX		byte_9
		BEQ		loc_E640
		JSR		_BIOS_wait_for_disk_irq
		LDX		#$26
		CMP		_PPU_DATA
		JSR		_BIOS_end_of_irq_break_if_no_zero
loc_E633:
		JSR		_BIOS_dec_data_size
		BCS		loc_E624
loc_E638:
		LDX		byte_9
		BEQ		loc_E649
		JSR		sub_E706
		RTS
; ---------------------------------------------------------------------------
loc_E640:
		LDA		_PPU_DATA
		JSR		_BIOS_wait_for_disk_irq
		JMP		loc_E633
; ---------------------------------------------------------------------------
loc_E649:
		JSR		sub_E729
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E64D:
		JSR		sub_E685
		LDY		#$00
		JSR		_BIOS_sub_E153
		JSR		_BIOS_sub_E153
		JSR		sub_EE17
		LDY		#$96
		JSR		_BIOS_sub_E153
		LDA		byte_F9
		ORA		#$80
		STA		byte_F9
		STA		_FDS_REG26
		LDX		#$02
		EOR		_FDS_REG33
		ROL
		JSR		_BIOS_end_of_irq_break_if_equal_or_above
		JSR		sub_E685
		JSR		sub_EE17
loc_E678:
		LDX		#$01
		LDA		_FDS_REG32
		LSR
		JSR		_BIOS_end_of_irq_break_if_equal_or_above
		LSR
		BCS		loc_E678
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E685:
		LDA		byte_FA
		AND		#$08
		ORA		#$26
		STA		_FDS_REG25
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E68F:
		LDY		#$05
		JSR		_BIOS_sub_E153
		STA		byte_7
		CLC
		ADC		#$21
		TAY
		LDA		byte_FA
		ORA		#$40
		STA		byte_FA
		STA		_FDS_REG25
		JSR		_BIOS_wait_for_disk_irq_mode40
		PHA
		TYA
		TAX
		PLA
		CMP		byte_7
		JSR		_BIOS_end_of_irq_break_if_no_zero
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E6B0:
		LDY		#$0A
		STA		byte_7
		LDA		byte_FA
		AND		#$2B
		STA		_FDS_REG25
		JSR		_BIOS_sub_E153
		LDY		#$00
		STY		_FDS_REG24
		ORA		#$40
		STA		byte_FA
		STA		_FDS_REG25
		LDA		#$80
		JSR		_BIOS_wait_for_disk_irq_mode40
		LDA		byte_7
		JSR		_BIOS_wait_for_disk_irq
		RTS
; ---------------------------------------------------------------------------
_disk_header_signature:
		.BYTE "*CVH-ODNETNIN*"

; =============== S U B	R O U T	I N E =======================================
_BIOS_disk_signature_check:
		JSR		sub_E64D
		LDY		#$C5
		JSR		_BIOS_sub_E153
		LDY		#$46
		JSR		_BIOS_sub_E153
		LDA		#$01
		JSR		sub_E68F
		LDY		#$0D
loc_E6F7:
		JSR		_BIOS_wait_for_disk_irq
		LDX		#$21
loc_E6FC:
		CMP		_disk_header_signature,Y
		JSR		_BIOS_end_of_irq_break_if_no_zero
		DEY
		BPL		loc_E6F7
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E706:
		JSR		_BIOS_wait_for_disk_irq
		LDX		#$28
		LDA		_FDS_REG30
		AND		#$40
		BNE		_BIOS_end_of_irq_break
		LDA		byte_FA
		ORA		#$10
		STA		byte_FA
		STA		_FDS_REG25
		JSR		_BIOS_wait_for_disk_irq
		LDX		#$27
		LDA		_FDS_REG30
		AND		#$10
		BNE		_BIOS_end_of_irq_break
		BEQ		sub_E74C

; =============== S U B	R O U T	I N E =======================================
sub_E729:
		JSR		_BIOS_wait_for_disk_irq
		LDX		#$29
		LDA		_FDS_REG30
		AND		#$40
		BNE		_BIOS_end_of_irq_break
		LDA		byte_FA
		ORA		#$10
		STA		byte_FA
		STA		_FDS_REG25
		LDX		#$B2
loc_E740:
		DEX
		BNE		loc_E740
		LDX		#$30
		LDA		_FDS_REG32
		AND		#$02
		BNE		_BIOS_end_of_irq_break

; =============== S U B	R O U T	I N E =======================================
sub_E74C:
		LDA		byte_FA
		AND		#$2F
		ORA		#$04
		STA		byte_FA
		STA		_FDS_REG25
		LDX		#$01
		LDA		_FDS_REG32
		LSR
		JSR		_BIOS_end_of_irq_break_if_equal_or_above
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E761:
		JSR		_BIOS_wait_for_disk_irq
		STA		(byte_A),Y
		LDX		#$28
		LDA		_FDS_REG30
		AND		#$40
		BNE		_BIOS_end_of_irq_break
		INY
		JSR		_BIOS_wait_for_disk_irq
		STA		(byte_A),Y
		JMP		sub_E74C

; =============== S U B	R O U T	I N E =======================================
_BIOS_end_of_irq_break_if_no_zero_exit_code0:
		LDX		#$00
		BEQ		_BIOS_end_of_irq_default

; =============== S U B	R O U T	I N E =======================================
_BIOS_end_of_irq_break_if_equal_or_above:
		BCS		_BIOS_end_of_irq_break
nullsub_4:
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_end_of_irq_break_if_no_zero:
		BEQ		nullsub_4
_BIOS_end_of_irq_break:
		TXA
		LDX		word_4
		TXS
		TAX

; =============== S U B	R O U T	I N E =======================================
_BIOS_end_of_irq_default:
		LDA		byte_FA
		AND		#$09
		ORA		#$26
		STA		byte_FA
		STA		_FDS_REG25
		TXA
		CLI
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_wait_for_disk_irq_mode40:
		LDX		#$40
		STX		byte_101
		ROL		byte_FA
		SEC
		ROR		byte_FA
		LDX		byte_FA
		STX		_FDS_REG25

; =============== S U B	R O U T	I N E =======================================
_BIOS_wait_for_disk_irq:
		CLI
loc_E7A4:
		JMP		loc_E7A4

; =============== S U B	R O U T	I N E =======================================
_BIOS_inc_data_ptr:
		INC		byte_A
		BNE		_BIOS_dec_data_size
		INC		byte_B

; =============== S U B	R O U T	I N E =======================================
_BIOS_dec_data_size:
		SEC
		LDA		byte_C
		SBC		#$01
		STA		byte_C
		LDA		byte_D
		SBC		#$00
		STA		byte_D
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_data_send_param:
		JSR		_BIOS_get_params2
		JMP		loc_E815
; ---------------------------------------------------------------------------
_BIOS_ppu_data_send_loop:
		PHA
		STA		_PPU_ADDR
		INY
		LDA		(word_0),Y
		STA		_PPU_ADDR
		INY
		LDA		(word_0),Y
		ASL
		PHA
		LDA		_ppu_ctrl_shadow
		ORA		#$04
		BCS		loc_E7D8
		AND		#$FB
loc_E7D8:
		STA		_PPU_CTRL
		STA		_ppu_ctrl_shadow
		PLA
		ASL
		PHP
		BCC		loc_E7E5
		ORA		#$02
		INY
loc_E7E5:
		PLP
		CLC
		BNE		loc_E7EA
		SEC
loc_E7EA:
		ROR
		LSR
		TAX
loc_E7ED:
		BCS		loc_E7F0
		INY
loc_E7F0:
		LDA		(word_0),Y
		STA		_PPU_DATA
		DEX
		BNE		loc_E7ED
		PLA
		CMP		#$3F
		BNE		loc_E809
		STA		_PPU_ADDR
		STX		_PPU_ADDR
		STX		_PPU_ADDR
		STX		_PPU_ADDR
loc_E809:
		SEC
		TYA
		ADC		word_0
		STA		word_0
		LDA		#$00
		ADC		word_0+1
		STA		word_0+1
loc_E815:
		LDX		_PPU_STATUS
		LDY		#$00
		LDA		(word_0),Y
		BPL		loc_E81F
		RTS
; ---------------------------------------------------------------------------
loc_E81F:
		CMP		#$60
		BNE		loc_E82D
		PLA
		STA		word_0+1
		PLA
		STA		word_0
		LDY		#$02
		BNE		loc_E809
loc_E82D:
		CMP		#$4C
		BNE		_BIOS_ppu_data_send_loop
		LDA		word_0
		PHA
		LDA		word_0+1
		PHA
		INY
		LDA		(word_0),Y
		TAX
		INY
		LDA		(word_0),Y
		STA		word_0+1
		STX		word_0
		BCS		loc_E815

; =============== S U B	R O U T	I N E =======================================
_BIOS_get_params2:
		TSX
		LDA		byte_103,X
		STA		word_4+1
		LDA		byte_104,X
		STA		byte_6
		LDY		#$01
		LDA		(word_4+1),Y
		STA		word_0
		INY
		LDA		(word_4+1),Y
		STA		word_0+1
		CLC
		LDA		#$02
		ADC		word_4+1
		STA		byte_103,X
		LDA		#$00
		ADC		byte_6
		STA		byte_104,X
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E86A:
		LDA		_ppu_ctrl_shadow
		AND		#$FB
		STA		_PPU_CTRL
		STA		_ppu_ctrl_shadow
		LDX		_PPU_STATUS
		LDY		#$00
		BEQ		loc_E8A5
loc_E87A:
		PHA
		STA		_PPU_ADDR
		INY
		LDA		byte_300+2,Y
		STA		_PPU_ADDR
		INY
		LDX		byte_300+2,Y
loc_E889:
		INY
		LDA		byte_300+2,Y
		STA		_PPU_DATA
		DEX
		BNE		loc_E889
		PLA
		CMP		#$3F
		BNE		loc_E8A4
		STA		_PPU_ADDR
		STX		_PPU_ADDR
		STX		_PPU_ADDR
		STX		_PPU_ADDR
loc_E8A4:
		INY
loc_E8A5:
		LDA		byte_300+2,Y
		BPL		loc_E87A
		STA		byte_300+2
		LDA		#$00
		STA		byte_300+1
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E8B3:
		LDA		_PPU_STATUS
loc_E8B6:
		LDA		byte_300,X
		STA		_PPU_ADDR
		INX
		LDA		byte_300,X
		STA		_PPU_ADDR
		INX
		LDA		_PPU_DATA
		LDA		_PPU_DATA
		STA		byte_300,X
		INX
		DEY
		BNE		loc_E8B6
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E8D2:
		STA		byte_3
		STX		byte_2
		STY		word_4
		JSR		_BIOS_get_params2
		LDY		#$FF
		LDA		#$01
		BNE		sub_E8F6

; =============== S U B	R O U T	I N E =======================================
sub_E8E1:
		STA		byte_3
		STX		byte_2
		JSR		_BIOS_get_params2
		LDY		#$00
		LDA		(word_0),Y
		AND		#$0F
		STA		word_4
		LDA		(word_0),Y
		LSR
		LSR
		LSR
		LSR

; =============== S U B	R O U T	I N E =======================================
sub_E8F6:
		STA		word_4+1
		LDX		byte_300+1
loc_E8FB:
		LDA		byte_3
		STA		byte_300+2,X
		JSR		sub_E93C
		LDA		byte_2
		STA		byte_300+2,X
		JSR		sub_E93C
		LDA		word_4
		STA		byte_6
		STA		byte_300+2,X
loc_E912:
		JSR		sub_E93C
		INY
		LDA		(word_0),Y
		STA		byte_300+2,X
		DEC		byte_6
		BNE		loc_E912
		JSR		sub_E93C
		STX		byte_300+1
		CLC
		LDA		#$20
		ADC		byte_2
		STA		byte_2
		LDA		#$00
		ADC		byte_3
		STA		byte_3
		DEC		word_4+1
		BNE		loc_E8FB
		LDA		#$FF
		STA		byte_300+2,X
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E93C:
		INX
		CPX		byte_300
		BCC		locret_E94E
		LDX		byte_300+1
		LDA		#$FF
		STA		byte_300+2,X
		PLA
		PLA
		LDA		#$01
locret_E94E:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E94F:
		DEX
		DEX
		DEX
		TXA
loc_E953:
		CLC
		ADC		#$03
		DEY
		BNE		loc_E953
		TAX
		TAY
		LDA		byte_300,X
		CMP		word_0
		BNE		loc_E970
		INX
		LDA		byte_300,X
		CMP		word_0+1
		BNE		loc_E970
		INX
		LDA		byte_300,X
		CLC
		RTS
; ---------------------------------------------------------------------------
loc_E970:
		LDA		word_0
		STA		byte_300,Y
		INY
		LDA		word_0+1
		STA		byte_300,Y
		SEC
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E97D:
		LDA		#$08
		STA		word_0
		LDA		byte_2
		ASL
		ROL		word_0
		ASL
		ROL		word_0
		AND		#$E0
		STA		word_0+1
		LDA		byte_3
		LSR
		LSR
		LSR
		ORA		word_0+1
		STA		word_0+1
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E997:
		LDA		word_0+1
		ASL
		ASL
		ASL
		STA		byte_3
		LDA		word_0+1
		STA		byte_2
		LDA		word_0
		LSR
		ROR		byte_2
		LSR
		ROR		byte_2
		LDA		#$F8
		AND		byte_2
		STA		byte_2
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E9B1:
		LDA		word_0,X
		AND		#$02
		STA		word_0
		LDA		word_0+1,X
		AND		#$02
		EOR		word_0
		CLC
		BEQ		loc_E9C1
		SEC
loc_E9C1:
		ROR		word_0,X
		INX
		DEY
		BNE		loc_E9C1
		RTS

; =============== S U B	R O U T	I N E =======================================
_ppu_spr_dma_start:
		LDA		#$00
		STA		_PPU_OAM_ADDR
		LDA		#$02
		STA		_PPU_OAM_DMA
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_E9D3:
		STX		word_0
		DEC		word_0,X
		BPL		loc_E9DE
		LDA		#$09
		STA		word_0,X
		TYA
loc_E9DE:
		TAX
loc_E9DF:
		LDA		word_0,X
		BEQ		loc_E9E5
		DEC		word_0,X
loc_E9E5:
		DEX
		CPX		word_0
		BNE		loc_E9DF
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_read_pads:
		LDX		byte_FB
		INX
		STX		_PAD0_REG
		DEX
		STX		_PAD0_REG
		LDX		#$08
loc_E9F7:
		LDA		_PAD0_REG
		LSR
		ROL		_pads_press
		LSR
		ROL		word_0
		LDA		_PAD1_REG
		LSR
		ROL		_pads_press+1
		LSR
		ROL		word_0+1
		DEX
		BNE		loc_E9F7
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_merge_pads:
		LDA		word_0
		ORA		_pads_press
		STA		_pads_press
		LDA		word_0+1
		ORA		_pads_press+1
		STA		_pads_press+1
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_get_inputB:
		JSR		_BIOS_read_pads
		BEQ		_BIOS_calc_padsB
		JSR		_BIOS_read_pads
		JSR		_BIOS_merge_pads

; =============== S U B	R O U T	I N E =======================================
_BIOS_calc_padsB:
		LDX		#$01
loc_EA27:
		LDA		_pads_press,X
		TAY
		EOR		_pads_held,X
		AND		_pads_press,X
		STA		_pads_press,X
		STY		_pads_held,X
		DEX
		BPL		loc_EA27
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_calc_pads_unref:
		JSR		_BIOS_read_pads
loc_EA39:
		LDY		_pads_press
		LDA		_pads_press+1
		PHA
		JSR		_BIOS_read_pads
		PLA
		CMP		_pads_press+1
		BNE		loc_EA39
		CPY		_pads_press
		BNE		loc_EA39
		BEQ		_BIOS_calc_padsB

; =============== S U B	R O U T	I N E =======================================
_BIOS_get_inputA:
		JSR		_BIOS_read_pads
		JSR		_BIOS_merge_pads
loc_EA52:
		LDY		_pads_press
		LDA		_pads_press+1
		PHA
		JSR		_BIOS_read_pads
		JSR		_BIOS_merge_pads
		PLA
		CMP		_pads_press+1
		BNE		loc_EA52
		CPY		_pads_press
		BNE		loc_EA52
		BEQ		_BIOS_calc_padsB
		JSR		_BIOS_read_pads
		LDA		word_0
		STA		_pads_held
		LDA		word_0+1
		STA		_pads_held+1
		LDX		#$03
loc_EA75:
		LDA		_pads_press,X
		TAY
		EOR		_pads_tmp,X
		AND		_pads_press,X
		STA		_pads_press,X
		STY		_pads_tmp,X
		DEX
		BPL		loc_EA75
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_screen_clear:
		STA		word_0
		STX		word_0+1
		STY		byte_2
		LDA		_PPU_STATUS
		LDA		_ppu_ctrl_shadow
		AND		#$FB
		STA		_PPU_CTRL
		STA		_ppu_ctrl_shadow
		LDA		word_0
		STA		_PPU_ADDR
		LDY		#$00
		STY		_PPU_ADDR
		LDX		#$04
		CMP		#$20
		BCS		loc_EAA8
		LDX		byte_2
loc_EAA8:
		LDY		#$00
		LDA		word_0+1
loc_EAAC:
		STA		_PPU_DATA
		DEY
		BNE		loc_EAAC
		DEX
		BNE		loc_EAAC
		LDY		byte_2
		LDA		word_0
		CMP		#$20
		BCC		loc_EACF
		ADC		#$02
		STA		_PPU_ADDR
		LDA		#$C0
		STA		_PPU_ADDR
		LDX		#$40
loc_EAC9:
		STY		_PPU_DATA
		DEX
		BNE		loc_EAC9
loc_EACF:
		LDX		word_0+1
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_EAD2:
		PHA
		TXA
		STY		word_0+1
		CLC
		SBC		word_0+1
		TAX
		PLA
		LDY		#$00
		STY		word_0
loc_EADF:
		STA		(word_0),Y
		DEY
		BNE		loc_EADF
		DEC		word_0+1
		INX
		BNE		loc_EADF
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_EAEA:
		LDA		_PPU_STATUS
		LDA		byte_FD
		STA		_PPU_SCROLL
		LDA		byte_FC
		STA		_PPU_SCROLL
		LDA		_ppu_ctrl_shadow
		STA		_PPU_CTRL
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_EAFD:
		ASL
		TAY
		INY
		PLA
		STA		word_0
		PLA
		STA		word_0+1
		LDA		(word_0),Y
		TAX
		INY
		LDA		(word_0),Y
		STA		word_0+1
		STX		word_0
		JMP		(word_0)

; =============== S U B	R O U T	I N E =======================================
sub_EB13:
		LDA		byte_FB
		AND		#$F8
		STA		byte_FB
		ORA		#$05
		STA		_PAD0_REG
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		LDX		#$08
loc_EB26:
		LDA		byte_FB
		ORA		#$04
		STA		_PAD0_REG
		LDY		#$0A
loc_EB2F:
		DEY
		BNE		loc_EB2F
		NOP
		LDY		byte_FB
		LDA		_PAD1_REG
		LSR
		AND		#$0F
		BEQ		loc_EB62
		STA		word_0,X
		LDA		byte_FB
		ORA		#$06
		STA		_PAD0_REG
		LDY		#$0A
loc_EB48:
		DEY
		BNE		loc_EB48
		NOP
		NOP
		LDA		_PAD1_REG
		ROL
		ROL
		ROL
		AND		#$F0
		ORA		word_0,X
		EOR		#$FF
		STA		word_0,X
		DEX
		BPL		loc_EB26
		LDY		byte_FB
		ORA		#$FF
loc_EB62:
		STY		_PAD0_REG
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_chr_unp_data_ptr_add8:
		LDA		#$08

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_chr_unp_data_ptr_add:
		PHP
		LDY		#$00
		CLC
		ADC		word_0
		STA		word_0
		LDA		#$00
		ADC		word_0+1
		STA		word_0+1
		PLP
		DEC		byte_2
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_write_read_chunk:
		LDX		#$08
loc_EB7C:
		BCS		loc_EB88
		LDA		(word_0),Y
		STA		_PPU_DATA
loc_EB83:
		INY
		DEX
		BNE		loc_EB7C
		RTS
; ---------------------------------------------------------------------------
loc_EB88:
		LDA		_PPU_DATA
		STA		(word_0),Y
		BCS		loc_EB83

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_fill_chunk:
		LDA		byte_3
		LDX		#$08
loc_EB93:
		BCS		loc_EB9C
		STA		_PPU_DATA
loc_EB98:
		DEX
		BNE		loc_EB93
		RTS
; ---------------------------------------------------------------------------
loc_EB9C:
		LDA		_PPU_DATA
		BCS		loc_EB98

; =============== S U B	R O U T	I N E =======================================
_BIOS_ppu_chr_xor_chunk:
		LDX		#$08
loc_EBA3:
		LDA		byte_3
		EOR		(word_0),Y
		STA		_PPU_DATA
		INY
		DEX
		BNE		loc_EBA3
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_1bpp_chr_load:
		STA		word_4
		STX		byte_2
		STY		byte_3
		JSR		_BIOS_get_params2
		LDA		_PPU_STATUS
		LDA		_ppu_ctrl_shadow
		AND		#$FB
		STA		_ppu_ctrl_shadow
		STA		_PPU_CTRL
		LDY		byte_3
		STY		_PPU_ADDR
		LDA		word_4
		AND		#$F0
		STA		_PPU_ADDR
		LDA		#$00
		STA		byte_3
		LDA		word_4
		AND		#$0F
		LSR
		BCC		loc_EBDD
		DEC		byte_3
loc_EBDD:
		LSR
		BCC		loc_EBE3
		LDX		_PPU_DATA
loc_EBE3:
		TAY
		BEQ		_unp_half_copy_mode
		DEY
		BEQ		_unp_half1_fill_mode
		DEY
		BEQ		_unp_half2_fill_mode
		DEY
_unp_half_inv_mode:
		JSR		_BIOS_ppu_chr_xor_chunk
		LDY		#$00
		JSR		_BIOS_ppu_write_read_chunk
		JSR		_BIOS_ppu_chr_unp_data_ptr_add8
		BNE		_unp_half_inv_mode
		RTS
; ---------------------------------------------------------------------------
_unp_half_copy_mode:
		JSR		_BIOS_ppu_write_read_chunk
		JSR		_BIOS_ppu_write_read_chunk
		LDA		#$10
		JSR		_BIOS_ppu_chr_unp_data_ptr_add
		BNE		_unp_half_copy_mode
		RTS
; ---------------------------------------------------------------------------
_unp_half1_fill_mode:
		JSR		_BIOS_ppu_write_read_chunk
		JSR		_BIOS_ppu_fill_chunk
		JSR		_BIOS_ppu_chr_unp_data_ptr_add8
		BNE		_unp_half1_fill_mode
		RTS
; ---------------------------------------------------------------------------
_unp_half2_fill_mode:
		JSR		_BIOS_ppu_fill_chunk
		JSR		_BIOS_ppu_write_read_chunk
		JSR		_BIOS_ppu_chr_unp_data_ptr_add8
		BNE		_unp_half2_fill_mode
		RTS

; =============== S U B	R O U T	I N E =======================================
nullsub_5:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_EC22:
		LDY		#$0B
		LDA		(word_0),Y
		STA		byte_2
		LDA		#$02
		STA		byte_3
		DEY
		LDA		(word_0),Y
		LSR
		LSR
		LSR
		LSR
		BEQ		nullsub_5
		STA		word_4
		STA		byte_C
		LDA		(word_0),Y
		AND		#$0F
		BEQ		nullsub_5
		STA		word_4+1
		LDY		#$01
		LDA		(word_0),Y
		TAX
		DEY
		LDA		(word_0),Y
		BEQ		loc_EC4F
		BPL		nullsub_5
		LDX		#$F4
loc_EC4F:
		STX		byte_8
		LDY		#$08
		LDA		(word_0),Y
		LSR
		AND		#$08
		BEQ		loc_EC5C
		LDA		#$80
loc_EC5C:
		ROR
		STA		byte_9
		INY
		LDA		(word_0),Y
		AND		#$23
		ORA		byte_9
		STA		byte_9
		LDY		#$03
		LDA		(word_0),Y
		STA		byte_A
		LDA		word_4+1
		STA		byte_7
		LDY		#$00
		STY		byte_B
loc_EC76:
		LDA		word_4
		STA		byte_6
		LDX		byte_8
loc_EC7C:
		TXA
		STA		(byte_2),Y
		CMP		#$F4
		BEQ		loc_EC87
		CLC
		ADC		#$08
		TAX
loc_EC87:
		INY
		INY
		LDA		byte_9
		STA		(byte_2),Y
		INY
		LDA		byte_A
		STA		(byte_2),Y
		INY
		INC		byte_B
		DEC		byte_6
		BNE		loc_EC7C
		LDA		byte_A
		CLC
		ADC		#$08
		STA		byte_A
		DEC		byte_7
		BNE		loc_EC76
		LDY		#$07
		LDA		(word_0),Y
		STA		byte_7
		DEY
		LDA		(word_0),Y
		STA		byte_8
		LDA		#$00
		STA		byte_A
		CLC
		LDX		byte_B
		DEY
loc_ECB7:
		LDA		(word_0),Y
		CLC
		ADC		byte_7
		STA		byte_7
		LDA		#$00
		ADC		byte_8
		STA		byte_8
		DEX
		BNE		loc_ECB7
		INC		byte_2
		LDY		#$00
		LDA		byte_8
		BNE		loc_ECD3
		DEC		byte_A
		LDY		byte_7
loc_ECD3:
		BIT		byte_9
		BMI		loc_ECF5
		BVS		loc_ECF7
loc_ECD9:
		LDA		(byte_7),Y
		BIT		byte_A
		BPL		loc_ECE0
		TYA
loc_ECE0:
		STA		(byte_2,X)
		DEY
		BIT		byte_9
		BMI		loc_ECE9
		INY
		INY
loc_ECE9:
		LDA		#$04
		CLC
		ADC		byte_2
		STA		byte_2
		DEC		byte_B
		BNE		loc_ECD9
		RTS
; ---------------------------------------------------------------------------
loc_ECF5:
		BVC		loc_ED09
loc_ECF7:
		TYA
		CLC
		ADC		byte_B
		TAY
		DEY
		BIT		byte_9
		BMI		loc_ECD9
		LDA		#$FF
		EOR		byte_C
		STA		byte_C
		INC		byte_C
loc_ED09:
		TYA
		CLC
		ADC		byte_C
		TAY
		LDA		word_4
		STA		byte_6
loc_ED12:
		DEY
		BIT		byte_9
		BMI		loc_ED19
		INY
		INY
loc_ED19:
		LDA		(byte_7),Y
		BIT		byte_A
		BPL		loc_ED20
		TYA
loc_ED20:
		STA		(byte_2,X)
		LDA		#$04
		CLC
		ADC		byte_2
		STA		byte_2
		DEC		byte_6
		BNE		loc_ED12
		TYA
		CLC
		ADC		byte_C
		TAY
		DEC		word_4+1
		BNE		loc_ED09
		RTS
; ---------------------------------------------------------------------------
byte_ED37:
		.BYTE $24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$17,$12,$17,$1D,$0E
		.BYTE $17,$0D,$18,$24,$28,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24
		.BYTE $24,$24,$24,$24,$24,$24,$24,$0F,$0A,$16,$12,$15,$22,$24,$0C,$18
		.BYTE $16,$19,$1E,$1D,$0E,$1B,$24,$1D,$16,$24,$24,$24,$24,$24,$24,$24
		.BYTE $24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24
		.BYTE $24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24
		.BYTE $24,$24,$1D,$11,$12,$1C,$24,$19,$1B,$18,$0D,$1E,$0C,$1D,$24,$12
		.BYTE $1C,$24,$16,$0A,$17,$1E,$0F,$0A,$0C,$1D,$1E,$1B,$0E,$0D,$24,$24
		.BYTE $24,$24,$0A,$17,$0D,$24,$1C,$18,$15,$0D,$24,$0B,$22,$24,$17,$12
		.BYTE $17,$1D,$0E,$17,$0D,$18,$24,$0C,$18,$27,$15,$1D,$0D,$26,$24,$24
		.BYTE $24,$24,$18,$1B,$24,$0B,$22,$24,$18,$1D,$11,$0E,$1B,$24,$0C,$18
		.BYTE $16,$19,$0A,$17,$22,$24,$1E,$17,$0D,$0E,$1B,$24,$24,$24,$24,$24
		.BYTE $24,$24,$15,$12,$0C,$0E,$17,$1C,$0E,$24,$18,$0F,$24,$17,$12,$17
		.BYTE $1D,$0E,$17,$0D,$18,$24,$0C,$18,$27,$15,$1D,$0D,$26,$26,$24,$24

; =============== S U B	R O U T	I N E =======================================
sub_EE17:
		ORA		#$01
		STA		_FDS_REG25
		AND		#$FD
		STA		byte_FA
		STA		_FDS_REG25
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_RESET:
		SEI
		LDA		#$10
		STA		_PPU_CTRL
		STA		_ppu_ctrl_shadow
		CLD
		LDA		#$06
		STA		_ppu_mask_shadow
		STA		_PPU_MASK
		LDX		#$02
loc_EE36:
		LDA		_PPU_STATUS
		BPL		loc_EE36
		DEX
		BNE		loc_EE36
		STX		_FDS_REG22
		STX		_FDS_REG23
		LDA		#$83
		STA		_FDS_REG23
		STX		byte_FD
		STX		byte_FC
		STX		byte_FB
		STX		_PAD0_REG
		LDA		#$2E
		STA		byte_FA
		STA		_FDS_REG25
		LDA		#$FF
		STA		byte_F9
		STA		_FDS_REG26
		STX		_APU_DMC_FREQ
		LDA		#$C0
		STA		_PAD1_REG
		LDA		#$0F
		STA		_APU_STATUS
		LDA		#$80
		STA		_FDS_REG80
		LDA		#$E8
		STA		_FDS_REG8A
		LDX		#$FF
		TXS
		LDA		#$C0
		STA		byte_100
		LDA		#$80
		STA		byte_101
		LDA		byte_102
		CMP		#$35
		BNE		loc_EEA2
		LDA		byte_103
		CMP		#$53
		BEQ		loc_EE9B
		CMP		#$AC
		BNE		loc_EEA2
		LDA		#$53
		STA		byte_103
loc_EE9B:
		JSR		sub_EAEA
		CLI
		JMP		(off_DFFC)
; ---------------------------------------------------------------------------
loc_EEA2:
		LDA		#$00
		LDX		#$F8
loc_EEA6:
		STA		word_0,X
		DEX
		BNE		loc_EEA6
		STA		byte_300+1
		LDA		#$7D
		STA		byte_300
		LDA		#$FF
		STA		byte_300+2
		JSR		_BIOS_get_inputB
		LDA		_pads_held
		CMP		#$30
		BNE		loc_EEC9
		LDA		#$00
		STA		byte_102
		JMP		_BIOS_self_test
; ---------------------------------------------------------------------------
loc_EEC9:
		JSR		loc_F3FA
		JSR		sub_F0FD
		LDA		#$4A
		STA		byte_A1
		LDA		#$30
		STA		byte_B1
		LDA		#$E4
		STA		_apu_chl0+3
		LDA		#$A9
		STA		byte_FC
		LDA		_FDS_REG32
		AND		#$01
		BEQ		loc_EEEA
		LDA		#$04
		STA		byte_E1
loc_EEEA:
		LDA		#$34
		STA		_apu_chl1
loc_EEEE:
		JSR		sub_F376
		JSR		_BIOS_wait_for_nmi_mode00
		LDA		_apu_chl1
		CMP		#$32
		BNE		loc_EEFE
		LDA		#$01
		STA		byte_E1
loc_EEFE:
		JSR		sub_F0B4
		JSR		sub_EAEA
		JSR		_BIOS_ppu_render_on
		JSR		sub_EFE8
		LDX		#$60
		LDY		#$20
		JSR		sub_E9B1
		JSR		sub_F143
		JSR		sub_F342
		LDX		#$00
		JSR		sub_F1E5
		LDX		#$10
		JSR		sub_F1E5
		LDA		#$C0
		STA		word_0
		LDA		#$00
		STA		word_0+1
		JSR		sub_EC22
		LDA		#$D0
		STA		word_0
		JSR		sub_EC22
		LDA		_FDS_REG32
		AND		#$01
		BNE		loc_EEEA
		LDA		byte_FC
		BEQ		loc_EF42
		LDA		#$01
		STA		byte_FC
loc_EF42:
		LDA		_apu_chl1
		BNE		loc_EEEE
		JSR		_BIOS_ppu_sprites_off
		JSR		_BIOS_wait_for_nmi_mode00
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD byte_EFFF
; ---------------------------------------------------------------------------
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD byte_F01C
; ---------------------------------------------------------------------------
		JSR		sub_EAEA
		JSR		_BIOS_load_files_by_idx
; ---------------------------------------------------------------------------
		.WORD _disk_id_side_dummy
		.WORD _disk_id_side_dummy
; ---------------------------------------------------------------------------
		BNE		loc_EF6C
		JSR		sub_F431
		BEQ		loc_EFAF
		JSR		sub_F5FB
		LDA		#$20
loc_EF6C:
		STA		byte_23
		JSR		loc_F3FA
		JSR		loc_F0E1
		JSR		loc_F0E7
		JSR		loc_F0ED
		JSR		sub_F179
		LDA		#$10
		STA		byte_A3
		LDA		byte_22
		BEQ		loc_EF8B
		LDA		#$01
		STA		_apu_chl0+3
		DEC		byte_21
loc_EF8B:
		JSR		sub_F376
		JSR		_BIOS_wait_for_nmi_mode00
		JSR		sub_E86A
		JSR		sub_EAEA
		JSR		_BIOS_ppu_bg_on
		JSR		sub_EFE8
		LDA		#$02
		STA		byte_E1
		LDA		byte_A3
		BNE		loc_EF8B
loc_EFA5:
		LDA		_FDS_REG32
		AND		#$01
		BEQ		loc_EFA5
		JMP		_BIOS_RESET
; ---------------------------------------------------------------------------
loc_EFAF:
		LDA		#$20
		STA		byte_A2
loc_EFB3:
		JSR		_BIOS_wait_for_nmi_mode00
		JSR		sub_EAEA
		JSR		_BIOS_ppu_bg_on
		LDX		byte_FC
		INX
		INX
		CPX		#$B0
		BCS		loc_EFC6
		STX		byte_FC
loc_EFC6:
		JSR		sub_EFE8
		LDA		byte_A2
		BNE		loc_EFB3
		LDA		#$35
		STA		byte_102
		LDA		#$AC
		STA		byte_103
		JSR		_BIOS_ppu_bg_off
		LDY		#$07
		JSR		sub_F48C
		LDA		#$00
		STA		byte_FD
		STA		byte_FC
		JMP		loc_EE9B

; =============== S U B	R O U T	I N E =======================================
sub_EFE8:
		JSR		loc_FF5C
		LDX		#_apu_chl0
		LDA		#_apu_chl1+$F
		LDY		#_apu_load_tmp_track_ptr+1
		JSR		sub_E9D3
		RTS
; ---------------------------------------------------------------------------
_disk_id_side_dummy:
		.BYTE $FF,$FF,$FF,$FF,$FF,$FF,$00,$00,$FF,$FF
byte_EFFF:
		.BYTE $21,$A6,$54,$24,$FF
byte_F004:
		.BYTE $21,$A6,$14,$19,$15,$0E,$0A,$1C,$0E,$24,$1C,$0E,$1D,$24,$0D,$12
		.BYTE $1C,$14,$24,$0C,$0A,$1B,$0D,$FF
byte_F01C:
		.BYTE $21,$A6,$0E,$17,$18,$20,$24,$15,$18,$0A,$0D,$12,$17,$10,$26,$26
		.BYTE $26,$FF
byte_F02E:
		.BYTE $0D,$12,$1C,$14,$24,$1C,$0E,$1D,$0B,$0A,$1D,$1D,$0E,$1B,$22,$24
		.BYTE $0A,$25,$0B,$24,$1C,$12,$0D,$0E,$0D,$12,$1C,$14,$24,$17,$18
byte_F04D:
		.BYTE $26,$21,$A6,$14,$0D,$12,$1C,$14,$24,$1D,$1B,$18,$1E,$0B,$15,$0E
		.BYTE $24,$24,$0E,$1B,$1B,$26,$02,$00,$FF
byte_F066:
		.BYTE $20,$E8,$10,$19,$1B,$0A,$16,$24,$0C,$1B,$0A,$16,$24,$24,$24,$24
		.BYTE $24,$18,$14,$21,$68,$04,$19,$18,$1B,$1D
byte_F080:
		.BYTE $3F,$00,$08,$0F,$20,$0F,$0F,$0F,$0F,$0F,$0F,$2B,$C0,$50,$00,$2B
		.BYTE $D0,$70,$55
byte_F093:
		.BYTE $FF
byte_F094:
		.BYTE $80,$B8,$00,$00,$00,$00,$00,$00,$10,$00,$32,$00,$00,$00,$01,$00
		.BYTE $80,$B8,$00,$F0,$00,$00,$00,$00,$00,$01,$32,$18,$00,$00,$FF,$00

; =============== S U B	R O U T	I N E =======================================
sub_F0B4:
		LDA		byte_FC
		BEQ		loc_F0C0
		DEC		byte_FC
		BNE		loc_F0C0
		LDA		#$10
		STA		_apu_chl1+4
loc_F0C0:
		LDX		_apu_chl1+4
		BEQ		loc_F0CD
		DEX
		BEQ		loc_F0E1
		DEX
		BEQ		loc_F0E7
		DEX
		BEQ		loc_F0ED
loc_F0CD:
		JSR		_ppu_spr_dma_start
		JSR		sub_E86A
		LDA		_apu_chl1+2
		BNE		loc_F0F3
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD byte_EFFF
; ---------------------------------------------------------------------------
		LDA		#$40
		STA		_apu_chl1+2
		RTS
; ---------------------------------------------------------------------------
loc_F0E1:
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD byte_F716
; ---------------------------------------------------------------------------
		RTS
; ---------------------------------------------------------------------------
loc_F0E7:
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD byte_F723
; ---------------------------------------------------------------------------
		RTS
; ---------------------------------------------------------------------------
loc_F0ED:
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD byte_F72C
; ---------------------------------------------------------------------------
		RTS
; ---------------------------------------------------------------------------
loc_F0F3:
		CMP		#$2E
		BNE		locret_F0FC
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD byte_F004
; ---------------------------------------------------------------------------
locret_F0FC:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_F0FD:
		LDA		#$F4
		LDX		#$02
		LDY		#$02
		JSR		sub_EAD2
		LDY		#$20
loc_F108:
		LDA		byte_F093,Y
		STA		_apu_load_tmp_track_ptr+1,Y
		DEY
		BNE		loc_F108
		LDA		#$D0
		STA		byte_60
		STA		word_0+1
loc_F117:
		LDY		#$02
		LDX		#$60
		JSR		sub_E9B1
		LDA		byte_60
		LDX		word_0+1
		STA		_spr_buf+$2F,X
		DEX
		STX		word_0+1
		BNE		loc_F117
		LDA		#$18
		LDX		#$D0
loc_F12E:
		STA		_spr_buf+$2D,X
		DEX
		DEX
		DEX
		DEX
		BNE		loc_F12E
		LDX		#$D0
		STX		_nmi_counter
loc_F13B:
		JSR		sub_F156
		CPX		#$D0
		BNE		loc_F13B
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_F143:
		LDA		_apu_chl0+4
		BNE		sub_F156
		LDA		#$04
		STA		_apu_chl0+4
		LDX		#$D0
loc_F14D:
		DEC		_spr_buf+$2C,X
		DEX
		DEX
		DEX
		DEX
		BNE		loc_F14D

; =============== S U B	R O U T	I N E =======================================
sub_F156:
		LDY		#$04
loc_F158:
		LDX		_nmi_counter
		DEC		_spr_buf+$2E,X
		LDA		#$03
		AND		_spr_buf+$2E,X
		ORA		#$20
		STA		_spr_buf+$2E,X
		DEX
		DEX
		DEX
		DEX
		BNE		loc_F16F
		LDX		#$D0
loc_F16F:
		STX		_nmi_counter
		DEY
		BNE		loc_F158
locret_F174:
		RTS
; ---------------------------------------------------------------------------
		.BYTE $01, $02,	$07, $08

; =============== S U B	R O U T	I N E =======================================
sub_F179:
		LDY		#$18
loc_F17B:
		LDA		byte_F04D,Y
		STA		byte_3F,Y
		DEY
		BNE		loc_F17B
		LDA		byte_23
		AND		#$0F
		STA		byte_56
		LDA		byte_23
		LSR
		LSR
		LSR
		LSR
		STA		_game_vat55
		CMP		#$02
		BEQ		loc_F1BD
		LDY		#$0E
		LDA		#$24
loc_F19A:
		STA		byte_42,Y
		DEY
		BNE		loc_F19A
		LDY		#$05
		LDA		byte_23
loc_F1A4:
		DEY
		BEQ		loc_F1BD
		CMP		locret_F174,Y
		BNE		loc_F1A4
		TYA
		ASL
		ASL
		ASL
		TAX
		LDY		#$07
loc_F1B3:
		DEX
		LDA		byte_F02E,X
		STA		byte_43,Y
		DEY
		BPL		loc_F1B3
loc_F1BD:
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD byte_40
; ---------------------------------------------------------------------------
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_chr_fonts_load:
		LDA		#$0D
		LDY		#$10
		LDX		#$29
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD _BIOS_chr_fonts_data
; ---------------------------------------------------------------------------
		LDA		#$06
		LDY		#$10
		LDX		#$29
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD _bios_font_buf
; ---------------------------------------------------------------------------
		LDA		#$09
		LDY		#$10
		LDX		#$29
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD _bios_font_buf
; ---------------------------------------------------------------------------
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_F1E5:
		JSR		sub_F1F2
		JSR		sub_F2EC
		JSR		sub_F273
		JSR		sub_F2C6
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_F1F2:
		LDA		byte_20,X
		BNE		locret_F227
		LDA		_apu_chl4,X
		BNE		locret_F227
		LDA		_apu_chl3
		BNE		locret_F227
		LDA		_apu_chl0+1,X
		BNE		locret_F227
		LDA		byte_62,X
		AND		#$3C
		STA		_apu_chl0+1,X
		TXA
		BNE		loc_F228
		LDA		byte_B2
		BNE		loc_F236
		LDA		_apu_ptrE5
		BEQ		loc_F23D
		LDA		byte_22
		BNE		loc_F21D
		LDA		byte_C3
		CMP		#$78
		BCC		loc_F24D
loc_F21D:
		LDA		#$00
		STA		byte_C8,X
		STA		byte_CF,X
		LDA		#$FF
		STA		byte_CE,X
locret_F227:
		RTS
; ---------------------------------------------------------------------------
loc_F228:
		LDA		_apu_chl4
		BEQ		loc_F25A
		LDA		byte_22
		BNE		loc_F21D
		LDA		byte_63,X
		CMP		#$80
		BCS		loc_F24D
loc_F236:
		LDA		#$00
		STA		byte_CF,X
		STA		byte_CE,X
		RTS
; ---------------------------------------------------------------------------
loc_F23D:
		LDA		byte_C8
		BNE		loc_F247
		LDA		byte_63,X
		CMP		#$C0
		BCC		loc_F21D
loc_F247:
		LDA		byte_64,X
		CMP		#$80
		BCC		loc_F236
loc_F24D:
		LDA		#$10
		STA		byte_C8,X
		LDA		#$00
		STA		byte_CF,X
		LDA		#$01
		STA		byte_CE,X
		RTS
; ---------------------------------------------------------------------------
loc_F25A:
		LDA		byte_64,X
		LDY		byte_C8
		BEQ		loc_F264
		CMP		#$40
		BCC		loc_F24D
loc_F264:
		CMP		#$C0
		BCC		loc_F236
		LDA		#$40
		STA		byte_CF,X
		LDA		#$00
		STA		byte_CE,X
		STA		byte_C8,X
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_F273:
		LDA		byte_20,X
		BEQ		locret_F2AA
		BMI		loc_F2AB
		CLC
		LDA		#$30
		ADC		byte_CD,X
		STA		byte_CD,X
		LDA		#$00
		ADC		byte_CC,X
		STA		byte_CC,X
		CLC
		LDA		byte_CD,X
		ADC		byte_C2,X
		STA		byte_C2,X
		LDA		byte_CC,X
		ADC		byte_C1,X
		CMP		#$B8
		BCC		loc_F2A4
		TXA
		BNE		loc_F2B6
		LDA		byte_60,X
		AND		#$30
		STA		_apu_chl0+1,X
loc_F29E:
		LDA		#$00
		STA		byte_20,X
		LDA		#$B8
loc_F2A4:
		STA		byte_C1,X
		LDA		#$03
		STA		byte_C5,X
locret_F2AA:
		RTS
; ---------------------------------------------------------------------------
loc_F2AB:
		DEC		byte_20,X
		LDA		#$FD
		STA		byte_CC,X
		LDA		#$00
		STA		byte_CD,X
		RTS
; ---------------------------------------------------------------------------
loc_F2B6:
		STA		byte_C8,X
		LDA		#$01
		STA		byte_CE,X
		LDA		#$C0
		STA		byte_CF,X
		LDA		#$FF
		STA		_apu_chl0+1,X
		BNE		loc_F29E

; =============== S U B	R O U T	I N E =======================================
sub_F2C6:
		LDA		_apu_chl3
		BNE		locret_F2E7
		LDA		byte_A1,X
		BNE		locret_F2E7
		LDA		_apu_chl4,X
		BEQ		locret_F2E7
		LDA		byte_62,X
		ORA		#$10
		AND		#$3C
		STA		_apu_chl0+1,X
		LDY		#$10
loc_F2DC:
		LDA		byte_F094,X
		STA		_apu_chl4,X
		INX
		DEY
		BNE		loc_F2DC
		STY		_apu_chl3,X
locret_F2E7:
		RTS
; ---------------------------------------------------------------------------
byte_F2E8:
		.BYTE $00, $02,	$01, $02

; =============== S U B	R O U T	I N E =======================================
sub_F2EC:
		LDA		_apu_chl4,X
		BNE		locret_F329
		CLC
		LDA		byte_CF,X
		ADC		byte_C4,X
		STA		byte_C4,X
		LDA		byte_CE,X
		ADC		byte_C3,X
		LDY		_apu_chl3
		CPY		#$20
		BCS		loc_F315
		CMP		#$F8
		BCC		loc_F32A
		CPY		#$1F
		BCS		loc_F315
		LDA		byte_60,X
		AND		#$2F
		ORA		#$06
		STA		byte_A1,X
		LDA		#$80
		STA		_apu_chl4,X
loc_F315:
		STA		byte_C3,X
		LSR
		LSR
		AND		#$03
		TAY
		LDA		byte_CE,X
		ORA		byte_CF,X
		BNE		loc_F324
		LDY		#$01
loc_F324:
		LDA		byte_F2E8,Y
		STA		byte_C5,X
locret_F329:
		RTS
; ---------------------------------------------------------------------------
loc_F32A:
		CMP		#$78
		BNE		loc_F315
		CPX		byte_22
		BNE		loc_F315
		LDY		byte_20,X
		BNE		loc_F315
		LDY		#$00
		STY		byte_CE,X
		STY		byte_CF,X
		LDY		#$80
		STY		byte_20,X
		BNE		loc_F315

; =============== S U B	R O U T	I N E =======================================
sub_F342:
		LDA		_apu_chl3
		BNE		locret_F36D
		LDA		_apu_chl4
		ORA		_apu_ptrE5
		BNE		locret_F36D
		CLC
		LDA		byte_C3
		ADC		#$19
		CMP		byte_D3
		BCC		locret_F36D
		STA		byte_D3
		LDA		#$02
		STA		byte_CE
		STA		byte_DE
		LDA		#$00
		STA		byte_CF
		STA		byte_DF
		LDA		#$10
		STA		byte_C8
		STA		byte_D8
		LDA		#$30
		STA		_apu_chl3
locret_F36D:
		RTS
; ---------------------------------------------------------------------------
word_F36E:
		.WORD $0A2A
		.WORD $0525
		.WORD $0121
		.WORD $1627

; =============== S U B	R O U T	I N E =======================================
sub_F376:
		LDY		#$08
		LDA		_apu_chl0+3
		BNE		loc_F3C8
		LDA		_apu_chl1+3
		BNE		loc_F3EF
		LDX		#$00
loc_F382:
		LDA		byte_C1,X
		CMP		#$A4
		BCS		loc_F39E
		LDA		#$20
		LDY		byte_B2
		BNE		loc_F39C
		LDA		#$08
		LDY		byte_65
		CPY		#$18
		BCS		loc_F39C
		LDA		#$08
		STA		byte_B2
		LDA		#$20
loc_F39C:
		STA		_apu_chl0+3,X
loc_F39E:
		CPX		#$10
		LDX		#$10
		BCC		loc_F382
		LDA		byte_22
		BEQ		locret_F3C7
		LDA		_apu_chl0+2
		BNE		locret_F3C7
		LDA		#$08
		STA		_apu_chl0+2
		LDX		#$0F
		LDA		byte_47
		CMP		#$0F
		BNE		loc_F3BA
		LDX		#$16
loc_F3BA:
		STX		byte_47
loc_F3BC:
		LDA		#$3F
		LDX		#$08
		LDY		#$08
		JSR		sub_E8D2
; ---------------------------------------------------------------------------
		.WORD byte_40
; ---------------------------------------------------------------------------
locret_F3C7:
		RTS
; ---------------------------------------------------------------------------
loc_F3C8:
		LDA		locret_F634,Y
		STA		byte_3F,Y
		DEY
		BNE		loc_F3C8
		INC		byte_21
		LDA		byte_21
		AND		#$06
		TAY
		LDA		word_F36E,Y
		STA		byte_42
		LDA		word_F36E+1,Y
		STA		byte_43
		LDY		#$00
		LDA		byte_B2
		BNE		loc_F3EA
		LDY		#$10
loc_F3EA:
		STY		byte_22
		JMP		loc_F3BC
; ---------------------------------------------------------------------------
loc_F3EF:
		LDA		byte_F63F,Y
		STA		byte_3F,Y
		DEY
		BNE		loc_F3EF
		BEQ		loc_F3EA
loc_F3FA:
		JSR		_BIOS_sub_E161
		LDA		#$00
		LDX		#$58
		LDY		#$13
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD byte_F735
; ---------------------------------------------------------------------------
		LDA		#$00
		LDX		#$19
		LDY		#$00
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD byte_FCA5
; ---------------------------------------------------------------------------
		JSR		_BIOS_chr_fonts_load
		LDA		#$20
		LDX		#$6D
		LDY		#$AA
		JSR		_BIOS_screen_clear
		LDA		#$28
		LDX		#$6D
		LDY		#$AA
		JSR		_BIOS_screen_clear
		JSR		_BIOS_wait_for_nmi_mode00
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD _BIOS_tlm_res
; ---------------------------------------------------------------------------
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_F431:
		JSR		_BIOS_sub_E161
		LDY		#$03
		JSR		sub_F48C
		JSR		_BIOS_chr_fonts_load
		JSR		_BIOS_wait_for_nmi_mode00
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD byte_F080
; ---------------------------------------------------------------------------
		LDA		#$20
		LDX		#$24
		LDY		#$00
		JSR		_BIOS_screen_clear
		LDA		_ppu_ctrl_shadow
		AND		#$FB
		STA		_ppu_ctrl_shadow
		STA		_PPU_CTRL
		LDX		_PPU_STATUS
		LDX		#$28
		STX		_PPU_ADDR
		LDA		#$00
		STA		_PPU_ADDR
		LDA		_PPU_DATA
		LDY		#$00
loc_F468:
		LDA		_PPU_DATA
		CMP		byte_ED37,Y
		BNE		locret_F483
		INY
		CPY		#$E0
		BNE		loc_F468
		STX		_PPU_ADDR
		STY		_PPU_ADDR
loc_F47B:
		LDA		#$24
		STA		_PPU_DATA
		INY
		BNE		loc_F47B
locret_F483:
		RTS
; ---------------------------------------------------------------------------
byte_F484:
		.BYTE $02, $30,	$10, $29, $32, $00, $29, $10

; =============== S U B	R O U T	I N E =======================================
sub_F48C:
		LDX		#$03
loc_F48E:
		LDA		byte_F484,Y
		STA		byte_7,X
		DEY
		DEX
		BPL		loc_F48E
		LDA		#$29
		STA		byte_B
loc_F49B:
		LDA		byte_7
		LDX		#$01
		LDY		byte_9
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD byte_10
; ---------------------------------------------------------------------------
		LDA		byte_8
		LDX		#$01
		LDY		byte_A
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD byte_10
; ---------------------------------------------------------------------------
		LDY		#$01
loc_F4B3:
		CLC
		LDA		#$10
		ADC		byte_7,Y
		STA		byte_7,Y
		LDA		#$00
		ADC		byte_9,Y
		STA		byte_9,Y
		DEY
		BPL		loc_F4B3
		DEC		byte_B
		BNE		loc_F49B
		RTS

; =============== S U B	R O U T	I N E =======================================
_BIOS_self_test:
		LDA		#$20
		LDX		#$24
		LDY		#$00
		JSR		_BIOS_screen_clear
		JSR		_BIOS_wait_for_nmi_mode00
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD byte_F066
; ---------------------------------------------------------------------------
		JSR		sub_F5FB
		BNE		loc_F527
		LDA		#$00
		LDX		#$00
		LDY		#$00
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD $C000
; ---------------------------------------------------------------------------
		LDA		#$00
		LDX		#$00
		LDY		#$10
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD $D000
; ---------------------------------------------------------------------------
		LDA		#$02
		LDX		#$00
		LDY		#$00
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD $C000
; ---------------------------------------------------------------------------
		LDA		#$02
		LDX		#$00
		LDY		#$10
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD $D000
; ---------------------------------------------------------------------------
		LDA		#$C0
		STA		word_0+1
		LDY		#$00
		STY		word_0
		LDX		#$20
		LDA		#$7F
		ADC		#$02
		JSR		sub_F61B
		BEQ		loc_F54E
		LDA		word_0+1
		AND		#$03
		STA		word_0+1
loc_F527:
		LDA		#$11
		STA		byte_B
		LDY		#$03
		LDA		word_0
loc_F52F:
		TAX
		AND		#$0F
		STA		byte_7,Y
		DEY
		TXA
		LSR
		LSR
		LSR
		LSR
		STA		byte_7,Y
		LDA		word_0+1
		DEY
		BPL		loc_F52F
		LDA		#$20
		LDX		#$F4
		LDY		#$05
		JSR		sub_E8D2
; ---------------------------------------------------------------------------
		.WORD byte_7
; ---------------------------------------------------------------------------
loc_F54E:
		JSR		_BIOS_chr_fonts_load
		JSR		_BIOS_get_inputB
		LDA		_pads_held
		CMP		#$81
		BNE		loc_F5B8
		JSR		_BIOS_ppu_data_send_param
; ---------------------------------------------------------------------------
		.WORD byte_F56B
; ---------------------------------------------------------------------------
		JSR		_BIOS_wait_for_nmi_mode00
		JSR		sub_EAEA
		JSR		_BIOS_ppu_bg_on
loc_F568:
		JMP		loc_F568
; ---------------------------------------------------------------------------
byte_F56B:
		.BYTE $20,$E7,$11,$02,$0C,$03,$03,$24,$12,$17,$1D,$0E,$1B,$17,$0A,$15
		.BYTE $24,$1B,$18,$16,$21,$63,$19,$19,$1B,$18,$10,$1B,$0A,$16,$0E,$0D
		.BYTE $24,$0B,$22,$24,$1D,$0A,$14,$0A,$18,$24,$1C,$0A,$20,$0A,$17,$18
		.BYTE $21,$A3,$19,$17,$12,$17,$1D,$0E,$17,$0D,$18,$24,$0C,$18,$27,$15
		.BYTE $1D,$0D,$26,$24,$0D,$0E,$1F,$26,$17,$18,$26,$02,$FF
; ---------------------------------------------------------------------------
loc_F5B8:
		LDA		#$01
		STA		byte_F
		LDA		#$FF
		CLC
		PHA
		PHP
loc_F5C1:
		JSR		_BIOS_wait_for_nmi_mode00
		JSR		sub_E86A
		JSR		sub_EAEA
		JSR		_BIOS_ppu_bg_on
		DEC		byte_F
		BNE		loc_F5DD
		PLP
		PLA
		STA		_FDS_REG26
		ROL
		PHA
		PHP
		LDA		#$19
		STA		byte_F
loc_F5DD:
		LDA		_FDS_REG33
		LDX		#$07
loc_F5E2:
		LDY		#$01
		ASL
		BCS		loc_F5E8
		DEY
loc_F5E8:
		STY		byte_7,X
		DEX
		BPL		loc_F5E2
		LDA		#$21
		LDX		#$70
		LDY		#$08
		JSR		sub_E8D2
; ---------------------------------------------------------------------------
		.WORD byte_7
; ---------------------------------------------------------------------------
		JMP		loc_F5C1

; =============== S U B	R O U T	I N E =======================================
sub_F5FB:
		LDA		#$60
		LDX		#$80
		STX		byte_3
		PHA
		STA		word_0+1
		LDY		#$00
		STY		word_0
		CLV
		JSR		sub_F61B
		PLA
		STA		word_0+1
		STY		word_0
		LDX		byte_3
		LDA		#$7F
		ADC		#$02
		JSR		sub_F61B
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_F61B:
		STX		byte_2
loc_F61D:
		LDA		byte_2
		BVS		loc_F62E
		STA		(word_0),Y
loc_F623:
		INC		byte_2
		DEY
		BNE		loc_F61D
		INC		word_0+1
		DEX
		BNE		sub_F61B
		RTS
; ---------------------------------------------------------------------------
loc_F62E:
		CMP		(word_0),Y
		BEQ		loc_F623
		STY		word_0
locret_F634:
		RTS
; ---------------------------------------------------------------------------
		.BYTE $0F,$30,$27,$16,$0F,$10,$00,$16
_BIOS_tlm_res:
		.BYTE $3F,$08
byte_F63F:
		.BYTE $18,$0F,$21,$01,$0F,$0F,$00,$02,$01,$0F,$27,$16,$01,$0F,$27,$30
		.BYTE $1A,$0F,$0F,$01,$0F,$0F,$0F,$0F,$0F,$20,$E4,$02,$6E,$73,$20,$E6
		.BYTE $54,$77,$20,$FA,$02,$78,$7C,$21,$04,$02,$6F,$74,$21,$06,$54,$24
		.BYTE $21,$1A,$02,$79,$7D,$21,$24,$C5,$70,$21,$3B,$C5,$70,$21,$25,$C5
		.BYTE $24,$21,$3A,$C5,$24,$21,$C4,$02,$71,$75,$21,$C6,$54,$24,$21,$DA
		.BYTE $02,$7A,$7E,$21,$E4,$02,$72,$76,$21,$E6,$54,$77,$21,$FA,$02,$7B
		.BYTE $7F,$21,$26,$14,$24,$24,$30,$31,$32,$33,$34,$35,$36,$37,$38,$39
		.BYTE $3A,$3B,$3C,$3D,$3E,$3F,$24,$24,$21,$46,$14,$24,$24,$40,$41,$42
		.BYTE $43,$44,$45,$46,$47,$48,$49,$4A,$4B,$4C,$4D,$4E,$4F,$24,$24,$21
		.BYTE $66,$14,$24,$24,$50,$51,$52,$53,$54,$55,$56,$57,$58,$59,$5A,$5B
		.BYTE $5C,$5D,$5E,$5F,$24,$24,$21,$86,$14,$24,$24,$24,$24,$24,$24,$24
		.BYTE $24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$24,$21,$A6,$54
		.BYTE $24,$22,$0F,$C4,$83,$22,$10,$C4,$84,$22,$8F,$02,$85,$86,$23,$E0
		.BYTE $50,$FF,$23,$F0,$48,$AF,$FF
byte_F716:
		.BYTE $20,$40,$60,$80,$20,$20,$60,$81,$20,$00,$60,$81,$FF
byte_F723:
		.BYTE $23,$40,$60,$80,$23,$60,$60,$81,$FF
byte_F72C:
		.BYTE $23,$80,$60,$82,$23,$A0,$60,$82,$FF
byte_F735:
		.BYTE $FF,$FF,$FF,$FF,$FE,$FE,$FE,$FE,$FF,$FF,$FF,$FC,$FD,$FD,$FD,$FD
		.BYTE $FF,$FF,$FF,$FF,$00,$00,$00,$00,$FF,$FF,$FF,$00,$FF,$FF,$FF,$C0
		.BYTE $FF,$FF,$FF,$FF,$7E,$7E,$7E,$7E,$FF,$FF,$FF,$7E,$7D,$7D,$7D,$7D
		.BYTE $FF,$FF,$FF,$FF,$00,$00,$00,$00,$FF,$FF,$FF,$01,$FE,$FE,$FE,$86
		.BYTE $FF,$FF,$FF,$FF,$FF,$FF,$FE,$FE,$FF,$FF,$FF,$FF,$FE,$FE,$FD,$FD
		.BYTE $FF,$FF,$FF,$FF,$01,$00,$00,$00,$FF,$FF,$FF,$03,$FD,$FE,$FF,$C3
		.BYTE $FF,$FF,$FF,$FF,$80,$00,$00,$00,$FF,$FF,$FF,$81,$7E,$FE,$FF,$87
		.BYTE $FF,$FF,$FF,$FF,$F8,$F8,$78,$78,$FF,$FF,$FF,$F0,$F7,$F7,$77,$77
		.BYTE $FF,$FF,$FF,$FF,$7E,$7C,$7C,$78,$FF,$FF,$FF,$7E,$7D,$7B,$7B,$77
		.BYTE $FF,$FF,$FF,$FF,$00,$00,$00,$00,$FF,$FF,$FF,$01,$FE,$FF,$FF,$CF
		.BYTE $FF,$FF,$FF,$FF,$FF,$7E,$7C,$78,$FF,$FF,$FF,$FF,$FE,$7D,$7B,$77
		.BYTE $FF,$FF,$FF,$FF,$00,$00,$00,$00,$FF,$FF,$FF,$00,$FF,$FF,$FF,$C3
		.BYTE $FF,$FF,$FF,$FF,$7F,$3F,$1F,$1F,$FF,$FF,$FF,$FF,$7F,$BF,$DE,$FE
		.BYTE $FF,$FF,$FF,$FF,$80,$80,$00,$00,$FF,$FF,$FF,$81,$7E,$7F,$FF,$E1
		.BYTE $FF,$FF,$FF,$FF,$C0,$00,$00,$00,$FF,$FF,$FF,$C0,$BF,$7F,$FF,$C3
		.BYTE $FF,$FF,$FF,$FF,$7F,$7F,$3F,$3F,$FF,$FF,$FF,$FF,$7F,$7F,$BF,$BF
		.BYTE $FE,$FE,$FE,$FE,$FE,$FE,$FE,$FE,$FD,$FD,$FD,$FD,$FD,$FD,$FD,$FD
		.BYTE $1F,$1F,$1F,$00,$00,$00,$00,$1F,$DF,$DF,$C0,$FE,$FE,$FE,$C0,$DF
		.BYTE $FC,$FC,$FC,$FC,$F8,$F8,$F8,$F8,$FB,$FB,$FB,$FB,$F7,$F7,$F7,$F7
		.BYTE $38,$38,$38,$38,$38,$7C,$7C,$00,$B7,$B7,$B7,$B7,$B7,$7B,$03,$FF
		.BYTE $7E,$7E,$7E,$7E,$3E,$3E,$3E,$3E,$7D,$7D,$7D,$7D,$BD,$BD,$BD,$BD
		.BYTE $1C,$1C,$1C,$1C,$1C,$1C,$1C,$1C,$DB,$DB,$DB,$DB,$DB,$DB,$DB,$DB
		.BYTE $38,$38,$38,$38,$38,$38,$38,$38,$B7,$B7,$B7,$B7,$B7,$B7,$B7,$B7
		.BYTE $78,$78,$78,$78,$78,$78,$78,$78,$77,$77,$77,$77,$77,$77,$77,$77
		.BYTE $78,$78,$78,$78,$78,$78,$78,$78,$77,$77,$77,$77,$77,$77,$77,$77
		.BYTE $38,$78,$7F,$7F,$7F,$7F,$7F,$7F,$B7,$70,$7F,$7F,$7F,$7F,$7F,$70
		.BYTE $78,$78,$F8,$F8,$F8,$F8,$F8,$F8,$77,$77,$F7,$F7,$F7,$F7,$F7,$77
		.BYTE $3E,$7F,$7F,$63,$63,$67,$7F,$7F,$BD,$7E,$66,$5A,$5A,$66,$7E,$7E
		.BYTE $0F,$0F,$0F,$0F,$0F,$0F,$0F,$0F,$EE,$EE,$EE,$EE,$EE,$EE,$EE,$EE
		.BYTE $0E,$0E,$0E,$0E,$0E,$0E,$0E,$0E,$ED,$ED,$ED,$ED,$ED,$ED,$ED,$ED
		.BYTE $1C,$1C,$1C,$1C,$1C,$1C,$1C,$1C,$DB,$DB,$DB,$DB,$DB,$DB,$DB,$DB
		.BYTE $3F,$3F,$3F,$3F,$3F,$3F,$3F,$3F,$BF,$BF,$BF,$BF,$BF,$BF,$BF,$BF
		.BYTE $FE,$FE,$FE,$FE,$FE,$FE,$FF,$FF,$FD,$FD,$FD,$FD,$FD,$FC,$FF,$FF
		.BYTE $1F,$1F,$1F,$1F,$1F,$1F,$FF,$FF,$DF,$DF,$DF,$DF,$DF,$1F,$FF,$FF
		.BYTE $F0,$F0,$F0,$F0,$F0,$F0,$FF,$FF,$EF,$EE,$EE,$EE,$EE,$E0,$FF,$FF
		.BYTE $00,$00,$FE,$FE,$FE,$FE,$FF,$FF,$FF,$01,$FD,$FD,$FD,$FC,$FF,$FF
		.BYTE $1E,$1E,$1E,$1E,$1E,$1E,$FF,$FF,$DD,$DD,$DD,$DD,$DD,$1C,$FF,$FF
		.BYTE $1C,$1C,$1C,$1C,$1C,$1C,$FF,$FF,$DB,$DB,$DB,$DB,$DB,$18,$FF,$FF
		.BYTE $38,$38,$38,$38,$38,$38,$FF,$FF,$B7,$B7,$B7,$B7,$B7,$30,$FF,$FF
		.BYTE $78,$78,$78,$78,$78,$78,$FF,$FF,$77,$77,$77,$77,$77,$70,$FF,$FF
		.BYTE $78,$78,$7C,$7C,$7E,$7F,$FF,$FF,$77,$77,$7B,$7B,$7D,$7E,$FF,$FF
		.BYTE $38,$10,$00,$00,$00,$01,$FF,$FF,$B7,$CF,$FF,$FF,$FE,$01,$FF,$FF
		.BYTE $78,$78,$7C,$7E,$FF,$FF,$FF,$FF,$77,$77,$7B,$7D,$FE,$FF,$FF,$FF
		.BYTE $3E,$1C,$00,$00,$00,$80,$FF,$FF,$BD,$C3,$FF,$FF,$FF,$00,$FF,$FF
		.BYTE $0F,$0F,$1F,$3F,$7F,$FF,$FF,$FF,$EE,$EE,$DE,$BE,$7E,$FE,$FF,$FF
		.BYTE $0E,$0E,$0E,$0E,$0E,$0E,$FF,$FF,$ED,$ED,$ED,$ED,$ED,$0C,$FF,$FF
		.BYTE $1C,$1C,$1C,$1C,$1C,$1C,$FF,$FF,$DB,$DB,$DB,$DB,$DB,$18,$FF,$FF
		.BYTE $3F,$3F,$3F,$3F,$3F,$3F,$FF,$FF,$BF,$BF,$BF,$BF,$BF,$3F,$FF,$FF
		.BYTE $02,$02,$06,$FF,$FF,$FF,$FF,$FF,$FD,$FD,$FD,$FF,$FF,$FF,$FF,$FF
		.BYTE $FF,$07,$07,$07,$07,$07,$07,$07,$07,$FF,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $07,$07,$07,$07,$07,$07,$07,$07,$FF,$FF,$FF,$FF,$FF,$FF,$FE,$FE
		.BYTE $07,$07,$07,$07,$07,$07,$07,$07,$FE,$FE,$FE,$FE,$FE,$FF,$FF,$FF
		.BYTE $07,$07,$07,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $FF,$F8,$E0,$C1,$83,$87,$07,$07,$F8,$E7,$DF,$BF,$7F,$7F,$FF,$FF
		.BYTE $07,$07,$07,$07,$07,$87,$83,$C3,$FF,$FF,$FF,$FF,$FF,$7F,$7F,$BD
		.BYTE $E1,$E0,$F8,$FF,$FF,$FF,$FF,$FF,$DE,$FF,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $FF,$0F,$03,$C1,$F0,$F8,$F8,$F8,$0F,$F3,$FD,$FE,$EF,$F7,$F7,$F7
		.BYTE $F8,$F8,$F8,$F8,$F8,$F8,$F0,$E0,$F7,$F7,$F7,$F7,$F7,$F7,$EF,$DF
		.BYTE $C1,$03,$0F,$FF,$FF,$FF,$FF,$FF,$3F,$FF,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $FF,$FF,$FF,$FF,$7F,$7F,$3F,$3F,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $3F,$3F,$3F,$3F,$3F,$7F,$7F,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
		.BYTE $00,$00,$01,$03,$06,$0C,$18,$10,$00,$03,$06,$0C,$19,$33,$27,$6F
		.BYTE $30,$20,$20,$60,$40,$40,$40,$40,$4F,$5E,$DC,$9C,$B9,$B9,$B9,$B9
		.BYTE $40,$40,$40,$40,$40,$40,$40,$40,$B9,$B9,$B9,$B9,$B9,$B9,$B9,$B9
		.BYTE $40,$40,$40,$40,$60,$20,$20,$20,$B9,$B9,$B9,$B9,$9C,$DE,$5F,$5F
		.BYTE $10,$00,$00,$00,$00,$00,$00,$00,$6F,$3F,$3F,$1F,$0E,$07,$03,$00
		.BYTE $00,$7F,$C0,$00,$00,$00,$00,$00,$FF,$80,$3F,$FF,$FF,$F0,$C0,$8F
		.BYTE $07,$1F,$3F,$7F,$7F,$FF,$FF,$FF,$3F,$7F,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $FF,$FF,$FF,$7F,$7F,$3F,$1F,$07,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $10,$0F,$00,$00,$00,$00,$00,$00,$EF,$F0,$FF,$FF,$FF,$00,$80,$FF
		.BYTE $00,$FF,$00,$00,$00,$00,$00,$00,$FF,$00,$FF,$FF,$FF,$00,$00,$FF
		.BYTE $00,$FA,$00,$00,$00,$00,$00,$00,$FF,$05,$FF,$FF,$FF,$3F,$1F,$FF
		.BYTE $E0,$F9,$FC,$FE,$FE,$FF,$FF,$FF,$FF,$FE,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $FF,$FF,$FF,$FE,$FE,$FC,$F9,$E3,$FF,$FF,$FF,$FF,$FF,$FF,$FE,$FC
		.BYTE $0E,$F8,$00,$00,$00,$00,$00,$00,$F1,$07,$FF,$FF,$FC,$00,$01,$FF
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$00,$C0,$E0,$F0,$F8,$FC,$FC,$FE
		.BYTE $00,$00,$80,$80,$40,$40,$40,$40,$FE,$FA,$7B,$79,$B9,$B9,$B9,$B9
		.BYTE $40,$40,$40,$40,$C0,$80,$80,$00,$B9,$B9,$B9,$B9,$39,$73,$72,$E2
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$E6,$C4,$8C,$18,$30,$60,$C0,$00
		.BYTE $00,$FF,$00,$FF,$00,$FF,$00,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $FF,$00,$FF,$FF,$FF,$00,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $FF,$FF,$00,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
		.BYTE $06,$06,$06,$06,$06,$06,$06,$00,$00,$00,$00,$00,$00,$00,$00,$00
		.BYTE $60,$60,$60,$60,$60,$60,$60,$00,$00,$00,$00,$00,$00,$00,$00,$00
		.BYTE $1F,$5F,$50,$57,$57,$50,$1F,$00,$20,$20,$AF,$A7,$A7,$AF,$60,$3F
		.BYTE $F8,$FA,$0A,$EA,$EA,$0A,$F8,$00,$04,$04,$F5,$E5,$E5,$F5,$06,$FC
byte_FCA5:
		.BYTE $00,$00,$00,$00,$00,$00,$03,$1F,$00,$00,$00,$03,$03,$0F,$00,$02
		.BYTE $3F,$1F,$0F,$07,$20,$70,$70,$20,$04,$1E,$00,$00,$01,$03,$0F,$1F
		.BYTE $00,$04,$0F,$1F,$0F,$0C,$00,$00,$0F,$07,$2F,$3F,$3F,$1C,$18,$00
		.BYTE $00,$00,$00,$00,$00,$00,$F0,$F8,$00,$00,$00,$80,$E0,$F0,$F0,$48
		.BYTE $F8,$FC,$F8,$E0,$10,$10,$32,$26,$48,$9C,$08,$00,$F0,$FC,$FC,$F8
		.BYTE $7C,$F8,$F8,$FC,$FC,$78,$00,$00,$F8,$F8,$F8,$FC,$FC,$7C,$1C,$38
		.BYTE $00,$00,$00,$00,$00,$00,$00,$07,$00,$00,$00,$00,$07,$07,$1F,$01
		.BYTE $3F,$7F,$3F,$1F,$0F,$01,$C2,$C2,$04,$08,$3D,$00,$00,$07,$0F,$1F
		.BYTE $C6,$07,$1F,$1F,$0F,$0F,$00,$00,$3F,$7F,$1D,$1F,$0F,$0F,$07,$0F
		.BYTE $00,$00,$00,$00,$00,$00,$00,$E0,$00,$00,$00,$00,$00,$C0,$E0,$E0
		.BYTE $F0,$F0,$F8,$F0,$C0,$00,$00,$00,$90,$90,$38,$10,$00,$E0,$F0,$F8
		.BYTE $0C,$1C,$FC,$F8,$F8,$78,$00,$00,$F0,$E0,$E0,$F4,$FE,$7E,$02,$00
		.BYTE $00,$00,$00,$00,$00,$00,$03,$1F,$00,$00,$00,$03,$03,$0F,$00,$02
		.BYTE $3F,$1F,$0F,$07,$00,$01,$01,$13,$04,$1E,$00,$00,$03,$07,$0F,$0F
		.BYTE $1F,$1F,$0F,$07,$07,$03,$00,$00,$0F,$0D,$0F,$07,$07,$03,$00,$01
		.BYTE $00,$00,$00,$00,$00,$00,$F0,$F8,$00,$00,$00,$80,$E0,$F0,$F0,$48
		.BYTE $F8,$FC,$F8,$E0,$80,$00,$00,$C0,$48,$9C,$08,$00,$E0,$F0,$F8,$F8
		.BYTE $80,$C0,$F0,$F0,$F0,$E0,$00,$00,$F8,$30,$10,$30,$F0,$E0,$E0,$E0
		.BYTE $00,$1C,$1E,$0E,$04,$00,$00,$07,$00,$00,$00,$10,$18,$3B,$38,$38
		.BYTE $0F,$07,$03,$03,$06,$0C,$09,$0F,$31,$3F,$1C,$1E,$0F,$0F,$4F,$4F
		.BYTE $1F,$1F,$1F,$07,$00,$00,$00,$00,$7E,$7F,$7F,$07,$00,$00,$00,$00
		.BYTE $00,$00,$00,$00,$00,$00,$FC,$FE,$00,$00,$00,$E0,$F8,$FC,$3C,$92
		.BYTE $FE,$FF,$FE,$F8,$60,$C0,$83,$87,$12,$A7,$02,$00,$FC,$FE,$FC,$F0
		.BYTE $D2,$F0,$E0,$F0,$F0,$60,$00,$00,$F0,$F8,$FC,$FE,$F2,$60,$00,$00
		.BYTE $00,$00,$00,$00,$00,$00,$00,$00,$80,$00,$00,$00,$00,$00,$00,$00
		.BYTE $FF

; =============== S U B	R O U T	I N E =======================================
sub_FE36:
		LSR
		BCS		loc_FE66
		LSR		byte_E1
		BCS		loc_FE47
		LSR
		BCS		loc_FEA6
		LSR		byte_E1
		BCS		loc_FE7A
		JMP		loc_FF6A
; ---------------------------------------------------------------------------
loc_FE47:
		LDA		#$10
		STA		_APU_PULSE1_ENV
		LDA		#$01
		STA		_APU_TRI_COUNT
		STY		byte_E3
		LDA		#$20
		STA		byte_E4
		LDX		#$5C
		LDY		#$7F
		STX		_APU_PULSE2_ENV
		STY		_APU_PULSE2_SWEEP
		LDA		#$F9
		STA		_APU_PULSE2_LEN
loc_FE66:
		LDA		byte_E4
		LSR
		BCC		loc_FE6F
		LDA		#$0D
		BNE		loc_FE71
loc_FE6F:
		LDA		#$7C
loc_FE71:
		STA		_APU_PULSE2_TIME
		JMP		loc_FFC6
; ---------------------------------------------------------------------------
loc_FE77:
		JMP		loc_FFCA
; ---------------------------------------------------------------------------
loc_FE7A:
		STY		byte_E3
		LDX		#$9C
		LDY		#$7F
		STX		_APU_PULSE1_ENV
		STX		_APU_PULSE2_ENV
		STY		_APU_PULSE1_SWEEP
		STY		_APU_PULSE2_SWEEP
		LDA		#$20
		STA		_APU_TRI_COUNT
		LDA		#$01
		STA		_APU_NOISE_ENV
		LDX		#$00
		STX		byte_E9
		STX		byte_EA
		STX		byte_EB
		LDA		#$01
		STA		byte_E6
		STA		byte_E7
		STA		byte_E8
loc_FEA6:
		DEC		byte_E6
		BNE		loc_FEC1
		LDY		byte_E9
		INY
		STY		byte_E9
		LDA		byte_FF1F,Y
		BEQ		loc_FE77
		JSR		sub_FFE9
		STA		byte_E6
		TXA
		AND		#$3E
		LDX		#$04
		JSR		sub_FFD9
loc_FEC1:
		DEC		byte_E7
		BNE		loc_FEDA
		LDY		byte_EA
		INY
		STY		byte_EA
		LDA		byte_FF33,Y
		JSR		sub_FFE9
		STA		byte_E7
		TXA
		AND		#$3E
		LDX		#$00
		JSR		sub_FFD9
loc_FEDA:
		DEC		byte_E8
		BNE		loc_FEFD
		LDA		#$09
		STA		_APU_NOISE_LOOP
		LDA		#$08
		STA		_APU_NOISE_LEN
		LDY		byte_EB
		INY
		STY		byte_EB
		LDA		byte_FF46,Y
		JSR		sub_FFE9
		STA		byte_E8
		TXA
		AND		#$3E
		LDX		#$08
		JSR		sub_FFD9
loc_FEFD:
		JMP		loc_FF6A
; ---------------------------------------------------------------------------
word_FF00:
		.WORD $5703
		.WORD $0000
		.WORD $D408
		.WORD $BD08
		.WORD $B208
		.WORD $AB09
		.WORD $7C09
		.WORD $3F09
		.WORD $1C09
		.WORD $FD08
		.WORD $EE08
		.WORD $FC09
		.WORD $DF09
byte_FF1A:
		.BYTE $06,$0C,$12,$18,$08
byte_FF1F:
		.BYTE $48,$CA,$CE,$D4,$13,$11,$0F,$90,$10,$C4,$C8,$07,$05,$15,$C4,$D2
		.BYTE $D4,$8E,$0C,$4F
byte_FF33:
		.BYTE $00,$D6,$D6,$CA,$0B,$19,$17,$98,$18,$CE,$D4,$15,$13,$11,$D2,$CA
		.BYTE $CC,$96,$18
byte_FF46:
		.BYTE $57,$CE,$0F,$0F,$0F,$CE,$CE,$CE,$CE,$CE,$0F,$0F,$0F,$CE,$CE,$CE
		.BYTE $CE,$CE,$0F,$0F,$0F,$CE
; ---------------------------------------------------------------------------
loc_FF5C:
		LDY		byte_E1
		LDA		byte_E3
		LSR		byte_E1
		BCS		loc_FF7B
		LSR
		BCS		loc_FF9A
		JMP		sub_FE36
; ---------------------------------------------------------------------------
loc_FF6A:
		LDA		#$00
		STA		byte_E1
		RTS
; ---------------------------------------------------------------------------
byte_FF6F:
		.BYTE $06, $0C,	$12
byte_FF72:
		.BYTE $47, $5F,	$71
byte_FF75:
		.BYTE $5F, $71,	$8E
byte_FF78:
		.BYTE $71, $8E,	$BE
; ---------------------------------------------------------------------------
loc_FF7B:
		STY		byte_E3
		LDA		#$12
		STA		byte_E4
		LDA		#$02
		STA		byte_E5
		LDX		#$9F
		LDY		#$7F
		STX		_APU_PULSE1_ENV
		STX		_APU_PULSE2_ENV
		STY		_APU_PULSE1_SWEEP
		STY		_APU_PULSE2_SWEEP
		LDA		#$20
		STA		_APU_TRI_COUNT
loc_FF9A:
		LDA		byte_E4
		LDY		byte_E5
		CMP		byte_FF6F,Y
		BNE		loc_FFC6
		LDA		byte_FF72,Y
		STA		_APU_PULSE1_TIME
		LDX		#$58
		STX		_APU_PULSE1_LEN
		LDA		byte_FF75,Y
		STA		_APU_PULSE2_TIME
		STX		_APU_PULSE2_LEN
		LDA		byte_FF78,Y
		STA		_APU_TRI_TIME
		STX		_APU_TRI_LEN
		LDA		byte_E5
		BEQ		loc_FFC6
		DEC		byte_E5
loc_FFC6:
		DEC		byte_E4
		BNE		loc_FFD6
loc_FFCA:
		LDA		#$00
		STA		byte_E3
		LDA		#$10
		STA		_APU_PULSE1_ENV
		STA		_APU_PULSE2_ENV
loc_FFD6:
		JMP		loc_FF6A

; =============== S U B	R O U T	I N E =======================================
sub_FFD9:
		TAY
		LDA		word_FF00+1,Y
		BEQ		locret_FFE8
		STA		_APU_PULSE1_TIME,X
		LDA		word_FF00,Y
		STA		_APU_PULSE1_LEN,X
locret_FFE8:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_FFE9:
		TAX
		ROR
		TXA
		ROL
		ROL
		ROL
		AND		#$07
		TAY
		LDA		byte_FF1A,Y
		RTS
; ---------------------------------------------------------------------------
		.BYTE $FF, $FF,	$FF
		.BYTE $01
		.WORD _BIOS_NMI
		.WORD _BIOS_RESET
		.WORD _BIOS_IRQ
