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
/*int verifica_existencia_mesa(casa *c, int *comprimento, int *largura)
{
	// 1 se existe , 0 se não existe

	for(auto i=c->mesas.begin();i<c->mesas.end();i++)
	{
		if(((*i).comprimento == *comprimento && (*i).largura == *largura)||
			(*i).comprimento == *largura  && (*i).largura == *comprimento) //girando 90º
		{
			return 1;
		}
	}


	return 0;
}*/
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
void verifica_mesas_quarto(vector <mesa> *pontos_maximos, casa *c)
{
	int max_ponto=0, max_largura=0, max_comprimento=0;
	int ip = 0, il = 0, ic = 0, i=0;

	for(i=0;i<pontos_maximos->size();i++)
	{
		if(pontos_maximos->at(i).area > max_ponto)
		{
			max_ponto = pontos_maximos->at(i).area;
			ip = i;
		}


		if(pontos_maximos->at(i).largura > max_largura)
		{
			max_largura = pontos_maximos->at(i).largura; 
			il = i;
		}

		if(pontos_maximos->at(i).comprimento > max_comprimento)
		{
			max_comprimento = pontos_maximos->at(i).comprimento;
			ic = i;
		}
	}
	vector <int> index_best{ip, il, ic};
	int aux_area = 0;
	int k=0, l=0, a=0; //index best, largura best, area best;
	int j, p, max_local;
	for(auto i=c->mesas.begin();i<c->mesas.end();i++)
	{
		if((*i).largura > max_largura || (*i).comprimento > max_comprimento)
		{
			c->mesas.erase(i);
		}
	}
	for(i=0;i<index_best.size();i++)
	{
		p = index_best[i];
		max_local = 0;
		for(j=0;j<c->mesas.size();j++)
		{
			if(c->mesas[j].area >= max_local && 
			pontos_maximos->at(p).area >= c->mesas[j].area)
			{
				max_local = c->mesas[j].area;
				if(max_local >= a)
				{
					if((c->mesas[j].largura <= pontos_maximos->at(p).largura && 
					c->mesas[j].comprimento <= pontos_maximos->at(p).comprimento)||
					(c->mesas[j].comprimento <= pontos_maximos->at(p).largura && 
					c->mesas[j].largura <= pontos_maximos->at(p).comprimento))
					{
						if((max_local>a)||
							(max_local == a && c->mesas[j].largura > l))
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
	for(i=0;i<c->quant_mesas;i++)
	{
		cin >> m.comprimento >> m.largura;
		m.area = m.comprimento * m.largura;
		if(m.area <= area_retangulo)
		{
			c->mesas.push_back(m);
		}
	}
	//monta_quarto_mesas(&pontos_maximos, c);
	verifica_mesas_quarto(&pontos_maximos, c);
	//seleciona_melhor(c, &pontos_maximos, area_retangulo);
}
int main()
{
	casa c; // objeto que irá armazenar a casa da entrada
	leitura_montagem_casa(&c);
	
	return 0;
}
