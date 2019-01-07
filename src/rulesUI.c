/*
============================================================================
Autor : Dominik Kuhbach & Julia Olbrich
Klasse : FA13
Projekt: Sudoku
Dateiname : rulesUI.c
Datum : xx.xx.2017
Beschreibung: -
Version : 1.0
Änderung : -
Programmschnittstelle: -
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
Funktion printRules()
Beschreibung: Gibt lediglich die Regeln aus. Durch das drücken der Taste x/X
              gelangt der Spieler dahin zurück, von wo er die Regeln aufge-
              rufen hat.
Uebergabeparameter: -
Rueckgabeparameter: -
============================================================================
*/
int printRules() {
    // Variablen
    char sAuswahl[] = {""};

    printSudokuLogo();

    printf("\n\t%c", 201);
    printLines(MENUEWIDTH, 205);
    printf("%c", 187);

    printf("\n\t%c Sudoku ist ein Zahlenraetsel. Das quadratische Spielfeld ist %c"
                   "\n\t%c in drei mal drei Bloecke unterteilt. Jeder dieser Bloecke be-%c"
                   "\n\t%c steht wiederum aus 9 Kaestchen. Das gesamte Spielfeld besteht%c"
                   "\n\t%c somit aus 81 Kaestchen die sich 9 Spalten und 9 Reihen zuord-%c"
                   "\n\t%c nen lassen. Von diesen 81 Feldern sind typischerweise 22 bis %c"
                   "\n\t%c 36 Felder vorgegeben, in denen Zahlen zwischen 1 bis 9 ste-  %c"
                   "\n\t%c hen.                                                         %c"
                   "\n\t%c                                                              %c"
                   "\n\t%c Das Ziel des Spiels ist, das Spielfeld zu vervollstaendigen. %c"
                   "\n\t%c Dabei sind die vom Spiel vorgegebenen Zahlen nicht veraender-%c"
                   "\n\t%c bar. Die leeren Kaestchen muessen mit Ziffern gefuellt wer-  %c"
                   "\n\t%c den. Dabei gelten folgende drei Regeln:                      %c"
                   "\n\t%c                                                              %c"
                   "\n\t%c     - In jeder Zeile duerfen die Ziffern von 1 bis 9 nur     %c"
                   "\n\t%c       einmal vorkommen                                       %c"
                   "\n\t%c     - In jeder Spalte duerfen die Ziffern von 1 bis 9 nur    %c"
                   "\n\t%c       einmal vorkommen                                       %c"
                   "\n\t%c     - In jedem Block duerfen die Ziffern von 1 bis 9 nur     %c"
                   "\n\t%c       einmal vorkommen                                       %c"
                   "\n\t%c                                                              %c"
                   "\n\t%c Das Spiel ist beendet, wenn alle Kaestchen korrekt gefuellt  %c"
                   "\n\t%c                                                              %c"
                   "\n\t%c x Zum Menue                                                  %c",186, 186, 186, 186, 186, 186, 186
            , 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186
            , 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186);

    printf("\n\t%c", 200);
    printLines(MENUEWIDTH, 205);
    printf("%c", 188);

    printf("\n\tAuswahl: ");
    scanf(" %s", sAuswahl);

    if (strcmp(sAuswahl, "x") == 0 || strcmp(sAuswahl, "X") == 0)
    {
        return 1;
    }
    else {
        return 0;
    }
}