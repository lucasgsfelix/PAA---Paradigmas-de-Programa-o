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
int max_area_histograma(int *m, int largura_casa, vector <mesa> *pontos_maximos)
{
	/*
		Calcula a área máxima do histograma, esta área irá representar
		qual a área máxima que podemos colocar a mesa
	*/
	stack <int> valores; // vai ter o comportamento de um pilha
	int area = 0, valor_topo, i=0, flag = 0, area_maxima = 0, largura = 0;
	mesa m_aux;
	while(i<largura_casa)
	{
		if(valores.empty() || m[valores.top()] <= m[i])
		{
			valores.push(i++);
		}
		else
		{
			valor_topo = m[valores.top()];
			valores.pop(); // removendo o elemento do "topo da pilha"
			area =  valor_topo * i;

			if(! valores.empty())
			{
				largura = (i - valores.top() - 1);
				area =  valor_topo * largura;
				flag = 1;
			}
			if(area > area_maxima)
			{
				area_maxima = area;
				m_aux.comprimento = valor_topo;
				if(flag == 1)
				{
					m_aux.largura = largura;
					flag = 0;
				}
				else
				{
					m_aux.largura = i;
				}
				m_aux.area = m_aux.largura * m_aux.comprimento;
				pontos_maximos->push_back(m_aux);
				/*if(verifica_existencia(pontos_maximos, &m_aux.comprimento, &m_aux.largura) == 0)
				{
					m_aux.area = m_aux.largura * m_aux.comprimento;
					pontos_maximos->push_back(m_aux);
				}*/
			}
		}
	}
	while (!valores.empty()) 
    { 
        valor_topo = m[valores.top()]; 
        valores.pop(); 
        area = valor_topo * i; 
        if (!valores.empty()) 
        	largura = valor_topo * (i - valores.top() - 1 ); 
            area = largura;
        	flag = 1;
  
        if(area > area_maxima)
		{
			area_maxima = area;
			m_aux.comprimento = valor_topo;
			if(flag == 1)
			{
				m_aux.largura = largura;
				flag = 0;
			}
			else
			{
				m_aux.largura = i;
			}
			m_aux.area = m_aux.largura * m_aux.comprimento;
			pontos_maximos->push_back(m_aux);
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
void seleciona_melhor(casa *c, vector <mesa> *pm)
{
	int a = 0, l = 0, index = 0, k=0;
	for(auto i=c->mesas.begin();i < c->mesas.end();i++)
	{
		for(auto const &j:(*pm)) // aqui está sendo avaliados os quartos
		{
			if(((*i).largura <= j.largura && 
				(*i).comprimento <= j.comprimento) ||
				((*i).comprimento <= j.largura && 
				(*i).largura <= j.comprimento)) // aqui por causa dos 90º
			{
				if((*i).area > a || ((*i).area == a && (*i).largura > l))
				{
					a = (*i).area;
					index = k;
					l = (*i).largura;
				}
			}
		}
		k++;
	}
	cout << c->mesas[index].comprimento << " " << c->mesas[index].largura << "\n";
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
void leitura_mesas(casa *c, mesa *p, int area_maxima)
{
	int i;
	mesa m;
	for(i=0;i<c->quant_mesas;i++)
	{
		cin >> m.comprimento >> m.largura;
		m.area = m.comprimento * m.largura;
		if((m.area <= area_maxima &&
		(m.comprimento <= p->comprimento && m.largura <= p->largura ||
		m.largura <=p->comprimento && m.comprimento <= p->largura) &&
		verifica_existencia_mesa(c, &m.comprimento, &m.largura) == 0))
		{
			c->mesas.push_back(m);
		}
	}
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
	cin >> c.quant_mesas;

	leitura_mesas(&c, &p, area_maxima);
	if(pontos_maximos.size() != 0) // a casa não possui paredes
	{
		seleciona_melhor(&c, &pontos_maximos);
	}
	else
	{
		int max = 0, l = 0, com = 0;
		for(auto const &i:(c.mesas))
		{
			if(i.area > max || i.area == max && l < i.largura)
			{
				max = i.area;
				l = i.largura;
				com = i.comprimento;
			}
		}
		cout << com << " " << l << "\n";
	}

	
	return 0;
}
