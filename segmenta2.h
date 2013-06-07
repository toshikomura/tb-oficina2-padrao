typedef struct estrutura
{
	int *cent;			//armazena os valores dos centróides
	int *conta;		//quantos elementos estão associados a determinado centróide
	int *soma;		//a soma dos valores dos elementos associados ao mesmo centróide
	int *centaux;		//variável auxiliar usada no critério de parada
	int *dist;			//guarda a distância do elemento até cada um dos centróides
}tipoS;
int buscaMenor(tipoS dados, int aux);
int segmenta(int *vetorIn, int *vetorOut, int linhas ,int colunas, int max, int aux);
