# --punto e.1.
```bash
gcc -Wall -std=c17 -pedantic-errors main.c tabla.c conversion.c -o programa
```

# --punto e.2.
```bash
PS C:\Users\tomas\Downloads\UTN\Sintaxis\tp1-grupo3> gcc -Wall -std=c17 -pedantic-errors main.c tabla.c conversion.c -o programa
```
tabla.c: In function 'armarTabla':
tabla.c:17:22: error: implicit declaration of function 'convertirANudosAKmh' [-Wimplicit-function-declaration]
   17 |         double kmh = convertirANudosAKmh(i);


Analisis: El compilador no pudo encontrar la definicion de la funcion llamada en tabla.c "convertirANudosAKmh". Esto se debe a que al no incluir el archivo de tabla.h, el cual tenia la definicion de la funcion, no encuentra la declaracion de la funcion.

# --punto e.3.
```bash
PS C:\Users\tomas\Downloads\UTN\Sintaxis\tp1-grupo3> gcc -Wall -std=c17 -pedantic-errors main.c conversion.c -o programa  
```
C:/msys64/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\tomas\AppData\Local\Temp\cc0hobAh.o:main.c:(.text+0xe8): undefined reference to `armarTabla'
collect2.exe: error: ld returned 1 exit status


Analisis: En este caso, al no incluir el archivo "tabla.c" en nuestro comando de compilación, el compilador no encuentra la referencia a la función ´armarTabla' y por ende no puede compilar el programa; retornando "collect2.exe: error: ld returned 1 exit status". Esta salida refiere a que hubo un problema en la fase de enlace de compilación (en nuestro caso se debió a que existía una función sin definir).

# --punto e.4.
gcc -E conversion.c -o conversion.i