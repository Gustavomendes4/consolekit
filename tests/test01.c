
#include <stdio.h>
#include <stdlib.h>

#include "../consolekit.h"

int main(int argc, char* argv[]){

    initTerminal();

    setTextColor(TERM_WHITE);

    printf("Ola mundo");
}
