#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
int posicion = 0;
char *textoCompleto;

int tablaDeTransicion[5][15] = {
    {ESTADO_IDENTIFICADOR,      ESTADO_CONSTANTE,         ESTADO_ASIGNACION,         ERROR_ASIGNACION_IGUAL,    OPERADOR_SUMA,           OPERADOR_RESTA,            OPERADOR_MULTIPLICACION,        OPERADOR_DIVISION,      OPERADOR_MODULO,        PARENTESIS_ABRE,        PARENTESIS_CIERRA,      COMA,                       PUNTO_Y_COMA,             FDT,                     ESTADO_ERROR},
    {ESTADO_IDENTIFICADOR,      ESTADO_IDENTIFICADOR,     IDENTIFICADOR,             IDENTIFICADOR,             IDENTIFICADOR,           IDENTIFICADOR,             IDENTIFICADOR,                  IDENTIFICADOR,          IDENTIFICADOR,          IDENTIFICADOR,          IDENTIFICADOR,          IDENTIFICADOR,              IDENTIFICADOR,            IDENTIFICADOR,           IDENTIFICADOR},
    {CONSTANTE_ENTERA,          ESTADO_CONSTANTE,         CONSTANTE_ENTERA,          CONSTANTE_ENTERA,          CONSTANTE_ENTERA,        CONSTANTE_ENTERA,          CONSTANTE_ENTERA,               CONSTANTE_ENTERA,       CONSTANTE_ENTERA,       CONSTANTE_ENTERA,       CONSTANTE_ENTERA,       CONSTANTE_ENTERA,           CONSTANTE_ENTERA,         CONSTANTE_ENTERA,        CONSTANTE_ENTERA},
    {ERROR_ASIGNACION_PUNTO,    ERROR_ASIGNACION_PUNTO,   ERROR_ASIGNACION_PUNTO,    OPERADOR_ASIGNACION,       ERROR_ASIGNACION_PUNTO,  ERROR_ASIGNACION_PUNTO,    ERROR_ASIGNACION_PUNTO,         ERROR_ASIGNACION_PUNTO, ERROR_ASIGNACION_PUNTO, ERROR_ASIGNACION_PUNTO, ERROR_ASIGNACION_PUNTO, ERROR_ASIGNACION_PUNTO,     ERROR_ASIGNACION_PUNTO,   ERROR_ASIGNACION_PUNTO,  ERROR_ASIGNACION_PUNTO},
    {ERROR_GENERAL,             ERROR_GENERAL,            ERROR_GENERAL,             ERROR_GENERAL,             ERROR_GENERAL,           ERROR_GENERAL,             ERROR_GENERAL,                  ERROR_GENERAL,          ERROR_GENERAL,          ERROR_GENERAL,          ERROR_GENERAL,          ERROR_GENERAL,              ERROR_GENERAL,            ERROR_GENERAL,           ESTADO_ERROR}};

char identificador[40]; 
int constante;
char cadenaError[40];

bool esCentinela(char caracter, ESTADO estado)
{
    switch (estado)
    {
    case IDENTIFICADOR:
        return isspace(caracter) || !isalnum(caracter);
    case CONSTANTE_ENTERA:
        return isspace(caracter) || !isdigit(caracter);
    case OPERADOR_ASIGNACION:
        return isspace(caracter) || caracter != '=';
    case ERROR_GENERAL:
        return isspace(caracter) || isalnum(caracter) || strchr(":=+-*/%(),;", caracter) != NULL || caracter == '\0';
    default:
        return isspace(caracter);
    }
}

bool esAceptor(ESTADO estado)
{
    switch (estado)
    {
    case IDENTIFICADOR:
    case CONSTANTE_ENTERA:
    case OPERADOR_ASIGNACION:
    case OPERADOR_SUMA:
    case OPERADOR_RESTA:
    case OPERADOR_MULTIPLICACION:
    case OPERADOR_DIVISION:
    case OPERADOR_MODULO:
    case PARENTESIS_ABRE:
    case PARENTESIS_CIERRA:
    case COMA:
    case PUNTO_Y_COMA:
    case FDT:
        return true;
    default:
        return false;
    }
}

bool deboParar(ESTADO estado)
{
    return ((estado != ESTADO_INICIAL && estado != ESTADO_IDENTIFICADOR && estado != ESTADO_CONSTANTE && estado != ESTADO_ASIGNACION && estado != ESTADO_ERROR) || estado == FDT);
}

TIPO_CARACTER tipoDeCaracter(char caracter)
{
    if (isalpha(caracter))
        return TIPO_LETRA;
    if (isdigit(caracter))
        return TIPO_DIGITO;
    switch (caracter)
    {
    case ':':
        return TIPO_DOS_PUNTOS;
    case '=':
        return TIPO_IGUAL;
    case '+':
        return TIPO_MAS;
    case '-':
        return TIPO_MENOS;
    case '*':
        return TIPO_ASTERISCO;
    case '/':
        return TIPO_BARRA;
    case '%':
        return TIPO_PORCENTAJE;
    case '(':
        return TIPO_PARENTESIS_ABRE;
    case ')':
        return TIPO_PARENTESIS_CIERRA;
    case ',':
        return TIPO_COMA;
    case ';':
        return TIPO_PUNTO_Y_COMA;
    case '\0':
        return TIPO_FIN;
    case EOF:
        return TIPO_FIN;
    default:
        return TIPO_OTRO;
    }
}

TOKEN scanner()
{
    char carac;
    ESTADO estado = ESTADO_INICIAL;
    int i = 0;

    constante = 0; // Reinicia la constante
    memset(identificador, 0, sizeof(identificador));
    memset(cadenaError, 0, sizeof(cadenaError));

    //Leo los espacios en blanco, y los salteo para mi análisis
    do {
        carac = getchar();
    } while (isspace(carac));

    while (!deboParar(estado))
    {
        TIPO_CARACTER tipo = tipoDeCaracter(carac);

        // Avanzar al siguiente estado
        estado = tablaDeTransicion[estado][tipo];

        //===================== MANEJO LEXEMAS =======================
        switch (estado)
        {
        case ESTADO_IDENTIFICADOR:
            identificador[i] = carac; 
            i++;
            carac = getchar();
            break;

        case ESTADO_CONSTANTE:
            constante = constante * 10 + (carac - '0'); // Construimos la constante
            carac = getchar();
            break;

        case ESTADO_ERROR:
            if(!isspace(carac)){
                cadenaError[i] = carac; 
                i++;
            }
            carac = getchar();
            break;

        case ESTADO_ASIGNACION:
            carac = getchar();
        default:
            break;
        }
        //===========================================================
    }

    //Se repite logica para respetar el pseudocodigo propuesto en clase
    if (esAceptor(estado))
    {
        if (esCentinela(carac, estado))
        {
            ungetc(carac, stdin);
        }

        return accept(estado, i); // Retornar token
    }
    else
    {
        if (esCentinela(carac, estado))
        {
            ungetc(carac, stdin);
        }

        return error(estado, i); // Retornar error
    }
}

TOKEN accept(ESTADO estado, int i)
{
    switch (estado)
    {
    case IDENTIFICADOR:
        identificador[i] = '\0'; // Termina el identificador
        printf("Identificador '%s'\n", identificador);
        return IDENTIFICADOR;
    case CONSTANTE_ENTERA:
        printf("Constante '%d'\n", constante);
        return CONSTANTE_ENTERA;
    case OPERADOR_ASIGNACION:
        printf("Asignación ':='\n");
        return OPERADOR_ASIGNACION;
    case OPERADOR_SUMA:
        printf("Más '+'\n");
        return OPERADOR_SUMA;
    case OPERADOR_RESTA:
        printf("Menos '-'\n");
        return OPERADOR_RESTA;
    case OPERADOR_MULTIPLICACION:
        printf("Multiplicación '*'\n");
        return OPERADOR_MULTIPLICACION;
    case OPERADOR_DIVISION:
        printf("División '/'\n");
        return OPERADOR_DIVISION;
    case OPERADOR_MODULO:
        printf("Módulo '%%'\n");
        return OPERADOR_MODULO;
    case PARENTESIS_ABRE:
        printf("Paréntesis que abre '('\n");
        return PARENTESIS_ABRE;
    case PARENTESIS_CIERRA:
        printf("Paréntesis que cierra: ')'\n");
        return PARENTESIS_CIERRA;
    case COMA:
        printf("Coma ','\n");
        return COMA;
    case PUNTO_Y_COMA:
        printf("Punto y coma ';'\n");
        return PUNTO_Y_COMA;
    case FDT:
        return FDT;
    default:
        printf("Token desconocido.\n");
        return ERROR_GENERAL;
    }
}

TOKEN error(ESTADO estado, int i)
{
    switch (estado)
    {
    case ERROR_GENERAL:
        cadenaError[i] = '\0'; // Termina la cadena de error
        printf("Error general '%s'\n", cadenaError);
        return ERROR_GENERAL;
    case ERROR_ASIGNACION_PUNTO:
        printf("Error en asignación por : solo ':'\n");
        return ERROR_ASIGNACION_PUNTO;
    case ERROR_ASIGNACION_IGUAL:
        printf("Error en asignación por = solo '='\n");
        return ERROR_ASIGNACION_IGUAL;
    default:
        return ERROR_GENERAL;
    }
}

#endif // SCANNER_H_INCLUDED