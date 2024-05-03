*-----------------------------------------------------------
*ZADATAK 1. (4 boda) Napisite program za MC68000 koji spaja vrijednosti dviju 16-bitnih varijabli
*VAR1 (s memorijske lokacije $4000) i VAR2 (s memorijske lokacije $4002) 
*u jednu 32-bitnu varijablu REZ (s memorijske lokacije $4100). 
*Pritom je 32-bitna vrijednost rezultata dobivena na nacin 
*da su naizmjenicno uzimane 4-bitne vrijednosti jedne i druge varijable.
*-----------------------------------------------------------

	ORG	$4000
VAR1:	DS.W	1
VAR2:	DS.W	1
	ORG	$4100
REZ:	DS.L	1

POMOC	EQU	$4200
*-----------------------------------------------------------
START:	MOVE.B	VAR1, D0
	AND.B	#$000000F0, D0
	MOVE.B	D0, POMOC

	MOVE.B	VAR1, D0
	LSL.B	#$4, D0
	MOVE.B	D0, POMOC+1

	MOVE.B	VAR1+1, D0
	AND.B	#$000000F0, D0
	MOVE.B	D0, POMOC+2

	MOVE.B	VAR1+1, D0
	LSL.B	#$4, D0
	MOVE.B	D0, POMOC+3

	MOVE.L	POMOC, D0
*-----------------------------------------------------------	
	MOVE.B	VAR2, D1
	LSR.B	#$4, D1
	MOVE.B	D1, POMOC

	MOVE.B	VAR2, D1
	AND.B	#$0000000F, D1
	MOVE.B	D1, POMOC+1

	MOVE.B	VAR2+1, D1
	LSR.B	#$4, D1
	MOVE.B	D1, POMOC+2

	MOVE.B	VAR2+1, D1
	AND.B	#$0000000F, D1
	MOVE.B	D1, POMOC+3

	MOVE.L	POMOC, D1
*-----------------------------------------------------------
	OR.L	D0, D1
	
	MOVE.L 	D1, REZ


	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings

	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
