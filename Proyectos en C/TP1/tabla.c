#include "tabla.h"
#include "conversion.h"


// Construye la tabla e imprime los valores.
void armarTabla(int inicio, int fin, int incremento) {
    assert(inicio >= 0 && fin >= inicio && incremento > 0);

    printf("Tabla de conversión de nudos a kilómetros por hora:\n");
    printf("Inicio: %d nudos\n", inicio);
    printf("Fin: %d nudos\n", fin);
    printf("Incremento (filas): %d nudos\n", incremento);
    printf("\nNudos\tKilometros por hora\n");
    printf("------------------------------\n");

    for (int i = inicio; i <= fin; i += incremento) {
        double kmh = convertirANudosAKmh(i);
        printf("%d\t%.2f\n", i, kmh);
    }

}