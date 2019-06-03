#include <bits/stdc++.h> 

using namespace std;


struct mesa
{
	/*
		Classe responsável armazenar todas as mesas 
		que podem ser compradas por Isabel.
	*/
	int comprimento = 0;
	int largura = 0;
	int area;
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
		int quant_mesas = 0;
		int **m;
		vector <mesa> mesas;
};

void alocar_matriz(casa *c)
{
 	/*
		Método responsável por realizar a alocação dinâmica de uma matriz
 	*/ 	

	c->m = (int**)malloc(c->comprimento_casa * sizeof(int*)); //Aloca um Vetor de Ponteiros	
	for (int i = 0; i < c->comprimento_casa; i++)
	{
		/*
			Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		*/
		c->m[i] = (int*) malloc(c->largura_casa * sizeof(int));
	  	
	}

}
int verifica_existencia(vector <mesa> *pontos_maximos, int *comprimento, int *largura)
{
	// 1 se existe , 0 se não existe

	for(auto i=pontos_maximos->begin();i<pontos_maximos->end();i++)
	{
		if((*i).comprimento == *comprimento && (*i).largura == *largura)
		{
			return 1;
		}
	}


	return 0;
}
int max_area_histograma(casa *c, int k, vector <mesa> *pontos_maximos)
{
	/*
		Calcula a área máxima do histograma, esta área irá representar
		qual a área máxima que podemos colocar a mesa
	*/
	vector <int> valores; // vai ter o comportamento de um pilha
	int area = 0, valor_topo, i=0, flag = 0, area_maxima = 0;
	mesa m_aux;
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
				flag = 1;
			}
			if(area > area_maxima)
			{
				area_maxima = area;
				m_aux.comprimento = valor_topo;
				if(flag == 1)
				{
					m_aux.largura = ((i - valores[valores.size()-1] - 1));
					flag = 0;
				}
				else
				{
					m_aux.largura = i;
				}
				if(verifica_existencia(pontos_maximos, &m_aux.comprimento, &m_aux.largura) == 0)
				{
					m_aux.area = m_aux.largura * m_aux.comprimento;
					pontos_maximos->push_back(m_aux);	
				}
			}
		}
	}
	valores.clear();
	return area_maxima;
}
int calcula_subareas_contiguas(casa *c, vector <mesa> *pontos_maximos)
{
	/*
		Função responsável por calcular as 
		maiores subáreas contíguas que a casa possui,
		pois é lá que a mesa irá ficar.
		Este problema pode ser resolvido com programação dinâmica
		https://www.geeksforgeeks.org/maximum-size-rectangle-binary-sub-matrix-1s/
		Neste site a base de como foi calculado as subáreas contíguas
	*/
	int i, j, area_maxima = 0;
	max_area_histograma(c, 0, pontos_maximos);
	int area_maxima_antiga;
	for(i=1;i<c->comprimento_casa;i++)
	{
		for(j=0;j<c->largura_casa;j++)
		{
			if(c->m[i][j] == 1)
			{
				c->m[i][j] += c->m[i-1][j];
			}
		}
		area_maxima = max(area_maxima, max_area_histograma(c, i, pontos_maximos));
	}
	return area_maxima;
}
void seleciona_melhor(casa *c, vector <mesa> *pontos_maximos, int area_retangulo)
{
	int aux = (c->largura_casa * c->comprimento_casa);
	int aux_2, index_aux_single = 0, k=0;
	
	for(auto i=c->mesas.begin();i<c->mesas.end();i++)
	{
		for(auto j=pontos_maximos->begin();j<pontos_maximos->end();j++)
		{
			if((*i).area <= (*j).area)
			{ // obdece a restrição de área
				if(((*i).largura <= (*j).largura && 
					(*i).comprimento <= (*j).comprimento) ||
					((*i).comprimento <= (*j).largura && 
					(*i).largura <= (*j).comprimento)) // aqui por causa dos 90º
				{
					aux_2 = (*j).area - (*i).area;
					if(aux > aux_2)
					{
						aux = aux_2;
						index_aux_single = k;
					}
					else if(aux_2 == aux)
					{
						if (((*i).area > c->mesas[index_aux_single].area) || 
							((*i).largura > c->mesas[index_aux_single].largura &&
							(*i).area == c->mesas[index_aux_single].area))
						{
							aux = aux_2;
							index_aux_single = k;	
						}
					}
				}
			}
		}
		k++;
	}
	cout << c->mesas[index_aux_single].comprimento << " " << c->mesas[index_aux_single].largura << "\n";
}
void leitura_montagem_casa(casa *c)
{

	/*
		Realiza a leitura do arquivo de dados e montagem da casa
		A casa será armazenada em uma matriz
		As mesas em um vetor
		Os outros dados serão armazenados em tipos primitivos
	*/
	ios_base::sync_with_stdio(false); // Toggle off synchronization of all the C++ standard streams
    cin.tie(NULL);                    // Disable the flushing of std::cout before std::cin accepts an input
	int i = 0, j = 0, k = 0;
	char valor_aux; // redeclarando valor

	cin >> c->comprimento_casa >> c->largura_casa; // lê o comprimento da casa
	/*
		Alocando a matriz que será a casa
	*/
	alocar_matriz(c);

	for(i=0;i<c->comprimento_casa;i++)
	{
		for(j=0;j<c->largura_casa;j++)
		{
			cin >> valor_aux;
			if(valor_aux == '#')
			{
				c->m[i][j] = 0;
			}
			else
			{
				c->m[i][j] = 1;
			}
		}
	}
	vector <mesa> pontos_maximos;
	int area_retangulo = calcula_subareas_contiguas(c, &pontos_maximos);
	
	for(i=0;i<c->comprimento_casa;i++) // liberando espaço de memória
	{
		free(c->m[i]);
	}
	free(c->m);
	cin >> c->quant_mesas; // aqui estou lendo o número total de mesas
	//c->mesas.resize(c->quant_mesas);
	mesa m; // struct mesa temporario
	int lower = (area_retangulo*0.9);
	for(i=0;i<c->quant_mesas;i++)
	{
		cin >> m.comprimento >> m.largura;
		m.area = m.comprimento * m.largura;
		if(m.area <= area_retangulo && verifica_existencia(&c->mesas, &m.comprimento, &m.largura) == 0)
		{
			c->mesas.push_back(m);
		}
	}
	seleciona_melhor(c, &pontos_maximos, area_retangulo);
	
}
int main()
{
	casa c; // objeto que irá armazenar a casa da entrada
	leitura_montagem_casa(&c);
	
	return 0;
}
