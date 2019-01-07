/*
============================================================================
Autoren : Lars Kahlert & Julia Olbrich
Klasse : FA13
Projekt: Sudoku
Dateiname : databaseUI.c
Datum : 31.05.2017
Beschreibung: DatabaseUI stellt alle Menüs im Zusammenhang mit der Datenbank
              dar, so z.B. die Anzeige des Bestenlisten-Menüs, des Logins und
              der Registrierung
Version : 1.2
Änderung : Bugfixes
Programmschnittstelle: sudoku.h
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
================================================================================
Funktion printLevelChooser
Beschreibung: Diese Funktion gibt ein Menü zur Auswahl des Schwierigkeitsgrades
              für die Bestenliste aus. Nach der Ausgabe des Sudoku-Logos und der
              Umrandung des Auswahlmenüs, werden die einzelnen Schwierigkeits-
              grade zur Auswahl angezeigt. Die Auswahl wird in die char Variable
              cLevel eingelesen. Die Abfrage lässt nur Eingaben von 1, 2, 3 oder
              x (für die Rückkehr ins Hauptmenü) zu. Nach dem Löschen des Screens
              wird die jeweilige Eingabe in die externe Variable iLevelFilter
              geschrieben und die unten genannten Parameter zurückgegeben.
Uebergabeparameter: -
Rueckgabeparameter: 0 ==> Wenn zum Menü gewechselt werden soll.
                    1 ==> Wenn ein korrektes Level gewählt wurde.
================================================================================
*/
int printLevelChooser() {
    char cLevel;

    printSudokuLogo();

    printf("\n\t%c", 201);
    printLines(MENUEWIDTH, 205);
    printf("%c", 187);
    printf("\n\t%c 1. Leicht                                                   "
           " %c"
           "\n\t%c 2. Normal                                                   "
           " %c"
           "\n\t%c 3. Schwer                                                   "
           " %c"
           "\n\t%c                                                             "
           " %c"
           "\n\t%c                                                             "
           " %c"
           "\n\t%c                                                             "
           " %c"
           "\n\t%c x Zum Menue                                                 "
           " %c"
           ,186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186);
    printf("\n\t%c", 200);
    printLines(MENUEWIDTH, 205);
    printf("%c", 188);
    do {
        printf("\n\tAuswahl: ");
        scanf(" %c", &cLevel);
        fflush(stdin);
    } while(cLevel != '1' && cLevel != '2' && cLevel != '3' && cLevel != 'x');

    clear();
    switch(cLevel) {
        case '1':
            iLevelFilter = 1;
            return 1;
            break;
        case '2':
            iLevelFilter = 2;
            return 1;
        case '3':
            iLevelFilter = 3;
            return 1;
            break;
        default:
            return 0;
            break;
    }
}
/*
================================================================================
Funktion printHighScore
Beschreibung: Zuerst wird die Funktion printLevelChooser() aufgerufen und deren
              Rückgabewert (siehe oben) in der Integer-Variable iLevelFilterIsSet
              gespeichert. Wenn dieser Wert nicht 0 ist (dann würde ins Haupt-
              menü zurückgegangen werden), dann wird der Bildschirm gelöscht,
              das Sudoku-Logo ausgegeben, sowie der Titel mit dem jeweiligen
              angezeigten Schwierigkeitsgrad (der in der zuvor aufgerufenen
              Funktion in iLevelFilter geschrieben wurde). Anschließend wird
              gefragt, ob nach Punkten oder Zeit sortiert werden soll und die
              Eingabe im Integer iSort gespeichert. Je nachdem wird die gewünsch-
              te Sortierung angezeigt und die Funktion getList aufgerufen und
              ihr die Parameter zur Sortierung (iSort) und des Levels (iLevel-
              Filter) übergeben. Nach der Ausgabe gibt es noch die Möglichkeit,
              die Bestenliste nach einem anderen Schwierigkeitsgrad oder einer
              anderen Sortierung auszuwählen oder ins Hauptmenü zurückzukehren.
              Dieses Schleife läuft solange die Auswahl 's' für Sortieren ist.
              Ist die Auswahl 'x', wird das Menü verlassen.
Uebergabeparameter: -
Rueckgabeparameter: 0 ==> Wenn das Menü nicht verlassen werden soll
                    1 ==> Wenn das Menü verlassen werden soll
================================================================================
*/
int printHighScore(){
    // Variablen
    char cAuswahl;
    int iSort = 0,iLevelFilterIsSet = 0, iCorrect = 0;

    iLevelFilterIsSet = printLevelChooser();

    if(iLevelFilterIsSet != 0) {
        do {
            clear();
            printSudokuLogo();

            printf("\n\t\t\t%c", 201);
            printLines(26, 205);
            printf("%c", 187);

            printf("\n\t\t\t%c  B E S T E N L I S T E   %c"
                   "\n\t\t\t%c ", 186, 186, 186);
            if(iLevelFilter == 1) {
                printf("      L E I C H T        %c", 186);
            } else if(iLevelFilter == 2) {
                printf("      M I T T E L        %c", 186);
            } else if(iLevelFilter == 3) {
                printf("      S C H W E R        %c", 186);
            }

            printf("\n\t\t\t%c", 200);
            printLines(26, 205);
            printf("%c", 188);

            do {
                printf("\n\n\t Sortieren nach Zeit (1) oder Punkten (2):");
                scanf(" %d", &iSort);
                fflush(stdin);
            } while(iSort != 1 && iSort != 2);

            //Interne Testzwecke:
            // printf("\n\tiSort: %d; iLevel: %d\n",iSort,iLevelFilter);

            if(iSort == 1) {
                printf("\n\t\t\t\t      Zeit");
            } else{
                printf("\n\t\t\t\t     Punkte");
            }

            printf("\n\t%c", 201);
            printLines(MENUEWIDTH, 205);
            printf("%c", 187);

            printf("\n\t%c Rang %c Name                  %c Zeit(sec.)     %c"
                   " Punkte       %c", 186, 186, 186, 186, 186);

            printf("\n\t%c", 204);
            printLines(MENUEWIDTH, 205);
            printf("%c", 185);

            getList(iSort,iLevelFilter);

            printf("\n\t%c", 200);
            printLines(MENUEWIDTH, 205);
            printf("%c", 188);

            printf("\n\n\tAnderes Level(L)?");
            printf("\n\tNeu Sortieren(S)?");
            printf("\n\tBeenden(X)?");

            do{
                printf("\n\tAuswahl: ");
                scanf(" %c", &cAuswahl);
                fflush(stdin);
                if(cAuswahl != 'S' && cAuswahl != 's' &&
                   cAuswahl != 'L' && cAuswahl != 'l' &&
                   cAuswahl != 'X' && cAuswahl != 'x') {
                    printf("\n\tUngueltige Eingabe!");
                    iCorrect = 0;
                } else {
                    iCorrect = 1;
                }
            } while(iCorrect == 0);

        } while (cAuswahl == 'S' || cAuswahl == 's');

        if (cAuswahl == 'X' || cAuswahl == 'x'){
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 1;
    }
}
/*
============================================================================
Funktion signInUI
Beschreibung: Nach der Ausgabe des Sudoku-Logos und der Eingabeaufforderung für
              den Benutzername, wird die folgende Eingabe in dem Char-Array
              sUsername gespeichert. Das Gleiche passiert mit dem Passwort.
              Dann wird die Funktion signIn() mit den beiden Eingaben als
              Parametern aufgerufen und deren Rückgabewert in dem Integer
              iStatus gespeichert. Wenn der Wert 1 oder oder -1 ist, wird die
              jeweilige Fehlermeldung ausgegeben und iStatus auf 1 für Fehler
              gesetzt. Dies wird dann dementsprechend zurückgegeben.
Uebergabeparameter: -
Rueckgabeparameter: 0 -> Passwort OK
                    1 -> Passwort Falsch bzw Fehler
============================================================================
*/
char* signInUI() {
    // Variablen
    char sUsername[20];
    char sPassword[40];
    int iStatus;

    printSudokuLogo();

    printf("\n\t\t\t%c", 201);
    printLines(26, 205);
    printf("%c", 187);

    printf("\n\t\t\t%c    E I N L O G G E N     %c", 186, 186);

    printf("\n\t\t\t%c", 200);
    printLines(26, 205);
    printf("%c", 188);

    printf("\n\t%c", 201);
    printLines(MENUEWIDTH, 205);
    printf("%c", 187);

    printf("\n\t%c Bitte geben Sie Ihren Benutzernamen ein:"
           "                     %c\n\t%c ", 186, 186, 186);

    scanf(" %s", sUsername);

    printf("\t%c                                           "
           "                   %c", 186, 186);
    printf("\n\t%c Bitte geben Sie Ihr Passwort ein:"
           "                            %c\n\t%c ", 186, 186, 186);

    scanf(" %s", sPassword);

    printf("\t%c                                           "
                   "                   %c", 186, 186);

    iStatus = signIn(sUsername, sPassword);
    //printf("\t%i\n",iStatus);
    if(iStatus == 1) {
        printf("\n\t%c Benutzer oder Passwort sind nicht korrekt."
               "                   %c", 186, 186);
    } else if(iStatus == -1) {
        printf("\n\t%c Es konnte keine Verbindung zur Datenbank"
               " aufgebaut werden     %c", 186, 186);
        iStatus = 1;
    } else {
        printf("\n\t%c                    Willkommen %s",186, name, 186);
    }

    printf("\n\t%c", 200);
    printLines(MENUEWIDTH, 205);
    printf("%c", 188);

    waitFor(5);
    return iStatus  ? (char *) iStatus : "1";
}
/*
============================================================================
Funktion signUpUI
Beschreibung: Nach der Ausgabe des Sudoku-Logos und der Titels wird man zur
              Eingabe des Vornamens, des Nachnamens sowie eines Benutzernamens
              aufgefordert. Diese Eingaben werden jeweils in den Char-Arrays
              sFirstName, sLastName und sUsername gespeichert.
              Anschließend wird 2 Mal das Passwort abgefragt und in zwei unter-
              schiedlichen Char-Arrays gespeichert, damit diese danach mit einem
              string compare verglichen werde können und das Ergebnis dessen in
              den Integer iCheckPassword gespeichert. Stimmen sie nicht überein,
              wird eine Fehlermeldung ausgegeben. Die eingegebenen Daten, inso-
              fern diese richtig sind, fungieren als Übergabeparameter für die
              Funktion signUp() und deren Rückgabeparameter in der Char Variable
              cCheck gespeichert. Ist der Inhalt dieser Variable 1, wird eine
              Fehlermeldung ausgegeben und dies zurückgegeben.
Uebergabeparameter: -
Rueckgabeparameter: 0 -> Passwort OK
                    1 -> Passwort Falsch
============================================================================
*/
char* signUpUI(){
    // Variablen
    char sUsername[20];
    char sFirstName[20];
    char sLastName[20];
    char sPassword[40];
    char sCheckPassword[40];
    char* cCheck;
    int iCheckPassword,i;

    printSudokuLogo();

    printf("\n\t\t\t%c", 201);
    printLines(27, 205);
    printf("%c", 187);

    printf("\n\t\t\t%c  R E G I S T R I E R E N  %c", 186, 186);

    printf("\n\t\t\t%c", 200);
    printLines(27, 205);
    printf("%c", 188);

    printf("\n\t%c", 201);
    printLines(MENUEWIDTH, 205);
    printf("%c", 187);

    printf("\n\t%c Bitte geben Sie Ihren Vornamen ein (20 Zeichen):"
           "             %c\n\t%c ", 186, 186, 186);
    scanf(" %s", sFirstName);

    printf("\t%c                                                     "
           "         %c", 186, 186);
    printf("\n\t%c Bitte geben Sie Ihren Nachnamen ein (20 Zeichen):"
           "            %c\n\t%c ", 186, 186, 186);
    scanf(" %s", sLastName);

    printf("\t%c                                                     "
                   "         %c", 186, 186);
    printf("\n\t%c Bitte geben Sie Ihren Benutzernamen ein (20 Zeichen):"
           "        %c\n\t%c ", 186, 186, 186);
    scanf(" %s", sUsername);

    printf("\t%c                                                     "
                   "         %c", 186, 186);
    printf("\n\t%c Bitte geben Sie ein Passwort ein:"
           "                            %c\n\t%c ", 186, 186, 186);
    scanf(" %s", sPassword);

    printf("\t%c                                                     "
                   "         %c", 186, 186);
    printf("\n\t%c Bitte geben Sie das Passwort erneut ein:"
           "                     %c\n\t%c ", 186, 186, 186);
    scanf(" %s", sCheckPassword);

    printf("\t%c                                                     "
                   "         %c", 186, 186);

    iCheckPassword = strcmp(sPassword, sCheckPassword);
    if(iCheckPassword != 0){
        printf("\n\t%c Die Passwoerter stimmen nicht ueberein!                 "
               "     %c", 186, 186);
    } else {
        cCheck = signUp(sUsername,sFirstName,sLastName, sPassword);
        //printf("%s", cCheck);
        if(strcmp(cCheck, "1") == 0){
            printf("\n\t%c Es ist in ein Fehler aufgetreten. Sie kommen nun"
                   " zurueck ins %c\n\t%c Hauptmenue.                      "
                   "                            %c", 186, 186, 186, 186);
            cCheck = NULL;
        }
    }

    //interne Testzwecke
    //printf("\tTest: %s\n",cCheck);
    printf("\n\t%c", 200);
    printLines(MENUEWIDTH, 205);
    printf("%c", 188);

    waitFor(5);
    return cCheck ? cCheck : NULL;
}