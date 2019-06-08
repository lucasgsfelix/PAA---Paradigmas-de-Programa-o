#include <iostream>
#include <vector>
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
	int ocupada  = 0;
	int existe = 0;
	//vector <int> mesas; // irá guardar o index das mesas que cabem
};
struct info_pontos
{
	/*
		Vai conter informações sobre os pontos que representam as salas 
	*/
	int il = 0; // index largura
	int ic = 0; // index comprimento
	int ia = 0; // index area
	int l = 0; // maior largura
	int a = 0; // maior area
	int c = 0; // maior comprimento
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
	int j;
	for (int i = 0; i < c->comprimento_casa; i++)
	{
		/*
			Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		*/
		c->m[i] = (int*) malloc(c->largura_casa * sizeof(int));

	  	for(j=0;j<c->largura_casa;j++)
	  	{
	  		c->m[i][j] = 1;
	  	}
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
int verifica_existencia_mesa(casa *c, int *comprimento, int *largura)
{
	// 1 se existe , 0 se não existe

	for(auto &i:c->mesas)
	{
		if((i.comprimento == *comprimento && i.largura == *largura)||
			i.comprimento == *largura  && i.largura == *comprimento) //girando 90º
		{
			return 1;
		}
	}


	return 0;
}
int max_area_histograma(casa *c, int k, vector <mesa> *pontos_maximos, info_pontos *p)
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
					if(m_aux.area > p->a)
					{
						p->a = m_aux.area;
						p->ia = pontos_maximos->size()-1;
					}
					if(m_aux.comprimento > p->c)
					{
						p->c = m_aux.comprimento;
						p->ic = pontos_maximos->size()-1;
					}
					if(m_aux.largura > p->l)
					{
						p->l = m_aux.largura;
						p->il = pontos_maximos->size()-1;
					}
				}
			}
		}
	}
	valores.clear();
	return area_maxima;
}
int calcula_subareas_contiguas(casa *c, vector <mesa> *pontos_maximos, info_pontos *p)
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
	max_area_histograma(c, 0, pontos_maximos, p);
	for(i=1;i<c->comprimento_casa;i++)
	{
		for(j=0;j<c->largura_casa;j++)
		{
			if(c->m[i][j] == 1)
			{
				c->m[i][j] += c->m[i-1][j];
			}
		}
		area_maxima = max(area_maxima, max_area_histograma(c, i, pontos_maximos, p));
	}
	return area_maxima;
}
void seleciona_melhor(casa *c, vector <mesa> *pm, int area_retangulo)
{
	int a = 0, l = 0, index = 0, k=0;
	for(auto const &i:c->mesas)
	{
		for(auto const &j:(*pm))
		{
			if((i.largura <= j.largura && 
				i.comprimento <= j.comprimento) ||
				(i.comprimento <= j.largura && 
				i.largura <= j.comprimento)) // aqui por causa dos 90º
			{
				if(i.area > a || (i.area == a && i.largura > l))
				{
					a = i.area;
					index = k;
					l = i.largura;
				}
			}
		}
		k++;
	}
	cout << c->mesas[index].comprimento << " " << c->mesas[index].largura << "\n";
}
void leitura_montagem_casa(casa *c)
{

	/*
		Realiza a leitura do arquivo de dados e montagem da casa
		A casa será armazenada em uma matriz
		As mesas em um vetor
		Os outros dados serão armazenados em tipos primitivos
	*/
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);                   
	
	int i, j;
	char valor_aux; // redeclarando valor
	mesa m; // struct mesa temporario

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
		}
	}
	vector <mesa> pontos_maximos;
	info_pontos p;
	
	
	int area_retangulo = calcula_subareas_contiguas(c, &pontos_maximos, &p);

	for(i=0;i<c->comprimento_casa;i++) // liberando espaço de memória
	{
		free(c->m[i]);
	}
	free(c->m);

	mesa **m_pontos = (mesa**)malloc((p.c + 1) * sizeof(mesa*)); //Aloca um Vetor de Ponteiros	
	for (i = 0; i < p.c + 1; i++)
	{
		m_pontos[i] = (mesa*) malloc((p.l + 1) * sizeof(mesa));
	}
	mesa p_aux;
	
	for(i=0; i < pontos_maximos.size();i++)
	{
		p_aux.existe = 1;
		m_pontos[pontos_maximos[i].comprimento][pontos_maximos[i].largura] = p_aux;
	}
	pontos_maximos.clear();

	cin >> c->quant_mesas;// >> c->quant_mesas; // aqui estou lendo o número total de mesas
	for(i=0;i<c->quant_mesas;i++)
	{
		cin >> m.comprimento >> m.largura;
		m.area = m.comprimento * m.largura;
		if(m.comprimento < (p.c + 1) && m.largura < (p.l + 1))
		{
			if(m_pontos[m.comprimento][m.largura].existe == 1)
			{
				if((m.area > m_pontos[m.comprimento][m.largura].area) &&
				(m_pontos[m.comprimento][m.largura].ocupada == 1 &&
				(m.area == m_pontos[m.comprimento][m.largura].area &&
				m.largura > m_pontos[m.comprimento][m.largura].largura)))
				{
					m.existe = 1;
					m.ocupada = 1;
					m_pontos[m.comprimento][m.largura] = m;
				}
			}
		}
	}
	int flag = 0;
	int maior_area = p.l * p.c;
	for(j=p.l;j>0;j--)
	{
		
		if(flag==1)
		{
			break;
		}
	}
	//seleciona_melhor(c, &pontos_maximos, area_retangulo);
}
int main()
{
	casa c; // objeto que irá armazenar a casa da entrada
	leitura_montagem_casa(&c);
	
	return 0;
}
