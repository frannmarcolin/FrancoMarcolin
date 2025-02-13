%code top {
    #include <stdio.h>
    #include "scanner.h"
}

%code provides {
    void yyerror(const char *);
    extern int yylexerrs;
}

%defines "parser.h"
%output "parser.c"

%define api.value.type {char *}
%define parse.error verbose

%token ENTERO LEER ESCRIBIR PROGRAMA FIN_PROGRAMA ID CTE 
%token ASIGNACION ":="

%left '+' '-'
%left '*' '/' '%'
%precedence NEG

%%

programa: PROGRAMA ID { printf("programa: %s\n", yylval); } lista_sentencias FIN_PROGRAMA 
                { if (yynerrs || yylexerrs) YYABORT; else YYACCEPT; };

lista_sentencias: sentencia 
                | lista_sentencias sentencia
                ;

sentencia:  ENTERO ID ';'  { printf("Sentencia declaración: %s\n", yylval); }
        | ID ASIGNACION expresion ';' { printf("Sentencia asignación\n"); }
        | LEER '(' lista_identificadores ')' ';' { printf("Sentencia leer\n"); }
        | ESCRIBIR '(' lista_expresiones ')' ';' { printf("Sentencia escribir\n"); }
        | error ';'
        ;

lista_expresiones:  expresion
                | lista_expresiones ',' expresion
                ;

expresion: termino 
        | expresion '+' termino { printf("suma\n"); }
        | expresion '-' termino { printf("resta\n"); }
        ;

termino: primaria
        | termino '*' primaria { printf("multiplicación\n"); }
        | termino '/' primaria { printf("división\n"); }
        | termino '%' primaria { printf("módulo\n"); }
        ;

primaria: '(' { printf("abre paréntesis\n"); } expresion ')' { printf("cierra paréntesis\n"); }
        | ID
        | CTE
        | '-' primaria %prec NEG { printf("inversión\n"); }
        ;

lista_identificadores:    lista_identificadores ',' ID 
                        | ID
                        ;

%%

void yyerror(const char *msg) {
    printf("línea #%d: %s\n", yylineno, msg);
    return;
}
