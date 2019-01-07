/*
============================================================================
Autor : Sebastian Weise
Klasse : FA13
Projekt: Sudoku
Dateiname : main.c
Datum : 22.05.2017
Beschreibung: -
Version : 1.0
Änderung : -
Programmschnittstelle: "sudoku.h" ==>
Compiler: GCC 6.3
IDE: CLion 2017.1
============================================================================
*/

/*
============================================================================
Includierungen
============================================================================
*/
#include "../header/sudoku.h"
/*
============================================================================
Funktion main()
Beschreibung: Ich glaube hier passiert einfach etwas magisches <3
Uebergabeparameter: -
Rueckgabeparameter: 0 ==> alles OK
                    1 ==> es ist ein Fehler aufgetreten
============================================================================
*/
int main(void) {
    // Variablen
    int iexit = 0;

    strcpy(name, "Gast");

    fullscreen();
    unicorn();
    clear();

    do {
        iexit = mainMenue();
        clear();
    }while (iexit != 1);
    return 0;
}