#include <iostream>
#include <vector>
#include <stack>
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
	int existe = 0;
	int ocupada = 0;
	//vector <int> mesas; // irá guardar o index das mesas que cabem
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
int calculo_areas(stack <int> *valores, int area_maxima, int i, vector <mesa> *pontos_maximos, int *m)
{
	int valor_topo, area, flag, largura;
	mesa m_aux;

	valor_topo = m[valores->top()];
	valores->pop(); // removendo o elemento do "topo da pilha"
	area =  valor_topo * i;
	flag = 0;

	if(! valores->empty())
	{
		largura = (i - valores->top() - 1);
		area =  valor_topo * largura;
		flag = 1;
	}
	
	if(area > area_maxima)
		area_maxima = area;

	m_aux.comprimento = valor_topo;
	m_aux.area = area;

	if(flag == 1)
		m_aux.largura = largura;
	else
		m_aux.largura = i;
	
	pontos_maximos->push_back(m_aux);
	
	return area_maxima;

}
int max_area_histograma(int *m, int largura_casa, vector <mesa> *pontos_maximos)
{
	/*
		Calcula a área máxima do histograma, esta área irá representar
		qual a área máxima que podemos colocar a mesa
	*/
	stack <int> valores; // vai ter o comportamento de um pilha
	int i=0, area_maxima = 0;
	while(i<largura_casa)
	{
		if(valores.empty() || m[valores.top()] <= m[i])
		{
			valores.push(i++);
		}
		else
		{
			area_maxima = calculo_areas(&valores, area_maxima, i, pontos_maximos, m);
		}
	}
	int area_aux = area_maxima;
	vector <mesa> aux_pm;
	
	while (!valores.empty()) 
    {
    	area_aux = calculo_areas(&valores, area_aux, i, &aux_pm, m);
    }
    if(area_aux >= area_maxima)
    {
    	area_maxima = area_aux;
    	for(auto const &j:(aux_pm))
    	{
    		pontos_maximos->push_back(j);
    	}
    }
    
    stack<int>().swap(valores);
    aux_pm.clear();
	
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
	max_area_histograma(c->m[0], c->largura_casa, pontos_maximos);
	for(i=1;i<c->comprimento_casa;i++)
	{
		for(j=0;j<c->largura_casa;j++)
		{
			if(c->m[i][j] == 1)
			{
				c->m[i][j] += c->m[i-1][j];
			}
		}
		area_maxima = max(area_maxima, max_area_histograma(c->m[i], 
			c->largura_casa, pontos_maximos));
	}
	for(i=0;i<c->comprimento_casa;i++) // liberando espaço de memória
	{
		free(c->m[i]);
	}
	free(c->m);

	if(area_maxima == 0)
	{
		area_maxima = c->comprimento_casa * c->largura_casa;
	}

	return area_maxima;
}

void leitura_alocacao_casa(casa *c)
{
	/*
		Alocando a matriz que será a casa
	*/ 
	int i, j;
	char valor_aux;
	alocar_matriz(c);
	for(i=0;i<c->comprimento_casa;i++)
	{
		for(j=0;j<c->largura_casa;j++)
		{
			//scanf(" %c", &valor_aux);
			cin >> valor_aux;
			if(valor_aux == '#')
			{
				c->m[i][j] = 0;
			}
		}
	}
}
void posiciona_mesa(mesa **q, mesa *m, int comprimento, int largura, int *mm, int *ll, int *cc, int flag)
{
	int com=0, l=0, max=0;
	if(q[comprimento][largura].ocupada == 0 || (q[comprimento][largura].ocupada == 1 && 
	(m->area > q[comprimento][largura].area || m->area == q[comprimento][largura].area &&
	largura > q[comprimento][largura].largura)))
	{
		m->ocupada = 1;
		m->existe = 1;
		com = comprimento;
		l = largura;
		max = m->area;
		q[comprimento][largura] = *m;
		if((max > *mm  || max == *mm && l > *ll))
		{
			*mm = max;
			if(flag == 0)
			{
				*ll = l;
				*cc = com;
			}
			else
			{
				*ll = com;
				*cc = l;
			}
		}
	}
}
void leitura_mesas(casa *c, mesa *p, int area_maxima, mesa *q[], int tp)
{
	mesa m;
	int mm=0, ll=0, cc=0;
	for(int i=0;i<c->quant_mesas;i++)
	{
		cin >> m.comprimento >> m.largura;
		m.area = m.comprimento * m.largura;
		if(m.area <= area_maxima)
		{
			if(tp!=0)
			{
				if(m.comprimento <= p->comprimento && m.largura <= p->largura &&
					q[m.comprimento][m.largura].existe == 1)
				{
					posiciona_mesa(q, &m, m.comprimento, m.largura, &mm, &ll, &cc, 0);
				}
				else if(m.largura <= p->comprimento && m.comprimento <= p->largura &&
					q[m.largura][m.comprimento].existe == 1)
				{
					posiciona_mesa(q, &m, m.largura, m.comprimento, &mm, &ll, &cc, 1);
				}
			}
			else
			{
				if(m.area > mm || m.area == mm && m.largura > ll)
				{
					mm = m.area;
					ll = m.largura;
					cc = m.comprimento;
				}
			}
		}
	}
	cout << cc << " " << ll << "\n";
}
void calc_pontos_maximos(vector <mesa> *pontos_maximos, mesa *p, casa *c)
{
	if(pontos_maximos->size() > 0)
	{
		for(auto const &i:(*pontos_maximos))
		{
			if(p->largura < i.largura)
			{
				p->largura = i.largura;
			}

			if(p->comprimento < i.comprimento)
			{
				p->comprimento = i.comprimento;
			}

			if(p->area < i.area)
			{
				p->area = i.area;
			}
		}
	}
	else
	{
		p->area = c->comprimento_casa * c->largura_casa;
		p->comprimento = c->comprimento_casa;
		p->largura = c->largura_casa;
	}
}
mesa **alocar_matriz_quartos(mesa *p)
{
	mesa m_aux;
	mesa **q = (mesa**)malloc((p->comprimento + 1) * sizeof(mesa*)); //Aloca um Vetor de Ponteiros	
	for (int i = 0; i < p->comprimento + 1; i++)
	{
		q[i] = (mesa*) malloc((p->largura + 1) * sizeof(mesa));
	  	for(int j=0;j<p->largura + 1;j++)
	  	{
	  		q[i][j] = m_aux;
	  	}
	}
	return q;
}
void preenche_matriz(vector <mesa> *pontos_maximos, mesa *q[], int area_maxima)
{
	int j, i, k;
	mesa m_aux;
	
	m_aux.existe = 1;
	
	for(auto const &i:(*pontos_maximos))
	{
		if(i.comprimento * i.largura <= area_maxima && i.comprimento > 0 && i.largura > 0)
		{
			for(j=i.comprimento;j>=0;j--)
			{
				for(k=i.largura;k>=0;k--)
				{
					if(q[j][k].existe == 1)
					{
						break;
					}
					q[j][k] = m_aux;
				}
			}
		}
	}
}
int main()
{

	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	casa c; // objeto que irá armazenar a casa da entrada
	vector <mesa> pontos_maximos;
	mesa p;

	cin >> c.comprimento_casa >> c.largura_casa;
	leitura_alocacao_casa(&c); // lê e aloca a casa
	
	int area_maxima = calcula_subareas_contiguas(&c, &pontos_maximos);

	calc_pontos_maximos(&pontos_maximos, &p, &c);
	
	mesa **q = alocar_matriz_quartos(&p);
	preenche_matriz(&pontos_maximos, q, area_maxima);
	
	int tamanho_pontos = pontos_maximos.size();
	pontos_maximos.clear();

	cin >> c.quant_mesas;
	leitura_mesas(&c, &p, area_maxima, q, tamanho_pontos);
	
	for(int i=0;i<p.comprimento;i++) // liberando espaço de memória
	{
		free(q[i]);
	}
	free(q);

	return 0;
}
