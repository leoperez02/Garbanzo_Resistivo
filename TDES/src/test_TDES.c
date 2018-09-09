#include"TDES.h"
#include<stdio.h>

int main(void)
{
	int i;
 	b64 cifrado,descifrado,texto;
	b64* K=(b64*)malloc(sizeof(b64)*3);
	b48* k=(b48*)malloc(sizeof(b48)*48);
	
	/* -- Vectores de prueba -- */
	texto=0x8787878787878787;
	K[0]=0x0E329232EA6D0D73;
	K[1]=0x0E329232EA6D0D73;
	K[2]=0x0E329232EA6D0D73;
	
	printf("\n\tTriple DES (DATA ENCRYPTION STANDARD)\n");
	
	/* Cálculo de subclaves */
	k=get_keys(K);
	printf("\nSubllaves k1 ... k48\n"); 
	for(i=0;i<48;i++)
		printf("k%d = %lx\n",i+1,k[i]);
	for(i=0;i<3;i++)
		printf("\tK%d = %lx\n",i+1,K[i]);		
	
	/* Versión 1 */
	cifrado=TDES_EEE(texto,k,CIFRA); /* Cifrado */
	printf("\nVersión 1 (C-C-C):\n\n");
	printf("\tTexto plano = %lx\n",texto);
	printf("\tTexto cifrado = %lx\n",cifrado);
	descifrado=TDES_EEE(cifrado,k,DESCIFRA); /* Descifrado */
	printf("\tTexto descifrado = %lx\n",descifrado);
	
	/* Versión 2 */
	cifrado=TDES_EDE(texto,k,CIFRA); /* Cifrado */
	printf("\nVersión 2 (C-D-C):\n\n");
	printf("\tTexto plano = %lx\n",texto);
	printf("\tTexto cifrado = %lx\n",cifrado);
	descifrado=TDES_EDE(cifrado,k,DESCIFRA); /* Descifrado */
	printf("\tTexto descifrado = %lx\n",descifrado);
	
	return 0;
}
