#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int contadorTemp = 1;

char *generarNuevoTemporal()
{
	char *nuevoTemporal = (char *)malloc(20);
	sprintf(nuevoTemporal, "_Temp%d", contadorTemp++);
	return nuevoTemporal;
}

// Genera el header y la función main del archivo.
void comenzar(void)
{
	printf("#include <stdio.h>\n\n");
	printf("int main(void) {\n");
}

// Escribe el final del archivo.txt
void terminar()
{
	printf("\treturn 0;\n}");
}

// A la cadena vizq le asigna Cadena vder.
void asignar(char *vizq, char *vder)
{
	printf("\t%s = %s;\n", vizq, vder);
}

// Genera un scanf en el stdout con la var recibida.
void leer_id(char *id)
{
	printf("\tscanf(\"%%d\", &%s);\n", id);
}

void escribir_exp(char *exp)
{
	printf("\tprintf(\"%%d\\n\", %s);\n", exp);
}

char *gen_infijo(char *pizq, char op, char *pder)
{
	char *_tempX = generarNuevoTemporal();
	char buffer[1000]; // Buffer temporal para construir la cadena final

	definir(_tempX);

	// Construye la cadena en un buffer independiente
	sprintf(buffer, "\t%s = %s %c %s;\n", _tempX, pizq, op, pder);

	// Muestra la cadena en stdout
	printf("%s", buffer);

	// Devuelve el temporal generado
	return _tempX;
}

// Invierte signo de var
// (a) = (-a)
char *invertir(char *id)
{
	char *_TempX = generarNuevoTemporal();
	char buffer[1000]; // Buffer temporal para construir la cadena final
	definir(_TempX);

	// Construye la cadena en un buffer independiente
	sprintf(buffer, "\t%s = -%s;\n", _TempX, id);

	// Muestra la cadena en stdout
	printf("%s", buffer);

	// Devuelve el temporal generado
	return _TempX;
}

bool es_entero(const char *str)
{
	if (str == NULL || *str == '\0')
	{
		return false; // Cadena nula o vacía no es un entero
	}

	// Permitir un signo negativo opcional al inicio
	if (*str == '-')
	{
		str++;
	}

	// Verificar que todos los caracteres restantes sean dígitos
	while (*str)
	{
		if (!isdigit((unsigned char)*str))
		{
			return false;
		}
		str++;
	}

	return true; // Todos los caracteres son dígitos
}