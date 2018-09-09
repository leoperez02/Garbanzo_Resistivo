#include"DES.h"
/* Funciones principales */
b64 TDES_EEE(b64,b48*,int); /* Cifra-Cifra-Cifra */
b64 TDES_EDE(b64,b48*,int); /* Cifra-Descifra-Cifra */
/* Recibe K1,K2,K3 de 64-bits c/u y regresa k1,k2,k3,...,k48 de 48-bits c/u */ 
b48* get_keys(b64*); 
