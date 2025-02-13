#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tabla.h"
#include "conversion.h"

int main(int argc, char *argv[])
{
    // Verifica que se haya pasado al menos un argumento
    if (argc < 3 || argc > 4)
    {
        printf("Error en la cantidad de argumentos enviados\n");
        printf("Uso: %s <valorInicialNudos> <valorFinalNudos> [incrementoNudos]\n", argv[0]);
        return 1;
    }

    // Obtener los valores para construiir la tabla.
    int valorInicialNudos = atoi(argv[1]);
    int valorFinalNudos = atoi(argv[2]);
    int incrementoNudos = 1;
    if (argc == 4)
    {
        incrementoNudos = atoi(argv[3]);
    }

    // Verificar que los argumentos sean números válidos
    if (valorInicialNudos == 0 || valorFinalNudos == 0 || (argc == 4 && incrementoNudos == 0))
    {
        printf("Error: Los argumentos deben ser números válidos\n");
        return 1;
    }

    printf("Valores recibidos: Inicial = %d, Final = %d, Incremento = %d\n", valorInicialNudos, valorFinalNudos, incrementoNudos);
    
    armarTabla(valorInicialNudos, valorFinalNudos, incrementoNudos);

    return 0;
}
