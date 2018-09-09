#include"DES.h"

#define L 1 /* 1 = left shift (bloque<<n-bits) */ 
#define R 0 /* 0 = rigth shift (bloque>>n-bits) */

typedef unsigned long int* b96;

/* Funciones principales */
b96 DES96(b96,b64,int);
b48* ronda_DES96(b48,b48,b48);
b48 f96(b48,b48);
b48* invertir_llaves(b48*);

/* Funciones de cajas */ 
b48* permuta_cajaIP96(b48,b48);
b48* permuta_cajaIP96_1(b48,b48);

/* Funciones auxiliares para bloques de 96 bits */
b96 new_b96(b48,b48);
b96 shift(b96,int,int);
void printf_b96(b96);
