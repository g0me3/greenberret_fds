
;		ORG $8080

; =============== S U B	R O U T	I N E =======================================
RESET:
		CLI
		CLD
		LDA		#$00
		STA		_main_sub_idx
		STA		byte_103
		LDX		#$FF
		TXS
		LDA		#$C0
		STA		byte_100
		JSR		_nmi_off_render_off
;		LDA		#$01
;		JSR		_integrity_test
;		BNE		_j_BIOS_RESET
;		LDA		#$09
;		JSR		_integrity_test
;		BNE		_j_BIOS_RESET
		LDX		#$F0
		LDA		#$00
loc_80A6:
		STA		$0000,X
		DEX
		BNE		loc_80A6
loc_80AB:
		STA		$0300,X
		STA		$0400,X
		STA		$0500,X
		STA		$0600,X
		STA		$0700,X
		DEX
		BNE		loc_80AB
		LDA		#$50
		STA		_hi_scores+1
		LDA		#$00
		STA		_ppu_queue_buf
		JSR		_render_on
		LDA		#$7D
		JSR		_apu_load_safe
_MAIN_IDLE_LOOP:
		JMP		_MAIN_IDLE_LOOP

; =============== S U B	R O U T	I N E =======================================
;_j_BIOS_RESET:
;		JMP		_BIOS_RESET

; =============== S U B	R O U T	I N E =======================================
NMI:
		PHP
		PHA
		TXA
		PHA
		TYA
		PHA
		LDA		_PPU_STATUS
		LDY		_busy_flags
		BNE		loc_80F3
		JSR		_nmi_off_render_off
		STA		_PPU_OAM_ADDR
		LDY		#$02
		STY		_PPU_OAM_DMA
		JSR		_nmi_ppu_dequeue
loc_80F3:
		LDX		_nmi_counter
		BEQ		loc_80F9
		DEC		_nmi_counter
loc_80F9:
		LDA		_busy_flags
		BNE		loc_8106
		LDA		_main_sub_idx
		CMP		#$0A
		BEQ		loc_8106
		JSR		sub_8EA7
loc_8106:
		LDA		_nmi_counter
		BNE		loc_8115
		LDA		_ppu_mask_shadow
		STA		_PPU_MASK
		JSR		_nmi_hud_draw_wait
		JSR		_apu_play_safe
loc_8115:
		LDY		_busy_flags
		BNE		loc_8130
		LDA		#$01
		STA		_busy_flags
		JSR		_j_BIOS_get_inputA
		JSR		_main_sub_exec
		JSR		_obj_compiler
		JSR		_sprite_manager
		JSR		_ppu_queue_byte00_insert
		LDA		#$00
		STA		_busy_flags
loc_8130:
		PLA
		TAY
		PLA
		TAX
		PLA
		PLP

; =============== S U B	R O U T	I N E =======================================
IRQ:
		RTI

; =============== S U B	R O U T	I N E =======================================
_render_on:
		LDA		#$0F
		STA		_apu_STATUS
		LDA		#$C0
		STA		_PAD1_REG

; =============== S U B	R O U T	I N E =======================================
_render_on_nmi_on:
		LDA		#$A8
		STA		_ppu_ctrl_shadow
		STA		_PPU_CTRL
		LDA		#$1E
		STA		_ppu_mask_shadow
		LDA		#$05
		STA		_nmi_counter
		RTS

; =============== S U B	R O U T	I N E =======================================
_nmi_hud_draw_wait:
		LDA		_busy_flags
		BNE		loc_8162
		LDA		_main_sub_idx
		CMP		#$0A
		BEQ		loc_818E
		LDA		byte_5B
		BNE		loc_8162
		JSR		_hud_draw_handlers
loc_8162:
		LDA		#$00
		STA		byte_5B
		LDA		#$20
		STA		_PPU_ADDR
		LDA		#$00
		STA		_PPU_ADDR
		LDA		_PPU_STATUS
		LDA		#$00
		STA		_PPU_SCROLL
		LDA		#$E8
		STA		_PPU_SCROLL
		LDA		_PPU_STATUS
		LDX		#$31
		LDA		_busy_flags
		BNE		loc_8188
		LDX		#$29
loc_8188:
		PHA
		LDA		#$16
		SEC
loc_E14D:
		SBC		#$01
		BCS		loc_E14D
		PLA
		DEX
		BPL		loc_8188
loc_818E:
		LDA		_PPU_STATUS
		LDA		byte_FD
		STA		_PPU_SCROLL
		LDA		#$E8
		STA		_PPU_SCROLL
		LDA		_ppu_ctrl_shadow

; =============== S U B	R O U T	I N E =======================================
_ppu_ctrl_set:
		STA		_PPU_CTRL
		CLI
		RTS

; =============== S U B	R O U T	I N E =======================================
_nmi_off_render_off:
;		LDA		#$47
;		STA		byte_FA
;		STA		_FDS_REG25
		LDA		#$00
		STA		_PPU_MASK
		BEQ		_ppu_ctrl_set

; =============== S U B	R O U T	I N E =======================================
_nmi_ppu_dequeue:
		LDY		#$00
		STY		word_0
loc_9AE2:
		LDX		_ppu_queue_buf,Y
		BEQ		loc_9B07
		LDA		_ppu_ctrl_shadow
		AND		#$18
		ORA		byte_9ADB,X
		STA		_PPU_CTRL
		INY
		LDA		_PPU_STATUS
		LDA		_ppu_queue_buf,Y
		STA		word_0
		STA		_PPU_ADDR
		INY
		LDA		_ppu_queue_buf,Y
		STA		_PPU_ADDR
		INY
		BNE		loc_9B19
loc_9B07:
		LDA		#$00
		STA		_ppu_queue_buf
		STA		_ppu_queue_pos
		LDA		_ppu_ctrl_shadow
		STA		_PPU_CTRL
		RTS
; ---------------------------------------------------------------------------
loc_9B14:
		LDA		#$FF
loc_9B16:
		STA		_PPU_DATA
loc_9B19:
		LDA		_ppu_queue_buf,Y
		INY
		CMP		#$FF
		BNE		loc_9B16
		LDA		_ppu_queue_buf,Y
		CMP		#$03
		BCS		loc_9B14
		LDA		word_0
		CMP		#$3F
		BNE		loc_9AE2
		STA		_PPU_ADDR
		LDA		#$00
		STA		_PPU_ADDR
		STA		_PPU_ADDR
		STA		_PPU_ADDR
		BEQ		loc_9AE2

; =============== S U B	R O U T	I N E =======================================
_obj_compiler:
		LDA		#$00
		LDX		#$00
loc_81B4:
		STA		byte_300,X
		INX
		CPX		#$10
		BNE		loc_81B4
		LDY		#$00
		LDX		#$00
loc_81C0:
		LDA		byte_500,Y
		BEQ		loc_81E3
		LDA		byte_500+3,Y
		STA		byte_330,X
		LDA		byte_500+5,Y
		STA		byte_320,X
		LDA		byte_500+$B,Y
		STA		byte_340,X
		LDA		byte_500+$E,Y
		STA		byte_310,X
		LDA		byte_500+$F,Y
		STA		byte_300,X
loc_81E3:
		TYA
		CLC
		ADC		#$20
		TAY
		INX
		CPX		#$08
		BNE		loc_81C0
loc_81ED:
		LDA		byte_600,Y
		BEQ		loc_8210
		LDA		byte_600+3,Y
		STA		byte_330,X
		LDA		byte_600+5,Y
		STA		byte_320,X
		LDA		byte_600+$B,Y
		STA		byte_340,X
		LDA		byte_600+$E,Y
		STA		byte_310,X
		LDA		byte_600+$F,Y
		STA		byte_300,X
loc_8210:
		TYA
		CLC
		ADC		#$20
		TAY
		INX
		CPX		#$10
		BNE		loc_81ED
		RTS

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
_BIOS_merge_pads:
		LDA		word_0
		ORA		_pads_press
		STA		_pads_press
		LDA		word_0+1
		ORA		_pads_press+1
		STA		_pads_press+1
		RTS

; =============== S U B	R O U T	I N E =======================================
_apu_play_safe:
		LDA		_busy_flags
		AND		#$02
		BNE		locret_8224
		JMP		_apu_play
; ---------------------------------------------------------------------------
locret_8224:
		RTS

; =============== S U B	R O U T	I N E =======================================
_apu_load_safe:
		PHA
		LDA		_busy_flags
		ORA		#$02
		STA		_busy_flags
		PLA
		JSR		_apu_load
		LDA		#$01
		AND		_busy_flags
		STA		_busy_flags
		RTS

; =============== S U B	R O U T	I N E =======================================
;_unref:
;		RTS

; =============== S U B	R O U T	I N E =======================================
_main_sub_exec:
		INC		_frames_counter
		LDA		_main_sub_idx
		CMP		#$03
		BCS		loc_8243
		JSR		_title_intro_input_handler
loc_8243:
		LDA		_main_sub_idx
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD _main00_title_init
		.WORD _main01_title_idle
		.WORD _main02_title_demo_idle
		.WORD _main03_title_start_pressed
		.WORD _main04_intro_cutscene
		.WORD _main05_game
		.WORD _main06_game_over
		.WORD _main07_stage_complete_init
		.WORD _main08_stage_complete_anim
		.WORD _main09_ending
;		.WORD _main0A_loading_screen

; =============== S U B	R O U T	I N E =======================================
_bios_fonts_load:
		JSR		_nmi_off_render_off
		LDX		#$01
		LDA		#$0C
		LDY		#$00
		STY		_ppu_ctrl_shadow
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD _BIOS_chr_fonts_data+$120
; ---------------------------------------------------------------------------
		LDX		#$02
		LDA		#$5C
		LDY		#$02
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD _BIOS_chr_fonts_data+$128
; ---------------------------------------------------------------------------
		LDX		#$24
		LDA		#$1C
		LDY		#$00
		JSR		_BIOS_1bpp_chr_load
; ---------------------------------------------------------------------------
		.WORD _BIOS_chr_fonts_data
; ---------------------------------------------------------------------------
		JMP		_render_on
;
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
		STA		$0103,X
		LDA		#$00
		ADC		byte_6
		STA		$0104,X
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
;nullsub_5:
;		RTS

; =============== S U B	R O U T	I N E =======================================
_main00_title_init:
		LDA		#$01
		STA		byte_20
		LDA		#$12
		JSR		_fds_data_load
		LDA		#$08
		JSR		_fds_data_load
		JSR		_title_screen_draw
		LDA		#$04
		STA		_delay_counter+1
		JMP		_next_main_sub_delay80
; ---------------------------------------------------------------------------
byte_829F:
		.BYTE $AB,$B3

; =============== S U B	R O U T	I N E =======================================
_main01_title_idle:
		LDA		#$50
		STA		byte_500
		STA		byte_500+3
		LDA		#$37
		STA		byte_500+$F
		LDX		_players_num
		LDA		byte_829F,X
		STA		byte_500+5
		LDA		_frames_counter
		AND		#$03
		STA		byte_500+$E
		JSR		_do_delay_counters
		BNE		nullsub_3
		JMP		_next_main_sub

; =============== S U B	R O U T	I N E =======================================
nullsub_3:
		RTS

; =============== S U B	R O U T	I N E =======================================
_main02_title_demo_idle:
		LDX		_sub_sub_idx
		BNE		loc_82D0
		INC		_sub_sub_idx
		JSR		sub_8BF0
		RTS
; ---------------------------------------------------------------------------
loc_82D0:
		JSR		_main05_game_demo
		LDA		byte_23
		BEQ		nullsub_3

; =============== S U B	R O U T	I N E =======================================
_restart_from_beginning:
		LDA		#$00
		JMP		_set_main_sub_delay50

; =============== S U B	R O U T	I N E =======================================
_main03_title_start_pressed:
		LDX		_sub_sub_idx
		BNE		loc_82EE
		LDA		#$1D
		JSR		_apu_load_safe
		LDA		#$00
		STA		byte_20
		LDA		#$50
		JMP		_next_sub_sub_delay_ex
; ---------------------------------------------------------------------------
loc_82EE:
		DEX
		BNE		loc_830C
		DEC		_delay_counter
		BNE		loc_82F8
		JMP		_next_sub_sub
; ---------------------------------------------------------------------------
loc_82F8:
		LDA		#$01
		CLC
		ADC		_players_num
		STA		word_0
		LDA		#$08
		AND		_delay_counter
		ASL
		ASL
		ASL
		ASL
		ORA		word_0
		JMP		_tlm_lib_load
; ---------------------------------------------------------------------------
loc_830C:
		LDX		#$00
		STX		_sub_sub_idx
		JSR		_game_init
		JMP		_next_main_sub

; =============== S U B	R O U T	I N E =======================================
_main04_intro_cutscene:
		LDA		_sub_sub_idx
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD _intro_cutscene_sub0
		.WORD _intro_cutscene_sub1
		.WORD _intro_cutscene_sub2

; =============== S U B	R O U T	I N E =======================================
_intro_cutscene_sub0:
		LDA		#$08
		JSR		_file_lib_unpack
		JSR		_screen_clear

; =============== S U B	R O U T	I N E =======================================
_next_sub_sub_1:
		INC		_sub_sub_idx
		RTS

; =============== S U B	R O U T	I N E =======================================
_intro_cutscene_sub1:
		JSR		_intro_curscene_screen_draw
		LDA		#$7D
		JSR		_apu_load_safe
		LDA		#$26
		JSR		_apu_load_safe
		JSR		sub_8DC0
		LDA		#$D4
		STA		byte_5A
		LDA		#$18
		STA		byte_6D0
		LDA		#$01
		STA		byte_540
		LDA		#$05
		STA		byte_545
		LDA		#$FF
		STA		byte_543
		LDA		#$73
		STA		byte_54F
		LDA		#$00
		STA		byte_54E
		LDA		#$02
		STA		byte_55F
		LDY		#$00
		JSR		_type_msg_ptr_fetch
		JMP		_next_sub_sub_1

; =============== S U B	R O U T	I N E =======================================
_intro_cutscene_sub2:
		LDA		_frames_counter
		AND		#$07
		BNE		loc_8383
		INC		byte_6D0
		LDA		byte_6D0
		CMP		#$1C
		BNE		loc_8380
		LDA		#$18
		STA		byte_6D0
loc_8380:
		JSR		_tlm_lib_load
loc_8383:
		JSR		_type_msg_handler
		LDA		byte_540
		BEQ		loc_83B8
		DEC		byte_55F
		BNE		loc_83AB
		LDA		#$02
		STA		byte_55F
		LDA		byte_54F
		CMP		#$73
		BNE		loc_83A1
		LDA		#$7C
		STA		byte_54F
loc_83A1:
		INC		byte_54F
		BPL		loc_83AB
		LDA		#$73
		STA		byte_54F
loc_83AB:
		DEC		byte_543
		LDA		byte_543
		BNE		loc_83B8
		LDY		#$00
		STY		byte_540
loc_83B8:
		CMP		#$58
		BEQ		loc_8404
		CMP		#$08
		BEQ		loc_8411
loc_83C0:
		LDX		#$00
loc_83C2:
		LDA		byte_500+5,X
		CMP		#$AE
		BEQ		loc_8439
		LDA		_frames_counter
		AND		#$01
		BNE		loc_83F8
		INC		byte_500+5,X
		LDY		#$6E
		LDA		byte_500+5,X
		CMP		#$3E
		BEQ		loc_8432
		INY
		CMP		#$54
		BEQ		loc_8432
		INY
		CMP		#$64
		BEQ		loc_8432
		INY
		CMP		#$74
		BEQ		loc_8432
		INY
		CMP		#$84
		BEQ		loc_8432
		CMP		#$AE
		BCC		loc_83F8
		LDA		#$01
		STA		byte_500+$F,X
loc_83F8:
		CPX		#$20
		BEQ		loc_845C
		TXA
		CLC
		ADC		#$20
		TAX
		JMP		loc_83C2
; ---------------------------------------------------------------------------
loc_8404:
		LDX		#$00
		TXA
		STA		byte_500+$E,X
		LDA		#$80
		STA		byte_500+3,X
		BNE		loc_8421
loc_8411:
		LDX		#$20
		LDA		_players_num
		BEQ		loc_83C0
		LDA		#$01
		STA		byte_500+$E,X
		LDA		#$30
		STA		byte_500+3,X
loc_8421:
		LDA		#$0A
		STA		byte_500+5,X
		LDA		#$01
		STA		byte_500,X
		LDA		#$6D
		STA		byte_500+$F,X
		BNE		loc_83C0
loc_8432:
		TYA
		STA		byte_500+$F,X
		JMP		loc_83F8
; ---------------------------------------------------------------------------
loc_8439:
		INC		byte_500+3,X
		LDA		byte_500+3,X
		BNE		loc_8444
		STA		byte_500,X
loc_8444:
		LDA		_frames_counter
		AND		#$07
		BNE		loc_83F8
		INC		byte_500+$F,X
		LDA		byte_500+$F,X
		CMP		#$05
		BCC		loc_83F8
		LDA		#$01
		STA		byte_500+$F,X
		JMP		loc_83F8
; ---------------------------------------------------------------------------
loc_845C:
		LDA		_frames_counter
		AND		#$03
		BNE		locret_8467
		JSR		sub_A367
		BEQ		loc_8468
locret_8467:
		RTS
; ---------------------------------------------------------------------------
loc_8468:
		LDA		#$00
		STA		_game_main_sub_idx
		STA		byte_500
		STA		byte_520
		JMP		_next_main_sub

; =============== S U B	R O U T	I N E =======================================
_main06_game_over:
		LDA		_sub_sub_idx
		BNE		loc_84C1
		JSR		_screen_clear
		JSR		_bios_fonts_load
		JSR		_fds_load_bufs_clear
		JSR		sub_8DC0
		LDA		#$7D
		JSR		_apu_load_safe
		LDA		#$6F
		JSR		_apu_load_safe
		LDA		#$10
		JSR		_tlm_lib_load
		LDA		_continues_count
		CMP		#$03
		BCS		loc_84BA
		LDA		#$14
		JSR		_tlm_lib_load
		LDA		#$15
		JSR		_tlm_lib_load
		LDA		#$16
		JSR		_tlm_lib_load
		LDA		#$01
		STA		byte_5F
		LDA		#$50
		STA		byte_500
		STA		byte_500+3
		LDA		#$37
		STA		byte_500+$F
loc_84BA:
		LDA		#$54
		STA		byte_5A
		INC		_sub_sub_idx
locret_84C0:
		RTS
; ---------------------------------------------------------------------------
loc_84C1:
		CMP		#$02
		BEQ		loc_8508
		LDA		_continues_count
		CMP		#$03
		BCS		loc_8526
		LDX		byte_5F
		LDA		byte_8524,X
		STA		byte_500+5
		LDA		_pads_press
		AND		#$30
		BEQ		loc_84E3
		CMP		#$10
		BEQ		loc_84F1
		LDA		byte_5F
		EOR		#$01
		STA		byte_5F
loc_84E3:
		LDA		_frames_counter
		AND		#$07
		BNE		locret_84C0
		JSR		sub_A367
		BNE		locret_84C0
loc_84EE:
		JMP		_restart_from_beginning
; ---------------------------------------------------------------------------
loc_84F1:
		LDA		byte_5F
		BEQ		loc_84EE
		INC		_continues_count
		LDA		#$7D
		JSR		_apu_load_safe
		LDA		#$1D
		JSR		_apu_load_safe
		LDA		#$70
		STA		byte_5A
		INC		_sub_sub_idx
locret_8507:
		RTS
; ---------------------------------------------------------------------------
loc_8508:
		DEC		byte_5A
		BNE		locret_8507
		JSR		_game_init_ex
		LDA		#$00
		STA		byte_465
		LDA		#$05
		STA		_main_sub_idx
		JSR		sub_A509
		LDA		#$03
		STA		_game_main_sub_idx
		LDA		#$17
		JMP		_file_lib_unpack
; ---------------------------------------------------------------------------
byte_8524:
		.BYTE $93,$83
; ---------------------------------------------------------------------------
loc_8526:
		LDA		_pads_press
		AND		#$30
		BNE		loc_84EE
		LDA		_frames_counter
		AND		#$07
		BNE		locret_84C0
		JSR		sub_A367
		BNE		locret_84C0
		JMP		loc_84EE

; =============== S U B	R O U T	I N E =======================================
_main07_stage_complete_init:
		LDA		#$00
		STA		byte_463
		LDA		#$7D
		JSR		_apu_load_safe
		JSR		_nmi_off_render_off
		JSR		_fds_load_bufs_clear
		JSR		_screen_clear
		LDX		_1p_stage
		CPX		#$05
		BEQ		loc_855E
		LDA		#$09
		JSR		_file_lib_unpack
		JSR		_render_on_nmi_on
		JMP		loc_8568
; ---------------------------------------------------------------------------
loc_855E:
		LDA		#$10
		JSR		_fds_data_load
		LDA		#$07
		JSR		_fds_data_load
loc_8568:
		JSR		_bios_fonts_load
		LDA		#$1C
		JSR		_tlm_lib_load
		INC		_main_sub_idx
		LDA		#$00
		STA		_sub_sub_idx
		RTS

; =============== S U B	R O U T	I N E =======================================
_main08_stage_complete_anim:
		LDA		_sub_sub_idx
		LDX		_1p_stage
		BEQ		sub_8584
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD _stage_complete_anim00
		.WORD _stage_complete_anim01A

; =============== S U B	R O U T	I N E =======================================
sub_8584:
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD _stage_complete_anim00
		.WORD _stage_complete_anim01B

; =============== S U B	R O U T	I N E =======================================
_stage_complete_anim00:
		LDA		_1p_stage
		CMP		#$05
		BNE		loc_8597
		JSR		_final_stage_complete_draw
		JMP		loc_859A
; ---------------------------------------------------------------------------
loc_8597:
		JSR		_regular_stage_complete_draw
loc_859A:
		LDA		_1p_stage
		CMP		#$05
		BCS		loc_85A7
		TAX
		LDA		_stage_complete_apu_list,X
		JSR		_apu_load_safe
loc_85A7:
		LDX		_1p_stage
		LDA		byte_868D,X
		STA		byte_5A
		INC		_sub_sub_idx
		INC		_2p_stage
		INC		_1p_stage
		LDA		_1p_stage
		CMP		#$06
		BCC		loc_8629
		LDA		#$00
		STA		_1p_stage
		LDA		#$1A
		STA		_nmi_counter
		LDA		#$60
		STA		byte_6C4
		LDA		#$50
		STA		byte_55F
		LDA		#$80
		STA		byte_54F
		LDA		#$03
		STA		byte_54E
		LDA		#$80
		STA		byte_543
		LDA		#$70
		STA		byte_545
		LDA		#$70
		STA		byte_580+$1E
		LDA		#$10
		STA		byte_580+$1F
		LDA		_1p_lives
		BEQ		loc_8611
		LDX		#$00
loc_85F0:
		LDA		#$01
		STA		byte_500,X
		LDA		#$78
		STA		byte_500+5,X
		LDA		#$00
		STA		byte_500+$F,X
		CPX		#$00
		BNE		loc_8620
		LDA		#$90
		STA		byte_500+3,X
		LDA		#$00
loc_860A:
		STA		byte_500+$E,X
		CPX		#$20
		BEQ		loc_861D
loc_8611:
		LDA		_players_num
		BEQ		loc_861D
		LDA		_2p_lives
		BEQ		loc_861D
		LDX		#$20
		BNE		loc_85F0
loc_861D:
		JMP		_type_msg_stage_fetch
; ---------------------------------------------------------------------------
loc_8620:
		LDA		#$50
		STA		byte_500+3,X
		LDA		#$01
		BNE		loc_860A
loc_8629:
		LDA		#$01
		STA		byte_540
		LDA		#$30
		STA		byte_543
		LDA		#$2C
		STA		byte_545
		LDA		#$87
		STA		byte_54F
		LDA		#$02
		STA		byte_54E
		LDX		#$00
		LDA		_1p_lives
		BNE		loc_864A
		LDX		#$20
loc_864A:
		LDA		#$01
		STA		byte_500,X
		LDA		#$B4
		STA		byte_500+5,X
		LDA		#$30
		CPX		#$20
		BEQ		loc_865C
		LDA		#$00
loc_865C:
		STA		byte_500+3,X
		LDA		#$01
		STA		byte_500+$F,X
		LDA		#$00
		CPX		#$00
		BEQ		loc_866C
		LDA		#$01
loc_866C:
		STA		byte_500+$E,X
		CPX		#$20
		BCS		_type_msg_stage_fetch
		LDA		_players_num
		BEQ		_type_msg_stage_fetch
		LDA		_2p_lives
		BEQ		_type_msg_stage_fetch
		LDX		#$20
		BNE		loc_864A

; =============== S U B	R O U T	I N E =======================================
_type_msg_stage_fetch:
		LDA		_1p_stage
		BNE		_type_msg_fetch_asl

; =============== S U B	R O U T	I N E =======================================
_type_msg_ending_fetch:
		LDA		#$0C
		BNE		_type_msg_fetch_ex

; =============== S U B	R O U T	I N E =======================================
_type_msg_fetch_asl:
		ASL

; =============== S U B	R O U T	I N E =======================================
_type_msg_fetch_ex:
		TAY
		JSR		_type_msg_ptr_fetch
		RTS
; ---------------------------------------------------------------------------
byte_868D:
		.BYTE $84,$78,$A2,$80,$A8,$B0
_stage_complete_apu_list:
		.BYTE $55,$58,$5B,$5E,$61

; =============== S U B	R O U T	I N E =======================================
_stage_complete_anim01A:
		JSR		_type_msg_handler
		LDA		_frames_counter
		AND		#$07
		BNE		loc_86B0
		INC		byte_54F
		LDA		byte_54F
		CMP		#$8A
		BCC		loc_86B0
		LDA		#$87
		STA		byte_54F
loc_86B0:
		LDX		#$00

; =============== S U B	R O U T	I N E =======================================
sub_86B2:
		LDA		byte_500,X
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD sub_8718
		.WORD sub_86C6
		.WORD sub_8703
		.WORD sub_874E
		.WORD sub_8782
		.WORD sub_87A1
		.WORD sub_87AE

; =============== S U B	R O U T	I N E =======================================
sub_86C6:
		LDA		#$A0
		CLC
		ADC		byte_500+8,X
		STA		byte_500+8,X
		BCC		loc_86D4
		INC		byte_500+3,X
loc_86D4:
		LDA		byte_500+3,X
		CMP		#$B4
		BCC		loc_86E6
		LDA		#$63
		STA		byte_500+$F,X
		INC		byte_500,X
		JMP		sub_8718
; ---------------------------------------------------------------------------
loc_86E6:
		LDA		#$24
		CLC
		ADC		byte_500+$18,X
		STA		byte_500+$18,X
		BCC		sub_8718
		INC		byte_500+$F,X
		LDA		byte_500+$F,X
		CMP		#$05
		BCC		sub_8718
		LDA		#$01
		STA		byte_500+$F,X
		JMP		sub_8718

; =============== S U B	R O U T	I N E =======================================
sub_8703:
		DEC		byte_500+5,X
		INC		byte_500+3,X
		LDA		byte_500+3,X
		CMP		#$C4
		BCC		sub_8718
		INC		byte_500,X
		LDA		#$64
		STA		byte_500+$F,X

; =============== S U B	R O U T	I N E =======================================
sub_8718:
		LDA		byte_500+3,X
		CMP		#$FF
		BNE		loc_8724
		LDA		#$00
		STA		byte_500,X
loc_8724:
		CPX		#$20
		BCS		loc_8730
		TXA
		CLC
		ADC		#$20
		TAX
		JMP		sub_86B2
; ---------------------------------------------------------------------------
loc_8730:
		LDA		_frames_counter
		AND		#$03
		BNE		locret_874D
		JSR		sub_A367
		BNE		locret_874D
loc_873B:
		LDA		#$7D
		JSR		_apu_load_safe
		JSR		_fds_load_bufs_clear
		LDA		#$00
		STA		_sub_sub_idx
		STA		_game_main_sub_idx
		LDA		#$05
		STA		_main_sub_idx
locret_874D:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_874E:
		LDA		_frames_counter
		AND		#$07
		BNE		loc_8763
		INC		byte_500+$F,X
		LDA		byte_500+$F,X
		CMP		#$66
		BCC		loc_8763
		LDA		#$64
		STA		byte_500+$F,X
loc_8763:
		DEC		byte_500+5,X
		LDA		byte_500+5,X
		CMP		#$62
		BCS		sub_8718
		LDA		#$63
		STA		byte_500+$F,X
		LDA		#$58
		STA		byte_500+5,X
		LDA		#$0A
		STA		byte_500+$1F,X
		INC		byte_500,X
		JMP		sub_8718

; =============== S U B	R O U T	I N E =======================================
sub_8782:
		DEC		byte_500+$1F,X
		BNE		sub_8718
		LDA		#$66
		STA		byte_500+$F,X
		LDA		#$18
		STA		byte_500+$1F,X
		LDA		#$FE
		STA		byte_500+9,X
		LDA		#$20
		STA		byte_500+$A,X
		INC		byte_500,X
		JMP		sub_8718

; =============== S U B	R O U T	I N E =======================================
sub_87A1:
		DEC		byte_500+$1F,X
		BNE		sub_87AE
		LDA		#$63
		STA		byte_500+$F,X
		INC		byte_500,X

; =============== S U B	R O U T	I N E =======================================
sub_87AE:
		LDA		#$B0
		CLC
		ADC		byte_500+8,X
		STA		byte_500+8,X
		BCC		loc_87BC
		INC		byte_500+3,X
loc_87BC:
		LDA		byte_500+5,X
		CMP		#$B4
		BCS		loc_87E6
		LDA		byte_500+$A,X
		CLC
		ADC		byte_500+6,X
		STA		byte_500+6,X
		LDA		byte_500+9,X
		ADC		byte_500+5,X
		STA		byte_500+5,X
		LDA		#$12
		ADC		byte_500+$A,X
		STA		byte_500+$A,X
		LDA		byte_500+9,X
		ADC		#$00
		STA		byte_500+9,X
loc_87E6:
		JMP		sub_8718

; =============== S U B	R O U T	I N E =======================================
_stage_complete_anim01B:
		LDA		byte_55F
		BEQ		loc_8830
		LDA		_frames_counter
		AND		#$01
		BEQ		loc_87F7
		JMP		loc_88A6
; ---------------------------------------------------------------------------
loc_87F7:
		LDA		byte_55F
		CMP		#$06
		BCS		loc_880F
		CMP		#$03
		BCC		loc_880A
		LDA		#$25
		JSR		_tlm_lib_load
		JMP		loc_880F
; ---------------------------------------------------------------------------
loc_880A:
		LDA		#$1C
		JSR		_tlm_lib_load
loc_880F:
		DEC		byte_55F
		BEQ		loc_8817
		JMP		loc_88A6
; ---------------------------------------------------------------------------
loc_8817:
		LDA		#$01
		STA		byte_540
		LDA		#$7D
		JSR		_apu_load_safe
		LDA		#$72
		JSR		_apu_load_safe
		LDA		#$00
		STA		byte_560+$1E
		LDA		#$30
		STA		byte_560+$1F
loc_8830:
		LDA		byte_560+$1F
		BEQ		loc_884D
		DEC		byte_560+$1F
		LDA		byte_FD
		BNE		loc_8844
		INC		byte_FD
		INC		byte_FD
		INC		byte_FD
		BNE		loc_888E
loc_8844:
		DEC		byte_FD
		DEC		byte_FD
		DEC		byte_FD
		JMP		loc_888E
; ---------------------------------------------------------------------------
loc_884D:
		LDA		byte_560+$1E
		BEQ		loc_885E
		CMP		#$08
		BEQ		loc_885E
		CMP		#$10
		BEQ		loc_885E
		CMP		#$18
		BNE		loc_887E
loc_885E:
		LDA		byte_580+$1E
		BEQ		loc_8869
		DEC		byte_580+$1E
		JMP		loc_888E
; ---------------------------------------------------------------------------
loc_8869:
		DEC		byte_580+$1F
		BNE		loc_888E
		LDA		byte_560+$1E
		CMP		#$10
		BCC		loc_8879
		LDA		#$4F
		BNE		loc_887B
loc_8879:
		LDA		#$2F
loc_887B:
		STA		byte_580+$1F
loc_887E:
		LDA		byte_560+$1E
		CMP		#$24
		BCS		loc_888E
		CLC
		ADC		#$26
		INC		byte_560+$1E
		JSR		_tlm_lib_load
loc_888E:
		LDA		_frames_counter
		AND		#$0F
		BNE		loc_88A6
		LDY		#$84
		LDA		byte_54F
		CMP		#$86
		BCC		loc_88A3
		TYA
		STA		byte_54F
		BNE		loc_88A6
loc_88A3:
		INC		byte_54F
loc_88A6:
		LDA		byte_6C4
		BEQ		loc_88CD
		LDA		_frames_counter
		AND		#$01
		BNE		locret_88C1
		DEC		byte_6C4
		BNE		locret_88C1
		LDA		#$74
		STA		byte_500+$F
		STA		byte_52F
		JMP		loc_891C
; ---------------------------------------------------------------------------
locret_88C1:
		RTS
; ---------------------------------------------------------------------------
loc_88C2:
		TYA
		STA		byte_500+$F,X
		CMP		#$7C
		BEQ		loc_891C
		JMP		loc_890B
; ---------------------------------------------------------------------------
loc_88CD:
		LDX		#$00
loc_88CF:
		LDA		_frames_counter
		AND		#$03
		BNE		loc_890B
		LDA		byte_500+5,X
		CMP		#$B8
		BEQ		loc_891C
		INC		byte_500+5,X
		LDY		#$75
		LDA		byte_500+5,X
		CMP		#$80
		BEQ		loc_88C2
		INY
		CMP		#$88
		BEQ		loc_88C2
		INY
		CMP		#$90
		BEQ		loc_88C2
		INY
		CMP		#$98
		BEQ		loc_88C2
		INY
		CMP		#$A0
		BEQ		loc_88C2
		INY
		CMP		#$A8
		BEQ		loc_88C2
		INY
		CMP		#$B0
		BEQ		loc_88C2
		INY
		CMP		#$B8
		BEQ		loc_88C2
loc_890B:
		LDA		_frames_counter
		AND		#$0F
		BNE		loc_891C
		LDA		byte_500+$B,X
		EOR		#$FF
		CLC
		ADC		#$02
		STA		byte_500+$B,X
loc_891C:
		TXA
		CLC
		ADC		#$20
		TAX
		CPX		#$40
		BCC		loc_88CF
		JSR		sub_A367
		BNE		locret_8936
		LDA		#$E8
		STA		byte_5A
		LDA		#$09
		STA		_main_sub_idx
		LDA		#$00
		STA		_sub_sub_idx
locret_8936:
		RTS

; =============== S U B	R O U T	I N E =======================================
_main09_ending:
		LDA		_sub_sub_idx
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD _ending00
		.WORD _ending01
		.WORD _ending02
		.WORD _ending03
		.WORD _ending04
		.WORD _ending05
		.WORD _ending06

; =============== S U B	R O U T	I N E =======================================
_ending02:
		LDA		#$15
		JSR		_file_lib_unpack
		JSR		_screen_clear
		JSR		_fds_load_bufs_clear
		LDA		#$4A
		JSR		_tlm_lib_load
		LDA		#$0E
		STA		byte_500+$11
		INC		_sub_sub_idx
		LDA		#$97
		STA		byte_5E0+$F
		LDA		#$96
		STA		byte_600+$F
		LDA		#$02
		STA		byte_5E0+$E
		STA		byte_600+$E
		LDA		#$50
		STA		byte_55D
		STA		byte_560+$1D
		STA		byte_580+$1D
		LDA		#$63
		STA		byte_580+$1E
		LDX		#$00
		LDA		#$B0
		STA		byte_545
		STA		byte_560+5
		STA		byte_580+5
		LDA		#$88
		STA		byte_5A0+5
		STA		byte_5C0+5
		LDA		#$D0
		STA		byte_543
		LDA		#$90
		STA		byte_560+3
		LDA		#$50
		STA		byte_580+3
		LDA		#$FF
		STA		byte_5A0+3
		STA		byte_5C0+3
		LDA		#$00
		STA		byte_5A0+$E
		LDA		#$01
		STA		byte_5C0+$E
		LDA		#$03
		STA		byte_54E
		STA		byte_560+$E
		STA		byte_580+$E
loc_89C4:
		LDA		#$1D
		CPX		#$60
		BCS		loc_89E4
		CPX		#$00
		BNE		loc_89D0
		LDA		#$21
loc_89D0:
		STA		byte_541,X
		JSR		sub_89FB
		CLC
		ADC		#$20
		TAX
		CPX		#$A0
		BCC		loc_89C4
		LDA		#$75
		JSR		_apu_load_safe
		RTS
; ---------------------------------------------------------------------------
loc_89E4:
		LDA		#$22
		BNE		loc_89D0

; =============== S U B	R O U T	I N E =======================================
_ending03:
		LDA		#$1D
		JSR		_tlm_lib_load
		LDY		byte_500+$11
		JSR		_type_msg_ptr_fetch
		LDA		#$F0
		STA		byte_500+$10

; =============== S U B	R O U T	I N E =======================================
sub_89F8:
		INC		_sub_sub_idx
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_89FB:
		TXA
		PHA
		TAY
		JSR		sub_C2CA
		PLA
		TAX
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_8A04:
		JSR		_type_msg_handler
		LDA		_frames_counter
		AND		#$01
		BEQ		nullsub_10
		DEC		byte_500+$10
		BNE		nullsub_10
		LDA		#$03
		STA		_sub_sub_idx
		LDA		byte_500+$11
		CMP		#$24
		BCC		loc_8A31
		LDA		#$1E
		JSR		_tlm_lib_load
		LDA		#$1F
		JSR		_tlm_lib_load
		LDA		#$21
		JSR		_tlm_lib_load
		LDA		#$05
		STA		_sub_sub_idx
		RTS
; ---------------------------------------------------------------------------
loc_8A31:
		CLC
		ADC		#$02
		STA		byte_500+$11
		LDA		#$1E
		JSR		_tlm_lib_load
		LDA		#$1F
		JSR		_tlm_lib_load

; =============== S U B	R O U T	I N E =======================================
nullsub_10:
		RTS

; =============== S U B	R O U T	I N E =======================================
_ending05:
		JSR		sub_8A78
		BEQ		loc_8A4A
		JMP		sub_8A5D
; ---------------------------------------------------------------------------
loc_8A4A:
		LDA		_frames_counter
		AND		#$1F
		BNE		nullsub_10
		LDA		#$1F
		JSR		_tlm_lib_load
		JMP		sub_89F8

; =============== S U B	R O U T	I N E =======================================
_ending06:
		JSR		sub_8A78
		BEQ		sub_8A68

; =============== S U B	R O U T	I N E =======================================
sub_8A5D:
		JSR		_screen_clear
		LDA		#$0F
		JSR		_fds_data_load
		JMP		loc_873B

; =============== S U B	R O U T	I N E =======================================
sub_8A68:
		LDA		_frames_counter
		AND		#$1F
		BNE		nullsub_10
		LDA		#$20
		JSR		_tlm_lib_load
		LDA		#$05
		STA		_sub_sub_idx
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_8A78:
		LDA		_pads_held
		AND		#$10
		RTS

; =============== S U B	R O U T	I N E =======================================
_next_sub_sub_delay80_unref:
		LDA		#$80

; =============== S U B	R O U T	I N E =======================================
_next_sub_sub_delay_ex:
		STA		_delay_counter

; =============== S U B	R O U T	I N E =======================================
_next_sub_sub:
		INC		_sub_sub_idx
		RTS

; =============== S U B	R O U T	I N E =======================================
_next_main_sub_delay80:
		LDA		#$80
		STA		_delay_counter

; =============== S U B	R O U T	I N E =======================================
_next_main_sub:
		INC		_main_sub_idx

; =============== S U B	R O U T	I N E =======================================
_sub_sub_reset:
		LDA		#$00
		STA		byte_23
		STA		_sub_sub_idx
		RTS

; =============== S U B	R O U T	I N E =======================================
_set_main_sub_delay50:
		STA		_main_sub_idx
		LDA		#$50
		STA		_delay_counter
		BNE		_sub_sub_reset

; =============== S U B	R O U T	I N E =======================================
_do_delay_counters:
		LDA		_delay_counter
		ORA		_delay_counter+1
		BEQ		locret_8AAB
		DEC		_delay_counter
		BNE		locret_8AAB
		LDA		_delay_counter+1
		BEQ		loc_8AA9
		DEC		_delay_counter+1
loc_8AA9:
		LDA		#$01
locret_8AAB:
		RTS

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
_type_msg00_your_mission_is:
		.WORD $A520
		.BYTE $23,$19,$1F,$1C,$00,$17,$13,$1D,$1D,$13,$19,$18
		.BYTE $41
		.BYTE $20,$C8,$0E,$0F,$1D,$1E,$1C,$19,$23,$00,$0F,$18,$0F,$17,$23
		.BYTE $41
		.BYTE $20,$E7,$1D,$0F,$0D,$1C,$0F,$1E,$00,$21,$0F,$0B,$1A,$19,$18,$26
		.BYTE $41
		.BYTE $21,$EA,$11,$19,$19,$0E,$00,$16,$1F,$0D,$15,$26
		.BYTE $40

; =============== S U B	R O U T	I N E =======================================
_j_BIOS_get_inputA:
		JMP		_BIOS_get_inputA

; =============== S U B	R O U T	I N E =======================================
_title_intro_input_handler:
		LDA		_pads_press
		AND		#$30
		BEQ		locret_8BE2
		JSR		sub_8BE8
		LDX		_main_sub_idx
		CPX		#$01
		BNE		loc_8BE3
		AND		#$20
		BNE		loc_8BD7
		LDA		#$03
		JMP		_set_main_sub_delay50
; ---------------------------------------------------------------------------
loc_8BD7:
		INC		_players_num
		LDA		#$02
		SEC
		SBC		_players_num
		BNE		locret_8BE2
		STA		_players_num
locret_8BE2:
		RTS
; ---------------------------------------------------------------------------
loc_8BE3:
		LDX		#$00
		STX		_main_sub_idx
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_8BE8:
		LDX		#$00
		STX		_delay_counter
		INX
		STX		_delay_counter+1
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_8BF0:
		LDA		byte_21
		PHA
		JSR		_ram_init
		PLA
		STA		byte_21
		INC		_1p_lives
		RTS

; =============== S U B	R O U T	I N E =======================================
_game_init:
		JSR		_ram_init

; =============== S U B	R O U T	I N E =======================================
_game_init_ex:
		LDX		#$04
		LDA		#$00
loc_8C03:
		STA		_1p_score,X
		STA		_2p_scores,X
		DEX
		BPL		loc_8C03
		STA		byte_20
		LDY		_players_num
		LDA		byte_8C62,Y
		STA		byte_21
		LDA		#$03
		STA		_1p_lives
		LDY		_players_num
		BEQ		loc_8C21
		LDA		#$03
		STA		_2p_lives
loc_8C21:
		LDA		#$01
		STA		byte_3D
		STA		byte_3E
		LDA		_pads_held+1
		CMP		#$C4
		BNE		locret_8C61
		LDX		#$01
		LDA		_pads_held
		BPL		loc_8C3B
		AND		#$CF
		CMP		#$80
		BEQ		loc_8C57
		BNE		locret_8C61
loc_8C3B:
		AND		#$0F
		CMP		#$04
		BEQ		loc_8C50
		INX
		CMP		#$02
		BEQ		loc_8C50
		INX
		CMP		#$08
		BEQ		loc_8C50
		INX
		CMP		#$01
		BNE		locret_8C61
loc_8C50:
		STX		_1p_stage
		STX		_2p_stage
		JMP		locret_8C61
; ---------------------------------------------------------------------------
loc_8C57:
		LDA		#$0A
		STA		_1p_lives
		LDX		_players_num
		BEQ		locret_8C61
		STA		_2p_lives
locret_8C61:
		RTS
; ---------------------------------------------------------------------------
byte_8C62:
		.BYTE $01,$07

; =============== S U B	R O U T	I N E =======================================
_ram_init:
		LDX		#$12
		JSR		_nmi_off_render_off
loc_8C69:
		CPX		#$17
		BEQ		loc_8C6F
		STA		_main_sub_idx,X
loc_8C6F:
		INX
		CPX		#$D9
		BNE		loc_8C69
		LDA		#<[byte_300]
		LDX		#$07
		LDY		#>[byte_300]
		STY		word_0+1
		STA		word_0
		LDY		#$00
loc_8C80:
		STA		(word_0),Y
		INY
		BNE		loc_8C80
		INC		word_0+1
		CPX		word_0+1
		BNE		loc_8C80
		JMP		_render_on_nmi_on

; =============== S U B	R O U T	I N E =======================================
_switch:
		ASL
		STX		byte_3
		STY		byte_2
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
		LDY		byte_2
		LDX		byte_3
		JMP		(word_0)

; =============== S U B	R O U T	I N E =======================================
_fds_load_bufs_clear:
		LDA		#$00
		LDX		#$00
loc_8CB0:
		STA		byte_500,X
		INX
		BNE		loc_8CB0
loc_8CB6:
		STA		byte_600,X
		INX
		BNE		loc_8CB6
		RTS

; =============== S U B	R O U T	I N E =======================================
_unref:
		LDY		#$FF
		BNE		loc_8CCD
		LDA		#$20
		LDY		#$77
		BNE		loc_8CCB
		LDA		#$30
		LDY		#$67
loc_8CCB:
		LDX		#$00
loc_8CCD:
		STA		word_0
		STX		word_0+1
		LDA		#$00
loc_8CD3:
		STA		(word_0),Y
		DEY
		CPY		#$FF
		BNE		loc_8CD3
		RTS

; =============== S U B	R O U T	I N E =======================================
_unref_0:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_8CDC:
		LDX		#$01
		BNE		sub_8CE2

; =============== S U B	R O U T	I N E =======================================
sub_8CE0:
		LDX		#$00

; =============== S U B	R O U T	I N E =======================================
sub_8CE2:
		TXA
		AND		#$01
		STA		byte_8
		LDA		#$00
		STA		byte_3
		LDA		byte_20
		BEQ		loc_8CF0
		RTS
; ---------------------------------------------------------------------------
loc_8CF0:
		LDA		#<[_1p_score]
		LDY		byte_8
		BEQ		loc_8CF8
		LDA		#<[_2p_scores]
loc_8CF8:
		STA		word_4
		LDY		#>[_1p_score]
		STY		word_4+1
		LDX		#$01
		LDY		#$00
		LDA		#$03
		STA		word_0
		CLC
loc_8D07:
		LDA		(word_4),Y
		JSR		sub_8D25
		STA		(word_4),Y
		INY
		INX
		DEC		word_0
		BNE		loc_8D07
		BCC		sub_8D4F
		LDX		#$02
		LDA		#$99
loc_8D1A:
		STA		_hi_scores,X
		DEX
		BPL		loc_8D1A
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_8D21:
		STX		word_0
		LDX		#$00

; =============== S U B	R O U T	I N E =======================================
sub_8D25:
		STA		byte_7
		AND		#$F0
		STA		byte_6
		EOR		byte_7
		STA		byte_7
		LDA		word_0,X
		AND		#$0F
		ADC		byte_7
		CMP		#$0A
		BCC		loc_8D3B
		ADC		#$05
loc_8D3B:
		ADC		byte_6
		STA		byte_6
		LDA		word_0,X
		AND		#$F0
		ADC		byte_6
		BCS		loc_8D4B
		CMP		#$A0
		BCC		locret_8D4E
loc_8D4B:
		SBC		#$A0
		SEC
locret_8D4E:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_8D4F:
		LDY		#$02
		LDA		(word_4),Y
		LDX		byte_8
		CMP		byte_3D,X
		BCC		loc_8D73
		LDX		#$01
		LDY		byte_8
		LDA		byte_3D,Y
		CLC
		JSR		sub_8D21
		BCC		loc_8D68
		LDA		#$FF
loc_8D68:
		LDX		byte_8
		STA		byte_3D,X
		INC		_1p_lives,X
		LDA		#$1C
		JSR		_apu_load_safe
loc_8D73:
		LDY		#$02
loc_8D75:
		LDA		_hi_scores,Y
		CMP		(word_4),Y
		BCC		loc_8D81
		BNE		locret_8D8B
		DEY
		BPL		loc_8D75
loc_8D81:
		LDY		#$02
loc_8D83:
		LDA		(word_4),Y
		STA		_hi_scores,Y
		DEY
		BPL		loc_8D83
locret_8D8B:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_8D8C:
		CPY		#$00
		BNE		loc_8D9B
		LDA		byte_66
		STA		byte_500+$1C
		LDA		byte_67
		STA		byte_500+$1D
		RTS
; ---------------------------------------------------------------------------
loc_8D9B:
		LDA		byte_68
		STA		byte_53C
		LDA		byte_69
		STA		byte_53D
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_8DA6:
		CPY		#$00
		BNE		loc_8DB5
		LDA		byte_500+$1C
		STA		byte_66
		LDA		byte_500+$1D
		STA		byte_67
		RTS
; ---------------------------------------------------------------------------
loc_8DB5:
		LDA		byte_53C
		STA		byte_68
		LDA		byte_53D

; =============== S U B	R O U T	I N E =======================================
sub_8DBD:
		STA		byte_69
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_8DC0:
		LDA		#$00
		STA		byte_66
		STA		byte_67
		STA		byte_68
		BEQ		sub_8DBD

; =============== S U B	R O U T	I N E =======================================
_demo_input_fetch:
		LDA		_pads_press
		AND		#$30
		BNE		loc_8E05
		LDY		byte_30
		BEQ		loc_8DE8
		LDY		byte_31
		DEY
		DEY
		LDA		_demo_input_data,Y
		STA		_pads_held
		LDA		#$00
		STA		_pads_press
		STA		_pads_press+1
		STA		_pads_held+1
		DEC		byte_30
		RTS
; ---------------------------------------------------------------------------
loc_8DE8:
		LDY		byte_31
		LDA		_demo_input_data,Y
		CMP		#$FF
		BEQ		loc_8E05
		STA		_pads_press
		STA		_pads_held
		LDA		#$00
		STA		_pads_press+1
		STA		_pads_held+1
		INY
		LDA		_demo_input_data,Y
		STA		byte_30
		INY
		STY		byte_31
		RTS
; ---------------------------------------------------------------------------
loc_8E05:
		INC		byte_23
		LDA		#$7D
		JSR		_apu_load_safe
		RTS
; ---------------------------------------------------------------------------
_demo_input_data:
		.BYTE $01,$80,$41,$0D,$01,$17,$41,$0C,$01,$4C,$09,$16,$08,$19,$00,$0E
		.BYTE $01,$1C,$00,$07,$08,$2B,$00,$18,$01,$06,$41,$09,$01,$AF,$41,$0E
		.BYTE $01,$6F,$00,$05,$08,$26,$00,$0C,$01,$02,$00,$0F,$04,$31,$00,$0A
		.BYTE $02,$12,$00,$53,$40,$0E,$00,$0C,$01,$12,$00,$09,$08,$24,$00,$08
		.BYTE $01,$CD,$00,$06,$02,$41,$00,$03,$04,$37,$00,$0C,$01,$2C,$41,$0C
		.BYTE $01,$8C,$41,$0B,$01,$74,$05,$02,$04,$0D,$84,$0A,$04,$02,$01,$68
		.BYTE $01,$F8,$41,$09,$01,$E6,$41,$0C,$01,$A7,$00,$02,$08,$27,$00,$0A
		.BYTE $01,$11,$05,$07,$45,$0D,$05,$07,$01,$09,$00,$06,$40,$0A,$00,$1D
		.BYTE $02,$1E,$00,$03,$04,$2B,$00,$11,$01,$09,$41,$04,$01,$2D,$01,$F0
		.BYTE $02,$F0,$01,$F0,$01,$F0,$01,$F0,$FF,$FF

; =============== S U B	R O U T	I N E =======================================
sub_8EA7:
		SEC
		LDA		_game_vat49
		SBC		_game_vat4B
		BEQ		sub_8EEB
		LDX		_game_vat49
		STX		_game_vat4B
		LDX		byte_48
		STX		byte_4A
		CLC
		ADC		byte_FD
		STA		byte_FD
		BCC		sub_8EEB
		LDA		_ppu_ctrl_shadow
		EOR		#$01
		STA		_ppu_ctrl_shadow
		JMP		sub_8EEB
; ---------------------------------------------------------------------------
locret_8EC6:
		RTS
; ---------------------------------------------------------------------------
loc_8EC7:
		JMP		loc_902F
; ---------------------------------------------------------------------------
loc_8ECA:
		LDA		_substage_rooms_lib,Y
		STA		byte_E
		LDA		_substage_rooms_lib+1,Y
		STA		byte_F
		LDA		_substage_macro_lib,Y
		STA		byte_14
		LDA		_substage_macro_lib+1,Y
		STA		byte_15
		LDA		_substage_attr_lib,Y
		STA		byte_16
		LDA		_substage_attr_lib+1,Y
		STA		byte_17
		JMP		sub_8F46

; =============== S U B	R O U T	I N E =======================================
sub_8EEB:
		LDA		_game_vat57
		BNE		loc_8EC7
		STA		byte_11
		LDA		_game_vat50
		BNE		loc_8F1B
		LDA		_game_vat55
		BNE		loc_8F17
		LDA		_game_vat49
		SEC
		SBC		_game_vat4D
		CMP		#$20
		BCC		locret_8EC6
		LDA		byte_58
		CLC
		ADC		#$18
		CMP		#$F0
		BCC		loc_8F0D
		LDA		#$00
loc_8F0D:
		STA		byte_58
		LDA		_game_vat49
		STA		_game_vat4D
		LDA		byte_48
		STA		byte_4C
loc_8F17:
		LDA		#$06
		STA		_game_vat50
loc_8F1B:
		LDA		#$01
		STA		byte_5B
		LDA		_1p_stage
		ASL
		TAY
		LDA		byte_465
		BNE		loc_8ECA
		LDA		_stage_rooms_lib,Y
		STA		byte_E
		LDA		_stage_rooms_lib+1,Y
		STA		byte_F
		LDA		_stage_macro_lib,Y
		STA		byte_14
		LDA		_stage_macro_lib+1,Y
		STA		byte_15
		LDA		_stage_attr_lib,Y
		STA		byte_16
		LDA		_stage_attr_lib+1,Y
		STA		byte_17

; =============== S U B	R O U T	I N E =======================================
sub_8F46:
		LDA		#$00
		STA		byte_8
		LDA		#$04
		STA		byte_9
		STA		byte_A
		LDA		byte_4E
		ASL
		TAY
		LDA		(byte_E),Y
		STA		byte_2
		INY
		LDA		(byte_E),Y
		STA		byte_3
		LDY		byte_4F
		LDA		(byte_2),Y
		STA		word_4
		LDX		#$04
		LDY		#$00
		STY		word_0
loc_8F69:
		ASL
		ROL		word_0
		DEX
		BNE		loc_8F69
		CLC
		ADC		byte_14
		STA		byte_14
		LDA		word_0
		ADC		byte_15
		STA		byte_15
loc_8F7A:
		LDA		byte_51
		STA		_PPU_ADDR
		LDA		byte_52
		STA		_PPU_ADDR
		LDY		byte_8
loc_8F86:
		LDA		(byte_14),Y
		STA		_PPU_DATA
		LDX		byte_11
		STA		byte_440,X
		LDA		#$01
		STA		_game_vat57
		INX
		STX		byte_11
		INY
		DEC		byte_9
		BNE		loc_8F86
		LDA		byte_8
		CLC
		ADC		#$04
		STA		byte_8
		DEC		byte_A
		BEQ		loc_8FB9
		LDA		#$04
		STA		byte_9
		LDA		byte_52
		CLC
		ADC		#$20
		STA		byte_52
		BCC		loc_8F7A
		INC		byte_51
		JMP		loc_8F7A
; ---------------------------------------------------------------------------
loc_8FB9:
		LDA		byte_53
		STA		_PPU_ADDR
		LDA		byte_54
		STA		_PPU_ADDR
		LDY		word_4
		LDA		(byte_16),Y
		STA		_PPU_DATA
		INC		byte_4F
		BNE		loc_8FD0
		INC		byte_4E
loc_8FD0:
		DEC		_game_vat50
		BNE		loc_8FF2
		LDA		byte_51
		AND		#$03
		CMP		#$03
		BEQ		loc_9007
loc_8FDC:
		LDA		byte_54
		SEC
		SBC		#$27
		STA		byte_54
		LDA		byte_51
		SEC
		SBC		#$03
		STA		byte_51
		LDA		byte_52
		CLC
		ADC		#$24
		STA		byte_52
locret_8FF1:
		RTS
; ---------------------------------------------------------------------------
loc_8FF2:
		LDA		byte_54
		CLC
		ADC		#$08
		STA		byte_54
		LDA		byte_52
		CLC
		ADC		#$20
		STA		byte_52
		BCC		locret_8FF1
		INC		byte_51
		JMP		locret_8FF1
; ---------------------------------------------------------------------------
loc_9007:
		LDA		byte_52
		CMP		#$7C
		BNE		loc_8FDC
		LDA		byte_51
		CMP		#$23
		BEQ		loc_901D
		LDA		#$20
		STA		byte_51
		LDA		#$23
		STA		byte_53
		BNE		loc_9025
loc_901D:
		LDA		#$24
		STA		byte_51
		LDA		#$27
		STA		byte_53
loc_9025:
		LDA		#$80
		STA		byte_52
		LDA		#$C8
		STA		byte_54
		BNE		locret_8FF1
loc_902F:
		LDA		#$01
		STA		byte_5B
		LDA		#$12
		LDY		byte_465
		BNE		loc_903F
		LDY		_1p_stage
		LDA		byte_90CA,Y
loc_903F:
		STA		byte_A
		LDA		#$04
		STA		byte_12
		LDX		#$00
		STX		_game_vat57
		STX		byte_16
		LDY		byte_56
		STX		byte_8
		STY		byte_9
loc_9051:
		JSR		sub_9091
		CLC
		ROL
		ROL
		STA		byte_C
		INC		byte_8
		JSR		sub_9091
		ORA		byte_C
		STA		byte_C
		INC		byte_8
		JSR		sub_9091
		LSR
		LSR
		ORA		byte_C
		STA		byte_C
		INC		byte_8
		JSR		sub_9091
		LSR
		LSR
		LSR
		LSR
		ORA		byte_C
		LDY		byte_9
		STA		byte_350,Y
		INC		byte_8
		LDX		byte_8
		INY
		STY		byte_9
		CPX		#$10
		BCC		loc_9051
		CPY		#$F0
		BCC		loc_908E
		LDY		#$00
loc_908E:
		STY		byte_56
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_9091:
		LDX		byte_16
		LDA		byte_440,X
		LDY		byte_A
		LDX		#$00
		CMP		byte_90B5,Y
		BCC		loc_90B1
		INY
		LDX		#$20
		CMP		byte_90B5,Y
		BCS		loc_90B1
		INY
		LDX		#$10
		CMP		byte_90B5,Y
		BCC		loc_90B1
		LDX		#$30
loc_90B1:
		INC		byte_16
		TXA
		RTS
; ---------------------------------------------------------------------------
byte_90B5:
		.BYTE $DF,$F0,$EB
		.BYTE $F5,$FD,$FB
		.BYTE $CE,$DF,$DB
		.BYTE $DA,$E9,$E4
		.BYTE $E3,$F7,$F2
		.BYTE $F9,$FD,$FB
		.BYTE $1C,$20,$1E
byte_90CA:
		.BYTE $00,$03,$06,$09,$0C,$0F,$12
_stage_rooms_lib:
		.WORD _stage1_rooms
		.WORD _stage2_rooms
		.WORD _stage3_rooms
		.WORD _stage4_rooms
		.WORD _stage5_rooms
		.WORD _stage6_rooms
_stage_macro_lib:
		.WORD _stage1_macro
		.WORD _stage2_macro
		.WORD _stage3_macro
		.WORD _stage4_macro
		.WORD _stage5_macro
		.WORD _stage6_macro
_stage_attr_lib:
		.WORD _stage1_attr
		.WORD _stage2_attr
		.WORD _stage3_attr
		.WORD _stage4_attr
		.WORD _stage5_attr
		.WORD _stage6_attr
_substage_rooms_lib:
		.WORD $7035
		.WORD _substage2_rooms
		.WORD $7035
		.WORD _substage4_rooms
off_90FD:
		.WORD _substage5_rooms
		.WORD $7035
_substage_macro_lib:
		.WORD _substages_macro
		.WORD _substages_macro
		.WORD _substages_macro
		.WORD _substages_macro
		.WORD _substages_macro
		.WORD _substages_macro
_substage_attr_lib:
		.WORD _substages_attr
		.WORD _substages_attr
		.WORD _substages_attr
		.WORD _substages_attr
		.WORD _substages_attr
		.WORD _substages_attr

; =============== S U B	R O U T	I N E =======================================
sub_9119:
		LDX		#$06
		LDA		byte_465
		BNE		loc_9122
		LDX		_1p_stage
loc_9122:
		LDA		byte_9194,X
		STA		byte_11
		LDA		byte_91A2,X
		STA		byte_12
		TXA
		CLC
		ADC		#$07
		TAX
		LDA		byte_9194,X
		STA		byte_10
		LDA		#$00
		STA		_PPU_MASK
		LDY		#$80
		LDA		#$20
		LDX		#$80
loc_9141:
		STA		_PPU_ADDR
		STX		_PPU_ADDR
		LDA		byte_10
		CPY		#$41
		BCC		loc_914F
		LDA		byte_11
loc_914F:
		STA		_PPU_DATA
		DEY
		BEQ		loc_9175
		CPY		#$60
		BEQ		loc_9169
		CPY		#$40
		BEQ		loc_9163
		CPY		#$20
		BEQ		loc_916F
		BNE		loc_914F
loc_9163:
		LDA		#$20
		LDX		#$A0
		BNE		loc_9141
loc_9169:
		LDA		#$24
		LDX		#$80
		BNE		loc_9141
loc_916F:
		LDA		#$24
		LDX		#$A0
		BNE		loc_9141
loc_9175:
		LDY		#$10
		LDA		#$23
		LDX		#$C8
loc_917B:
		STA		_PPU_ADDR
		STX		_PPU_ADDR
		LDA		byte_12
loc_9183:
		STA		_PPU_DATA
		DEY
		BEQ		locret_9193
		CPY		#$08
		BNE		loc_9183
		LDA		#$27
		LDX		#$C8
		BNE		loc_917B
locret_9193:
		RTS
; ---------------------------------------------------------------------------
byte_9194:
		.BYTE $C2,$2B,$3C,$C5,$DA,$66,$11
		.BYTE $C2,$2B,$3C,$C5,$DA,$46,$12
byte_91A2:
		.BYTE $00,$FF,$55,$00,$00,$55,$A0

; =============== S U B	R O U T	I N E =======================================
_title_screen_draw:
		LDA		#$7D
		JSR		_apu_load_safe
		JSR		_nmi_off_render_off
		JSR		_fds_load_bufs_clear
		JSR		_game_vars_init
		LDA		#$1E
		STA		_ppu_mask_shadow
		JSR		_nmi_off_render_off
		LDA		#$13
		STA		_nmi_counter
		LDX		#$02
		JSR		_screen_lib_load
		LDA		#$00
		STA		_ppu_queue_pos
		LDA		#$06
		JSR		_tlm_lib_load
		JSR		_nmi_off_render_off
		LDA		#$03
		STA		byte_8
loc_91D7:
		LDA		byte_8
		CLC
		ADC		#$01
		JSR		_tlm_lib_load
		DEC		byte_8
		BPL		loc_91D7

; =============== S U B	R O U T	I N E =======================================
_ppu_ctrl_reload:
		LDA		_ppu_ctrl_shadow
		STA		_PPU_CTRL
		RTS

; =============== S U B	R O U T	I N E =======================================
_regular_stage_complete_draw:
		LDA		#$7D
		JSR		_apu_load_safe
		JSR		_nmi_off_render_off
		JSR		_game_vars_init
		LDX		#$04
		JSR		_screen_lib_load
		LDA		#$13
		JSR		_tlm_lib_load
		JMP		_ppu_ctrl_reload

; =============== S U B	R O U T	I N E =======================================
_intro_curscene_screen_draw:
		LDA		#$7D
		JSR		_apu_load_safe
		JSR		_nmi_off_render_off
		JSR		_game_vars_init
		LDX		#$06
		JSR		_screen_lib_load
		LDA		#$18
		JSR		_tlm_lib_load
		JMP		_ppu_ctrl_reload

; =============== S U B	R O U T	I N E =======================================
_final_stage_complete_draw:
		LDA		#$7D
		JSR		_apu_load_safe
		LDA		#$00
		STA		_PPU_CTRL
		STA		_PPU_MASK
		JSR		_game_vars_init
		LDX		#$08
		JSR		_screen_lib_load
		JMP		_ppu_ctrl_reload

; =============== S U B	R O U T	I N E =======================================
_screen_clear:
		LDX		#$00

; =============== S U B	R O U T	I N E =======================================
_screen_lib_load:
		LDA		#$00
		STA		_PPU_CTRL
		STA		_PPU_MASK
		LDA		_screen_libs,X
		STA		byte_3
		LDA		_screen_libs+1,X
		STA		word_4
		LDA		#$00
		STA		_ppu_queue_pos
		STA		byte_FC
		STA		byte_FD
		LDX		#$20
		LDY		#$00
		LDA		_PPU_STATUS
		STX		_PPU_ADDR
		STY		_PPU_ADDR
		LDA		#$00
		STA		word_0
loc_925E:
		LDY		word_0
		CPY		#$08
		BEQ		loc_9276
		LDA		(byte_3),Y
		STA		word_0+1
		INY
		LDA		(byte_3),Y
		STA		byte_2
		INY
		STY		word_0
		JSR		_screen_unpack
		JMP		loc_925E
; ---------------------------------------------------------------------------
loc_9276:
		JMP		_render_on_nmi_on

; =============== S U B	R O U T	I N E =======================================
_game_vars_init:
		LDA		#$00
		STA		_game_vat50
		STA		_game_vat57
		STA		_game_vat49
		STA		_game_vat4B
		STA		_game_vat4D
		STA		_game_vat55
		RTS

; =============== S U B	R O U T	I N E =======================================
_screen_unpack:
		LDY		#$00
loc_928A:
		LDA		(word_0+1),Y
		CMP		#$34
		BEQ		loc_929B
		CMP		#$39
		BEQ		locret_929A
		STA		_PPU_DATA
loc_9297:
		INY
		BNE		loc_928A
locret_929A:
		RTS
; ---------------------------------------------------------------------------
loc_929B:
		INY
		LDA		(word_0+1),Y
		INY
		CMP		#$34
		BEQ		loc_92AE
		TAX
		LDA		(word_0+1),Y
loc_92A6:
		STA		_PPU_DATA
		DEX
		BNE		loc_92A6
		BEQ		loc_9297
loc_92AE:
		LDA		(word_0+1),Y
		STA		_PPU_ADDR
		INY
		LDA		(word_0+1),Y
		STA		_PPU_ADDR
		JMP		loc_9297
; ---------------------------------------------------------------------------
_screen_libs:
		.WORD _screen_lib0_blank
		.WORD _screen_lib2_title
		.WORD _screen_lib4_regular_stage_complete
		.WORD _screen_lib6_intro
		.WORD _screen_lib8_final_stage_complete
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

; =============== S U B	R O U T	I N E =======================================
_hud_draw_handlers:
		LDA		_ppu_queue_pos
		BEQ		loc_949C

; =============== S U B	R O U T	I N E =======================================
_hud_draw_exit:
		RTS

; =============== S U B	R O U T	I N E =======================================
_hud_draw_loop:
		CMP		#$09
		BEQ		_hud_draw_exit
		LDA		_1p_stage
		BEQ		_hud_draw_exit
		JMP		loc_94C7
; ---------------------------------------------------------------------------
loc_949C:
		LDA		_frames_counter
		LSR
		BCC		_hud_draw_exit
		LDA		_main_sub_idx
		CMP		#$08
		BEQ		_hud_draw_exit
		BCS		_hud_draw_loop
		CMP		#$05
		BNE		loc_94BF
		LDA		_game_main_sub_idx
		CMP		#$0C
		BCS		loc_94C7
		CMP		#$06
		BEQ		loc_94C7
		BNE		_hud_draw_exit
loc_94B9:
		LDA		byte_5A
		BNE		_hud_draw_exit
		BEQ		loc_94C7
loc_94BF:
		CMP		#$02
		BEQ		loc_94B9
		CMP		#$07
		BCC		_hud_draw_exit
loc_94C7:
		INC		_hud_draw_sub_idx
		LDA		_hud_draw_sub_idx
		AND		#$07
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD _hud_draw_sub00
		.WORD _hud_draw_sub01
		.WORD _hud_draw_sub02
		.WORD _hud_draw_sub03
		.WORD _hud_draw_sub04
		.WORD _hud_draw_sub05
		.WORD _hud_draw_sub06
		.WORD _hud_draw_sub07

; =============== S U B	R O U T	I N E =======================================
_hud_draw_sub07:
		RTS

; =============== S U B	R O U T	I N E =======================================
_hud_draw_sub00:
		LDA		_1p_lives
		BNE		loc_94E8
		JMP		_hud_draw_sub05
; ---------------------------------------------------------------------------
loc_94E8:
		LDA		#$07
		JSR		_tlm_lib_load
		LDA		_1p_lives
		STA		byte_9

; =============== S U B	R O U T	I N E =======================================
_hud_draw_lives_ex:
		LDA		#$05
		STA		byte_8
		LDA		byte_9
		BEQ		loc_9509
loc_94F9:
		DEC		byte_9
		BEQ		loc_9509
		LDA		#$0D
		STA		_ppu_queue_buf,X
		INX
		DEC		byte_8
		BEQ		sub_9542
		BNE		loc_94F9
loc_9509:
		LDA		#$00
loc_950B:
		STA		_ppu_queue_buf,X
		INX
		DEC		byte_8
		BNE		loc_950B
		BEQ		sub_9542

; =============== S U B	R O U T	I N E =======================================
_hud_draw_sub01:
		LDA		_2p_lives
		BNE		loc_951C
		JMP		_hud_draw_sub06
; ---------------------------------------------------------------------------
loc_951C:
		LDA		#$0D
		JSR		_tlm_lib_load
		LDA		_2p_lives
		STA		byte_9
		JMP		_hud_draw_lives_ex

; =============== S U B	R O U T	I N E =======================================
_hud_draw_sub02:
		LDA		#$08
		JSR		_tlm_lib_load
		LDA		#$00
		STA		byte_2
		LDY		#$02
loc_9533:
		LDA		_hi_scores,Y
		JSR		sub_9550
		DEY
		BPL		loc_9533

; =============== S U B	R O U T	I N E =======================================
sub_953C:
		LDA		#$01
		STA		_ppu_queue_buf,X
		INX

; =============== S U B	R O U T	I N E =======================================
sub_9542:
		LDA		#$FF
		STA		_ppu_queue_buf,X
		INX
		LDA		#$00
		STA		_ppu_queue_buf,X
		STX		_ppu_queue_pos
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_9550:
		STA		word_0
		LSR
		LSR
		LSR
		LSR
		CLC
		ADC		#$01
		JSR		sub_956F
		STA		_ppu_queue_buf,X
		INX
		LDA		word_0
		AND		#$0F
		CLC
		ADC		#$01
		JSR		sub_956F
		STA		_ppu_queue_buf,X
		INX
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_956F:
		PHA
		CMP		#$01
		BNE		loc_957D
		LDA		byte_2
		BNE		loc_9581
		PLA
		LDA		#$00
		BEQ		locret_9582
loc_957D:
		LDA		#$01
		STA		byte_2
loc_9581:
		PLA
locret_9582:
		RTS

; =============== S U B	R O U T	I N E =======================================
_hud_draw_sub03:
		LDA		#$09
		JSR		_tlm_lib_load
		LDA		#$00
		STA		byte_2
		LDY		#$02
loc_958E:
		LDA		_1p_score,Y
		JSR		sub_9550
		DEY
		BPL		loc_958E
		BMI		sub_953C

; =============== S U B	R O U T	I N E =======================================
_hud_draw_sub04:
		LDA		_players_num
		BEQ		_hud_draw_sub03
		LDA		#$0A
		JSR		_tlm_lib_load
		LDA		#$00
		STA		byte_2
		LDY		#$02
loc_95A8:
		LDA		_2p_scores,Y
		JSR		sub_9550
		DEY
		BPL		loc_95A8
		BMI		sub_953C

; =============== S U B	R O U T	I N E =======================================
_hud_draw_sub05:
		LDA		_main_sub_idx
		CMP		#$05
		BEQ		loc_95BD
		CMP		#$02
		BNE		locret_95C6
loc_95BD:
		LDA		_1p_lives
		BNE		loc_95C7
		LDA		#$11
		JSR		_tlm_lib_load
locret_95C6:
		RTS
; ---------------------------------------------------------------------------
loc_95C7:
		LDA		#$0E
		JSR		_tlm_lib_load
		LDA		byte_500+$1C

; =============== S U B	R O U T	I N E =======================================
sub_95CF:
		CLC
		ADC		#$01
		STA		_ppu_queue_buf,X
		INX
		JMP		sub_9542

; =============== S U B	R O U T	I N E =======================================
_hud_draw_sub06:
		LDA		_main_sub_idx
		CMP		#$05
		BEQ		loc_95E3
		CMP		#$02
		BNE		locret_95F0
loc_95E3:
		LDA		_players_num
		BEQ		locret_9582
		LDA		_2p_lives
		BNE		loc_95F1
		LDA		#$12
		JSR		_tlm_lib_load
locret_95F0:
		RTS
; ---------------------------------------------------------------------------
loc_95F1:
		LDA		#$0F
		JSR		_tlm_lib_load
		LDA		byte_53C
		JMP		sub_95CF

; =============== S U B	R O U T	I N E =======================================
;_tlm_lib_loadA_unref:
;		STX		word_4
;		JSR		_tlm_lib_load
;		LDA		word_4
;		BNE		_tlm_lib_load_ex

; =============== S U B	R O U T	I N E =======================================
_tlm_lib_load:
		PHA
		LDA		#$02
		STA		byte_3
		LDA		#$01
		JSR		_ppu_queue_byte_insert
		PLA

; =============== S U B	R O U T	I N E =======================================
;_tlm_lib_load_ex:
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

; =============== S U B	R O U T	I N E =======================================
_main05_game_demo:
		JSR		_demo_input_fetch

; =============== S U B	R O U T	I N E =======================================
_main05_game:
		LDA		_game_main_sub_idx
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD _game00
		.WORD _game01
		.WORD _game02
		.WORD _game03
		.WORD _game04
		.WORD _game05
		.WORD _game06
		.WORD _game09
		.WORD _game09
		.WORD _game09
		.WORD _game0A
		.WORD _game0B
		.WORD _game0C
		.WORD _game0D
		.WORD _game0E
		.WORD _game0F
		.WORD _game10

; =============== S U B	R O U T	I N E =======================================
_game00:
		LDA		#$1E
		STA		_ppu_mask_shadow
		JSR		_screen_clear
		JSR		_fds_load_bufs_clear
		LDA		#$00
		STA		byte_44
		STA		byte_45
		STA		byte_46
		STA		byte_47
		STA		byte_465
		LDA		#$08
		STA		byte_5A
		LDA		#$01
		STA		byte_2E
		INC		_game_main_sub_idx

; =============== S U B	R O U T	I N E =======================================
nullsub_8:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_A367:
		LDA		_frames_counter
		AND		#$01
		BNE		locret_A36F
		DEC		byte_5A
locret_A36F:
		RTS

; =============== S U B	R O U T	I N E =======================================
_game01:
		JSR		_hud_draw_handlers
		JSR		sub_A367
		BNE		nullsub_8
		LDA		#$14
		STA		_nmi_counter
		INC		_game_main_sub_idx
		RTS

; =============== S U B	R O U T	I N E =======================================
_game02:
		LDA		_1p_stage
		CLC
		ADC		#$09
		JSR		_fds_data_load
		LDA		_1p_stage
		CLC
		ADC		#$01
		JSR		_fds_data_load
		LDA		#$17
		JSR		_file_lib_unpack
		JSR		_fds_load_bufs_clear
		INC		_game_main_sub_idx
		RTS

; =============== S U B	R O U T	I N E =======================================
_game03:
		LDA		#$7D
		JSR		_apu_load_safe
		LDX		_1p_stage
		LDA		_stage_mus_list,X
		STA		byte_7F
		LDA		#$29
		JSR		_apu_load_safe
		LDA		#$13
		STA		_nmi_counter
		INC		_game_main_sub_idx
		RTS
; ---------------------------------------------------------------------------
_stage_mus_list:
		.BYTE $2F,$35,$2F,$35,$2F,$3B

; =============== S U B	R O U T	I N E =======================================
_game04:
		JSR		sub_9119
		LDA		byte_44
		LDX		byte_45
		STA		byte_48
		STX		_game_vat49
		STA		byte_4A
		STX		_game_vat4B
		STA		byte_4C
		STX		_game_vat4D
		LDA		byte_46
		LDX		byte_47
		STA		byte_4E
		STX		byte_4F
		LDA		#$00
		STA		_game_vat57
		STA		_game_vat50
		STA		byte_56
		STA		byte_58
		JSR		sub_A561
		LDA		#$0C
		STA		_game_vat55
loc_A3E4:
		JSR		sub_8EEB
		DEC		_game_vat55
		BNE		loc_A3E4
		LDA		#$09
		STA		byte_461
		INC		_game_main_sub_idx
		RTS

; =============== S U B	R O U T	I N E =======================================
_game05:
		LDA		#$0C
		STA		_game_vat55
loc_A3F7:
		LDA		#$05
		STA		_nmi_counter
		JSR		sub_8EEB
		DEC		_game_vat55
		BNE		loc_A3F7
		DEC		byte_461
		BNE		locret_A440
		LDA		#$00
		STA		_ppu_queue_pos
		LDA		byte_465
		BEQ		loc_A418
		LDX		_1p_stage
		LDA		byte_A441,X
		JMP		loc_A41D
; ---------------------------------------------------------------------------
loc_A418:
		LDA		_1p_stage
		CLC
		ADC		#$4D
loc_A41D:
		JSR		_tlm_lib_load
		LDA		#$00
		STA		byte_500
		STA		byte_520
		STA		byte_460
		STA		byte_459
		STA		byte_45A
		STA		byte_5D
		STA		byte_6A
		LDA		#$22
		STA		byte_462
		INC		_game_main_sub_idx
		LDA		#$08
		STA		_nmi_counter
locret_A440:
		RTS
; ---------------------------------------------------------------------------
byte_A441:
		.BYTE $53,$53,$53,$55,$56,$56

; =============== S U B	R O U T	I N E =======================================
_game06:
		JSR		sub_A5E1
		LDA		byte_2D
		BNE		locret_A440
		LDA		#$01
		STA		byte_2E
		LDA		_1p_lives
		BNE		loc_A45B
		LDA		#$80
		STA		byte_500+3
loc_A45B:
		LDA		_2p_lives
		BNE		loc_A464
		LDA		#$80
		STA		byte_523
loc_A464:
		JSR		sub_ADB6
		JSR		sub_B7D1
		JSR		sub_C7B7
		JSR		sub_A6DF
		LDA		byte_500
		ORA		byte_520
		BEQ		loc_A47E
		BMI		loc_A47E
		LDA		#$00
		STA		byte_2E
loc_A47E:
		LDA		_1p_stage
		CMP		#$05
		BNE		loc_A4A1
		LDA		_frames_counter
		AND		#$07
		BNE		loc_A4A1
		LDA		byte_460
		BEQ		loc_A4A1
		INC		byte_462
		LDA		byte_462
		CMP		#$25
		BCC		loc_A49E
		LDA		#$22
		STA		byte_462
loc_A49E:
		JSR		_tlm_lib_load
loc_A4A1:
		LDA		_1p_lives
		ORA		_2p_lives
		BNE		nullsub_7
		LDA		_main_sub_idx
		CMP		#$02
		BEQ		sub_A4B6
		LDA		#$00
		STA		_sub_sub_idx
		LDA		#$06

; =============== S U B	R O U T	I N E =======================================
sub_A4B3:
		STA		_main_sub_idx

; =============== S U B	R O U T	I N E =======================================
nullsub_7:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_A4B6:
		LDA		#$00
		BEQ		sub_A4B3

; =============== S U B	R O U T	I N E =======================================
_game09:
		LDA		_1p_stage

; =============== S U B	R O U T	I N E =======================================
sub_A4BC:
		STA		byte_465
		LDA		#$30
		STA		byte_6C
		JSR		_fds_load_bufs_clear
		JSR		_screen_clear
		JSR		sub_A553
		LDA		_2p_stage
		CMP		#$01
		BEQ		sub_A4ED
		LDA		byte_6A
		BEQ		sub_A4ED
		DEC		byte_4E
		LDA		byte_4F
		SEC
		SBC		#$BC
		STA		byte_47
		LDA		byte_4E
		SBC		#$00
		STA		byte_46
		LDA		byte_48
		SEC
		SBC		#$08
		JMP		sub_A4FE

; =============== S U B	R O U T	I N E =======================================
sub_A4ED:
		LDA		byte_4F
		SEC
		SBC		#$3C
		STA		byte_47
		LDA		byte_4E
		SBC		#$00
		BMI		sub_A50D
		STA		byte_46
		LDA		byte_48

; =============== S U B	R O U T	I N E =======================================
sub_A4FE:
		STA		byte_44
		LDA		_game_vat49
		AND		#$E0
		STA		byte_45
		JMP		sub_A517

; =============== S U B	R O U T	I N E =======================================
sub_A509:
		LDA		#$20
		STA		byte_5A

; =============== S U B	R O U T	I N E =======================================
sub_A50D:
		LDA		#$00
		STA		byte_44
		STA		byte_45
		STA		byte_46
		STA		byte_47

; =============== S U B	R O U T	I N E =======================================
sub_A517:
		INC		_game_main_sub_idx
		RTS

; =============== S U B	R O U T	I N E =======================================
_game0A:
		JMP		_game04

; =============== S U B	R O U T	I N E =======================================
_game0B:
		JMP		_game05

; =============== S U B	R O U T	I N E =======================================
_game0C:
		LDA		#$7D
		JSR		_apu_load_safe
		LDA		#$3E
		STA		byte_7F
		JSR		_apu_load_safe
		LDA		#$06
		STA		_game_main_sub_idx
		JMP		_game06

; =============== S U B	R O U T	I N E =======================================
_game0D:
		LDA		#$7D
		JSR		_apu_load_safe
		LDA		#$00
		BEQ		sub_A4BC

; =============== S U B	R O U T	I N E =======================================
_game0E:
		JMP		_game04

; =============== S U B	R O U T	I N E =======================================
_game0F:
		JMP		_game05

; =============== S U B	R O U T	I N E =======================================
_game10:
		LDX		_1p_stage
		LDA		_stage_mus_list,X
		STA		byte_7F
		JSR		_apu_load_safe
		LDA		#$06
		STA		_game_main_sub_idx
		JMP		_game06

; =============== S U B	R O U T	I N E =======================================
sub_A553:
		LDA		byte_4F
		CLC
		ADC		_game_vat50
		STA		byte_4F
		LDA		byte_4E
		ADC		#$00
		STA		byte_4E
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_A561:
		LDX		#$A8
		LDA		byte_48
		AND		#$01
		STA		byte_10
		BEQ		loc_A56D
		LDX		#$A9
loc_A56D:
		STX		_ppu_ctrl_shadow
		LDA		_game_vat49
		STA		byte_FD
		LSR
		LSR
		LSR
		LSR
		LSR
		STA		byte_11
		CLC
		ADC		byte_11
		ADC		byte_11
		ADC		byte_11
		LDX		byte_10
		BEQ		loc_A588
		CLC
		ADC		#$20
loc_A588:
		TAX
		LDA		byte_A5A1,X
		STA		byte_51
		INX
		LDA		byte_A5A1,X
		STA		byte_52
		INX
		LDA		byte_A5A1,X
		STA		byte_53
		INX
		LDA		byte_A5A1,X
		STA		byte_54
		RTS
; ---------------------------------------------------------------------------
byte_A5A1:
		.BYTE $20,$80,$23,$C8
		.BYTE $20,$84,$23,$C9
		.BYTE $20,$88,$23,$CA
		.BYTE $20,$8C,$23,$CB
		.BYTE $20,$90,$23,$CC
		.BYTE $20,$94,$23,$CD
		.BYTE $20,$98,$23,$CE
		.BYTE $20,$9C,$23,$CF
		.BYTE $24,$80,$27,$C8
		.BYTE $24,$84,$27,$C9
		.BYTE $24,$88,$27,$CA
		.BYTE $24,$8C,$27,$CB
		.BYTE $24,$90,$27,$CC
		.BYTE $24,$94,$27,$CD
		.BYTE $24,$98,$27,$CE
		.BYTE $24,$9C,$27,$CF

; =============== S U B	R O U T	I N E =======================================
sub_A5E1:
		LDA		byte_20
		ORA		byte_2E
		ORA		_nmi_counter
		BNE		locret_A607
		LDA		_pads_press
		LDY		byte_2D
		BNE		loc_A5FD
		AND		#$10
		BEQ		locret_A607
		LDA		#$01
		STA		byte_2D
		LDA		#$78
		JSR		_apu_load_safe
		RTS
; ---------------------------------------------------------------------------
loc_A5FD:
		LDA		_pads_press
		AND		#$10
		BEQ		locret_A607
		LDA		#$00
		STA		byte_2D
locret_A607:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_A608:
		STA		byte_6
		LDX		#$CC
		STX		byte_7
		LDA		#$01
		STA		byte_B
		BNE		loc_A61C

; =============== S U B	R O U T	I N E =======================================
sub_A614:
		STA		byte_6
		STX		byte_7
		LDA		#$00
		STA		byte_B
loc_A61C:
		LDA		byte_FD
		AND		#$07
		CLC
		ADC		byte_6
		STA		byte_6
		LDA		byte_6
		AND		#$E0
		LSR
		LSR
		LSR
		LSR
		LSR
		TAX
		LDA		byte_A6A9,X
		CLC
		ADC		byte_58
		BCS		loc_A63B
		CMP		#$F0
		BCC		loc_A63E
loc_A63B:
		CLC
		ADC		#$10
loc_A63E:
		STA		word_0
		LDA		byte_FD
		AND		#$1F
		LSR
		LSR
		LSR
		STA		word_0+1
		LDA		byte_6
		AND		#$1F
		LSR
		LSR
		LSR
		CLC
		ADC		word_0+1
		STA		word_0+1
		LDA		byte_7
		SEC
		SBC		#$1C
		BCS		loc_A65E
		LDA		#$00
loc_A65E:
		LSR
		LSR
		LSR
		CLC
		ADC		word_0
		STA		word_0
		TAX
		LDA		word_0+1
		CMP		#$04
		BCC		loc_A682
		PHA
		TXA
		CLC
		ADC		#$18
		BCS		loc_A678
		CMP		#$F0
		BCC		loc_A67B
loc_A678:
		CLC
		ADC		#$10
loc_A67B:
		TAX
		PLA
		SEC
		SBC		#$04
		STA		word_0+1
loc_A682:
		LDA		byte_B
		BNE		loc_A699
		LDA		byte_350,X
		LDX		word_0+1
		AND		byte_A6B1,X
		BEQ		locret_A698
loc_A690:
		LSR
		BCS		loc_A697
		LSR
		BCC		loc_A690
		ROL
loc_A697:
		ROL
locret_A698:
		RTS
; ---------------------------------------------------------------------------
loc_A699:
		LDA		byte_350,X
		STX		byte_B
		LDX		word_0+1
		ORA		byte_A6B1,X
		LDX		byte_B
		STA		byte_350,X
		RTS
; ---------------------------------------------------------------------------
byte_A6A9:
		.BYTE $00,$18,$30,$48,$60,$78,$90,$A8
byte_A6B1:
		.BYTE $C0,$30,$0C,$03,$3F,$CF,$F3,$FC

; =============== S U B	R O U T	I N E =======================================
sub_A6B9:
		LDX		#$27
		LDA		byte_543,Y
		CLC
		ADC		#$08
		CLC
		ADC		_game_vat49
		PHA
		LDA		byte_48
		ADC		#$00
		AND		#$01
		BNE		loc_A6CF
		LDX		#$23
loc_A6CF:
		PLA
		AND		#$F8
		CLC
		LSR
		LSR
		LSR
		ADC		#$40
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_A6D9:
		JMP		sub_A830

; =============== S U B	R O U T	I N E =======================================
sub_A6DC:
		JMP		sub_A826

; =============== S U B	R O U T	I N E =======================================
sub_A6DF:
		LDA		_frames_counter
		LSR
		BCC		sub_A6E7
		JMP		sub_A8D5

; =============== S U B	R O U T	I N E =======================================
sub_A6E7:
		LDY		#$00

; =============== S U B	R O U T	I N E =======================================
sub_A6E9:
		LDX		#$01
		LDA		byte_500+1,Y
		CMP		#$0B
		BEQ		loc_A6FC
		CMP		#$03
		BCC		loc_A6FA
		CMP		#$06
		BCC		loc_A6FC
loc_A6FA:
		LDX		#$00
loc_A6FC:
		STX		byte_10
		LDX		#$00

; =============== S U B	R O U T	I N E =======================================
sub_A700:
		LDA		byte_500,Y
		BEQ		sub_A6D9
		BMI		sub_A6D9
		LDA		byte_540,X
		BEQ		sub_A6DC
		BMI		sub_A6DC
		LDA		byte_541,X
		CMP		#$23
		BEQ		sub_A6DC
		CMP		#$06
		BNE		loc_A71E
		LDA		byte_54F,X
		BEQ		sub_A6DC
loc_A71E:
		LDA		byte_500+3,Y
		SEC
		SBC		byte_543,X
		BCS		loc_A72C
		EOR		#$FF
		CLC
		ADC		#$01
loc_A72C:
		STX		byte_11
		LDX		byte_10
		CMP		byte_A8D3,X
		LDX		byte_11
		BCS		loc_A75A
		LDA		byte_541,X
		CMP		#$06
		BNE		sub_A74A
		JMP		sub_A83C

; =============== S U B	R O U T	I N E =======================================
sub_A741:
		JMP		sub_A844

; =============== S U B	R O U T	I N E =======================================
sub_A744:
		JMP		sub_A848

; =============== S U B	R O U T	I N E =======================================
sub_A747:
		JMP		sub_A826

; =============== S U B	R O U T	I N E =======================================
sub_A74A:
		LDA		byte_500+$D,Y
		SEC
		SBC		byte_545,X
		BCS		loc_A758
		EOR		#$FF
		CLC
		ADC		#$01
loc_A758:
		CMP		#$25
loc_A75A:
		BCS		sub_A747
		LDA		byte_500+5,Y
		SEC
		SBC		byte_545,X
		BCS		loc_A76A
		EOR		#$FF
		CLC
		ADC		#$01
loc_A76A:
		CMP		#$12
		BCS		sub_A747
		LDA		byte_541,X
		CMP		#$0F
		BEQ		sub_A741
		CMP		#$10
		BEQ		sub_A744
		CMP		#$1D
		BNE		loc_A780
		JMP		sub_A856
; ---------------------------------------------------------------------------
loc_A780:
		CMP		#$1E
		BNE		loc_A787
		JMP		sub_A86F
; ---------------------------------------------------------------------------
loc_A787:
		LDA		byte_500+$C,Y
		BNE		loc_A7EA
		LDA		byte_54F,X
		BNE		loc_A794
		JMP		sub_A826
; ---------------------------------------------------------------------------
loc_A794:
		LDA		#$7D
		JSR		_apu_load_safe
		LDA		#$80
		STA		byte_500,Y
		LDA		_1p_lives
		CMP		#$02
		BCS		loc_A7C0
		LDA		byte_500
		BEQ		loc_A7AB
		BPL		loc_A7C0
loc_A7AB:
		LDA		_2p_lives
		CMP		#$02
		BCS		loc_A7C0
		LDA		byte_520
		BEQ		loc_A7B8
		BPL		loc_A7C0
loc_A7B8:
		LDA		#$01
		STA		byte_5D
		LDA		#$7D
		STA		byte_7F
loc_A7C0:
		LDA		byte_541,X
		CMP		#$06
		BEQ		loc_A7CD
		JSR		sub_AD01
		JMP		loc_A7D2
; ---------------------------------------------------------------------------
loc_A7CD:
		LDA		#$6D
		JSR		_apu_load_safe
loc_A7D2:
		LDA		#$80
		STA		byte_500,Y
		LDA		byte_500+$1D,Y
		CMP		#$03
		BCC		loc_A7E3
		LDA		#$00
		STA		byte_500+$1D,Y
loc_A7E3:
		LDA		#$18
		STA		byte_500+$C,Y
		BNE		loc_A817
loc_A7EA:
		JSR		sub_AD86
		LDA		byte_541,X
		CMP		#$17
		BEQ		loc_A800
		CMP		#$18
		BEQ		loc_A800
		CMP		#$11
		BCC		loc_A812
		CMP		#$14
		BCS		loc_A812
loc_A800:
		LDA		byte_545,X
		CLC
		SBC		#$20
		STA		byte_545,X
		LDA		#$00
		STA		byte_54F,X
		LDA		#$82
		BNE		loc_A814
loc_A812:
		LDA		#$80
loc_A814:
		STA		byte_540,X
loc_A817:
		LDA		byte_541,X
		CMP		#$06
		BNE		loc_A823
		LDA		#$82
		STA		byte_540,X
loc_A823:
		JMP		sub_A830

; =============== S U B	R O U T	I N E =======================================
sub_A826:
		TXA
		CLC
		ADC		#$20
		TAX
		BEQ		sub_A830
		JMP		sub_A700

; =============== S U B	R O U T	I N E =======================================
sub_A830:
		CPY		#$20
		BNE		loc_A837
		JMP		sub_A8D5
; ---------------------------------------------------------------------------
loc_A837:
		LDY		#$20
		JMP		sub_A6E9

; =============== S U B	R O U T	I N E =======================================
sub_A83C:
		LDA		byte_500+$10,Y
		BNE		sub_A826
		JMP		sub_A74A

; =============== S U B	R O U T	I N E =======================================
sub_A844:
		LDA		#$01
		BNE		sub_A84D

; =============== S U B	R O U T	I N E =======================================
sub_A848:
		JSR		sub_AAA1
		LDA		#$02

; =============== S U B	R O U T	I N E =======================================
sub_A84D:
		PHA
		LDA		#$1A
		JSR		_apu_load_safe
		PLA
		BNE		loc_A8A9

; =============== S U B	R O U T	I N E =======================================
sub_A856:
		JSR		sub_8DA6
		JSR		sub_AAA1
		LDA		#$67
		JSR		_apu_load_safe
		LDA		#$44
		JSR		_apu_load_safe
		LDA		#$C5
		STA		byte_500+$C,Y
		LDA		#$03
		BNE		loc_A89E

; =============== S U B	R O U T	I N E =======================================
sub_A86F:
		JSR		sub_8DA6
		LDA		byte_500+$11,Y
		BNE		loc_A88D
		LDA		byte_500+$1D,Y
		CMP		#$01
		BNE		loc_A88D
		LDA		byte_500+$F,Y
		CLC
		ADC		#$07
		CMP		#$1B
		BCC		loc_A88A
		LDA		#$16
loc_A88A:
		STA		byte_500+$F,Y
loc_A88D:
		LDA		#$67
		JSR		_apu_load_safe
		LDA		#$41
		JSR		_apu_load_safe
		LDA		#$E4
		STA		byte_500+$16,Y
		LDA		#$04
loc_A89E:
		STA		byte_500+$1D,Y
		LDA		#$1A
		JSR		_apu_load_safe
		JMP		loc_A8C8
; ---------------------------------------------------------------------------
loc_A8A9:
		PHA
		LDA		byte_500+$1D,Y
		CMP		#$03
		BCC		loc_A8B5
		PLA
		JMP		loc_A8B9
; ---------------------------------------------------------------------------
loc_A8B5:
		PLA
		STA		byte_500+$1D,Y
loc_A8B9:
		LDA		byte_500+$1C,Y
		CLC
		ADC		#$01
		CMP		#$0A
		BCC		loc_A8C5
		LDA		#$09
loc_A8C5:
		STA		byte_500+$1C,Y
loc_A8C8:
		LDA		#$00
		STA		byte_540,X
		JSR		sub_AD86
		JMP		sub_A826
; ---------------------------------------------------------------------------
byte_A8D3:
		.BYTE $08,$10

; =============== S U B	R O U T	I N E =======================================
sub_A8D5:
		LDA		_frames_counter
		LSR
		BCS		loc_A8DD
		JMP		sub_AABB
; ---------------------------------------------------------------------------
loc_A8DD:
		LDY		#$00

; =============== S U B	R O U T	I N E =======================================
sub_A8DF:
		LDX		#$00
loc_A8E1:
		LDA		byte_500,Y
		BEQ		loc_A933
		BMI		loc_A933
		LDA		#$00
		STA		byte_10
		LDA		byte_500+1,Y
		CMP		#$0A
		BEQ		loc_A8FB
		CMP		#$0B
		BNE		loc_A933
		LDA		#$01
		STA		byte_10
loc_A8FB:
		LDA		byte_540,X
		BEQ		loc_A930
		BMI		loc_A930
		LDA		byte_500+3,Y
		CMP		#$40
		BCS		loc_A90E
		LDA		byte_543,X
		BMI		loc_A930
loc_A90E:
		LDA		byte_541,X
		CMP		#$23
		BEQ		loc_A930
		LDA		byte_500+$B,Y
		BEQ		loc_A93F
		LDA		byte_10
		BNE		loc_A927
		LDA		byte_500+3,Y
		SEC
		SBC		#$11
		JMP		loc_A949
; ---------------------------------------------------------------------------
loc_A927:
		LDA		byte_500+3,Y
		SEC
		SBC		#$19
		JMP		loc_A949
; ---------------------------------------------------------------------------
loc_A930:
		JMP		loc_A9FB
; ---------------------------------------------------------------------------
loc_A933:
		JMP		sub_AA05
; ---------------------------------------------------------------------------
loc_A936:
		LDA		byte_500+3,Y
		CLC
		ADC		#$19
		JMP		loc_A949
; ---------------------------------------------------------------------------
loc_A93F:
		LDA		byte_10
		BNE		loc_A936
		LDA		byte_500+3,Y
		CLC
		ADC		#$11
loc_A949:
		SEC
		SBC		byte_543,X
		BCS		loc_A954
		EOR		#$FF
		CLC
		ADC		#$01
loc_A954:
		STX		byte_11
		PHA
		LDA		byte_541,X
		CMP		#$0B
		BEQ		loc_A96E
		CMP		#$0C
		BEQ		loc_A96E
		CMP		#$19
		BEQ		loc_A96E
		CMP		#$1A
		BEQ		loc_A96E
		LDX		#$00
		BEQ		loc_A970
loc_A96E:
		LDX		#$01
loc_A970:
		PLA
		CMP		byte_AA9F,X
		LDX		byte_11
		BCC		loc_A97B
		JMP		loc_A9FB
; ---------------------------------------------------------------------------
loc_A97B:
		LDA		byte_500+$D,Y
		SEC
		SBC		byte_545,X
		BCS		loc_A989
		EOR		#$FF
		CLC
		ADC		#$01
loc_A989:
		CMP		#$25
		BCS		loc_A9FB
		LDA		byte_541,X
		CMP		#$0B
		BEQ		loc_A9A0
		CMP		#$0F
		BEQ		loc_A9A0
		CMP		#$19
		BEQ		loc_A9A0
		CMP		#$1A
		BNE		loc_A9A4
loc_A9A0:
		LDA		byte_10
		BEQ		loc_A9FB
loc_A9A4:
		LDA		byte_500+5,Y
		SEC
		SBC		byte_545,X
		BCS		loc_A9B2
		EOR		#$FF
		CLC
		ADC		#$01
loc_A9B2:
		CMP		#$10
		BCS		loc_A9FB
		JMP		sub_AA11
; ---------------------------------------------------------------------------
loc_A9B9:
		LDA		byte_541,X
		CMP		#$06
		BNE		loc_A9CE
		LDA		byte_54F,X
		BNE		loc_A9FB
		LDA		byte_500+1,Y
		CMP		#$0B
		BNE		loc_A9FB
		BEQ		loc_A9F2
loc_A9CE:
		JSR		sub_AD86
		LDA		byte_541,X
		CMP		#$17
		BEQ		loc_A9E4
		CMP		#$18
		BEQ		loc_A9E4
		CMP		#$11
		BCC		loc_A9F6
		CMP		#$14
		BCS		loc_A9F6
loc_A9E4:
		LDA		byte_545,X
		CLC
		SBC		#$20
		STA		byte_545,X
		LDA		#$00
		STA		byte_54F,X
loc_A9F2:
		LDA		#$82
		BNE		loc_A9F8
loc_A9F6:
		LDA		#$80
loc_A9F8:
		STA		byte_540,X
loc_A9FB:
		TXA
		CLC
		ADC		#$20
		TAX
		BEQ		sub_AA05
		JMP		loc_A8E1

; =============== S U B	R O U T	I N E =======================================
sub_AA05:
		CPY		#$20
		BNE		loc_AA0C
		JMP		sub_AABB
; ---------------------------------------------------------------------------
loc_AA0C:
		LDY		#$20
		JMP		sub_A8DF

; =============== S U B	R O U T	I N E =======================================
sub_AA11:
		LDA		byte_541,X
		CMP		#$0F
		BEQ		loc_A9FB
		CMP		#$10
		BEQ		loc_A9FB
		CMP		#$1D
		BEQ		loc_A9FB
		CMP		#$1E
		BEQ		loc_A9FB
		CMP		#$0B
		BCC		loc_A9B9
		CMP		#$0F
		BCC		loc_AA40
		CMP		#$19
		BCC		loc_A9B9
		CMP		#$1D
		BCS		loc_A9B9
		CLC
		ADC		#$02
		CMP		#$1D
		BCS		loc_AA49
		ADC		#$02
		JMP		loc_AA49
; ---------------------------------------------------------------------------
loc_AA40:
		CLC
		ADC		#$02
		CMP		#$0F
		BCS		loc_AA49
		ADC		#$02
loc_AA49:
		STA		byte_541,X
		STA		byte_55E,X
		LDA		#$00
		STA		byte_550,X
		STA		byte_551,X
		LDA		#$07
		JSR		_apu_load_safe
		TYA
		PHA
		LDA		#$37
		LDY		byte_541,X
		CPY		#$0F
		BEQ		loc_AA75
		LDA		#$38
		CPY		#$10
		BEQ		loc_AA75
		LDA		#$54
		CPY		#$1D
		BEQ		loc_AA75
		LDA		#$55
loc_AA75:
		STA		byte_54F,X
		PLA
		TAY
		LDA		#$01
		STA		byte_54E,X
		LDA		#$00
		STA		byte_54B,X
		STA		byte_552,X
		STA		byte_548,X
		LDA		#$01
		STA		byte_547,X
		LDA		#$FC
		STA		byte_549,X
		LDA		#$C0
		STA		byte_54A,X
		JSR		sub_AD86
		JMP		loc_A9FB
; ---------------------------------------------------------------------------
byte_AA9F:
		.BYTE $09,$12

; =============== S U B	R O U T	I N E =======================================
sub_AAA1:
		LDA		byte_500+$11,Y
		BNE		locret_AABA
		LDA		byte_500+$1D,Y
		CMP		#$01
		BNE		locret_AABA
		LDA		byte_500+$F,Y
		CMP		#$0F
		BCC		locret_AABA
		SEC
		SBC		#$0E
		STA		byte_500+$F,Y
locret_AABA:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_AABB:
		LDY		#$00
loc_AABD:
		LDX		#$01
		LDA		byte_500+1,Y
		CMP		#$0B
		BEQ		loc_AAD0
		CMP		#$03
		BCC		loc_AACE
		CMP		#$06
		BCC		loc_AAD0
loc_AACE:
		LDX		#$00
loc_AAD0:
		STX		byte_10
		LDX		#$00
loc_AAD4:
		LDA		byte_500,Y
		BEQ		loc_AB4C
		BMI		loc_AB4C
		LDA		byte_500+$C,Y
		BNE		loc_AB4C
		LDA		byte_640,X
		BEQ		loc_AB57
		LDA		byte_500+3,Y
		SEC
		SBC		byte_643,X
		BCS		loc_AAF3
		EOR		#$FF
		CLC
		ADC		#$01
loc_AAF3:
		STX		byte_11
		LDX		byte_10
		CMP		byte_ADB0,X
		LDX		byte_11
		BCS		loc_AB57
		LDA		byte_500+5,Y
		CLC
		STX		byte_11
		LDX		byte_10
		ADC		byte_ADB4,X
		LDX		byte_11
		SEC
		SBC		byte_645,X
		BCS		loc_AB16
		EOR		#$FF
		CLC
		ADC		#$01
loc_AB16:
		STX		byte_11
		LDX		byte_10
		CMP		byte_ADB2,X
		LDX		byte_11
		BCS		loc_AB57
		LDA		#$80
		STA		byte_500,Y
		LDA		#$20
		STA		byte_500+$C,Y
		LDA		#$00
		STA		byte_500+$1D,Y
		LDA		byte_641,X
		CMP		#$01
		BEQ		loc_AB3F
		CMP		#$04
		BEQ		loc_AB3F
		CMP		#$05
		BNE		loc_AB4F
loc_AB3F:
		LDA		#$6D
		JSR		_apu_load_safe
		LDA		#$02
		STA		byte_641,X
		JMP		loc_AB57
; ---------------------------------------------------------------------------
loc_AB4C:
		JMP		loc_AB63
; ---------------------------------------------------------------------------
loc_AB4F:
		JSR		sub_AD01
		LDA		#$00
		STA		byte_640,X
loc_AB57:
		TXA
		CLC
		ADC		#$20
		TAX
		CMP		#$80
		BEQ		loc_AB63
		JMP		loc_AAD4
; ---------------------------------------------------------------------------
loc_AB63:
		CPY		#$20
		BEQ		loc_AB6C
		LDY		#$20
		JMP		loc_AABD
; ---------------------------------------------------------------------------
loc_AB6C:
		LDY		#$00
loc_AB6E:
		LDX		#$00
loc_AB70:
		LDA		byte_6C0,Y
		BNE		loc_AB78
loc_AB75:
		JMP		loc_AC6C
; ---------------------------------------------------------------------------
loc_AB78:
		LDA		byte_6C1,Y
		CMP		#$01
		BEQ		loc_AB75
		LDA		byte_540,X
		BEQ		loc_AB86
		BPL		loc_AB90
loc_AB86:
		JMP		sub_AC62
; ---------------------------------------------------------------------------
loc_AB89:
		LDA		byte_543,X
		BPL		loc_AB86
		BMI		loc_ABA5
loc_AB90:
		LDA		byte_6C3,Y
		CMP		#$40
		BCC		loc_AB9B
		CMP		#$C0
		BCC		loc_ABA5
loc_AB9B:
		LDA		byte_6C3,Y
		BMI		loc_AB89
		LDA		byte_543,X
		BMI		loc_AB86
loc_ABA5:
		LDA		byte_541,X
		CMP		#$0F
		BEQ		loc_AB86
		CMP		#$10
		BEQ		loc_AB86
		CMP		#$1D
		BEQ		loc_AB86
		CMP		#$1E
		BEQ		loc_AB86
		CMP		#$23
		BNE		loc_ABBF
		JMP		sub_AD0F
; ---------------------------------------------------------------------------
loc_ABBF:
		LDA		byte_6C1,Y
		BNE		loc_ABD0
		LDA		byte_6DB,Y
		BNE		loc_ABD0
		LDA		byte_541,X
		CMP		#$06
		BEQ		loc_AB86
loc_ABD0:
		LDA		byte_6C1,Y
		CMP		#$03
		BEQ		loc_ABE0
		LDA		#$15
		STA		byte_11
		LDA		#$09
		JMP		loc_ABE6
; ---------------------------------------------------------------------------
loc_ABE0:
		LDA		#$28
		STA		byte_11
		LDA		#$38
loc_ABE6:
		STA		byte_10
		LDA		byte_6C3,Y
		SEC
		SBC		#$04
		SEC
		SBC		byte_543,X
		BCS		loc_ABF9
		EOR		#$FF
		CLC
		ADC		#$01
loc_ABF9:
		CMP		byte_10
		BCS		sub_AC62
		LDA		byte_6C5,Y
		CLC
		ADC		#$F6
		SEC
		SBC		byte_545,X
		BCS		loc_AC0E
		EOR		#$FF
		CLC
		ADC		#$01
loc_AC0E:
		CMP		byte_11
		BCS		sub_AC62
		LDA		byte_541,X
		CMP		#$11
		BCC		loc_AC1D
		CMP		#$14
		BCC		loc_AC37
loc_AC1D:
		CMP		#$17
		BEQ		loc_AC37
		CMP		#$18
		BEQ		loc_AC37
		CMP		#$06
		BNE		loc_AC4E
		LDA		byte_54F,X
		BEQ		sub_AC62
		LDA		byte_6C1,Y
		CMP		#$04
		BEQ		sub_AC62
		BNE		loc_AC4A
loc_AC37:
		LDA		#$00
		STA		byte_6C0,Y
		LDA		byte_545,X
		SEC
		SBC		#$20
		STA		byte_545,X
		LDA		#$00
		STA		byte_54F,X
loc_AC4A:
		LDA		#$82
		BNE		loc_AC50
loc_AC4E:
		LDA		#$80
loc_AC50:
		STA		byte_540,X
		LDA		byte_6C1,Y
		CMP		#$04
		BNE		loc_AC5F
		LDA		#$00
		STA		byte_6C0,Y
loc_AC5F:
		JSR		sub_AD86

; =============== S U B	R O U T	I N E =======================================
sub_AC62:
		TXA
		CLC
		ADC		#$20
		TAX
		BEQ		loc_AC6C
		JMP		loc_AB70
; ---------------------------------------------------------------------------
loc_AC6C:
		CPY		#$20
		BEQ		loc_AC75
		LDY		#$20
		JMP		loc_AB6E
; ---------------------------------------------------------------------------
loc_AC75:
		LDA		_players_num
		BEQ		locret_ACC6
		LDY		#$00
		LDX		#$20
loc_AC7D:
		LDA		byte_500,Y
		BEQ		loc_ACC2
		BMI		loc_ACC2
		LDA		byte_500+$1D,Y
		CMP		#$03
		BCS		loc_ACC2
		LDA		byte_6C0,X
		BEQ		loc_ACC2
		BMI		loc_ACC2
		LDA		byte_6D2,X
		BNE		loc_ACC2
		LDA		byte_6C3,X
		CLC
		ADC		#$10
		BCC		loc_ACA1
		LDA		#$F8
loc_ACA1:
		SEC
		SBC		byte_500+3,Y
		BCS		loc_ACAC
		EOR		#$FF
		CLC
		ADC		#$01
loc_ACAC:
		CMP		#$0B
		BCS		loc_ACC2
		LDA		byte_6C5,X
		SEC
		SBC		byte_500+5,Y
		BCS		loc_ACBE
		EOR		#$FF
		CLC
		ADC		#$01
loc_ACBE:
		CMP		#$0E
		BCC		loc_ACCD
loc_ACC2:
		CPY		#$20
		BCC		loc_ACC7
locret_ACC6:
		RTS
; ---------------------------------------------------------------------------
loc_ACC7:
		LDY		#$20
		LDX		#$00
		BEQ		loc_AC7D
loc_ACCD:
		LDA		#$1A
		JSR		_apu_load_safe
		LDA		byte_500+$1D,Y
		CMP		#$01
		BNE		loc_ACE2
		LDA		byte_500+$F,Y
		SEC
		SBC		#$0E
		STA		byte_500+$F,Y
loc_ACE2:
		LDA		byte_6C1,X
		CLC
		ADC		#$01
		STA		byte_500+$1D,Y
		LDA		byte_500+$1C,Y
		CLC
		ADC		#$01
		CMP		#$0A
		BCC		loc_ACF7
		LDA		#$09
loc_ACF7:
		STA		byte_500+$1C,Y
		LDA		#$01
		STA		byte_6D2,X
		BNE		loc_ACC2

; =============== S U B	R O U T	I N E =======================================
sub_AD01:
		LDA		#$7D
		JSR		_apu_load_safe
		LDA		#$6A
		JSR		_apu_load_safe
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_AD0C:
		JMP		sub_AC62

; =============== S U B	R O U T	I N E =======================================
sub_AD0F:
		LDA		byte_460
		BEQ		sub_AD0C
		LDA		byte_6C1,Y
		CMP		#$03
		BEQ		sub_AD0C
		LDA		byte_6C3,Y
		CMP		#$C0
		BCS		sub_AD0C
		CMP		#$B0
		BCC		sub_AD0C
		LDA		#$02
		STA		byte_6C1,Y
		DEC		byte_556,X
		BNE		sub_AD0C
		LDA		#$7D
		JSR		_apu_load_safe
		LDX		#$00
		STX		byte_10
loc_AD39:
		LDY		byte_10
		LDA		byte_AD66,Y
		STA		byte_545,X
		INY
		LDA		byte_AD66,Y
		STA		byte_540,X
		INY
		LDA		byte_AD66,Y
		STA		byte_54F,X
		LDA		#$02
		STA		byte_54E,X
		INY
		LDA		byte_AD66,Y
		STA		byte_55F,X
		INY
		STY		byte_10
		TXA
		CLC
		ADC		#$20
		TAX
		BNE		loc_AD39
		RTS
; ---------------------------------------------------------------------------
byte_AD66:
		.BYTE $A8,$84,$1B,$05,$98,$85,$00,$20,$78,$84,$00,$40,$68,$85,$00,$60
		.BYTE $58,$84,$00,$80,$48,$85,$00,$A0,$38,$84,$00,$C8,$28,$85,$00,$E0

; =============== S U B	R O U T	I N E =======================================
sub_AD86:
		LDA		byte_559,X
		ASL
		ASL
		ASL
		ASL
		STA		word_0+1
		LDA		byte_559,X
		LSR
		LSR
		LSR
		LSR
		STA		byte_2
		PHA
		TXA
		PHA
		TYA
		PHA
		CPY		#$00
		BEQ		loc_ADAA
		JSR		sub_8CDC
loc_ADA4:
		PLA
		TAY
		PLA
		TAX
		PLA
		RTS
; ---------------------------------------------------------------------------
loc_ADAA:
		JSR		sub_8CE0
		JMP		loc_ADA4
; ---------------------------------------------------------------------------
byte_ADB0:
		.BYTE $08,$13
byte_ADB2:
		.BYTE $0A,$04
byte_ADB4:
		.BYTE $0C,$18

; =============== S U B	R O U T	I N E =======================================
sub_ADB6:
		LDA		#$00
		STA		byte_8
		LDY		#$00
loc_ADBC:
		LDA		_1p_lives
		CPY		#$00
		BEQ		loc_ADC4
		LDA		_2p_lives
loc_ADC4:
		CMP		#$00
		BNE		loc_ADCB
		JMP		loc_B362
; ---------------------------------------------------------------------------
loc_ADCB:
		LDA		byte_500,Y
		BNE		loc_AE2C
		LDA		byte_500+$C,Y
		PHA
		LDX		#$20
		TYA
		PHA
		LDA		#$00
loc_ADDA:
		STA		byte_500,Y
		INY
		DEX
		BNE		loc_ADDA
		PLA
		TAY
		PLA
		BEQ		loc_ADF5
		STA		byte_500+$C,Y
		LDA		#$00
		STA		byte_500+$1C,Y
		LDA		#$03
		STA		byte_500+$1D,Y
		BNE		loc_ADF8
loc_ADF5:
		JSR		sub_8D8C
loc_ADF8:
		LDA		#$01
		STA		byte_500,Y
		LDA		#$AE
		LDX		byte_465
		BEQ		loc_AE06
		LDA		byte_6C
loc_AE06:
		STA		byte_500+5,Y
		LDA		#$40
		CPY		#$00
		BEQ		loc_AE11
		LDA		#$60
loc_AE11:
		STA		byte_500+3,Y
		LDA		#$FF
		STA		byte_500+1,Y
		LDA		#$00
		CPY		#$00
		BEQ		loc_AE21
		LDA		#$01
loc_AE21:
		STA		byte_500+$E,Y
		LDA		#$01
		STA		byte_500+$F,Y
		JMP		sub_B0F9
; ---------------------------------------------------------------------------
loc_AE2C:
		LDA		byte_500+3,Y
		CMP		#$10
		BCS		loc_AE35
		INC		byte_8
loc_AE35:
		JSR		_get_player_input
		LDA		byte_500,Y
		BMI		loc_AE40
		JMP		sub_AF3A
; ---------------------------------------------------------------------------
loc_AE40:
		AND		#$0F
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD sub_AE4F
		.WORD sub_AE7F
		.WORD sub_AEB0
		.WORD sub_AED2
		.WORD sub_AEFB

; =============== S U B	R O U T	I N E =======================================
sub_AE4F:
		LDA		#$00
		CPY		#$00
		BNE		loc_AE5B
		STA		byte_66
		STA		byte_67
		BEQ		loc_AE5F
loc_AE5B:
		STA		byte_68
		STA		byte_69
loc_AE5F:
		LDA		#$60
		STA		byte_500+$1F,Y
		LDA		#$FD
		STA		byte_500+9,Y
		LDA		#$90
		STA		byte_500+$A,Y
		LDA		#$00
		STA		byte_500+$12,Y

; =============== S U B	R O U T	I N E =======================================
sub_AE73:
		LDA		byte_500,Y
		CLC
		ADC		#$01
		STA		byte_500,Y

; =============== S U B	R O U T	I N E =======================================
sub_AE7C:
		JMP		sub_B2FC

; =============== S U B	R O U T	I N E =======================================
sub_AE7F:
		LDA		byte_500+$A,Y
		CLC
		ADC		#$20
		STA		byte_500+$A,Y
		LDA		byte_500+9,Y
		ADC		#$00
		STA		byte_500+9,Y
		LDA		byte_500+5,Y
		LDX		byte_465
		BEQ		loc_AE9E
		CMP		#$9D
		BCC		sub_AE7C
		BCS		loc_AEA2
loc_AE9E:
		CMP		#$AD
		BCC		sub_AE7C
loc_AEA2:
		LDA		#$0C
		STA		byte_500+1,Y
		JSR		sub_B481
		JSR		sub_B551
		JMP		sub_AE73

; =============== S U B	R O U T	I N E =======================================
sub_AEB0:
		LDA		byte_500+$1F,Y
		SEC
		SBC		#$01
		STA		byte_500+$1F,Y
		BNE		sub_AE7C
		LDA		#$9E
		STA		byte_6C
		LDA		#$00
		STA		byte_500,Y
		CPY		#$00
		BNE		loc_AECD
		DEC		_1p_lives
		JMP		sub_AE7C
; ---------------------------------------------------------------------------
loc_AECD:
		DEC		_2p_lives
loc_AECF:
		JMP		sub_AE7C

; =============== S U B	R O U T	I N E =======================================
sub_AED2:
		LDA		#$7D
		JSR		_apu_load_safe
		JSR		sub_B551
		LDA		#$01
		LDX		byte_465
		BEQ		loc_AEE3
		LDA		#$FF
loc_AEE3:
		STA		byte_500+9,Y
		LDA		#$00
		STA		byte_500+$A,Y
		STA		byte_500+$E
		LDA		#$01
		STA		byte_52E
		LDA		#$14
		STA		byte_500+$1F,Y
		JMP		sub_AE73

; =============== S U B	R O U T	I N E =======================================
sub_AEFB:
		LDA		byte_500+$1F,Y
		SEC
		SBC		#$01
		STA		byte_500+$1F,Y
		BNE		loc_AF37
		TYA
		TAX
		LDY		#$00
		LDA		byte_500+$1D,Y
		CMP		#$03
		BNE		loc_AF14
		JSR		sub_8D8C
loc_AF14:
		JSR		sub_8DA6
		LDY		#$20
		LDA		byte_500+$1D,Y
		CMP		#$03
		BNE		loc_AF23
		JSR		sub_8D8C
loc_AF23:
		JSR		sub_8DA6
		TXA
		TAY
		LDA		byte_465
		BEQ		loc_AF31
		LDA		#$0D
		BNE		loc_AF33
loc_AF31:
		LDA		#$09
loc_AF33:
		STA		_game_main_sub_idx
		BNE		loc_AECF
loc_AF37:
		JMP		sub_B2FC

; =============== S U B	R O U T	I N E =======================================
sub_AF3A:
		LDA		_1p_stage
		BEQ		sub_AF60
		CMP		#$02
		BEQ		sub_AF60
		CMP		#$05
		BEQ		sub_AF60
		LDA		byte_465
		BEQ		loc_AF54
		LDA		byte_500+5,Y
		CMP		#$2A
		BCC		loc_AF5B
		BCS		sub_AF60
loc_AF54:
		LDA		byte_500+5,Y
		CMP		#$B7
		BCC		sub_AF60
loc_AF5B:
		LDA		#$83
		STA		byte_500,Y

; =============== S U B	R O U T	I N E =======================================
sub_AF60:
		LDA		byte_500+$C,Y
		BEQ		loc_AF97
		LDA		_frames_counter
		AND		#$03
		BNE		loc_AF84
		LDA		byte_500+$C,Y
		SEC
		SBC		#$01
		STA		byte_500+$C,Y
		BNE		loc_AF84
		JSR		sub_B7A5
		LDA		#$00
		CPY		#$00
		BEQ		loc_AF94
		LDA		#$01
		JMP		loc_AF94
; ---------------------------------------------------------------------------
loc_AF84:
		LDA		_frames_counter
		AND		#$03
		BNE		loc_AF97
		LDX		byte_500+$E,Y
		CPY		#$00
		BNE		loc_AFAA
		LDA		byte_AFB0,X
loc_AF94:
		STA		byte_500+$E,Y
loc_AF97:
		LDA		byte_500+$10,Y
		BNE		sub_B010
		LDA		byte_500+5,Y
		STA		byte_500+$D,Y
		LDA		byte_500+$11,Y
		BEQ		sub_AFB6
		JMP		loc_B07F
; ---------------------------------------------------------------------------
loc_AFAA:
		LDA		byte_AFB3,X
		JMP		loc_AF94
; ---------------------------------------------------------------------------
byte_AFB0:
		.BYTE $02,$00,$00
byte_AFB3:
		.BYTE $00,$02,$01

; =============== S U B	R O U T	I N E =======================================
sub_AFB6:
		LDA		#$00
		STA		byte_500+2,Y
		LDA		byte_500+$1F,Y
		BEQ		loc_AFEF
		JSR		sub_B28F
		LDA		byte_500+1,Y
		CMP		#$0A
		BEQ		loc_AFD2
		CMP		#$06
		BCC		loc_AFDF
		CMP		#$09
		BCS		loc_AFDF
loc_AFD2:
		LDA		byte_11
		CMP		#$04
		BCC		loc_AFDF
		CMP		#$07
		BCS		loc_AFDF
		JMP		loc_AFE1
; ---------------------------------------------------------------------------
loc_AFDF:
		LDA		byte_10
loc_AFE1:
		AND		#$0F
		BEQ		loc_AFE9
		CMP		#$0B
		BCC		loc_AFEF
loc_AFE9:
		JMP		sub_B2FC
; ---------------------------------------------------------------------------
loc_AFEC:
		JMP		sub_B0F9
; ---------------------------------------------------------------------------
loc_AFEF:
		LDA		byte_11
		AND		#$0F
		CMP		#$0B
		BCS		loc_AFEC
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD sub_B0F9
		.WORD sub_B11C
		.WORD sub_B14C
		.WORD sub_B0F9
		.WORD sub_B18F
		.WORD sub_B1AE
		.WORD sub_B1BF
		.WORD sub_B0F9
		.WORD sub_B1D9
		.WORD sub_B1FB
		.WORD sub_B227

; =============== S U B	R O U T	I N E =======================================
sub_B010:
		JSR		sub_B27D
		JSR		sub_B467
		JSR		sub_B26C
		CMP		#$00
		BEQ		loc_B07C
		PHA
		LDA		byte_500+9,Y
		BMI		loc_B02C
		CMP		#$03
		BCC		loc_B02C
		LDA		#$18
		JSR		_apu_load_safe
loc_B02C:
		LDA		#$00
		STA		byte_500+$10,Y
		STA		byte_500+$1B,Y
		PLA
		CMP		#$02
		BEQ		loc_B091
		LDA		#$02
		STA		byte_500+$F,Y
loc_B03E:
		LDA		byte_500+5,Y
		AND		#$0F
		CMP		#$06
		BCS		loc_B053
		LDA		byte_500+5,Y
		SEC
		SBC		#$10
		STA		byte_500+5,Y
		JMP		loc_B056
; ---------------------------------------------------------------------------
loc_B053:
		LDA		byte_500+5,Y
loc_B056:
		AND		#$0F
		CMP		#$06
		BCC		loc_B060
		CMP		#$0E
		BCC		loc_B06A
loc_B060:
		LDA		byte_500+5,Y
		AND		#$FE
		ORA		#$0E
		JMP		loc_B071
; ---------------------------------------------------------------------------
loc_B06A:
		LDA		byte_500+5,Y
		AND		#$F6
		ORA		#$06
loc_B071:
		STA		byte_500+5,Y
		LDA		#$00
		STA		byte_500+$12,Y
		JSR		sub_B551
loc_B07C:
		JMP		sub_B146
; ---------------------------------------------------------------------------
loc_B07F:
		JSR		sub_B551
		LDA		byte_11
		AND		#$0F
		CMP		#$04
		BEQ		sub_B0A4
		CMP		#$08
		BEQ		sub_B0CF
		JMP		sub_B2FF
; ---------------------------------------------------------------------------
loc_B091:
		JSR		sub_B551
		LDA		#$01
		STA		byte_500+$11,Y
		LDA		#$09
		STA		byte_500+1,Y
		JSR		sub_B481
		JMP		sub_B2FC

; =============== S U B	R O U T	I N E =======================================
sub_B0A4:
		JSR		sub_B26C
		CMP		#$01
		BNE		loc_B0C2
		LDA		#$03
		STA		byte_500+1,Y
		LDA		#$01
		STA		byte_500+$F,Y
		LDA		#$00
		STA		byte_500+$12,Y
loc_B0BA:
		LDA		#$00
		STA		byte_500+$11,Y
		JMP		loc_B03E
; ---------------------------------------------------------------------------
loc_B0C2:
		LDA		#$01
		STA		byte_500+9,Y
		LDA		#$40
loc_B0C9:
		STA		byte_500+$A,Y
		JMP		sub_B2FC

; =============== S U B	R O U T	I N E =======================================
sub_B0CF:
		JSR		sub_B26C
		CMP		#$01
		BEQ		loc_B0DA
		CMP		#$03
		BNE		loc_B0F0
loc_B0DA:
		LDA		#$01
		STA		byte_500+$F,Y
		LDA		#$06
		STA		byte_500+1,Y
		LDA		#$00
		STA		byte_500+$12,Y
		LDA		#$01
		STA		byte_500+$F,Y
		BNE		loc_B0BA
loc_B0F0:
		LDA		#$FE
		STA		byte_500+9,Y
		LDA		#$C0
		BNE		loc_B0C9

; =============== S U B	R O U T	I N E =======================================
sub_B0F9:
		LDA		#$00
		STA		byte_500+1,Y
		LDA		byte_500+$1B,Y
		BNE		loc_B108
		LDA		#$02
		STA		byte_500+$F,Y
loc_B108:
		JSR		sub_B551
		JSR		sub_B28F
		JSR		sub_B26C
		CMP		#$00
		BEQ		loc_B174
		CMP		#$02
		BEQ		loc_B174
		JMP		sub_B2FF

; =============== S U B	R O U T	I N E =======================================
sub_B11C:
		LDA		byte_500+1,Y
		CMP		#$01
		BEQ		loc_B135
		LDA		#$01
		STA		byte_500+1,Y
		JSR		sub_B481
		LDA		#$01
		STA		byte_500+7,Y
		LDA		#$00
		STA		byte_500+8,Y
loc_B135:
		LDA		#$01
		STA		byte_500+2,Y
		LDA		#$00
		STA		byte_500+$B,Y
		JSR		sub_B26C
		CMP		#$00
		BEQ		loc_B174

; =============== S U B	R O U T	I N E =======================================
sub_B146:
		JSR		sub_B28F
		JMP		sub_B2FC

; =============== S U B	R O U T	I N E =======================================
sub_B14C:
		LDA		byte_500+1,Y
		CMP		#$02
		BEQ		loc_B165
		LDA		#$02
		STA		byte_500+1,Y
		JSR		sub_B481
		LDA		#$FF
		STA		byte_500+7,Y
		LDA		#$00
		STA		byte_500+8,Y
loc_B165:
		LDA		#$01
		STA		byte_500+$B,Y
		JSR		sub_B26C
		CMP		#$00
		BEQ		loc_B174
		JMP		sub_B146
; ---------------------------------------------------------------------------
loc_B174:
		JSR		sub_B259
		LDA		#$00
		STA		byte_500+7,Y
		STA		byte_500+7,Y
		LDA		#$01
		STA		byte_500+$10,Y
		LDA		#$06
		STA		byte_500+1,Y
		JSR		sub_B481
		JMP		sub_B2FC

; =============== S U B	R O U T	I N E =======================================
sub_B18F:
		LDA		byte_500+1,Y
		CMP		#$03
		BEQ		loc_B19E
		LDA		#$03
		STA		byte_500+1,Y
		JSR		sub_B481
loc_B19E:
		JSR		sub_B26C
		CMP		#$03
		BEQ		loc_B1AB
		JSR		sub_B551
		JMP		sub_B146
; ---------------------------------------------------------------------------
loc_B1AB:
		JMP		loc_B091

; =============== S U B	R O U T	I N E =======================================
sub_B1AE:
		LDA		#$00
		STA		byte_500+$B,Y
		LDA		byte_500+1,Y
		CMP		#$04
		BEQ		loc_B1D3
		LDA		#$04
		JMP		loc_B1CD

; =============== S U B	R O U T	I N E =======================================
sub_B1BF:
		LDA		#$01
loc_B1C1:
		STA		byte_500+$B,Y
		LDA		byte_500+1,Y
		CMP		#$05
		BEQ		loc_B19E
		LDA		#$05
loc_B1CD:
		STA		byte_500+1,Y
		JSR		sub_B481
loc_B1D3:
		JSR		sub_B551
		JMP		sub_B146

; =============== S U B	R O U T	I N E =======================================
sub_B1D9:
		LDA		byte_500+1,Y
		CMP		#$06
		BEQ		loc_B1F8
		LDA		#$01
		STA		byte_500+$10,Y
		LDA		#$06
		STA		byte_500+1,Y
		JSR		sub_B481
		JSR		sub_B24E
		LDA		#$00
		STA		byte_500+7,Y
		STA		byte_500+8,Y
loc_B1F8:
		JMP		sub_B2FC

; =============== S U B	R O U T	I N E =======================================
sub_B1FB:
		LDA		byte_500+1,Y
		CMP		#$07
		BEQ		loc_B224
		LDA		#$01
		STA		byte_500+$10,Y
		STA		byte_500+2,Y
		LDA		#$00
		STA		byte_500+$B,Y
		LDA		#$07
		STA		byte_500+1,Y
		JSR		sub_B481
		JSR		sub_B24E
		LDA		#$01
		STA		byte_500+7,Y
		LDA		#$00
		STA		byte_500+8,Y
loc_B224:
		JMP		sub_B2FC

; =============== S U B	R O U T	I N E =======================================
sub_B227:
		LDA		byte_500+1,Y
		CMP		#$08
		BEQ		loc_B24B
		LDA		#$01
		STA		byte_500+$10,Y
		STA		byte_500+$B,Y
		LDA		#$08
		STA		byte_500+1,Y
loc_B23B:
		JSR		sub_B481
		JSR		sub_B24E
		LDA		#$FF
		STA		byte_500+7,Y
		LDA		#$00
		STA		byte_500+8,Y
loc_B24B:
		JMP		sub_B2FC

; =============== S U B	R O U T	I N E =======================================
sub_B24E:
		LDA		#$FD
		STA		byte_500+9,Y
		LDA		#$80
		STA		byte_500+$A,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_B259:
		LDA		#$FF
		STA		byte_500+9,Y
		LDA		#$60
		STA		byte_500+$A,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_B264:
		LDA		byte_500+5,Y
		CLC
		ADC		#$26
		BNE		sub_B272

; =============== S U B	R O U T	I N E =======================================
sub_B26C:
		LDA		byte_500+5,Y
		CLC
		ADC		#$1E

; =============== S U B	R O U T	I N E =======================================
sub_B272:
		TAX
		LDA		byte_500+3,Y
		CLC
		ADC		#$08
		JSR		sub_A614
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_B27D:
		LDA		byte_500+$A,Y
		CLC
		ADC		#$1A
		STA		byte_500+$A,Y
		LDA		byte_500+9,Y
		ADC		#$00
		STA		byte_500+9,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_B28F:
		LDA		byte_10
		AND		#$40
		BEQ		loc_B2D4
		LDA		byte_500+$1F,Y
		CMP		#$09
		BCS		loc_B2D9
		LDA		#$05
		JSR		_apu_load_safe
		LDA		byte_500+$10,Y
		BNE		loc_B2A9
		JSR		sub_B551
loc_B2A9:
		JSR		sub_B467
		LDA		byte_500+1,Y
		CMP		#$0A
		BEQ		loc_B2CB
		CMP		#$0B
		BEQ		loc_B2CB
		STA		byte_500+$1E,Y
		CMP		#$03
		BCC		loc_B2C6
		CMP		#$06
		BCS		loc_B2C6
		LDA		#$0B
		BNE		loc_B2C8
loc_B2C6:
		LDA		#$0A
loc_B2C8:
		STA		byte_500+1,Y
loc_B2CB:
		JSR		sub_B481
		LDA		#$0D
		STA		byte_500+$1F,Y
locret_B2D3:
		RTS
; ---------------------------------------------------------------------------
loc_B2D4:
		LDA		byte_500+$1F,Y
		BEQ		locret_B2D3
loc_B2D9:
		LDA		byte_500+$1F,Y
		SEC
		SBC		#$01
		STA		byte_500+$1F,Y
		BNE		locret_B2D3
		LDA		byte_500+$1E,Y
		STA		byte_500+1,Y
		JSR		sub_B481
		LDA		byte_500+$10,Y
		BNE		locret_B2D3
		LDA		#$FF
		STA		byte_500+1,Y
		PLA
		PLA
		JMP		loc_AFEF

; =============== S U B	R O U T	I N E =======================================
sub_B2FC:
		JSR		sub_B4A3

; =============== S U B	R O U T	I N E =======================================
sub_B2FF:
		JSR		sub_B594
		LDA		byte_500+$10,Y
		BNE		loc_B311
		LDA		byte_500,Y
		BMI		loc_B311
		LDA		byte_500+$1B,Y
		BNE		loc_B33F
loc_B311:
		CLC
		LDA		byte_500+8,Y
		ADC		byte_500+4,Y
		STA		byte_500+4,Y
		LDA		byte_500+7,Y
		ADC		byte_500+3,Y
		CMP		#$10
		BCC		loc_B32C
		CMP		#$D8
		BCS		loc_B32C
		STA		byte_500+3,Y
loc_B32C:
		CLC
		LDA		byte_500+$A,Y
		ADC		byte_500+6,Y
		STA		byte_500+6,Y
		LDA		byte_500+9,Y
		ADC		byte_500+5,Y
		STA		byte_500+5,Y
loc_B33F:
		LDA		byte_500+$1D,Y
		CMP		#$04
		BEQ		loc_B36F
		CMP		#$01
		BNE		loc_B362
		LDA		byte_500+$F,Y
		BEQ		loc_B362
		CMP		#$08
		BNE		loc_B358
		LDA		#$02
		JMP		loc_B35C
; ---------------------------------------------------------------------------
loc_B358:
		CMP		#$06
		BCS		loc_B362
loc_B35C:
		CLC
		ADC		#$0E
loc_B35F:
		STA		byte_500+$F,Y
loc_B362:
		LDA		_players_num
		BEQ		loc_B384
		CPY		#$20
		BEQ		loc_B38D
		LDY		#$20
		JMP		loc_ADBC
; ---------------------------------------------------------------------------
loc_B36F:
		LDA		byte_500+$F,Y
		CMP		#$08
		BNE		loc_B37A
		LDA		#$17
		BNE		loc_B35F
loc_B37A:
		CMP		#$06
		BCS		loc_B362
		CLC
		ADC		#$15
		JMP		loc_B35F
; ---------------------------------------------------------------------------
loc_B384:
		LDA		#$81
		CMP		byte_500+3
		BCC		loc_B3BE
		BCS		locret_B3BD
loc_B38D:
		LDA		byte_8
		BNE		locret_B3BD
		LDA		#$81
		CMP		byte_500+3
		BCC		loc_B3A4
loc_B398:
		CMP		byte_523
		BCS		locret_B3BD
		LDX		byte_522
		BEQ		locret_B3BD
		BNE		loc_B3BE
loc_B3A4:
		LDX		byte_500+2
		BEQ		loc_B398
		BNE		loc_B3BE
loc_B3AB:
		LDA		_game_vat49
		CMP		byte_B44A,X
		BNE		loc_B3EC
		LDA		byte_48
		CMP		byte_B450,X
		BCC		loc_B3EC
		LDA		#$01
		STA		byte_6A
locret_B3BD:
		RTS
; ---------------------------------------------------------------------------
loc_B3BE:
		LDX		byte_465
		BNE		loc_B3AB
		LDX		_1p_stage
		LDA		_game_vat49
		CMP		byte_B43E,X
		BNE		loc_B3EC
		LDA		byte_48
		CMP		byte_B444,X
		BCC		loc_B3EC
		LDA		byte_460
		BNE		locret_B3BD
		LDA		#$67
		STA		byte_7F
		JSR		_apu_load_safe
		LDA		#$00
		STA		byte_463
		LDA		#$01
		STA		byte_460
		JMP		locret_B3BD
; ---------------------------------------------------------------------------
loc_B3EC:
		DEC		byte_500+3
		DEC		byte_523
		LDX		#$00
loc_B3F4:
		DEC		byte_543,X
		LDA		byte_543,X
		CMP		#$FF
		BEQ		loc_B422
loc_B3FE:
		TXA
		CLC
		ADC		#$20
		TAX
		BNE		loc_B3F4
loc_B405:
		DEC		byte_65D,X
		CMP		#$FF
		BEQ		loc_B429
		DEC		byte_643,X
		LDA		byte_643,X
		CMP		#$FF
		BEQ		loc_B429
loc_B416:
		TXA
		CLC
		ADC		#$20
		TAX
		CPX		#$C0
		BEQ		loc_B430
		JMP		loc_B405
; ---------------------------------------------------------------------------
loc_B422:
		LDA		#$00
		STA		byte_540,X
		BEQ		loc_B3FE
loc_B429:
		LDA		#$00
		STA		byte_640,X
		BEQ		loc_B416
loc_B430:
		LDA		#$01
		STA		byte_458
		INC		_game_vat49
		BNE		loc_B43B
		INC		byte_48
loc_B43B:
		JMP		locret_B3BD
; ---------------------------------------------------------------------------
byte_B43E:
		.BYTE $FF,$FF,$FF,$FF,$FF,$FF
byte_B444:
		.BYTE $09,$0D,$0C,$0D,$0F,$12
byte_B44A:
		.BYTE $FF,$FF,$FF,$FF,$FF,$FF
byte_B450:
		.BYTE $08,$0C,$0B,$0C,$0E,$11

; =============== S U B	R O U T	I N E =======================================
_get_player_input:
		LDA		_pads_press
		LDX		_pads_held
		CPY		#$00
		BEQ		loc_B462
		LDA		_pads_press+1
		LDX		_pads_held+1
loc_B462:
		STA		byte_10
		STX		byte_11
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_B467:
		LDA		byte_11
		AND		#$0F
		BEQ		locret_B480
		CMP		#$04
		BEQ		locret_B480
		CMP		#$08
		BEQ		locret_B480
		CMP		#$11
		BCS		locret_B480
		TAX
		LDA		byte_B560,X
		STA		byte_500+$B,Y
locret_B480:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_B481:
		LDX		byte_500+1,Y
		LDA		byte_B56B,X
		STA		byte_500+$14,Y
		STA		byte_500+$F,Y
		TAX
		LDA		byte_B585,X
		STA		byte_500+$12,Y
		LDX		byte_500+1,Y
		LDA		byte_B578,X
		STA		byte_500+$15,Y
		LDA		#$00
		STA		byte_500+$13,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_B4A3:
		LDA		byte_500+$1B,Y
		BEQ		loc_B4AB
		JMP		locret_B547
; ---------------------------------------------------------------------------
loc_B4AB:
		LDA		byte_500+$1A,Y
		BEQ		loc_B4D0
		LDA		#$00
		STA		byte_500+$1A,Y
		LDA		byte_500+$10,Y
		BEQ		loc_B4C8
		LDA		#$08
		LDA		byte_500+$F,Y
loc_B4BF:
		STA		byte_500+$14,Y
		STA		byte_500+$15,Y
		JMP		locret_B547
; ---------------------------------------------------------------------------
loc_B4C8:
		LDA		#$FF
		STA		byte_500+1,Y
		JMP		loc_AFEF
; ---------------------------------------------------------------------------
loc_B4D0:
		LDA		byte_500+$12,Y
		CLC
		ADC		byte_500+$13,Y
		STA		byte_500+$13,Y
		BCC		locret_B547
		LDA		byte_500+$1D,Y
		CMP		#$04
		BNE		loc_B4F4
		LDA		byte_500+$F,Y
		CMP		#$16
		BCC		loc_B509
		CMP		#$1A
		BCS		loc_B509
		SEC
		SBC		#$15
		JMP		loc_B50C
; ---------------------------------------------------------------------------
loc_B4F4:
		CMP		#$01
		BNE		loc_B509
		LDA		byte_500+$F,Y
		CMP		#$0F
		BCC		loc_B509
		CMP		#$13
		BCS		loc_B509
		SEC
		SBC		#$0E
		JMP		loc_B50C
; ---------------------------------------------------------------------------
loc_B509:
		LDA		byte_500+$F,Y
loc_B50C:
		CMP		byte_500+$15,Y
		BEQ		loc_B548
		LDA		byte_500+$F,Y
		CLC
		ADC		#$01
		STA		byte_500+$F,Y
loc_B51A:
		LDA		byte_500+$F,Y
		CMP		#$0F
		BCC		loc_B53E
		CMP		#$13
		BCS		loc_B528
		JMP		loc_B537
; ---------------------------------------------------------------------------
loc_B528:
		CMP		#$16
		BCC		loc_B53E
		CMP		#$1A
		BCS		loc_B53E
		SEC
		SBC		#$15
		TAX
		JMP		loc_B541
; ---------------------------------------------------------------------------
loc_B537:
		SEC
		SBC		#$0E
		TAX
		JMP		loc_B541
; ---------------------------------------------------------------------------
loc_B53E:
		LDX		byte_500+$F,Y
loc_B541:
		LDA		byte_B585,X
		STA		byte_500+$12,Y
locret_B547:
		RTS
; ---------------------------------------------------------------------------
loc_B548:
		LDA		byte_500+$14,Y
		STA		byte_500+$F,Y
		JMP		loc_B51A

; =============== S U B	R O U T	I N E =======================================
sub_B551:
		LDA		#$00
		STA		byte_500+7,Y
		STA		byte_500+8,Y
		STA		byte_500+9,Y
		STA		byte_500+$A,Y
		RTS
; ---------------------------------------------------------------------------
byte_B560:
		.BYTE $00,$00,$01,$00,$00,$00,$01,$00,$00,$00,$01
byte_B56B:
		.BYTE $01,$01,$01,$05,$05,$05,$08,$08,$08,$06,$09,$0B,$0D
byte_B578:
		.BYTE $04,$04,$04,$05,$05,$05,$08,$08,$08,$07,$0A,$0C,$0E
byte_B585:
		.BYTE $00,$20,$30,$20,$30,$00,$18,$18,$00,$48,$00,$48,$00,$08,$00

; =============== S U B	R O U T	I N E =======================================
sub_B594:
		LDX		#$00
		CPY		#$00
		BEQ		loc_B59C
		LDX		#$20
loc_B59C:
		LDA		byte_500,Y
		BMI		locret_B5B1
		LDA		byte_500+$1B,Y
		BEQ		loc_B5AC
		SEC
		SBC		#$01
		STA		byte_500+$1B,Y
loc_B5AC:
		LDA		byte_500+$1D,Y
		BNE		loc_B5B2
locret_B5B1:
		RTS
; ---------------------------------------------------------------------------
loc_B5B2:
		CMP		#$03
		BEQ		locret_B5B1
		LDA		byte_500+$16,Y
		BEQ		loc_B5E3
		LDA		_frames_counter
		AND		#$03
		BNE		loc_B5E3
		LDA		byte_500+$16,Y
		SEC
		SBC		#$01
		STA		byte_500+$16,Y
		BNE		loc_B5E3
		JSR		sub_B7A5
		LDA		byte_500+$F,Y
		CMP		#$16
		BCC		loc_B5E8
		CMP		#$1B
		BCS		loc_B5E8
		SEC
		SBC		#$15
		STA		byte_500+$F,Y
		JMP		locret_B67D
; ---------------------------------------------------------------------------
loc_B5E3:
		LDA		byte_500+$11,Y
		BEQ		loc_B5EB
loc_B5E8:
		JMP		locret_B67D
; ---------------------------------------------------------------------------
loc_B5EB:
		LDA		byte_6C0,X
		BNE		loc_B5E8
		LDA		byte_10
		BPL		loc_B5E8
		LDA		#$01
		STA		byte_6C0,X
		LDA		#$00
		STA		byte_6D2,X
		LDA		byte_500+$B,Y
		STA		byte_6CB,X
		LDA		byte_500+$1D,Y
		CMP		#$03
		BEQ		locret_B67D
		CMP		#$04
		BNE		loc_B612
		JMP		loc_B748
; ---------------------------------------------------------------------------
loc_B612:
		CMP		#$01
		BEQ		loc_B67E
		LDA		#$09
		JSR		_apu_load_safe
		LDA		#$01
		STA		byte_6C1,X
		LDA		byte_6CB,X
		BEQ		loc_B628
		JMP		loc_B70F
; ---------------------------------------------------------------------------
loc_B628:
		LDA		#$01
		STA		byte_6C7,X
		LDA		#$80
		STA		byte_6C8,X
		LDA		byte_500+3,Y
		CLC
		ADC		#$08
loc_B638:
		STA		byte_6C3,X
		LDA		byte_500+5,Y
		SEC
		SBC		#$0A
		STA		byte_6C5,X
		LDA		byte_500+$F,Y
		CMP		#$05
		BNE		loc_B654
		LDA		byte_6C5,X
		CLC
		ADC		#$13
		STA		byte_6C5,X
loc_B654:
		LDA		#$38
		STA		byte_6CF,X
		LDA		#$01
		STA		byte_6CE,X
		LDA		#$FE
		STA		byte_6C9,X
		LDA		#$20
		STA		byte_6CA,X
		LDA		#$18
		STA		byte_500+$1B,Y
loc_B66D:
		LDA		byte_500+$1C,Y
		SEC
		SBC		#$01
		STA		byte_500+$1C,Y
		BNE		locret_B67D
		LDA		#$00
		STA		byte_500+$1D,Y
locret_B67D:
		RTS
; ---------------------------------------------------------------------------
loc_B67E:
		LDA		#$13
		JSR		_apu_load_safe
		LDA		#$00
		STA		byte_6C1,X
		LDA		byte_6CB,X
		BEQ		loc_B690
		JMP		loc_B722
; ---------------------------------------------------------------------------
loc_B690:
		LDA		#$01
		STA		byte_6C7,X
		LDA		#$C0
		STA		byte_6C8,X
		LDA		byte_500+3,Y
		CLC
		ADC		#$10
loc_B6A0:
		STA		byte_6C3,X
		LDA		#$00
		STA		byte_6DB,X
		LDA		byte_500+5,Y
		SEC
		SBC		#$06
		STA		byte_6C5,X
		LDA		byte_500+$F,Y
		CMP		#$0B
		BCC		loc_B6CE
		CMP		#$0D
		BCC		loc_B6C0
		CMP		#$13
		BNE		loc_B6CE
loc_B6C0:
		LDA		byte_6C5,X
		CLC
		ADC		#$0F
		STA		byte_6C5,X
		LDA		#$01
		STA		byte_6DB,X
loc_B6CE:
		LDA		#$3E
		STA		byte_6CF,X
		LDA		#$01
		STA		byte_6CE,X
		LDA		#$00
		STA		byte_6C9,X
		STA		byte_6CA,X
		LDA		byte_500+$F,Y
		STA		byte_500+$1B,Y
		LDA		#$18
		STA		byte_500+$1B,Y
		LDA		byte_500+$F,Y
		CMP		#$13
		BEQ		loc_B70C
		CMP		#$09
		BCC		loc_B702
		CMP		#$0B
		BCC		loc_B702
		CMP		#$0D
		BCS		loc_B702
		LDA		#$13
		BNE		loc_B704
loc_B702:
		LDA		#$14
loc_B704:
		STA		byte_500+$F,Y
		LDA		#$01
		STA		byte_500+$1A,Y
loc_B70C:
		JMP		loc_B66D
; ---------------------------------------------------------------------------
loc_B70F:
		LDA		#$FE
		STA		byte_6C7,X
		LDA		#$80
		STA		byte_6C8,X
		LDA		byte_500+3,Y
		CLC
		ADC		#$00
		JMP		loc_B638
; ---------------------------------------------------------------------------
loc_B722:
		LDA		#$FE
		STA		byte_6C7,X
		LDA		#$40
		STA		byte_6C8,X
		LDA		byte_500+3,Y
		SEC
		SBC		#$08
		JMP		loc_B6A0
; ---------------------------------------------------------------------------
loc_B735:
		LDA		#$FC
		STA		byte_6C7,X
		LDA		#$00
		STA		byte_6C8,X
		LDA		byte_500+3,Y
		SEC
		SBC		#$0E
		JMP		loc_B771
; ---------------------------------------------------------------------------
loc_B748:
		LDA		#$0B
		JSR		_apu_load_safe
		LDA		#$00
		STA		byte_6C9,X
		STA		byte_6CA,X
		LDA		#$04
		STA		byte_6C1,X
		LDA		byte_6CB,X
		BEQ		loc_B761
		BNE		loc_B735
loc_B761:
		LDA		#$04
		STA		byte_6C7,X
		LDA		#$00
		STA		byte_6C8,X
		LDA		byte_500+3,Y
		CLC
		ADC		#$16
loc_B771:
		STA		byte_6C3,X
		LDA		byte_500+1,Y
		CMP		#$0B
		BEQ		loc_B783
		CMP		#$03
		BCC		loc_B78C
		CMP		#$06
		BCS		loc_B78C
loc_B783:
		LDA		byte_500+5,Y
		CLC
		ADC		#$16
		JMP		loc_B792
; ---------------------------------------------------------------------------
loc_B78C:
		LDA		byte_500+5,Y
		CLC
		ADC		#$04
loc_B792:
		STA		byte_6C5,X
		LDA		#$01
		STA		byte_6CE,X
		LDA		#$56
		STA		byte_6CF,X
		LDA		#$14
		STA		byte_6D0,X
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_B7A5:
		LDA		byte_500+$1C,Y
		BNE		loc_B7AE
		STA		byte_500+$1D,Y
		RTS
; ---------------------------------------------------------------------------
loc_B7AE:
		STA		byte_C
		JSR		sub_8D8C
		LDA		byte_C
		STA		byte_500+$1C,Y
		LDA		byte_500+$1D,Y
		BEQ		loc_B7C1
		CMP		#$03
		BCC		locret_B7D0
loc_B7C1:
		LDA		_1p_stage
		CMP		#$05
		BNE		loc_B7CB
		LDA		#$01
		BNE		loc_B7CD
loc_B7CB:
		LDA		#$02
loc_B7CD:
		STA		byte_500+$1D,Y
locret_B7D0:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_B7D1:
		LDA		byte_460
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD sub_B936
		.WORD sub_B7E1
		.WORD sub_B7F8
		.WORD sub_B8D2
		.WORD sub_B8FE

; =============== S U B	R O U T	I N E =======================================
sub_B7E1:
		LDA		#$00
		STA		byte_45C
		LDA		#$F0
		STA		byte_45D
		LDA		#$03
		STA		byte_466
		LDA		#$02
		STA		byte_460
		JMP		sub_B941

; =============== S U B	R O U T	I N E =======================================
sub_B7F8:
		LDA		byte_466
		BEQ		loc_B80B
		LDA		_frames_counter
		AND		#$3F
		BNE		loc_B80B
		LDA		#$19
		JSR		_apu_load_safe
		DEC		byte_466
loc_B80B:
		DEC		byte_45D
		BNE		loc_B85E
		LDA		byte_463
		BNE		loc_B840
		LDA		#$67
		JSR		_apu_load_safe
		LDA		#$50
		LDX		_1p_stage
		CPX		#$05
		BEQ		loc_B824
		LDA		#$4A
loc_B824:
		STA		byte_7F
		STA		byte_6C
		LDA		_players_num
		BNE		loc_B836
		LDA		byte_A2
		CMP		#$6A
		BEQ		loc_B83B
		LDA		byte_5D
		BNE		loc_B83B
loc_B836:
		LDA		byte_6C
		JSR		_apu_load_safe
loc_B83B:
		LDA		#$01
		STA		byte_463
loc_B840:
		LDA		_1p_stage
		ASL
		TAX
		LDA		off_B8C6,X
		STA		byte_10
		LDA		off_B8C6+1,X
		STA		byte_11
		LDY		byte_45C
		LDA		(byte_10),Y
		CMP		#$FE
		BEQ		sub_B7E1
		CMP		#$FF
		BNE		loc_B861
		INC		byte_460
loc_B85E:
		JMP		loc_B8BA
; ---------------------------------------------------------------------------
loc_B861:
		STA		byte_45D
		INY
		LDA		(byte_10),Y
		CMP		#$F0
		BCC		loc_B87A
		BEQ		loc_B872
		LDA		#$54
		JMP		loc_B874
; ---------------------------------------------------------------------------
loc_B872:
		LDA		#$53
loc_B874:
		JSR		_apu_load_safe
		INY
		LDA		(byte_10),Y
loc_B87A:
		INY
		STY		byte_45C
		STA		byte_12
		LDX		#$00
loc_B882:
		LDA		byte_540,X
		BEQ		loc_B891
		TXA
		CLC
		ADC		#$20
		BEQ		loc_B8BA
		TAX
		JMP		loc_B882
; ---------------------------------------------------------------------------
loc_B891:
		LDA		byte_12
		STA		byte_541,X
		LDA		#$01
		STA		byte_540,X
		LDA		#$00
		STA		byte_550,X
		STA		byte_551,X
		LDA		byte_541,X
		CMP		#$0A
		BEQ		loc_B8AE
		CMP		#$0B
		BNE		loc_B8B2
loc_B8AE:
		LDA		#$40
		BNE		loc_B8B4
loc_B8B2:
		LDA		#$AE
loc_B8B4:
		STA		byte_545,X
		JSR		sub_C0B2
loc_B8BA:
		LDA		_1p_stage
		CMP		#$05
		BEQ		loc_B8C3
		JMP		sub_B941
; ---------------------------------------------------------------------------
loc_B8C3:
		JMP		sub_B8D2
; ---------------------------------------------------------------------------
off_B8C6:
		.WORD _stage1_dataA
		.WORD _stage2_dataA
		.WORD _stage3_dataA
		.WORD _stage4_dataA
		.WORD _stage5_dataA
		.WORD _stage6_dataA

; =============== S U B	R O U T	I N E =======================================
sub_B8D2:
		LDX		#$08
		LDY		#$00
loc_B8D6:
		LDA		byte_540,Y
		BEQ		loc_B8DF
		CMP		#$86
		BNE		sub_B941
loc_B8DF:
		TYA
		CLC
		ADC		#$20
		TAY
		DEX
		BNE		loc_B8D6
		LDA		_1p_stage
		CMP		#$05
		BNE		loc_B8F1
		LDA		#$A0
		BNE		loc_B8F3
loc_B8F1:
		LDA		#$40
loc_B8F3:
		STA		byte_45D
		LDA		#$04
		STA		byte_460
		JMP		sub_B941

; =============== S U B	R O U T	I N E =======================================
sub_B8FE:
		LDA		_frames_counter
		AND		#$01
		BNE		loc_B933
		DEC		byte_45D
		BNE		loc_B933
		TYA
		PHA
		LDY		#$00
		JSR		sub_8DA6
		LDA		byte_67
		CMP		#$03
		BCC		loc_B91C
		LDA		#$00
		STA		byte_66
		STA		byte_67
loc_B91C:
		LDY		#$20
		JSR		sub_8DA6
		LDA		byte_69
		CMP		#$03
		BCC		loc_B92D
		LDA		#$00
		STA		byte_68
		STA		byte_69
loc_B92D:
		PLA
		TAY
		LDA		#$07
		STA		_main_sub_idx
loc_B933:
		JMP		sub_B941

; =============== S U B	R O U T	I N E =======================================
sub_B936:
		JSR		sub_C426
		LDA		byte_458
		BEQ		sub_B941
		JMP		_stage_object_manager

; =============== S U B	R O U T	I N E =======================================
sub_B941:
		LDY		#$00

; =============== S U B	R O U T	I N E =======================================
sub_B943:
		LDA		byte_540,Y
		BNE		sub_B94B
		JMP		sub_C031

; =============== S U B	R O U T	I N E =======================================
sub_B94B:
		BMI		sub_B950
		JMP		sub_BAEC

; =============== S U B	R O U T	I N E =======================================
sub_B950:
		AND		#$0F
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD sub_B963
		.WORD sub_B9A3
		.WORD sub_BA51
		.WORD sub_BA77
		.WORD sub_BA8E
		.WORD sub_BA9C
		.WORD sub_BAB5

; =============== S U B	R O U T	I N E =======================================
sub_B963:
		LDA		#$2D
		STA		byte_55F,Y
		LDA		#$02
		LDX		byte_541,Y
		CPX		#$14
		BNE		loc_B973
		LDA		#$15
loc_B973:
		STA		byte_541,Y
		LDA		#$07
		JSR		_apu_load_safe
		LDA		word_0
		STA		byte_550,Y
		STA		byte_551,Y
		LDA		byte_545,Y
		SEC
		SBC		#$0A
		STA		byte_545,Y
		JSR		sub_C2BB
		LDA		#$FD
		STA		byte_549,Y
loc_B994:
		LDA		byte_540,Y
		CLC
		ADC		#$01
		STA		byte_540,Y
		JSR		sub_C2CA
		JMP		sub_C02E

; =============== S U B	R O U T	I N E =======================================
sub_B9A3:
		LDA		byte_54A,Y
		CLC
		ADC		#$26
		STA		byte_54A,Y
		LDA		byte_549,Y
		ADC		#$00
		STA		byte_549,Y
loc_B9B4:
		LDA		byte_55F,Y
		SEC
		SBC		#$01
		STA		byte_55F,Y
		BNE		loc_BA26
		LDA		#$00
		STA		byte_540,Y
		LDA		byte_557,Y
		BEQ		loc_BA23
		LDA		byte_543,Y
		CMP		#$F0
		BCS		loc_BA23
		CLC
		ADC		#$08
		JSR		sub_A608
		LDA		byte_543,Y
		CLC
		ADC		#$10
		JSR		sub_A608
		JSR		sub_A6B9
		STX		byte_C
		STA		byte_D
		LDA		#$25
		STA		byte_F
		JSR		sub_BA29
		LDA		byte_D
		CLC
		ADC		#$20
		STA		byte_D
		JSR		sub_BA29
		LDA		byte_D
		SEC
		SBC		#$20
		CMP		#$5F
		BNE		loc_BA0D
		LDA		#$00
		STA		byte_D
		LDA		byte_C
		AND		#$04
		STA		byte_C
		JMP		loc_BA12
; ---------------------------------------------------------------------------
loc_BA0D:
		CLC
		ADC		#$01
		STA		byte_D
loc_BA12:
		LDA		#$26
		STA		byte_F
		JSR		sub_BA29
		LDA		byte_D
		CLC
		ADC		#$20
		STA		byte_D
		JSR		sub_BA29
loc_BA23:
		JMP		sub_C031
; ---------------------------------------------------------------------------
loc_BA26:
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_BA29:
		LDX		_ppu_queue_pos
		LDA		#$01
		STA		_ppu_queue_buf,X
		INX
		LDA		byte_C
		STA		_ppu_queue_buf,X
		INX
		LDA		byte_D
		STA		_ppu_queue_buf,X
		INX
		LDA		byte_F
		STA		_ppu_queue_buf,X
		INX
		LDA		#$FF
		STA		_ppu_queue_buf,X
		INX
		LDA		#$00
		STA		_ppu_queue_buf,X
		STX		_ppu_queue_pos
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_BA51:
		LDA		#$15
		JSR		_apu_load_safe
		JSR		sub_C2BB
		LDA		byte_545,Y
		CLC
		ADC		#$20
		STA		byte_545,Y
		LDA		#$02
		STA		byte_54E,Y
		LDA		#$12
		STA		byte_55F,Y
		LDA		#$07
		STA		byte_541,Y
		JSR		sub_C2BB
		JMP		loc_B994

; =============== S U B	R O U T	I N E =======================================
sub_BA77:
		LDA		byte_55F,Y
		CMP		#$05
		BNE		loc_BA8B
		LDA		#$2D
		STA		byte_54F,Y
		LDA		#$00
		STA		byte_552,Y
		STA		byte_553,Y
loc_BA8B:
		JMP		loc_B9B4

; =============== S U B	R O U T	I N E =======================================
sub_BA8E:
		LDA		#$B8
		STA		byte_543,Y
		LDA		#$02
		CLC
		ADC		byte_540,Y
		JMP		loc_BAA7

; =============== S U B	R O U T	I N E =======================================
sub_BA9C:
		LDA		#$B0
		STA		byte_543,Y
		LDA		#$01
		CLC
		ADC		byte_540,Y
loc_BAA7:
		STA		byte_540,Y
		LDA		#$02
		STA		byte_54E,Y
		JSR		sub_C2BB
		JMP		sub_C031

; =============== S U B	R O U T	I N E =======================================
sub_BAB5:
		LDA		_frames_counter
		AND		#$0F
		BNE		loc_BAC0
		LDA		#$15
		JSR		_apu_load_safe
loc_BAC0:
		LDA		byte_55F,Y
		SEC
		SBC		#$01
		STA		byte_55F,Y
		BNE		loc_BAE9
		LDA		#$0C
		STA		byte_55F,Y
		LDA		byte_54F,Y
		CMP		#$1B
		BCS		loc_BADB
		LDA		#$1B
		BNE		loc_BAE6
loc_BADB:
		CMP		#$1D
		BCS		loc_BAE4
		CLC
		ADC		#$01
		BNE		loc_BAE6
loc_BAE4:
		LDA		#$1C
loc_BAE6:
		STA		byte_54F,Y
loc_BAE9:
		JMP		sub_C031

; =============== S U B	R O U T	I N E =======================================
sub_BAEC:
		LDA		_frames_counter
		AND		#$03
		CMP		#$03
		BNE		loc_BAFF
		LDA		byte_54D,Y
		BEQ		loc_BAFF
		SEC
		SBC		#$01
		STA		byte_54D,Y
loc_BAFF:
		LDA		byte_550,Y
		BEQ		loc_BB07
		JMP		loc_BF66
; ---------------------------------------------------------------------------
loc_BB07:
		LDA		byte_551,Y
		BEQ		loc_BB0F
		JMP		sub_BEFC
; ---------------------------------------------------------------------------
loc_BB0F:
		LDA		byte_541,Y
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD sub_BB5D
		.WORD sub_BB5D
		.WORD sub_BB5D
		.WORD sub_BB83
		.WORD sub_BB5D
		.WORD sub_BBDD
		.WORD sub_BC32
		.WORD sub_BB5D
		.WORD sub_BC4A
		.WORD sub_BB5D
		.WORD sub_BD26
		.WORD sub_BD49
		.WORD sub_BD49
		.WORD sub_BB5D
		.WORD sub_BB5D
off_BB33:
		.WORD sub_BD73
		.WORD sub_BD73
		.WORD sub_2BD41
		.WORD sub_2BDD4
		.WORD sub_2BE0E
		.WORD sub_34386
		.WORD sub_34386
		.WORD sub_BDD8
		.WORD sub_3BFAF
		.WORD sub_3C018
		.WORD sub_BD49
		.WORD sub_BD49
		.WORD sub_BB5D
		.WORD sub_BB5D
		.WORD sub_BD73
		.WORD sub_BD73
		.WORD sub_4C23D
		.WORD sub_4C279
		.WORD sub_4C288
		.WORD sub_4C37F
		.WORD sub_4C39C

; =============== S U B	R O U T	I N E =======================================
sub_BB5D:
		JSR		sub_BE99
		CMP		#$00
		BEQ		sub_BB67
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_BB67:
		LDA		byte_541,Y
		STA		byte_55E,Y
		LDA		#$00
		STA		byte_552,Y
		LDA		byte_465
		BEQ		loc_BB7D
		JSR		sub_BED0
		JMP		sub_BFEA
; ---------------------------------------------------------------------------
loc_BB7D:
		JSR		sub_BEC0
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_BB83:
		LDX		#$00

; =============== S U B	R O U T	I N E =======================================
sub_BB85:
		LDA		byte_500,X
		BEQ		loc_BB99
		LDA		byte_545,Y
		SEC
		SBC		byte_500+5,X
		BEQ		loc_BBA5
		BCC		loc_BB99
		CMP		#$28
		BCC		loc_BBA5
loc_BB99:
		CPX		#$20
		BEQ		sub_BB5D
		TXA
		CLC
		ADC		#$20
		TAX
		JMP		sub_BB85
; ---------------------------------------------------------------------------
loc_BBA5:
		LDA		byte_543,Y
		SEC
		SBC		byte_500+3,X
		STA		word_0
		BCS		loc_BBB5
		EOR		#$FF
		CLC
		ADC		#$01
loc_BBB5:
		CMP		#$2C
		BCS		loc_BB99
		LDA		byte_54B,Y
		BNE		loc_BBC5
		LDA		word_0
		BPL		loc_BB99
		JMP		loc_BBC9
; ---------------------------------------------------------------------------
loc_BBC5:
		LDA		word_0
		BMI		loc_BB99
loc_BBC9:
		LDA		byte_541,Y
		STA		byte_55E,Y
		LDA		#$04
		STA		byte_541,Y
		JSR		sub_C2CA
		JSR		sub_BED0
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_BBDD:
		LDX		#$00
		LDA		byte_54C,Y
		BEQ		loc_BBE6
		LDX		#$20
loc_BBE6:
		LDA		byte_543,Y
		SEC
		SBC		byte_500+3,X
		BCS		loc_BBF4
		LDA		#$00
		JMP		loc_BBF6
; ---------------------------------------------------------------------------
loc_BBF4:
		LDA		#$01
loc_BBF6:
		STA		byte_54B,Y
		LDA		byte_543,Y
		SEC
		SBC		byte_500+3,X
		BCS		loc_BC07
		EOR		#$FF
		CLC
		ADC		#$01
loc_BC07:
		CMP		#$20
		BCC		loc_BC2F
		LDA		byte_55D,Y
		SEC
		SBC		#$01
		STA		byte_55D,Y
		BNE		loc_BC2F
		LDA		_1p_stage
		CMP		#$01
		BNE		loc_BC27
		JSR		sub_C51B
		LDA		#$80
		STA		byte_55D,Y
		JMP		loc_BC2F
; ---------------------------------------------------------------------------
loc_BC27:
		JSR		sub_C523
		LDA		#$A0
		STA		byte_55D,Y
loc_BC2F:
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_BC32:
		LDA		_frames_counter
		AND		#$07
		BNE		loc_BC47
		LDA		byte_54E,Y
		TAX
		CMP		#$03
		BNE		loc_BC42
		LDX		#$00
loc_BC42:
		INX
		TXA
		STA		byte_54E,Y
loc_BC47:
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_BC4A:
		LDA		byte_54D,Y
		BNE		loc_BC52
		JMP		sub_BB5D
; ---------------------------------------------------------------------------
loc_BC52:
		JSR		sub_BE99
		CMP		#$00
		BEQ		loc_BC9D
		JSR		sub_BE3A
		LDX		byte_8
		LDA		byte_543,Y
		CMP		#$30
		BCC		loc_BC80
		CMP		#$D8
		BCS		loc_BC80
		LDA		byte_545,Y
		CMP		byte_500+$D,X
		BEQ		loc_BCAE
		BCC		loc_BC83
		JSR		sub_BEAE
		CMP		#$02
		BNE		loc_BC7D
		JSR		sub_BED0
loc_BC7D:
		JMP		loc_BD23
; ---------------------------------------------------------------------------
loc_BC80:
		JMP		loc_BCF1
; ---------------------------------------------------------------------------
loc_BC83:
		JSR		sub_BE99
		CMP		#$03
		BNE		loc_BC7D
		JSR		sub_C2BB
		LDA		#$01
		STA		byte_549,Y
		LDA		#$20
		STA		byte_54A,Y
		JSR		sub_BEE0
		JMP		loc_BD23
; ---------------------------------------------------------------------------
loc_BC9D:
		LDA		byte_541,Y
		STA		byte_55E,Y
		LDA		#$00
		STA		byte_552,Y
		JSR		sub_BEC0
		JMP		loc_BD23
; ---------------------------------------------------------------------------
loc_BCAE:
		LDA		byte_55D,Y
		BEQ		loc_BCBB
		SEC
		SBC		#$01
		STA		byte_55D,Y
		BNE		loc_BCF1
loc_BCBB:
		LDA		byte_543,Y
		SEC
		SBC		byte_500+3,X
		LDX		#$01
		BCS		loc_BCCD
		EOR		#$FF
		CLC
		ADC		#$01
		LDX		#$00
loc_BCCD:
		STX		byte_9
		CMP		#$38
		BCC		loc_BCF1
		JSR		sub_C2BB
		LDA		byte_541,Y
		STA		byte_55E,Y
		LDA		#$0A
		STA		byte_541,Y
		LDA		#$20
		STA		byte_55D,Y
		LDA		byte_9
		STA		byte_54B,Y
		JSR		sub_C2CA
		JMP		loc_BD23
; ---------------------------------------------------------------------------
loc_BCF1:
		LDX		byte_543,Y
		LDA		byte_54B,Y
		BEQ		loc_BD0D
		CPX		#$08
		BCS		loc_BD23
		JSR		sub_C2BB
		LDA		#$01
		STA		byte_547,Y
		LDA		#$20
		STA		byte_548,Y
		JMP		loc_BD1B
; ---------------------------------------------------------------------------
loc_BD0D:
		CPX		#$F0
		BCC		loc_BD23
		LDA		#$FE
		STA		byte_547,Y
		LDA		#$E0
		STA		byte_548,Y
loc_BD1B:
		LDA		byte_54B,Y
		EOR		#$01
		STA		byte_54B,Y
loc_BD23:
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_BD26:
		LDA		byte_55D,Y
		SEC
		SBC		#$01
		STA		byte_55D,Y
		BEQ		loc_BD3B
		CMP		#$0C
		BNE		loc_BD46
		JSR		sub_C523
		JMP		loc_BD46
; ---------------------------------------------------------------------------
loc_BD3B:
		LDA		byte_543,Y
		PHA
loc_BD3F:
		JSR		sub_C1A8
		PLA
		STA		byte_543,Y
loc_BD46:
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_BD49:
		LDA		byte_55F,Y
		SEC
		SBC		#$01
		STA		byte_55F,Y
		BNE		loc_BD70
		LDA		byte_541,Y
		CLC
		ADC		#$02
		STA		byte_541,Y
		STA		byte_55E,Y
		JSR		sub_C2CA
		LDA		byte_543,Y
		PHA
		LDA		#$20
		JSR		sub_C24C
		PLA
		STA		byte_543,Y
loc_BD70:
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_BD73:
		LDA		_frames_counter
		AND		#$03
		CMP		#$03
		BNE		loc_BD8B
		LDA		byte_54E,Y
		CMP		#$01
		BNE		loc_BD86
		LDA		#$03
		BNE		loc_BD88
loc_BD86:
		LDA		#$01
loc_BD88:
		STA		byte_54E,Y
loc_BD8B:
		LDA		byte_545,Y
		CMP		#$2A
		BCC		loc_BDA2
		LDA		byte_549,Y
		BMI		loc_BDA2
		JSR		sub_BE99
		CMP		#$01
		BEQ		loc_BDD2
		CMP		#$03
		BEQ		loc_BDD2
loc_BDA2:
		LDA		byte_543,Y
		CMP		#$D7
		BCC		loc_BDBE
		LDA		byte_547,Y
		BMI		loc_BDBE
		EOR		#$FF
		STA		byte_547,Y
		LDA		byte_548,Y
		EOR		#$FF
		CLC
		ADC		#$01
		STA		byte_548,Y
loc_BDBE:
		LDA		byte_54A,Y
		CLC
		ADC		#$1E
		STA		byte_54A,Y
		LDA		byte_549,Y
		ADC		#$00
		STA		byte_549,Y
		JMP		loc_BDD5
; ---------------------------------------------------------------------------
loc_BDD2:
		JSR		sub_C2BB
loc_BDD5:
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_BDD8:
		JSR		sub_BE99
		AND		#$01
		BEQ		loc_BDF8
		LDA		#$00
		STA		byte_550,Y
		STA		byte_551,Y
		JSR		sub_C2BB
		LDA		byte_543,Y
		PHA
		JSR		sub_C1A0
		PLA
		STA		byte_543,Y
		JMP		loc_BE37
; ---------------------------------------------------------------------------
loc_BDF8:
		LDA		byte_548,Y
		CLC
		ADC		#$05
		STA		byte_548,Y
		LDA		byte_547,Y
		ADC		#$00
		STA		byte_547,Y
		LDX		#$00
		LDA		byte_54C,Y
		BEQ		loc_BE12
		LDX		#$20
loc_BE12:
		LDA		byte_543,Y
		SEC
		SBC		byte_500+3,X
		BCC		loc_BE1F
		LDA		#$01
		BNE		loc_BE21
loc_BE1F:
		LDA		#$00
loc_BE21:
		STA		byte_54B,Y
		LDA		byte_55D,Y
		SEC
		SBC		#$01
		STA		byte_55D,Y
		BNE		loc_BE37
		LDA		#$48
		STA		byte_55D,Y
		JSR		sub_C51B
loc_BE37:
		JMP		sub_BFEA

; =============== S U B	R O U T	I N E =======================================
sub_BE3A:
		LDA		byte_500
		BEQ		loc_BE91
		LDX		#$00
		LDA		byte_520
		BEQ		loc_BE93
		LDA		byte_500+3
		SEC
		SBC		byte_543,Y
		BCS		loc_BE54
		EOR		#$FF
		CLC
		ADC		#$01
loc_BE54:
		STA		byte_9
		LDA		byte_500+$D
		SEC
		SBC		byte_545,Y
		BCS		loc_BE64
		EOR		#$FF
		CLC
		ADC		#$01
loc_BE64:
		CLC
		ADC		byte_9
		STA		byte_9
		LDA		byte_523
		SEC
		SBC		byte_543,Y
		BCS		loc_BE77
		EOR		#$FF
		CLC
		ADC		#$01
loc_BE77:
		STA		byte_A
		LDA		byte_52D
		SEC
		SBC		byte_545,Y
		BCS		loc_BE87
		EOR		#$FF
		CLC
		ADC		#$01
loc_BE87:
		CLC
		ADC		byte_A
		LDX		#$00
		SEC
		SBC		byte_9
		BCS		loc_BE93
loc_BE91:
		LDX		#$20
loc_BE93:
		STX		byte_8
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_BE96:
		LDA		#$01
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_BE99:
		LDA		byte_545,Y
		CMP		#$AE
		BCS		sub_BE96
		CLC
		ADC		#$1E

; =============== S U B	R O U T	I N E =======================================
sub_BEA3:
		TAX
		LDA		byte_543,Y
		CLC
		ADC		#$08
		JSR		sub_A614
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_BEAE:
		LDA		byte_545,Y
		CLC
		ADC		#$03
		JMP		sub_BEA3

; =============== S U B	R O U T	I N E =======================================
sub_BEB7:
		LDA		byte_545,Y
		CLC
		ADC		#$25
		JMP		sub_BEA3

; =============== S U B	R O U T	I N E =======================================
sub_BEC0:
		LDA		#$01
		STA		byte_550,Y
		LDA		#$FF
		STA		byte_549,Y
		LDA		#$60
		STA		byte_54A,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_BED0:
		LDA		#$01
		STA		byte_550,Y
		LDA		#$FD
		STA		byte_549,Y
		LDA		#$C0
		STA		byte_54A,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_BEE0:
		LDA		#$00
		STA		byte_550,Y
		STA		byte_54B,Y
		LDA		#$01
		STA		byte_551,Y
		LDA		byte_541,Y
		STA		byte_55E,Y
		LDA		#$09
		STA		byte_541,Y
		JSR		sub_C2CA
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_BEFC:
		LDA		byte_549,Y
		BMI		loc_BF0B
loc_BF01:
		JSR		sub_BE99
		CMP		#$01
		BEQ		loc_BF2C
		JMP		sub_BFEA
; ---------------------------------------------------------------------------
loc_BF0B:
		LDA		byte_545,Y
		CMP		#$2F
		BCS		loc_BF1E
		LDA		#$01
		STA		byte_549,Y
		LDA		#$20
		STA		byte_54A,X
		BNE		loc_BF01
loc_BF1E:
		JSR		sub_BE99
		CMP		#$01
		BEQ		loc_BF2C
		CMP		#$03
		BEQ		loc_BF2C
		JMP		sub_BFEA
; ---------------------------------------------------------------------------
loc_BF2C:
		JSR		sub_C2BB
		JSR		sub_BE3A
		LDX		byte_8
		LDA		byte_500+3,X
		SEC
		SBC		byte_543,Y
		BCS		loc_BF4F
		LDA		#$01
		STA		byte_54B,Y
		LDA		#$FE
		STA		byte_547,Y
		LDA		#$F0
		STA		byte_548,Y
		JMP		loc_BF5E
; ---------------------------------------------------------------------------
loc_BF4F:
		LDA		#$00
		STA		byte_54B,Y
		LDA		#$01
		STA		byte_547,Y
		LDA		#$10
		STA		byte_548,Y
loc_BF5E:
		LDA		#$00
		STA		byte_551,Y
		JMP		loc_BFA3
; ---------------------------------------------------------------------------
loc_BF66:
		LDA		byte_54A,Y
		CLC
		ADC		#$1E
		STA		byte_54A,Y
		LDA		byte_549,Y
		ADC		#$00
		STA		byte_549,Y
		LDA		byte_55E,Y
		CMP		#$08
		BNE		loc_BF93
		JSR		sub_BE99
		CMP		#$02
		BNE		loc_BF96
		JSR		sub_C2BB
		LDA		#$FF
		STA		byte_549,Y
		JSR		sub_BEE0
		JMP		sub_BFEA
; ---------------------------------------------------------------------------
loc_BF93:
		JSR		sub_BE99
loc_BF96:
		CMP		#$01
		BEQ		loc_BF9E
		CMP		#$03
		BNE		sub_BFEA
loc_BF9E:
		LDA		#$00
		STA		byte_550,Y
loc_BFA3:
		LDA		byte_55E,Y
		STA		byte_541,Y
		JSR		sub_C2CA
		LDA		byte_545,Y
		AND		#$0F
		CMP		#$06
		BCS		loc_BFC1
		LDA		byte_545,Y
		SEC
		SBC		#$10
		STA		byte_545,Y
		JMP		loc_BFC4
; ---------------------------------------------------------------------------
loc_BFC1:
		LDA		byte_545,Y
loc_BFC4:
		AND		#$0F
		CMP		#$06
		BCC		loc_BFCE
		CMP		#$0E
		BCC		loc_BFD8
loc_BFCE:
		LDA		byte_545,Y
		AND		#$FE
		ORA		#$0E
		JMP		loc_BFDF
; ---------------------------------------------------------------------------
loc_BFD8:
		LDA		byte_545,Y
		AND		#$F6
		ORA		#$06
loc_BFDF:
		STA		byte_545,Y
		LDA		#$00
		STA		byte_549,Y
		STA		byte_54A,Y

; =============== S U B	R O U T	I N E =======================================
sub_BFEA:
		LDX		byte_543,Y
		LDA		byte_544,Y
		CLC
		ADC		byte_548,Y
		STA		byte_544,Y
		LDA		byte_543,Y
		ADC		byte_547,Y
		CMP		#$03
		BCS		loc_C008
		CPX		#$80
		BCC		loc_C018
		JMP		loc_C010
; ---------------------------------------------------------------------------
loc_C008:
		CMP		#$FD
		BCC		loc_C018
		CPX		#$80
		BCS		loc_C018
loc_C010:
		LDA		#$00
		STA		byte_540,Y
		JMP		sub_C02E
; ---------------------------------------------------------------------------
loc_C018:
		STA		byte_543,Y
		LDA		byte_546,Y
		CLC
		ADC		byte_54A,Y
		STA		byte_546,Y
		LDA		byte_545,Y
		ADC		byte_549,Y
		STA		byte_545,Y

; =============== S U B	R O U T	I N E =======================================
sub_C02E:
		JSR		sub_C324

; =============== S U B	R O U T	I N E =======================================
sub_C031:
		TYA
		CLC
		ADC		#$20
		TAY
		BEQ		locret_C03B
		JMP		sub_B943
; ---------------------------------------------------------------------------
locret_C03B:
		RTS

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
		.WORD sub_C0DC
		.WORD sub_C0F3
		.WORD sub_C10A
		.WORD sub_C12C
		.WORD sub_C15F
		.WORD sub_C1A0
		.WORD sub_C1C1
		.WORD sub_C1F3
		.WORD sub_2BE35
		.WORD sub_343A1
		.WORD sub_C1FF
		.WORD sub_3C086
		.WORD sub_C1F7
		.WORD sub_C1FB
		.WORD sub_4C39F
		.WORD sub_4C3E6
		.WORD sub_C194

; =============== S U B	R O U T	I N E =======================================
sub_C0DC:
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
sub_C0F3:
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
sub_C10A:
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
sub_C12C:
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
sub_C15F:
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
sub_C194:
		JSR		sub_C240
		JSR		sub_C173
		LDA		#$00
		STA		byte_54F,Y
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_C1A0:
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
sub_C1C1:
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
sub_C1F3:
		LDA		#$0C
		BNE		sub_C1C3

; =============== S U B	R O U T	I N E =======================================
sub_C1F7:
		LDA		#$19
		BNE		sub_C1C3

; =============== S U B	R O U T	I N E =======================================
sub_C1FB:
		LDA		#$1A
		BNE		sub_C1C3

; =============== S U B	R O U T	I N E =======================================
sub_C1FF:
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
		JSR		sub_C0DC
		JMP		loc_C493
; ---------------------------------------------------------------------------
loc_C47B:
		LDA		#$01
loc_C47D:
		STA		byte_541,Y
		LDA		#$01
		STA		byte_540,Y
		JSR		sub_C0F3
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
		.WORD	$6F1E
		.WORD _substage2_objs
		.WORD $6F1E
		.WORD _substage4_objs
		.WORD _substage5_objs
		.WORD $7192

; =============== S U B	R O U T	I N E =======================================
sub_C51B:
		LDA		#$01
		STA		byte_10
		LDX		#$00
		BEQ		loc_C527

; =============== S U B	R O U T	I N E =======================================
sub_C523:
		LDX		#$00
		STX		byte_10
loc_C527:
		LDA		byte_640,X
		BEQ		loc_C52F
		JMP		loc_C686
; ---------------------------------------------------------------------------
loc_C52F:
		LDA		byte_541,Y
		CMP		#$05
		BNE		loc_C539
		JMP		loc_C605
; ---------------------------------------------------------------------------
loc_C539:
		CMP		#$11
		BEQ		loc_C541
		CMP		#$17
		BNE		loc_C55F
loc_C541:
		JMP		loc_C692
; ---------------------------------------------------------------------------
loc_C544:
		LDA		byte_543,Y
		SEC
		SBC		#$01
		JMP		loc_C5BC
; ---------------------------------------------------------------------------
loc_C54D:
		LDA		byte_543,Y
		CLC
		ADC		#$08
		JMP		loc_C5BC
; ---------------------------------------------------------------------------
loc_C556:
		LDA		byte_545,Y
		CLC
		ADC		#$12
		JMP		loc_C5DC
; ---------------------------------------------------------------------------
loc_C55F:
		TXA
		PHA
		LDX		_1p_stage
		LDA		byte_C5FF,X
		JSR		_apu_load_safe
		PLA
		TAX
		LDA		#$01
		STA		byte_640,X
		LDA		#$00
		STA		byte_641,X
		STA		byte_647,X
		STA		byte_648,X
		STA		byte_649,X
		STA		byte_64A,X
		LDA		byte_54B,Y
		BNE		loc_C590
		LDA		#$01
		STA		byte_647,X
		LDA		#$80
		JMP		loc_C597
; ---------------------------------------------------------------------------
loc_C590:
		LDA		#$FE
		STA		byte_647,X
		LDA		#$80
loc_C597:
		STA		byte_648,X
		LDA		byte_54B,Y
		BEQ		loc_C5AF
		LDA		byte_541,Y
		CMP		#$05
		BEQ		loc_C544
		LDA		byte_543,Y
		SEC
		SBC		#$0C
		JMP		loc_C5BC
; ---------------------------------------------------------------------------
loc_C5AF:
		LDA		byte_541,Y
		CMP		#$05
		BEQ		loc_C54D
		LDA		byte_543,Y
		CLC
		ADC		#$10
loc_C5BC:
		STA		byte_643,X
		LDA		byte_541,Y
		CMP		#$05
		BEQ		loc_C556
		LDA		_1p_stage
		BEQ		loc_C5D6
		CMP		#$04
		BEQ		loc_C5D6
		LDA		byte_545,Y
		CLC
		ADC		#$09
		BNE		loc_C5DC
loc_C5D6:
		LDA		byte_545,Y
		CLC
		ADC		#$0B
loc_C5DC:
		STA		byte_645,X
		LDA		_1p_stage
		CMP		#$03
		BEQ		loc_C5FA
		CMP		#$04
		BEQ		loc_C5FA
		LDA		#$01
loc_C5EB:
		STA		byte_64E,X
		LDA		#$4B
		STA		byte_64F,X
		LDA		byte_10
		BEQ		locret_C5FE
		JMP		loc_C6DE
; ---------------------------------------------------------------------------
loc_C5FA:
		LDA		#$02
		BNE		loc_C5EB
locret_C5FE:
		RTS
; ---------------------------------------------------------------------------
byte_C5FF:
		.BYTE $0D,$0B,$0B,$0B,$0D,$0B
; ---------------------------------------------------------------------------
loc_C605:
		LDA		_1p_stage
		CMP		#$01
		BNE		loc_C60E
		JMP		loc_C55F
; ---------------------------------------------------------------------------
loc_C60E:
		LDA		#$0F
		JSR		_apu_load_safe
		LDA		#$9A
		STA		byte_55D,Y
		LDA		byte_500
		BEQ		loc_C625
		LDA		byte_520
		BEQ		loc_C627
		LDA		byte_54C,Y
loc_C625:
		EOR		#$01
loc_C627:
		STA		byte_54C,Y
		LDA		#$01
		STA		byte_640,X
		STA		byte_641,X
		LDA		byte_54B,Y
		BNE		loc_C640
		LDA		byte_543,Y
		CLC
		ADC		#$0A
		JMP		loc_C646
; ---------------------------------------------------------------------------
loc_C640:
		LDA		byte_543,Y
		SEC
		SBC		#$04
loc_C646:
		STA		byte_643,X
		LDA		byte_545,Y
		CLC
		ADC		#$0A
		STA		byte_645,X
		DEC		byte_645,X
		LDA		byte_54B,Y
		BEQ		loc_C667
		LDA		#$FE
		STA		byte_647,X
		LDA		#$D0
		STA		byte_648,X
		JMP		loc_C671
; ---------------------------------------------------------------------------
loc_C667:
		LDA		#$01
		STA		byte_647,X
		LDA		#$30
		STA		byte_648,X
loc_C671:
		LDA		#$FA
		STA		byte_649,X
		LDA		#$80
		STA		byte_64A,X
		LDA		#$00
		STA		byte_64E,X
		LDA		#$2B
		STA		byte_64F,X
locret_C685:
		RTS
; ---------------------------------------------------------------------------
loc_C686:
		CPX		#$60
		BEQ		locret_C685
		TXA
		CLC
		ADC		#$20
		TAX
		JMP		loc_C527
; ---------------------------------------------------------------------------
loc_C692:
		LDA		#$01
		STA		byte_640,X
		LDA		#$04
		STA		byte_641,X
		LDA		#$00
		STA		byte_64F,X
		LDA		#$38
		STA		byte_64F,X
		LDA		#$B0
		STA		byte_55D,Y
		LDA		byte_54B,Y
		BEQ		loc_C6BD
		LDA		#$FF
		STA		byte_647,X
		LDA		#$80
		STA		byte_648,X
		JMP		loc_C6C7
; ---------------------------------------------------------------------------
loc_C6BD:
		LDA		#$00
		STA		byte_647,X
		LDA		#$80
		STA		byte_648,X
loc_C6C7:
		LDA		#$FD
		STA		byte_649,X
		LDA		#$80
		STA		byte_64A,X
		LDA		byte_543,Y
		STA		byte_643,X
		LDA		byte_545,Y
		STA		byte_645,X
		RTS
; ---------------------------------------------------------------------------
loc_C6DE:
		LDA		byte_54B,Y
		STA		byte_11
		TYA
		PHA
		LDA		byte_500
		BEQ		loc_C6F8
		LDA		byte_520
		BEQ		loc_C6F4
		LDA		byte_54C,Y
		BNE		loc_C6F8
loc_C6F4:
		LDY		#$00
		BEQ		loc_C6FA
loc_C6F8:
		LDY		#$20
loc_C6FA:
		LDA		byte_500+5,Y
		SEC
		SBC		byte_645,X
		PHP
		LDA		#$00
		STA		byte_14
		STA		byte_16
		LDA		byte_500+3,Y
		CLC
		ADC		#$04
		STA		byte_12
		LDA		byte_500+5,Y
		CLC
		ADC		#$0C
		STA		byte_13
		LDA		byte_643,X
		SEC
		SBC		byte_12
		BCS		loc_C725
		EOR		#$FF
		CLC
		ADC		#$01
loc_C725:
		STA		byte_15
		LDA		byte_645,X
		SEC
		SBC		byte_13
		BCS		loc_C734
		EOR		#$FF
		CLC
		ADC		#$01
loc_C734:
		STA		byte_17
		LDA		byte_15
		BNE		loc_C747
		LDA		byte_17
		BNE		loc_C747
		LDA		#$00
		STA		byte_640,X
		PLA
		JMP		loc_C7B4
; ---------------------------------------------------------------------------
loc_C747:
		LDA		#$00
		STA		byte_10
		LDA		byte_15
		SEC
		SBC		byte_17
		BCS		loc_C768
loc_C752:
		INC		byte_10
		CLC
		ROL		byte_17
		ROL		byte_16
		LDA		byte_16
		BEQ		loc_C752
loc_C75D:
		CLC
		ROL		byte_15
		ROL		byte_14
		DEC		byte_10
		BNE		loc_C75D
		BEQ		loc_C77C
loc_C768:
		INC		byte_10
		CLC
		ROL		byte_15
		ROL		byte_14
		LDA		byte_14
		BEQ		loc_C768
loc_C773:
		CLC
		ROL		byte_17
		ROL		byte_16
		DEC		byte_10
		BNE		loc_C773
loc_C77C:
		LDA		byte_11
		BEQ		loc_C78F
		LDA		byte_15
		EOR		#$FF
		CLC
		ADC		#$01
		STA		byte_15
		LDA		byte_14
		EOR		#$FF
		STA		byte_14
loc_C78F:
		PLP
		BCS		loc_C7A0
		LDA		byte_17
		EOR		#$FF
		ADC		#$01
		STA		byte_17
		LDA		byte_16
		EOR		#$FF
		STA		byte_16
loc_C7A0:
		LDA		byte_14
		STA		byte_647,X
		LDA		byte_15
		STA		byte_648,X
		LDA		byte_16
		STA		byte_649,X
		LDA		byte_17
		STA		byte_64A,X
loc_C7B4:
		PLA
		TAY
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_C7B7:
		LDX		#$00
loc_C7B9:
		LDA		byte_6C0,X
		BEQ		loc_C82C
		LDA		byte_6C1,X
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD loc_C7CE
		.WORD loc_C7E2
		.WORD sub_C87C
		.WORD sub_C8B0
		.WORD loc_C7D4
; ---------------------------------------------------------------------------
loc_C7CE:
		JSR		sub_C838
		JMP		loc_C82C
; ---------------------------------------------------------------------------
loc_C7D4:
		JSR		sub_C838
		DEC		byte_6D0,X
		BNE		loc_C7DF
		JSR		loc_C876
loc_C7DF:
		JMP		loc_C82C
; ---------------------------------------------------------------------------
loc_C7E2:
		LDA		_frames_counter
		AND		#$07
		CMP		#$07
		BNE		loc_C7F6
		LDA		#$00
		LDY		byte_6CB,X
		BNE		loc_C7F3
		LDA		#$01
loc_C7F3:
		STA		byte_6CB,X
loc_C7F6:
		LDA		byte_6CA,X
		CLC
		ADC		#$1C
		STA		byte_6CA,X
		LDA		byte_6C9,X
		ADC		#$00
		STA		byte_6C9,X
		JSR		sub_C838
		LDA		byte_6C9,X
		BMI		loc_C82C
		CMP		#$02
		BCC		loc_C82C
		STX		byte_11
		LDA		byte_6C5,X
		STA		byte_10
		LDA		byte_6C3,X
		LDX		byte_10
		JSR		sub_A614
		LDX		byte_11
		CMP		#$01
		BEQ		loc_C869
		CMP		#$03
		BEQ		loc_C869
loc_C82C:
		TXA
		CLC
		ADC		#$20
		TAX
		CPX		#$40
		BNE		loc_C7B9
		JMP		sub_C90C

; =============== S U B	R O U T	I N E =======================================
sub_C838:
		LDA		byte_6C4,X
		CLC
		ADC		byte_6C8,X
		STA		byte_6C4,X
		LDA		byte_6C3,X
		ADC		byte_6C7,X
		STA		byte_6C3,X
		BEQ		loc_C876
		CMP		#$FD
		BCS		loc_C876
		LDA		byte_6C6,X
		CLC
		ADC		byte_6CA,X
		STA		byte_6C6,X
		LDA		byte_6C5,X
		ADC		byte_6C9,X
		STA		byte_6C5,X
		CMP		#$C4
		BCS		loc_C869
		RTS
; ---------------------------------------------------------------------------
loc_C869:
		LDA		byte_6C1,X
		CMP		#$04
		BEQ		locret_C875
		LDA		#$02
		STA		byte_6C1,X
locret_C875:
		RTS
; ---------------------------------------------------------------------------
loc_C876:
		LDA		#$00
		STA		byte_6C0,X
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_C87C:
		LDA		#$15
		JSR		_apu_load_safe
		INC		byte_6C1,X
		LDA		byte_460
		BEQ		loc_C88D
		LDA		#$10
		BNE		loc_C88F
loc_C88D:
		LDA		#$30
loc_C88F:
		STA		byte_6DF,X
		LDA		byte_6C3,X
		STA		byte_6DD,X
		LDA		byte_6C5,X
		STA		byte_6DE,X
		LDA		#$00
		STA		byte_6DC,X
		LDA		#$2D
		STA		byte_6CF,X
		LDA		#$02
		STA		byte_6CE,X
		JMP		loc_C82C

; =============== S U B	R O U T	I N E =======================================
sub_C8B0:
		LDA		_frames_counter
		AND		#$07
		BNE		loc_C8C5
		INC		byte_6CF,X
		LDA		byte_6CF,X
		CMP		#$2F
		BCC		loc_C8C5
		LDA		#$2D
		STA		byte_6CF,X
loc_C8C5:
		LDA		byte_6DD,X
		BEQ		loc_C876
		DEC		byte_6DF,X
		BEQ		loc_C876
		LDA		_frames_counter
		AND		#$03
		CMP		#$03
		BNE		loc_C8F9
		LDY		byte_6DC,X
		LDA		byte_C8FC,Y
		CLC
		ADC		byte_6DD,X
		STA		byte_6C3,X
		INY
		LDA		byte_C8FC,Y
		CLC
		ADC		byte_6DE,X
		STA		byte_6C5,X
		CPY		#$0A
		BNE		loc_C8F5
		LDY		#$00
loc_C8F5:
		TYA
		STA		byte_6DC,X
loc_C8F9:
		JMP		loc_C82C
; ---------------------------------------------------------------------------
byte_C8FC:
		.BYTE $00,$FA
		.BYTE $00,$06
		.BYTE $FA,$00
		.BYTE $06,$00
		.BYTE $FA,$FA
		.BYTE $06,$06
		.BYTE $06,$FA
		.BYTE $FA,$06

; =============== S U B	R O U T	I N E =======================================
sub_C90C:
		LDX		#$00

; =============== S U B	R O U T	I N E =======================================
sub_C90E:
		LDA		byte_640,X
		BEQ		sub_C93F
		LDA		byte_641,X
		JSR		_switch
; ---------------------------------------------------------------------------
		.WORD sub_C925
		.WORD sub_C92B
		.WORD sub_C9AD
		.WORD sub_C9C9
		.WORD sub_C949
		.WORD sub_C925

; =============== S U B	R O U T	I N E =======================================
sub_C925:
		JSR		sub_C960
		JMP		sub_C93F

; =============== S U B	R O U T	I N E =======================================
sub_C92B:
		LDA		byte_64A,X
		CLC
		ADC		#$22
		STA		byte_64A,X
		LDA		byte_649,X
		ADC		#$00
		STA		byte_649,X
		JSR		sub_C960

; =============== S U B	R O U T	I N E =======================================
sub_C93F:
		TXA
		CLC
		ADC		#$20
		TAX
		CPX		#$80
		BNE		sub_C90E
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_C949:
		LDA		byte_64A,X
		CLC
		ADC		#$20
		STA		byte_64A,X
		LDA		byte_649,X
		ADC		#$00
		STA		byte_649,X
		JSR		sub_C960
		JMP		sub_C93F

; =============== S U B	R O U T	I N E =======================================
sub_C960:
		LDA		byte_644,X
		CLC
		ADC		byte_648,X
		STA		byte_644,X
		LDA		byte_643,X
		ADC		byte_647,X
		STA		byte_643,X
		BEQ		loc_C9A7
		CMP		#$FD
		BCS		loc_C9A7
		LDA		byte_646,X
		CLC
		ADC		byte_64A,X
		STA		byte_646,X
		LDA		byte_645,X
		ADC		byte_649,X
		STA		byte_645,X
		CMP		#$CE
		BCC		locret_C9A6
		LDA		byte_641,X
		BEQ		loc_C9A7
		LDA		byte_641,X
		CMP		#$05
		BNE		loc_C9A1
		LDA		#$11
		JSR		_apu_load_safe
loc_C9A1:
		LDA		#$02
		STA		byte_641,X
locret_C9A6:
		RTS
; ---------------------------------------------------------------------------
loc_C9A7:
		LDA		#$00
		STA		byte_640,X
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_C9AD:
		LDA		#$15
		JSR		_apu_load_safe
		LDA		#$03
		STA		byte_641,X
		LDA		#$12
		STA		byte_65F,X
		LDA		#$02
		STA		byte_64E,X
		LDA		#$2D

; =============== S U B	R O U T	I N E =======================================
sub_C9C3:
		STA		byte_64F,X

; =============== S U B	R O U T	I N E =======================================
sub_C9C6:
		JMP		sub_C93F

; =============== S U B	R O U T	I N E =======================================
sub_C9C9:
		DEC		byte_65F,X
		BNE		loc_C9D1
		JSR		loc_C9A7
loc_C9D1:
		LDA		byte_65F,X
		CMP		#$0C
		BEQ		loc_C9E1
		CMP		#$05
		BNE		sub_C9C6
		LDA		#$2D
		JMP		sub_C9C3
; ---------------------------------------------------------------------------
loc_C9E1:
		LDA		#$2E
		BNE		sub_C9C3

_substages_macro:
		.BYTE $11,$11,$11,$11
		.BYTE $12,$12,$12,$12
		.BYTE $13,$14,$13,$14
		.BYTE $15,$16,$15,$16
		.BYTE $1C,$1D,$1C,$1D
		.BYTE $15,$16,$15,$16
		.BYTE $17,$18,$17,$18
		.BYTE $1A,$19,$1A,$19
		.BYTE $1B,$1A,$19,$1A
		.BYTE $1A,$19,$1A,$19
		.BYTE $19,$1A,$19,$1A
		.BYTE $1A,$19,$1A,$19
		.BYTE $1C,$1D,$1C,$1D
		.BYTE $15,$16,$15,$16
		.BYTE $13,$14,$13,$14
		.BYTE $15,$16,$15,$16
		.BYTE $1E,$1F,$1C,$1D
		.BYTE $20,$21,$15,$16
		.BYTE $22,$23,$17,$18
		.BYTE $24,$21,$1A,$19
		.BYTE $22,$23,$19,$1A
		.BYTE $24,$21,$1A,$19
		.BYTE $22,$23,$19,$1A
		.BYTE $24,$21,$1A,$19
		.BYTE $19,$1A,$17,$18
		.BYTE $1A,$19,$1A,$19
		.BYTE $19,$1A,$1B,$1A
		.BYTE $1A,$19,$1A,$19
		.BYTE $11,$11,$11,$11
		.BYTE $12,$12,$12,$12
		.BYTE $1E,$1F,$13,$14
		.BYTE $20,$21,$15,$16
		.BYTE $22,$23,$19,$1A
		.BYTE $24,$21,$1A,$19
		.BYTE $19,$1A,$19,$1A
		.BYTE $1A,$19,$1A,$19
_substages_attr:
		.BYTE $A0,$5A,$55,$AA,$59,$55,$55,$90,$55

;_fds_data_pal_list:
;		.BYTE $00,$54,$54,$54,$54,$54,$54,$00,$00,$54,$54,$54,$54,$54,$54,$00
;		.BYTE $00,$00,$00
;_fds_data_sides_list:
;		.BYTE $00,$01,$01,$01,$01,$01,$00,$00,$01,$01,$01,$01,$01,$01,$00,$00
;		.BYTE $00,$00,$01
_integrity_test_list:
		.BYTE $FF,$FF,$FF,$FF
		.BYTE $0B,$0A,$FF,$FF
		.BYTE $0C,$0D,$FF,$FF
		.BYTE $0B,$0E,$FF,$FF
		.BYTE $0C,$0F,$FF,$FF
		.BYTE $0B,$10,$FF,$FF
		.BYTE $11,$FF,$FF,$FF
		.BYTE $12,$FF,$FF,$FF
		.BYTE $08,$FF,$FF,$FF
		.BYTE $02,$03,$FF,$FF
		.BYTE $02,$04,$FF,$FF
		.BYTE $02,$05,$FF,$FF
		.BYTE $02,$06,$FF,$FF
		.BYTE $02,$07,$FF,$FF
		.BYTE $13,$FF,$FF,$FF
		.BYTE $09,$FF,$FF,$FF
		.BYTE $14,$FF,$FF,$FF
		.BYTE $02,$FF,$FF,$FF
		.BYTE $02,$16,$FF,$FF

; =============== S U B	R O U T	I N E =======================================
_fds_data_load:
;		PHA
;		JSR		_fds_load_bufs_clear
		JSR		_bios_fonts_load
;		PLA
		STA		_fds_data_idx
		ASL
		ASL
		TAX
		LDY		#$00
loc_D98B:
		LDA		_integrity_test_list,X
		STA		_fds_files_buf,Y
		INY
		INX
		CPY		#$04
		BCC		loc_D98B
;		LDX		_main_sub_idx
;		STX		_main_sub_idx_backup
;		LDX		_sub_sub_idx
;		STX		_sub_sub_idx_backup
;		PLA
;		CLC
;		ADC		#$01
;		STA		_fds_data_load_exit_pc_backup
;		PLA
;		ADC		#$00
;		STA		_fds_data_load_exit_pc_backup+1
;		LDA		#$0A
;		STA		_main_sub_idx
;		LDX		#$0A
;loc_D9B7:
;		LDA		_fds_disk_info_data,X
;		STA		_fds_disk_info_buf,X
;		DEX
;		BPL		loc_D9B7
		LDA		#$7D
		JSR		_apu_load_safe
;		LDA		#$55
;		STA		_fds_status_fifo
		JSR		_screen_clear

		JSR		_file_unpack_if_needed

;		LDA		#$0A
;		STA		_ppu_mask_shadow
;		LDA		#$4C
;		JSR		_tlm_lib_load
;		LDA		#$05
;		JSR		_tlm_lib_load
;		LDX		_fds_data_idx
;		LDA		_fds_data_pal_list,X
;		BEQ		loc_D9E6
;		JSR		_tlm_lib_load
;loc_D9E6:
;		LDA		#$00
;		STA		_sub_sub_idx
;		LDX		_fds_data_idx
;		LDA		_fds_data_sides_list,X
;		STA		_fds_req_side
;		LDA		_fds_req_side
;		CMP		_fds_cur_side
;		BEQ		loc_DA00
;		STA		_fds_cur_side
;		LDA		#$04
;		STA		_sub_sub_idx
;loc_DA00:
;		JMP		_please_set_side_draw

; =============== S U B	R O U T	I N E =======================================
;_fds_read_status_fifo:
;		LDA		_FDS_REG32
;		ROR
;		ROR		_fds_status_fifo
;		LDA		_fds_status_fifo
;		RTS

; =============== S U B	R O U T	I N E =======================================
;_main0A_loading_screen:
;		JSR		_fds_read_status_fifo
;		LDA		_sub_sub_idx
;		JSR		_switch
; ---------------------------------------------------------------------------
;		.WORD _loading_screen00_loading_draw
;		.WORD _loading_screen01_wait_for_drive
;		.WORD _loading_screen02_load_unpack_exit
;		.WORD _loading_screen03_error_draw
;		.WORD _loading_screen04_wait_for_drive
;		.WORD _loading_screen05_please_set_x
;		.WORD _loading_screen06_wait_for_side

; =============== S U B	R O U T	I N E =======================================
;_loading_screen05_please_set_x:
;		INC		_sub_sub_idx
;		JMP		_please_set_side_draw

; =============== S U B	R O U T	I N E =======================================
;_loading_screen06_wait_for_side:
;		JSR		_fds_read_status_fifo
;		BNE		nullsub_2
;		LDA		#$00
;		STA		_sub_sub_idx
;		RTS

; =============== S U B	R O U T	I N E =======================================
;_loading_screen01_wait_for_drive:
;		JSR		_fds_read_status_fifo
;		BNE		nullsub_2

; =============== S U B	R O U T	I N E =======================================
;_next_sub_sub_0:
;		INC		_sub_sub_idx

; =============== S U B	R O U T	I N E =======================================
;nullsub_2:
;		RTS

; =============== S U B	R O U T	I N E =======================================
;_loading_screen04_wait_for_drive:
;		JSR		_fds_read_status_fifo
;		CMP		#$FF
;		BEQ		_next_sub_sub_0
;		RTS

; =============== S U B	R O U T	I N E =======================================
;_loading_screen00_loading_draw:
;		LDA		#$8B
;		JSR		_tlm_lib_load
;		LDA		#$4B
;		JSR		_tlm_lib_load
;		INC		_sub_sub_idx
;		RTS

; =============== S U B	R O U T	I N E =======================================
;_loading_screen03_error_draw:
;		LDA		#$8B
;		JSR		_tlm_lib_load
;		LDA		#$0C
;		JSR		_tlm_lib_load
;		LDA		_fds_error_code
;		LSR
;		LSR
;		LSR
;		LSR
;		CLC
;		ADC		#$01
;		STA		byte_6E0+$1D,X
;		LDA		_fds_error_code
;		AND		#$0F
;		CLC
;		ADC		#$01
;		STA		byte_6E0+$1E,X
;		INC		_sub_sub_idx
;		RTS

; =============== S U B	R O U T	I N E =======================================
;_loading_screen02_load_unpack_exit:
;		JSR		_fds_file_load
;		LDA		_fds_error_code
;		BEQ		loc_DA80
;		INC		_sub_sub_idx
;		RTS
; ---------------------------------------------------------------------------
;loc_DA80:
;		JSR		_file_crc_test
;		BNE		_read_file_again
;		JSR		_file_unpack_if_needed
;		LDA		#$05
;		STA		_nmi_counter
;		LDX		_main_sub_idx_backup
;		STX		_main_sub_idx
;		LDX		_sub_sub_idx_backup
;		STX		_sub_sub_idx
;		JMP		(_fds_data_load_exit_pc_backup)
; ---------------------------------------------------------------------------
;_read_file_again:
;		LDA		#$00
;		STA		_sub_sub_idx
;		RTS

; =============== S U B	R O U T	I N E =======================================
;_nmi_off_bg_render_on:
;		LDA		#$00
;		STA		_PPU_CTRL
;		STA		_ppu_ctrl_shadow
;		LDA		#$08
;		STA		_ppu_mask_shadow
;		STA		_PPU_MASK
;		LDA		#$00
;		STA		_FDS_REG22
;		STA		_apu_DMC_FREQ
;		LDA		#$0F
;		STA		_apu_STATUS
;		LDA		#$C0
;		STA		_PAD1_REG
;		RTS

; =============== S U B	R O U T	I N E =======================================
;_fds_file_load:
;		JSR		_nmi_off_bg_render_on
;		JSR		_BIOS_load_files_by_idx
; ---------------------------------------------------------------------------
;		.WORD _fds_disk_info_buf
;		.WORD _fds_files_buf
; ---------------------------------------------------------------------------
;		STA		_fds_error_code
;		LDA		#$C0
;		STA		byte_100
;		LDA		#$80
;		STA		byte_101
;		JMP		_render_on

; =============== S U B	R O U T	I N E =======================================
;_please_set_side_draw:
;		LDA		#$0B
;		JSR		_tlm_lib_load
;		LDA		_fds_req_side
;		CLC
;		ADC		#$0B
;		STA		byte_6E0+$1E,X
;		RTS

; =============== S U B	R O U T	I N E =======================================
_add16:
		CLC
		ADC		word_0,X
		STA		word_0,X
		BCC		locret_DAF1
		INC		word_0+1,X
locret_DAF1:
		RTS

; =============== S U B	R O U T	I N E =======================================
;_sub16_unref:
;		EOR		#$FF
;		SEC
;		ADC		word_0,X
;		STA		word_0,X
;		BCS		locret_DAFD
;		DEC		word_0+1,X
;locret_DAFD:
;		RTS

; ---------------------------------------------------------------------------
_lib_files_dst_lo:
		.BYTE $FF
		.BYTE $FF
		.BYTE <[_chr02_PO_COME]
		.BYTE <[_chr03_PO1D]
		.BYTE <[_chr04_PO2D]
		.BYTE <[_chr05_PO3D]
		.BYTE <[_chr06_PO4D]
		.BYTE <[_chr07_PO5D]
		.BYTE <[_chr08_titleA]
		.BYTE <[_chr09_POPD_titleB]
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE <[_chr13_PO6D]
		.BYTE <[_chr14_POED1_endingA]
		.BYTE <[_chr15_endingB]
		.BYTE <[_chr16_PTCD]
		.BYTE <[_chr17_game_over]
_lib_files_dst_hi:
		.BYTE $FF
		.BYTE $FF
		.BYTE <[_chr02_PO_COME]
		.BYTE <[_chr03_PO1D]
		.BYTE <[_chr04_PO2D]
		.BYTE <[_chr05_PO3D]
		.BYTE <[_chr06_PO4D]
		.BYTE <[_chr07_PO5D]
		.BYTE <[_chr08_titleA]
		.BYTE <[_chr09_POPD_titleB]
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE <[_chr13_PO6D]
		.BYTE <[_chr14_POED1_endingA]
		.BYTE <[_chr15_endingB]
		.BYTE <[_chr16_PTCD]
		.BYTE <[_chr17_game_over]
_lib_files_bank:
		.BYTE $FF
		.BYTE $FF
		.BYTE _chr02_PO_COME_BANK
		.BYTE _chr03_PO1D_BANK
		.BYTE _chr04_PO2D_BANK
		.BYTE _chr05_PO3D_BANK
		.BYTE _chr06_PO4D_BANK
		.BYTE _chr07_PO5D_BANK
		.BYTE _chr08_titleA_BANK
		.BYTE _chr09_POPD_titleB_BANK
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE $FF
		.BYTE _chr13_PO6D_BANK
		.BYTE _chr14_POED1_endingA_BANK
		.BYTE _chr15_endingB_BANK
		.BYTE _chr16_PTCD_BANK
		.BYTE _chr17_game_over_BANK

; =============== S U B	R O U T	I N E =======================================
_file_unpack_if_needed:
		LDX		#$00
		STX		byte_10
loc_DB32:
		LDX		byte_10
		LDA		_fds_files_buf,X
		CMP		#$FF
		BEQ		loc_DB58
		CMP		#$15
		BEQ		loc_DB58
		CMP		#$08
		BEQ		loc_DB58
		CMP		#$09
		BEQ		loc_DB58
;		ASL
		TAX
		LDA		_lib_files_dst_lo,X
		CMP		#$FF
		BEQ		loc_DB53
		JSR		_file_lib_unpack_ex
loc_DB53:
		INC		byte_10
		JMP		loc_DB32
; ---------------------------------------------------------------------------
loc_DB58:
		JMP		_render_on_nmi_on

; =============== S U B	R O U T	I N E =======================================
_file_lib_unpack:
;		ASL
		TAX

; =============== S U B	R O U T	I N E =======================================
_file_lib_unpack_ex:

		LDA		_lib_files_dst_lo,X
		STA		word_0
		LDA		_lib_files_dst_hi,X
		STA		word_0+1
loc_DB67:
		LDA		#$00
		STA		_PPU_MASK
		STA		_PPU_CTRL
		STA		_ppu_queue_pos
		STA		byte_FC
		STA		byte_FD
		LDA		_PPU_STATUS
		LDY		#$01
		LDA		(word_0),Y
		STA		_PPU_ADDR
		DEY
		LDA		(word_0),Y
		STA		_PPU_ADDR
		LDX		#$00
		LDA		#$02
		JSR		_add16
loc_DB8C:
		LDY		#$00
		LDA		(word_0),Y
		CMP		#$FF
		BEQ		loc_DBD2
		CMP		#$7F
		BEQ		loc_DBCA
		TAY
		BPL		loc_DBB8
		AND		#$7F
		STA		byte_2
		LDY		#$01
loc_DBA1:
		LDA		(word_0),Y
		STA		_PPU_DATA
		CPY		byte_2
		BEQ		loc_DBAD
		INY
		BNE		loc_DBA1
loc_DBAD:
		LDA		#$01
		CLC
		ADC		byte_2
loc_DBB2:
		JSR		_add16
		JMP		loc_DB8C
; ---------------------------------------------------------------------------
loc_DBB8:
		LDY		#$01
		STA		byte_2
		LDA		(word_0),Y
		LDY		byte_2
loc_DBC0:
		STA		_PPU_DATA
		DEY
		BNE		loc_DBC0
		LDA		#$02
		BNE		loc_DBB2
loc_DBCA:
		LDA		#$01
		JSR		_add16
		JMP		loc_DB67
; ---------------------------------------------------------------------------
loc_DBD2:
		JMP		_render_on_nmi_on

; =============== S U B	R O U T	I N E =======================================
;_file_crc_test:
;		LDY		#$00
;		STY		byte_8
;loc_DBD9:
;		LDX		byte_8
;		LDA		_fds_files_buf,X
;		CMP		#$16
;		BCS		loc_DBF0
;		CMP		#$FF
;		BEQ		loc_DBF0
;		JSR		_integrity_test
;		BNE		locret_DBEF
;		INC		byte_8
;		BNE		loc_DBD9
;locret_DBEF:
;		RTS; ---------------------------------------------------------------------------
;loc_DBF0:
;		LDA		#$00
;		RTS

; =============== S U B	R O U T	I N E =======================================
;_integrity_test:
;		ASL
;		STA		word_0
;		ASL
;		TAX
;		LDA		_intergity_ofs_list,X
;		STA		word_4
;		LDA		_intergity_ofs_list+1,X
;		STA		word_4+1
;		LDA		_intergity_size_list,X
;		STA		byte_2
;		LDA		_intergity_size_list+1,X
;		STA		byte_3
;		LDY		#$00
;		STY		byte_6
;		STY		byte_7
;loc_DC12:
;		LDA		byte_2
;		SEC
;		SBC		#$01
;		STA		byte_2
;		LDA		byte_3
;		SBC		#$00
;		STA		byte_3
;		BCC		loc_DC32
;		LDA		(word_4),Y
;		LDX		#byte_6
;		JSR		_add16
;		LDX		#word_4
;		LDA		#$01
;		JSR		_add16
;		JMP		loc_DC12
; ---------------------------------------------------------------------------
;loc_DC32:
;		LDX		word_0
;		LDA		byte_6
;		CMP		_intergity_crc_list,X
;		BNE		locret_DC40
;		LDA		byte_7
;		CMP		_intergity_crc_list+1,X
;locret_DC40:
;		RTS
; ---------------------------------------------------------------------------
;_intergity_ofs_list:
;		.WORD $FFFF
;_intergity_size_list:
;		.WORD $FFFF
;		.WORD _FDS_RESET
;		.WORD $5F80
;		.WORD _chr02_PO_COME
;		.WORD $06B7
;		.WORD _chr03_PO1D
;		.WORD $1013
;		.WORD _chr04_PO2D
;		.WORD $1037
;		.WORD _chr05_PO3D
;		.WORD $0E70
;		.WORD _chr06_PO4D
;		.WORD $1080
;		.WORD _chr07_PO5D
;		.WORD $1024
;		.WORD _screen_lib2_title
;		.WORD $1853
;		.WORD _chr09_POPD_titleB
;		.WORD $07E2
;		.WORD _stage1_rooms
;		.WORD $08A4
;		.WORD byte_16000
;		.WORD $069D
;		.WORD _apu32
;		.WORD $05BC
;		.WORD _stage2_rooms
;		.WORD $0D6D
;		.WORD _apu44
;		.WORD $0EA1
;		.WORD _stage4_rooms
;		.WORD $115B
;		.WORD _stage5_rooms
;		.WORD $0FE9
;		.WORD byte_4B000
;		.WORD $1576
;		.WORD _screen_lib8_final_stage_complete
;		.WORD $1D79
;		.WORD _chr13_PO6D
;		.WORD $1734
;		.WORD _chr14_POED1_endingA
;		.WORD $16A1
;		.WORD $0000
;		.WORD $0001
;		.WORD _chr16_PTCD
;		.WORD $0A54
;_intergity_crc_list:
;		.WORD $965C
;		.WORD $69A3
;		.WORD $7A15
;		.WORD $CD53
;		.WORD $0B9C
;		.WORD $9AB8
;		.WORD $7D79
;		.WORD $806B
;		.WORD $B0AF
;		.WORD $AAA4
;		.WORD $8DC9
;		.WORD $AFB2
;		.WORD $1945
;		.WORD $4C4E
;		.WORD $A8C2
;		.WORD $38B4
;		.WORD $581F
;		.WORD $C92E
;		.WORD $0367
;		.WORD $AA03
;		.WORD $C3F4
;		.WORD $FFFF
;		.WORD $BC10

;_fds_disk_info_data:
;		.BYTE $A4
;		.BYTE "GRN "
;		.BYTE $00,$00,$00,$00,$00
;		.BYTE $A4
;		.BYTE "GRN "
;		.BYTE $00,$01,$00,$00,$00
