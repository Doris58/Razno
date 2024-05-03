*--------------------------------------------------------------------------------
*ZADATAK 2. (4 boda) 
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

START:	MOVE.B	DATA1+3, D0 	*uzimam najmanje znacajni byte elementa niza (moze se u registar smjestiti i sva 32 bita, pa napraviti AND s #$1)
	AND.B	#$01, D0	*ovime ce mi od njega ostati samo najmanje znacajni bit, dakle 0 ili 1, sve prije ce biti 0
	MOVE.B	D0, D1		*spremam taj 0 ili 1 u registar D1; ovo je samo za prvi clan niza, sluzi kao inicijalizacija sume za broj neparnih elemenata
	
	MOVE.B	DATA2+3, D0
	AND.B	#$01, D0
	ADD.B 	D0, D1		*za ostale clanove niza: nadodajem njihov najmanje znacajni bit u sumu u registru D1
	
	MOVE.B	DATA3+3, D0
	AND.B	#$01, D0
	ADD.B	D0, D1
	
	MOVE.B	DATA4+3, D0
	AND.B	#$01, D0
	ADD.B	D0, D1
	
	MOVE.B	DATA5+3, D0
	AND.B	#$01, D0
	ADD.B	D0, D1		*u registru D1 (najmanje znacajni byte) sada je broj neparnih elemenata niza, jer su 1 doprinijele sumi, a 0 nisu
	
	MOVE.B	#$5, D2		*najmanje znacajni byte u registru D2 postavljam na broj elemenata niza, tj. 5
	SUB.B	D1, D2		*od njega oduzimam broj neparnih elemenata, i time u D2 dobivam broj parnih elemenata
	
	LSL.B	#$4, D2		*ovime broj parnih elemenata niza dolazi u znacajnija 4 bita svog bytea, a ostala 4 bita su nule
	OR.B	D1, D2		*ovime dobivamo trazeni rezultat u najmanje znacajnom byteu registra D2
	
	MOVE.B	D2, REZULTAT


	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings

	END	START		; last line of source


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
