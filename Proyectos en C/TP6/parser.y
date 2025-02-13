%code top {
    #include <stdio.h>
    #include "scanner.h"
    #include "semantic.h"
    #include "symbol.h"
    #include <stdlib.h>
    extern int yylineno; // Declarar yylineno como externo para obtener el número de línea
    int errores_semanticos = 0; // Initialize errores_semanticos
}

%code provides {
    extern int yylexerrs;
}

%code requires {
    void yyerror(const char *msg);
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

programa: PROGRAMA ID {comenzar(); } lista_sentencias FIN_PROGRAMA 
                { 
                    terminar(); 
                    
                };

lista_sentencias: sentencia 
                | lista_sentencias sentencia
                ;

sentencia:  ENTERO ID ';'  { 
                    if(!definir($2)) {
                        errores_semanticos++;
                        char msg[100];
                        sprintf(msg, "Error semántico: identificador %s ya declarado", $2);
                        YYERROR;
                    } 
                }
        | ID ASIGNACION expresion ';' { 
                    if(verificar($1)) {
                        errores_semanticos++;
                        char msg[100];
                        sprintf(msg, "Error semántico: identificador %s NO declarado", $1);
                        YYERROR;
                    } else {
                        asignar($1, $3);
                    }
                }
        | ID ';' { 
                    errores_semanticos++;
                    char msg[100];
                    sprintf(msg, "Error semántico: identificador %s NO declarado", $1);
                    printf("línea #%d: Error semántico: identificador %s NO declarado\n", yylineno, $1);
                    YYERROR;
                }
        | LEER '(' lista_identificadores ')' ';'
        | ESCRIBIR '(' lista_expresiones ')' ';'
        | error ';'
        ;

lista_expresiones:  expresion { escribir_exp($1); }
                | lista_expresiones ',' expresion { 
                    if(verificar($3) && !es_entero($3)){
                        char msg[100];
                        sprintf(msg, "Error semántico: identificador %s NO declarado", $3);
                        printf("línea #%d: Error semántico: identificador %s NO declarado\n", yylineno, $3);
                        errores_semanticos++;
                        YYERROR;
                    } else escribir_exp($3);}
                ;

expresion: expresion '+' expresion { $$ = gen_infijo($1, '+', $3);  }
        | expresion '-' expresion { $$ = gen_infijo($1, '-', $3);  }
        | expresion '*' expresion { $$ = gen_infijo($1, '*', $3);  }
        | expresion '/' expresion { $$ = gen_infijo($1, '/', $3);  }
        | expresion '%' expresion { $$ = gen_infijo($1, '%', $3);  }
        | '-' expresion %prec NEG { $$ = invertir($2);  }
        | '(' expresion ')'       { $$ = $2;}
        | ID                     { $$ = $1; }
        | CTE                    { $$ = $1; }
        ;

lista_identificadores:    lista_identificadores ',' ID { leer_id($3); }
                        | ID { leer_id($1); }
                        ;

%%

void yyerror(const char *msg) {
    printf("línea #%d: %s\n", yylineno, msg);
    return;
}