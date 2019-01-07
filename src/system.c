/*
============================================================================
Autor : Lars Kahlert, Dominik Kuhbach, Julia Olbrich, Sebastian Weise
Klasse : FA13
Projekt: Sudoku
Dateiname : system.c
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
Funktion clear()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: -
============================================================================
*/
void clear(){
    if(!strcmp(OS, "WINDOWS")) {
        system("cls");
    } else {
        system("clear");
    }
}

/*
============================================================================
Funktion pause()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: -
============================================================================
*/
void pause(){
    if(!strcmp(OS, "WINDOWS")) {
        system("pause");
    } else {
        system("read -r -p \"Druecken Sie eine beliebige Taste . . .\"");
    }

}

/*
============================================================================
Funktion waitFor()
Beschreibung: Funktion um einen Delay zu erzeugen.
Uebergabeparameter: secs - Die Zeit, die das Programm warten soll in Sekunden
Rueckgabeparameter: -
============================================================================
*/
void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;
    while (time(0) < retTime);
}

/*
============================================================================
Funktion fullscreen()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: -
============================================================================
*/

void fullscreen() {
    if(!strcmp(OS, "WINDOWS")) {
        keybd_event(VK_MENU, 0x38, 0, 0);
        keybd_event(VK_RETURN, 0x1c, 0, 0);
        keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
        keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(handle, &info);
        COORD new_size =
                {
                        info.srWindow.Right - info.srWindow.Left + 1,
                        info.srWindow.Bottom - info.srWindow.Top + 1
                };
        SetConsoleScreenBufferSize(handle, new_size);
    }
}
