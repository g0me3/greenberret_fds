
		ORG $8000

		BANK_START $04

		SECTION_START
		FAR_PTR _stage1_data
		INCLUDE "../map/FC_1.inc"
		SECTION_END "STAGE 1 data (FC_1)"

		SECTION_START
		FAR_PTR _stage2_data
		INCLUDE "../map/FC_2.inc"
		SECTION_END "STAGE 2 data (FC_2)"

		SECTION_START
		FAR_PTR _stage3_data
		INCLUDE "../map/FC_3.inc"
		SECTION_END "STAGE 3 data (FC_3)"

		SECTION_START
		FAR_PTR _stage4_data
		INCLUDE "../map/FC_4.inc"
		SECTION_END "STAGE 4 data (FC_4)"

		SECTION_START
		FAR_PTR _stage5_data
		INCLUDE "../map/FC_5.inc"
		SECTION_END "STAGE 5 data (FC_5)"

		SECTION_START
		FAR_PTR _stage6_data
		INCLUDE "../map/FC_6.inc"
		SECTION_END "STAGE 6 data (FC_6)"

		BANK_END 4,$C000
