/*
================================================================================
Autor : Julia Olbrich & Lars Kahlert
Klasse : FA13
Projekt: Sudoku
Dateiname : database.c
Datum : 23.05.2017
Beschreibung: Diese Quelldatei beinhaltet alle Funktionen, welche eine
              Verbindung zur Datenbank benötigen. Genaue erklärung aller
              Funktionen befindet sich in dem Dokumentationsbereich der
              entsprechenden Funktion.
Version : 1.0
Änderung : -
Programmschnittstelle: - "sudoku.h" ==> Headerdatei für alle Quelldateien
                       - "sqlite3.h" ==> SQLite-API
                       - "sudoku.sqlite3" ==> Datenbank mit Benutzern
                                              und Bestenliste
Compiler: GCC 6.3
IDE: CLion 2017.1+
================================================================================
*/

/*
============================================================================
Includierungen
============================================================================
*/
#include "../header/sudoku.h"
#include "../header/sqlite3.h"
/*
================================================================================
Funktion signUp
Beschreibung: Die Funktion wird genutzt um einen neuen Benutzer
              in der Datenbank anzulegen. Dabei wird zuerst eine Verbindung zur
              Datenbank aufgebaut, welche daraufhin geprüft wird.
              Falls keine Verbindung aufgebaut werden konnte,
              wird der Wert -1 zurück gegeben. Falls eine Verbindung aufgebaut
              werden konnte, wird das entsprechende
              SQL-Statement vorbereitet und ausgeführt.
              Anschließend wird der Returncode des ausgeführten
              SQL-Statements geprüft und entsprechend bearbeitet.
              Bei einem korrekt ausgeführten SQL-Statement wird der Spielername
              des regestrierten Benutzers zruück gegeben, bei einem fehlerhaft
              ausgeführten SQL-Statement wird der Wert 1 zurück gegeben.
Uebergabeparameter: char* username ==> Einzigartiger Spielername
                    char* firstName ==> Vorname des Spielers
                    char* lastName ==> Nachname des Spielername
                    char* password ==> Passwort
Rueckgabeparameter: Username des registrierten Spielers ==> Alles ok
                     1 ==> es ist ein SQL-Fehler aufgetreten
                    -1 ==> Keine Verbindung zur Datenbank
================================================================================
*/
char* signUp(char* sUsername, char* sFirstName, char* sLastName, char* sPassword){
    // Variablen
    sqlite3 *db_handle;
    char *cErrMsg;
    char *cSql;
    int iRc;

    encrypt(sPassword,0xFACA);

    iRc = sqlite3_open(DATABASE_FILE, &db_handle);

    if(iRc == SQLITE_OK) {
        /*
         * printf("\tEs konnte eine Verbindung zur "
         *              "Datenbank hergestellt werden\n");
         */
        cSql = sqlite3_mprintf("INSERT INTO user(Username, Password,"
                                      " FirstName, LastName) "
                                      "VALUES (%Q, %Q, %Q, %Q);", sUsername,
                              sPassword, sFirstName, sLastName);
        
        /* SQL Statement ausführen */
        iRc = sqlite3_exec(db_handle, cSql, NULL, NULL, &cErrMsg);
        /* Returncode prüfen */
        if ( iRc!= SQLITE_OK ){
            // printf("\tSQL Fehler: %s\n", cErrMsg);
            sqlite3_free(cErrMsg);
            return (char *) "1";
        } else {
            /*
             * printf("\n\t%c Datensatz erfolgreich erstellt."
             * "                              %c", 186, 186);
             */
        }
        sqlite3_close(db_handle);
        return sUsername;
    } else {
        /*
         * printf("\n\t%c Es konnte keine Verbindung zur "
         *              "Datenbank hergestellt werden  %c", 186, 186);
         */
        return (char *) "-1";
    }
}

/*
================================================================================
Funktion signIn
Beschreibung: Diese Funktion wird genutzt um einen Benutzer einzulogen.
              Dabei wird, genau wie bei der signUp-Funktion zuerst
              eine Verbindung zur Datenbank aufgebaut, welche geprüft wird.
              Je nachdem, ob die Verbindung erfolgreich aufgebaut wurde,
              wird ein SELECT-Statement vorbeiret und ausgeführt.
              Zeile für Zeile werden die Ergebnisse des erfolgreichen
              SQL-Statements durchgangen. Bei jedem Durchlauf der Ergebisse, wird
              zuerst geprüft ob das eingegebene Passwort korrekt ist.
              Im Normalfall sollte diese Funktion nur einmal durchlaufen werden,
              da jeder Benutzername einmalig in der Datenbank hinterlegt wurde.
              Falls das SQL-Statement nicht korrekt ausgeführt wurde,
              der Bentzer nicht vorhanden ist oder das Password inkorrekt ist,
              wird der Wert 1 an die aufrufende Funktion übergeben, bei einem
              erfolgreich eingelogten Benutzer der Wert 0.
Uebergabeparameter: char* name
                    char* password
Rueckgabeparameter:  0 ==> Benutzer erfolgreich eingelogt
                    -1 ==> Keine Verbindung zur Datenbank
                     1 ==> Kein gültiger Datensatz gefunden
                           (Falsches Passwort/Username)
================================================================================
*/
int signIn(char* sUsername, char* sPassword){
    // Variablen
    sqlite3 *db_handle;
    sqlite3_stmt *stmt;
    char *cSql, *cRet;
    int iStatus = 0;
    int iRc;

    encrypt(sPassword,0xFACA);

    iRc = sqlite3_open(DATABASE_FILE, &db_handle);
    if (iRc == SQLITE_OK) {
        cSql = sqlite3_mprintf("SELECT * FROM user WHERE Username = %Q",
                              sUsername);
        iRc = sqlite3_prepare_v2(db_handle, cSql, strlen(cSql), &stmt,NULL);

        if ( iRc!= SQLITE_OK ){
            iStatus = 1;
        } else {
            while( sqlite3_step( stmt ) == SQLITE_ROW ) {
                if(strcmp(sPassword,
                          (const char *) sqlite3_column_text(stmt, 2))) {
                    iStatus = 1;
                } else {
                    cRet = (char *) sqlite3_column_text(stmt, 1);
                    strcpy(name, cRet);
                    iStatus = 0;
                }
            }
        }
        sqlite3_close(db_handle);
    }
    else {
        /*
         * printf("\n\t%c Es konnte keine Verbindung zur "
         *              "Datenbank hergestellt werden  %c", 186, 186);
         */
         iStatus = -1;
    }
    return iStatus;
}

/*
================================================================================
Funktion getList
Beschreibung: Diese Funktion wird genutzt um den Inhalt der Bestenliste gefiltert
              und sortiert auszugeben.
              Dabei wird zu erst eine Verbindung auf die Datenbank aufgebaut,
              welche geprüft wird. Bei einer korrekt aufgebauten Verbindung,
              wird ein SELECT-Statement in abhängigkeit nach welchen Kriterium
              sortiert werden soll vorbereitet. Wenn zum Beispiel der Wert 1
              übergeben wurde, wird zuerst aufsteigend nach der Zeit und dann
              absteigend nach den Punkten sortiert (Absteigend bedeutet in
              dem Fall, dass größere Zahlen über den kleineren Zahlen stehen).
              Dieses vorbereitete SQL-Statement wird ausgeführt und auf seine
              korrekte ausführung getestet. Bei einem korrekt ausgeführten
              Statement wird zeilenweise durch das Ergebniss iteriert und formatiert
              auf dem Std.-Outputstream ausgegeben. Bei jedem durchlauf wird ein
              Counter inkrementiert, welcher den Rang des Eintrages in der
              Bestenliste repräsentiert. Nachdem alle Einträge bearbeitet wurden,
              wird der Wert 0 an die aufrufende Funktion zurück geben. Bei einem
              fehlerhaft ausgeüfhrten SQL-Statement der Wert 1.
Uebergabeparameter: int iSort ==> Nach welchem Filter soritert wird
                    int level ==> Nach welchem Level gefiltert werden soll
Rueckgabeparameter:  0 ==> Alles okay
                     1 ==> SQL-Fehler
                    -1 ==> Keine Verbindung zur Datenbank
================================================================================
*/
int getList(int iSort, int iLevel) {
    // Variablen
    sqlite3 *db_handle;
    sqlite3_stmt *stmt;
    char *cSql;
    int iRc, iStatus, iCount = 0;

    iRc = sqlite3_open(DATABASE_FILE, &db_handle);
    if (iRc == SQLITE_OK) {
        if(iSort == 1) {
            cSql = sqlite3_mprintf("SELECT * FROM highscore WHERE Level = %d"
                                  " ORDER BY SpentTime ASC, Score DESC "
                                  "LIMIT 10", iLevel);
        } else {
            cSql = sqlite3_mprintf("SELECT * FROM highscore WHERE Level = %d"
                                  " ORDER BY Score DESC, SpentTime ASC "
                                  "LIMIT 10", iLevel);
        }
        iRc = sqlite3_prepare_v2(db_handle, cSql, strlen(cSql), &stmt,NULL);

        if ( iRc!= SQLITE_OK ){
            iStatus = 1;
        } else {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                iCount++;

                printf("\n\t%c %-4d %c %-21s %c %-10s sec.%c %-12s %c",
                       186,
                       iCount,
                       186,
                       sqlite3_column_text(stmt, 1),
                       186,
                       sqlite3_column_text(stmt, 4),
                       186,
                       sqlite3_column_text(stmt, 2),
                       186);
            }
            iStatus = 0;
        }
        sqlite3_close(db_handle);
    }
    else {
        /*
         * printf("\tEs konnte keine Verbindung zur
         * Datenbank hergestellt werden\n");
         */
        iStatus = -1;
    }

    return iStatus;
}

/*
================================================================================
Funktion saveToList
Beschreibung: Diese Funktion wird dazu genutzt, um einen neuen Bestenlisten-
              Eintrag zu erstellen. Es wird eine Verbindung zur Datenbank aufebaut,
              auf welche geprüft wird.
              Nur bei einer korrek aufgebauten Verbindung wird ein INSERT-
              Statement mit allen Übergabeparametern der Funktion vorbereitet
              und ausgeführt. Bei erfolgreich ausgeführten INSERT, wird der Wert 0
              zurück gegeben, bei einem fehlerhaft ausgeführten INSERT
              hingegen der Wert -1.
Uebergabeparameter: char* name ==> Name des Spielers
                    int points ==> Erreichte Punkte
                    int time   ==> Spielzeit
                    int level  ==> Gespielter Schwierigkeitsgrad
Rueckgabeparameter: 0  ==> Bestenlisteneintrag erfolgreich gespeichert
                    -1 ==> Keine Verbindung zur Datenbank
                    1  ==> SQL-Fehlert
================================================================================
*/
int saveToList(char* sName, int iPoints, int iTime, int iLevel) {
    // Variablen
    sqlite3 *db_handle;
    char *cErrMsg;
    char *cSql;
    int iRc,iStatus = 0;

    iRc = sqlite3_open(DATABASE_FILE, &db_handle);

    if(iRc == SQLITE_OK) {
        cSql = sqlite3_mprintf("INSERT INTO highscore(Username, Score,"
                                      " Level, SpentTime) "
                                      "VALUES (%Q, %d, %d, %d);", sName,
                              iPoints, iLevel, iTime);
        iRc = sqlite3_exec(db_handle, cSql, NULL, NULL, &cErrMsg);
        if ( iRc!= SQLITE_OK ){
            printf("\tSQL Fehler: %s\n", cErrMsg);
            sqlite3_free(cErrMsg);
            iStatus = 1;
        } else {
            /*
             * printf("\tDatensatz erfolgreich erstellt.\n");
             */
            iStatus = 0;
        }
        sqlite3_close(db_handle);
    } else {
        iStatus =  -1;
    }
    return iStatus;
}