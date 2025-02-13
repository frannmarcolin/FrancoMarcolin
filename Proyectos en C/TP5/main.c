#include <stdio.h>
#include "parser.h"

extern int yynerrs;
int yylexerrs = 0;

int main(void)
{
	switch (yyparse())
	{
	case 0:
		puts("Compilación terminada con éxito");
		break;
	case 1:
		puts("Errores de compilación");
		break;
	case 2:
		puts("No hay memoria suficiente");
		break;
	}

	printf("Errors sintácticos: %d - Errores léxicos: %d\n", yynerrs, yylexerrs);

	return 0;
}