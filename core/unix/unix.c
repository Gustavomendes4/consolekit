
#include <stdio.h>
#include "../../consolekit.h"

void initTerminal(){

    #ifdef BOOKMARK_H_INCLUDED
    initBookMark();
    #endif

    return;
}

void clearScreen(){
    printf("\033[2J\033[H");
}

void clearLine(){
    printf("\033[2K");
}

void clearToEnd(){
    printf("\033[0K");
}

void clearToStart(){
    printf("\033[1K");
}

