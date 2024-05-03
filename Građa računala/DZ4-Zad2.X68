*----------------------------------------------------------------------------
*Zadatak 2. (5 bodova) 
*Napisite program za MC68000 koji u stringu zamjenjuje sva mala slova 
*engleske abecede od ‘k’ od ‘t’ (oba ukljucivo) znakom ‘.’ (znak tocka). 
*Pocetna adresa stringa sadrzana je u varijabli START s adrese $6000, 
*a duljina stringa sadrzana je u 16-bitnoj varijabli DULJINA s adrese $6004. 
*String pocetno ne sadrzi znakove koji nisu slova engleske abecede.
*----------------------------------------------------------------------------

DATA	EQU	$6000
PROGRAM	EQU	$6100

	ORG	DATA

START:	DS.L	1
DULJINA:	DS.W	1

TOCKA	EQU	'.'
POCETAK	EQU	'k'
KRAJ	EQU	't'

	ORG	PROGRAM
	
ZAD:	MOVEQ	#TOCKA, D0
	MOVEQ	#POCETAK, D1
	MOVEQ	#KRAJ, D3
	
	MOVEA.L	START, A0
	
	MOVE.W	DULJINA, D2
	TST.W	D2
	BEQ.S	DONE
	
	SUBQ.W	#1, D2
LOOP:	CMP.B	(A0)+, D1
	BHI	NEMOJ_STAVITI_TOCKU
	
	CMP.B	-1(A0), D3
	BCS	NEMOJ_STAVITI_TOCKU
	
STAVI_TOCKU:	MOVE.B	D0, -1(A0)

NEMOJ_STAVITI_TOCKU:	DBRA	D2, LOOP

DONE:	EQU	*


	MOVE.B	#9,D0
	TRAP	#15		; halt simulator


	END	ZAD		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
