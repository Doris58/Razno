*----------------------------------------------------------------------------
*Zadatak 1. (5 bodova) 
*Napisite program za MC68k koji racuna zbroj elemenata vezane liste 8-bitnih BCD brojeva. *Pocetna adresa vezane liste dana je na adresi $6000, 
*dok je duljina vezane liste (tj. broj elemenata u vezanoj listi) 
*dan 16-bitnom vrijednosti s adrese $6004. 
*List u vezanoj listi sastoji se od 32-bitne adrese iduceg lista i 8-bitnog BCD broja.
*Rezultat treba spremiti kao 16-bitni BCD broj (ne 8-bitni jer pazimo na moguci prijenos)
*na adresu $6006.

*Podsjetnik. Instrukcija ABCD zbraja dva BCD broja zajedno s extend bitom. 
*Instrukcija dopusta samo .B sufiks (koji se ne mora navoditi), 
*a dolazi u dva oblika: ABCD Dy,Dx i ABCD -(Ay),-(Ax).
*----------------------------------------------------------------------------

DATA	EQU	$6000
PROGRAM	EQU	$6100

	ORG	DATA
	
POCETAK	DS.L	1
DULJINA	DS.W	1
REZULTAT	DS.W	1

	ORG	PROGRAM
	
START:	MOVEA.L	POCETAK, A0
	MOVE.W	DULJINA, D2
		
	MOVE.W #0, POCETAK
	MOVE.B #0, POCETAK+2
	
	MOVEA.L	#(POCETAK+2), A1
	MOVEA.L	#(POCETAK+4), A2
	
	TST.W	D2
	BEQ.S	DONE
	
	SUBQ.W	#1, D2
	MOVE	#0, CCR
	
LOOP:	MOVE.B	4(A0), POCETAK+3
	MOVEA.L	(A0), A0
	ABCD	-(A2), -(A1)
	ABCD	-(A2), -(A1)
	TST.W (A1)+
	TST.W (A2)+
	DBRA	D2, LOOP
		
DONE:	MOVE.W	POCETAK, REZULTAT

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
