/*
============================================================================
Autor : Sebastian Weise & Lars Kahlert
Klasse : FA13
Projekt: Sudoku
Dateiname : mainMenue.c
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
Funktion mainMenue()
Beschreibung: Ruft die printMainMenue auf, um eine Oberfläche zu erhalten.
              Alle Eingaben bezüglich des Menue´s werden von
              dieser Funktion abgefragt und ausgewertet. Für welche Auswahl
              sich der Spieler entscheidet, diese Funktion leitet ihn an
              die richtige Funktion weiter.
Uebergabeparameter: -
Rueckgabeparameter: -
============================================================================
*/
int mainMenue() {
    // Variablen
    char sMenue[20];
    int iexit;

    printMainMenue();

    printf("\n\tAuswahl: ");
    scanf(" %20s", sMenue);
    clear();

    if (strcmp(sMenue, "1") == 0)
    {
        if(strcmp(name, "Gast") == 0) {
            signInUI();
        }
    }
    else if (strcmp(sMenue, "2") == 0)
    {
        if(strcmp(name, "Gast") == 0) {
            signUpUI();
        }
    }
    else if (strcmp(sMenue, "3") == 0)
    {
        do{
            iexit = printHighScore();
            clear();
        }while(iexit != 1);
    }
    else if (strcmp(sMenue, "4") == 0)
    {
        do{
            iexit = printRules();
            clear();
        }while(iexit != 1);
    }
    else if (strcmp(sMenue, "5") == 0)
    {
        do {
            iexit = StartGameMenue();
            clear();
        }while (iexit != 1);
    }
    else if (strcmp(sMenue, "X") == 0 || strcmp(sMenue, "x") == 0)
    {
        return 1;
    }
    return 0;
}

/*
============================================================================
Funktion StartGameMenue()
Beschreibung: Ruft die printStartGame auf, um eine Oberfläche zu erhalten.
              Alle Eingaben bezüglich des Schwierigkeitsgrades werden von
              dieser Funktion abgefragt und ausgewertet. Jeweils die ein-
              gegebene Schwierigkeitsstufe wird zum Start des Sudokus über-
              geben.
Uebergabeparameter: -
Rueckgabeparameter: -
============================================================================
*/
int StartGameMenue() {
    // Variablen
    char sStartGame[] = {""};
    int iLevel, iReturnCode;

    printStartGame();

    printf("\n\tAuswahl: ");
    scanf(" %s", sStartGame);

    if (strcmp(sStartGame, "1") == 0)
    {
        iLevel = 1;
        iReturnCode = 1;
    }
    else if (strcmp(sStartGame, "2") == 0)
    {
        iLevel = 2;
        iReturnCode = 1;
    }
    else if (strcmp(sStartGame, "3") == 0)
    {
        iLevel = 3;
        iReturnCode = 1;
    }
    else if (strcmp(sStartGame, "X") == 0 || strcmp(sStartGame, "x") == 0) {
        iReturnCode = 1;
    }
    else {
        iReturnCode = 0;
    }

    gameUI(iLevel);
    return iReturnCode;
}

/*
============================================================================
Funktion printMainMenue()
Beschreibung: Gibt lediglich das MainMenue aus. Allerdings variert das Menu
              in seiner Anzeige, je nach dem ob ein Spieler angemeldet oder
              abgemeldet ist.
Uebergabeparameter: -
Rueckgabeparameter: imainMenue
============================================================================
*/
void printMainMenue() {
    printSudokuLogo();

    printf("\n\t                      Willkommen %s", name);
    printf("\n\t%c", 201);
    printLines(MENUEWIDTH, 205);
    printf("%c", 187);

    if(strcmp(name, "Gast") == 0) {
        printf("\n\t%c 1. Login"
               "                                  "
               "                   %c", 186,186);
        printf("\n\t%c 2. Register                        "
               "                          %c", 186,186);
    }
    printf("\n\t%c 3. Bestenliste                         "
           "                      %c", 186, 186);
    printf("\n\t%c 4. Spielregeln                         "
           "                      %c", 186, 186);
    printf("\n\t%c 5. Spiel starten                       "
           "                      %c", 186, 186);
    printf("\n\t%c                                        "
           "                      %c", 186, 186);
    printf("\n\t%c x Spiel beenden                        "
           "                      %c", 186, 186);
    printf("\n\t%c", 200);
    printLines(MENUEWIDTH, 205);
    printf("%c", 188);
}
/*
============================================================================
Funktion printStartGame()
Beschreibung: Gibt lediglich das Schwierigkeitsmenu aus.
Uebergabeparameter: -
Rueckgabeparameter: -
============================================================================
*/
void printStartGame() {
    printSudokuLogo();

    printf("\n\t%c", 201);
    printLines(MENUEWIDTH, 205);
    printf("%c", 187);

    printf("\n\t%c 1. Leicht                                                    %c"
           "\n\t%c 2. Normal                                                    %c"
           "\n\t%c 3. Schwer                                                    %c"
           "\n\t%c                                                              %c"
           "\n\t%c                                                              %c"
           "\n\t%c                                                              %c"
           "\n\t%c x Zum Menue                                                  %c",
           186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186);

    printf("\n\t%c", 200);
    printLines(MENUEWIDTH, 205);
    printf("%c", 188);
}