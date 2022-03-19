#include <stdlib.h>
#include "structures.h"

void initializeCharArray(char charArray[WYS][DLU]) {

	int pomocnicza = 4;
	int jakaLitera = 65;
	int temp = 49;

	for (int i = 0; i < WYS; i++) {
		for (int j = 0; j < DLU; j++) {
			if (i == 0) {									//LINIA ZERO
				if (j == pomocnicza) {
					charArray[i][j] = jakaLitera++;
					pomocnicza += 6;
				}
				else {
					charArray[i][j] = 0x20;					//od pewnego momentu nie moge uzywac '\0' tylko nagle ' ' 
				}
			}
			else {
				if (i == 1) {								//LINIA JEDEN
					if (j == 0) {							//RZAD ZERO
						charArray[i][j] = 0x20;
					}
					else {
						if (j == 1) {						//RZAD JEDEN
							charArray[i][j] = 201;
						}
						else {
							if (j == (DLU - 1)) {			//RZAD OSTATNI
								charArray[i][j] = 187;
							}
							else {
								if (j % 6 != 1) {			//RZAD GRANICZNY
									charArray[i][j] = 205;
								}
								else {
									charArray[i][j] = 203;
								}
							}
						}
					}
				}
				else {
					if (i == WYS - 1) {						//OSTATNIA LINIA
						if (j == 0) {
							charArray[i][j] = 0x20;
						}
						else {
							if (j == 1) {
								charArray[i][j] = 200;
							}
							else {
								if (j == DLU - 1) {
									charArray[i][j] = 188;
								}
								else {
									if (j % 6 != 1) {
										charArray[i][j] = 205;
									}
									else {
										charArray[i][j] = 202;
									}
								}
							}
						}
					}
					else {
						if (i % 2 == 0) {					//LINIA PARZYSTA
							if (j == 0) {
								charArray[i][j] = temp++;
							}
							else {
								if ((j == 1) || (j % 6 == 1)) {
									charArray[i][j] = 186;
								}
								else {
									charArray[i][j] = 'x';
								}
							}
						}
						else {
							if (j == 0) {
								charArray[i][j] = 0x20;
							}
							else {
								if (j == DLU - 1) {
									charArray[i][j] = 185;
								}
								else {
									if (j == 1) {
										charArray[i][j] = 204;
									}
									else {
										if (j % 6 != 1) {
											charArray[i][j] = 205;
										}
										else {
											charArray[i][j] = 206;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void initializeValueArray(Cell valueArray[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			valueArray[i][j].value = 0;
			valueArray[i][j].pHead = NULL;
		}
	}
}

void czyObszarX(int* x, int key, int* czyPrzejscie, int* posX) {
	int wartosc = *x;
	if ((*x == 0) || (*x == 1)) {	//jezeli pozycja wskazuje numeracje wierszy LUB lewa granice arkusza
		++(*x);
	}
	else {
		if ((*x % 6 == 1) && (*x != (DLU - 1))) {	//jezeli pozycja wskazuje pionowa granice miedzy komorkami
			if (key == 0x4D) {	//jezeli kursor ma zostac przesuniety w lewo
				++(*x);			//przejscie kursora
				++(*posX);
			}
			else {
				--(* x);
				--(*posX);
			}
			*czyPrzejscie = 1;
		}
		else {
			if (*x == (DLU - 1)) {  //jezeli pozycja wskazuje prawa granice obszaru roboczego
				--(*x);
			}
		}
	}
}

void czyObszarY(int* y, int key, int* czyPrzejscie, int* posY) {
	if ((*y == 0) || (*y == 1)) {	//jezeli pozycja wskazuje nazewnictwo kolumn
		++(*y);
	}
	else {
		if ((*y % 2 != 0) && (*y != (WYS - 1))) {  //jezeli pozycja wskazuje pozioma granice miedzy komorkami
			if (key == 0x50) {
				++(*y);
				++(*posY);
			}
			else {
				--(*y);
				--(*posY);
			}
			*czyPrzejscie = 1;
		}
		else {
			if (*y == (WYS - 1)) {
				--(*y);
			}
		}
	}
}

wsplXY correctCoordinates(int key, int posX, int posY) {
	wsplXY temp;
	temp.x = posX;
	temp.y = posY;
	
	if (key == 0x4D) {			//ostatnia pozycja X przed zmiana komorki w poziomie
		temp.x = --posX;
	}
	else {
		if (key == 0x4B) {
			temp.x = ++posX;
		}
	}

	if (key == 0x50) {			//ostatnia pozycja X przed zmiana komorki w poziomie
		temp.y = --posY;
	}
	else {
		if (key == 0x48) {
			temp.y = ++posY;
		}
	}

	return temp;
}