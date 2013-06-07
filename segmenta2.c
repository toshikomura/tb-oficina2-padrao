#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "segmenta2.h"

/*  Função que busca o menor elemento de um vetor. Nesse caso, procura-se o índice para o
qual a distância entre o elemento e o centróide é mínima.
  Primeiro assume-se que o primeiro elemento do vetor é o menor;
  Em seguida varre-se o vetor inteiro procurando, através de comparações, o menor elemento.*/
int buscaMenor(tipoS dados, int aux)
{
	int i, indice = 0;
	int menor = dados.dist[0];
	for (i = 1; i < aux; i++)
		if (dados.dist[i] < menor)
		{
			menor = dados.dist[i];
			indice = i;
		}
	return indice;
}

/*Esta função funciona da seguinte forma:
   1) Primeiro são gerados valores aleatórios para os centróides;
   2) Em seguida calcula-se a distância de cada píxel da imagem original até cada um dos centróides;
   3) Verifica-se para qual centróide a distância é a menor para cada um dos píxeis;
   4) Rotula-se, no vetor de saída, todos os píxeis de acordo com o centróide mais próximo;
   5) Calcula-se os valores dos novos centróides a partir da média aritmética para cada um dos centróides atuais;
   6) Verifica se houve mudança no valor de pelos um centróide, se houve voltar para o passo 2;
   7) Quando não  houver mais mudanças a segmentação estará completa.*/
int segmenta(int *vetorIn, int *vetorOut, int linhas ,int colunas, int max, int aux)
{
	int tam = linhas * colunas;
	int i, j, indice;
	int mudou = 1;
	srand(time(NULL));                //inicializa a função random
	tipoS dados;
	dados.cent = (int *) malloc(sizeof(int) * aux);
	dados.conta = (int *) malloc(sizeof(int) * aux);
	dados.soma = (int *) malloc(sizeof(int) * aux);
	dados.centaux = (int *) malloc(sizeof(int) * aux);
	dados.dist = (int *) malloc(sizeof(int) * aux);
	if ((!dados.cent) || (!dados.conta) || (!dados.soma) || (!dados.centaux) || (!dados.dist))  //se não conseguiu alocar memória
		return 0;
	for (i = 0; i < aux; i++)
	{
		dados.cent[i] = rand () % max + 1;              //Gera valores aleatórios para os centróides.
		dados.centaux[i] = dados.cent[i];
	}
	while (mudou != 0)           //Enquanto houver mudanças no valor de pelo menos um centróide.
	{
		mudou = 0;
		for (i = 0; i < aux; i++)
		{
			dados.conta[i] = 0;            //Zera o número de elementos de cada centróide.
			dados.soma[i] = 0;            //Zera o valor da soma.
		}
		for (i = 0; i < tam; i++)
		{
			for (j = 0; j < aux; j++)
			{
				dados.dist[j] = vetorIn[i] - dados.cent[j]; //Valor do elemento - valor do centróide, ou seja, a distância do elemento até o centróide.
				if (dados.dist[j] < 0)
					dados.dist[j] = dados.dist[j] * -1;  //Corrige eventuais valores negativos.
			}
			indice = buscaMenor(dados, aux);          //Verifica para o elemento em questão qual o centróide mais próximo.
			vetorOut[i] = dados.cent[indice];      //Armazena em vetorOut o valor do centróide mais próximo.
			dados.soma[indice] = dados.soma[indice] + vetorIn[i];   //Guarda o valor da soma dos elementos associados a cada centróide.
			dados.conta[indice]++;   //Guarda o número de elementos associados a cada centróide.
		}
		for (i = 0; i < aux; i++)
		{
			if (dados.conta[i] != 0)           //Para evitar divisão por zero.
			{
				dados.cent[i] = dados.soma[i] / dados.conta[i];       //Atribui um novo valor para os centróides a partir da média aritmética.
			}
			if (dados.cent[i] != dados.centaux[i])  //Critério de parada. Verifica se houve mudanças nos valores dos centróides.
			{
				dados.centaux[i] = dados.cent[i];
				mudou = mudou + 1;
			}
		}
	}
	return 1;
}
