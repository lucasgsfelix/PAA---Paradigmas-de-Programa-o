#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class data{
	public:
		long long int t;
		long long int m;
		long long int n;
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
long long int ** alocar_matriz(long long int linhas, long long int colunas){ //Recebe a quantidade de linhas e colunas como Parâmetro
  	
  	long long int i,j;
	long long int **m = (long long int**)malloc(linhas * sizeof(long long int*)); //Aloca um Vetor de Ponteiros
	for (i = 0; i < linhas; i++)
	{ //Percorre as linhas do Vetor de Ponteiros
	   m[i] = (long long int*) malloc(colunas * sizeof(long long int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
	   for (j = 0; j < colunas; j++)
	   { //Percorre o Vetor de Inteiros atual.
	        m[i][j] = 1; //Inicializa com 0.
	   }
	}
	return m; //Retorna o Ponteiro para a Matriz Alocada
}
int ginastica_pd(data *d)
{
	long long int i, j, tamanho_coluna = d->n - d->m + 1, soma = 0;
	long long int iter_aux_i = 0, iter_aux_j = 1, aux = 0;
	long long int **m = alocar_matriz(d->t, tamanho_coluna);
	long long int mod = pow(10, 9) + 7;
	for(i=1;i<d->t;i++)
	{
		for(j=1;j<tamanho_coluna;j++)
		{
			m[iter_aux_j][j] = (m[iter_aux_i][j-1] + m[iter_aux_i][j+1]) % mod;
		}
		m[iter_aux_j][0] = m[iter_aux_i][1];
		m[iter_aux_j][tamanho_coluna-1] = m[iter_aux_i][tamanho_coluna - 2];

		aux = iter_aux_i;
		iter_aux_i = iter_aux_j;
		iter_aux_j = aux;
	}

	cout << iter_aux_i << "\n";
	for(i=0;i<d->t;i++)
	{
		soma = 0;
		for(j=0;j<tamanho_coluna;j++)
		{
			soma = (m[iter_aux_i][j] + soma) % mod;
		}
		//cout << soma << "\n";
	}
		
	
	return soma;

}
int main()
{
	data d;
	leitura(&d);
	cout << ginastica_pd(&d);
	

	return 0;
}