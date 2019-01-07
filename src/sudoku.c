/*
============================================================================
Autor : Lars Kahlert & Dominik Kuhbach
Klasse : FA13
Projekt: Sudoku
Dateiname : sudoku.c
Datum : 01.06.2017
Beschreibung:
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
Funktion generateSudoku()
Beschreibung:   In dieser Funktion wird durch Aufrufen von initSudoku(),
                randomSingleSwap() und fillSudoku() das fertig gelöste
                Sudoku generiert.

Uebergabeparameter: int sudoku[SIZE][SIZE]
                    unsigned int iLevel

Rueckgabeparameter: -
============================================================================
*/
void generateSudoku(int sudoku[SIZE][SIZE],unsigned int iLevel) {
    initSudoku(solvedSudoku);

    randomSingleSwap(solvedSudoku,1);
    randomSingleSwap(solvedSudoku,0);
    fillSudoku(sudoku,solvedSudoku,iLevel);
}

/*
============================================================================
Funktion initSudoku()
Beschreibung:   Diese Funktion generiert ein 9x9 Feld.
                In jeder Spalte und Reihe kommen die Zahlen 1-9 nur jeweils
                einmal vor.
                Bei der randomSingleSwap()-Funktion werden die Spalten
                und Reihen zufällig vertauscht
                (siehe randomSingleSwap() in sudoku.c).

Uebergabeparameter: int sudoku[SIZE][SIZE]
Rueckgabeparameter: -
============================================================================
*/
void initSudoku(int sudoku[SIZE][SIZE]) {
    int i,j;
    int k,n = 1;

    for(i = 0;i < SIZE;i++){
        k = n;
        for (j = 0; j < SIZE; j++) {
            if(k<=SIZE){
                sudoku[i][j]=k;
                k++;
            }else{
                /* K auf 1 setzen um den Algorithmus erneut zu starten*/
                k=1;
                sudoku[i][j]=k;
                k++;
            }
            /* Da durch wird k beim nächsten durchlaufen der äußeren Schleife
             * um 3 erhöht, heißt also anstatt 1 beginnt man mit 4 usw.
             */
            n=k+3;
            /* Wenn k eine ungütlige Zahl ist startet die nächste Zeile mit 4 */
            if(k>SIZE) {
                n = 4;
            }
            if(n>SIZE) {
                n=(n%SIZE)+1;
            }
        }
    }
}
/*
============================================================================
Funktion randomSingleSwap()
Beschreibung:   Hier werden jeweils 3 Spalten (swapSingleCol()-Funktion)
                und 3 Reihen (swapSingleRow()-Funktion)
                aus dem schon gelösten Sudoku (solvedSudoku[][]) zufällig
                verteilt.

Uebergabeparameter: int sudoku[SIZE][SIZE]
                    unsigned int iCheck
Rueckgabeparameter: -
============================================================================
*/
void randomSingleSwap(int sudoku[SIZE][SIZE],unsigned int iCheck) {
    int iK1,iK2,i;
    int iMax=2,iMin=0;

    srand((unsigned int) time(NULL));

    for(i=0;i<3;i++) {
        iK1=(rand()%(iMax-iMin+1))+iMin;
        do{
            iK2=(rand()%(iMax-iMin+1))+iMin;
        } while(iK1==iK2);
        iMax+=3;iMin+=3;

        if(iCheck==1) {
            swapSingleRow(sudoku,iK1, iK2);
        }
        else if(iCheck==0) {
            swapSingleCol(sudoku,iK1,iK2);
        }
    }
}
/*
============================================================================
Funktion swapSingleRow()
Beschreibung: -
Uebergabeparameter: int sudoku[SIZE][SIZE]
                    int iK1
                    int iK2
Rueckgabeparameter: -
============================================================================
*/
void swapSingleRow(int sudoku[SIZE][SIZE],int iK1,int iK2){
    int iTmp,i;
    for(i=0;i<SIZE;i++)
    {
        iTmp=sudoku[iK1][i];
        sudoku[iK1][i]=sudoku[iK2][i];
        sudoku[iK2][i]=iTmp;
    }
}
/*
============================================================================
Funktion swapSingleCol()
Beschreibung: -
Uebergabeparameter: int sudoku[SIZE][SIZE]
                    int iK1
                    int iK2
Rueckgabeparameter: -
============================================================================
*/
void swapSingleCol(int sudoku[SIZE][SIZE],int iK1,int iK2){
    int iTmp,i;

    for(i=0;i<SIZE;i++)
    {
        iTmp=sudoku[i][iK1];
        sudoku[i][iK1]=sudoku[i][iK2];
        sudoku[i][iK2]=iTmp;
    }
}

/*
============================================================================
Funktion fillSudoku()
Beschreibung:   In dieser Funktion werden zufällig Felder (je nach
                Schwierigkeitsgrad 'level') aus dem fertig gelösten Sudoku
                (solvedSudoku[][]) in das zu lösende Sudoku (sudoku[][])
                kopiert. Das Array savedSudoku[][] dient später zum Abgleichen,
                ob Zahlen die der Benutzer einfügen möchte schon vorgesetzte
                sind (siehe insertField[][]-Funktion in sudoku.c).

                Zuerst wird sudoku[][] und savedSudoku[][] in einer
                for-Schleife mit Nullen initialisiert. Die Variable diff
                beinhaltet die Anzahl der Zahlen, die später je nach
                Schwierigkeit angezeigt werden.
                Je höher die Schwierigkeit, desto geringer ist der Wert von
                diff (d.h. weniger Zahlen werden angezeigt)

                Es werden Zufallszahlen zwischen 1 und 9 generiert und aus dem
                vorgefertigtem Sudoku (solvedSudoku[][]) in das zu lösende
                Sudoku kopiert (sudoku[][]). Dieser Vorgang wird je nach Wert
                von diff wiederholt. Nach dem generieren wird das zu lösende
                Sudoku mit der checkFields-Funktion überprüft,
                ob auch die gewünschte Anzahl an Feldern enthalten sind
                (siehe checkFields-Funktion).

Uebergabeparameter: int sudoku[SIZE][SIZE],
                    unsigned int iLevel
Rueckgabeparameter: -
============================================================================
*/
void fillSudoku(int sudoku[SIZE][SIZE],
                int solvedSudoku[SIZE][SIZE],
                unsigned int iLevel) {

    srand((unsigned int) time(NULL));
    unsigned int iRand_column, iRand_row;
    unsigned int iDiff = 0;
    int i, j, iResult;

    do {
        /* Array mit 0 initialisieren */
        for(i=0;i<SIZE;i++) {
            for(j=0;j<SIZE;j++) {
                sudoku[i][j] = 0;
                savedSudoku[i][j] = 0;
            }
        }

        switch (iLevel) {
            /* einfach */
            case 1:
                iDiff = 40;
                break;
            /* mittel */
            case 2:
                iDiff = 35;
                break;
            /* schwer */
            case 3:
                iDiff = 25;
                break;
        }

        do {
            do {
                iRand_column = (rand() % 9);
            } while (iRand_column < 0);

            do {
                iRand_row = (rand() % 9);
            } while (iRand_row < 0);

            sudoku[iRand_row][iRand_column]
                    = solvedSudoku[iRand_row][iRand_column];
            savedSudoku[iRand_row][iRand_column]
                    = solvedSudoku[iRand_row][iRand_column];

            iDiff--;
        } while (iDiff > 0);

        iResult = checkFields(sudoku, iLevel);
    } while(iResult != 1);
}

/*
============================================================================
Funktion checkFields()
Beschreibung:   In dieser Funktion werden die leeren Felder des in
                fillSudoku[][] erstellten Sudokus gezaehlt und überprüft,
                ob dessen Anzahl mit der anzuzeigenden Anzahl an leeren Felder
                (Variable ges) (je nach gesetzter Schwierigkeit) überstimmt.
                Falls nicht, wird 0 zurückgegeben und der Vorgang in
                fillSudok() wird erneut ausgeführt. Je höher die Schwierigkeit,
                desto weniger leere Felder sind vorhanden.
              
Uebergabeparameter: int sudoku[SIZE][SIZE],
                    unsigned int iLevel

Rueckgabeparameter: 1: Anzahl stimmt überein
                    0: Anzahl stimmt nicht überein
============================================================================
*/
int checkFields(int sudoku[SIZE][SIZE], int iLevel) {
    unsigned int iDiff = 0;
    int iCount = 0;
    int x, y;

    switch (iLevel) {
        /* einfach */
        case 1:
            iDiff = 40;
            break;
        /* mittel */
        case 2:
            iDiff = 35;
            break;
        /* schwer */
        case 3:
            iDiff = 25;
            break;
    }

    /* Anzahl der leeren Felder: */
    int iGes = 81-iDiff;

    /* Prüfe wo leere Felder sind, und zaehle diese mit count: */
    for (x = 0; x < SIZE; x++) {
        for (y = 0; y < SIZE; y++) {
            if (sudoku[x][y] == 0) {
                iCount++;
            }
        }
    }

    if(iCount == iGes) {
        return 1;
    } else {
        return 0;
    }
}

/*
============================================================================
Funktion insertField()
Beschreibung: In dieser Funktion wird das aktuelle Sudoku hineingereicht und
              überprüft ob das zu setzende Feld ein schon bereits
              vordefiniertes Feld ist.
              Falls die angegebene Zeile und Spalte bereits in
              savedSudoku[][] enthalten ist (= vordefiniertes Feld ),
              wird 0 zurückgegeben.
              Falls das Feld keines der vorgefertigen war,
              wird eingegebene Zahl eingefügt.

Uebergabeparameter: int sudoku[SIZE][SIZE],
                    int iRow,
                    int iColumn,
                    int iNumber,
                    
Rueckgabeparameter: 0 = Fehler
                    1 = Erfolgreich
============================================================================
*/
int insertField(int sudoku[SIZE][SIZE], int iRow, int iColumn, int iNumber) {

    if(savedSudoku[iRow][iColumn] != 0) {
        return 0;
    } else {
        sudoku[iRow][iColumn] = iNumber;
        return 1;
    }
}

/*
============================================================================
Funktion getField()
Beschreibung:   Hier wird ein Feld aus dem gelösten Sudoku (solvedSudoku[][])
                in das zu lösende Sudoku (sudoku[][]) kopiert.

Uebergabeparameter: int sudoku[SIZE][SIZE],
                    int iRow,
                    int iColumn,

Rueckgabeparameter: -
============================================================================
*/
int getField(int iRow, int iColumn) {

    return solvedSudoku[iRow][iColumn];
}

/*
============================================================================
Funktion void timer(int option)
Beschreibung:   In dieser Funktion wird je nach hineingereichten
                Integer-Parameter ein Timer gestartet (bei Parameter 1),
                pausiert (Parameter 2) oder gestoppt (Parameter 3).
                Die Variable dDiff berechnet die Differenz durch die Funktion
                difftime() von start und stop.
                Die Gesamtzeit wird in die globale Variable dOverallTime
                gespeichert.

Uebergabeparameter: unsigned iOption
                        Möglichen Parameter für iOption:
                        (1) = Start
                        (2) = Pause
                        (3) = Stop

Rueckgabeparameter: -
============================================================================
*/

void timer(int option) {

    switch(option) {
        /* Start */
        case 1:
            t_start = time(NULL);
            break;
        /* Pause */
        case 2:
            t_pause = time(NULL);
            t_diff += difftime(t_pause, t_start);
            break;
        /* Stop */
        case 3:
            t_stop = time(NULL);
            t_diff += difftime(t_stop, t_start);
            break;
    }

    // printf("Gesamte Differenz in Sekunden:\t%f", diff);

    /*
     * int timer(void) {
	double dMinuten;
	double dSekunden;
	if(iReset == 0){
    	tnow = 0;
    	t = clock() - t - tnow;
	}
	else{
    	t = clock() - tnow;
	}
	time_taken = t / CLOCKS_PER_SEC;
	iZeit = time_taken;
	//Rechnet wieviele Stunden

	dTimerStunden = time_taken / 3600;
	iStunden = dTimerStunden;

	//Rechnet wieviele Minuten

	dTimerMinuten = (dTimerStunden - iStunden);
	dMinuten = 60 * dTimerMinuten;
	iMinuten = dMinuten;
	//Rechnet wieviele Sekunden

	dTimerSekunden = (dMinuten- iMinuten);
	dSekunden = 60 * dTimerSekunden;
	iSekunden = dSekunden;
}
     */
}

/*
============================================================================
Funktion checkSudoku()
Beschreibung:   Diese Funktion zählt die Anzahl an leeren Feldern in einem Array
                (sudoku[][]). Falls keine leeren Felder enthalten sind,
                wird 1 zurückgegeben.

Uebergabeparameter: int sudoku[SIZE][SIZE],

Rueckgabeparameter: -1 = Leere Felder sind enthalten
                     1 = Keine leeren Felder enthalten
============================================================================
*/
int checkSudoku(int sudoku[SIZE][SIZE]) {
    int i,j;
    int iCounter = 0;

    for(i=0;i<SIZE;i++) {
        for(j=0;j<SIZE;j++) {
            if (sudoku[i][j] == 0) {
                iCounter++;
            }
        }
    }

    if(iCounter == 0) {
        return 1;
    } else {
        return -1;
    }
}

/*
============================================================================
Funktion checkIfInsertIsCorrect()
Beschreibung:   Diese Funktion überprüft, ob das eingegebene Feld richtig ist.
                Dafür für das Feld von sudoku[][] und solvedSudoku[][]
                verglichen.
                Falls diese identisch sind, wird 0 zurückgegeben.

Uebergabeparameter: int sudoku[SIZE][SIZE],
                    int solved Sudoku[SIZE][SIZE]

Rueckgabeparameter: 0: Felder sind identisch
                    1: Felder sind nicht identisch
============================================================================
*/
int checkIfInsertIsCorrect(int sudoku[SIZE][SIZE],
                           int solvedSudoku[SIZE][SIZE],
                           int iRow,
                           int iColumn) {
    if(sudoku[iRow][iColumn] == solvedSudoku[iRow][iColumn]) {
        return 0;
    } else {
        return 1;
    }

}

/*
============================================================================
Funktion resetCurrentSudoku()
Beschreibung:   Diese Funktion setzt die eingegebenen Felder des Sudokus
                auf den Wert 0 zurück.

Uebergabeparameter: int sudoku[SIZE][SIZE],
                    int savedSudoku[SIZE][SIZE]

Rueckgabeparameter: -
============================================================================
*/
void resetCurrentSudoku(int sudoku[SIZE][SIZE], int savedSudoku[SIZE][SIZE]) {


    int iRow, iColumn;

    for(iRow = 0;iRow < SIZE; iRow++) {
        for(iColumn = 0;iColumn < SIZE; iColumn++) {
            sudoku[iRow][iColumn] = savedSudoku[iRow][iColumn];
        }
    }
}