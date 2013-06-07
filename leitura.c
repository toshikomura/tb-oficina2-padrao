#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"

//Função que faz a leitura do arquivo de entrada e gera
int leImagem(FILE *imgO, int *linhas, int *colunas, int *max)
{
	int i, j;
	char str[2];             //variável auxiliar para leitura de strings
	int ch;                    //variável auxiliar para litura de chars
	int num = 0;           //variável auxiliar para leitura de números
	*linhas = 0;             //passado por referência já que será usado em outras funções
	*colunas = 0;	        //         ||
	*max = 0;                 //         ||
	fpos_t pos;            //variável do tipo fpos_t que armazena a posição no arquivo
	fscanf(imgO, "%s", str);
	if (strcmp(str, "P2") != 0)
		return 0;		//caso a imagem não seja do tipo plain PGM
	ch = fgetc(imgO);
	while (*max == 0)         //enquanto não for lido o valor máximo do arquivo
	{
		fgetpos(imgO, &pos);     // marca posição do char que foi pego
		ch = fgetc(imgO);
		if (ch == 35)        //se o char for o #
		{
			while (ch != 10)       //enquanto for diferente de \n
				ch = fgetc(imgO);
		}
		else if (num == 0)        // como os primeiros números no arquivo são o número de colunas e o de linhas, num ainda está em zero
		{
			fsetpos(imgO, &pos);     //retorna para a posição marcada
			fscanf(imgO, "%d", &num);     //lê o número de colunas
			*colunas = num;
			fscanf(imgO, "%d", &num);    //lê o número de linhas
			*linhas = num;
		}
		else        //como já foram lidos o número de colunas e de linhas, num != 0
		{
			fsetpos(imgO, &pos);
			fscanf(imgO, "%d", &num);      //lê o valor máximo do arquivo
			*max = num;
		}
	}
	return 1;
}

void criaVetor(FILE *imgO, int *vetor, int tam)
{
	int i, j, num;
	for (i = 0; i < tam; i++)
	{
			fscanf(imgO, "%d", &num);        //lê informações do arquivo e armazena no vetor
			vetor[i] = num;
	}
}
