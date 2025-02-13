#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdbool.h>

// Definiciones de constantes
#define MAX_VARIABLES 100
#define MAX_LONGITUD_NOMBRE 50

// Declaración de variables globales
extern char *tabla[MAX_VARIABLES];
extern int numVariables;

// Declaración de funciones
bool buscar(char  *id, char *ts[]); 
void colocar(char *id, char *ts[]);
bool definir(char *id);
bool verificar(char *id);

#endif // SYMBOL_H