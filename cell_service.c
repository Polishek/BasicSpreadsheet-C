#define _CRT_SECURE_NO_WARRNINGS

#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "arithmetic.h"
#include "obsluga_listy.h"

double clearValue(char tabChar[WYS][DLU], helpCoord* pomKoordy) {

	double wagaCalk = liczPotege(tabChar, *pomKoordy);
	double wynik = 0.0;
	int czyCiaglosc = 0;												//czy odczytywanie wartosci sie zaczelo jezeli tak to czyCiaglosc przyjmuje wartosc wieksza od 0
	int czyMinus = 0;													//czy odczytywana wartosc jest juz po przecinku czy nadal nalezy do liczb calkowitych, jezeli liczby calkowite to czyMinus przyjmuje 0

	for (int i = pomKoordy->startX; i <= pomKoordy->endX; i++) {
		char znak = tabChar[pomKoordy->constY][i];
		if (((znak == 'x') && (!czyCiaglosc)) || (znak == 0x2E)) {		//jezeli przed liczba jest 'x' a odczytywanie wartosci jeszcze sie nie rozpoczelo
			continue;
		}
		else {
			if (((znak == 'x') || (znak == '+') || (znak == '-') || (znak == '*') || (znak == '/')) && (czyCiaglosc)) {	//jezeli w srodku lub na koncu pojawia sie 'x' LUB '-'
				pomKoordy->startX = i;
				break;
			}
			else {
				if ((znak == 0x2D) && (!czyCiaglosc)) {					//jezeli jest minus przed wartoscia (i minus sie jeszcze nie powtarzal, jak powtorzony to drugi minus nie brany pod uwage)
					czyMinus++;
				}
				else {													//jezeli znak to zmien na int i dodaj do wartosci koncowej
					wynik += (znak - 48) * wagaCalk;
					wagaCalk /= 10;
					czyCiaglosc++;
				}
			}
		}
	}

	if (czyMinus) {
		wynik *= -1;
	}

	return wynik;
}

wsplXY oneCell(char tabChar[WYS][DLU], helpCoord* pomKoordy, wsplXY lastCoord, Cell valueArray[HEIGHT][WIDTH]) {
	wsplXY tempCoord;
	tempCoord.y = 0;
	char znak;
	int czyCiaglosc = 0;
	int liczba = 0;

	int waga = liczPotege(tabChar, *pomKoordy);

	for (int i = pomKoordy->startX; i <= pomKoordy->endX; i++) {
		znak = tabChar[pomKoordy->constY][i];

		if ((znak == 'x') && (!czyCiaglosc)) {	//jezeli 'x' wystepuje przed koordami
			continue;
		}
		else {
			if (((znak >= 0x30) && (znak <= 0x39)) && (czyCiaglosc)) {		//jezeli wystepuja cyfry po literze
				liczba += (znak - 48) * waga;
				waga /= 10;
			}
			else {
				if (((znak >= 0x41) && (znak <= 0x5A)) && (!czyCiaglosc)) {		//jezeli wystepuje litera i nie bylo wczesniej zadnej
					czyCiaglosc++;
					tempCoord.x = znak - 65;
				}
				else {
					pomKoordy->startX = i;
					break;
				}
			}
		}
	}
	
	tempCoord.y = liczba - 1;

	dodajBiorce(tempCoord, lastCoord, valueArray);				//nie dzia³a!

	return tempCoord;
}

double duoValue(char tabChar[WYS][DLU], helpCoord poczKoordy) {
	helpCoord tempCoord = poczKoordy;
	double wartoscA = 0.0, wartoscB = 0.0, wynik = 0.0;

	wartoscA = clearValue(tabChar, &tempCoord);

	char znak = tabChar[tempCoord.constY][tempCoord.startX++];

	wartoscB = clearValue(tabChar, &tempCoord);

	switch (znak)
	{
	case 0x2B:
		addition(&wynik, wartoscA, wartoscB);
		break;
	case 0x2D:
		subtraction(&wynik, wartoscA, wartoscB);
		break;
	case 0x2A:
		multiplication(&wynik, wartoscA, wartoscB);
		break;
	case 0x2F:
		division(&wynik, wartoscA, wartoscB);
		break;
	default:
		break;
	}
	
	return wynik;
}

double duoCell(char tabChar[WYS][DLU], Cell valueArray[HEIGHT][WIDTH], helpCoord poczKoordy, wsplXY lastCoord) {
	helpCoord tempCoord = poczKoordy;
	wsplXY miejsce;
	double wartoscA = 0.0, wartoscB = 0.0, wynik = 0.0;

	miejsce = oneCell(tabChar, &tempCoord, lastCoord, valueArray);
	wartoscA = valueArray[miejsce.x][miejsce.y].value;

	char znak = tabChar[tempCoord.constY][tempCoord.startX++];

	miejsce = oneCell(tabChar, &tempCoord, lastCoord, valueArray);
	wartoscB = valueArray[miejsce.x][miejsce.y].value;

	switch (znak)
	{
	case 0x2B:
		addition(&wynik, wartoscA, wartoscB);
		break;
	case 0x2D:
		subtraction(&wynik, wartoscA, wartoscB);
		break;
	case 0x2A:
		multiplication(&wynik, wartoscA, wartoscB);
		break;
	case 0x2F:
		division(&wynik, wartoscA, wartoscB);
		break;
	default:
		break;
	}

	return wynik;
}

double bothElements(char tabChar[WYS][DLU], Cell valueArray[HEIGHT][WIDTH], helpCoord poczKoordy, wsplXY lastCoord) {
	int poz = poczKoordy.startX;
	double wartoscA = 0.0, wartoscB = 0.0, wynik;
	char znak = tabChar[poczKoordy.constY][poz];
	char operacja;

	while (znak == 'x') {
		poz++;
		char znak = tabChar[poczKoordy.constY][poz];
	}

	if (((znak >= 0x30) && (znak <= 0x39)) || (znak == '-')) {
		wartoscA = clearValue(tabChar, &poczKoordy);
		operacja = tabChar[poczKoordy.constY][poczKoordy.startX++];
		wsplXY miejsce = oneCell(tabChar, &poczKoordy, lastCoord, valueArray);
		wartoscB = valueArray[miejsce.x][miejsce.y].value;
	}
	else {
		wsplXY miejsce = oneCell(tabChar, &poczKoordy, lastCoord, valueArray);
		operacja = tabChar[poczKoordy.constY][poczKoordy.startX++];
		wartoscA = valueArray[miejsce.x][miejsce.y].value;
		wartoscB = clearValue(tabChar, &poczKoordy);
	}

	switch (operacja) 
	{
	case 0x2B:
		addition(&wynik, wartoscA, wartoscB);
		break;
	case 0x2D:
		subtraction(&wynik, wartoscA, wartoscB);
		break;
	case 0x2A:
		multiplication(&wynik, wartoscA, wartoscB);
		break;
	case 0x2F:
		division(&wynik, wartoscA, wartoscB);
		break;
	default:
		break;
	}
	
	return wynik;
}

void checkCell(wsplXY lastCoord, char tabChar[WYS][DLU], Cell valueArray[HEIGHT][WIDTH]) {
	
	helpCoord pomKoordy;
	pomKoordy.startX = 2 + lastCoord.x * 6;
	pomKoordy.endX = pomKoordy.startX + 4;
	pomKoordy.constY = 2+lastCoord.y*2;

	double Gieblo = valueArray[lastCoord.x][lastCoord.y].value;

	char znak;
	int opcja = 0;
	int czyCiaglosc = 0, czyPrzec = 0;
	int wagaCalk = 0;

	for (int i = pomKoordy.startX; i <= pomKoordy.endX; i++) {
		znak = tabChar[pomKoordy.constY][i];
		if ((znak == 'x') && (!czyCiaglosc)) {		//jezeli jest 'x' i znajduje sie przed liczba
			continue;
		}
		else {
			if (((znak == 'x') && (czyCiaglosc)) || ((znak == 0x2E) && (!czyCiaglosc))) {	//jezeli jest 'x' i pojawia sie w srodku odczytywanej wartosci LUB jezeli pojawia sie '.' i jest na poczatku samym
				break;
			}
			else {
				if ((((znak == 0x2B) || (znak == 0x2D)) && (!czyCiaglosc)) || (znak == 0x2E)) {	//jezeli pojawia sie '+' lub '-' PRZED wartoscia LUB jezeli pojawia sie przecinek w trakcie odczytywania wartosci
					continue;
				}
				else {
					if ((znak >= 0x30) && (znak <= 0x39)) {	//jezeli pojawia sie cyfra i nie jest ona po przecinku
						opcja++;
						czyCiaglosc++;
					}
					else {
						if ((znak >= 0x41) && (znak <= 0x5A)) {
							opcja += 5;
							czyCiaglosc++;
						}
						else {
							if ((znak == 0x2B) || (znak == 0x2D) || (znak == 0x2A) || (znak == 0x2F)) {
								opcja += 10;
							}
							else {
								opcja += 50;
							}
						}
					}
				}
			}
		}
	}

		if (opcja >= 50) {
			valueArray[lastCoord.x][lastCoord.y].value = 0;		//bledna wartosc zapisana w tabeli charow skutkuje wpisaniem wartosci 0 do tabeli wartosci
		}
		else {
			if (opcja >= 22) {
				valueArray[lastCoord.x][lastCoord.y].value = duoCell(tabChar, valueArray, pomKoordy, lastCoord);
			}
			else {
				if (opcja >= 17) {
					valueArray[lastCoord.x][lastCoord.y].value = bothElements(tabChar, valueArray, pomKoordy, lastCoord);
				}
				else {
					if (opcja >= 12) {
						valueArray[lastCoord.x][lastCoord.y].value = duoValue(tabChar, pomKoordy);
					}
					else {
						if (opcja >= 6) {
							wsplXY temp=oneCell(tabChar, &pomKoordy, lastCoord, valueArray);
							valueArray[lastCoord.x][lastCoord.y].value = valueArray[temp.x][temp.y].value;
						}
						else {
							valueArray[lastCoord.x][lastCoord.y].value =  clearValue(tabChar, &pomKoordy);
						}
					}
				}
			}
		}

		if (Gieblo != valueArray[lastCoord.x][lastCoord.y].value) {
//			updateValues(valueArray, lastCoord);	<--- funkcja aktualizujaca biorcow komorki
		}
}



