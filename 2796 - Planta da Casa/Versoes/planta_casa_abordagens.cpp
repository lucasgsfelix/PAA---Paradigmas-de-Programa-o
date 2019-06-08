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
/*int verifica_existencia_mesa(casa *c, int *comprimento, int *largura)
{
	// 1 se existe , 0 se não existe

	for(auto i=c->mesas.begin();i<c->mesas.end();i++)
	{
		if((c->mesas[i].comprimento == *comprimento && c->mesas[i].largura == *largura)||
			c->mesas[i].comprimento == *largura  && c->mesas[i].largura == *comprimento) //girando 90º
		{
			return 1;
		}
	}


	return 0;
}*/
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
	int i, j;
	int a = 0, l = 0, index = 0;
	for(i=0;i<c->mesas.size();i++)
	{
		for(j=0;j<pm->size();j++)
		{
			if((c->mesas[i].largura <= pm->at(j).largura && 
				c->mesas[i].comprimento <= pm->at(j).comprimento) ||
				(c->mesas[i].comprimento <= pm->at(j).largura && 
				c->mesas[i].largura <= pm->at(j).comprimento)) // aqui por causa dos 90º
			{
				if(c->mesas[i].area > a || (c->mesas[i].area == a && c->mesas[i].largura > l))
				{
					a = c->mesas[i].area;
					index = i;
					l = c->mesas[i].largura;
				}
			}
		}
	}
	cout << c->mesas[index].comprimento << " " << c->mesas[index].largura << "\n";
}
void monta_quarto_mesas(vector <mesa> *pontos_maximos, casa *c)
{
	int i, j, max_local = 0, max_area=0, index=0, largura_max=0;
	for(i=0;i<pontos_maximos->size();i++)
	{
		max_local = 0;
		for(j=0;j<c->mesas.size();j++)
		{
			if(c->mesas[j].area >= max_local && pontos_maximos->at(i).area >= c->mesas[j].area)
			{
				max_local = c->mesas[j].area;
				if(max_local >= max_area)
				{
					if((c->mesas[j].largura <= pontos_maximos->at(i).largura && 
					c->mesas[j].comprimento <= pontos_maximos->at(i).comprimento)||
					(c->mesas[j].comprimento <= pontos_maximos->at(i).largura && 
					c->mesas[j].largura <= pontos_maximos->at(i).comprimento))
					{
						if((max_local>max_area)||
							(max_local == max_area && c->mesas[j].largura > largura_max))
						{
							max_area = max_local;
							index = j;
							largura_max = c->mesas[j].largura;
						}
					}	
				}
			}
		}
	}

	cout << c->mesas[index].comprimento << " " << c->mesas[index].largura << "\n";
	/*for(i=0;i<pontos_maximos->size();i++)
	{
		for(j=0;j<pontos_maximos->at(i).mesas.size();j++)
		{
			if()
		}
	}*/

}
void verifica_mesas_quarto(vector <mesa> *pontos_maximos, casa *c, info_pontos *p)
{
	int max_ponto=0, max_largura=0, max_comprimento=0;
	vector <int> index_best{p->ia, p->il, p->ic};
	int aux_area = 0;
	int k=0, l=0, a=0, j, max_local, pi;
	for(int i=0;i<index_best.size();i++)
	{
		pi = index_best[i];
		max_local = 0;
		for(j=0;j<c->mesas.size();j++)
		{
			max_local = c->mesas[j].area;
			if(c->mesas[j].area >= max_local && 
			pontos_maximos->at(pi).area >= c->mesas[j].area)
			{
				cout << max_local <<" "<< a << "\n";
				if(max_local >= a)
				{
					if((c->mesas[j].comprimento <= pontos_maximos->at(pi).largura && 
					c->mesas[j].largura <= pontos_maximos->at(pi).comprimento)||
					(c->mesas[j].largura <= pontos_maximos->at(pi).largura && 
					c->mesas[j].comprimento <= pontos_maximos->at(pi).comprimento))
					{
						if((max_local>a)||(max_local == a && c->mesas[j].largura > l))
						{
							a = max_local;
							k = j;
							l = c->mesas[j].largura;
						}
					}	
				}
			}
		}
	}
	cout << c->mesas[k].comprimento << " " << c->mesas[k].largura << "\n";
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
	
	cin >> c->quant_mesas; // aqui estou lendo o número total de mesas
	for(i=0;i<c->quant_mesas;i++)
	{
		cin >> m.comprimento >> m.largura;
		m.area = m.comprimento * m.largura;
		if(m.area <= area_retangulo && ((m.comprimento <= p.c && m.largura <= p.l) || (m.largura <= p.c && m.comprimento <= p.l)))
		{
			c->mesas.push_back(m);
		}
	}
	//monta_quarto_mesas(&pontos_maximos, c);
	//verifica_mesas_quarto(&pontos_maximos, c, &p);
	
	seleciona_melhor(c, &pontos_maximos, area_retangulo);
}
int main()
{
	casa c; // objeto que irá armazenar a casa da entrada
	leitura_montagem_casa(&c);
	
	return 0;
}
