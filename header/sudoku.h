/*
============================================================================
Autor : Lars Kahlert, Julia Olbrich, Dominik Kuhbach, Sebastian Weise
Klasse : FA13
Projekt: Sudoku
Dateiname : system.h
Datum : xx.xx.2017
Beschreibung: -
Version : 1.0
Änderung : -
Programmschnittstelle: -
Compiler: GCC 6.3
IDE: CLion 2017.1
============================================================================
*/
#ifndef VAR
#define VAR
/*
============================================================================
Includierungen
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <malloc.h>
/*
============================================================================
Präprozessoranweisungen
============================================================================
*/

#ifdef __linux
#define OS "LINUX"
#elif _WIN32
#define OS "WINDOWS"
#include <windows.h>
#else
#define OS "MAC"
#endif

#define DATABASE_FILE "../sudoku.sqlite3"
#define SIZE 9
#define MENUEWIDTH 62
/*
============================================================================
Funktionsprototyping
============================================================================
*/
//Database
char* signUp(char*, char*, char*, char*);
int signIn(char*, char* );
int getList(int, int );
int saveToList(char*, int, int, int);

//DatabaseUI
int printLevelChooser(void);
int printHighScore(void);
char* signInUI(void);
char* signUpUI(void);

//Rules
int printRules();

//GameUI
void gameUI(int);
int startSudoku(int sudoku[SIZE][SIZE], int iLevel);
void printSudoku(int sudoku[SIZE][SIZE]);
void unicorn(void);
void printSudokuLogo(void);
void printLines(int, int);

//MainMenue
int mainMenue(void);
int StartGameMenue(void);
void printMainMenue(void);
void printStartGame(void);

//Timer
void timer(int option);

//Sudoku
void generateSudoku(int sudoku[SIZE][SIZE],unsigned int iLevel);
void initSudoku(int sudoku[SIZE][SIZE]);
void randomSingleSwap(int sudoku[SIZE][SIZE],unsigned int iCheck);
void swapSingleRow(int sudoku[SIZE][SIZE],int iK1,int iK2);
void swapSingleCol(int sudoku[SIZE][SIZE],int iK1,int iK2);
void fillSudoku(int sudoku[SIZE][SIZE],
                int solvedSudoku[SIZE][SIZE],
                unsigned int iLevel);
int getField(int, int);
void resetCurrentSudoku(int sudoku[SIZE][SIZE], int savedSudoku[SIZE][SIZE]);
int checkFields(int sudoku[SIZE][SIZE], int iLevel);
int insertField(int sudoku[SIZE][SIZE], int iRow, int iColumn, int iNumber);
int checkSudoku(int sudoku[SIZE][SIZE]);
int checkIfInsertIsCorrect(int sudoku[SIZE][SIZE],int solvedSudoku[SIZE][SIZE],
                           int, int);


//System
void clear(void);
void pause(void);
void waitFor (unsigned int);
void fullscreen();

//Encrypt
void encrypt(char str[],int key);
void decrypt(char str[],int key);

/*
============================================================================
Externe Variablen
============================================================================
*/
//System
int iConsoleWidth;
int iConsoleHeight;
int iPosition;

//Sudoku
int solvedSudoku[SIZE][SIZE];
int savedSudoku[SIZE][SIZE];
unsigned int iGamePoints;

//Database
char name[20];

// DatabaseUI
int iLevelFilter;

//Timer
static double t_diff = 0.0;
time_t t_start, t_pause, t_stop, t;
#endif