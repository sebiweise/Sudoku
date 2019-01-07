cmake_minimum_required(VERSION 3.6)
project(Sudoku)

set(CMAKE_C_STANDARD 99)


AUX_SOURCE_DIRECTORY(src/ SOURCE_FILES)

add_executable(Sudoku ${SOURCE_FILES} src/gameUI.c header/sudoku.h src/databaseUI.c src/rulesUI.c src/encrypt.c)

# Nur hinzufügen, wenn das Programm unter einem Linux-System
# ausgeführt werden soll

# target_link_libraries(Sudoku m dl pthread)
