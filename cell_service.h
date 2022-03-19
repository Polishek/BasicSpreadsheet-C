#ifndef CELL_SERVICE_H
#define CELL_SERVICE_H

#include "sheet_service.h"
#include "structures.h"

void checkCell(wsplXY lastCoord, char tabChar[WYS][DLU], Cell valueArray[HEIGHT][WIDTH]);

double clearValue(char tabChar[WYS][DLU], helpCoord* pomKoordy);

wsplXY oneCell(char tabChar[WYS][DLU], helpCoord* pomKoordy, wsplXY lastCoord, Cell valueArray[HEIGHT][WIDTH]);

double duoValue(char tabChar[WYS][DLU], helpCoord poczKoordy);

double duoCell(char tabChar[WYS][DLU], Cell valueArray[HEIGHT][WIDTH], helpCoord poczKoordy, wsplXY lastCoord);

#endif