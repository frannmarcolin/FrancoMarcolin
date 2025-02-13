#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

TOKEN tokenActual;
char traduccion[40];

// Función principal del parser
void parser()
{
    programa();
    match(FDT);
}

// Regla para "programa"
void programa()
{
    char lexema[512];
    int i = 0;
    match(PROGRAMA);

    match(IDENTIFICADOR);
    while (lexema[i - 1] != '~')
    {
        lexema[i] = getCadenaTemporal(i);
        i++;
    }
    lexema[i - 1] = '\0';

    printf("Programa: %s\n", lexema);

    // entra a lista_setencias siendo tokenActual = ENTERO
    lista_sentencias();

    match(FIN);
    printf("fin\n");
}

void lista_sentencias()
{
    sentencia();
    while (1)
    {
        switch (proxToken())
        {
        case IDENTIFICADOR:
        case LEER:
        case ESCRIBIR:
        case ENTERO:
            sentencia();
            break;
        default:
            return;
        }
    }
}

void sentencia()
{
    TOKEN tok = proxToken();
    // printf("entro en sentencia como %d\n", tok);
    switch (tok)
    {
    case IDENTIFICADOR:
        match(IDENTIFICADOR);
        match(OPERADOR_ASIGNACION);
        expresion();
        match(PUNTO_Y_COMA);
        printf("Sentencia asignacion\n");
        break;
    case ENTERO:
        match(ENTERO);
        match(IDENTIFICADOR);
        match(PUNTO_Y_COMA);
        printf("Sentencia declaracion\n");
        break;
    case LEER:
        match(LEER);
        printf("Sentencia leer\n");
        match(PARENTESIS_ABRE);
        lista_identificadores();
        match(PARENTESIS_CIERRA);
        match(PUNTO_Y_COMA);

        break;
    case ESCRIBIR:
        match(ESCRIBIR);
        match(PARENTESIS_ABRE);
        lista_expresiones();
        match(PARENTESIS_CIERRA);
        match(PUNTO_Y_COMA);
        printf("Sentencia escribir\n");
        break;
    default:
        printf("(Switch de sentencia) Error de sintaxis: nuestro token es: %d\n", tokenActual);
        break;
    }
}

void lista_expresiones()
{
    expresion();
    while (proxToken() == COMA)
    {
        match(COMA);
        expresion();
    }
}

void primaria()
{
    TOKEN tok = proxToken();
    switch (tok)
    {
    case IDENTIFICADOR:
        match(IDENTIFICADOR);
        break;
    case CONSTANTE_ENTERA:
        match(CONSTANTE_ENTERA);
        break;
    case PARENTESIS_ABRE:
        match(PARENTESIS_ABRE);
        expresion();
        match(PARENTESIS_CIERRA);
        break;
    case OPERADOR_RESTA:
        match(OPERADOR_RESTA);
        match(IDENTIFICADOR);
        break;
    default:
        error_sintactico(tok);
        break;
    }
}

void lista_identificadores()
{
    match(IDENTIFICADOR);
    do
    {
        match(COMA);
        match(IDENTIFICADOR);
    } while (proxToken() == COMA);
}

void expresion()
{
    TOKEN t;
    primaria();
    for (t = proxToken(); t == OPERADOR_SUMA || t == OPERADOR_RESTA || t == OPERADOR_MULTIPLICACION || t == OPERADOR_DIVISION || t == OPERADOR_MODULO; t = proxToken())
    {
        operador_aditivo();
        primaria();
    }
}

void operador_aditivo()
{
    TOKEN t = proxToken();
    switch (t)
    {
    case OPERADOR_SUMA:
        match(OPERADOR_SUMA);
        break;
    case OPERADOR_RESTA:
        match(OPERADOR_RESTA);
        break;
    case OPERADOR_DIVISION:
        match(OPERADOR_DIVISION);
        break;
    case OPERADOR_MODULO:
        match(OPERADOR_MODULO);
        break;
    case OPERADOR_MULTIPLICACION:
        match(OPERADOR_MULTIPLICACION);
        break;
    default:
        error_sintactico(t);
        break;
    }
}

void error_sintactico(TOKEN tok)
{
    traduccionTokenString(tok);
    printf("Error sintactico no se esperaba el token '%s'\n", traduccion);
}

void traduccionTokenString(TOKEN tokenActual)
{
    switch (tokenActual)
    {

    case 0:
        strcpy(traduccion, "IDENTIFICADOR");
        break;

    case 1:

        strcpy(traduccion, "CONSTANTE_ENTERA");
        break;

    case 2:
        strcpy(traduccion, "OPERADOR_ASIGNACION");
        break;

    case 3:
        strcpy(traduccion, "OPERADOR_SUMA");
        break;

    case 4:
        strcpy(traduccion, "OPERADOR_RESTA");
        break;

    case 5:
        strcpy(traduccion, "OPERADOR_MULTIPLICACION");
        break;

    case 6:
        strcpy(traduccion, "OPERADOR_DIVISION");
        break;

    case 7:
        strcpy(traduccion, "OPERADOR_MODULO");
        break;

    case 8:
        strcpy(traduccion, "PARENTESIS_ABRE");
        break;

    case 9:
        strcpy(traduccion, "PARENTESIS_CIERRA");
        break;

    case 10:
        strcpy(traduccion, "COMA");
        break;

    case 11:
        strcpy(traduccion, "PUNTO_Y_COMA");
        break;

    case 12:
        strcpy(traduccion, "ERROR_GENERAL");
        break;

    case 13:
        strcpy(traduccion, "ERROR_ASIGNACION");
        break;

    case 14:
        strcpy(traduccion, "FDT");
        break;

    case 15:
        strcpy(traduccion, "PROGRAMA");
        break;

    case 26:
        strcpy(traduccion, "FIN");
        break;

    case 37:
        strcpy(traduccion, "ENTERO");
        break;

    case 48:
        strcpy(traduccion, "LEER");
        break;

    case 59:
        strcpy(traduccion, "ESCRIBIR");
        break;

    default:
        break;
    }
}
