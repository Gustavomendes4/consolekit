
#include <stdio.h>
#include <stdlib.h>

#include "../consolekit.h"
#include "../bookmark.h"

int main(int argc, char* argv[]){

    initTerminal();
    clearScreen();

    setTextColor(TERM_RED);
    
    createCursorBookmark("Nome", 10, 5);
    moveCursor(10, 5);
    printf("Maryana Matins\n");

    moveCursor(0, 5);
    char i;
    i = getche();

    gotoCursorBookmark("Nome");

    printf("Gustavo Mendes\n");

    resetColor();

    printf("you put: %c\n", i);

}