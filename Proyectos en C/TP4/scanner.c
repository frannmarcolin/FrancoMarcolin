#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "parser.h"

bool deboEscanear = true;
static TOKEN tokenActual;
int posicion = 0;
char *textoCompleto;

const char *palabrasReservadas[] = {"programa", "fin", "entero", "leer", "escribir", "asignacion"};

int tablaDeTransicion[5][15] = {
    {1, 2, 3, 202, 43, 45, 42, 47, 37, 40, 41, 44, 59, 103, 4},                  // Transiciones desde el estado 0
    {1, 1, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100},     // Transiciones desde el estado 1
    {101, 2, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101},   // Transiciones desde el estado 2
    {201, 201, 201, 102, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201}, // Transiciones desde el estado 3
    {200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 4}};  // Transiciones desde el estado 4

void setToken(TOKEN token)
{
    tokenActual = token;
}

bool esCentinela(char caracter)
{
    return (caracter != ' ' || caracter != '\n' || caracter != '\t');
}

bool deboParar(int estado)
{
    return (estado != 0 && estado != 1 && estado != 2 && estado != 3 && estado != 4);
}

int tipoDeCaracter(char caracter)
{
    if ((caracter >= 'A' && caracter <= 'Z') || (caracter >= 'a' && caracter <= 'z'))
        return 0; // Letra
    if (caracter >= '0' && caracter <= '9')
        return 1; // Dígito
    switch (caracter)
    {
    case ':':
        return 2;
    case '=':
        return 3;
    case '+':
        return 4;
    case '-':
        return 5;
    case '*':
        return 6;
    case '/':
        return 7;
    case '%':
        return 8;
    case '(':
        return 9;
    case ')':
        return 10;
    case ',':
        return 11;
    case ';':
        return 12;
    case '\0':
        return 13; // Final de cadena (EOF)
    default:
        return 14; // Error general
    }
}

char cadenaTemporal[512];

char getCadenaTemporal(int i)
{
    if (cadenaTemporal[i] != '\0')
    {
        return cadenaTemporal[i];
    }
    else
    {
        return '~';
    }
}

bool necesitaCargarTexto = true;
TOKEN scanner()
{
    if (necesitaCargarTexto)
    {
        recibirTexto();
    }
    necesitaCargarTexto = false;

    char carac;
    // Recorre toda la cadena.
    while (1)
    {
        int i = 0;      // Índice para la cadena temporal.
        int tipo;       // Variable para almacenar el tipo de carácter.
        int estado = 0; // Inicia en el estado 0 (estado inicial).

        // Procesa caracteres hasta que el estado sea distinto de los estados del 0 al 4.
        while (!deboParar(estado))
        {
            carac = textoCompleto[posicion];          // Obtiene el carácter actual.
            tipo = tipoDeCaracter(carac);             // Determina el tipo del carácter.
            estado = tablaDeTransicion[estado][tipo]; // Cambia de estado según la tabla de transición.
            cadenaTemporal[i] = carac;                // Almacena el carácter en la cadena temporal.

            i++;
            posicion++;
        }
        cadenaTemporal[i - 1] = '\0'; // Termina la cadena con el carácter nulo.

        if (esCentinela(carac))
        {               // Si el carácter actual es un centinela, ajustar la posición.
            posicion--; // Retrocede una posición para reanalizar el centinela.
        }

        // Manejo de tokens y errores según el estado final alcanzado.
        switch (estado)
        {
        case 100: // Identificador reconocido.

            // printf("Identificador: '%s'\n", cadenaTemporal); //! BORRAR AL FINALIZAR EL TP
            return IDENTIFICADOR;

        case 101: // Constante reconocida.
            // printf("Constante: '%s'\n", cadenaTemporal);
            return CONSTANTE_ENTERA;

        case 102: // Asignacion reconocida.
            // printf("Asignacion: ':='\n");
            posicion++;
            return OPERADOR_ASIGNACION;

        case 43: // Operador "mas" reconocido.
            // printf("Mas: '+'\n");
            posicion++;
            return OPERADOR_SUMA;

        case 45: // Operador "menos" reconocido.
            // printf("Menos: '-'\n");
            posicion++;
            return OPERADOR_RESTA;

        case 42: // Operador "multiplicación" reconocido.
            // printf("Multiplicacion: '*'\n");
            posicion++;
            return OPERADOR_MULTIPLICACION;

        case 47: // Operador "división" reconocido.
            // printf("Division: '/'\n");
            posicion++;
            return OPERADOR_DIVISION;

        case 37: // Operador "modulo" reconocido.
            // printf("Modulo: '%%'\n");
            posicion++;
            return OPERADOR_MODULO;

        case 40: // Paréntesis que abre.
            // printf("Parentesis que abre: '('\n");
            posicion++;
            return PARENTESIS_ABRE;

        case 41: // Paréntesis que cierra.
            // printf("Parentesis que cierra: ')'\n");
            posicion++;
            return PARENTESIS_CIERRA;

        case 44: // Coma reconocida.
            // printf("Coma: ','\n");
            posicion++;
            return COMA;

        case 59: // Punto y coma reconocido.
            // printf("Punto y coma: ';'\n");
            posicion++;
            return PUNTO_Y_COMA;

        case 103:       // FDT reconocido.
            return FDT; // Fin de archivo.

        case 200: // Error general.
            if (noHayNadaEntreEspacios(cadenaTemporal))
            { // Si el error es por un espacio o enter, no se imprime nada.
                break;
            }
            eliminarEspacios(cadenaTemporal);
            // printf("Error general: '%s'\n", cadenaTemporal);
            return ERROR_GENERAL;

        case 201: // Error por ":" sin "=".
            // printf("Error en asignacion por : solo ':'.\n");
            posicion++;
            return ERROR_ASIGNACION;

        case 202: // Error por "=" sin ":".
            // printf("Error en asignacion por = solo '='\n");
            posicion++;
            return ERROR_ASIGNACION;

        default:
            printf("Token desconocido.\n");
        }
    }
}

// Toma todo el texto insertado en la consola
void recibirTexto()
{

    // Reserva de 1024 bytes para almacenar la entrada completa desde la consola.
    int posicion = 0;
    textoCompleto = calloc(1024, sizeof(char));
    if (textoCompleto == NULL)
    {
        perror("Error al asignar memoria");
        return;
    }
    // Posición actual en el buffer de texto.
    char carac; // Variable para almacenar el carácter leído actualmente.

    // Lee caracteres del archivo hasta el final.
    while ((carac = getchar()) != EOF)
    {
        if (posicion < 1023)
        {                                      // Check para no sobrepasar el buffer
            textoCompleto[posicion++] = carac; // Almacena cada carácter y avanza la posición.
        }
    }

    // Agregar el carácter nulo al final de la cadena
    textoCompleto[posicion] = '\0';
}

void eliminarEspacios(char *cadena)
{
    int i, j = 0;
    int longitud = strlen(cadena);

    for (i = 0; i < longitud; i++)
    {
        if (!isspace((unsigned char)cadena[i]))
        {
            cadena[j++] = cadena[i];
        }
    }
    cadena[j] = '\0'; // Añadir el carácter nulo al final
}

bool noHayNadaEntreEspacios(char *cadena)
{
    while (*cadena)
    {
        if (*cadena != ' ' && *cadena != '\n' && *cadena != '\t')
        {
            return false;
        }
        cadena++;
    }
    return true;
}

// Función para verificar que el token actual coincida con el esperado
void match(TOKEN esperado)
{
    if (esperado != proxToken())
        error_sintactico(proxToken());
    // printf("(Match) Error de sintaxis: No se esperaba el token %d\n", );
    deboEscanear = true;
}

// Lee el siguiente caracter del texto de entrada
TOKEN proxToken()
{
    if (deboEscanear)
    {
        tokenActual = scanner();
        while (tokenActual == ERROR_GENERAL || tokenActual == ERROR_ASIGNACION)
        {
            if (tokenActual == ERROR_ASIGNACION)
            {
                if (strcmp(cadenaTemporal, ":") == 0)
                {
                    printf("Error en asignacion por : solo ':'\n");
                }
                else
                {
                    printf("Error en asignacion por = solo '='\n");
                }
            }
            if (tokenActual == ERROR_GENERAL)
            {
                printf("Error general: '%s'\n", cadenaTemporal);
            }
            tokenActual = scanner();
        }
        deboEscanear = false;

        if (tokenActual == IDENTIFICADOR)
        {
            buscarPalabraReservada();
        }
    }
    return tokenActual;
}

void buscarPalabraReservada()
{
    // Comparar el lexema con cada palabra reservada del lenguaje
    if (strcmp(cadenaTemporal, "programa") == 0)
    {
        tokenActual = PROGRAMA;
    }
    else if (strcmp(cadenaTemporal, "leer") == 0)
    {
        tokenActual = LEER;
    }
    else if (strcmp(cadenaTemporal, "escribir") == 0)
    {
        tokenActual = ESCRIBIR;
    }
    else if (strcmp(cadenaTemporal, "entero") == 0)
    {
        tokenActual = ENTERO;
    }
    else if (strcmp(cadenaTemporal, "fin") == 0)
    {
        tokenActual = FIN;
    }
}