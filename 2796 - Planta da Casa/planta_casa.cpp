#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class mesa
{
	/*
		Classe responsável armazenar todas as mesas 
		que podem ser compradas por Isabel.
	*/
	public:
		int comprimento = 0;
		int largura = 0;
		/*
			Essa terá que ter duas versões uma normal
			e outra que roda 90º
		*/
};
class casa
{
	/*
		Classe responsável por armazenar os dados da casa,
		além de guardar um mapa do mesmo.
	*/
	public: 
		int comprimento_casa = 0;
		int largura_casa = 0;
		int quantidade_mesas = 0;
		int **m;
		int **s; //irá armazenar a soma
		vector <mesa> mesas;
};

void alocar_matriz(int linhas, int colunas, casa *c, int flag)
{
 	/*
		Método responsável por realizar a alocação dinâmica de uma matriz
 	*/ 	
 	if(flag == 0)
 	{
		c->m = (int**)malloc(linhas * sizeof(int*)); //Aloca um Vetor de Ponteiros	
 	}
 	else
 	{
 		c->s = (int**)malloc(linhas * sizeof(int*)); //Aloca um Vetor de Ponteiros
 	}
	for (int i = 0; i < linhas; i++)
	{
		/*
			Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		*/
		if(flag == 0)
		{
			c->m[i] = (int*) malloc(colunas * sizeof(int));
		}
		else
		{
			c->s[i] = (int*) malloc(colunas * sizeof(int));
		}
	  	
	}

}
void leitura_montagem_casa(vector <char> *buffer, casa *c)
{

	/*
		Realiza a leitura do arquivo de dados e montagem da casa
		A casa será armazenada em uma matriz
		As mesas em um vetor
		Os outros dados serão armazenados em tipos primitivos
	*/
	int i = 0, j = 0, k = 0, valor;
	char valor_aux; // redeclarando valor

	cin >> valor; // lê o comprimento da casa
	c->comprimento_casa = valor;
	cin >> valor; // lê a largura da casa
	c->largura_casa = valor;
	/*
		Alocando a matriz que será a casa
	*/
	alocar_matriz(c->comprimento_casa, c->largura_casa, c, 0);
	while(i < c->largura_casa * c->comprimento_casa)
	{
		/*
			Esta etapa monta o mapa da casa

		*/
		cin >> valor_aux;
		if(valor_aux == '#')
		{
			c->m[k][j] = 0;
		}
		else if(valor_aux=='.')
		{
			c->m[k][j] =1;
		}
		//cout << c->m[k][j] << ",";
		i++;
		j++;
		if(j == c->largura_casa)
		{
			j = 0;
			k++;
		}
	}
	cin >> valor; // aqui estou lendo o número total de mesas
	c->quantidade_mesas = valor;
	mesa m; // objeto mesa temporario
	i = 0;
	while(i<c->quantidade_mesas)
	{
		/* Armazenando Mesas */
		cin >> valor;
		m.comprimento = valor; // largura de uma mesa
		cin >> valor;
		m.largura = valor; // comprimento de uma mesa
		c->mesas.push_back(m); // adicionando na lista de mesas
		i++;
	}

}
int calcula_subareas_contiguas(casa *c)
{
	/*
		Função responsável por calcular as 
		maiores subáreas contíguas que a casa possui,
		pois é lá que a mesa irá ficar.
		Este problema pode ser resolvido com programação dinâmica
		https://www.geeksforgeeks.org/maximum-size-rectangle-binary-sub-matrix-1s/
		Neste site a base de como foi calculado as subáreas contíguas
	*/
	int i, j;

	alocar_matriz(c->comprimento_casa, c->largura_casa, c, 1); // alocando a matriz de soma
	/*
		Inicializando primeira linha e primeira coluna
	*/
	for(i=0;i<c->comprimento_casa;i++)
	{
		c->s[i][0] = c->m[i][0]; //copiando a primeira coluna
	}
	for(i=0;i<c->largura_casa;i++)
	{
		c->s[0][i] = c->m[0][i]; //copiando a primeira linha
	}


	for(i=1;i<c->comprimento_casa;i++)
	{
		for(j=1;j<c->largura_casa;j++)
		{
			if(c->m[i][j] == 1)
			{
				//c->s[i][j] = min(c->s[i][j-1], min(c->s[i-1][j], c->s[i-1][j-1])) + 1;
				c->s[i][j] += c->s[i-1][j] + 1;
			}
			else
			{
				c->s[i][j] = 0;
			}
			cout << c->s[i][j];
		}
		cout << "\n";
	}

	/*
		Selecionando e salvando o melhor valor e index das linhas
	*/
	int best_i, best_j, local_best = c->s[0][0];
	for(i=0;i<c->comprimento_casa;i++)
	{
		for(j=0;j<c->largura_casa;j++)
		{
			if(local_best < c->s[i][j])
			{
				local_best = c->s[i][j];
				best_i = i;
				best_j = j;
			}
		}
	}
	cout << "Local Best: " << local_best << "\n";
	cout << best_i << " " << best_i - local_best << "\n";
	int comprimento = best_i - (best_i-local_best);
	cout << comprimento << "\n";
	cout << best_j << " " << best_j - local_best << "\n";
	int largura = best_j - (best_j - local_best);
	cout << largura << "\n";
	
	return 0;
}
int main()
{
	casa c; // objeto que irá armazenar a casa da entrada
	vector <char> buffer;
	leitura_montagem_casa(&buffer, &c);
	buffer.clear();//limpando buffer
	calcula_subareas_contiguas(&c);


	return 0;
}
