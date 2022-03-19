#ifndef STRUCTURES_H
#define STRUCTURES_H

#define HEIGHT 4 //UWAGA!!! maksymalnie 9
#define WIDTH 4 //UWAGA!!! maksymalnie 26
#define WYS 2+HEIGHT*2
#define DLU 2+WIDTH*6

typedef struct wsplXY {
	int x;
	int y;
}wsplXY;

/**
* Struktura komorki ktora przechowuje odczytanie wartosci
*/
typedef struct Cell{
	double value;
	struct dluzny* pHead;
}Cell;

typedef struct dluzny {
	wsplXY biorca;
	struct dluzny* pNext;
}dluzny;

/**
* Struktura pomocnicza przy odczytywaniu tablicy charów w pliku cell_service
*/
typedef struct helpCoord {
	int startX, endX, constY;
}helpCoord;

#endif

