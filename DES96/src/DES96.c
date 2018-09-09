#include"DES96.h"

b96 DES96(b96 texto,b64 clave,int opc)
{
	int i;
	b48* bloques;
	b48 L0,R0,Li,Ri;
	/*Repartir 48 y 48 bits del texto de 96 en L0 y R0 */
	L0=(texto[0]<<16)|(texto[1]>>48);
	R0=texto[1]&0x0000FFFFFFFFFFFF;
	/* Calcula subclaves */
	b48* K=calcula_subclaves(clave);
	/* Descifrado */
	if(!opc){K=invertir_llaves(K);} /*Arreglo de llaves invertido */
 	/* Imprimir claves */
	printf("\nSubllaves k1 ... k16\n");
	for(i=0;i<16;i++)
		printf("k%d = %lx\n",i+1,K[i]);
	/* Lo,Ro */
	printf("\nL0 = %lx,\tR0 = %lx\n",L0,R0);
	/* Ronda 1 */
	bloques=ronda_DES96(L0,R0,K[0]); /* K1 */
	Li=bloques[0]; /* L1 */
	Ri=bloques[1]; /* R1 */
	printf("\nL1 = %lx,\tR1 = %lx\n",Li,Ri);
	/* Ronda 2 */
	bloques=ronda_DES96(Li,Ri,K[1]); /* K2 */
	Li=bloques[0]; /* L2 */
	Ri=bloques[1]; /* R2 */
	printf("\nL2 = %lx,\tR2 = %lx\n",Li,Ri);
	/* Aplicar permutación inicial IP de 96 bits */ 
	if(opc)	/* Cifrado */
	{
		bloques=permuta_cajaIP96(Li,Ri); /* IP(L2R2) */
		Li=bloques[0]; /* L2 (permutado) */
		Ri=bloques[1]; /* R2 (permutado) */
	}
	else /* Descifrado */
	{	
		bloques=permuta_cajaIP96(Ri,Li); /* IP(R2L2) */
		Li=bloques[1]; /* L2 (permutado) */
		Ri=bloques[0]; /* R2 (permutado) */
	}
	printf("\nPermutación IP96\nIP(L2,R2)= \n");
	printf("\nL2p = %lx,\tR2p = %lx\n",Li,Ri);
	for(i=2;i<14;i++)
	{ /* Ronda i desde la 3 (i=2) hasta la 14 (i=13) */
		bloques=ronda_DES96(Li,Ri,K[i]);
		Li=bloques[0]; /* L1 */
		Ri=bloques[1]; /* R1 */
		printf("\nL%d: %lx,\tR%d: %lx",i+1,Li,i+1,Ri);
	}
	/* Aplicar permutación IP inversa de 96 bits */
	if(opc)	/* Cifrado */
	{	
		bloques=permuta_cajaIP96_1(Li,Ri); /* IP_1(L14R14) */
		Li=bloques[0]; /* L14 (permutado) */
		Ri=bloques[1]; /* R14 (permutdo) */
	}
	else /* Descifrado */
	{	
		bloques=permuta_cajaIP96_1(Ri,Li); /* IP(R14L14) */
		Li=bloques[1]; /* L14 (permutado) */
		Ri=bloques[0]; /* R14 (permutado) */
	}
	printf("\nPermutación IP96_inv\nIP_inv(L14,R14)= \n");
	printf("\nL14p = %lx,\tR14p = %lx\n",Li,Ri);
	/* Ronda 15 */
	bloques=ronda_DES96(Li,Ri,K[14]); /* K15 */
	Li=bloques[0]; /* L15 */
	Ri=bloques[1]; /* R15 */
	printf("\nL15 = %lx,\tR15 = %lx\n",Li,Ri);
	/* Ronda 16 */
	bloques=ronda_DES96(Li,Ri,K[15]); /* K16 */
	Li=bloques[0]; /* L16 */ 
	Ri=bloques[1]; /* R16 */
	/* Intercambio??? */
 	bloques[0]=Ri;
	bloques[1]=Li;
	printf("\nL16 = %lx,\tR16 = %lx\n",Li,Ri);
	/* Reacomodar en 32 y 64 bits */
	Ri=(bloques[0]<<48)|bloques[1];
	Li=bloques[0]>>16;
	return new_b96(Li,Ri);
}

b48* ronda_DES96(b48 Li,b48 Ri,b48 Ki)
{
	b48* bloques=(b48*)malloc(sizeof(b48)*2);
	bloques[0]=Ri;
	bloques[1]=Li^f96(Ki,Ri);
	return bloques;
}

b48 f96(b48 Ki,b48 Ri)
{
	b48 paso1=Ki^Ri;
	b32 paso2=permuta_cajas_S(paso1);
	return permuta_cajaE(paso2);
}

b48* invertir_llaves(b48* Keys)
{
	int i;
	b48* K=(b48*)malloc(sizeof(b48)*16);
	for(i=0;i<16;i++)
		K[i]=Keys[15-i];
	return K;
}
