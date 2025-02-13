#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdio.h>
#include "symbol.h"

void comenzar(void);
void terminar();

void asignar(char *vizq, char *vder);

void leer_id(char *id);
void escribir_exp(char *exp);

char *gen_infijo(char *pizq, char op, char *pder);
char *invertir(char *id);
bool es_entero(const char *str);
#endif // SEMANTIC_H