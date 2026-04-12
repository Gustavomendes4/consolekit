
#include <stdio.h>
#include <stdlib.h>

#include "../consolekit.h"

int main(int argc, char* argv[]){

    initTerminal();

    setTextColor(TERM_WHITE);

    printf("Ola mundo");

    gotoxy(0, 0);
    
    int x = getCursorX();
    int y = getCursorY();

    printf("x: %d | y: %d", x, y);
}
