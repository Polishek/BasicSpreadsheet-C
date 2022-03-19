#include <stdio.h>
#include <conio.h>

#include "data_collection.h"

void collectData() {

		ShowConsoleCursor(1);


		char values[HEIGHT][WIDTH];

		for (int i = 0; i < HEIGHT; ++i)
			for (int j = 0; j < WIDTH; ++j)
				values[i][j] = 'a' + (i * HEIGHT + j) % 26;
		int x = 0, y = 0;

		while (1)
		{
			SimplePrintScreen(values);

			gotoxy(x, y);

			//int ax = _kbhit(); // ta funkcja sie moze gdzies tez Panu przydac
			int c = _getch();

			//TUTAJ brakuje spradzenia czy nie wyjdziemy za ekran
			if (c == 0xE0) //arrow
			{
				c = _getch();
				switch (c)
				{
				case 0x4B:
					--x;
					break;
				case 0x4D:
					++x;
					break;
				case 0x48:
					--y;
					break;
				case 0x50:
					++y;
					break;
				default:
					break;
				}
			}
			else
				values[y][x] = c;





		}
		//gotoxy(10, 10);

}