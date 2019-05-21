#include <vector>
#include <iostream>

using namespace std;

class data{
	public:
		long long int t;
		long long int m;
		long long int n;
		long long int p = 0; // atributo que irá receber a quantidade de combinações válidas possíveis
};
void leitura(data *d)
{
	long long int valor;
	cin >> valor;
	d->t = valor; // tamanho da combinação, nº de minutos
	cin >> valor;
	d->m = valor; // valor de dificuldade mínima
	cin >> valor;
	d->n = valor; // valor de dificuldade máxima
}
int ** alocar_matriz(int linhas,int colunas){ //Recebe a quantidade de linhas e colunas como Parâmetro
  	
  	int i,j;
	int **m = (int**)malloc(linhas * sizeof(int*)); //Aloca um Vetor de Ponteiros
	for (i = 0; i < linhas; i++)
	{ //Percorre as linhas do Vetor de Ponteiros
	   m[i] = (int*) malloc(colunas * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
	   for (j = 0; j < colunas; j++)
	   { //Percorre o Vetor de Inteiros atual.
	        m[i][j] = 0; //Inicializa com 0.
	   }
	}
	return m; //Retorna o Ponteiro para a Matriz Alocada
}
void inicializa_vetor_combinacoes(vector <int> *combinacoes, data *d)
{
	int valor = d->m;
	for(int i=0;i<combinacoes->size();i++)
	{
		combinacoes->at(i) = 0;
		valor++;
	}
}
int ginastica_pd(data *d, int i, int t)
{

	if(i < d->m || i > d->n) // aqui vai além dos limites do problema
	{
		return 0;
	}

	if(t == 1)
	{
		return 1;
	}
	long long int soma = (ginastica_pd(d, i-1, t-1) + ginastica_pd(d, i+1, t-1));
	return soma;
	
}
int main()
{
	data d;
	leitura(&d);
	long long int soma = 0;
	for(int i=d.m; i<=d.n; i++)
	{
		soma = ginastica_pd(&d, i, d.t) + soma;
	}
	cout << soma << "\n";
	return 0;
}