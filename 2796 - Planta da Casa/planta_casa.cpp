#include <iostream>
#include <vector>
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
		vector <mesa> mesas;
};

void alocar_matriz(int linhas, int colunas, casa *c)
{
 	/*
		Método responsável por realizar a alocação dinâmica de uma matriz
 	*/ 	

	c->m = (int**)malloc(linhas * sizeof(int*)); //Aloca um Vetor de Ponteiros	
	for (int i = 0; i < linhas; i++)
	{
		/*
			Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		*/
		c->m[i] = (int*) malloc(colunas * sizeof(int));
	  	
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
	alocar_matriz(c->comprimento_casa, c->largura_casa, c);
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
int max_area_histograma(casa *c, int k)
{
	/*
		Calcula a área máxima do histograma, esta área irá representar
		qual a área máxima que podemos colocar a mesa
	*/
	vector <int> valores; // vai ter o comportamento de um pilha
	int area = 0, area_maxima = 0, valor_topo, i=0;
	while(i<c->largura_casa)
	{
		if(valores.empty() || c->m[k][valores[valores.size()-1]] <= c->m[k][i])
		{
			valores.push_back(i++);
		}
		else
		{
			valor_topo = c->m[k][valores[valores.size()-1]];
			valores.pop_back(); // removendo o elemento do "topo da pilha"
			area =  valor_topo * i;

			if(! valores.empty())
			{
				area =  valor_topo * (i - valores[valores.size()-1] - 1);
			}
			area_maxima = max(area, area_maxima);
		}
	}
	return area_maxima;
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
	int area_retangulo = max_area_histograma(c, 0);

	for(i=1;i<c->comprimento_casa;i++)
	{
		for(j=0;j<c->largura_casa;j++)
		{
			if(c->m[i][j] == 1)
			{
				c->m[i][j] += c->m[i-1][j];
			}
		}
		area_retangulo = max(area_retangulo, max_area_histograma(c, i));
	}

	return area_retangulo;
}
int main()
{
	casa c; // objeto que irá armazenar a casa da entrada
	vector <char> buffer;
	leitura_montagem_casa(&buffer, &c);
	buffer.clear();//limpando buffer
	int area_retangulo = calcula_subareas_contiguas(&c);
	int i=0, melhor_solucao, aux_2, index_aux_single, aux;
	aux = area_retangulo-(c.mesas[0].comprimento * c.mesas[0].largura);
	for(i=1;i<c.mesas.size();i++)
	{ // aqui acha a melhor solução
		aux_2 = area_retangulo-(c.mesas[i].comprimento * c.mesas[i].largura);
		if(aux > aux_2 && aux >= 0 && aux_2 >= 0)
		{
			aux = aux_2;
			index_aux_single = i;
		}
		else if(aux_2 == aux)
		{
			if(c.mesas[index_aux_single].largura >= c.mesas[i].largura)
			{
				aux = aux_2;
				index_aux_single = i;
			}

		}
	}
	for(i=0;i<c.mesas.size();i++)
	{ // aqui verifica se há iguais
		aux_2 = area_retangulo-(c.mesas[i].comprimento * c.mesas[i].largura);
		if(aux == aux_2)
		{
			if(c.mesas[index_aux_single].largura < c.mesas[i].largura)
			{
				aux = aux_2;
				index_aux_single = i;
			}
		}
	}
	cout << c.mesas[index_aux_single].comprimento << " " << c.mesas[index_aux_single].largura << "\n";
	return 0;
}
