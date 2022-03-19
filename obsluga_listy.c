#define _CRT_SECURE_NO_WARRNINGS

#include <stdlib.h>

#include "structures.h"

void dodajBiorce(wsplXY tempCoord, wsplXY lastCoord, Cell valueArray[HEIGHT][WIDTH]) {
	
	dluzny* pGlowa = valueArray[tempCoord.x][tempCoord.y].pHead;
	int czyAktualizacja = 0;

	if (pGlowa == NULL) {
		dluzny* nowy = malloc(sizeof(dluzny));
		nowy->biorca.x = tempCoord.x;
		nowy->biorca.y = tempCoord.y;
		nowy->pNext = NULL;
	}
	else {
		while (pGlowa->pNext == NULL) {

		}
	}

	if (czyAktualizacja) {			//jezeli nie ma elementu w liscie
		Cell* nowy = malloc(sizeof(Cell));
	}


}


//void wypiszListe(Cell valueArray[HEIGHT][WIDTH], wsplXY lastCoord){
//
//	Cell* wsk = valueArray[lastCoord.x][lastCoord.y].pHead;
//	while (wsk != NULL)
//	{
//		printf("%d ", wsk->value);
//		wsk = wsk->pHead;
//	}
//}