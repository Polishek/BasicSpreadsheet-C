#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

void makeFile(Cell valueArray[HEIGHT][WIDTH]){
	FILE* plik = fopen("sheet.bin", "wb");

	for (int i= 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			fwrite(valueArray[i][j].value, sizeof(double), 1, plik);
		}
	}

	fclose(plik);
}