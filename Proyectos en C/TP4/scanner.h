#ifndef SCANNER_H_
#define SCANNER_H_
#define INICIAL 0 // Estado inicial para la máquina de estados

#include <stdio.h>
#include <stdbool.h>
// Definición de los tokens
typedef enum
{
    IDENTIFICADOR,
    CONSTANTE_ENTERA,
    OPERADOR_ASIGNACION,
    OPERADOR_SUMA,
    OPERADOR_RESTA,
    OPERADOR_MULTIPLICACION,
    OPERADOR_DIVISION,
    OPERADOR_MODULO,
    PARENTESIS_ABRE,
    PARENTESIS_CIERRA,
    COMA,
    PUNTO_Y_COMA,
    ERROR_GENERAL,
    ERROR_ASIGNACION,
    FDT
} TOKEN;

#define PROGRAMA 15
#define FIN 26
#define ENTERO 37
#define LEER 48
#define ESCRIBIR 59

extern char *textoCompleto;
void traduccionTokenString(TOKEN tokenActual);

TOKEN getToken();
// extern TOKEN tokenActual;
void setToken(TOKEN token);

void eliminarEspacios(char *cadena);

bool noHayNadaEntreEspacios(char *cadena);

void recibirTexto();

extern int tablaDeTransicion[5][15];

bool esCentinela(char caracter);

int tipoDeCaracter(char caracter);

bool deboParar(int estado);

bool centinela(char caracter);

TOKEN scanner(void);

void buscarPalabraReservada();

//  ||| Funciones relacionadas con el manejo de tokens |||

// Lee el siguiente token del texto de entrada
TOKEN proxToken();
char getCadenaTemporal(int i);

// Verifica que el token actual sea el esperado
void match(TOKEN esperado);
extern bool deboEscanear;

#endif // SCANNER_H_