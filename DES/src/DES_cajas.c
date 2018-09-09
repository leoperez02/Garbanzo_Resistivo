#include"DES.h"
#include"cajasDES.h"

b64 permuta_cajaIP(b64 texto)
{
	b64 permutado=0,s=1,aux;			 
	int i;
	for(i=0;i<64;i++)
	{ /* El MSB es el bit 1 (i=0), el LSB es el bit 64 (i=63) */
		aux=texto>>(64-IP[i]); /* Recorrer bit buscado al final de la cadena */
		aux&=s; /* And con un 1 para limpiar el resto de los bits */
		aux<<=(64-1-i); /*Se acomoda el bit buscado en la posición que diga i */
		permutado|=aux; /* Se hace un Or con permutado para acumular los bits */
	}
	return permutado;
}

b64 permuta_cajaIP_1(b64 texto)
{
	b64 permutado=0,s=1,aux;			 
	int i;
	for(i=0;i<64;i++)
	{ /* El MSB es el bit 1 (i=0), el LSB es el bit 64 (i=63) */ 
		aux=texto>>(64-IP_inv[i]);/*Recorrer bit buscado al final de la cadena*/
		aux&=s;/*And con un 1 para limpiar el resto de los bits*/
		aux<<=(64-1-i); /*Se acomoda el bit buscado en la posición que diga i */
		permutado|=aux; /* Se hace un Or con permutado para acumular los bits */
	}
	return permutado;
}

b56 permuta_cajaPC_1(b64 clave)
{/*El MSB del bloque de salida es el bit 1 (i=0) y el LSB es el bit 56 (i=55)*/
	b56 permutado=0,s=1,aux;			 
	int i;
	for(i=0;i<56;i++)
	{/*El MSB de la clave es el bit 1 (0), el LSB es el bit 64 (63) */
		aux=clave>>(64-PC_1[i]);/*Recorrer bit buscado al final de la cadena*/
		aux&=s;/*And con un 1 para limpiar el resto de los bits*/
		aux<<=(56-1-i);/*Se acomoda el bit buscado en la posición que diga i*/
		permutado|=aux;/*Se hace un Or con permutado para guardar los bits*/
	}
	return permutado;
}

b48 permuta_cajaPC_2(b28 Ci,b28 Di)
{/*El MSB del bloque de salida es el bit 1 (i=0) y el LSB es el bit 48 (i=47)*/
	int i;
	b48 permutado=0,s=1,aux;
	b56 concatenadas=6;
	/* Concatenar Ci y Di en CiDi de 56 bits	*/
	concatenadas=Ci;
	concatenadas=(concatenadas<<28)|Di;
	/*
	printf("\nC = %x,\tD = %x",Ci,Di);
	printf("\nconcatenadas = %lx \n",concatenadas);
	*/
	for(i=0;i<48;i++)
	{/*El MSB de CiDi el bit 1 (0) y el LSB es el bit 56 (55)*/
		aux=concatenadas>>(56-PC_2[i]);/*Recorrer bit buscado al final*/
		aux&=s;/*And con un 1 para limpiar el resto de los bits*/
		aux<<=(48-1-i);/*Se acomoda el bit buscado en la posición que diga i*/
		permutado|=aux;/*Se hace un Or con permutado para guardar los bits */
	}
	return permutado;
}

b48 permuta_cajaE(b32 bloque)
{/*El MSB del bloque de salida es el bit 1 (i=0) y el LSB es el bit 48 (i=47)*/
	b48 permutado=0,s=1,aux;			 
	int i;
	for(i=0;i<48;i++)
	{/*El MSB del bloque es el bit 1 (0), el LSB es el bit 32 (31) */
		aux=bloque>>(32-E[i]);/*Recorrer bit buscado al final de la cadena*/
		aux&=s;/*And con un 1 para limpiar el resto de los bits*/
		aux<<=(48-1-i);/*Se acomoda el bit buscado en la posición que indique i*/
		permutado|=aux;/*Se hace un Or con permutado para guardar los bits*/
	}
	return permutado;
}

b32 permuta_cajaP(b32 bloque)
{
	b32 permutado=0,s=1,aux;			 
	int i;
	for(i=0;i<32;i++)
	{/*El MSB es el bit 1 (i=0), el LSB es el bit 32 (i=31) */
		aux=bloque>>(32-P[i]);/*Recorrer bit buscado al final de la cadena*/
		aux&=s;/*And con un 1 para limpiar el resto de los bits*/
		aux<<=(32-1-i);/*Se acomoda el bit buscado en la posición que diga i*/
		permutado|=aux;/*Se hace un Or con permutado para guardar los bits*/
	}
	return permutado;
}

b32 permuta_cajas_S(b48 bloque)
{
	/*8 pares ordenados (m,n) que dan números de 4 bits */
	short int coordenadas[8][2];
	short int b6[8]; /* Bloques B1,B2 ... B8 de 4-bits, B1 = S1[m][n] */
	b32 concatenado=0; /*Concatenación de los 8-bloques Bi*/
	int i;
	for(i=0;i<8;i++)
	{
		b6[i]=bloque>>(42-6*i);/*Extracción de bloques de bits de 6 en 6 */
		coordenadas[i][1]=(b6[i] & 30)>>1;/*Punto n*/
		coordenadas[i][0]=(b6[i] & 1)|((b6[i] & 32)>>4);/*Punto m */
		/*printf("(m,n) = (%d,%d)\n",coordenadas[i][0],coordenadas[i][1]);*/
	}	
	b6[7]=s8[coordenadas[7][0]][coordenadas[7][1]];/*bloques de 4 bits */
	b6[6]=s7[coordenadas[6][0]][coordenadas[6][1]];
	b6[5]=s6[coordenadas[5][0]][coordenadas[5][1]];
	b6[4]=s5[coordenadas[4][0]][coordenadas[4][1]];
	b6[3]=s4[coordenadas[3][0]][coordenadas[3][1]];
	b6[2]=s3[coordenadas[2][0]][coordenadas[2][1]];
	b6[1]=s2[coordenadas[1][0]][coordenadas[1][1]];
	b6[0]=s1[coordenadas[0][0]][coordenadas[0][1]];
	/*Concatenar bloques Bi */
	for(i=0;i<8;i++)
		concatenado=concatenado|(b6[i])<<(31-4*i-3);
	return concatenado;
}
