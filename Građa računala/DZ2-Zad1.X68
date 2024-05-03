*-----------------------------------------------------------
*ZADATAK 1. (3 boda) Napisite program za MC68k koji kopira sadrzaj 
*s memorijskih lokacija $6001-$6007 na memorijske lokacije $6801-$6807. 
*Sacuvajte redoslijed podataka (te ne mijenjajte sadrzaj bajta na adresi $6800). 
*Pritom rjesenje koje koristi (strogo) vise od dvije instrukcije sa sufiksom .B 
*donosi najvise 2 boda na ovome zadatku.
*-----------------------------------------------------------

	ORG	$6800
PART1:	DS.W	1
PART2:	DS.W	1
PART3:	DS.W	2
START:	MOVE.B 	#$1A, D1	; spremit cu u memoriju podatke iz primjera u zadatku, radi provjere
        MOVE.W	#$2371, D2
        MOVE.L	#$B224EF79, D3
        MOVE.B	D1, $6001
        MOVE.W  D2, $6002
        MOVE.L	D3, $6004 
 	MOVE.B	$6001, PART1+1
	MOVE.W 	$6002, PART2
	MOVE.L	$6004, PART3

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings

	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
