
		ORG $8000

		ECHO "PROGRAM BEGIN"
		ECHO "-------------"

_total_free	SET 0

		BANK_START $00

		SECTION_START
;		INCLUDE "..\"
		.BYTE		$FF
		SECTION_END ""

		BANK_END 0,$C000