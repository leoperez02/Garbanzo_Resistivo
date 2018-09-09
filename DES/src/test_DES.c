#include"DES.h"
#include<stdio.h>
#define NUM_VECTORS 4
int main(void)
{
	/* DES (DATA ENCRYPTION STANDARD) */
	/*
		Set 1, vector#  0:
                           key=8000000000000000
                         plain=0000000000000000
                        cipher=95A8D72813DAA94D
                     decrypted=0000000000000000
            Iterated 100 times=F749E1F8DEFAF605
           Iterated 1000 times=F396DD0B33D04244

		Set 1, vector#  1:
                           key=4000000000000000
                         plain=0000000000000000
                        cipher=0EEC1487DD8C26D5
                     decrypted=0000000000000000
            Iterated 100 times=E5BEE86B600F3B48
           Iterated 1000 times=1D5931D700EF4E15

		Set 1, vector#  2:
                           key=2000000000000000
                         plain=0000000000000000
                        cipher=7AD16FFB79C45926
                     decrypted=0000000000000000
            Iterated 100 times=C4B51BB0A1E0DF57
           Iterated 1000 times=B2D1B91E994BA5FF

		Set 1, vector#  3:
                           key=1000000000000000
                         plain=0000000000000000
                        cipher=D3746294CA6A6CF3
                     decrypted=0000000000000000
            Iterated 100 times=0008AEE9CDC85FC6
           Iterated 1000 times=984080D72E08BB81
	*/
	int i,index;
	b64 claves[NUM_VECTORS];
	b64 textos[NUM_VECTORS];
	b64 cifrado,descifrado,cifrado100;
	b48* K;	
	/* -- Vectores de prueba -- */				
	claves[0]=0x8000000000000000;
	claves[1]=0x4000000000000000;
	claves[2]=0x2000000000000000;
	claves[3]=0x1000000000000000; 
	textos[0]=0x0000000000000000;
	textos[1]=0x0000000000000000;
	textos[2]=0x0000000000000000;
	textos[3]=0x0000000000000000;
	
	printf("\n\tDES (DATA ENCRYPTION STANDARD)\n");
	
	for(index=0;index<NUM_VECTORS;index++)
	{
		/* Calcula subclaves */
		K=calcula_subclaves(claves[index]);
		/* Imprimir claves */
			/* 
			printf("\nSubllaves k1 ... k16\n"); 
			for(i=0;i<16;i++)
				printf("k%d = %lx\n",i+1,K[i]);
			*/	
		/* Cifrado */
		cifrado=DES(textos[index],K,CIFRA);
		/* Descifrado */
		descifrado=DES(cifrado,K,DESCIFRA);
		/* Test de 100 iteraciones */
		cifrado100=cifrado;
		for(i=1;i<100;i++)
			cifrado100=DES(cifrado100,K,CIFRA);
		printf("\n\n****************************************************\n\n");	
		printf("\tSet 1, vector #%d:\n\n",index);
		printf("Clave = %lx\n",claves[index]);
		printf("Texto = %lx\n",textos[index]);	
		printf("Cifrado = %lx\n",cifrado);
		printf("Descifrado = %lx\n",descifrado);
		printf("Iterado 100 veces: %lx\n",cifrado100);
		printf("\n\n****************************************************\n\n");
	}
	return 0;
}
