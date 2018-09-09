#include"TDES.h"

b64 TDES_EEE(b64 texto,b48* K,int opc)
{
	int i;
	b32* bloques;
	b32 Li,Ri;
	/* Permutación IP al inicio */
	texto=permuta_cajaIP(texto); 
	Li=texto>>32;
	Ri=texto&0x00000000ffffffff;
	/* 48 rondas DES; 16-> K1, 16-> K2, 16-> K3 */
	for(i=0;i<48;i++)
	{
		if(opc) /* Cifrado */
			bloques=ronda_DES(Li,Ri,K[i]);
		else /* Descifrado (llaves aplicadas en orden inverso )*/
			bloques=ronda_DES(Li,Ri,K[47-i]);
		/* Intercambio de Li y Ri cada 16 rondas */
		if(i!=15&&i!=31)
		{
			Li=bloques[0];
			Ri=bloques[1];
		}
		else
		{
			Li=bloques[1];
			Ri=bloques[0];
		}
	}
	/* Intercambio de bloques L48 y R48 : bloque=R48,L48 */
	texto=Ri;
	texto=(texto<<32)|Li;
	/* Permutación IP inversa al final */
	return permuta_cajaIP_1(texto);
}

b64 TDES_EDE(b64 texto,b48* K,int opc)
{
	int i;
	b32* bloques;
	b32 Li,Ri;
	/*Permutación IP al inicio*/
	texto=permuta_cajaIP(texto);
	Li=texto>>32;
	Ri=texto&0x00000000ffffffff;
	/* Rondas 1-16: cifrar */
	for(i=0;i<16;i++)
	{
		if(opc) /* Cifrado */
			bloques=ronda_DES(Li,Ri,K[i]);
		else
			bloques=ronda_DES(Li,Ri,K[47-i]);
		Li=bloques[0];
		Ri=bloques[1];
	}
	/* Intercambio de bloques L16 y R16 : bloque=R16,L16 */
	Li=bloques[1];
	Ri=bloques[0];
	/* Rondas 17-32: descifrar */
	for(;i<32;i++)
	{
		if(opc) /* Cifrado */
			bloques=ronda_DES(Li,Ri,K[47-i]);
		else
			bloques=ronda_DES(Li,Ri,K[i]);
		Li=bloques[0];
		Ri=bloques[1];
	}
	/* Intercambio de bloques L32 y R32 : bloque=R32,L32 */
	Li=bloques[1];
	Ri=bloques[0];
	/* Rondas 33-48: cifrar */
	for(;i<48;i++)
	{
		if(opc) /* Cifrado */
			bloques=ronda_DES(Li,Ri,K[i]);
		else
			bloques=ronda_DES(Li,Ri,K[47-i]);
		Li=bloques[0];
		Ri=bloques[1];
	}
	/* Intercambio final */
	texto=Ri;
	texto=(texto<<32)|Li;
	/* Permutación IP inversa al final */
	return permuta_cajaIP_1(texto);
}

b48* get_keys(b64* claves)
{
	int i,j;
	/* k = set de 16 subclaves de una K, sub_claves = arreglo de las tres k */
	b48* k;
	b48* sub_claves;
	sub_claves=(b48*)malloc(sizeof(b48)*48);
	k=calcula_subclaves(claves[0]);
	for(i=0;i<16;i++)
		sub_claves[i]=k[i];
	k=calcula_subclaves(claves[1]);
	for(j=0;i<32;i++,j++)
		sub_claves[i]=k[j];	
	k=calcula_subclaves(claves[2]);
	for(j=0;i<48;i++,j++)
		sub_claves[i]=k[j];
	return sub_claves;	
} 
