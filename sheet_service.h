#ifndef SHEET_SERVICE_H
#define SHEET_SERVICE_H

#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include "structures.h"

/** Funkcja odpowiedzialna za wywo³ywanie odpowiednich procedur potrzebnych do pozyskania wartosci tabeli */
void collectData();

void ShowConsoleCursor(int showFlag);

void SimplePrintScreen(char screen[WYS][DLU], Cell valueArray[HEIGHT][WIDTH], wsplXY tempCoord, int posX, int posY);

void gotoxy(int x, int y);


#endif
