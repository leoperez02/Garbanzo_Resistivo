#include"DES.h"
#include<stdio.h>
#include<string.h>
/* DES (DATA ENCRYPTION STANDARD) */
int main(int argc,char* argv[])
{
	/* argv[1] = C/D (cifrar/descifrar) */
	if(argc==2)
	{
		int i;
		b64 texto,clave;
		b48* K;	
		printf("Texto plano: ");
		scanf("%lx",&texto);
		fflush(stdin);
		printf("Clave: ");
		scanf("%lx",&clave);
		fflush(stdin);
		/* Calcula subclaves */
		K=calcula_subclaves(clave);
		/* Imprimir claves */
		printf("\nSubllaves k1 ... k16\n"); 
		for(i=0;i<16;i++)
			printf("k%d = %lx\n",i+1,K[i]);	
		if(!strcmp(argv[1],"C"))
			texto=DES(texto,K,CIFRA);
		else
			texto=DES(texto,K,DESCIFRA);
		printf("\n\nTexto: %lx\n",texto);
		free(K);
		return 0;
	}
	else
	{
		printf("\nArgumentos incompletos. Programa finalizado...\n");
      return 1;
	}
}
