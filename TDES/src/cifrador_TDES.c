#include"TDES.h"
#include<stdio.h>
#include<string.h>
#define MAX 200



int main(int argc, char* argv[])
{	
	/*
		argv[0] = nombre de programa 
			name = cifrado_TDES
		
		argv[1] = opcion de programa
			file = cifrar archivo
			block = cifrar bloque de 64 bits 
		
		argv[2] = opcion de cifrado
			EDE = cifrar-descifrar-cifrar
			EEE = cifrar-cifrar-cifrar
			
		argv[3] = cifrar o descifrar
			C = cifrar
			D = descifrar
	*/
	if(argc==4) /* Argumentos completos */
	{
		b64* K=(b64*)malloc(sizeof(b64)*3);
		b48* k=(b48*)malloc(sizeof(b48)*48);
		printf("K1: ");
		scanf("%lx",&K[0]);
		fflush(stdin);
		printf("K2: ");
		scanf("%lx",&K[1]);
		fflush(stdin);
		printf("K3: ");
		scanf("%lx",&K[2]);
		fflush(stdin);
		k=get_keys(K);
		if(!strcmp(argv[1],"block"))/*Cifrar un bloque de 64 bits desde consola*/
		{
			b64 texto;
			printf("Texto plano: ");
			scanf("%lx",&texto);
			fflush(stdin);
			if(!strcmp(argv[2],"EDE")) /* Cifrado EDE=cifrar-descifrar-cifrar */
			{
				if(!strcmp(argv[3],"C"))
					texto=TDES_EDE(texto,k,CIFRA);
				else
					texto=TDES_EDE(texto,k,DESCIFRA);
			}
			else /* Cifrado EEE = cifrar-cifrar-cifrar */
			{
				if(!strcmp(argv[3],"C"))
					texto=TDES_EEE(texto,k,CIFRA);
				else
					texto=TDES_EEE(texto,k,DESCIFRA);
			}
			printf("Texto cifrado: %lx\n",texto);
			free(K);
			free(k);
			return 0;
		}
		else /* Cifrar archivo */
		{
			FILE *fichero_in,*fichero_out;
			char* ruta;
			ruta=(char*)malloc(MAX*sizeof(char));
			printf("Ruta del archivo: ");
			scanf("%s",ruta);
			fflush(stdin);
			fichero_in=fopen(ruta,"rb");
			if(fichero_in)
			{
				/* Crear archivo de salida */
				b64 bloque_64;
				fichero_out=fopen(strcat(ruta,".cifrado"),"wb");
				if(!strcmp(argv[2],"EDE"))/*Cifrado EDE=cifrar-descifrar-cifrar*/
				{
					while(fread(&bloque_64,8,1,fichero_in)==1)
					{
						if(!strcmp(argv[3],"C"))
							bloque_64=TDES_EDE(bloque_64,k,CIFRA);
						else
							bloque_64=TDES_EDE(bloque_64,k,DESCIFRA);
						fwrite(&bloque_64,8,1,fichero_out);
					}
				}
				else /* Cifrado EEE = cifrar-cifrar-cifrar */
				{
					while(fread(&bloque_64,8,1,fichero_in)==1)
					{
						if(!strcmp(argv[3],"C"))
							bloque_64=TDES_EEE(bloque_64,k,CIFRA);
						else
							bloque_64=TDES_EEE(bloque_64,k,DESCIFRA);
						fwrite(&bloque_64,8,1,fichero_out);
					}
				}
				fclose(fichero_in);
				fclose(fichero_out);
				free(K);
				free(k);
				return 0;
			}
			else
			{
				printf("\nError leyendo archivo: %s\n",ruta);
				free(K);
				return 1;
			}
		}	
	} 
	else
	{
		printf("\nArgumentos incompletos. Programa finalizado...\n");
      return 1;	
	}
}
