
		INCLUDE		"..\macroses.inc"

;--------------------R-A-M----------------------

		ORG $0000

word_0:
		.BYTE 0,0
byte_2:
		.BYTE 0
byte_3:
		.BYTE 0
word_4:
		.BYTE 0,0
byte_6:
		.BYTE 0
byte_7:
		.BYTE 0
byte_8:
		.BYTE 0
byte_9:
		.BYTE 0
byte_A:
		.BYTE 0
byte_B:
		.BYTE 0
byte_C:
		.BYTE 0
byte_D:
		.BYTE 0
byte_E:
		.BYTE 0
byte_F:
		.BYTE 0
byte_10:
		.BYTE 0
byte_11:
		.BYTE 0
byte_12:
		.BYTE 0
byte_13:
		.BYTE 0
byte_14:
		.BYTE 0
byte_15:
		.BYTE 0
byte_16:
		.BYTE 0
byte_17:
		.BYTE 0
_main_sub_idx:
		.BYTE 0
_sub_sub_idx:
		.BYTE 0
_frames_counter:
		.BYTE 0
_busy_flags:
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_20:
		.BYTE 0
byte_21:
		.BYTE 0
byte_22:
		.BYTE 0
byte_23:
		.BYTE 0
_nmi_counter:
		.BYTE 0
_ppu_queue_pos:
		.BYTE 0
_players_num:
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
_hud_draw_sub_idx:
		.BYTE	0
byte_2D:
		.BYTE 0
byte_2E:
		.BYTE 0
_cur_side:
		.BYTE 0
byte_30:
		.BYTE 0
byte_31:
		.BYTE 0
_delay_counter:
		.BYTE 0,0
_game_main_sub_idx:
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
_1p_stage:
		.BYTE 0
_2p_stage:
		.BYTE 0
_1p_lives:
		.BYTE 0
_2p_lives:
		.BYTE 0
		.BYTE 0
byte_3D:
		.BYTE 0
byte_3E:
		.BYTE 0
byte_3F:
		.BYTE 0
byte_40:
		.BYTE 0
		.BYTE 0
byte_42:
		.BYTE 0
byte_43:
		.BYTE 0
byte_44:
		.BYTE 0
byte_45:
		.BYTE 0
byte_46:
		.BYTE 0
byte_47:
		.BYTE 0
byte_48:
		.BYTE 0
_game_vat49:
		.BYTE 0
byte_4A:
		.BYTE 0
_game_vat4B:
		.BYTE 0
byte_4C:
		.BYTE 0
_game_vat4D:
		.BYTE 0
byte_4E:
		.BYTE 0
byte_4F:
		.BYTE 0
_game_vat50:
		.BYTE 0
byte_51:
		.BYTE 0
byte_52:
		.BYTE 0
byte_53:
		.BYTE 0
byte_54:
		.BYTE 0
_game_vat55:
		.BYTE 0
byte_56:
		.BYTE 0
_game_vat57:
		.BYTE 0
byte_58:
		.BYTE 0
byte_59:
		.BYTE 0
byte_5A:
		.BYTE 0
byte_5B:
		.BYTE 0
		.BYTE 0
byte_5D:
		.BYTE 0
_continues_count:
		.BYTE 0
byte_5F:
		.BYTE 0
byte_60:
		.BYTE 0
		.BYTE 0
byte_62:
		.BYTE 0
byte_63:
		.BYTE 0
byte_64:
		.BYTE 0
byte_65:
		.BYTE 0
byte_66:
		.BYTE 0
byte_67:
		.BYTE 0
byte_68:
		.BYTE 0
byte_69:
		.BYTE 0
byte_6A:
		.BYTE 0
byte_6B:
		.BYTE 0
byte_6C:
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_7E:
		.BYTE 0
byte_7F:
		.BYTE 0
_apu_chl0:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
_apu_chl1:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
_apu_chl2:
		.BYTE 0
byte_A1:
		.BYTE 0
byte_A2:
		.BYTE 0
byte_A3:
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_A7:
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
_cur_apu_chnl_ram_ofs:
		.BYTE 0
_cur_apu_chnl_ofs:
		.BYTE	0
		.BYTE 0
		.BYTE 0
		.BYTE 0
_apu_chl3:
		.BYTE 0
byte_B1:
		.BYTE 0
byte_B2:
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_B5:
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_B8:
		.BYTE 0
		.BYTE 0
_cur_track_data_ptr:
		.BYTE 0,0
byte_BC:
		.BYTE 0
byte_BD:
		.BYTE 0
_apu_load_tmp_track_ptr:
		.BYTE 0,0
_apu_chl4:
		.BYTE 0
byte_C1:
		.BYTE 0
byte_C2:
		.BYTE 0
byte_C3:
		.BYTE 0
byte_C4:
		.BYTE 0
byte_C5:
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_C8:
		.BYTE 0
		.BYTE 0
byte_CA:
		.BYTE 0
		.BYTE 0
byte_CC:
		.BYTE 0
byte_CD:
		.BYTE 0
byte_CE:
		.BYTE 0
byte_CF:
		.BYTE 0
_apu_ptrE5:
		.BYTE 0,0
byte_D2:
		.BYTE 0
byte_D3:
		.BYTE 0
_apu_load_tmp_ofs:
		.BYTE	0
_track_chnl_var_ofs:
		.BYTE 0
_apu_track_settings:
		.BYTE 0
_cur_track_ofs:
		.BYTE 0
byte_D8:
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_DE:
		.BYTE 0
byte_DF:
		.BYTE 0
		.BYTE 0
byte_E1:
		.BYTE 0
		.BYTE 0
byte_E3:
		.BYTE 0
byte_E4:
		.BYTE 0
byte_E5:
		.BYTE 0
byte_E6:
		.BYTE 0
byte_E7:
		.BYTE 0
byte_E8:
		.BYTE 0
byte_E9:
		.BYTE 0
byte_EA:
		.BYTE 0
byte_EB:
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_EE:
		.BYTE 0
byte_EF:
		.BYTE 0
		.BYTE 0
_pads_tmp:
		.BYTE 0,0,0,0
_pads_press:
		.BYTE 0,0
_pads_held:
		.BYTE 0,0
byte_F9:
		.BYTE 0
byte_FA:
		.BYTE 0
byte_FB:
		.BYTE 0
byte_FC:
		.BYTE 0
byte_FD:
		.BYTE 0
_ppu_mask_shadow:
		.BYTE 0
_ppu_ctrl_shadow:
		.BYTE 0

		ECHO "-------------"
		ECHO "zero ram free:",[$100-.]
		ECHO "-------------"

		ORG $0100

_cur_prg_bank:
		.BYTE 0
_cur_apu_idx:
		.BYTE 0
byte_102:
		.BYTE 0
byte_103:
		.BYTE 0
byte_104:
		.BYTE 0
byte_105:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0

		ORG $0200

_spr_buf:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

		ORG $0300

byte_300:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_310:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_320:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_330:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_340:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_350:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_440:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0
byte_458:
		.BYTE 0
byte_459:
		.BYTE 0
byte_45A:
		.BYTE 0
byte_45B:
		.BYTE 0
byte_45C:
		.BYTE 0
byte_45D:
		.BYTE 0
byte_45E:
		.BYTE 0
		.BYTE 0
byte_460:
		.BYTE 0
byte_461:
		.BYTE 0
byte_462:
		.BYTE 0
byte_463:
		.BYTE 0
		.BYTE 0
byte_465:
		.BYTE 0
byte_466:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0
_main_sub_idx_backup:
		.BYTE 0
_sub_sub_idx_backup:
		.BYTE 0
_data_idx:
		.BYTE 0
		.BYTE 0
_data_load_exit_pc_backup:
		.BYTE 0,0
_error_code:
		.BYTE 0
		.BYTE 0
_files_buf:
		.BYTE 0,0,0,0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
_disk_info_buf:
		.BYTE 0,0,0,0,0,0
_req_side:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0
_status_fifo:
		.BYTE 0
		.BYTE 0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0
byte_500:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_520:
		.BYTE 0
		.BYTE 0
byte_522:
		.BYTE 0
byte_523:
		.BYTE 0
		.BYTE 0
byte_525:
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_52D:
		.BYTE 0
byte_52E:
		.BYTE 0
byte_52F:
		.BYTE 0
		.BYTE 0
byte_531:
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_53C:
		.BYTE 0
byte_53D:
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_540:
		.BYTE 0
byte_541:
		.BYTE 0
		.BYTE 0
byte_543:
		.BYTE 0
byte_544:
		.BYTE 0
byte_545:
		.BYTE 0
byte_546:
		.BYTE 0
byte_547:
		.BYTE 0
byte_548:
		.BYTE 0
byte_549:
		.BYTE 0
byte_54A:
		.BYTE 0
byte_54B:
		.BYTE 0
byte_54C:
		.BYTE 0
byte_54D:
		.BYTE 0
byte_54E:
		.BYTE 0
byte_54F:
		.BYTE 0
byte_550:
		.BYTE 0
byte_551:
		.BYTE 0
byte_552:
		.BYTE 0
byte_553:
		.BYTE 0
byte_554:
		.BYTE 0
byte_555:
		.BYTE 0
byte_556:
		.BYTE 0
byte_557:
		.BYTE 0
		.BYTE 0
byte_559:
		.BYTE 0
byte_55A:
		.BYTE 0
byte_55B:
		.BYTE 0
byte_55C:
		.BYTE 0
byte_55D:
		.BYTE 0
byte_55E:
		.BYTE 0
byte_55F:
		.BYTE 0
byte_560:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_580:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_5A0:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_5C0:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_5E0:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_600:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_640:
		.BYTE 0
byte_641:
		.BYTE 0
		.BYTE 0
byte_643:
		.BYTE 0
byte_644:
		.BYTE 0
byte_645:
		.BYTE 0
byte_646:
		.BYTE 0
byte_647:
		.BYTE 0
byte_648:
		.BYTE 0
byte_649:
		.BYTE 0
byte_64A:
		.BYTE 0
byte_64B:
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_64E:
		.BYTE 0
byte_64F:
		.BYTE 0
byte_650:
		.BYTE 0
byte_651:
		.BYTE 0
byte_652:
		.BYTE 0
byte_653:
		.BYTE 0
byte_654:
		.BYTE 0
byte_655:
		.BYTE 0
byte_656:
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_65D:
		.BYTE 0
		.BYTE 0
byte_65F:
		.BYTE 0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
byte_6C0:
		.BYTE 0
byte_6C1:
		.BYTE 0
		.BYTE 0
byte_6C3:
		.BYTE 0
byte_6C4:
		.BYTE 0
byte_6C5:
		.BYTE 0
byte_6C6:
		.BYTE 0
byte_6C7:
		.BYTE 0
byte_6C8:
		.BYTE 0
byte_6C9:
		.BYTE 0
byte_6CA:
		.BYTE 0
byte_6CB:
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_6CE:
		.BYTE 0
byte_6CF:
		.BYTE 0
byte_6D0:
		.BYTE 0
		.BYTE 0
byte_6D2:
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
		.BYTE 0
byte_6DB:
		.BYTE 0
byte_6DC:
		.BYTE 0
byte_6DD:
		.BYTE 0
byte_6DE:
		.BYTE 0
byte_6DF:
		.BYTE 0
byte_6E0:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
_ppu_queue_buf:
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
_hi_scores:
		.BYTE 0,0,0,0
_1p_score:
		.BYTE 0,0,0,0
_2p_scores:
		.BYTE 0,0,0,0
		.BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.BYTE 0,0,0,0

;--------------------P-P-U----------------------

		ORG $2000

_PPU_CTRL:
		.BYTE 0
_PPU_MASK:
		.BYTE 0
_PPU_STATUS:
		.BYTE 0
_PPU_OAM_ADDR:
		.BYTE 0
_PPU_OAM_DATA:
		.BYTE 0
_PPU_SCROLL:
		.BYTE 0
_PPU_ADDR:
		.BYTE 0
_PPU_DATA:
		.BYTE 0

;--------------------A-P-U----------------------

		ORG $4000

_apu_PULSE1_ENV:
		.BYTE 0
_apu_PULSE1_SWEEP:
		.BYTE	0
_apu_PULSE1_TIME:
		.BYTE 0
_apu_PULSE1_LEN:
		.BYTE 0
_apu_PULSE2_ENV:
		.BYTE 0
_apu_PULSE2_SWEEP:
		.BYTE	0
_apu_PULSE2_TIME:
		.BYTE 0
_apu_PULSE2_LEN:
		.BYTE 0
_apu_TRI_COUNT:
		.BYTE 0
_apu_TRI_UNUSED:
		.BYTE 0
_apu_TRI_TIME:
		.BYTE 0
_apu_TRI_LEN:
		.BYTE 0
_apu_NOISE_ENV:
		.BYTE 0
_apu_NOISE_UNUSED:
		.BYTE 0
_apu_NOISE_LOOP:
		.BYTE 0
_apu_NOISE_LEN:
		.BYTE 0
_apu_DMC_FREQ:
		.BYTE 0
_apu_DMC_LOAD:
		.BYTE 0
_apu_DMC_ADDR:
		.BYTE 0
_apu_DMC_LEN:
		.BYTE 0
_PPU_OAM_DMA:
		.BYTE 0
_apu_STATUS:
		.BYTE 0
_PAD0_REG:
		.BYTE 0
_PAD1_REG:
		.BYTE 0
