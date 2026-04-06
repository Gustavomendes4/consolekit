
/*
    Implementação de um interface para manipulação do terminal, manipulando:
        - Cor de texto;
        - Cor de fundo;
        - Cursor;
        - ...

    O projeto eh desenvolvido para compilar em windows, usando a interface
    <windows.h> para windows e ANSI para Linux. 


    Disponível em: .

    Gustavo dos Santos Mendes, 05/04/2026.
*/

#include "./consolekit.h"

#ifdef _WIN32

#include "./core/winConsoleKit.c"

#else

#include "./core/unixConsoleKit.c"

#endif