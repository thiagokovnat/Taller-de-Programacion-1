# Taller1-TP0

## Introducción

El siguiente trabajo practico consiste en una serie de pasos, en los cuales se va optimizando y arreglando errores dentro del programa. El proposito de dicho programa es un simple contador de palabras que nos indica cuantas palabras hay en un archivo. El proposito del trabajo practico es familiarizarse con el sistema de entrega SERCOM y el reconocimiento de las buenas practicas de programacion.

## Imagenes

Las imagenes se encuentran en la carpeta screenshots dentro del repositorio.

## Paso 0

### Valgrind

Valgrind es una herramienta que permite detectar errores relacionados a la memoria. Generalmente es usado para detectar accesos indebidos de memoria y perdida de la misma. Valgrind nos brinda herramientas con las cual es mas facil detectar dichos errores. Nos informa si intentamos acceder a memoria no alocada, si intentemos liberar memoria que ya fue liberada, si accedemos a un puntero nulo, entre otros. Ademas, nos puede brindar con la linea en la que este error ocurrio lo que facilita aun mas la deteccion de errores de este tipo. Su opcion mas comun es el Memcheck, el cual es utilizado para los chequeos mencionados anteriormente.

### Sizeof

El sizeof representa el tamaño que ocupa en memoria el tipo de dato que le pasamos por parametro. El sizeof(char) es 1 byte mientras que el sizeof(int) es 4 bytes.
El sizeof de un struct no es la suma de los sizeof de sus componentes. Esto se vio en la primera clase cuando se explico que esta involucrado el padding dentro de los structs para que queden alineados en multiplos de 4 en memoria lo cual facilita su acceso. Teniendo como ejemplo el siguiente struct: struct s{ char c; int* p; }; su sizeof no es 9 (suma de sus sizeof) si no 16, debido al padding interno y externo.

### Canales de Entrada/Salida

Por default, el canal de entrada de los programas es el STDIN, mientras que el default de salida es el STDOUT. Ademas, se cuenta con un canal para errores llamado STDERR. Estos canales se usan para tomar input para el programa, para mostrar contenido del programa (Ej una impresion por pantalla) o bien para dejar constancia de los errores ocurridos durante la ejecucion. Estos canales pueden ser redirigidos utilizando los operadores > < que le indican al shell que queremos tomar otro canal de entrada/salida distinto del stdin o del stdout. Por ejemplo, puedo usar el comando <input.txt comando para que el standard input de comando venga de input.txt. Ademas, se puede conectar el output de un programa con el input de otro, mediante el uso de pipes (Operador |). Por ejemplo, al utilizar el siguiente comando comandoA | comandoB lo que estoy indicando es que la entrada del comandoB va a ser la salida del comandoA, conectando asi ambos canales.

## Paso 1

### Salida por pantalla del codigo

```
escomprimiendo el codigo 'source_unsafe.zip'...
Archive:  source_unsafe.zip
  inflating: source_unsafe/README.md
  inflating: source_unsafe/paso1_main.c
  inflating: source_unsafe/paso1_wordscounter.c
  inflating: source_unsafe/paso1_wordscounter.h
Compilando el codigo...
  CC  paso1_main.o
paso1_main.c: In function ‘main’:
paso1_main.c:22:9: error: unknown type name ‘wordscounter_t’
   22 |         wordscounter_t counter;
      |         ^~~~~~~~~~~~~~
paso1_main.c:23:9: error: implicit declaration of function ‘wordscounter_create’ [-Wimplicit-function-declaration]
   23 |         wordscounter_create(&counter);
      |         ^~~~~~~~~~~~~~~~~~~
paso1_main.c:24:9: error: implicit declaration of function ‘wordscounter_process’ [-Wimplicit-function-declaration]
   24 |         wordscounter_process(&counter, input);
      |         ^~~~~~~~~~~~~~~~~~~~
paso1_main.c:25:24: error: implicit declaration of function ‘wordscounter_get_words’ [-Wimplicit-function-declaration]
   25 |         size_t words = wordscounter_get_words(&counter);
      |                        ^~~~~~~~~~~~~~~~~~~~~~
paso1_main.c:27:9: error: implicit declaration of function ‘wordscounter_destroy’ [-Wimplicit-function-declaration]
   27 |         wordscounter_destroy(&counter);
      |         ^~~~~~~~~~~~~~~~~~~~
make: *** [<builtin>: paso1_main.o] Error 1

real    0m0.036s
user    0m0.021s
sys     0m0.014s
[Error] Fallo la compilacion del codigo en 'source_unsafe.zip'. Codigo de error 2

/task/student//source_unsafe/paso1_wordscounter.c:27:  Missing space before ( in while(  [whitespace/parens] [5]
/task/student//source_unsafe/paso1_wordscounter.c:41:  Mismatching spaces inside () in if  [whitespace/parens] [5]
/task/student//source_unsafe/paso1_wordscounter.c:41:  Should have zero or one spaces inside ( and ) in if  [whitespace/parens] [5]
/task/student//source_unsafe/paso1_wordscounter.c:47:  An else should appear on the same line as the preceding }  [whitespace/newline] [4]
/task/student//source_unsafe/paso1_wordscounter.c:47:  If an else has a brace on one side, it should have it on both  [readability/braces] [5]
/task/student//source_unsafe/paso1_wordscounter.c:48:  Missing space before ( in if(  [whitespace/parens] [5]
/task/student//source_unsafe/paso1_wordscounter.c:53:  Extra space before last semicolon. If this should be an empty statement, use {} instead.  [whitespace/semicolon] [5]
/task/student//source_unsafe/paso1_wordscounter.h:5:  Lines should be <= 80 characters long  [whitespace/line_length] [2]
/task/student//source_unsafe/paso1_main.c:12:  Almost always, snprintf is better than strcpy  [runtime/printf] [4]
/task/student//source_unsafe/paso1_main.c:15:  An else should appear on the same line as the preceding }  [whitespace/newline] [4]
/task/student//source_unsafe/paso1_main.c:15:  If an else has a brace on one side, it should have it on both  [readability/braces] [5]
Done processing /task/student//source_unsafe/paso1_wordscounter.c
Done processing /task/student//source_unsafe/paso1_wordscounter.h
Done processing /task/student//source_unsafe/paso1_main.c
Total errors found: 11
```
## Errores en la generación del ejecutable

Podemos observar que todos los errores en la generación del ejectuable estan marcados de la siguiente manera
```
error: implicit declaration of function ‘wordscounter_create’ [-Wimplicit-function-declaration]
```
Esto es un error de compilacion ya que el compilador no puede encontrar la declaracion de una funcion, en este caso son las funciones declaradas en el archivo paso1_wordcounter.h. El cual contiene las declaraciones de las funciones de wordcounter junto con el struct wordcounter_t. Lo que falto en el paso1_main.c fue hacer el #include "paso1_wordcounter.h" para que las declaraciones de las funciones y structs se copien al comienzo del archivo y asi dichas funciones esten declaradas.

### Errores de estilo
El error **Missing space before( in while** nos esta recomendando que dejemos un espacio luego de una instruccion, sea un if, un while,etc. Esto es recomendado por cuestiones de legibilidad de codigo.

El error **Mismatching spaces inside () in if** nos esta diciendo que estamos poniendo mas espacios de un lado de la expresion que del otro. En este caso se tenia **if (  c == EOF)**. Esto empeora la legibilidad del codigo y es por eso que se nos recomienda cambiarlo.

El error **Should have zero or one spaces inside ( and ) in if** nos esta recomendado que nos limites a, como mucho, un espacio luego de un if. La linea en cuestion es la misma que la del error anterior que tenia doble espacio. Nos lo recomienda por la misma cuestion.

El error **An else should appear on the same line as the preceding** nos esta recomendando que pongamos el else if en la misma linea que cerramos el if anterior. Mejora la legibilidad del codigo.

El error **If an else has a brace on one side, it should have it on both** se refiere a lo mismo que la linea anterior. Nos pide que tengamos los braces a ambos lados del else. Y en el caso de que no haya un brace a un lado, no deberia tenerlo del otro.

El error **Missing space before ( in if(** es el mismo que el primero listado.

El error **Extra space before last semicolon. If this should be an empty statement, use {} instead.** nos recomienda que no tengamos un espacio extra entre el final de nuestro statemente y el ; que marca su final.

El error **Lines should be <= 80 characters long** se refiere a la linea del primer comentario del .h, en general es ideal mantener las lineas con un largo menor a 80, principalmente para mejorar la legibilidad y, en el caso de tener una pantalla de menor tamaño, no tener que estar moviendose para leer la linea completa.

El error **Almost always, snprintf is better than strcpy** es una recomendacion por un tema de seguridad. Como se vio, la funcion strcpy no es segura ya que no controla el tamaño de lo que escribimos. Lo que puede terminar en una vulnerabilidad de nuestro programa que puede ser explotada.

Los dos errores restantes son identicos a los listados anteriormente, son reocmendaciones de legibilidad del codigo.


## Paso 2

### Mejoras en el codigo

La diferencia entre este paso y el anterior es que se arreglaron todos los errores de estilo que nos daba el linter en el paso anterior. Ademas, se incluyo la biblioteca "paso2_wordcounter.h" en el main.c del programa, por lo que ya no hay problemas de declaraciones faltantes de funciones o structs. Un problema muy importante que se arregló fue que no se usó mas la funcion strcpy, la cual es insegura, y en su lugar se uso memcpy definiendo el largo del contenido a copiar.

### Normas de programacion

```

Verificando el codigo...

Done processing /task/student//source_unsafe/paso2_wordscounter.c
Done processing /task/student//source_unsafe/paso2_main.c
Done processing /task/student//source_unsafe/paso2_wordscounter.h

```

### Errores en la generacion del ejecutable


```
Descomprimiendo el codigo 'source_unsafe.zip'...
Archive:  source_unsafe.zip
  inflating: source_unsafe/paso2_main.c
  inflating: source_unsafe/paso2_wordscounter.c
  inflating: source_unsafe/paso2_wordscounter.h
Compilando el codigo...
  CC  paso2_wordscounter.o
In file included from paso2_wordscounter.c:1:
paso2_wordscounter.h:7:5: error: unknown type name ‘size_t’
    7 |     size_t words;
      |     ^~~~~~
paso2_wordscounter.h:20:1: error: unknown type name ‘size_t’
   20 | size_t wordscounter_get_words(wordscounter_t *self);
      | ^~~~~~
paso2_wordscounter.h:1:1: note: ‘size_t’ is defined in header ‘<stddef.h>’; did you forget to ‘#include <stddef.h>’?
  +++ |+#include <stddef.h>
    1 | #ifndef __WORDSCOUNTER_H__
paso2_wordscounter.h:25:49: error: unknown type name ‘FILE’
   25 | void wordscounter_process(wordscounter_t *self, FILE *text_file);
      |                                                 ^~~~
paso2_wordscounter.h:1:1: note: ‘FILE’ is defined in header ‘<stdio.h>’; did you forget to ‘#include <stdio.h>’?
  +++ |+#include <stdio.h>
    1 | #ifndef __WORDSCOUNTER_H__
paso2_wordscounter.c:17:8: error: conflicting types for ‘wordscounter_get_words’
   17 | size_t wordscounter_get_words(wordscounter_t *self) {
      |        ^~~~~~~~~~~~~~~~~~~~~~
In file included from paso2_wordscounter.c:1:
paso2_wordscounter.h:20:8: note: previous declaration of ‘wordscounter_get_words’ was here
   20 | size_t wordscounter_get_words(wordscounter_t *self);
      |        ^~~~~~~~~~~~~~~~~~~~~~
paso2_wordscounter.c: In function ‘wordscounter_next_state’:
paso2_wordscounter.c:30:25: error: implicit declaration of function ‘malloc’ [-Wimplicit-function-declaration]
   30 |     char* delim_words = malloc(7 * sizeof(char));
      |                         ^~~~~~
paso2_wordscounter.c:30:25: error: incompatible implicit declaration of built-in function ‘malloc’ [-Werror]
paso2_wordscounter.c:5:1: note: include ‘<stdlib.h>’ or provide a declaration of ‘malloc’
    4 | #include <stdbool.h>
  +++ |+#include <stdlib.h>
    5 |
cc1: all warnings being treated as errors
make: *** [<builtin>: paso2_wordscounter.o] Error 1

real    0m0.022s
user    0m0.007s
sys     0m0.015s
[Error] Fallo la compilacion del codigo en 'source_unsafe.zip'. Codigo de error 2
```
Los errores en este paso son del compilador. El problema es, otra vez, que se declaran implicitamente funciones y tipos de datos como size_t. Esto ocurre cuando no se incluye las bibliotecas apropiadas que incluyen dichas definiciones. Por ejemplo, no se incluyo la biblioteca stddef.h ni stdlib.h.


## Paso 3

### Mejoras en el codigo

La diferencia entre este paso y el anterior es que se incluyeron las bibliotecas faltantes correspondientes y dentro del .h se hizo un include de las bibliotecas que se necesitaban ahi. Esto soluciono los problemas de compilacion relacionados a la falta de declaracion de funciones y/o tipos de dato.

### Problemas en la generacion del ejecutable

```
Descomprimiendo el codigo 'source_unsafe.zip'...
Archive:  source_unsafe.zip
  inflating: source_unsafe/paso3_main.c
  inflating: source_unsafe/paso3_wordscounter.c
  inflating: source_unsafe/paso3_wordscounter.h
Compilando el codigo...
  CC  paso3_wordscounter.o
  CC  paso3_main.o
  LD  tp
/usr/bin/ld: paso3_main.o: in function `main':
/task/student/source_unsafe/paso3_main.c:27: undefined reference to `wordscounter_destroy'
collect2: error: ld returned 1 exit status
make: *** [/task/student/MakefileTP0:142: tp] Error 1

real    0m0.236s
user    0m0.126s
sys     0m0.061s
[Error] Fallo la compilacion del codigo en 'source_unsafe.zip'. Codigo de error 2
```
En este caso tambien tenemos problemas del compilador. Lo que ocurre es que la funcion que esta declarada en el .h **wordcounter_destroy** no esta implementada en el .c, por lo tanto cuando intentemos usarla en el main de nuestro programa se genera un problema. Para solucionarlo habria que implementar dicha funcion en el .c


## Paso 4

### Mejoras en el codigo

La diferencia con respecto al paso anterior es que se implemento la funcion wordscounter_destroy. Aunque realmente sea una funcion la cual no hace nada, esto resuelve el problema de compilacion del paso previo.

### Valgrind prueba TDA

```
[=>] Executando el caso '/task/student//cases/tda' (con valgrind)...
[=>] Command line: /usr/bin/valgrind
                --tool=memcheck
                --leak-check=full --leak-resolution=med --show-reachable=yes
                --trace-children=yes
                --track-fds=yes
                --track-origins=no
                --time-stamp=yes --num-callers=20
                --error-exitcode=42
                --log-file=__valgrind__
                --suppressions=/task/student/suppressions.txt ./tp input_tda.txt

real    0m0.953s
user    0m0.817s
sys     0m0.087s

==00:00:00:00.000 59== Memcheck, a memory error detector
==00:00:00:00.000 59== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==00:00:00:00.000 59== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==00:00:00:00.000 59== Command: ./tp input_tda.txt
==00:00:00:00.000 59== Parent PID: 58
==00:00:00:00.000 59==
==00:00:00:00.922 59==
==00:00:00:00.922 59== FILE DESCRIPTORS: 5 open at exit.
==00:00:00:00.922 59== Open file descriptor 4: input_tda.txt
==00:00:00:00.922 59==    at 0x495FEAB: open (open64.c:48)
==00:00:00:00.922 59==    by 0x48E2195: _IO_file_open (fileops.c:189)
==00:00:00:00.922 59==    by 0x48E2459: _IO_file_fopen@@GLIBC_2.2.5 (fileops.c:281)
==00:00:00:00.922 59==    by 0x48D4B0D: __fopen_internal (iofopen.c:75)
==00:00:00:00.922 59==    by 0x48D4B0D: fopen@@GLIBC_2.2.5 (iofopen.c:86)
==00:00:00:00.922 59==    by 0x109177: main (paso4_main.c:14)
==00:00:00:00.922 59==
==00:00:00:00.922 59== Open file descriptor 3: /task/student/cases/tda/__valgrind__
==00:00:00:00.922 59==    <inherited from parent>
==00:00:00:00.922 59==
==00:00:00:00.922 59== Open file descriptor 2: /task/student/cases/tda/__stderr__
==00:00:00:00.922 59==    <inherited from parent>
==00:00:00:00.922 59==
==00:00:00:00.923 59== Open file descriptor 1: /task/student/cases/tda/__stdout__
==00:00:00:00.923 59==    <inherited from parent>
==00:00:00:00.923 59==
==00:00:00:00.923 59== Open file descriptor 0: /task/student/cases/tda/__stdin__
==00:00:00:00.923 59==    <inherited from parent>
==00:00:00:00.923 59==
==00:00:00:00.923 59==
==00:00:00:00.923 59== HEAP SUMMARY:
==00:00:00:00.923 59==     in use at exit: 1,977 bytes in 216 blocks
==00:00:00:00.923 59==   total heap usage: 218 allocs, 2 frees, 10,169 bytes allocated
==00:00:00:00.923 59==
==00:00:00:00.923 59== 472 bytes in 1 blocks are still reachable in loss record 1 of 2
==00:00:00:00.923 59==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==00:00:00:00.923 59==    by 0x48D4AAD: __fopen_internal (iofopen.c:65)
==00:00:00:00.923 59==    by 0x48D4AAD: fopen@@GLIBC_2.2.5 (iofopen.c:86)
==00:00:00:00.923 59==    by 0x109177: main (paso4_main.c:14)
==00:00:00:00.923 59==
==00:00:00:00.923 59== 1,505 bytes in 215 blocks are definitely lost in loss record 2 of 2
==00:00:00:00.923 59==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==00:00:00:00.923 59==    by 0x109301: wordscounter_next_state (paso4_wordscounter.c:35)
==00:00:00:00.923 59==    by 0x1093B5: wordscounter_process (paso4_wordscounter.c:30)
==00:00:00:00.923 59==    by 0x109197: main (paso4_main.c:24)
==00:00:00:00.923 59==
==00:00:00:00.923 59== LEAK SUMMARY:
==00:00:00:00.923 59==    definitely lost: 1,505 bytes in 215 blocks
==00:00:00:00.923 59==    indirectly lost: 0 bytes in 0 blocks
==00:00:00:00.923 59==      possibly lost: 0 bytes in 0 blocks
==00:00:00:00.923 59==    still reachable: 472 bytes in 1 blocks
==00:00:00:00.923 59==         suppressed: 0 bytes in 0 blocks
==00:00:00:00.923 59==
==00:00:00:00.923 59== For lists of detected and suppressed errors, rerun with: -s
==00:00:00:00.923 59== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
El problema que indica en este caso valgrind es que hay una perdida de memoria en nuestro programa. Nos indica ademas que esta memoria fue pedida por un malloc en la linea 35 de wordscounter.c Luego nos indica la cantidad de bytes perdidos. Tambien nos indica que no estamos cerrando un archivo. Esto ocurro en el main, que es donde hacemos el fopen pero nunca hacemos el fclose.

### Valgrind Long Filename

```
[=>] Executando el caso '/task/student//cases/nombre_largo' (con valgrind)...
[=>] Command line: /usr/bin/valgrind
                --tool=memcheck
                --leak-check=full --leak-resolution=med --show-reachable=yes
                --trace-children=yes
                --track-fds=yes
                --track-origins=no
                --time-stamp=yes --num-callers=20
                --error-exitcode=42
                --log-file=__valgrind__
                --suppressions=/task/student/suppressions.txt ./tp input_extremely_long_filename.txt

real    0m0.891s
user    0m0.779s
sys     0m0.063s

**00:00:00:00.841 47** *** memcpy_chk: buffer overflow detected ***: program terminated
==00:00:00:00.000 47== Memcheck, a memory error detector
==00:00:00:00.000 47== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==00:00:00:00.000 47== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==00:00:00:00.000 47== Command: ./tp input_extremely_long_filename.txt
==00:00:00:00.000 47== Parent PID: 46
==00:00:00:00.000 47==
**00:00:00:00.841 47** *** memcpy_chk: buffer overflow detected ***: program terminated
==00:00:00:00.842 47==    at 0x483E9CC: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==00:00:00:00.842 47==    by 0x4843C0A: __memcpy_chk (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==00:00:00:00.842 47==    by 0x109168: memcpy (string_fortified.h:34)
==00:00:00:00.842 47==    by 0x109168: main (paso4_main.c:13)
==00:00:00:00.862 47==
==00:00:00:00.862 47== FILE DESCRIPTORS: 4 open at exit.
==00:00:00:00.862 47== Open file descriptor 3: /task/student/cases/nombre_largo/__valgrind__
==00:00:00:00.862 47==    <inherited from parent>
==00:00:00:00.862 47==
==00:00:00:00.862 47== Open file descriptor 2: /task/student/cases/nombre_largo/__stderr__
==00:00:00:00.862 47==    <inherited from parent>
==00:00:00:00.862 47==
==00:00:00:00.862 47== Open file descriptor 1: /task/student/cases/nombre_largo/__stdout__
==00:00:00:00.862 47==    <inherited from parent>
==00:00:00:00.862 47==
==00:00:00:00.862 47== Open file descriptor 0: /task/student/cases/nombre_largo/__stdin__
==00:00:00:00.862 47==    <inherited from parent>
==00:00:00:00.862 47==
==00:00:00:00.863 47==
==00:00:00:00.863 47== HEAP SUMMARY:
==00:00:00:00.863 47==     in use at exit: 0 bytes in 0 blocks
==00:00:00:00.863 47==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==00:00:00:00.863 47==
==00:00:00:00.863 47== All heap blocks were freed -- no leaks are possible
==00:00:00:00.863 47==
==00:00:00:00.863 47== For lists of detected and suppressed errors, rerun with: -s
==00:00:00:00.863 47== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
El problema que nos indica Valgrind aca es que ocurrio un Buffer overflow. Estamos tratando de copiar algo mas largo en un lugar mas chico, por lo cual no entra y escribe memoria que no le corresponde. Esto ocurre dado que, como indica la prueba, se utiliza un filename muy larga pero nuestro buffer esta limitado a 30 caracteres.

### Uso de strncopy

El problema podria haberse solucionado usando strncopy, pero eso no hubiese resultado en una prueba exitosa debido a que en el buffer quedaria un filename recortado, y cuando intente abrir dicho archivo no lo encontraria, o encontraria un archivo distinto al esperado. Ademas, seguirian existiendo los problemas de perdida de memorias mostrados anteriormente.

### Segmentation Fault y Buffer Overflow

Segmentation fault es una manera de indicar al usuario que se intento acceder a una parte de memoria que no nos correspondia. Ya sea que esa memoria no fue alocada o esa memoria ya fue liberada. Es una excepcion para indicarnos que hubo un mal uso en la parte de la memoria del programa.

Buffer Overflow, por otro lado, es un error en el cual, cuando se intenta escribir contenido en un buffer, se termina escribiendo mas del tamaño destinado, por lo cual se terminan viendo afectadas las memorias contiguas a dicho buffer. Esto puede ser explotado dado que es una vulnerabilidad, si sabemos el tamaño del buffer y que representa la memoria contigua, se puede modificar dicha memoria.


## Paso 5

### Mejoras en el codigo

Con respecto al paso anterior, se solucionaron los problemas de perdida de memoria ya que no se alocan mas utilizando malloc los caracteres delimitantes. Ademas, se cierra apropiadamete el archivo en caso de que se haya abierto correctamente y se chequea que no se este intentenado cerrar el stdin. Ya no existe el problema del long filename ya que se abre directamente usando argv[1].


### Fallos en los casos de prueba publicos

```
[=>] Comparando archivo_invalido/__return_code__...
1c1
< 255
---
> 1

[=>] Comparando una_palabra/__return_code__...
[=>] Comparando una_palabra/__stdout__...
1c1
< 0
---
> 1
```

El SERCOM nos informa del resultado esperado (indicado con el >) y el resultado que obtuvo la prueba(indicado con el <)

### Hexdump

El ultimo caracter en el archivo input_single_word.txt es la letra d. Luego de eso el archivo termina.

### GDB

El comando **info functions** nos lista todas las funciones que estan definidas en nuestros archivos. El comando **list wordscounter_next_state** nos muestra 10 lineas al rededor de la funcion wordscounter_next_state. Luego, el comand **list** tambien nos muestra 10 lineas, en este caso nos mostro las 10 lineas seguidas a las que vimos en el comando previo. El comando **break** setea un breakpoint, es decir, la ejecucion del programa se parara cuando se llegue a ese punto. El comando **run** ejecuta nuestro programa, mientras que **quit** finaliza el uso del gdb.

El debugger no se freno en el breakpoint de la linea 45 porque nunca se llegó a ese punto. Al tener una sola palabra, el programa entra en el if del EOF, por lo que nunca llega a esa parte y se devuelve automaticamente STATE_FINISHED.


## Paso 6

En cuanto al paso anterior, se soluciono el problema del EOF. Ahora si se tiene una sola palabra y el archivo finaliza sin tener ningun delimiter, se suma correctamente una palabra al contador. Ademas, las delim words pasaron de ser un const char* dentro de la funcion next_state a ser un #define DELIM_WORDS.
