#ifndef INTERFACE_H
#define INTERFACE_H

#include "sheet_service.h"
#include "structures.h"

/** Funkcja zapisaujaca odpowiednie wartosci danym komorkow */
void initializeCharArray(char tablica[WYS][DLU]);

/** Funkcja inicjalizuj¹ca tabele wartosci z wartoscia poczatkowa 0 */
void initializeValueArray(Cell valueArray[HEIGHT][WIDTH]);

/**Funkcja sprawdzaj¹ca oraz dbaj¹ca, aby kursor przemieszcza³ siê tylko po polach komorek w linii poziomej
*	Dodatkowo przesy³a informacje dotycz¹ce wspó³rzêdnych potrzebnych przy obs³udze tablicy wartoœci.
*	Dodatkowo sprawdza czy potrzebna jest kontrola zawartoœci komórki w tablicy charów.
*/
int czyObszarX(int* x, int key, int* czyPrzejscie, int* posX);

/**Funkcja sprawdzaj¹ca oraz dbaj¹ca, aby kursor przemieszcza³ siê tylko po polach komorek w linii pionowej.
*	Dodatkowo przesy³a informacje dotycz¹ce wspó³rzêdnych potrzebnych przy obs³udze tablicy wartoœci.
*	Dodatkowo sprawdza czy potrzebna jest kontrola zawartoœci komórki w tablicy charów.
*/
int czyObszarY(int* y, int key, int* czyPrzejscie, int* posY);

wsplXY correctCoordinates(int key, int posX, int posY);

#endif
