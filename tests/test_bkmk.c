
#include <stdio.h>
#include <stdlib.h>

#include "../consolekit.h"
#include "../bookmark.h"

int main(int argc, char* argv[]){

    createCursorBookmark("Nome", 5, 5);
    createCursorBookmark("email", 5, 10);
    createCursorBookmark("fone", 5, 15);

    gotoCursorBookmark("Nome");
    moveLeft(6);
    printf("Nome: ");

    gotoCursorBookmark("email");
    moveLeft(6);
    printf("Mail: ");

    gotoCursorBookmark("fone");
    moveLeft(6);
    printf("Fone: ");

    
    gotoxy(0, 0);
    int f;
    scanf("%d", &f);

    gotoCursorBookmark("Nome");
    printf("Gustavo Mendes");
    gotoCursorBookmark("email");
    printf("gustavomendes@gmail.com");
    gotoCursorBookmark("fone");
    printf("51-997852770");


}
