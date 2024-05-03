*--------------------------------------------------------------------------------
*ZADATAK 2. (4boda) 
*Napisite program za MC68000 koji za niz od pet 32-bitnih brojeva bez predznaka 
*racuna broj parnih elemenata te broj neparnih elemenata u tom nizu. 
*Brojevi su spremljeni uzastopno u memoriji pocevsi od adrese $5000.
*Trazene vrijednosti sespremaju zajedno u jednu 8-bitnu varijablu REZULTAT s adrese $5100
*na sljedeci nacin: 
*broj parnih brojeva niza sprema se u znacajnija 4 bita te varijable,
*a broj neparnih elemenata niza sprema u manje znacajna 4 bita te varijable.

*--------------------------------------------------------------------------------

*NAPOMENA: Rjesenje je bez upotrebe operacije dijeljenja i grananja.

*--------------------------------------------------------------------------------

	ORG	$5000
DATA1:	DS.L	1
DATA2:	DS.L	1
DATA3:	DS.L	1
DATA4:	DS.L	1
DATA5:	DS.L	1

	ORG	$5100
REZULTAT:	DS.B	1	

START:	MOVE.L	DATA1, D1 	*uzimam najmanje znacajni byte elementa niza (moze se u registar smjestiti i sva 32 bita, pa napraviti AND s #$1)
	AND.L	#$00000001, D1	*ovime ce mi od njega ostati samo najmanje znacajni bit, dakle 0 ili 1, sve prije ce biti 0
	MOVE.L	D1, D6		*spremam taj 0 ili 1 u registar D6; ovo je samo za prvi clan niza, sluzi kao inicijalizacija sume za broj neparnih elemenata
	
	MOVE.L	DATA2, D2
	AND.L	#$00000001, D2
	ADD.L 	D2, D6		*za ostale clanove niza: nadodajem njihov najmanje znacajni bit u sumu u registru D6
	
	MOVE.L	DATA3, D3
	AND.L	#$00000001, D3
	ADD.L	D3, D6
	
	MOVE.L	DATA4, D4
	AND.L	#$00000001, D4
	ADD.L	D4, D6
	
	MOVE.L	DATA5, D5
	AND.L	#$00000001, D5
	ADD.L	D5, D6		*u registru D6 sada je broj neparnih elemenata niza, jer su 1 doprinijele sumi, a 0 nisu
	
	MOVE.L	#$00000005, D7	*registar D7 postavljam na broj elemenata niza, tj. 5
	SUB.L	D6, D7		*od njega oduzimam broj neparnih elemenata, i time u D7 dobivam broj parnih elemenata
	
	LSL.B	#$4, D7		*ovime broj parnih elemenata niza dolazi u znacajnija 4 bita svog najmanje znacajnog bytea, a ostala 4 bita su nule
	OR.L	D6, D7		*ovime dobivamo trazeni rezultat u najmanje znacajnom byteu registra D7
	
	MOVE.B	D7, REZULTAT


	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings

	END	START		; last line of source


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
