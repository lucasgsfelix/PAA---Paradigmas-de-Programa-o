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
		if((i.comprimento == *comprimento && i.largura == *largura)) //girando 90º
		{
			return 1;
		}
	}


	return 0;
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
	if(flag == 1)
	{
		m_aux.largura = largura;
	}
	else
	{
		m_aux.largura = i;
	}

	m_aux.area = m_aux.largura * m_aux.comprimento;
	pontos_maximos->push_back(m_aux);
	flag = 0;
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
	mesa m_aux;
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
	if(q[comprimento][largura].ocupada == 0 || 
	(q[comprimento][largura].ocupada == 1 && 
	(m->area > q[comprimento][largura].area ||
	m->area == q[comprimento][largura].area &&
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
void leitura_mesas(casa *c, mesa *p, int area_maxima, mesa **q, int tp)
{
	int i, max=0, l=0, com=0;
	mesa m;
	int mm=0, ll=0, cc=0;
	for(i=0;i<c->quant_mesas;i++)
	{
		cin >> m.comprimento >> m.largura;
		m.area = m.comprimento * m.largura;
		if(m.area <= area_maxima &&
		verifica_existencia_mesa(c, &m.comprimento, &m.largura) == 0)
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
				if(m.area > max || m.area == max && m.largura > ll)
				{
					max = m.area;
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
int main()
{

	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	casa c; // objeto que irá armazenar a casa da entrada
	vector <mesa> pontos_maximos;
	mesa p;

	//scanf("%i", &c.comprimento_casa); // lê o comprimento da casa
	//scanf("%i", &c.largura_casa); // lê a largura da casa
	cin >> c.comprimento_casa >> c.largura_casa;
	leitura_alocacao_casa(&c); // lê e aloca a casa
	
	int area_maxima = calcula_subareas_contiguas(&c, &pontos_maximos);

	calc_pontos_maximos(&pontos_maximos, &p, &c);

	//scanf("%i", &c.quant_mesas); // aqui estou lendo o número total de mesas
	
	int j, i, k;
	mesa m_aux;
	mesa **q = (mesa**)malloc((p.comprimento + 1) * sizeof(mesa*)); //Aloca um Vetor de Ponteiros	
	for (i = 0; i < p.comprimento + 1; i++)
	{
		/*
			Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		*/
		q[i] = (mesa*) malloc((p.largura + 1) * sizeof(mesa));
	  	for(j=0;j<p.largura + 1;j++)
	  	{
	  		q[i][j] = m_aux;
	  	}
	}
	int flag_break = 0;
	m_aux.existe = 1;
	for(i=0;i<pontos_maximos.size();i++)
	{
		if(pontos_maximos[i].comprimento * pontos_maximos[i].largura <= area_maxima
			&& pontos_maximos[i].comprimento > 0 && pontos_maximos[i].largura > 0)
		{
			for(j=pontos_maximos[i].comprimento;j>=0;j--)
			{
				for(k=pontos_maximos[i].largura;k>=0;k--)
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
	int tamanho_pontos = pontos_maximos.size();
	pontos_maximos.clear();
	cin >> c.quant_mesas;
	leitura_mesas(&c, &p, area_maxima, q, tamanho_pontos);
	return 0;
}
