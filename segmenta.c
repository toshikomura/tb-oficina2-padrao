#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "segmenta2.h"
#include "gera_saida.h"

int main(int count, char *argv[])
{
	int aux = atoi(argv[2]);     //número de segmentos solicitados
	if (count != 4)  //caso os parâmetros não sejam passados corretamente.
	{
		printf("Parâmetros incorretos.\n");
		printf("Modo de uso: ./segmenta [imagem de entrada] [segmentos] [imagem de saída].\nTente novamente.\n");
	}
	else if ((aux < 2) || (aux > 10))
		printf("O número de segmentos deve estar entre 2 e 10.\nTente novamente.\n");
	else
	{
		int linhas, colunas, max, i, tam;
		char *caminho;
		int *vetorIn, *vetorOut;          //vetor onde serão armazenadas os valores do arquivo e vetor contendo apenas os valores baseados nos centróides
		FILE *imgO;
		FILE *imgR;
		caminho = (char *) malloc(sizeof(char) * (strlen(argv[1]) + 5));
		if (!caminho)   //caso o programa não consiga alocar memória
		{
			printf("Memória insuficiente.\n");
			return 0;
		}
		strcpy(caminho, "../");		//define a pasta anterior como sendo o diretório atual do executável
		strcat(caminho, argv[1]);		//concatena as strings
		imgO = fopen(caminho, "r+");
		free(caminho);
		caminho = (char *) malloc(sizeof(char) * (strlen(argv[3]) + 5));
		if (!caminho)
		{
			printf("Memória insuficiente.\n");
			return 0;
		}
		strcpy(caminho, "../");
		strcat(caminho, argv[3]);
		imgR = fopen(caminho, "w");
		free(caminho);
		i = leImagem(imgO, &linhas, &colunas, &max);
		if (i == 0)  //se a imagem não for válida
		{
			printf("Imagem inválida.\nInsira uma imagem do tipo plain Pgm.\n");
			return 0;
		}
		tam = linhas * colunas;
		vetorIn = (int *) malloc(sizeof(int) * tam);  //aloca a memória necessária para o vetor
		vetorOut = (int *) malloc(sizeof(int) * tam);
		criaVetor(imgO, vetorIn, tam);
		i = segmenta(vetorIn, vetorOut, linhas, colunas, max, aux);
		if (i == 0)
		{
			printf("Memória insuficiente.\n");
			return 0;
		}
		geraArquivo(imgR, vetorOut, linhas, colunas, max);
		fclose(imgO);
		fclose(imgR);
		free(vetorIn);	//libera a memória alocada anteriormente
		free(vetorOut);
	}
	return 1;
}
