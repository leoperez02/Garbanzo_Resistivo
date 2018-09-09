#include"DES96.h"
#include<stdio.h>

int main(void)
{
	/* -- Vectores de prueba -- */
	/* Texto plano */
	b96 texto=new_b96(0x000000001E559232,0x1E329232EA6D0D73);
	/* clave */
	b64 clave=0x8000000000000000; /* 0x0E329232EA6D0D73 */
	printf("\n\tDES-96 (DATA ENCRYPTION STANDARD) ... mejorado :)\n");
	texto=DES96(texto,clave,CIFRA);/* Cifrado */
	printf("\n\n\tTexto cifrado = %lx %lx\n\n",texto[0],texto[1]);
	texto=DES96(texto,clave,DESCIFRA); /* Descifrado */
	printf("\n\n\tTexto descifrado= %lx %lx\n\n",texto[0],texto[1]);
	
	
	return 0;
}
