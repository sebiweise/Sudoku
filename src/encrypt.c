/*
============================================================================
Autor : Sebastian Weise
Klasse : FA13
Projekt: Sudoku
Dateiname : encrypt.c
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
Funktion encrypt()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: -
============================================================================
*/
void encrypt(char str[],int key)
{
    unsigned int i;
    for(i=0;i<strlen(str);++i)
    {
        str[i] = str[i] - key;
    }
}

/*
============================================================================
Funktion decrypt()
Beschreibung: -
Uebergabeparameter: -
Rueckgabeparameter: -
============================================================================
*/
void decrypt(char str[],int key)
{
    unsigned int i;
    for(i=0;i<strlen(str);++i)
    {
        str[i] = str[i] + key;
    }
}

