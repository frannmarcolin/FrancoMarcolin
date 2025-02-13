#include "conversion.h"

// Conversión de nudos a kilómetros por hora
double convertirANudosAKmh(int nudos)
{
    double unidadNudo = 1.852;
    return nudos * unidadNudo; // 1 nudo = 1.852 kilómetros por hora
}