#include <stdio.h>
#include <stdlib.h>
#include "gera_saida.h"

/*Esta função escreve no arquivo de saída as informações do cabeçalho e em 
seguida os valores contidos em vetorOut, que é o vetor que guarda os valores
dos píxeis baseados nos centróides.*/
void geraArquivo(FILE *imgR, int *vetorOut, int linhas, int colunas, int max)	
{
	int i;
	int tam = linhas * colunas;
	fprintf(imgR, "P2\n");               //cria o arquivo PGM de saída
	fprintf(imgR, "%d %d\n", colunas, linhas);
	fprintf(imgR, "%d\n", max);
	for (i = 0; i < tam; i++)
		fprintf(imgR, "%d\n", vetorOut[i]);
}
