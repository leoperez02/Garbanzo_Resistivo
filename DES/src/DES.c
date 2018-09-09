#include"DES.h"

b64 DES(b64 texto,b48* K,int opc)
{
	int i;
	b32* bloques;
	b32 Li,Ri;
	/* Permutación inicial IP al texto de 64 bits */
	texto=permuta_cajaIP(texto);
	printf("\nPermutación IP\nIP(texto)= %lx\n",texto);
	/* Partición en L0 y R0 */
	Li=texto>>32;
	Ri=texto&0x00000000ffffffff;
	printf("\nL0 = %x,\tR0 = %x\n",Li,Ri);
	/* Inicio de 16 rondas DES */
	for(i=0;i<16;i++)
	{
		if(opc) /* Cifrado */
			bloques=ronda_DES(Li,Ri,K[i]);
		else /* Descifrado */
			bloques=ronda_DES(Li,Ri,K[15-i]);
		Li=bloques[0];
		Ri=bloques[1];
		printf("\nL%d: %x,\tR%d: %x",i+1,Li,i+1,Ri);
	}
	texto=Ri;
	texto=(texto<<32)|Li;
	return permuta_cajaIP_1(texto);
}

b32* ronda_DES(b32 Li,b32 Ri,b48 Ki)
{
	b32* bloques=(b32*)malloc(sizeof(b32)*2);
	bloques[0]=Ri;
	bloques[1]=Li^f(Ki,Ri);
	return bloques;
}

b32 f(b48 Ki,b32 Ri)
{
	b48 paso1=Ki^permuta_cajaE(Ri);
	b32 paso2=permuta_cajas_S(paso1);
	return permuta_cajaP(paso2);
}

b48* calcula_subclaves(b64 clave)
{
	int i,corrimientos[]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	b28 Co,Do;
	b48* K=(b48*)malloc(sizeof(b48)*16);
	b56 Co_Do=permuta_cajaPC_1(clave);
	/* printf("\nPC-1\nDecimal: %lu\nHexadecimal: %lx\n",Co_Do,Co_Do);*/
	Co=(b28)(Co_Do>>28);
	Do=(b28)(Co_Do&0x000000000fffffff);
	/* printf("\nC0 = %x,\tD0 = %x",Co,Do); */
	for(i=0;i<16;i++)
	{
		Co=rotar(Co,corrimientos[i]);
		Do=rotar(Do,corrimientos[i]);	
		/* printf("\nC%d = %x,\tD%d = %x",i+1,Co,i+1,Do); */
		K[i]=permuta_cajaPC_2(Co,Do);
	}
	return K;
}

b28 rotar(b28 bloque,int desplazamiento)
{
	return ((bloque<<desplazamiento)|(bloque>>(28-desplazamiento)))&0x0fffffff;
}
