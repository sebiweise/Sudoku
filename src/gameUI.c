/*
============================================================================
Autor : Sebastian Weise, Dominik Kuhbach, Lars Kahlert
Klasse : FA13
Projekt: Sudoku
Dateiname : gameUI.c
Datum : 31.05.2017
Beschreibung: -
Version : 2.2
Änderung : -
Programmschnittstelle: "sudoku.h" ==> Schnittstelle zu allen
                                      anderen Quelldateien
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
Funktionsprototyping für lokale Funktionen
    (Werden in keiner anderen Quelldatei benötigt)
============================================================================
*/
int insertCommand(void);
int setColumn(void);
int setRow(void);
int setValue(void);
void setFieldValue(int sudoku[SIZE][SIZE], int, int, int, int,int);
void showRules(void);
void resetSudoku(int sudoku[SIZE][SIZE]);
void solveSudoku(char sName[], int, int, int);
int showFinish(char sName[], int, int, int);

/*
============================================================================
Funktion gameUI()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: -
============================================================================
*/
void gameUI(int level) {
    // Variablen
    int sudoku[SIZE][SIZE];
    int iexit = 0;

    generateSudoku(sudoku, (unsigned int) level);
    t = time(0);

    iGamePoints = 0;
    do {
        iexit = startSudoku(sudoku, level);
    }while (iexit == 0);

    // Start des Timers
    timer(1);
}

/*
============================================================================
Funktion startSudoku()
Beschreibung: -
Uebergabeparameter: int sudoku[SIZE][SIZE]
Rueckgabeparameter:  0 ==> Wenn das Spiel nicht verlassen werden soll.
                     1 ==> Wenn das Spiel verlassen werden soll.
============================================================================
*/
int startSudoku(int sudoku[SIZE][SIZE], int iLevel){
    // Variablen
    int iReturncode = 0, iexit, iMenue = 0;
    int iColumn = 0, iRow = 0, iValue = 0;

    printSudoku(sudoku);

    iMenue = insertCommand();

    switch (iMenue){
        case 1:
            iReturncode = 1;
            break;
        case 2:
            showRules();
            iReturncode = 0;
            break;
        case 3:
            solveSudoku(name,iGamePoints,0,iLevel);
            iReturncode = 1;
            break;
        case 4:
            iColumn = setColumn();
            if(iColumn != 0) {
                iRow = setRow();
            }
            if(iRow != 0) {
                iValue = setValue();
            }
            if(iValue != 0) {
                setFieldValue(sudoku,iLevel,iColumn,iRow,iValue,0);
            }
            iReturncode = 0;
            break;
        case 5:
            iColumn = setColumn();
            if(iColumn != 0) {
                iRow = setRow();
            }
            if(iRow != 0) {
                setFieldValue(sudoku,iLevel,iColumn,iRow,0,1);
            }
            iReturncode = 0;
            break;
        case 6:
            resetSudoku(sudoku);
            iReturncode = 0;
            break;
        case 7:
            iColumn = setColumn();
            if(iColumn != 0) {
                iRow = setRow();
            }
            if(iRow != 0) {
                getField(iColumn,iRow);
                setFieldValue(sudoku,iLevel,iColumn,iRow,
                              getField(iColumn,iRow),1);
                pause();
            }
            iReturncode = 0;
            break;
        default:
            printf("\n\t\tUngueltige Eingabe!!!\n\t\t");
            pause();
            break;
    }
    clear();
    return iReturncode;
}
/*
================================================================================
Funktion insertCommand()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: 0 ==> Ungültige oder keine Eingabe.
                    1 ==> Wenn das Spiel beendet werden soll.
                    2 ==> Wenn die Regeln angezeigt werden sollen.
                    3 ==> Wenn das Sudoku vollständig gelöst werden soll.
                    4 ==> Wenn ein Feld eingegeben werden soll.
                    5 ==> Wenn ein Feld geleert werden soll.
                    6 ==> Wenn das Sudoku resettet werden soll.
                    7 ==> Wenn ein Feld gelöst werden soll.
================================================================================
*/
int insertCommand(void) {
    // Variablen
    char cAuswahl;
    int iReturnCode = 0;

    printf("\n\t\tBefehl: ");
    scanf(" %c", &cAuswahl);
    fflush(stdin);

    if (cAuswahl == 'X' || cAuswahl == 'x') {
        iReturnCode = 1;
    } else if(cAuswahl == 'R' || cAuswahl == 'r') {
        iReturnCode = 2;
    }else if (cAuswahl == 'K' || cAuswahl == 'k') {
        iReturnCode = 3;
    } else if(cAuswahl == 'E' || cAuswahl == 'e'){
        iReturnCode = 4;
    } else if (cAuswahl == '0'){
        iReturnCode = 5;
    }else if (cAuswahl == 'Z' || cAuswahl == 'z') {
        iReturnCode = 6;
    } else if (cAuswahl == 'N' || cAuswahl == 'n') {
        iReturnCode = 7;
    }else{
        iReturnCode = 0;
    }

    return iReturnCode;
}
/*
============================================================================
Funktion printSudoku()
Beschreibung: Gibt das Sudoku-Feld aus. Sowohl die Zahlen aus dem mit-
              gegebenen Sudoku als auch die GameUI an sich.
              Die Zahlen werden aus dem Array Zeilenweise ausgelesen und
              ausgegeben. Währenddessen und nach diesem Vorgang, wird das
              Spielfeld umd die Zahlen herrum gebaut.
Uebergabeparameter: int sudoku[SIZE][SIZE]
Rueckgabeparameter: -
============================================================================
*/
void printSudoku(int sudoku[SIZE][SIZE]){
    // Variablen
    int i, j;

    clear();

    printSudokuLogo();

    printf("\n\t\t   A    B    C      D    E    F      G    H    I");

    printf("\n\t\t%c", 201);
    printLines(50, 205);
    printf("%c", 187);

    for (i = 0; i < SIZE; ++i) {
        printf("\n\t%i\t%c", i + 1, 186);
        for (j = 0; j < SIZE; ++j) {

            if(sudoku[i][j] != 0) {
                printf("  %d  ",sudoku[i][j]);
            } else {
                printf("  %c  ", 250);
            }

            if (((j + 1) % 3) == 0) {
                printf(" %c", 186);
            }
        }
        if (((i + 1) % 3) == 0) {
            printf("\n\t\t%c", 204);
            printLines(50, 205);
            printf("%c", 185);
        }
    }
    printf("\n\t\t%c(E) Wert eingeben               (R) Regeln        %c",
           186, 186);
    printf("\n\t\t%c(0) Feld leeren                 (N) Feld loesen   %c",
           186, 186);
    printf("\n\t\t%c(Z) Sudoku resetten             (K) Sudoku loesen %c",
           186, 186);
    printf("\n\t\t%c(X) Spiel beenden                                 %c",
           186, 186);
    printf("\n\t\t%c", 200);
    printLines(50, 205);
    printf("%c", 188);
}
/*
============================================================================
Funktion setColumn()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: 1 - 9 ==> bei einer korrekt eingegebenen Spalte
                    0     ==> Bei einer fehlerhaften Eingabe
============================================================================
*/
int setColumn(void) {
    // Variablen
    int iReturnCode = 0;
    char cAuswahl;

    printf("\n\t\tAuswahl Spalte: ");
    scanf(" %c", &cAuswahl);
    fflush(stdin);

    if (cAuswahl == 'A' || cAuswahl == 'a') {
        iReturnCode = 1;
    } else if(cAuswahl == 'B' || cAuswahl == 'b') {
        iReturnCode = 2;
    } else if(cAuswahl == 'C' || cAuswahl == 'c') {
        iReturnCode = 3;
    } else if(cAuswahl == 'D' || cAuswahl == 'd') {
        iReturnCode = 4;
    } else if(cAuswahl == 'E' || cAuswahl == 'e') {
        iReturnCode = 5;
    } else if(cAuswahl == 'F' || cAuswahl == 'f') {
        iReturnCode = 6;
    } else if(cAuswahl == 'G' || cAuswahl == 'g') {
        iReturnCode = 7;
    } else if(cAuswahl == 'H' || cAuswahl == 'h') {
        iReturnCode = 8;
    } else if(cAuswahl == 'I' || cAuswahl == 'i') {
        iReturnCode = 9;
    } else {
        iReturnCode = 0;
    }
    printf("\n");
    return iReturnCode;
}

/*
============================================================================
Funktion setRow()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: 1 - 9 ==> bei einer korrekt eingegebenen Zeile
                    0     ==> Bei einer fehlerhaften Eingabe
============================================================================
*/
int setRow(void) {
    int iReturnCode = 0;
    char cAuswahl;

    printf("\n\t\tAuswahl Zeile: ");
    scanf(" %c", &cAuswahl);
    fflush(stdin);

    if (cAuswahl == '1') {
        iReturnCode = 1;
    } else if(cAuswahl == '2') {
        iReturnCode = 2;
    } else if(cAuswahl == '3') {
        iReturnCode = 3;
    } else if(cAuswahl == '4') {
        iReturnCode = 4;
    } else if(cAuswahl == '5') {
        iReturnCode = 5;
    } else if(cAuswahl == '6') {
        iReturnCode = 6;
    } else if(cAuswahl == '7') {
        iReturnCode = 7;
    } else if(cAuswahl == '8') {
        iReturnCode = 8;
    } else if(cAuswahl == '9') {
        iReturnCode = 9;
    } else {
        iReturnCode = 0;
    }
    return iReturnCode;
}

/*
============================================================================
Funktion setFieldValue()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: 1 - 9 ==> bei einem korrekt eingegebenen Wert
                    0     ==> Bei einer fehlerhaften Eingabe
============================================================================
*/
int setValue(void){
    // Variablen
    int iReturnCode = 0;
    char cAuswahl;

    printf("\n\t\tAuswahl Wert: ");
    scanf(" %c", &cAuswahl);
    fflush(stdin);

    if (cAuswahl == '1') {
        iReturnCode = 1;
    } else if(cAuswahl == '2') {
        iReturnCode = 2;
    } else if(cAuswahl == '3') {
        iReturnCode = 3;
    } else if(cAuswahl == '4') {
        iReturnCode = 4;
    } else if(cAuswahl == '5') {
        iReturnCode = 5;
    } else if(cAuswahl == '6') {
        iReturnCode = 6;
    } else if(cAuswahl == '7') {
        iReturnCode = 7;
    } else if(cAuswahl == '8') {
        iReturnCode = 8;
    } else if(cAuswahl == '9') {
        iReturnCode = 9;
    } else {
        iReturnCode = 0;
    }
    return iReturnCode;
}

/*
============================================================================
Funktion setValue()
Beschreibung: -
Uebergabeparameter: int sudoku[SIZE][SIZE]
Rueckgabeparameter: -
============================================================================
*/
void setFieldValue(int sudoku[SIZE][SIZE], int iLevel,
                   int iColumn, int iRow, int iValue, int iHelp) {
    // Variablen
    int iSolved = 0;

    insertField(sudoku, iRow - 1, iColumn - 1, iValue);

    if(iHelp == 0) {
        if (checkIfInsertIsCorrect(sudoku,solvedSudoku,iRow -1,
                                   iColumn -1) == 0) {
            iGamePoints += 50;
        } else {
            if( iGamePoints >= 25) {
                iGamePoints -= 25;
            } else {
                iGamePoints = 0;
            }
        }
    }
    
    iSolved = checkSudoku(sudoku);

    if (iSolved == 1) {
        saveToList(name, iGamePoints, 100, iLevel);
    }
}

/*
============================================================================
Funktion showFinish()
Beschreibung: -
Uebergabeparameter:
Rueckgabeparameter: -
============================================================================
*/
int showFinish(char sName[], int iPoints, int iTime, int iLevel) {
    // Variablen
    char cMenue;

    clear();
    printSudokuLogo();

    printf("\n\t                    Glueckwunsch %s", sName);
    printf("\n\t%c", 201);
    printLines(MENUEWIDTH, 205);
    printf("%c", 187);

    printf("\n\t%c     %-21s %-10i sec.       %-12i %c",186,
           sName,iPoints,iLevel,186);
    printf("\n\t%c                                          "
           "                    %c", 186, 186);

    if(strcmp(sName, "Gast") == 0) {
        printf("\n\t%c Sie koennen leider als Gast keine Punkte speichern!"
               "          %c", 186,186);
    }else {
        printf("\n\t%c Sie koennen nun Ihre Punkte speichern!"
               "                       %c", 186, 186);
        printf("\n\t%c                                       "
               "                       %c", 186, 186);
        printf("\n\t%c 1: Speichern                          "
               "                       %c", 186, 186);
    }
    printf("\n\t%c                                           "
           "                   %c", 186, 186);
    printf("\n\t%c x Zum Menue (Verwirft die Punkte)         "
           "                   %c", 186, 186);

    printf("\n\t%c", 200);
    printLines(MENUEWIDTH, 205);
    printf("%c", 188);

    do {
        printf("\n\tAuswahl: ");
        scanf(" %20s", &cMenue);
        fflush(stdin);
    } while(cMenue != '1' && cMenue != 'X' && cMenue != 'x');
    clear();

    if (cMenue == '1'){
        showFinish(name, iGamePoints, iTime, iLevel);
    }
    else if (cMenue == 'X' || cMenue == 'x') {
        return 1;
    }
    return 0;
}

/*
============================================================================
Funktion showRules()
Beschreibung: -
Uebergabeparameter: int sudoku[SIZE][SIZE]
Rueckgabeparameter: -
============================================================================
*/
void showRules(void) {
    // Variablen
    int iExit = 0;

    do{
        clear();
        iExit = printRules();
    }while(iExit != 1);
}

/*
============================================================================
Funktion showRules()
Beschreibung: -
Uebergabeparameter: int sudoku[SIZE][SIZE]
Rueckgabeparameter: -
============================================================================
*/
void solveSudoku(char sName[], int iPoints, int iTime, int iLevel) {
    printSudoku(solvedSudoku);
    printf("\n\t\t    ");
    showFinish(sName, iPoints, iTime, iLevel);
}

/*
============================================================================
Funktion unicorn()
Beschreibung: Ladebildschirm bei Programmstart
Uebergabeparameter: -
Rueckgabeparameter: -
============================================================================
*/
void unicorn() {
    printf("\n\n\n");
    printf("                                                    /\n");
    printf("                                                  .7\n");
    printf("                                       \\       , //\n");
    printf("                                       |\\.--._/|//\n");
    printf("                                      /\\ ) ) ).'/\n");
    printf("                                     /(  \\  // /\n");
    printf("                                    /(   J`((_/ \\\n");
    printf("                                   / ) | _\\     /\n");
    printf("                                  /|)  \\  eJ    L\n");
    printf("                                 |  \\ L \\   L   L\n");
    printf("                                /  \\  J  `. J   L\n");
    printf("                                |  )   L   \\/   \\\n");
    printf("                               /  \\    J   (\\   /\n");
    printf("             _....___         |  \\      \\   \\```\n");
    printf("      ,.._.-'        '''--...-||\\     -. \\   \\\n");
    printf("    .'.=.'                    `         `.\\ [ Y\n");
    printf("   /   /                                  \\]  J\n");
    printf("  Y / Y                                    Y   L\n");
    printf("  | | |          \\                         |   L\n");
    printf("  | | |           Y                        A  J\n");
    printf("  |   I           |                       /I\\ /\n");
    printf("  |    \\          I             \\        ( |]/|\n");
    printf("  J     \\         /._           /        -tI/ |\n");
    printf("   L     )       /   /'-------'J           `'-:.\n");
    printf("   J   .'      ,'  ,' ,     \\   `'-.__          \\\n");
    printf("    \\ T      ,'  ,'   )\\    /|        ';'---7   /\n");
    printf("     \\|    ,'L  Y...-' / _.' /         \\   /   /\n");
    printf("      J   Y  |  J    .'-'   /         ,--.(   /\n");
    printf("       L  |  J   L -'     .'         /  |    /\\\n");
    printf("       |  J.  L  J     .-;.-/       |    \\ .' /\n");
    printf("       J   L`-J   L____,.-'`        |  _.-'   |\n");
    printf("        L  J   L  J                  ``  J    |\n");
    printf("        J   L  |   L                     J    |\n");
    printf("         L  J  L    \\                    L    \\\n");
    printf("         |   L  ) _.'\\                    ) _.'\\\n");
    printf("         L    \\('`    \\                  ('`    \\\n");
    printf("          ) _.'\\`-....'                   `-....'\n");
    printf("         ('`    \\\n");
    printf("          `-.___/\n");
    waitFor(3);
    clear();
}
/*
================================================================================
Funktion printSudokuLogo()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: imainMenue
================================================================================
*/
void printSudokuLogo() {
    printf("\n\t    /$$$$$$  /$$   /$$ /$$$$$$$   /$$$$$$  /$$   /$$ /$$   /$$\n");
    printf("\t   /$$__  $$| $$  | $$| $$__  $$ /$$__  $$| $$  /$$/| $$  | $$\n");
    printf("\t  | $$  \\__/| $$  | $$| $$  \\ $$| $$  \\ $$| $$ /$$/ | $$  | $$\n");
    printf("\t  |  $$$$$$ | $$  | $$| $$  | $$| $$  | $$| $$$$$/  | $$  | $$\n");
    printf("\t   \\____  $$| $$  | $$| $$  | $$| $$  | $$| $$  $$  | $$  | $$\n");
    printf("\t   /$$  \\ $$| $$  | $$| $$  | $$| $$  | $$| $$\\  $$ | $$  | $$\n");
    printf("\t  |  $$$$$$/|  $$$$$$/| $$$$$$$/|  $$$$$$/| $$ \\  $$|  $$$$$$/\n");
    printf("\t   \\______/  \\______/ |_______/  \\______/ |__/  \\__/ \\______/ \n\n");
}
/*
================================================================================
Funktion printLines()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: -
================================================================================
*/
void printLines(int iTimes, int j) {
    for(int i = 0; i < iTimes; ++i){
        printf("%c", j);
    }
}
/*
================================================================================
Funktion resetSudoku()
Beschreibung: Diese Funktion ruft lediglich die resetCurrentSudoku-Funktion aus
              der Datei sudoku.c auf und setzt die aktuelllen erspielten Punkte
              auf 0.
Uebergabeparameter: int sudoku[SIZE][SIZE] - Das aktuelle Sudoku,
                    auf dem gespielt wird
Rueckgabeparameter: -
================================================================================
*/
void resetSudoku(int sudoku[SIZE][SIZE]) {
    resetCurrentSudoku(sudoku,savedSudoku);
    iGamePoints = 0;
}
