#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//#include "sheet_service.h"
#include "structures.h"
#include "interface.h"
#include "cell_service.h"
#include "obsluga_listy.h"

void ShowConsoleCursor(int showFlag)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = showFlag;
	cursorInfo.dwSize = 100;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SimplePrintScreen(char screen[WYS][DLU], Cell valueArray[HEIGHT][WIDTH], wsplXY tempCoord, int posX, int posY)
{
	system("cls");								//czyszczenie konsoli; dodano dla lepszego efektu wizualnego; widoczne mruganie konsoli podczas operacji w arkuszu
	gotoxy(0, 0);

	for (int i = 0; i < WYS; ++i)
	{
		for (int j = 0; j < DLU; ++j)
		{
			putc(screen[i][j], stdout);
		}
		putc('\n', stdout);
	}

//	printf("Aktualna komorka Y: %d X: %d\n", posY, posX);
//	printf("Ostatnia komorka Y: %d X: %d\n", tempCoord.y, tempCoord.x);
	printf("Wartosc aktualnej komorki wartosc: %.3f\n", valueArray[posX][posY].value);
//	printf("Ostatnia odczytana wartosc: %f\n", valueArray[tempCoord.x][tempCoord.y].value);

	gotoxy(0, 20);
//	wypiszListe(valueArray, tempCoord);
}


void collectData() {

	ShowConsoleCursor(1);

	char charArray[WYS][DLU];
	Cell valueArray[HEIGHT][WIDTH];
	
	FILE* plik;
	if (plik = fopen("sheet.bin", "rb") != NULL) {

	}
	initializeCharArray(charArray);
	initializeValueArray(valueArray);

		int x = 2, y = 2;			//poczatkowe wspolrzedne kursora
		int posX = 0, posY = 0;		//wspolrzedne komorki w jakiej aktualnie znajduje sie kursor
		wsplXY lastCoord;
		lastCoord.x = 0;
		lastCoord.y = 0;

		while (1)
		{
			SimplePrintScreen(charArray, valueArray, lastCoord, posX, posY);

			gotoxy(x, y);

			//int ax = _kbhit(); // ta funkcja sie moze gdzies tez Panu przydac
			int c = _getch();

			int ifCross = 0;	//wartosc uzywana do kontroli przejsc miedzy komorkami

			if (c == 0xE0) //arrow
			{
				c = _getch();
				switch (c)
				{
				case 0x4B:
					--x;
					czyObszarX(&x, c, &ifCross, &posX);
					break;
				case 0x4D:
					++x;
					czyObszarX(&x, c, &ifCross, &posX);
					break;
				case 0x48:
					--y;
					czyObszarY(&y, c, &ifCross, &posY);
					break;
				case 0x50:
					++y;
					czyObszarY(&y, c, &ifCross, &posY);
					break;
				default:
					break;
				}

				if (ifCross) {
					lastCoord = correctCoordinates(c, posX, posY);
					checkCell(lastCoord, charArray, valueArray);
				}
			}
			else
				if (c == 0x08) {		//jezeli wcisnieto backspace to czysci znak na aktualnej pozycji
					charArray[y][x] = 'x';
				}
				else {
					if (c == 13) {	//jezeli wcisnieto spacje
						makeFile(valueArray);
						break;
					}
					else
					{
						charArray[y][x] = c;
					}
				}
		}
}