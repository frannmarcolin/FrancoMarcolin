#ifndef SCANNER_H_
#define SCANNER_H_

#include <stdio.h>
#include <stdbool.h>

// Definición de los tokens
typedef enum
{
    IDENTIFICADOR = 100,
    CONSTANTE_ENTERA = 101,
    OPERADOR_ASIGNACION = 102,
    OPERADOR_SUMA = 43,
    OPERADOR_RESTA = 45,
    OPERADOR_MULTIPLICACION = 42,
    OPERADOR_DIVISION = 47,
    OPERADOR_MODULO = 37,
    PARENTESIS_ABRE = 40,
    PARENTESIS_CIERRA = 41,
    COMA = 44,
    PUNTO_Y_COMA = 59,
    ERROR_GENERAL = 200,
    ERROR_ASIGNACION_PUNTO = 201,
    ERROR_ASIGNACION_IGUAL = 202,
    FDT = 103
} TOKEN;

// Definición de los estados de la máquina, filas de la matriz
typedef enum
{
    ESTADO_INICIAL = 0,
    ESTADO_IDENTIFICADOR = 1,
    ESTADO_CONSTANTE = 2,
    ESTADO_ASIGNACION = 3,
    ESTADO_ERROR = 4
} ESTADO;

// Tipos de caracteres válidos , columnas de la matriz
typedef enum
{
    TIPO_LETRA,
    TIPO_DIGITO,
    TIPO_DOS_PUNTOS,
    TIPO_IGUAL,
    TIPO_MAS,
    TIPO_MENOS,
    TIPO_ASTERISCO,
    TIPO_BARRA,
    TIPO_PORCENTAJE,
    TIPO_PARENTESIS_ABRE,
    TIPO_PARENTESIS_CIERRA,
    TIPO_COMA,
    TIPO_PUNTO_Y_COMA,
    TIPO_FIN,
    TIPO_OTRO,
} TIPO_CARACTER;

// Variables globales
extern int tablaDeTransicion[5][15];
extern char identificador[40];
extern int constante;
extern char cadenaError[40];

// Prototipos de funciones
bool deboParar(ESTADO estado);
bool esCentinela(char caracter, ESTADO estado);
bool esAceptor(ESTADO estado);

TIPO_CARACTER tipoDeCaracter(char caracter);

TOKEN scanner(void);
TOKEN accept(ESTADO estado, int i);
TOKEN error(ESTADO estado, int i);

#endif // SCANNER_H_