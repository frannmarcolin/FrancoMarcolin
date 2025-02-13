#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED

#include "symbol.h"
#include <string.h>
#include <stdio.h>

#define MAX_VARIABLES 100
#define MAX_LONGITUD_NOMBRE 50


// Definición de variables globales
char *tabla[MAX_VARIABLES];
int numVariables = 0;

// Función para buscar una variable en el diccionario
bool buscar(char *id, char *ts[])
{
    for (int i = 0; i < numVariables; i++)
    {
        if (strcmp(ts[i], id) == 0)
        {
            return true; // La variable se encuentra en el diccionario
        }
    }
    return false; // La variable no se encuentra en el diccionario
}

// Función para agregar una nueva variable al diccionario
void colocar(char *id, char *ts[])
{
    if (numVariables < MAX_VARIABLES)
    {
        ts[numVariables] = strdup(id); // Duplicar la cadena id
        numVariables++;
    }
    else
    {
        printf("\tError: Diccionario lleno. No se pueden agregar más variables.\n");
    }
}

// Función para definir (verificar y agregar) una variable
bool definir(char *id)
{ 
    if (!buscar(id, tabla))
    {
        colocar(id, tabla);
        printf("\tint %s;\n", id);
        return true; // La variable se agregó correctamente
    }
    else
    {
        return false; // La variable ya estaba definida
    }
}

// Función para verificar si una variable está en el diccionario. Es True cuando la variable no está en el diccionario
bool verificar(char *id)
{
    return !buscar(id, tabla);
}

#endif