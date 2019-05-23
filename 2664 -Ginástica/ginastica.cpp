#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class dados{
	// Classe responsável por armazenar os dados
	public:
		long long int t; // tempo que será realizado essas atividades
		long long int m; // dificuldade mínima
		long long int n; // dificuldade máxima
};
void leitura(dados *d)
{
	/*
		Método responsável por realizar a leitura de dados
	*/
	long long int valor;
	cin >> valor;
	d->t = valor; // tamanho da combinação, nº de minutos
	cin >> valor;
	d->m = valor; // valor de dificuldade mínima
	cin >> valor;
	d->n = valor; // valor de dificuldade máxima
}
long long int ** alocar_matriz(long long int linhas, long long int colunas)
{
 	/*
		Método responsável por realizar a alocação dinâmica de uma matriz
 	*/ 	
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
long long int sum(long long int **m, long long int tamanho_coluna, long long int iter_aux_i)
{
	long long int soma = 0;
	for(int j=0;j<tamanho_coluna;j++)
	{
		/*
			Somando a quantidade de possibilidades total que respeita as restrições
		*/
		soma = (m[iter_aux_i][j] + soma);
	}
	return soma;
}
int ginastica_pd(dados *d)
{
	/*
		Para a resolução problema da ginastica foi utilizado um método
		programação dinâmica.

		O método implementado calculo a quantidade possíveis combinações
		para cada instante de tempo. Este método se mostrou mais apropriado
		que a resolução apenas por recursão (indução), pois armazena os valores
		na matriz. Desta maneira, não era necessário o recalculo para atingir um
		determinado valor tornando o tempo de execução menor.

		A complexidade deste algoritmo é O(t*tamanho_coluna). Onde t é a quantidade
		de tempo que irá ser feito uma atividade e o tamanho da coluna resume a
		quantidade de atividades totais que podem ser realizadas em determinado
		período de tempo.

	*/
	long long int i, j, tamanho_coluna = d->n - d->m + 1, soma = 0;
	long long int iter_aux_i = 0, iter_aux_j = 1, aux = 0;

	long long int **m = alocar_matriz(d->t, tamanho_coluna); // chama a alocação de matrizes
	/*
		Calcula o mod para dividir os números 
		os quais podem ser muito grandes
		tornando inviável o cálculo simples.
	*/
	long long int mod = pow(10, 9) + 7;

	for(i=1;i<d->t;i++)
	{
		for(j=1;j<tamanho_coluna;j++)
		{
			/*
				Calculando a quantidade de combinações que cada valor por receber em um 
				instante de tempo t
			*/
			m[iter_aux_j][j] = (m[iter_aux_i][j-1] + m[iter_aux_i][j+1]);
			/*
				Dividindo pelo mod para evitar problema com números muito grandes
			*/
			m[iter_aux_j][j] = m[iter_aux_j][j] % mod;  
		}
		/*
			Salvando valores que serão armazenados na tabela
		*/
		m[iter_aux_j][0] = m[iter_aux_i][1];
		m[iter_aux_j][tamanho_coluna-1] = m[iter_aux_i][tamanho_coluna - 2];

		/*
			lógica de variáveis auxiliares para guardar posições
		*/
		aux = iter_aux_i;
		iter_aux_i = iter_aux_j;
		iter_aux_j = aux;
	}

	/*
		Dividindo pelo mod para evitar problema com números muito grandes
	*/
	return sum(m, tamanho_coluna, iter_aux_i) % mod;

}
int main()
{
	dados d;
	leitura(&d);
	
	if(! d.t < 1 or d.t>50 or d.m < 1 or d.n < 1 or d.m > pow(10, 5) or d.n > pow(10, 5))
	{
		/*
			Avalia para que não passe parâmetros inválidos
		*/
		
		int s = ginastica_pd(&d); // chamada para instância a programação dinâmica para este problema
		
		cout << s << "\n"; // imprime solução final
	}
		

	return 0;
}