
#include <stdio.h>
#include <stdlib.h>

#include "../consolekit.h"
#include "../bookmark.h"

int main(int argc, char* argv[]){

    showCursor();
    putchar('.');
    initTerminal();

    moveCursor(10, 1);
    printf("Press any key to continue... %d\n", getCursorY());
    
    home();
}