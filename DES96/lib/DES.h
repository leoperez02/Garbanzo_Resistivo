#include<stdlib.h>
#define CIFRA 1
#define DESCIFRA 0
/* Bloques de 32 y 64 bits */
typedef unsigned long int b64;
typedef unsigned long int b56;
typedef unsigned long int b48;
typedef unsigned int b32;
typedef unsigned int b28;

/* Funciones principales */
b64 DES(b64,b64,int);
b32* ronda_DES(b32,b32,b48);
b32 f(b48,b32);
b48* calcula_subclaves(b64);
b28 rotar(b28,int);

/* Funciones de cajas */
b64 permuta_cajaIP(b64);
b64 permuta_cajaIP_1(b64);
b56 permuta_cajaPC_1(b64);
b48 permuta_cajaPC_2(b28,b28);
b48 permuta_cajaE(b32);
b32 permuta_cajaP(b32);
b32 permuta_cajas_S(b48);
