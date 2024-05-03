*-------------------------------------------------------------------------
*Zadatak 1. (4 boda) Napisite program za MC68000 koji za string ASCII znakova 
*provjerava pojavljuju li se u njemu iskljucivo mala slova engleske abecede. 
*Pocetna adresa stringa sadrzana je u 32-bitnoj varijabli START s adrese $5000. 
*Pritom prva dva bajta stringa oznacavaju duljinu tog stringa u bajtovima. 
*(Niz znakova, tj. string, zapravo pocinje na trecem bajtu.) 
*Ukoliko se u stringu ne pojavljuje nissta osim malih slova engleske abecede 
*(uocimo da prazan string trivijalno zadovoljava ovaj uvjet!), 
*spremite u 8-bitnu varijablu PROVJERA s adrese $5004 vrijednost 1, 
*a u protivnom spremite u nju vrijednost 2.

*Uputa: Kako znamo da su ASCII kodovi uredeni, 
*tj. iza koda za znak a slijedi kod za znak b, itd. 
*dovoljno je za provjeru je li neki znak malo slovo 
*provjeriti je li njegov ASCII kod veci ili jednak ’a’ i manji ili jednak ’z’.
*-------------------------------------------------------------------------

DATA	EQU	$5000
PROGRAM	EQU	$5100

	ORG	DATA
	
START:	DS.L	1
PROVJERA:	DS.B	1

POCETAK	EQU	'a'
KRAJ	EQU	'z'

	ORG	PROGRAM
	
ZAD:	MOVEQ	#2, D0
	MOVEQ	#POCETAK, D1
	MOVEQ	#KRAJ, D3
	
	MOVEA.L	START, A0
	MOVE.W	(A0)+, D2
	TST.W	D2
	BEQ.S	OK
	
	SUBQ.W	#1, D2
LOOP:	CMP.B	(A0)+, D1
	BHI	DONE
	
	CMP.B	-1(A0), D3
	DBCS	D2, LOOP
	BCS	DONE
	
OK:	MOVEQ	#1, D0
DONE:	MOVE.B	D0, PROVJERA


	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

	END	ZAD		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
