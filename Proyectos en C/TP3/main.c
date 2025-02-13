#include <stdio.h>
#include "tokens.h"

extern int yylex();

int main()
{
    int token;
    while ((token = yylex()) != 0)
    {
        switch (token)
        {
        case PROGRAMA:
            printf("Token: Programa\n");
            break;
        case FIN:
            printf("Token: Fin\n");
            break;
        case ENTERO:
            printf("Token: Entero\n");
            break;
        case LEER:
            printf("Token: Leer\n");
            break;
        case ESCRIBIR:
            printf("Token: Escribir\n");
            break;
        case ASIGNACION:
            printf("Token: Asignacion\n");
            break;
        default:
            printf("Token desconocido.\n");
        }
    }
    return 0;
}