#ifndef INTERFACE_H
#define INTERFACE_H

#include "sheet_service.h"
#include "structures.h"

/** Funkcja zapisaujaca odpowiednie wartosci danym komorkow */
void initializeCharArray(char tablica[WYS][DLU]);

/** Funkcja inicjalizuj�ca tabele wartosci z wartoscia poczatkowa 0 */
void initializeValueArray(Cell valueArray[HEIGHT][WIDTH]);

/**Funkcja sprawdzaj�ca oraz dbaj�ca, aby kursor przemieszcza� si� tylko po polach komorek w linii poziomej
*	Dodatkowo przesy�a informacje dotycz�ce wsp�rz�dnych potrzebnych przy obs�udze tablicy warto�ci.
*	Dodatkowo sprawdza czy potrzebna jest kontrola zawarto�ci kom�rki w tablicy char�w.
*/
int czyObszarX(int* x, int key, int* czyPrzejscie, int* posX);

/**Funkcja sprawdzaj�ca oraz dbaj�ca, aby kursor przemieszcza� si� tylko po polach komorek w linii pionowej.
*	Dodatkowo przesy�a informacje dotycz�ce wsp�rz�dnych potrzebnych przy obs�udze tablicy warto�ci.
*	Dodatkowo sprawdza czy potrzebna jest kontrola zawarto�ci kom�rki w tablicy char�w.
*/
int czyObszarY(int* y, int key, int* czyPrzejscie, int* posY);

wsplXY correctCoordinates(int key, int posX, int posY);

#endif
