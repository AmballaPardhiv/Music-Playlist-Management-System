#include <stdio.h>
#include "utility.h"
#include <string.h>
#include <stdlib.h>

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #elif defined(_linux) || defined(APPLE_)
        system("clear");
    #endif
}
void pauseScreen(){
    while (getchar() != '\n');
}
#ifdef _WIN32
#include <windows.h>
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
#else
#include <sys/ioctl.h>
#include <unistd.h>
int getConsoleWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}
#endif

void printCentered(const char *text) {
    int consoleWidth = getConsoleWidth();
    int textLength = strlen(text);
    int padding = (consoleWidth - textLength) / 2;

    if (padding < 0) padding = 0;

    for (int i = 0; i < padding; i++) {
        putchar(' ');
    }
    printf("%s\n", text);
}

void printDivider() {
    printCentered(CYAN"=================================================================================================================================================================================================\n"RESET);
}

void printdot() {
    printf(CYAN"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"RESET);
}
