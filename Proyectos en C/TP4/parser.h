// parser.h

#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"

// Prototipos de funciones del parser
void parser();           // Función principal del parser
void programa();         // Regla para programa
void sentencia();        // Regla para sentencia
void expresion();        // Regla para expresión
void termino();          // Regla para término
void factor();           // Regla para factor
void lista_sentencias(); // Regla para lista de sentencias
void declaracion();
void asignacion();
void lectura();
void escritura();
void error_sintactico();
void ErrorSintactico(TOKEN tok);

void primaria();
void operador_aditivo();
void lista_identificadores();
void lista_expresiones();

#endif // PARSER_H
