
		ORG $8000

		BANK_START $05

		SECTION_START
		FAR_PTR _stage4_data
		INCLUDE "..\FC_4.inc"
		SECTION_END "STAGE 4 data (FC_4)"

		SECTION_START
		FAR_PTR _ending_data
		INCLUDE "..\FC_E.inc"
		SECTION_END "ENDING data (FC_E)"

		SECTION_START
		FAR_PTR _title_data
		INCLUDE "..\FC_S.inc"
		SECTION_END "TITLE data (FC_S)"

		BANK_END 5,$C000
