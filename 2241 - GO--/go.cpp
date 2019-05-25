#include <iostream>
#include <vector>

using namespace std;

class pecas
{
	/*
		Irá armazenar as coordenadas das peças dos jogadores
	*/
	public:
		int x = 0;
		int y = 0;
};
class coordenadas
{
	/*
		Irá armazenar as coordenadas que depois serão avaliadas;
	*/
	public:
		int x_inicial = 0;
		int x_final = 0;
		int y_inicial = 0;
		int y_final = 0;
};
class jogadores
{
	/*
		Classe responsável por armazenar os dados dos jogadores
	*/
	public:
		int dimensao_tab = 0; // na definição é n
		int quant_pedras = 0; // na definição é p
		int **tabuleiro; // a matriz que irá armazenar as peças
		vector <pecas> pretas; // armazena as peças pretas
		vector <pecas> brancas; // armazena as peças brancas
		int pontuacao_preto = 0;
		int pontuacao_branco = 0;
};
void alocar_matriz(int linhas, int colunas, jogadores *j)
{
 	/*
		Método responsável por realizar a alocação dinâmica de uma matriz
 	*/ 	

	j->tabuleiro = (int**)malloc(linhas * sizeof(int*)); //Aloca um Vetor de Ponteiros	
	for (int i = 0; i < linhas; i++)
	{
		/*
			Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		*/
		j->tabuleiro[i] = (int*) malloc(colunas * sizeof(int));
		for(int k=0; k<colunas; k++)
		{
			j->tabuleiro[i][k] = 0; // deixando o tabuleiro vazio
		}
	  	
	}

}
void leitura_montagem_dados(jogadores *j)
{
	/*
		Método responsável pela leitura e montagem dos dados dos jogadores
	*/
	pecas p;
	cin >> j->dimensao_tab; // lendo a dimensao do tabuleiro
	cin >> j->quant_pedras; // lendo a quantidade de pedras no tabuleiro
	/*
		Armazenando dados de peças pretas
	*/
	alocar_matriz(j->dimensao_tab, j->dimensao_tab, j);
	for(int i=0;i<j->quant_pedras;i++)
	{
		cin >> p.x;
		cin >> p.y;
		j->tabuleiro[p.x-1][p.y-1] = 1; // peças pretas
		j->pretas.push_back(p);
	}
	/*
		Armazenando dados de peças brancas
	*/
	for(int i=0;i<j->quant_pedras;i++)
	{
		cin >> p.x;
		cin >> p.y;
		j->tabuleiro[p.x-1][p.y-1] = 2; // peças brancas
		j->brancas.push_back(p);
	}
}
void somando_dimensoes(jogadores *j)
{
	/*
		Método responsável por fazer as principais computações que 
		irão definir a pontuação do jogador.
		Para isso é utilizado um quadrado de dimensão N que varia e verifica
		quais são as peças que há nas subáreas quadráticas. 
	*/
	int k, l;
	vector <coordenadas> c_list;
	coordenadas c;
	for(int i=0;i<j->dimensao_tab-1;i++)
	{
		for(k=0;k<j->dimensao_tab;k++)
		{
			for(l=0;l<j->dimensao_tab;l++)
			{
				c.y_inicial = k;
				c.y_final = i+k;
				c.x_inicial = l;
				c.x_final = i+l;
				if(k <= j->dimensao_tab && i+k <= j->dimensao_tab
					&& l <= j->dimensao_tab && i+l <= j->dimensao_tab)
				{
					c_list.push_back(c); // adicionando na lista de coordenadas

				}
			}
		}
	}

	int soma_pretos;
	int soma_brancos;
	for(int i=0;i<c_list.size();i++)
	{
		soma_brancos = 0;
		soma_pretos = 0;
		for(k=c_list[i].x_inicial;k<c_list[i].x_final;k++)
		{
			for(l=c_list[i].y_inicial;l<c_list[i].y_final;l++)
			{
				if(j->tabuleiro[k][l] == 0)
					continue;

				if(j->tabuleiro[k][l] == 1) // pretos
				{
					soma_pretos++;
				}
				else if(j->tabuleiro[k][l] == 2) // brancos
				{
					soma_brancos++;
				}
				if(soma_brancos > 1 && soma_pretos > 1)
				{
					break;
				}
			}
		}
		if(soma_brancos == 0 && soma_pretos > 0)
		{ // tem apenas pretos
			j->pontuacao_preto = j->pontuacao_preto + 1;
		}
		else if(soma_pretos == 0 && soma_brancos > 0)
		{
			j->pontuacao_branco = j->pontuacao_branco + 1;
		}
	}
	c_list.clear();
}

int main()
{
	jogadores j;
	leitura_montagem_dados(&j); // também monta o tabuleiro
	somando_dimensoes(&j);
	if (j.pontuacao_preto == 0 && j.pontuacao_branco == 0)
	{
		cout << j.pretas.size() << " " << j.brancas.size() << "\n";
	}
	else
	{
		cout << j.pontuacao_preto << " " << j.pontuacao_branco << "\n";
	}
	
	/*for(int i=0;i<j.dimensao_tab;i++)
	{
		for(int k=0;k<j.dimensao_tab;k++)
		{
			cout << j.tabuleiro[i][k];
		}
		cout << "\n";
	}*/
	return 0;
}