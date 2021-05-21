
		ORG $8000

		ECHO "PROGRAM BEGIN"
		ECHO "-------------"

_total_free	SET 0

		BANK_START $00

		SECTION_START

_apu_tracks_lib_ofs:
		.WORD _apu_track_lib-3

; =============== S U B	R O U T	I N E =======================================
_apu_load:
		STA		_track_chnl_var_ofs
;		LDA		#$7D
;		CMP		_track_chnl_var_ofs
		CMP		#$7D
		BEQ		loc_CA33
		LDA		byte_20
		BEQ		loc_C9FD
		LDA		_track_chnl_var_ofs
		CMP		#$29
		BEQ		loc_CA12
		CMP		#$2C
		BEQ		loc_CA12
loc_C9FD:
		LDA		_apu_chl1+2
		CMP		#$44
		BNE		loc_CA16
		LDA		_track_chnl_var_ofs
		CMP		#$67
		BEQ		loc_CA12
		LDA		_track_chnl_var_ofs
		CMP		#$6A
		BEQ		loc_CA12
		JMP		loc_CA16
; ---------------------------------------------------------------------------
loc_CA12:
		JSR		_apu_delay
		RTS
; ---------------------------------------------------------------------------
loc_CA16:
		LDA		_track_chnl_var_ofs
		CMP		#$6A
		BEQ		loc_CA29
		LDA		_track_chnl_var_ofs
		CMP		#$6D
		BEQ		loc_CA29
		LDA		byte_6B
		BNE		loc_CA12
		JMP		loc_CA33
; ---------------------------------------------------------------------------
loc_CA29:
		STA		byte_6B
		LDA		byte_5D
		BEQ		loc_CA33
		LDA		#$7D
		STA		byte_7F
loc_CA33:
		TXA
		PHA
		TYA
		PHA
		LDA		_track_chnl_var_ofs
		CMP		#$7D
		BNE		loc_CA45
		LDA		#$00
		STA		byte_C2
		STA		byte_D2
		STA		byte_6B
loc_CA45:
		LDX		#$03
		LDA		_apu_tracks_lib_ofs
		STA		_apu_ptrE5
		LDA		_apu_tracks_lib_ofs+1
		STA		_apu_ptrE5+1
loc_CA51:
		LDA		_track_chnl_var_ofs
		CLC
		ADC		_apu_ptrE5
		STA		_apu_ptrE5
		LDA		#$00
		ADC		_apu_ptrE5+1
		STA		_apu_ptrE5+1
		DEX
		BNE		loc_CA51
		LDY		#$00
		STY		_apu_load_tmp_ofs
		LDA		(_apu_ptrE5),Y
		ROL
		ROL
		ROL
		AND		#$03
		STA		_apu_track_settings
		LDA		_track_chnl_var_ofs
		CMP		byte_C2
		BEQ		loc_CAA1
loc_CA74:
		LDY		_apu_load_tmp_ofs
		LDA		(_apu_ptrE5),Y
		AND		#$3F
		CMP		#$10
		BNE		loc_CAA3
		LDA		byte_C2
		BEQ		loc_CAA1
		JMP		loc_CA88
; ---------------------------------------------------------------------------
loc_CA85:
		JMP		loc_CB5E
; ---------------------------------------------------------------------------
loc_CA88:
		LDA		_track_chnl_var_ofs
		CMP		#$13
		BNE		loc_CA98
		LDA		byte_C2
		SEC
		SBC		#$03
		CMP		_track_chnl_var_ofs
		JMP		loc_CA9C
; ---------------------------------------------------------------------------
loc_CA98:
		LDA		byte_C2
		CMP		_track_chnl_var_ofs
loc_CA9C:
		BCC		loc_CAA1
		JMP		loc_CA85
; ---------------------------------------------------------------------------
loc_CAA1:
		LDA		#$10
loc_CAA3:
		STA		_cur_track_ofs
		LSR
		LSR
		TAY
		LDX		_track_chnl_var_list,Y
		LDA		_track_chnl_var_ofs
		BEQ		loc_CAE5
		CMP		#$0B
		BEQ		loc_CAC6
		CMP		#$0D
		BEQ		loc_CACC
		CMP		#$0F
		BEQ		loc_CAD2
		CMP		#$11
		BEQ		loc_CAD8
		CMP		#$13
		BEQ		loc_CADE
		JMP		loc_CAE1
; ---------------------------------------------------------------------------
loc_CAC6:
		CLC
		ADC		#$0A
		JMP		loc_CAE1
; ---------------------------------------------------------------------------
loc_CACC:
		CLC
		ADC		#$08
		JMP		loc_CAE1
; ---------------------------------------------------------------------------
loc_CAD2:
		CLC
		ADC		#$06
		JMP		loc_CAE1
; ---------------------------------------------------------------------------
loc_CAD8:
		CLC
		ADC		#$04
		JMP		loc_CAE1
; ---------------------------------------------------------------------------
loc_CADE:
		CLC
		ADC		#$02
loc_CAE1:
		CMP		_apu_chl0+2-$80,X
		BCC		loc_CB5E
loc_CAE5:
		LDA		#$00
		STA		_apu_chl0+2-$80,X
		LDY		_apu_load_tmp_ofs
		INY
		LDA		(_apu_ptrE5),Y
		STA		_apu_chl0+3-$80,X
		STA		_apu_load_tmp_track_ptr
		INY
		LDA		(_apu_ptrE5),Y
		STA		_apu_chl0+4-$80,X
		STA		_apu_load_tmp_track_ptr+1
		LDY		#$01
		STY		_apu_chl0-$80,X
		DEY
		STY		_apu_chl0+6-$80,X
		CPX		#_apu_chl0
		BNE		loc_CB08
		STY		byte_A1
		STY		byte_A7
loc_CB08:
		CPX		#_apu_chl1
		BNE		loc_CB10
		STY		byte_B5
		STY		byte_B8
loc_CB10:
		CPX		#_apu_chl2
		BEQ		loc_CB1A
		STY		_apu_chl0+1-$80,X
		CPX		#_apu_chl3
		BEQ		loc_CB2D
loc_CB1A:
		LDA		(_apu_load_tmp_track_ptr),Y
		BNE		loc_CB24
		STA		_track_chnl_var_ofs
		CPX		#_apu_chl3
		BEQ		loc_CB2D
loc_CB24:
		AND		#$F0
		CMP		#$20
		BEQ		loc_CB2B
		INY
loc_CB2B:
		STY		_apu_chl0+8-$80,X
loc_CB2D:
		LDY		_cur_track_ofs
		CPY		#$00
		BNE		loc_CB3A
		LDA		byte_C2
		BNE		loc_CB5A
		JMP		loc_CB42
; ---------------------------------------------------------------------------
loc_CB3A:
		CPY		#$04
		BNE		loc_CB42
		LDA		byte_D2
		BNE		loc_CB5A
loc_CB42:
		TYA
		AND		#$0F
		TAY
		LDA		#$00
		CPY		#$08
		BEQ		loc_CB54
		STA		_apu_PULSE1_SWEEP,Y
		JSR		_apu_delay
		LDA		#$30
loc_CB54:
		STA		_apu_PULSE1_ENV,Y
		JSR		_apu_delay
loc_CB5A:
		LDA		_track_chnl_var_ofs
		STA		_apu_chl0+2-$80,X
loc_CB5E:
		DEC		_apu_track_settings
		BMI		loc_CB6C
		LDY		_apu_load_tmp_ofs
		INY
		INY
		INY
		STY		_apu_load_tmp_ofs
		JMP		loc_CA74
; ---------------------------------------------------------------------------
loc_CB6C:
		LDA		#$00
		STA		_apu_ptrE5+1
		PLA
		TAY
		PLA
		TAX
		RTS
; ---------------------------------------------------------------------------
_track_chnl_var_list:
		.BYTE _apu_chl0
		.BYTE _apu_chl1
		.BYTE _apu_chl2
		.BYTE _apu_chl3
		.BYTE _apu_chl4

; =============== S U B	R O U T	I N E =======================================
_apu_delay:
		PHA
		TXA
		PHA
		LDX		#$14
loc_CB7F:
		NOP
		DEX
		BNE		loc_CB7F
		PLA
		TAX
		PLA
		RTS

; =============== S U B	R O U T	I N E =======================================
_apu_cmdFF_A:
		LDA		#$00
		STA		byte_CA
		STA		byte_7E
		CPX		#_apu_chl4
		BEQ		loc_CB94
		JMP		loc_CB9E
; ---------------------------------------------------------------------------
loc_CB94:
		LDA		#$6D
		CMP		byte_C2
		BNE		loc_CB9E
		LDA		#$6A
		STA		byte_7E
loc_CB9E:
		CPX		#_apu_chl2
		BNE		loc_CBD9
		LDA		#$29
		CMP		byte_A2
		BEQ		loc_CBCA
		LDA		#$44
		CMP		byte_A2
		BEQ		loc_CBCA
		LDA		#$41
		CMP		byte_A2
		BEQ		loc_CBCA
		LDA		#$6A
		CMP		byte_A2
		BNE		loc_CBD9
		LDA		byte_5D
		BNE		loc_CBC1
		JMP		loc_CBCA
; ---------------------------------------------------------------------------
loc_CBC1:
		LDA		#$67
		STA		byte_7F
		STA		byte_6B
		JMP		loc_CBD9
; ---------------------------------------------------------------------------
loc_CBCA:
		LDA		#$29
		CMP		byte_A2
		BNE		loc_CBD6
		JSR		sub_CC50
		JMP		loc_CBD9
; ---------------------------------------------------------------------------
loc_CBD6:
		JSR		sub_CC43
loc_CBD9:
		CPX		#_apu_chl0
		BNE		loc_CBEB
		LDA		#$6A
		CMP		_apu_chl0+2
		BNE		loc_CBEB
		LDA		byte_5D
		BNE		loc_CBEB
		LDA		#$00
		STA		byte_6B
loc_CBEB:
		CPX		#_apu_chl4
		BNE		loc_CC05
		LDA		#$78
		CMP		byte_C2
		BNE		loc_CC05
		JSR		sub_CC5D
		LDA		#$00
		STA		byte_C2
		LDA		#$30
		STA		_apu_PULSE1_ENV
		JSR		_apu_delay
		RTS
; ---------------------------------------------------------------------------
loc_CC05:
		TYA
		STY		_apu_chl0+2-$80,X
		CPX		#_apu_chl4
		BNE		loc_CC1F
		LDA		_apu_chl0+2
		BEQ		loc_CC1F
		JSR		sub_CC5D
		LDA		_apu_chl0+7
		STA		_apu_PULSE1_ENV
		JSR		_apu_delay
		JSR		sub_CC76
		RTS
; ---------------------------------------------------------------------------
loc_CC1F:
		CPX		#_apu_chl2
		BEQ		loc_CC2D
		LDA		#$00
		STA		_apu_chl0+1-$80,X
		LDA		#$30
		CPX		#_apu_chl3
		BEQ		loc_CC2F
loc_CC2D:
		STY		_apu_chl0+8-$80,X
loc_CC2F:
		JSR		_apu_check_chnl
		BCS		loc_CC39
		LDX		_cur_apu_chnl_ofs
		STA		_apu_PULSE1_ENV,X
loc_CC39:
		JSR		sub_CC85
		JSR		sub_CC76
		JSR		_apu_delay
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_CC43:
		LDA		byte_460
		BEQ		sub_CC58
		LDA		byte_463
		BNE		sub_CC50
		JMP		sub_CC58

; =============== S U B	R O U T	I N E =======================================
sub_CC50:
		LDA		byte_7F
		SEC
		SBC		#$03
		JMP		sub_CC5A

; =============== S U B	R O U T	I N E =======================================
sub_CC58:
		LDA		byte_7F

; =============== S U B	R O U T	I N E =======================================
sub_CC5A:
		STA		byte_CA
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_CC5D:
		LDA		#$00
		STA		_apu_PULSE1_SWEEP
		JSR		_apu_delay
		LDA		byte_A7
		STA		_apu_PULSE1_TIME
		JSR		_apu_delay
		LDA		_apu_chl0+1
		STA		_apu_PULSE1_LEN
		JSR		_apu_delay
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_CC76:
		LDA		byte_7E
		BEQ		locret_CC84
		LDA		#$7D
		JSR		_apu_load
		LDA		byte_7E
		JSR		_apu_load
locret_CC84:
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_CC85:
		LDA		byte_CA
		BEQ		locret_CC9B
		LDA		#$00
		STA		_apu_chl0+2
		STA		_apu_chl1+2
		STA		byte_A2
		LDA		#$7D
		JSR		_apu_load
		LDA		byte_CA
		JSR		_apu_load
locret_CC9B:
		RTS

; =============== S U B	R O U T	I N E =======================================
_apu_jsr:
		INY
		LDA		(_cur_track_data_ptr),Y
		STA		_apu_chl0+3-$80,X
		INY
		LDA		(_cur_track_data_ptr),Y
		STA		_apu_chl0+4-$80,X
		RTS

; =============== S U B	R O U T	I N E =======================================
_apu_cmdFE:
		LDA		_apu_chl0+6-$80,X
		CLC
		ADC		#$01
		INY
		CMP		(_cur_track_data_ptr),Y
		BEQ		loc_CCC5
		BMI		loc_CCB6
		SEC
		SBC		#$01
loc_CCB6:
		STA		_apu_chl0+6-$80,X
		INY
		LDA		(_cur_track_data_ptr),Y
		STA		_apu_chl0+3-$80,X
		INY
		LDA		(_cur_track_data_ptr),Y
		STA		_apu_chl0+4-$80,X
		JMP		sub_CCD8
; ---------------------------------------------------------------------------
loc_CCC5:
		LDA		#$00
		STA		_apu_chl0+6-$80,X
		INY
		INY
		INY
		TYA
		CLC
		ADC		_cur_track_data_ptr
		STA		_apu_chl0+3-$80,X
		LDA		#$00
		ADC		_cur_track_data_ptr+1
		STA		_apu_chl0+4-$80,X

; =============== S U B	R O U T	I N E =======================================
sub_CCD8:
		LDA		#$01
		STA		_apu_chl0-$80,X
		JMP		_apu_channel_play

; =============== S U B	R O U T	I N E =======================================
_apu_play:
		LDX		#_apu_chl0
		LDY		#$00
loc_CCE3:
		STX		_cur_apu_chnl_ram_ofs
		STY		_cur_apu_chnl_ofs
		LDA		_apu_chl0+2-$80,X
		BEQ		loc_CCEE
		JSR		_apu_channel_play
loc_CCEE:
		LDA		_cur_apu_chnl_ram_ofs
		CLC
		ADC		#$10
		CMP		#$E0
		BNE		loc_CCF8
		RTS
; ---------------------------------------------------------------------------
loc_CCF8:
		TAX
		LDA		_cur_apu_chnl_ofs
		CLC
		ADC		#$04
		AND		#$0F
		TAY
		BCC		loc_CCE3

; =============== S U B	R O U T	I N E =======================================
_apu_channel_play:
		LDY		#$00
		LDA		_apu_chl0+3-$80,X
		STA		_cur_track_data_ptr
		LDA		_apu_chl0+4-$80,X
		STA		_cur_track_data_ptr+1
		DEC		_apu_chl0-$80,X
		BNE		loc_CD14
		JMP		_apu_cmd_fetch
; ---------------------------------------------------------------------------
loc_CD14:
		LDA		byte_2D
		BEQ		loc_CD44
		STA		byte_EF
		LDA		#$78
		CMP		_apu_chl0+2-$80,X
		BNE		loc_CD23
		JMP		_apu_more_parse
; ---------------------------------------------------------------------------
loc_CD23:
		INC		_apu_chl0-$80,X
		LDA		#$30
		STA		_apu_PULSE2_ENV
		JSR		_apu_delay
		LDA		#$00
		STA		_apu_TRI_COUNT
		JSR		_apu_delay
		LDA		#$30
		STA		_apu_NOISE_ENV
		JSR		_apu_delay
		LDA		#$00
		STA		byte_EE
		STA		byte_B2
		RTS
; ---------------------------------------------------------------------------
loc_CD44:
		LDA		byte_EF
		BEQ		loc_CD4B
		JSR		sub_CD52
loc_CD4B:
		LDA		#$00
		STA		byte_EF
		JMP		_apu_more_parse

; =============== S U B	R O U T	I N E =======================================
sub_CD52:
		LDA		#$00
		STA		_apu_chl0+1
		RTS

; =============== S U B	R O U T	I N E =======================================
_apu_cmd_fetch:
		LDA		(_cur_track_data_ptr),Y
		CMP		#$FD
		BCC		_apu_data
_apu_cmdFD:
		BNE		loc_CD7A
		LDX		_cur_apu_chnl_ram_ofs
		LDA		_apu_chl0+8-$80,X
		ORA		#$08
		STA		_apu_chl0+8-$80,X
		JSR		_apu_jsr
		INY
		TYA
		CLC
		ADC		_cur_track_data_ptr
		STA		_apu_chl0+$E-$80,X
		LDA		#$00
		ADC		_cur_track_data_ptr+1
		STA		_apu_chl0+$F-$80,X
		JMP		sub_CCD8
; ---------------------------------------------------------------------------
loc_CD7A:
		CMP		#$FE
		BNE		_apu_cmdFF
		JMP		_apu_cmdFE
; ---------------------------------------------------------------------------
_apu_cmdFF:
		CPX		#_apu_chl3
		BEQ		loc_CD8B
		LDA		_apu_chl0+8-$80,X
		AND		#$08
		BNE		_apu_cmdFF_B
loc_CD8B:
		JMP		_apu_cmdFF_A
; ---------------------------------------------------------------------------
_apu_cmdFF_B:
		LDA		_apu_chl0+8-$80,X
		AND		#$F7
		STA		_apu_chl0+8-$80,X
		LDA		_apu_chl0+$E-$80,X
		STA		_apu_chl0+3-$80,X
		LDA		_apu_chl0+$F-$80,X
		STA		_apu_chl0+4-$80,X
		JMP		sub_CCD8
; ---------------------------------------------------------------------------
_apu_data:
		CPX		#_apu_chl3
		BEQ		_apu_chnl3_parse
		LDA		_apu_chl0+8-$80,X
		AND		#$01
		BEQ		_apu_chnl3_parse
		JMP		_apu_other_parse

; =============== S U B	R O U T	I N E =======================================
_apu_chnl3_parse:
		LDA		(_cur_track_data_ptr),Y
		AND		#$F0
		CMP		#$20
		BNE		loc_CDD3
		LDA		(_cur_track_data_ptr),Y
		AND		#$0F
		STA		_apu_chl0+9-$80,X
		INY
		LDA		(_cur_track_data_ptr),Y
		JSR		_apu_check_chnl
		BCS		loc_CDCA
		LDX		_cur_apu_chnl_ofs
		STA		_apu_PULSE1_ENV,X
		JSR		_apu_delay
loc_CDCA:
		LDX		_cur_apu_chnl_ram_ofs
		CPX		#_apu_chl2
		BEQ		loc_CDD2
		STA		_apu_chl0+7-$80,X
loc_CDD2:
		INY
loc_CDD3:
		LDA		_apu_chl0+9-$80,X
		STA		_apu_chl0-$80,X
		CPX		#_apu_chl2
		BEQ		loc_CE32
		LDA		(_cur_track_data_ptr),Y
		CMP		#$11
		BNE		loc_CDEB
		LDA		_apu_chl0+8-$80,X
		ORA		#$10
		STA		_apu_chl0+8-$80,X
		INY
		JMP		_apu_chnl3_parse
; ---------------------------------------------------------------------------
loc_CDEB:
		CMP		#$10
		BNE		loc_CE08
		JSR		_apu_fetch_byte
		INY
		JSR		_apu_check_chnl
		BCS		loc_CE00
		LDX		_cur_apu_chnl_ofs
		STA		_apu_PULSE1_SWEEP,X
		JSR		_apu_delay
loc_CE00:
		LDX		_cur_apu_chnl_ram_ofs
		LDA		_apu_chl0+8-$80,X
		ORA		#$80
		STA		_apu_chl0+8-$80,X
loc_CE08:
		LDA		_apu_chl0+7-$80,X
		AND		#$10
		BEQ		loc_CE32
		LDA		_apu_chl0+7-$80,X
		AND		#$F0
		STA		_apu_chl0+7-$80,X
		LDA		(_cur_track_data_ptr),Y
		CMP		#$F8
		BNE		loc_CE1D
		INY
		LDA		(_cur_track_data_ptr),Y
loc_CE1D:
		LSR
		LSR
		LSR
		LSR
		ORA		_apu_chl0+7-$80,X
		STA		_apu_chl0+7-$80,X
		JSR		_apu_check_chnl
		BCS		loc_CE32
		LDX		_cur_apu_chnl_ofs
		STA		_apu_PULSE1_ENV,X
		JSR		_apu_delay
loc_CE32:
		LDA		(_cur_track_data_ptr),Y
		AND		#$07
		STA		byte_BC
		INY
		LDA		(_cur_track_data_ptr),Y
		STA		byte_BD
		LDX		_cur_apu_chnl_ram_ofs
		JSR		_apu_parse_more
		JMP		_apu_unpade_data_pc

; =============== S U B	R O U T	I N E =======================================
_apu_more_parse:
		CPX		#_apu_chl3
		BEQ		locret_CE4F
		LDA		_apu_chl0+8-$80,X
		AND		#$01
		BNE		loc_CE50
locret_CE4F:
		RTS
; ---------------------------------------------------------------------------
loc_CE50:
		CPX		#_apu_chl2
		BNE		loc_CE55
		RTS
; ---------------------------------------------------------------------------
loc_CE55:
		LDA		_cur_track_data_ptr
		BNE		loc_CE5B
		DEC		_cur_track_data_ptr+1
loc_CE5B:
		DEC		_cur_track_data_ptr
		LDY		#$00
		LDA		(_cur_track_data_ptr),Y
		AND		#$F0
		CMP		#$C0
		BNE		loc_CE68
		RTS
; ---------------------------------------------------------------------------
loc_CE68:
		LDA		_apu_chl0+7-$80,X
		AND		#$10
		BNE		loc_CE6F
		RTS
; ---------------------------------------------------------------------------
loc_CE6F:
		LDA		_apu_chl0+$B-$80,X
		SEC
		SBC		#$01
		STA		_apu_chl0+$B-$80,X
		CMP		_apu_chl0-$80,X
		BNE		loc_CE82
		SEC
		SBC		_apu_chl0+$D-$80,X
		BCC		loc_CE87
		BEQ		loc_CE87
		RTS
; ---------------------------------------------------------------------------
loc_CE82:
		SEC
		SBC		#$01
		STA		_apu_chl0+$B-$80,X
loc_CE87:
		LDA		_apu_chl0+7-$80,X
		AND		#$0F
		SEC
		SBC		#$01
		BPL		loc_CE91
		RTS
; ---------------------------------------------------------------------------
loc_CE91:
		LDA		_apu_chl0+7-$80,X
		SBC		#$01
		STA		_apu_chl0+7-$80,X
		JSR		_apu_check_chnl
		BCS		loc_CEA1
		LDX		_cur_apu_chnl_ofs
		STA		_apu_PULSE1_ENV,X
loc_CEA1:
		JSR		_apu_delay
		RTS

; =============== S U B	R O U T	I N E =======================================
sub_CEA5:
		JMP		_apu_cmd_fetch

; =============== S U B	R O U T	I N E =======================================
_j_apu_cmdFD:
		JMP		_apu_cmdFD

; =============== S U B	R O U T	I N E =======================================
_apu_other_parse:
		LDA		byte_2D
		BNE		loc_CEB2
		JMP		loc_CEB5
; ---------------------------------------------------------------------------
loc_CEB2:
		JMP		loc_CD14
; ---------------------------------------------------------------------------
loc_CEB5:
		LDA		(_cur_track_data_ptr),Y
		AND		#$F0
		CMP		#$D0
		BNE		loc_CEDC
		LDA		(_cur_track_data_ptr),Y
		AND		#$0F
		STA		_apu_chl0+9-$80,X
		INY
		LDA		(_cur_track_data_ptr),Y
		STA		_apu_chl0+5-$80,X
		INY
		CPX		#_apu_chl2
		BEQ		loc_CF03
		LDA		(_cur_track_data_ptr),Y
		LSR
		LSR
		LSR
		LSR
		STA		_apu_chl0+$C-$80,X
		LDA		(_cur_track_data_ptr),Y
		AND		#$0F
		STA		_apu_chl0+$D-$80,X
		INY
loc_CEDC:
		CPX		#_apu_chl2
		BEQ		loc_CF03
		LDA		(_cur_track_data_ptr),Y
		CMP		#$FD
		BCS		_j_apu_cmdFD
		CMP		#$F0
		BNE		loc_CF03
		JSR		_apu_fetch_byte
		JSR		_apu_check_chnl
		BCS		loc_CEFA
		LDX		_cur_apu_chnl_ofs
		STA		_apu_PULSE1_SWEEP,X
		JSR		_apu_delay
loc_CEFA:
		LDX		_cur_apu_chnl_ram_ofs
		LDA		_apu_chl0+8-$80,X
		ORA		#$80
		STA		_apu_chl0+8-$80,X
		INY
loc_CF03:
		LDA		(_cur_track_data_ptr),Y
		CMP		#$E8
		BEQ		_apu_dataE8
		CMP		#$E9
		BEQ		_apu_dataE9
		CMP		#$EA
		BEQ		_apu_dataEA
		CMP		#$EB
		BEQ		_apu_dataEB
		CMP		#$EC
		BEQ		_apu_dataEC
		CMP		#$EE
		BEQ		_apu_dataEE
		CMP		#$EF
		BEQ		_apu_dataEF
		CMP		#$ED
		BEQ		_apu_dataED
		AND		#$F0
		CMP		#$E0
		BNE		loc_CF69
		LDA		(_cur_track_data_ptr),Y
		AND		#$0F
		STA		_apu_chl0+$A-$80,X
		INY
		JMP		_apu_cmd_fetch
; ---------------------------------------------------------------------------
_apu_dataEA:
		LDA		#$02
		JMP		loc_CF58
; ---------------------------------------------------------------------------
_apu_dataE9:
		LDA		#$01
		JMP		loc_CF58
; ---------------------------------------------------------------------------
_apu_dataEB:
		LDA		#$03
		JMP		loc_CF58
; ---------------------------------------------------------------------------
_apu_dataEC:
		LDA		#$1F
		JMP		loc_CF58
; ---------------------------------------------------------------------------
_apu_dataEE:
		LDA		#$21
		JMP		loc_CF58
; ---------------------------------------------------------------------------
_apu_dataEF:
		LDA		#$23
		JMP		loc_CF58
; ---------------------------------------------------------------------------
_apu_dataED:
		LDA		#$25
		JMP		loc_CF58
loc_CF58:
		JSR		_apu_load
		INY
		JMP		_apu_other_parse
; ---------------------------------------------------------------------------
_apu_dataE8:
		LDA		_apu_chl0+8-$80,X
		ORA		#$10
		STA		_apu_chl0+8-$80,X
		INY
		JMP		_apu_other_parse
; ---------------------------------------------------------------------------
loc_CF69:
		JSR		_apu_unpade_data_pc
		DEY
		LDA		(_cur_track_data_ptr),Y
		AND		#$0F
		STA		byte_BC
		BEQ		loc_CF80
		LDA		_apu_chl0+9-$80,X
		CLC
loc_CF78:
		ADC		_apu_chl0+9-$80,X
		DEC		byte_BC
		BNE		loc_CF78
		BEQ		loc_CF82
loc_CF80:
		LDA		_apu_chl0+9-$80,X
loc_CF82:
		STA		_apu_chl0-$80,X
		LDA		(_cur_track_data_ptr),Y
		AND		#$F0
		CMP		#$C0
		BEQ		loc_CFB5
		CPX		#_apu_chl2
		BEQ		loc_CF97
		LDA		_apu_chl0-$80,X
		CLC
		ADC		_apu_chl0+$C-$80,X
		STA		_apu_chl0+$B-$80,X
loc_CF97:
		LDA		_apu_chl0+5-$80,X
		CPX		#_apu_chl2
		BEQ		loc_CF9F
		STA		_apu_chl0+7-$80,X
loc_CF9F:
		JSR		_apu_check_chnl
		BCS		loc_CFAC
		LDX		_cur_apu_chnl_ofs
		STA		_apu_PULSE1_ENV,X
		JSR		_apu_delay
loc_CFAC:
		LDA		(_cur_track_data_ptr),Y
		LSR
		LSR
		LSR
		LSR
		JMP		loc_CFCB
; ---------------------------------------------------------------------------
loc_CFB5:
		LDA		#$30
		CPX		#_apu_chl2
		BNE		loc_CFBD
		LDA		#$00
loc_CFBD:
		JSR		_apu_check_chnl
		BCS		loc_CFC7
		LDX		_cur_apu_chnl_ofs
		STA		_apu_PULSE1_ENV,X
loc_CFC7:
		JSR		_apu_delay
		RTS
; ---------------------------------------------------------------------------
loc_CFCB:
		LDX		_cur_apu_chnl_ram_ofs
		ASL
		TAY
		LDA		byte_D087,Y
		STA		byte_BC
		INY
		LDA		byte_D087,Y
		STA		byte_BD
		LDY		_apu_chl0+$A-$80,X
loc_CFDC:
		TYA
		CMP		#$04
		BEQ		_apu_parse_more
		LSR		byte_BC
		ROR		byte_BD
		INY
		JMP		loc_CFDC

; =============== S U B	R O U T	I N E =======================================
_apu_parse_more:
		CPX		#_apu_chl2
		BCS		loc_CFF9
		LDA		_apu_chl0+8-$80,X
		AND		#$10
		BEQ		loc_CFF9
		INC		byte_BD
		BNE		loc_CFF9
		INC		byte_BC
loc_CFF9:
		LDA		byte_BC
		ORA		#$08
		STA		byte_BC
		CPX		#_apu_chl2
		BEQ		loc_D01B
		CMP		_apu_chl0+1-$80,X
		BNE		loc_D019
		CPX		#_apu_chl3
		BEQ		loc_D02C
		LDA		_apu_chl0+7-$80,X
		AND		#$10
		BEQ		loc_D01B
		LDA		_apu_chl0+8-$80,X
		AND		#$80
		BNE		loc_D01B
		BEQ		loc_D02C
loc_D019:
		STA		_apu_chl0+1-$80,X
loc_D01B:
		LDA		byte_BC
		JSR		_apu_check_chnl
		BCS		loc_D02C
		LDX		_cur_apu_chnl_ofs
		STA		_apu_PULSE1_LEN,X
		JSR		_apu_delay
		LDX		_cur_apu_chnl_ram_ofs
loc_D02C:
		LDA		byte_BD
		CPX		#_apu_chl0
		BEQ		loc_D039
		CPX		#_apu_chl1
		BEQ		loc_D03E
		JMP		loc_D040
; ---------------------------------------------------------------------------
loc_D039:
		STA		byte_A7
		JMP		loc_D040
; ---------------------------------------------------------------------------
loc_D03E:
		STA		byte_B8
loc_D040:
		JSR		_apu_check_chnl
		BCS		loc_D04A
		LDX		_cur_apu_chnl_ofs
		STA		_apu_PULSE1_TIME,X
loc_D04A:
		JSR		_apu_delay
		RTS

; =============== S U B	R O U T	I N E =======================================
_apu_unpade_data_pc:
		INY
		TYA
		CLC
		ADC		_cur_track_data_ptr
		LDX		_cur_apu_chnl_ram_ofs
		STA		_apu_chl0+3-$80,X
		BCC		locret_D05F
		LDA		_cur_track_data_ptr+1
		ADC		#$00
		STA		_apu_chl0+4-$80,X
locret_D05F:
		RTS

; =============== S U B	R O U T	I N E =======================================
_apu_fetch_byte:
		INY
		LDA		(_cur_track_data_ptr),Y
		CPX		#_apu_chl0
		BEQ		loc_D06E
		CPX		#_apu_chl1
		BEQ		loc_D073
		JMP		locret_D075
; ---------------------------------------------------------------------------
loc_D06E:
		STA		byte_A1
		JMP		locret_D075
; ---------------------------------------------------------------------------
loc_D073:
		STA		byte_B5
locret_D075:
		RTS

; =============== S U B	R O U T	I N E =======================================
_apu_check_chnl:
		LDX		_cur_apu_chnl_ram_ofs
		CPX		#_apu_chl0
		BNE		loc_D083
		LDX		byte_C2
		BEQ		loc_D083
		SEC
		BCS		loc_D084
loc_D083:
		CLC
loc_D084:
		LDX		_cur_apu_chnl_ram_ofs
		RTS
; ---------------------------------------------------------------------------
byte_D087:
		.BYTE $06,$AE
		.BYTE $06,$4E
		.BYTE $05,$F4
		.BYTE $05,$9E
		.BYTE $05,$4E
		.BYTE $05,$01
		.BYTE $04,$B9
		.BYTE $04,$76
		.BYTE $04,$36
		.BYTE $03,$F9
		.BYTE $03,$C0
		.BYTE $03,$8A
_apu_track_lib:
		.BYTE $0C
		.WORD _apu01
		.BYTE $0C
		.WORD _apu02
		.BYTE $10
		.WORD _apu03
		.BYTE $10
		.WORD _apu04
		.BYTE $0C
		.WORD _apu05
		.BYTE $0C
		.WORD _apu06
		.BYTE $0C
		.WORD _apu07
		.BYTE $0C
		.WORD _apu08
		.BYTE $10
		.WORD _apu09
		.BYTE $10
		.WORD _apu0A
		.BYTE $50
		.WORD _apu0B
		.BYTE $0C
		.WORD _apu0C
		.BYTE $50
		.WORD _apu0D
		.BYTE $0C
		.WORD _apu0E
		.BYTE $50
		.WORD _apu0F
		.BYTE $0C
		.WORD _apu10
		.BYTE $50
		.WORD _apu11
		.BYTE $0C
		.WORD _apu12
		.BYTE $50
		.WORD _apu13
		.BYTE $0C
		.WORD _apu14
		.BYTE $50
		.WORD _apu15
		.BYTE $0C
		.WORD _apu16
		.BYTE $10
		.WORD _apu17
		.BYTE $0C
		.WORD _apu18
		.BYTE $10
		.WORD _apu19
		.BYTE $50
		.WORD _apu1A
		.BYTE $0C
		.WORD _apu1B
		.BYTE $10
		.WORD _apu1C
		.BYTE $50
		.WORD _apu1D
		.BYTE $0C
		.WORD _apu1E
		.BYTE $50
		.WORD _apu1F
		.BYTE $0C
		.WORD _apu20
		.BYTE $50
		.WORD _apu21
		.BYTE $0C
		.WORD _apu22
		.BYTE $50
		.WORD _apu1F
		.BYTE $0C
		.WORD _apu20
		.BYTE $0C
		.WORD _apu25
		.BYTE $80
		.WORD _apu26
		.BYTE $04
		.WORD _apu27
		.BYTE $08
		.WORD _apu28
		.BYTE $80
		.WORD _apu29
		.BYTE $04
		.WORD _apu2A
		.BYTE $08
		.WORD _apu2B
		.BYTE $80
off_D121:
		.WORD _apu2C
		.BYTE $04
		.WORD _apu2D
		.BYTE $08
		.WORD _apu2E
		.BYTE $80
		.WORD _apu2F
		.BYTE $04
		.WORD _apu30
		.BYTE $08
		.WORD _apu31
		.BYTE $80
		.WORD _apu32
		.BYTE $04
		.WORD _apu33
		.BYTE $08
		.WORD _apu34
		.BYTE $80
		.WORD _apu35
		.BYTE $04
		.WORD _apu36
		.BYTE $08
		.WORD _apu37
		.BYTE $80
		.WORD _apu38
		.BYTE $04
		.WORD _apu39
		.BYTE $08
		.WORD _apu3A
		.BYTE $80
		.WORD _apu3B
		.BYTE $04
		.WORD _apu3C
		.BYTE $08
		.WORD _apu3D
		.BYTE $80
		.WORD _apu3E
		.BYTE $04
		.WORD _apu3F
		.BYTE $08
		.WORD _apu40
		.BYTE $80
		.WORD _apu41
		.BYTE $04
		.WORD _apu42
		.BYTE $08
		.WORD _apu43
		.BYTE $80
		.WORD _apu44
		.BYTE $04
		.WORD _apu45
		.BYTE $08
		.WORD _apu46
		.BYTE $80
		.WORD _apu47
		.BYTE $04
		.WORD _apu48
		.BYTE $08
		.WORD _apu49
		.BYTE $80
		.WORD _apu4A
		.BYTE $04
		.WORD _apu4B
		.BYTE $08
		.WORD _apu4C
		.BYTE $80
		.WORD _apu4D
		.BYTE $04
		.WORD _apu4E
		.BYTE $08
		.WORD _apu4F
		.BYTE $80
		.WORD _apu50
		.BYTE $04
		.WORD _apu51
		.BYTE $08
		.WORD _apu52
		.BYTE $00
		.WORD _apu53
		.BYTE $00
		.WORD _apu54
		.BYTE $80
		.WORD _apu55
		.BYTE $04
		.WORD _apu56
		.BYTE $08
		.WORD _apu57
		.BYTE $80
		.WORD _apu58
		.BYTE $04
		.WORD _apu59
		.BYTE $08
		.WORD _apu5A
		.BYTE $80
		.WORD _apu5B
		.BYTE $04
		.WORD _apu5C
		.BYTE $08
		.WORD _apu5D
		.BYTE $80
		.WORD _apu5E
		.BYTE $04
		.WORD _apu5F
		.BYTE $08
		.WORD _apu60
		.BYTE $80
		.WORD _apu61
		.BYTE $04
		.WORD _apu62
		.BYTE $08
		.WORD _apu63
		.BYTE $80
		.WORD _apu64
		.BYTE $04
		.WORD _apu64
		.BYTE $08
		.WORD _apu64
		.BYTE $80
		.WORD _apu64
		.BYTE $04
		.WORD _apu64
		.BYTE $08
		.WORD _apu64
		.BYTE $80
		.WORD _apu6A
		.BYTE $04
		.WORD _apu6B
		.BYTE $08
		.WORD _apu6C
		.BYTE $50
		.WORD _apu15
		.BYTE $0C
		.WORD _apu16
		.BYTE $80
		.WORD _apu6f
		.BYTE $04
		.WORD _apu70
		.BYTE $08
		.WORD _apu71
		.BYTE $80
		.WORD _apu72
		.BYTE $04
		.WORD _apu73
		.BYTE $08
		.WORD _apu74
		.BYTE $80
		.WORD _apu75
		.BYTE $04
		.WORD _apu76
		.BYTE $08
		.WORD _apu77
		.BYTE $10
		.WORD _apu78
		.BYTE $C0
		.WORD _apu64
		.BYTE $04
		.WORD _apu64
		.BYTE $08
		.WORD _apu64
		.BYTE $0C
		.WORD _apu64
		.BYTE $C0
		.WORD _apu64
		.BYTE $04
		.WORD _apu64
		.BYTE $08
		.WORD _apu64
		.BYTE $0C
		.WORD _apu64
_apu78:
		.BYTE $25,$82
_apu64:
		.BYTE $00
		.BYTE $D5,$00,$8E,$00,$A9,$22,$B0,$C0,$6A,$B0,$6A,$90,$6A,$80,$6A,$70
		.BYTE $6A,$50,$6A,$30,$6A,$40,$6A,$FF
_apu01:
		.BYTE $22,$30,$50,$06,$30,$06,$F8,$20,$06,$F8,$10,$01,$FF
_apu02:
		.BYTE $21,$30,$70,$03,$30,$01,$F8,$10,$01,$FF
_apu1C:
		.BYTE $25,$B0,$10,$8B,$B1,$CD,$70,$FC,$91,$CD,$50,$FC,$71,$CD,$30,$FC
		.BYTE $51,$CD,$F8,$20,$FC,$31,$CD,$F8,$10,$FC,$F8,$21,$CD,$FF
_apu1D:
		.BYTE $23,$B0,$10,$83,$F2,$33,$00,$00
_apu13:
		.BYTE $27,$B0,$10,$83,$F2,$20,$D1,$28,$A1,$20,$71,$18,$41,$10,$31,$00
		.BYTE $F8,$20,$F0,$F8,$10,$D0,$FF
_apu1E:
		.BYTE $23,$10,$F0,$0F,$00,$00
_apu14:
		.BYTE $28,$10,$F0,$0F,$C0,$0C,$90,$0D,$60,$0D,$40,$0D,$30,$0D,$F8,$20
		.BYTE $0D,$F8,$10,$0D,$FF
_apu09:
		.BYTE $22,$B0,$10,$84,$F8,$10,$40,$F8,$20,$50,$30,$60,$40,$80,$40,$A0
		.BYTE $40,$C0,$40,$E0,$41,$00,$41,$20,$41,$40,$41,$60,$31,$80,$FF
_apu0F:
		.BYTE $23,$B0,$10,$83,$F2,$F4,$D3,$00,$93,$0D,$73,$18,$53,$38,$42,$A8
		.BYTE $32,$58,$32,$10,$F8,$21,$BD,$FF
_apu10:
		.BYTE $24,$10,$00,$00,$F0,$0E,$D0,$0E,$90,$0E,$70,$0D,$50,$0D,$40,$0D
		.BYTE $30,$0D,$30,$0D,$F8,$20,$0C,$FF
_apu06:
		.BYTE $21,$10,$90,$0A,$30,$0B,$50,$08,$30,$0A,$F8,$10,$09,$FF
_apu17:
		.BYTE $21,$F0,$10,$84,$A1,$77,$31,$77,$F8,$21,$77,$31,$77,$FF
_apu18:
		.BYTE $22,$10,$F0,$0D,$21,$30,$00,$00,$22,$30,$F0,$0A,$FF
_apu05:
		.BYTE $21,$30,$60,$09,$70,$0A,$80,$0B,$90,$0C,$80,$0A,$70,$09,$FF
_apu07:
		.BYTE $21,$30,$B0,$03,$B0,$06,$B0,$09,$C0,$0C,$C0,$0D,$D0,$0B,$C0,$08
		.BYTE $B0,$04,$FF
_apu11:
		.BYTE $25,$30,$10,$82,$F1,$28,$B0,$F4,$70,$D8,$30,$B4,$FF
_apu12:
		.BYTE $27,$F0,$00,$00,$F0,$0D,$B0,$0E,$70,$0D,$40,$0E,$F8,$20,$0C,$FF
_apu16:
		.BYTE $29,$F0,$00,$00,$F0,$0E,$B0,$0F,$70,$0E,$40,$0F,$F8,$20,$0E,$FF
_apu15:
		.BYTE $27,$F0,$10,$82,$F1,$30,$D0,$F4,$70,$D8,$40,$B8,$FF
_apu0D:
		.BYTE $22,$F0,$10,$82,$E1,$18,$F8,$10,$B0
		.WORD $06FE
		.WORD _apu0D
		.BYTE $31,$20,$F8,$20,$D0,$00,$00,$F8,$21,$18,$F8,$11,$17,$FF
_apu0E:
		.BYTE $22,$10,$E0,$0B,$F8,$20,$0E
		.WORD $07FE
		.WORD _apu0E
		.BYTE $70,$0B,$F8,$20,$0E,$30,$0E,$F8,$20,$0B,$00,$00,$40,$0A,$30,$0D
		.BYTE $F8,$20,$0B,$F8,$10,$0B,$FF
_apu0B:
		.BYTE $21,$30,$10,$89,$C2,$5B,$52,$03,$31,$CD,$00,$00,$27,$B0,$10,$84
		.BYTE $51,$48,$31,$00,$30,$BD,$F8,$21,$48,$F8,$11,$00,$FF
_apu0C:
		.BYTE $21,$10,$F0,$0E,$E0,$0B,$C0,$0C,$B0,$0C,$80,$0C,$80,$0C,$40,$0C
		.BYTE $40,$0C,$30,$0C,$F8,$20,$0C,$F8,$10,$0F,$50,$0B,$50,$0B,$40,$0B
		.BYTE $40,$0B,$30,$0B,$30,$0B,$F8,$20,$0B,$F8,$20,$0B,$00,$00,$00,$00
		.BYTE $F8,$20,$0B,$F8,$20,$0B,$FF
_apu1A:
		.BYTE $26,$F0,$10,$83,$30,$4D,$22,$30,$10,$8E,$F0,$66,$90,$5A,$60,$50
		.BYTE $50,$48,$40,$44,$30,$3F,$F8,$20,$3F,$F8,$10,$3F,$F8,$10,$3F,$F8
		.BYTE $10,$3F,$FF
_apu1B:
		.BYTE $21,$30,$70,$09,$80,$09,$90,$09,$A0,$09,$B0,$09,$C0,$09,$D0,$0A
		.BYTE $D0,$09,$D0,$09,$D0,$0A,$D0,$0B,$60,$0B,$90,$0B,$50,$0B,$40,$0B
		.BYTE $30,$0B,$F8,$20,$0B,$F8,$10,$0A,$FF
_apu29:
		.BYTE $23,$B0,$10,$8D,$F8,$12,$0D,$F8,$21,$E8,$31,$C0,$41,$A0,$51,$80
		.BYTE $51,$60,$51,$40,$51,$20,$51,$00,$50,$E0,$2F,$B0,$10,$88,$50,$C8
		.BYTE $50,$C8,$50,$C8,$50,$C8,$23,$B0,$10,$87,$50,$D0,$50,$D8,$50,$E0
		.BYTE $50,$F0,$51,$00,$51,$10,$51,$20,$51,$40,$51,$60,$41,$88,$31,$B0
		.BYTE $F8,$21,$D8,$00,$00,$00,$00
		.WORD $02FE
		.WORD _apu29
		.BYTE $FF
_apu2A:
		.BYTE $23,$B0,$10,$8E,$F8,$12,$0A,$F8,$21,$E5,$31,$BD,$41,$9D,$41,$7D
		.BYTE $41,$5D,$41,$3D,$41,$1D,$40,$FD,$40,$E0,$2F,$B0,$10,$88,$40,$C7
		.BYTE $40,$C7,$40,$C7,$40,$C7,$23,$B0,$10,$86,$40,$CF,$40,$D7,$40,$DF
		.BYTE $40,$E7,$40,$EF,$40,$F7,$40,$FD,$41,$0F,$41,$1F,$41,$3F,$31,$5F
		.BYTE $31,$7F,$F8,$21,$AF,$F8,$11,$DF,$00,$00
		.WORD $02FE
		.WORD _apu2A
		.BYTE $FF
_apu2B:
		.BYTE $DF,$10,$C0
		.WORD $12FE
		.WORD _apu2B
		.BYTE $D1,$10,$C0,$C0,$FF
_apu19:
		.BYTE $21,$F0,$10,$87,$F8,$13,$40,$21,$F0,$F8,$22,$C0,$31,$E0,$41,$B8
		.BYTE $51,$90,$61,$80,$71,$70,$71,$68,$71,$60,$71,$58,$71,$50,$71,$48
		.BYTE $71,$40
byte_D523:
		.BYTE $71,$39,$71,$3A,$71,$3B
		.WORD $0AFE
		.WORD byte_D523
		.BYTE $51,$39,$31,$3A,$F8,$21,$3B,$F8,$11,$39,$FF,$28,$30,$10,$84,$30
		.BYTE $76,$50,$86,$70,$96,$90,$A6,$2F,$B0,$10,$84,$B0,$B6,$70,$B6,$30
		.BYTE $B6,$F8,$10,$B6,$FF,$28,$30,$10,$84,$30,$96,$50,$A6,$70,$B6,$90
		.BYTE $C6,$2E,$B0,$10,$84,$B0,$D6,$70,$D6,$30,$D6,$F8,$10,$D6,$FF
_apu6f:
		.BYTE $D7,$B5,$24,$E2,$48,$D7,$B7,$40,$71,$40,$D7,$B5,$24,$B8,$D7,$B7
		.BYTE $40,$71,$40,$D7,$B5,$25,$E1,$21,$C0,$15,$D7,$B7,$40,$E2,$91,$40
		.BYTE $D7,$B5,$24,$95,$D7,$B8,$50,$92,$B2,$D7,$B5,$24,$E1,$05,$D7,$B7
		.BYTE $50,$E2,$72,$42,$D7,$B6,$30,$E1,$20,$C0,$E2,$90,$62,$40,$20,$E3
		.BYTE $90,$60,$90,$E2,$20,$40,$E3,$B0,$90,$88,$FF
_apu70:
		.BYTE $E8,$D7,$B4,$24,$E3,$B8,$D7,$B6,$40,$E2,$41,$E3,$B0,$D7,$B4,$24
		.BYTE $E2,$48,$D7,$B6,$40,$41,$E3,$B0,$D7,$B5,$33,$E2,$91,$C0,$95,$D7
		.BYTE $B6,$40,$41,$E3,$90,$D7,$B4,$24,$E2,$45,$D7,$B7,$50,$42,$62,$D7
		.BYTE $B5,$33,$75,$D7,$B6,$50,$42,$02,$D7,$B5,$30,$E1,$21,$E2,$90,$62
		.BYTE $40,$20,$90,$60,$90,$E2,$20,$40,$E3,$B0,$90,$88,$FF
_apu71:
		.BYTE $D7,$30,$E2,$E9,$42,$D7,$10,$EA,$40,$EA,$40,$EA,$40,$D7,$30,$EA
		.BYTE $42,$EA,$42,$E9,$42,$D7,$10,$EA,$40,$EA,$40,$EA,$40,$D7,$30,$EA
		.BYTE $42,$EA,$42,$E3,$E9,$92,$D7,$10,$EA,$90,$EA,$90,$EA,$90,$D7,$30
		.BYTE $EA,$92,$EA,$92,$E9,$92,$D7,$10,$EA,$90,$EA,$90,$EA,$90,$D7,$30
		.BYTE $E9,$92,$E9,$B2,$E2,$E9,$02,$D7,$10,$EA,$00,$EA,$00,$EA,$00,$D7
		.BYTE $30,$EA,$02,$EA,$02,$D7,$30,$E9,$22,$D7,$10,$E9,$20,$E9,$20,$E9
		.BYTE $20,$D7,$30,$E9,$22,$D7,$10,$E9,$20,$E9,$20,$E9,$20,$E9,$40,$E9
		.BYTE $40,$E9,$40,$D7,$90,$E9,$48,$FF
_apu6B:
		.BYTE $D3,$F6,$11
		.BYTE $FD
		.WORD byte_D69C
		.BYTE $FF
_apu6A:
		.BYTE $E8,$D3,$F6,$11,$C0
		.BYTE $FD
		.WORD byte_D69C
		.BYTE $FF
_apu6C:
		.BYTE $D6,$12,$E2,$A0,$60,$50,$30,$80,$A0,$80,$60,$D6,$77,$45,$CB,$FF
byte_D69C:
		.BYTE $E1,$01,$E2,$A1,$81,$61,$41,$61,$41,$31,$1C,$FF
_apu4A:
		.BYTE $D5,$B3,$00,$E3
byte_D6AC:
		.BYTE $30,$50,$70,$50
		.WORD $03FE
		.WORD byte_D6AC
		.BYTE $30,$50,$70,$70
byte_D6B8:
		.BYTE $80,$A0,$E2,$00,$E3,$A0
		.WORD $03FE
		.WORD byte_D6B8
		.BYTE $80,$A0,$E2,$00,$00
_apu47:
		.BYTE $D5,$77,$36,$E3,$83,$53,$E2,$03,$E3,$A3,$81,$71,$51,$31,$51,$71
		.BYTE $51,$31,$01,$31,$51,$71,$51,$31,$51,$71,$81,$71,$51,$31,$51,$71
		.BYTE $51,$31
		.WORD $FFFE
		.WORD _apu47
_apu4B:
		.BYTE $D5,$B3,$00,$E3
byte_D6F1:
		.BYTE $70,$80,$A0,$80
		.WORD $03FE
		.WORD byte_D6F1
		.BYTE $70,$80,$A0,$B0,$E2
byte_D6FE:
		.BYTE $00,$10,$30,$10
		.WORD $03FE
		.WORD byte_D6FE
		.BYTE $00,$10,$30,$40
_apu48:
		.BYTE $D5,$77,$36,$E2,$03,$E3,$83,$E2,$33,$13,$01,$E3,$A1,$81,$71,$81
		.BYTE $A1,$81,$71,$51,$71,$81,$A1,$81,$71,$81,$A1,$E2,$01,$E3,$A1,$81
		.BYTE $71,$81,$A1,$81,$71
		.WORD $FFFE
		.WORD _apu48
_apu4C:
		.BYTE $D5,$0D,$E2,$EA,$01,$EA,$00,$EA,$00
		.WORD $08FE
		.WORD _apu4C
_apu49:
		.BYTE $D5,$0D
byte_D742:
		.BYTE $E2
		.BYTE $FD
		.WORD byte_D790
		.BYTE $FD
		.WORD byte_D790
		.BYTE $EA,$81,$EA,$80,$EA,$80,$E9,$81,$EA,$80,$EA,$80,$EA,$31,$EA,$30
		.BYTE $EA,$30,$E9,$30,$EA,$30,$EA,$30,$EA,$30
		.BYTE $FD
		.WORD byte_D790
		.BYTE $EA,$11,$EA,$10,$EA,$10,$E9,$11,$EA,$10,$EA,$10,$EA,$31,$EA,$30
		.BYTE $EA,$30,$E9,$31,$EA,$30,$EA,$30,$EA,$01,$EA,$00,$EA,$00,$E9,$00
		.BYTE $E9,$C0,$E9,$00,$E9,$00
		.WORD $FFFE
		.WORD byte_D742
byte_D790:
		.BYTE $EA,$51,$EA,$50,$EA,$50,$E9,$51,$EA,$50,$EA,$50,$FF
_apu3E:
		.BYTE $E8,$D7,$B3,$00,$C1
byte_D7A2:
		.BYTE $FD
		.WORD byte_D7D3
		.BYTE $FD
		.WORD byte_D800
		.WORD $FFFE
		.WORD byte_D7A2
_apu3F:
		.BYTE $D7,$B7,$23
		.BYTE $FD
		.WORD byte_D7D3
		.BYTE $FD
		.WORD byte_D800
		.WORD $FFFE
		.WORD _apu3F
_apu40:
		.BYTE $FD
		.WORD byte_D821
		.BYTE $FD
		.WORD byte_D821
		.BYTE $FD
		.WORD byte_D841
		.BYTE $E9,$21
		.BYTE $FD
		.WORD byte_D841
		.BYTE $D1,$15,$E9,$24,$E9,$24,$E9,$23
		.WORD $FFFE
		.WORD _apu40
byte_D7D3:
		.BYTE $E2,$41,$E3,$41,$A1,$E2,$71,$E3,$41,$A1,$E2,$A1,$E3,$41,$A1,$E2
		.BYTE $41,$E3,$41,$A1,$E2,$31,$E3,$31,$91,$E2,$61,$E3,$31,$91,$E2,$91
		.BYTE $E3,$31,$91,$E2,$31,$E3,$31,$91
		.WORD $02FE
		.WORD byte_D7D3
		.BYTE $FF
byte_D800:
		.BYTE $E1,$67,$91,$E0,$09,$E1,$91,$61,$E1,$51,$E0,$21,$81,$E1,$B1,$E0
		.BYTE $21,$51,$E1,$A1,$E0,$21,$81,$E1,$51,$E0,$21,$51
		.WORD $02FE
		.WORD byte_D800
		.BYTE $FF
byte_D821:
		.BYTE $D7,$15,$E2,$E9,$11,$E9,$11,$E9,$11,$E9,$15
byte_D82C:
		.BYTE $E9,$11
		.WORD $06FE
		.WORD byte_D82C
		.BYTE $E9,$01,$E9,$01,$E9,$01,$E9,$05
byte_D83A:
		.BYTE $E9,$01
		.WORD $06FE
		.WORD byte_D83A
		.BYTE $FF
byte_D841:
		.BYTE $E9,$31,$E9,$31,$E9,$31,$D1,$15
byte_D849:
		.BYTE $E9,$32
		.WORD $0EFE
		.WORD byte_D849
		.BYTE $D7,$15,$E9,$31,$E9,$30,$E9,$C0,$E9,$31,$E9,$31,$31,$31,$E9,$21
		.BYTE $E9,$21,$E9,$21,$E9,$25,$E9,$21,$E9,$21,$E9,$21,$E9,$21,$E9,$21
		.BYTE $FF

; ==========================
; ==== BGM 1================
; ==========================

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

; ==========================
; ==== BGM 1================
; ==========================

_apu32:
		.BYTE $D4,$75,$33,$E2
		.BYTE $FD
		.WORD byte_243C5
		.BYTE $01,$01
		.BYTE $FD
		.WORD byte_243C5
		.BYTE $11,$31
_apu35:
		.BYTE $D4,$B5,$33,$E2,$81,$C1,$81,$0B,$01,$31,$51,$37,$31,$01,$E3,$AB
		.BYTE $E2,$11,$51,$71,$8B,$51,$71,$81,$E1,$0B,$E2,$A5,$75
		.WORD $02FE
		.WORD _apu35
byte_2402F:
		.BYTE $E2,$81,$A1,$E1,$01,$E2,$85,$D4,$B4,$33,$51,$01,$01,$D4,$B5,$33
		.BYTE $81,$A1,$E1,$01,$E2,$A1,$A1,$C1,$51,$51,$C1,$21,$21,$C1,$51,$51
		.BYTE $C1
		.WORD $02FE
		.WORD byte_2402F
		.BYTE $D4,$B5,$33,$E2,$81,$C1,$81,$0B,$01,$31,$01,$81,$C1,$81,$0B,$01
		.BYTE $71,$81,$A1,$C1,$A1,$5B,$21,$51,$A1,$E1,$1B,$05,$45,$D4,$75,$33
		.BYTE $E2,$51,$71,$81,$E1,$05,$D4,$B4,$33,$E2,$51,$01,$01,$D4,$75,$33
		.BYTE $A1,$81,$71,$85,$D4,$B4,$33,$E2,$01,$21,$31,$51,$71,$51,$31,$21
		.BYTE $01,$D4,$75,$33,$51,$71,$81,$E1,$05,$D4,$B4,$33,$E2,$51,$01,$01
		.BYTE $D4,$75,$33,$A1,$81,$71,$85,$D4,$B4,$33,$E2,$51,$71,$81,$A1,$E1
		.BYTE $01,$E2,$A1,$81,$71,$81,$D4,$75,$33,$E2,$A1,$C1,$E2,$21,$2B,$21
		.BYTE $51,$71,$51,$C1,$01,$05,$D4,$B4,$33,$01,$31,$51,$71,$51,$31,$D4
		.BYTE $75,$33,$E1,$21,$C1,$E2,$21,$2B,$21,$51,$71,$51,$C1,$01,$0B,$C5
		.BYTE $D4,$75,$33,$E3,$71,$71,$71,$71,$E2,$01,$21,$45,$01,$21,$41,$5B
		.BYTE $35,$15,$E3,$A1,$A1,$A1,$A1,$E2,$31,$51,$75,$E3,$A1,$E2,$31,$71
		.BYTE $AB,$85,$75,$71,$41,$71,$75,$D4,$B4,$33,$E2,$41,$51,$71,$51,$41
		.BYTE $71
		.WORD $FFFE
		.WORD _apu35
_apu33:
		.BYTE $D4,$75,$33,$E2
		.BYTE $FD
		.WORD byte_243D4
		.BYTE $41,$41
		.BYTE $FD
		.WORD byte_243D4
		.BYTE $51,$71
_apu36:
		.BYTE $D4,$B6,$33,$E1,$01,$C1,$01,$E2,$5B,$51,$71,$81,$77,$71,$51,$3B
		.BYTE $51,$81,$A1,$E1,$0B,$E2,$81,$A1,$E1,$01,$3B,$25,$E2,$A5
		.WORD $02FE
		.WORD _apu36
byte_24149:
		.BYTE $D4,$B6,$33,$E1,$01,$21,$31,$57,$D4,$B5,$33,$E2,$51,$51,$D4,$B6
		.BYTE $33,$E1,$01,$21,$31,$21,$21,$C1,$E2,$A1,$A1,$C1,$51,$51,$C1,$A1
		.BYTE $A1,$C1
		.WORD $02FE
		.WORD byte_24149
		.BYTE $D4,$B6,$33,$E1,$01,$C1,$01,$E2,$5B,$51,$71,$51,$E1,$01,$C1,$01
		.BYTE $E2,$5B,$51,$A1,$E1,$01,$21,$C1,$21,$E2,$AB,$51,$A1,$E1,$21,$5B
		.BYTE $45,$75,$D4,$76,$33,$E2,$81,$A1,$E1,$01,$37,$D4,$B5,$33,$E2,$51
		.BYTE $51,$D4,$76,$33,$E1,$21,$01,$E2,$A1,$E1,$05,$D4,$B5,$33,$E2,$31
		.BYTE $51,$71,$81,$A1,$81,$71,$51,$31,$D4,$76,$33,$E2,$81,$A1,$E1,$01
		.BYTE $37,$D4,$B5,$33,$E2,$51,$51,$D4,$76,$33,$E1,$21,$01,$E2,$A1,$E1
		.BYTE $05,$D4,$B5,$33,$E2,$81,$A1,$E1,$01,$21,$31,$21,$01,$E2,$A1,$E1
		.BYTE $01,$D4,$76,$33,$E1,$21,$C1,$E2,$51,$5B,$51,$81,$A1,$81,$C1,$51
		.BYTE $55,$D4,$B5,$33,$51,$71,$81,$A1,$81,$71,$D4,$76,$33,$E1,$51,$C1
		.BYTE $E2,$51,$5B,$51,$81,$A1,$81,$C1,$51,$5B,$C5,$D4,$76,$33,$E2,$01
		.BYTE $01,$01,$01,$41,$51,$75,$41,$51,$71,$8B,$75,$55,$31,$31,$31,$31
		.BYTE $71,$81,$A5,$31,$71,$A1,$E1,$1B,$05,$E2,$A5,$E1,$01,$E2,$71,$A1
		.BYTE $E1,$05,$D4,$B5,$33,$E2,$71,$81,$A1,$81,$71,$A1
		.WORD $FFFE
		.WORD _apu36
_apu34:
		.BYTE $D4,$10,$E2,$E9,$51,$E9,$51,$E9,$51,$E9,$51,$EA,$C1,$EA,$C1,$E9
		.BYTE $31,$E9,$31,$E9,$31,$E9,$31,$EA,$C1,$EA,$C1,$E9,$11,$E9,$11,$E9
		.BYTE $11,$E9,$11,$EA,$C1,$EA,$C1,$E9,$01,$E9,$01,$E9,$01,$E9,$01,$E9
		.BYTE $01,$E9,$01
		.WORD $02FE
		.WORD _apu34
_apu37:
		.BYTE $D4,$10,$E2
		.BYTE $FD
		.WORD byte_243E3
		.BYTE $FD
		.WORD byte_243E3
		.BYTE $FD
		.WORD byte_243F0
		.BYTE $FD
		.WORD byte_243F0
		.BYTE $FD
		.WORD byte_243FD
		.BYTE $FD
		.WORD byte_243FD
		.BYTE $FD
		.WORD byte_2440A
		.BYTE $FD
		.WORD byte_24417
		.BYTE $FD
		.WORD byte_243E3
		.BYTE $FD
		.WORD byte_243E3
		.BYTE $FD
		.WORD byte_243F0
		.BYTE $FD
		.WORD byte_243F0
		.BYTE $FD
		.WORD byte_243FD
		.BYTE $FD
		.WORD byte_243FD
		.BYTE $FD
		.WORD byte_2440A
		.BYTE $FD
		.WORD byte_24417
byte_242A9:
		.BYTE $D4,$10,$E2,$EA,$51,$EA,$51,$EA,$51,$EA,$71,$E9,$71,$E9,$71,$E9
		.BYTE $81,$EA,$81,$EA,$81,$EA,$91,$EA,$91,$EA,$91,$EA,$A1,$EA,$A1,$EA
		.BYTE $A1,$E9,$51,$EA,$51,$EA,$51,$E3,$EA,$A1,$EA,$A1,$EA,$A1,$E2,$E9
		.BYTE $51,$EA,$51,$EA,$51
		.WORD $02FE
		.WORD byte_242A9
		.BYTE $E2
		.BYTE $FD
		.WORD byte_243E3
		.BYTE $FD
		.WORD byte_243E3
		.BYTE $FD
		.WORD byte_2440A
		.BYTE $FD
		.WORD byte_2440A
		.BYTE $FD
		.WORD byte_24417
		.BYTE $FD
		.WORD byte_24417
		.BYTE $E1
		.BYTE $FD
		.WORD byte_243FD
byte_242F9:
		.BYTE $E9,$01
		.WORD $06FE
		.WORD byte_242F9
byte_242FF:
		.BYTE $D4,$10,$E2,$EA,$51,$EA,$81,$E1,$EA,$01,$E2,$E9,$51,$EA,$81,$E1
		.BYTE $EA,$01,$E2,$EA,$51,$EA,$81,$E1,$EA,$01,$E2,$E9,$01,$EA,$51,$EA
		.BYTE $71,$EA,$81,$E1,$EA,$01,$EA,$31,$E2,$E9,$81,$E1,$EA,$01,$EA,$31
		.BYTE $E2,$E9,$81,$E1,$E9,$01,$E9,$31,$E2,$E9,$81,$E1,$E9,$31,$E2,$E9
		.BYTE $31
		.WORD $02FE
		.WORD byte_242FF
byte_24344:
		.BYTE $D4,$10,$E2,$EA,$A1,$E1,$EA,$21,$EA,$51,$E2,$E9,$A1,$E1,$EA,$21
		.BYTE $EA,$51,$E2,$EA,$A1,$E1,$EA,$21,$EA,$51,$E2,$E9,$A1,$E1,$EA,$21
		.BYTE $EA,$51,$E2,$EA,$51,$EA,$81,$E1,$EA,$01,$E2,$E9,$51,$EA,$81,$E1
		.BYTE $EA,$01,$E2,$EA,$51,$EA,$81,$E1,$EA,$01,$E2,$E9,$51,$EA,$81,$E1
		.BYTE $EA,$01
		.WORD $02FE
		.WORD byte_24344
byte_2438A:
		.BYTE $D4,$10,$E2,$EA,$01,$EA,$01,$EA,$01,$E9,$01,$EA,$01,$EA,$01
		.WORD $02FE
		.WORD byte_2438A
		.BYTE $FD
		.WORD byte_243FD
		.BYTE $FD
		.WORD byte_243FD
		.BYTE $FD
		.WORD byte_243F0
		.BYTE $FD
		.WORD byte_243F0
		.BYTE $FD
		.WORD byte_2440A
		.BYTE $FD
		.WORD byte_2440A
		.BYTE $EA,$01,$EA,$01,$EA,$01,$E9,$01,$EA,$01,$EA,$01
byte_243BB:
		.BYTE $E9,$01
		.WORD $06FE
		.WORD byte_243BB
		.WORD $FFFE
		.WORD _apu37
byte_243C5:
		.BYTE $01,$01,$01,$55,$31,$71,$51,$35,$11,$51,$31,$15,$15,$01,$FF
byte_243D4:
		.BYTE $51,$51,$51,$85,$71,$A1,$81,$75,$51,$81,$71,$55,$55,$41,$FF
byte_243E3:
		.BYTE $EA,$51,$EA,$51,$EA,$51,$E9,$51,$EA,$51,$EA,$51,$FF
byte_243F0:
		.BYTE $EA,$31,$EA,$31,$EA,$31,$E9,$31,$EA,$31,$EA,$31,$FF
byte_243FD:
		.BYTE $EA,$11,$EA,$11,$EA,$11,$E9,$11,$EA,$11,$EA,$11,$FF
byte_2440A:
		.BYTE $EA,$81,$EA,$81,$EA,$81,$E9,$81,$EA,$81,$EA,$81,$FF
byte_24417:
		.BYTE $EA,$A1,$EA,$A1,$EA,$A1,$E9,$A1,$EA,$A1,$EA,$A1,$FF
_apu59:
		.BYTE $D2,$B6,$26,$E2,$CE,$47,$43,$D6,$B5,$26,$92,$C0,$42,$C0,$B2,$C0
		.BYTE $D2,$B6,$26,$43,$83,$B3,$E1,$45,$C1,$13,$D6,$B6,$26,$E2,$97,$D2
		.BYTE $B6,$26,$E1,$16,$C0,$E2,$93,$D6,$B6,$26,$62,$C0,$E1,$27,$D2,$B6
		.BYTE $26,$E2,$B7,$83,$D6,$B6,$26,$9B,$FF
_apu58:
		.BYTE $D2,$B5,$25,$E3,$CE,$B7,$B3,$D6,$B5,$25,$E2,$42,$C0,$E3,$92,$C0
		.BYTE $E2,$42,$C0,$D2,$B5,$25,$E3,$B3,$E2,$43,$83,$95,$C1,$43,$D6,$B5
		.BYTE $25,$17,$D2,$B5,$25,$96,$C0,$43,$D6,$B5,$25,$22,$C0,$67,$D2,$B5
		.BYTE $25,$47,$23,$D6,$B5,$25,$1B,$FF
_apu5A:
		.BYTE $D6,$24,$E3,$C8,$E9,$93,$EA,$93,$EA,$43,$D2,$24,$E9,$43,$E9,$C3
		.BYTE $E9,$C3,$D6,$24,$E9,$93,$EA,$93,$EA,$93,$E9,$43,$E9,$23,$E9,$23
		.BYTE $EA,$43,$EA,$43,$E9,$93,$E9,$43,$E9,$93,$FF
_apu5E:
		.BYTE $D6,$B5,$23,$C4,$E3,$A0,$E2,$00,$20,$40,$D6,$B6,$32,$53,$D6,$B5
		.BYTE $23,$52,$90,$E1,$00,$E2,$90,$E1,$03,$51,$D6,$B6,$33,$05,$D6,$B5
		.BYTE $22,$E2,$A1,$93,$72,$90,$D6,$B6,$33,$A1,$D6,$B5,$22,$51,$A1,$E1
		.BYTE $21,$03,$D2,$B6,$33,$E2,$03,$53,$93,$D6,$B6,$34,$E1,$05,$D6,$B5
		.BYTE $22,$E2,$01,$58,$FF
_apu5F:
		.BYTE $D6,$B4,$23,$C4,$E3,$70,$90,$A0,$E2,$00,$D6,$B5,$33,$03,$D6,$B4
		.BYTE $24,$02,$50,$90,$50,$93,$E1,$01,$D6,$B5,$33,$E2,$95,$D6,$B4,$22
		.BYTE $71,$53,$42,$50,$D6,$B5,$33,$51,$D6,$B4,$22,$21,$51,$A1,$93,$D2
		.BYTE $B4,$22,$E3,$93,$E2,$03,$53,$D6,$B5,$33,$95,$D6,$B4,$22,$E3,$91
		.BYTE $E2,$08,$FF
_apu60:
		.BYTE $D6,$0A,$E2,$C4,$E9,$00,$E9,$00,$E9,$00,$E9,$00,$D6,$18,$E9,$53
		.BYTE $EA,$03,$EA,$23,$EA,$43,$E2,$EA,$53,$EA,$03,$EA,$51,$01,$E3,$EA
		.BYTE $91,$E2,$E9,$00,$E9,$C0,$E3,$E9,$A3,$EA,$A3,$E2,$EA,$53,$EA,$53
		.BYTE $EA,$03,$EA,$03,$D6,$0A,$EA,$51,$E2,$E9,$00,$E9,$00,$D6,$76,$E2
		.BYTE $E9,$57,$FF
_apu04:
		.BYTE $21,$B0,$10,$88,$53,$50,$21,$30,$10,$81,$F2,$88,$72,$00,$31,$F0
		.BYTE $F8,$11,$D8,$FF
_apu08:
		.BYTE $22,$10,$30,$09,$40,$09,$50,$0A,$60,$0B,$70,$0B,$80,$0B,$90,$0B
		.BYTE $A0,$0C,$B0,$0C,$C0,$0D,$D0,$0D,$50,$0E,$30,$0E,$FF

; ==========================
; ==== STAGE 3 =============
; ==========================

_apu44:
		.BYTE $D5,$75,$98,$E3,$C1,$20,$50,$70,$90,$70,$90,$B0,$E2,$00,$E3,$B0
		.BYTE $E2,$00,$20,$30,$20,$30,$50,$70
byte_336B5:
		.BYTE $D5,$35,$98,$E1,$70,$E2,$00,$E2,$70,$E2,$00,$00,$00,$E1,$00,$E2
		.BYTE $00,$00,$00,$E1,$30,$E2,$00,$00,$00,$E1,$00,$E2,$00,$E1,$60,$E2
		.BYTE $20,$E2,$90,$20,$20,$20,$E1,$20,$E2,$20,$20,$20,$E1,$60,$E2,$20
		.BYTE $20,$20,$E1,$20,$E2,$20,$E1,$70,$E2,$30,$70,$30,$30,$30,$E1,$00
		.BYTE $E2,$30,$30,$30,$E1,$30,$E2,$30,$30,$30,$E1,$00,$E2,$30,$E1,$50
		.BYTE $E2,$50,$E2,$80,$E2,$50,$50,$50,$E1,$00,$E2,$50,$50,$50,$E1,$50
		.BYTE $E2,$50,$50,$50,$E1,$00,$E2,$50
		.WORD $02FE
		.WORD byte_336B5
		.BYTE $D5,$76,$33,$E1,$00,$C0,$00,$00,$E2,$B5,$FF
_apu45:
		.BYTE $D5,$75,$98,$E3,$C1,$70,$90,$B0,$E2,$00,$E3,$B0,$E2,$00,$20,$30
		.BYTE $20,$30,$50,$70,$50,$70,$90,$B0
byte_33744:
		.BYTE $D5,$76,$98,$E0,$00,$E3,$70,$E1,$00,$E3,$70,$70,$70,$E1,$30,$E3
		.BYTE $70,$70,$70,$E1,$70,$E3,$70,$70,$70,$E1,$30,$E3,$70,$E0,$00,$E3
		.BYTE $90,$E1,$20,$E3,$90,$90,$90,$E1,$60,$E3,$90,$90,$90,$E1,$90,$E3
		.BYTE $90,$90,$90,$E1,$60,$E3,$90,$E0,$00,$E3,$A0,$E1,$00,$E3,$A0,$A0
		.BYTE $A0,$E1,$30,$E3,$A0,$A0,$A0,$E1,$70,$E3,$A0,$A0,$A0,$E1,$30,$E3
		.BYTE $A0,$E0,$00,$E2,$00,$E1,$00,$E2,$00,$00,$00,$E1,$50,$E2,$00,$00
		.BYTE $00,$E1,$80,$E2,$00,$00,$00,$E1,$50,$E2,$00
		.WORD $02FE
		.WORD byte_33744
		.BYTE $D5,$76,$33,$E1,$70,$C0,$70,$70,$75,$FF
_apu46:
		.BYTE $D5,$0A,$E2,$C1
byte_337C1:
		.BYTE $EA,$70,$EA,$70,$EA,$70,$EA,$70,$E9,$70,$EA,$70,$EA,$70,$EA,$70
		.WORD $02FE
		.WORD byte_337C1
		.BYTE $FD
		.WORD byte_337E7
		.BYTE $FD
		.WORD byte_337E7
		.BYTE $E9,$70,$C0,$E9,$70,$E9,$70,$D5,$90,$E9,$75,$FF
byte_337E7:
		.BYTE $D5,$0A,$E2
byte_337EA:
		.BYTE $EA,$00,$EA,$00,$EA,$00,$EA,$00,$E9,$00,$EA,$00,$EA,$00,$EA,$00
		.WORD $02FE
		.WORD byte_337EA
byte_337FE:
		.BYTE $EA,$20,$EA,$20,$EA,$20,$EA,$20,$E9,$20,$EA,$20,$EA,$20,$EA,$20
		.WORD $02FE
		.WORD byte_337FE
byte_33812:
		.BYTE $EA,$30,$EA,$30,$EA,$30,$EA,$30,$E9,$30,$EA,$30,$EA,$30,$EA,$30
		.WORD $02FE
		.WORD byte_33812
byte_33826:
		.BYTE $EA,$50,$EA,$50,$EA,$50,$EA,$50,$E9,$50,$EA,$50,$EA,$50,$EA,$50
		.WORD $02FE
		.WORD byte_33826
		.BYTE $FF
_apu41:
		.BYTE $D3,$B3,$00,$E2,$C3,$00,$30,$50,$70,$D6,$76,$44,$E2,$80,$50,$00
		.BYTE $50,$00,$50,$A0,$50,$00,$50,$E1,$00,$E2,$50,$00,$50,$00,$50,$A0
		.BYTE $50,$00,$50,$00,$50,$80,$E2,$50,$00,$50,$70,$50,$80,$50,$00,$50
		.BYTE $E2,$80,$30,$00,$30,$00,$30,$A0,$30,$00,$30,$E1,$00,$E2,$30,$00
		.BYTE $30,$00,$30,$A0,$30,$00,$30,$00,$30,$80,$E2,$30,$00,$30,$70,$30
		.BYTE $80,$30,$00,$30,$E2,$A0,$E2,$50,$20,$50,$20,$50,$E1,$00,$E2,$50
		.BYTE $20,$50,$E1,$20,$E2,$50,$20,$50,$20,$50,$E1,$00,$E2,$70,$00,$70
		.BYTE $00,$70,$E2,$A0,$70,$00,$70,$70,$E2,$70,$E1,$00,$E2,$70,$00,$70
		.BYTE $E1,$10,$E2,$50,$10,$50,$10,$50,$E1,$30,$E2,$50,$10,$50,$E1,$50
		.BYTE $E2,$50,$10,$50,$10,$50,$E1,$30,$E2,$30,$E3,$A0,$E2,$30,$E3,$A0
		.BYTE $E2,$30,$E1,$10,$E2,$30,$E3,$A0,$E2,$30,$E2,$A0,$E2,$30,$E1,$30
		.BYTE $E2,$30,$E3,$A0,$E2,$30,$E1,$50,$50,$50,$E2,$50,$00,$50,$50,$90
		.BYTE $50,$90,$E2,$90,$E1,$02,$FF
_apu42:
		.BYTE $D3,$B3,$00,$E2,$C3,$50,$70,$80,$A0,$D6,$76,$44,$E1,$00,$D6,$B6
		.BYTE $33,$E2,$00,$50,$00,$50,$00,$D6,$76,$44,$E1,$20,$D6,$B6,$33,$E2
		.BYTE $00,$50,$00,$D6,$76,$44,$E1,$30,$D6,$B6,$33,$E2,$00,$50,$00,$50
		.BYTE $00,$D6,$76,$44,$E1,$20,$D6,$B6,$33,$E2,$00,$50,$00,$50,$00,$D6
		.BYTE $76,$44,$E1,$00,$D6,$B6,$33,$E2,$00,$50,$00,$D6,$76,$44,$E2,$A0
		.BYTE $D6,$B6,$33,$E2,$00,$D6,$76,$44,$E1,$00,$D6,$B6,$33,$E2,$00,$50
		.BYTE $00,$D6,$76,$44,$E1,$00
		.BYTE $FD
		.WORD byte_33B61
		.BYTE $20
		.BYTE $FD
		.WORD byte_33B6F
		.BYTE $E1,$30
		.BYTE $FD
		.WORD byte_33B61
		.BYTE $20
		.BYTE $FD
		.WORD byte_33B61
		.BYTE $00,$FD
		.WORD byte_33B6F
		.BYTE $E2,$A0,$D6,$B6,$33,$E2,$00,$D6,$76,$44,$E1,$00,$D6,$B6,$33,$E2
		.BYTE $00,$30,$00,$D6,$76,$44,$E1,$20,$D6,$B6,$33,$E2,$20,$50,$20,$50
		.BYTE $20,$D6,$76,$44,$E1,$30,$D6,$B6,$33,$E2,$20,$50,$20,$D6,$76,$44
		.BYTE $E1,$50,$D6,$B6,$33,$E2,$20,$50,$20,$50,$20,$D6,$76,$44,$E1,$40
		.BYTE $D6,$B6,$33,$E2,$00,$70,$00,$70,$00,$D6,$76,$44,$E1,$20,$D6,$B6
		.BYTE $33,$E2,$00,$70,$00,$D6,$76,$44,$E1,$00,$D6,$B6,$33,$E2,$00,$D6
		.BYTE $76,$44,$E1,$40,$D6,$B6,$33,$E2,$00,$70,$00,$D6,$76,$44,$E1,$50
		.BYTE $D6,$B6,$33,$E2,$10,$50,$10,$50,$10,$D6,$76,$44,$E1,$70,$D6,$B6
		.BYTE $33,$E2,$10,$50,$10,$D6,$76,$44,$E1,$80,$D6,$B6,$33,$E2,$10,$50
		.BYTE $10,$50,$10,$D6,$76,$44,$E1,$70,$D6,$B6,$33,$E3,$A0,$E2,$30,$E3
		.BYTE $A0,$E2,$30,$E3,$A0,$D6,$76,$44,$E1,$50,$D6,$B6,$33,$E3,$A0,$E2
		.BYTE $30,$E3,$A0,$D6,$76,$44,$E1,$30,$D6,$B6,$33,$E3,$A0,$D6,$76,$44
		.BYTE $E1,$70,$D6,$B6,$33,$E3,$A0,$E2,$30,$E3,$A0,$D6,$76,$44,$E1,$90
		.BYTE $90,$90,$D6,$B6,$23,$E2,$00,$50,$00,$90,$50,$90,$50,$E1,$00,$E2
		.BYTE $92,$FF
_apu43:
		.BYTE $D3,$08,$C3,$E2,$00,$00,$00,$00,$D6,$10,$EA,$51,$EA,$C0,$EA,$50
		.BYTE $E9,$01,$EA,$50,$EA,$C0,$EA,$C0,$50,$EA,$30,$EA,$C0,$E9,$00,$00
		.BYTE $E2,$EA,$30,$EA,$00,$EA,$51,$EA,$C0,$EA,$50,$E9,$01,$EA,$50,$EA
		.BYTE $C0,$EA,$C0,$50,$EA,$30,$EA,$C0,$E9,$00,$30,$EA,$50,$EA,$70,$E2
		.BYTE $EA,$81,$EA,$C0,$EA,$80,$E9,$31,$EA,$80,$EA,$C0,$EA,$C0,$80,$EA
		.BYTE $50,$EA,$C0,$E9,$31,$EA,$50,$EA,$C0,$EA,$81,$EA,$C0,$EA,$80,$E9
		.BYTE $31,$EA,$80,$EA,$C0,$EA,$C0,$80,$EA,$50,$EA,$C0,$E9,$30,$E9,$C0
		.BYTE $E9,$50,$E9,$C0,$D6,$0F,$E2,$EA,$A0,$A0,$EA,$C0,$EA,$A0,$E9,$51
		.BYTE $EA,$A0,$EA,$C0,$EA,$C0,$A0,$EA,$50,$EA,$C0,$E3,$E9,$A0,$E2,$20
		.BYTE $EA,$50,$E3,$EA,$A0,$E2,$EA,$01,$EA,$C0,$EA,$00,$E9,$71,$EA,$00
		.BYTE $EA,$C0,$EA,$C0,$00,$EA,$00,$EA,$C0,$E9,$00,$E1,$00,$D6,$18,$EA
		.BYTE $00,$EA,$C0,$D6,$0D,$E2,$EA,$11,$EA,$C0,$EA,$10,$E9,$51,$EA,$80
		.BYTE $EA,$C0,$EA,$C0,$80,$EA,$80,$EA,$C0,$E9,$B1,$EA,$80,$EA,$C0,$EA
		.BYTE $31,$EA,$C0,$EA,$30,$E9,$71,$EA,$A1,$EA,$C0,$EA,$A0,$EA,$A1,$E1
		.BYTE $E9,$00,$E9,$30,$E9,$30,$E9,$C0,$D6,$0D,$E2,$EA,$51,$EA,$C0,$EA
		.BYTE $50,$E9,$01,$EA,$50,$EA,$C0,$E9,$50,$E9,$50,$E9,$50,$D6,$30,$E9
		.BYTE $51,$C3,$FF
byte_33B61:
		.BYTE $D6,$B6,$33,$E2,$00,$30,$00,$30,$00,$D6,$76,$44,$E1,$FF
byte_33B6F:
		.BYTE $D6,$B6,$33,$E2,$00,$30,$00,$D6,$76,$44,$FF

; ==========================
; ==== STAGE 6 =============
; ==========================

byte_4B000:
		.BYTE $D6,$75,$24,$E2,$00,$00,$E3,$90,$90,$E2,$40,$40,$E3,$90,$90
		.WORD $02FE
		.WORD byte_4B000
byte_4B013:
		.BYTE $E2,$00,$00,$E3,$90,$90,$E2,$50,$50,$E3,$90,$90
		.WORD $02FE
		.WORD byte_4B013
byte_4B023:
		.BYTE $B0,$B0,$70,$70,$E2,$20,$20,$E3,$70,$70
		.WORD $02FE
		.WORD byte_4B023
		.BYTE $FF
byte_4B032:
		.BYTE $E3,$B0,$E2,$00,$E3,$B0,$E2,$20,$E3,$B0,$E2,$40,$E3,$B0,$E2,$00
		.BYTE $E3,$B0,$E2,$00,$E3,$B0,$E2,$20,$E3,$B0,$E2,$40,$E3,$B0,$E2,$00
		.BYTE $E3,$B0,$E2,$00,$E3,$B0,$E2,$20,$E3,$B0,$E2,$40,$E3,$B0,$E2,$00
		.BYTE $FF
byte_4B063:
		.BYTE $E3,$B0,$B0,$E2,$40,$40,$B0,$B0,$40,$40,$E3,$B0,$B0,$E2,$01,$C0
		.BYTE $01,$C0,$E3,$B0,$B0,$E2,$40,$40,$B0,$B0,$40,$40,$FF
byte_4B080:
		.BYTE $E2,$90,$90,$E1,$40,$40,$90,$90,$40,$40
		.WORD $02FE
		.WORD byte_4B080
byte_4B08E:
		.BYTE $E2,$90,$90,$E1,$50,$50,$90,$90,$50,$50
		.WORD $02FE
		.WORD byte_4B08E
byte_4B09C:
		.BYTE $E2,$70,$70,$E1,$20,$20,$70,$70,$20,$20
		.WORD $02FE
		.WORD byte_4B09C
		.BYTE $FF
byte_4B0AB:
		.BYTE $E2,$40,$40,$B0,$B0,$E1,$40,$40,$E2,$B0,$B0,$40,$40,$51,$C0,$51
		.BYTE $C0,$40,$40,$B0,$B0,$E1,$40,$40,$E2,$B0,$B0,$E1,$FF
byte_4B0C8:
		.BYTE $EA,$91,$EA,$90,$EA,$90,$E9,$91,$EA,$90,$EA,$90
		.WORD $04FE
		.WORD byte_4B0C8
byte_4B0D8:
		.BYTE $EA,$B1,$EA,$B0,$EA,$B0,$E9,$B1,$EA,$B0,$EA,$B0
		.WORD $02FE
		.WORD byte_4B0D8
		.BYTE $E2,$EA,$41,$EA,$40,$EA,$40,$E9,$41,$EA,$40,$EA,$40,$FF
_apu38:
		.BYTE $FD
		.WORD byte_4B000
byte_4B0F9:
		.BYTE $B0,$B0,$80,$80,$E2,$40,$40,$E3,$80,$80
		.WORD $02FE
		.WORD byte_4B0F9
		.BYTE $FD
		.WORD byte_4B000
		.BYTE $D6,$75,$24,$E3,$B0,$B0,$80,$80,$E2,$40,$40,$E3,$80,$80,$E2,$40
		.BYTE $50,$70,$50,$40,$20,$00,$E3,$B0
_apu3B:
		.BYTE $D6,$75,$24,$E2,$40,$40,$D6,$72,$12,$40,$40,$D6,$75,$24,$40,$40
		.BYTE $D6,$72,$12,$40,$40,$D6,$75,$24,$C1,$50,$50,$C0,$52,$40,$40,$D6
		.BYTE $72,$12,$40,$40,$D6,$75,$24,$40,$40,$D6,$72,$12,$40,$40,$D6,$75
		.BYTE $24,$B0,$B0,$B1,$B0,$E1,$01,$00,$E2,$40,$40,$D6,$72,$12,$40,$40
		.BYTE $D6,$75,$24,$40,$40,$D6,$72,$12,$40,$40,$D6,$75,$24,$C1,$50,$50
		.BYTE $C0,$52,$40,$40,$D6,$72,$12,$40,$40,$D6,$75,$24,$40,$40,$D6,$72
		.BYTE $12,$40,$40,$D6,$75,$24,$40,$50,$C0,$50,$C0,$52
		.WORD $02FE
		.WORD _apu3B
byte_4B192:
		.BYTE $D6,$74,$03,$E3,$90,$B0,$90,$E2,$00,$E3,$90,$E2,$20,$E3,$90,$B0
		.WORD $04FE
		.WORD byte_4B192
		.BYTE $E3,$B0,$E2,$00,$E3,$B0,$E2,$20,$E3,$B0,$E2,$40,$E3,$B0,$E2,$00
		.BYTE $FD
		.WORD byte_4B032
byte_4B1B9:
		.BYTE $E3,$90,$B0,$90,$E2,$00,$E3,$90,$E2,$20,$E3,$90,$B0
		.WORD $04FE
		.WORD byte_4B1B9
		.BYTE $D6,$74,$03
		.BYTE $FD
		.WORD byte_4B032
		.BYTE $E3,$50,$50,$90,$E2,$00,$E3,$70,$70,$B0,$E2,$20,$D6,$34,$23
		.BYTE $FD
		.WORD byte_4B063
		.BYTE $B0,$B1,$C0,$E1,$00,$01,$C0
		.BYTE $FD
		.WORD byte_4B063
		.BYTE $90,$90,$91,$B0,$B0,$B1
		.WORD $FFFE
		.WORD _apu3B
_apu39:
		.BYTE $D6,$B5,$24
		.BYTE $FD
		.WORD byte_4B080
byte_4B1FC:
		.BYTE $E2,$B0,$B0,$E1,$40,$40,$80,$80,$40,$40
		.WORD $02FE
		.WORD byte_4B1FC
		.BYTE $FD
		.WORD byte_4B080
		.BYTE $E2,$B0,$B0,$E1,$40,$40,$80,$80,$40,$40,$40,$50,$70,$50,$40,$20
		.BYTE $00,$E2,$B0
_apu3C:
		.BYTE $D6,$75,$24,$E2,$90,$90,$D6,$72,$12,$90,$90,$D6,$75,$24,$90,$90
		.BYTE $D6,$72,$12,$90,$90,$D6,$75,$24,$C1,$A0,$A0,$C0,$A2,$90,$90,$D6
		.BYTE $72,$12,$90,$90,$D6,$75,$24,$90,$90,$D6,$72,$12,$90,$90,$D6,$75
		.BYTE $24,$E1,$40,$40,$41,$40,$51,$50,$E2,$90,$90,$D6,$72,$12,$90,$90
		.BYTE $D6,$75,$24,$90,$90,$D6,$72,$12,$90,$90,$D6,$75,$24,$C1,$A0,$A0
		.BYTE $C0,$A2,$90,$90,$D6,$72,$12,$90,$90,$D6,$75,$24,$90,$90,$D6,$72
		.BYTE $12,$90,$90,$D6,$75,$24,$90,$A0,$C0,$A0,$C0,$A2
		.WORD $02FE
		.WORD _apu3C
byte_4B290:
		.BYTE $D6,$72,$00,$E2,$90,$D6,$73,$00,$90,$D6,$74,$00,$90,$D6,$75,$00
		.BYTE $90,$93,$D6,$73,$00,$90,$D6,$74,$00,$90,$D6,$75,$00,$90,$D6,$73
		.BYTE $00,$E1,$00,$D6,$74,$00,$00,$D6,$75,$00,$00,$71,$D6,$72,$00,$50
		.BYTE $D6,$73,$00,$50,$D6,$74,$00,$50,$D6,$75,$00,$50,$53,$D6,$72,$00
		.BYTE $20,$D6,$73,$00,$20,$D6,$74,$00,$20,$D6,$75,$00,$20,$23,$D6,$72
		.BYTE $00,$E2,$B0,$D6,$73,$00,$B0,$D6,$74,$00,$B0,$D6,$75,$00,$B0,$B3
		.BYTE $D6,$73,$00,$B0,$D6,$74,$00,$B0,$D6,$75,$00,$B0,$D6,$73,$00,$E1
		.BYTE $20,$D6,$74,$00,$20,$D6,$75,$00,$20,$71,$D6,$72,$00,$50,$D6,$73
		.BYTE $00,$50,$D6,$74,$00,$50,$D6,$75,$00,$50,$53,$D6,$72,$00,$40,$D6
		.BYTE $73,$00,$40,$D6,$74,$00,$40,$D6,$75,$00,$44
		.WORD $02FE
		.WORD byte_4B290
		.BYTE $D6,$B5,$24
		.BYTE $FD
		.WORD byte_4B0AB
		.BYTE $40,$41,$C0,$50,$51,$C0
		.BYTE $FD
		.WORD byte_4B0AB
		.BYTE $50,$50,$51,$70,$70,$71
		.WORD $FFFE
		.WORD _apu3C
_apu3A:
		.BYTE $D6,$90,$E3,$EA,$90,$EA,$90,$EA,$90,$EA,$C0
		.WORD $18FE
		.WORD _apu3A
byte_4B357:
		.BYTE $EA,$70,$EA,$C0
		.WORD $08FE
		.WORD byte_4B357
byte_4B35F:
		.BYTE $EA,$40,$EA,$C0
		.WORD $04FE
		.WORD byte_4B35F
		.BYTE $E2,$EA,$40,$EA,$50,$EA,$70,$EA,$50,$E9,$40,$E9,$20,$E9,$00,$E3
		.BYTE $E9,$B0
_apu3D:
		.BYTE $D6,$0F,$E3,$EA,$91,$EA,$90,$EA,$90,$E9,$91,$EA,$90,$EA,$90,$EA
		.BYTE $91,$EA,$90,$EA,$90,$EA,$91,$EA,$90,$EA,$90,$EA,$91,$EA,$90,$EA
		.BYTE $90,$E9,$91,$EA,$90,$EA,$90,$EA,$40,$EA,$40,$EA,$41,$E9,$40,$EA
		.BYTE $51,$EA,$50,$EA,$91,$EA,$90,$EA,$90,$E9,$91,$EA,$90,$EA,$90,$EA
		.BYTE $91,$EA,$90,$EA,$90,$E9,$91,$EA,$90,$EA,$90,$EA,$91,$EA,$90,$EA
		.BYTE $90,$E9,$91,$EA,$90,$EA,$90,$EA,$90,$E9,$A0,$EA,$C0,$E9,$A0,$EA
		.BYTE $C0,$E9,$A0,$E9,$A0,$E9,$A0
		.WORD $02FE
		.WORD _apu3D
		.BYTE $D6,$0F,$E3
		.BYTE $FD
		.WORD byte_4B0C8
		.BYTE $EA,$41,$EA,$40,$EA,$40,$E9,$20,$E9,$20,$E9,$20,$E9,$20,$E3
		.BYTE $FD
		.WORD byte_4B0C8
		.BYTE $E3,$EA,$50,$EA,$50,$E9,$50,$EA,$50,$EA,$70,$EA,$70,$E9,$70,$EA
		.BYTE $70,$D6,$90,$E3,$EA,$41,$EA,$C0,$EA,$B1,$EA,$C0,$E2,$EA,$40,$EA
		.BYTE $C0,$E3,$E9,$40,$E9,$C0,$EA,$51,$EA,$C0,$EA,$51,$EA,$C0
byte_4B42A:
		.BYTE $D6,$90,$E3,$EA,$41,$EA,$C0,$EA,$B1,$EA,$C0,$E2,$EA,$40,$EA,$C0
		.BYTE $E3,$E9,$40,$E9,$C0,$EA,$50,$EA,$C1,$EA,$51,$EA,$C0
		.WORD $02FE
		.WORD byte_4B42A
		.BYTE $E3,$EA,$41,$E9,$C0,$EA,$B1,$EA,$C0,$E2,$EA,$40,$EA,$C0,$D6,$0E
		.BYTE $E9,$50,$E9,$50,$E9,$50,$EA,$C0,$E9,$70,$E9,$70,$E9,$70,$EA,$C0
		.WORD $FFFE
		.WORD _apu3D
_apu0A:
		.BYTE $23,$30,$10,$82,$A0,$31,$A0,$31,$90,$31,$A0,$31,$A0,$31,$90,$31
		.BYTE $A0,$31,$90,$31,$80,$31,$90,$31,$80,$31,$FF
_apu50:
		.BYTE $D7,$F5,$30,$E1,$20,$E2,$20,$E1,$20,$E2,$20,$90,$20,$E1,$20,$E2
		.BYTE $20,$E1,$20,$E2,$20,$90,$20,$E1,$20,$E2,$90,$E1,$20,$E2,$90,$E1
		.BYTE $20,$E2,$90,$E1,$40,$E2,$90,$E1,$40,$40,$20,$10
		.WORD $02FE
		.WORD _apu50
_apu4D:
		.BYTE $D7,$F5,$30,$E2,$90,$50,$90,$E1,$20,$E2,$90,$E1,$20,$E2,$90,$50
		.BYTE $90,$E1,$10,$E2,$90,$E1,$10,$E2,$90,$50,$90,$72,$52,$22,$E2,$90
		.BYTE $50,$90,$E1,$20,$E2,$90,$E1,$20,$E2,$90,$50,$90,$E1,$10,$E2,$90
		.BYTE $E1,$10,$E2,$90,$50,$90,$E1,$A2,$90,$40,$20,$10,$E2,$90,$40
		.WORD $02FE
		.WORD _apu4D
byte_4B4FD:
		.BYTE $E8,$D7,$F5,$30,$E2,$A0,$A0,$A0,$A0,$A0,$A0,$E1,$70,$40,$10,$E2
		.BYTE $A0,$70,$40,$E1,$70,$70,$70,$70,$70,$70,$40,$10,$E2,$90,$40,$10
		.BYTE $E3,$90
		.WORD $02FE
		.WORD byte_4B4FD
		.WORD $FFFE
		.WORD _apu50
_apu51:
		.BYTE $D7,$F5,$30,$E1,$90,$E2,$90,$E1,$90,$E2,$90,$E1,$20,$E2,$90,$E1
		.BYTE $90,$E2,$90,$E1,$90,$E2,$90,$E1,$20,$E2,$90,$E1,$80,$20,$80,$20
		.BYTE $80,$20,$70,$20,$70,$70,$50,$40
		.WORD $02FE
		.WORD _apu51
_apu4E:
		.BYTE $D7,$F5,$30,$E1,$20,$C0,$20,$50,$20,$50,$20,$C0,$20,$70,$20,$70
		.BYTE $20,$C0,$20,$A0,$20,$A0,$90,$20,$90,$50,$20,$50,$E1,$20,$C0,$20
		.BYTE $50,$20,$50,$20,$C0,$20,$70,$20,$70,$20,$C0,$20,$E0,$22,$10,$E1
		.BYTE $90,$70,$40,$10,$E2,$90
		.WORD $02FE
		.WORD _apu4E
byte_4B58D:
		.BYTE $D7,$F5,$30,$E1,$A0,$A0,$A0,$A0,$A0,$A0,$A0,$70,$40,$10,$E2,$A0
		.BYTE $70,$E1,$A0,$A0,$A0,$A0,$A0,$A0,$90,$40,$10,$E2,$90,$40,$10
		.WORD $02FE
		.WORD byte_4B58D
		.WORD $FFFE
		.WORD _apu51
_apu52:
		.BYTE $D7,$10,$E2,$E9,$20,$EA,$20,$E9,$20,$EA,$C0,$EA,$C0,$EA,$C0,$E9
		.BYTE $20,$EA,$20,$E9,$20,$EA,$C0,$EA,$C0,$EA,$C0,$E9,$A0,$EA,$C0,$E9
		.BYTE $A0,$EA,$A0,$EA,$A0,$EA,$A0,$E9,$90,$EA,$90,$E9,$90,$E3,$E9,$90
		.BYTE $E9,$90,$E9,$90
		.WORD $02FE
		.WORD _apu52
_apu4F:
		.BYTE $FD
		.WORD byte_4B636
		.BYTE $FD
		.WORD byte_4B636
byte_4B5F2:
		.BYTE $D7,$10,$E2,$E9,$70,$EA,$70,$E9,$70,$E9,$70,$E9,$70,$E9,$70,$E9
		.BYTE $90,$E3,$EA,$90,$EA,$90,$EA,$90,$EA,$90,$EA,$90
		.WORD $02FE
		.WORD byte_4B5F2
		.BYTE $E2
		.BYTE $FD
		.WORD byte_4B676
		.BYTE $E9,$A0,$EA,$40,$E9,$A0,$E9,$40,$EA,$A0,$E9,$40
		.BYTE $FD
		.WORD byte_4B676
		.BYTE $E9,$90,$EA,$90,$E9,$90,$E3,$E9,$90,$EA,$90,$E9,$90
		.WORD $FFFE
		.WORD _apu52
byte_4B636:
		.BYTE $D7,$10,$E2,$E9,$20,$EA,$20,$E9,$20,$E3,$EA,$90,$E2,$EA,$20,$E3
		.BYTE $EA,$90
		.WORD $04FE
		.WORD byte_4B636
byte_4B64C:
		.BYTE $E2,$E9,$A0,$EA,$A0,$E9,$A0,$EA,$50,$EA,$A0,$EA,$50
		.WORD $02FE
		.WORD byte_4B64C
		.BYTE $E9,$70,$EA,$70,$E9,$70,$EA,$20,$EA,$70,$EA,$20,$E9,$90,$EA,$90
		.BYTE $E9,$90,$EA,$40,$EA,$90,$EA,$40,$FF
byte_4B676:
		.BYTE $E9,$70,$EA,$40,$E9,$70,$E9,$40,$EA,$70,$E9,$40,$FF

; ==========================
; ==== ENDING ==============
; ==========================

_apu72:
		.BYTE $22,$70,$36,$FD,$46,$20,$45,$F9,$56,$50,$66,$90
_apu73:
		.BYTE $23,$70,$56,$FD,$67,$20,$47,$7C,$56,$50,$67,$90,$67,$37,$67,$C4
		.BYTE $57,$40,$57,$22,$87,$F0,$57,$45,$67,$36,$56,$DD,$57,$E4,$67,$88
		.BYTE $56,$22,$77,$FD,$87,$89,$67,$3A,$57,$DD,$67,$65,$67,$99,$57,$A8
		.BYTE $77,$40,$57,$77
		.WORD $06FE
		.WORD _apu73
		.BYTE $FF
_apu74:
		.BYTE $D8,$10,$EC,$C6,$EE,$C5,$EE,$C2,$EE,$C4,$EE,$C3,$EF,$C6,$ED,$C9
		.BYTE $ED,$C0,$FF
_apu25:
		.BYTE $21,$30,$F0,$0D,$F0,$0D,$A0,$0E,$60,$0D,$40,$0F,$60,$0E,$80,$0F
		.BYTE $B0,$0E,$40,$0F,$60,$0E,$B0,$0D,$A0,$0E,$50,$0F,$40,$0F,$40,$0E
		.BYTE $50,$0F,$D0,$0E,$70,$0F,$40,$0D,$30,$F0,$F0,$0E,$70,$0D,$40,$0F
		.BYTE $F0,$0F
		.WORD $03FE
		.WORD _apu25
		.BYTE $23,$10,$D0,$0D,$50,$0E,$B0,$0F,$50,$0E,$90,$0E,$40,$0D,$70,$0F
		.BYTE $30,$0E,$60,$0F,$30,$0F,$50,$0E,$F8,$20,$0E,$40,$0F,$F8,$10,$0E
		.BYTE $30,$0E,$F8,$20,$0F,$F8,$10,$0E,$F8,$20,$0E,$F8,$10,$0E,$F8,$10
		.BYTE $0F,$F8,$10,$0F,$FF
_apu1F:
		.BYTE $29,$B0,$10,$83,$F2,$20,$F2,$20,$29,$B0,$D1,$38,$A1,$30,$71,$28
		.BYTE $41,$20,$31,$10,$F8,$21,$00,$FF
_apu20:
		.BYTE $2A,$10,$F0,$0E,$F0,$0F,$2A,$B0,$C0,$0C,$90,$0D,$60,$0D,$40,$0D
		.BYTE $30,$0D,$F8,$20,$0D,$F8,$10,$0D,$FF
_apu21:
		.BYTE $29,$B0,$10,$83,$D2,$20,$A1,$5D,$81,$58,$51,$4D,$31,$48,$F8,$21
		.BYTE $40,$FF
_apu22:
		.BYTE $2A,$10,$E0,$0F,$A0,$0F,$80,$0E,$50,$0E,$30,$0D,$F8,$20,$0D,$F8
		.BYTE $10,$0D,$FF
_apu75:
		.BYTE $D7,$B0,$33,$CF
		.WORD $04FE
		.WORD _apu75
byte_53373:
		.BYTE $E8,$D7,$B5,$22,$E2,$53,$A2,$90,$53,$22,$30,$5B,$22,$30,$53,$72
		.BYTE $90,$A3,$E1,$02,$20,$03,$E2,$93,$53,$72,$90
		.BYTE $FD
		.WORD byte_5347E
		.BYTE $A2,$E1,$00,$D7,$B5,$36,$E1,$23,$52,$50,$23,$E2,$A2,$E1,$00,$2B
		.BYTE $E2,$A2,$E1,$00,$23,$32,$50,$73,$92,$A0,$93,$53,$23,$32,$50,$E1
		.BYTE $73,$93,$53,$33,$23,$E2,$A3,$53,$92,$A0,$E1,$03,$E2,$03,$E1,$03
		.BYTE $E2,$A2,$E1,$00,$E2,$37,$23,$C3
		.BYTE $FD
		.WORD byte_53493
		.BYTE $C7,$D7,$75,$21,$E3,$33,$32,$50,$73,$A3,$E2,$07,$E3,$73,$E2,$03
		.BYTE $E3,$93,$A3,$E2,$03,$53,$2B,$C3
		.BYTE $FD
		.WORD byte_53493
		.BYTE $C3,$D7,$B5,$21,$02,$20,$E2,$33,$23,$03,$E3,$A3,$93,$73,$53,$33
		.BYTE $23,$23,$53,$73,$93,$A3,$E2,$03,$03,$D7,$B5,$36,$E2,$23,$52,$50
		.BYTE $23,$E3,$A2,$E2,$00,$2B,$E3,$A2,$E2,$00,$23,$32,$50,$73,$92,$A0
		.BYTE $93,$53,$23,$32,$50,$73,$93,$53,$33,$23,$E3,$A3,$73,$92,$A0,$E2
		.BYTE $03,$23,$33,$73,$53,$33,$23,$A2,$E1,$00,$23,$52,$50,$23,$E2,$A2
		.BYTE $E1,$00,$2B,$E2,$A2,$E1,$00,$23,$32,$50,$73,$92,$A0,$93,$53,$23
		.BYTE $32,$50,$73,$93,$53,$33,$23,$E2,$A3,$53,$92,$A0,$E1,$03,$E2,$03
		.BYTE $E1,$03,$D1,$B6,$26,$E2,$A9,$A9,$E1,$09,$DE,$B7,$36,$E2,$33,$21
		.BYTE $C1
byte_53468:
		.BYTE $D7,$B0,$33,$CF
		.WORD $07FE
		.WORD byte_53468
		.BYTE $CB,$D7,$B4,$11,$E3,$90,$A0,$B0,$E2,$00
		.WORD $FFFE
		.WORD byte_53373
byte_5347E:
		.BYTE $A3,$E1,$03,$E2,$93,$73,$53,$23,$E3,$A3,$E2,$02,$20,$33,$53,$73
		.BYTE $A3,$93,$73,$53,$FF
byte_53493:
		.BYTE $D7,$75,$21,$E3,$73,$72,$90,$A3,$E2,$23,$D1,$B4,$43,$78,$78,$79
		.BYTE $D7,$B5,$21,$73,$C7,$E3,$53,$52,$70,$93,$E2,$03,$D1,$B4,$43,$58
		.BYTE $58,$59,$D7,$B5,$21,$53,$FF
		.WORD _apu75
_apu76:
		.BYTE $D7,$B0,$33,$CF
		.WORD $04FE
		.WORD _apu76
byte_534C4:
		.BYTE $D7,$B5,$22,$E2,$53,$A2,$90,$53,$22,$30,$5B,$22,$30,$53,$72,$90
		.BYTE $A3,$E1,$02,$20,$03,$E2,$93,$53,$72,$90,$A3,$E1,$03,$E2,$93,$73
		.BYTE $53,$23,$E3,$A3,$E2,$02,$20,$33,$53,$73,$A3,$93,$73,$53,$E1,$22
		.BYTE $30,$D7,$B6,$24,$E1,$53,$A2,$90,$53,$22,$30,$5B,$22,$30,$53,$72
		.BYTE $90,$A3,$E0,$02,$20,$03,$E1,$93,$53,$72,$90,$A3,$E0,$03,$E1,$93
		.BYTE $73,$53,$23,$E2,$A3,$E1,$02,$20,$33,$E2,$53,$E1,$33,$22,$30,$07
		.BYTE $E2,$A3,$C3,$D7,$76,$22,$E3,$73,$72,$90,$A3,$E2,$23,$17,$C7,$E3
		.BYTE $53,$52,$70,$93,$E2,$03,$27,$C7,$E3,$33,$32,$50,$73,$A3,$E2,$07
		.BYTE $E3,$73,$E2,$03,$E3,$93,$A3,$E2,$03,$53,$2B,$C3,$E3,$73,$72,$90
		.BYTE $A3,$E2,$23,$17,$C7,$E3,$53,$52,$70,$93,$E2,$03,$27,$C3,$32,$50
		.BYTE $E2,$73,$53,$33,$23,$03,$E3,$A3,$93,$73,$63,$63,$93,$A3,$E2,$03
		.BYTE $23,$33,$43,$D7,$B6,$22,$E2,$53,$A2,$90,$53,$22,$30,$5B,$22,$30
		.BYTE $53,$72,$90,$A3,$E1,$02,$20,$03,$E2,$93,$53,$72,$90
		.BYTE $FD
		.WORD byte_5347E
		.BYTE $E1,$22,$30,$D7,$B6,$36,$E1,$53,$A2,$90,$53,$22,$30,$5B,$22,$30
		.BYTE $53,$72,$90,$A3,$E0,$02,$20,$03,$E1,$93,$53,$72,$90,$A3,$E0,$03
		.BYTE $E1,$93,$73,$53,$23,$E2,$A3,$E1,$02,$20,$33,$E2,$53,$E1,$33,$D1
		.BYTE $B7,$25,$29,$29,$39,$DE,$B8,$36,$03,$E2,$A1,$C1
byte_535D0:
		.BYTE $D7,$B0,$33,$CF
		.WORD $07FE
		.WORD byte_535D0
		.BYTE $CB,$D7,$B4,$11,$10,$20,$30,$40
		.WORD $FFFE
		.WORD byte_534C4
_apu77:
		.BYTE $FD
		.WORD byte_53883
		.BYTE $FD
		.WORD byte_5389B
		.BYTE $FD
		.WORD byte_53883
		.BYTE $FD
		.WORD byte_5389B
byte_535F0:
		.BYTE $FD
		.WORD byte_538BE
		.BYTE $FD
		.WORD byte_5395E
		.BYTE $D7,$3D,$E2,$EA,$21,$D7,$0C,$E1,$E9,$21
		.BYTE $FD
		.WORD byte_53A39
		.BYTE $D7,$3D,$E2,$EA,$21,$D7,$0C,$E1,$E9,$71,$D7,$3D,$E2,$EA,$01,$D7
		.BYTE $0C,$E1,$E9,$A1,$D7,$3D,$E3,$EA,$A1,$D7,$0C,$E1,$E9,$31,$D7,$3D
		.BYTE $E2,$EA,$51,$D7,$0C,$E1,$E9,$01,$D7,$3D,$E2,$EA,$01,$D7,$0C,$E1
		.BYTE $E9,$51,$D7,$3D,$E3,$EA,$51,$D7,$0C,$E1,$E9,$C0,$E9,$C0,$D7,$3D
		.BYTE $E2,$E9,$91,$D7,$0C,$E1,$E9,$C1
		.BYTE $FD
		.WORD byte_538BE
		.BYTE $FD
		.WORD byte_5395E
		.BYTE $D7,$3D,$E2,$EA,$21,$D7,$13,$E1,$E9,$51,$D7,$3D,$E2,$EA,$C3,$53
		.BYTE $EA,$C3,$52,$E2,$50,$D1,$22
byte_53668:
		.BYTE $E9,$03
		.WORD $05FE
		.WORD byte_53668
byte_5366E:
		.BYTE $E9,$C3
		.WORD $09FE
		.WORD byte_5366E
		.BYTE $D7,$0D,$E3,$E9,$C1,$E9,$A0,$E9,$A0,$D7,$3D,$E9,$A3
		.BYTE $FD
		.WORD byte_539A5
		.BYTE $FD
		.WORD byte_53A1B
		.BYTE $E9,$31,$E9,$31,$E9,$31,$D2,$10,$E9,$31,$E9,$31,$E9,$32,$D7,$10
		.BYTE $E9,$30,$E9,$30,$E9,$30,$E9,$30,$E9,$33,$E9,$51,$E9,$51,$E9,$51
		.BYTE $D2,$10,$E9,$51,$E9,$51,$E9,$52,$D7,$10,$E9,$50,$E9,$50,$E9,$50
		.BYTE $E9,$50,$E9,$53,$E9,$A1,$E9,$A1,$E9,$A1,$D4,$18,$E9,$A0,$E9,$A0
		.BYTE $E9,$A0,$D2,$10,$A0,$D7,$10,$E9,$90,$E9,$90,$E9,$90,$E9,$90,$E9
		.BYTE $93
		.BYTE $FD
		.WORD byte_539A5
		.BYTE $FD
		.WORD byte_53A39
		.BYTE $D7,$3D,$E3,$EA,$A1,$D7,$0C,$E1,$E9,$71,$D7,$3D,$E2,$EA,$31,$D7
		.BYTE $0C,$E1,$E9,$A1,$D7,$3D,$E2,$EA,$A1,$D7,$0C,$E1,$E9,$71,$D7,$3D
		.BYTE $E2,$EA,$01,$D7,$0C,$E1,$E9,$31,$D7,$3D,$E2,$EA,$71,$D7,$0C,$E1
		.BYTE $E9,$71,$D7,$3D,$E2,$EA,$01,$D7,$09,$E0,$E9,$01,$D7,$3D,$E2,$EA
		.BYTE $31,$D7,$0C,$E1,$E9,$70,$E9,$70,$D7,$3D,$E2,$EA,$21,$D7,$0C,$E1
		.BYTE $E9,$21,$D7,$3D,$E2,$EA,$61,$D7,$0C,$E1,$E9,$61,$D7,$3D,$E2,$EA
		.BYTE $91,$D7,$0C,$E1,$E9,$91,$D7,$3D,$E2,$EA,$71,$D7,$0C,$E1,$E9,$71
		.BYTE $D7,$3D,$E2,$EA,$51,$D7,$0C,$E1,$E9,$01,$D7,$3D,$E3,$EA,$51,$D7
		.BYTE $0C,$E1,$E9,$51,$D7,$3D,$E3,$EA,$71,$D7,$0C,$E1,$E9,$91,$D7,$3D
		.BYTE $E3,$E9,$90,$D7,$0C,$E1,$E9,$C0,$E9,$C0,$E9,$C0
		.BYTE $FD
		.WORD byte_538BE
		.BYTE $FD
		.WORD byte_5395E
		.BYTE $D7,$3D,$E2,$EA,$21,$D7,$0C,$E1,$E9,$21
		.BYTE $FD
		.WORD byte_53A39
		.BYTE $D7,$3D,$E2,$EA,$21,$D7,$0C,$E1,$E9,$71,$D7,$3D,$E2,$EA,$01,$D7
		.BYTE $0C,$E1,$E9,$A1,$D7,$3D,$E3,$EA,$A1,$D7,$0C,$E1,$E9,$31,$D7,$3D
		.BYTE $E2,$EA,$51,$D7,$0C,$E1,$E9,$01,$D7,$3D,$E2,$EA,$01,$D7,$0C,$E1
		.BYTE $E9,$51,$D7,$3D,$E3,$EA,$51,$E9,$C0,$E9,$C0,$E9,$91,$E9,$C1
		.BYTE $FD
		.WORD byte_538BE
		.BYTE $FD
		.WORD byte_5395E
		.BYTE $D7,$3D,$E2,$EA,$21,$D7,$13,$E1,$E9,$51,$D7,$3D,$E2,$EA,$C3,$53
		.BYTE $EA,$C3,$D1,$23,$E9,$59,$E9,$59,$E9,$59
byte_537EC:
		.BYTE $E9,$03
		.WORD $05FE
		.WORD byte_537EC
byte_537F2:
		.BYTE $E9,$C3
		.WORD $09FE
		.WORD byte_537F2
		.BYTE $D7,$0D,$E3,$E9,$C1,$E9,$A0,$E9,$A0,$DE,$40,$E9,$A1
		.BYTE $FD
		.WORD byte_53883
		.BYTE $FD
		.WORD byte_5389B
		.BYTE $FD
		.WORD byte_53883
		.BYTE $FD
		.WORD byte_5389B
		.BYTE $D7,$10,$E9,$C1,$D2,$10,$E9,$C1,$E9,$C1,$E9,$C2,$D7,$10,$E9,$C1
		.BYTE $E9,$C1,$E9,$C1,$E9,$C5,$E9,$C0,$E9,$C0,$E9,$C0,$E9,$C0,$E9,$C1
		.BYTE $D2,$10,$E9,$C1,$E9,$C1,$E9,$C2,$D7,$10,$E9,$C1,$E9,$C5,$D1,$10
		.BYTE $E9,$C3,$E9,$C3,$E9,$C3,$E9,$C3,$E9,$C3,$E9,$C3,$E9,$C3,$E9,$C3
		.BYTE $E9,$C3,$E9,$C3,$E9,$C3,$E9,$C3,$E9,$C3,$E9,$C3,$D7,$10,$E9,$C1
		.BYTE $E9,$C5,$E9,$C1,$D2,$10,$E9,$C1,$E9,$C1,$E9,$C2,$D7,$10,$E9,$C1
		.BYTE $E9,$C1,$E9,$C1,$E9,$C1,$E9,$C0,$E9,$C0,$E9,$C0,$E9,$C0
		.WORD $FFFE
		.WORD byte_535F0
byte_53883:
		.BYTE $D7,$10,$E9,$C1,$E9,$C1,$E9,$C1,$D4,$10,$E9,$C0,$E9,$C0,$E9,$C0
		.BYTE $D2,$10,$C0
		.WORD $02FE
		.WORD byte_53883
		.BYTE $FF
byte_5389B:
		.BYTE $D7,$10,$E9,$C1,$E9,$C1,$E9,$C0,$E9,$C0,$E9,$C0,$E9,$C0,$E9,$C1
		.BYTE $E9,$C1,$D1,$10,$E9,$C3,$E9,$C3,$E9,$C3,$E9,$C3,$E9,$C3,$E9,$C3
		.BYTE $E9,$C3,$FF
byte_538BE:
		.BYTE $D7,$3D,$E2,$EA,$A1,$D7,$0C,$E1,$E9,$21,$D7,$3D,$E2,$EA,$51,$D7
		.BYTE $0C,$E1,$E9,$51,$D7,$3D,$E2,$EA,$A1,$D7,$0B,$E1,$E9,$A1,$D7,$3D
		.BYTE $E2,$EA,$51,$D7,$0C,$E1,$E9,$51,$D7,$3D,$E2,$EA,$A1,$D7,$0C,$E1
		.BYTE $E9,$21,$D7,$3D,$E2,$EA,$51,$D7,$0C,$E1,$E9,$51,$D7,$3D,$E2,$EA
		.BYTE $71,$D7,$0B,$E1,$E9,$A1,$D7,$3D,$E2,$EA,$91,$D7,$0C,$E1,$E9,$51
		.BYTE $D7,$3D,$E2,$EA,$A1,$D7,$0C,$E1,$E9,$21,$D7,$3D,$E2,$EA,$51,$D7
		.BYTE $0C,$E1,$E9,$51,$D7,$3D,$E2,$EA,$A1,$D7,$0B,$E1,$E9,$A1,$D7,$3D
		.BYTE $E1,$EA,$21,$D7,$0C,$E1,$E9,$51,$D7,$3D,$E1,$EA,$01,$D7,$0C,$E1
		.BYTE $E9,$91,$D7,$3D,$E2,$EA,$91,$D7,$0C,$E1,$E9,$51,$D7,$3D,$E2,$EA
		.BYTE $71,$D7,$0C,$E1,$E9,$70,$E9,$70,$D7,$3D,$E2,$E9,$51,$E9,$C1,$FF
byte_5395E:
		.BYTE $D7,$3D,$E2,$EA,$31,$D7,$0C,$E1,$E9,$A1,$D7,$3D,$E3,$EA,$A1,$D7
		.BYTE $0C,$E1,$E9,$71,$D7,$3D,$E2,$EA,$31,$D7,$0C,$E1,$E9,$31,$D7,$3D
		.BYTE $E2,$EA,$71,$D7,$0C,$E1,$E9,$71,$D7,$3D,$E2,$EA,$51,$D7,$0C,$E1
		.BYTE $E9,$21,$D7,$3D,$E2,$EA,$21,$D7,$0C,$E1,$E9,$51,$D7,$3D,$E3,$EA
		.BYTE $A1,$D7,$0B,$E1,$E9,$A1,$FF
byte_539A5:
		.BYTE $D7,$10,$E2,$E9,$71,$E9,$71,$E9,$71,$D2,$10,$E9,$71,$E9,$71,$E9
		.BYTE $72,$D7,$10,$E9,$71,$E9,$71,$E9,$71,$D2,$10,$E9,$71,$E9,$71,$E9
		.BYTE $72,$D7,$10,$E9,$71,$E9,$71,$E9,$70,$E9,$70,$E9,$70,$E9,$70,$E9
		.BYTE $71,$E9,$71,$D1,$10
byte_539DA:
		.BYTE $E9,$73
		.WORD $07FE
		.WORD byte_539DA
		.BYTE $D7,$10,$E9,$51,$E9,$51,$E9,$51,$D2,$10,$E9,$51,$E9,$51,$E9,$52
		.BYTE $D7,$10,$E9,$51,$E9,$51,$E9,$51,$D2,$10,$E9,$51,$E9,$51,$E9,$52
		.BYTE $D7,$10,$E9,$51,$E9,$51,$E9,$50,$E9,$50,$E9,$50,$E9,$50,$E9,$51
		.BYTE $E9,$51,$D1,$10
byte_53A14:
		.BYTE $E9,$53
		.WORD $07FE
		.WORD byte_53A14
		.BYTE $FF
byte_53A1B:
		.BYTE $D7,$10,$E2,$E9,$31,$E9,$31,$E9,$31,$D2,$10,$E9,$31,$E9,$31,$E9
		.BYTE $32,$D7,$10,$E9,$30,$E9,$30,$E9,$30,$E9,$30,$E9,$33,$FF
byte_53A39:
		.BYTE $D7,$3D,$E2,$EA,$31,$D7,$0C,$E1,$E9,$31,$FF

; ==========================
; ==== TITLE ===============
; ==========================

_apu26:
		.BYTE $D6,$77,$32
		.BYTE $FD
		.WORD byte_6266
		.BYTE $D8,$B8,$35
		.BYTE $FD
		.WORD byte_6284
		.BYTE $A0,$C0,$A0,$A2,$90,$A0,$90
		.BYTE $FD
		.WORD byte_6284
		.BYTE $D4,$B7,$30,$A4,$D4,$B3,$00,$A2,$D4,$B2,$00,$A4,$FF
_apu27:
		.BYTE $D8,$B0,$00,$C0,$E8,$D6,$74,$10
		.BYTE $FD
		.WORD byte_6266
		.BYTE $D8,$B4,$11
		.BYTE $FD
		.WORD byte_6284
		.BYTE $A0,$C0,$A0,$A2,$90,$A0,$90
		.BYTE $FD
		.WORD byte_6284
		.BYTE $A4,$FF
_apu28:
		.BYTE $D6,$28,$E2,$E9,$C0,$E9,$C0,$E9,$C0,$E9,$01,$EA,$C0,$D6,$02,$E0
		.BYTE $EA,$30,$E9,$70,$30,$EA,$00,$E1,$EA,$70,$EA,$30,$70,$E0,$EA,$00
		.BYTE $EA,$30,$E9,$70,$30,$D6,$10,$E2,$E9,$00,$E3,$E9,$B0,$D6,$28,$E9
		.BYTE $A0,$C0,$EA,$C0,$D6,$02,$E0,$EA,$50,$E9,$A0,$50,$EA,$20,$E1,$EA
		.BYTE $A0,$EA,$50,$A0,$E0,$EA,$20,$EA,$50,$E9,$A0,$50,$D6,$10,$E3,$E9
		.BYTE $A0,$E9,$90,$D6,$28,$E9,$80,$C0,$EA,$C0,$D6,$02,$E0,$EA,$30,$E9
		.BYTE $80,$30,$EA,$00,$E1,$EA,$80,$EA,$30,$80,$E0,$EA,$00,$EA,$30,$E9
		.BYTE $80,$30,$D6,$10,$E3,$E9,$80,$E9,$80,$D6,$28,$E9,$70,$C0,$EA,$C0
		.BYTE $D6,$02,$E0,$EA,$70,$E9,$B0,$70,$EA,$20,$E1,$EA,$B0,$EA,$70,$B0
		.BYTE $E0,$EA,$20,$EA,$70,$E9,$B0,$70,$20,$70
		.BYTE $FD
		.WORD byte_6291
		.BYTE $FD
		.WORD byte_6291
		.BYTE $D8,$18,$E2,$E9,$00,$E9,$20,$E9,$30,$E9,$31,$E9,$30,$D4,$90
byte_6240:
		.BYTE $E9,$30
		.WORD $06FE
		.WORD byte_6240
		.BYTE $D8,$20,$E9,$20,$E9,$30,$E9,$20
		.BYTE $FD
		.WORD byte_6291
		.BYTE $FD
		.WORD byte_6291
		.BYTE $D8,$20,$E2,$E9,$01,$E3,$E9,$70,$D4,$90,$E2
byte_625F:
		.BYTE $E9,$00
		.WORD $0CFE
		.WORD byte_625F
		.BYTE $FF
byte_6266:
		.BYTE $C2,$E3,$74,$70,$E2,$00,$30,$74,$70,$80,$70,$53,$73,$83,$A3,$E3
		.BYTE $54,$50,$80,$E2,$00,$34,$30,$50,$30,$23,$33,$53,$63,$FF
byte_6284:
		.BYTE $E2,$70,$C0,$70,$62,$70,$C0,$70,$62,$70,$90,$A0,$FF
byte_6291:
		.BYTE $D8,$20,$E2,$E9,$01,$E9,$00,$D4,$90,$E3
byte_629B:
		.BYTE $E9,$B0
		.WORD $06FE
		.WORD byte_629B
		.BYTE $FF

		SECTION_END "APU ENGINE"

		BANK_END 0,$C000
