#include"DES96.h"
#include"cajasDES96.h"

b48* permuta_cajaIP96(b48 Li,b48 Ri)
{
	int i;
	b48* permutados=(b48*)malloc(sizeof(b48)*2);	
	b96 texto96,aux;
	Ri=(Li<<48)|Ri;
	Li=Li>>16;
	texto96=new_b96(Li,Ri);
	aux=new_b96(0,0);	
	for(i=0;i<96;i++)
	{/*El MSB es el bit 1 (i=0), el LSB es el bit 96 (i=95) */
		/*aux=texto>>(96-IP96[i]);//Recorrer bit buscado al final de la cadena*/
		aux=shift(new_b96(Li,Ri),R,96-IP96[i]);
		/*aux&=s;//And con un 1 para limpiar el resto de los bits*/
		aux[0]=0;
		aux[1]=aux[1]&0x0000000000000001;
		/*aux<<=(64-1-i);//Se acomoda el bit buscado en la posición que diga i*/
		aux=shift(aux,L,96-1-i);
		/*permutado|=aux;//Se hace un Or con permutado para acumular los bits*/
		permutados[0]=permutados[0]|aux[0];
		permutados[1]=permutados[1]|aux[1];
	}/*Repartir 48 y 48 */
	permutados[0]=(permutados[0]<<16)|(permutados[1]>>48);
	permutados[1]=permutados[1]&0x0000FFFFFFFFFFFF;
	return permutados;
}

b48* permuta_cajaIP96_1(b48 Li,b48 Ri)
{
	int i;
	b48* permutados=(b48*)malloc(sizeof(b48)*2);	
	b96 texto96,aux;
	Ri=(Li<<48)|Ri;
	Li=Li>>16;
	texto96=new_b96(Li,Ri);
	aux=new_b96(0,0);	
	for(i=0;i<96;i++)
	{/*El MSB es el bit 1 (i=0), el LSB es el bit 96 (i=95) */
		/*aux=texto>>(96-IP96[i]);//Recorrer bit buscado al final de la cadena*/
		aux=shift(new_b96(Li,Ri),R,96-IP96_inv[i]);
		/*aux&=s;//And con un 1 para limpiar el resto de los bits*/
		aux[0]=0;
		aux[1]=aux[1]&0x0000000000000001;
		/*aux<<=(64-1-i);//Se acomoda el bit buscado en la posición que diga i*/
		aux=shift(aux,L,96-1-i);
		/*permutado|=aux;//Se hace un Or con permutado para acumular los bits*/
		permutados[0]=permutados[0]|aux[0];
		permutados[1]=permutados[1]|aux[1];
	}/*Repartir 48 y 48 */
	permutados[0]=(permutados[0]<<16)|(permutados[1]>>48);
	permutados[1]=permutados[1]&0x0000FFFFFFFFFFFF;
	return permutados;
}

b96 new_b96(b48 a,b48 b)
{
	b96 lain=(b96)malloc(sizeof(b48)*2);
	lain[0]=a;
	lain[1]=b;
	return lain;
}

b96 shift(b96 bloques,int dir,int n)
{
	if(n)
	{
		if(dir) /* Corrimiento a la izquierda */
		{
			if(n<64)
			{
				bloques[0]=bloques[0]<<n;
				bloques[0]=bloques[0] | (bloques[1]>>(64-n));
				bloques[1]=bloques[1]<<n;
			}
			else
			{
				if(n<96)
				{
					bloques[0]=bloques[0]<<n;
					bloques[0]=bloques[0] | (bloques[1]<<(n-64));
					bloques[1]=0;
				}
				else
				{
					bloques[0]=0;
					bloques[1]=0;
				}
			}
		}
		else /* Corrimiento a la derecha */
		{
			if(n<64)
			{
				bloques[1]=bloques[1]>>n;
				bloques[1]=(bloques[0]<<(64-n)) | bloques[1];
				bloques[0]=bloques[0]>>n;
			}
			else
			{
				bloques[1]=0;
				bloques[1]=(bloques[0]>>(n-64)) | bloques[1];
				bloques[0]=0;
			}
		}
	}
	return bloques;
}

void printf_b96(b96 bloque)
{
	int i;
	for(i=0;i<2;i++)
		printf("%lx ",bloque[i]);
}
