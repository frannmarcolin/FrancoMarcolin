#include <stdio.h>
#include "parser.h"

extern int yynerrs;
extern int yylexerrs;
extern int errores_semanticos; // Declarar errores_semanticos como externo
int yylexerrs = 0;

int main(void)
{
	switch (yyparse())
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	}
	if (yynerrs != 0 || yylexerrs != 0 || errores_semanticos != 0)
	{
		printf("\nErrores sintácticos: %d - Errores léxicos: %d - Errores Semánticos: %d", yynerrs, yylexerrs, errores_semanticos);
		return 1;
	}

	return 0;
}