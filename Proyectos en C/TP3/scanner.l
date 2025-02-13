%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
%}

%%
"programa"        { return PROGRAMA; }
"fin"             { return FIN; }
"entero"          { return ENTERO; }
"leer"            { return LEER; }
"escribir"        { return ESCRIBIR; }
":="              { return ASIGNACION; }

[0-9]+               { printf("Token: Constante	lexema: %s\n", yytext); }
[a-zA-Z][a-zA-Z0-9]* { printf("Token: Identificador	lexema: %s\n", yytext); }

"+"               { printf("Token: '+'\n"); }
"-"               { printf("Token: '-'\n"); }
"*"               { printf("Token: '*'\n"); }
"/"               { printf("Token: '/'\n"); }
"%"               { printf("Token: '%'\n"); }
"("               { printf("Token: '('\n"); }
")"               { printf("Token: ')'\n"); }
","               { printf("Token: ','\n"); }         
";"               { printf("Token: ';'\n"); }

"//".*            { /* Ignorar comentario */ }

"\n"              { /* Ignorar comentario */ }

"\t"              { /* Ignorar comentario */ }

" "               { /* Ignorar comentario */ }

[0-9]+[a-zA-Z_][a-zA-Z0-9]*                     {printf("Error lexico: constante invalida: %s\n", yytext);}

[a-zA-Z][a-zA-Z0-9]*[^\t\n a-zA-Z0-9_;,()]+.+   {printf("Error lexico: identificador invalido: %s\n", yytext);}

[^a-zA-Z0-9 \r\t\n/+*%()-,;]+                   {printf("Error lexico: cadena desconocida: %s\n", yytext);}
%%