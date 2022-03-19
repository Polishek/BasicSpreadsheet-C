#include <math.h>

#include "structures.h"

double liczPotege(char tabChar[WYS][DLU], helpCoord pomKoordy) {
	double wagaWynik = 0.0;
	int czyCiaglosc = 0;

	for (int i = pomKoordy.startX; i <= pomKoordy.endX; i++) {
		char znak = tabChar[pomKoordy.constY][i];
		if ((znak >= 0x30) && (znak <= 0x39)) {
			wagaWynik++;
			czyCiaglosc++;
		}
		else {
			if (((znak == 'x') || (znak == '.') || (znak == '+') || (znak == '-') || (znak == '*') || (znak == '/')) && (czyCiaglosc)) {
				break;
			}
			else {
				continue;
			}
		}
	}

	return 1 * pow(10, wagaWynik - 1);
}

void addition(double* result, double wartoscA, double wartoscB) {
	*result = wartoscA + wartoscB;
}

void subtraction(double* result, double wartoscA, double wartoscB) {
	*result = wartoscA - wartoscB;
}

void multiplication(double* result, double wartoscA, double wartoscB) {
	*result = wartoscA * wartoscB;
}

void division(double* result, double wartoscA, double wartoscB) {
	*result = wartoscA / wartoscB;
}