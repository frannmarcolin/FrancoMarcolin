#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

// Definición de los contadores globales para los lexemas
int countIdentificadores = 0;
int countConstantes = 0;
int countAsignaciones = 0;
int countOperadoresMas = 0;
int countOperadoresMenos = 0;
int countOperadoresMultiplicacion = 0;
int countOperadoresDivision = 0;
int countOperadoresModulo = 0;
int countParentesisAbre = 0;
int countParentesisCierra = 0;
int countComas = 0;
int countPuntosYComas = 0;
int countErroresGenerales = 0;
int countErroresAsignaciones = 0;

int main(void)
{
    TOKEN token;

    do
    {
        token = scanner();

        switch (token)
        {
        case IDENTIFICADOR:
            countIdentificadores++;
            break;
        case CONSTANTE_ENTERA:
            countConstantes++;
            break;
        case OPERADOR_ASIGNACION:
            countAsignaciones++;
            break;
        case OPERADOR_SUMA:
            countOperadoresMas++;
            break;
        case OPERADOR_RESTA:
            countOperadoresMenos++;
            break;
        case OPERADOR_MULTIPLICACION:
            countOperadoresMultiplicacion++;
            break;
        case OPERADOR_DIVISION:
            countOperadoresDivision++;
            break;
        case OPERADOR_MODULO:
            countOperadoresModulo++;
            break;
        case PARENTESIS_ABRE:
            countParentesisAbre++;
            break;
        case PARENTESIS_CIERRA:
            countParentesisCierra++;
            break;
        case COMA:
            countComas++;
            break;
        case PUNTO_Y_COMA:
            countPuntosYComas++;
            break;
        case ERROR_GENERAL:
            countErroresGenerales++;
            break;
        case ERROR_ASIGNACION_PUNTO:
            countErroresAsignaciones++;
            break;
        case ERROR_ASIGNACION_IGUAL:
            countErroresAsignaciones++;
            break;
        default:
            break;
        }
    } while (token != FDT);

    printf("\nTotal:\n");
    printf("Identificadores: %d\n", countIdentificadores);
    printf("Constantes enteras: %d\n", countConstantes);
    printf("Asignaciones: %d\n", countAsignaciones);
    printf("Operadores de suma: %d\n", countOperadoresMas);
    printf("Operadores de resta: %d\n", countOperadoresMenos);
    printf("Operadores de multiplicación: %d\n", countOperadoresMultiplicacion);
    printf("Operadores de división: %d\n", countOperadoresDivision);
    printf("Operadores de módulo: %d\n", countOperadoresModulo);
    printf("Paréntesis de apertura: %d\n", countParentesisAbre);
    printf("Paréntesis de cierre: %d\n", countParentesisCierra);
    printf("Comas: %d\n", countComas);
    printf("Puntos y comas: %d\n", countPuntosYComas);
    printf("Errores generales: %d\n", countErroresGenerales);
    printf("Errores de asignación: %d\n", countErroresAsignaciones);

    return 0;
}