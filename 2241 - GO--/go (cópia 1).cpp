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
		int area = 0;
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
int **alocar_matriz(int linhas, int colunas)
{
 	/*
		Método responsável por realizar a alocação dinâmica de uma matriz
 	*/ 	

	int **m = (int**)malloc(linhas * sizeof(int*)); //Aloca um Vetor de Ponteiros	
	for (int i = 0; i < linhas; i++)
	{
		/*
			Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		*/
		m[i] = (int*) malloc(colunas * sizeof(int));
		for(int k=0; k<colunas; k++)
		{
			m[i][k] = 0; // deixando o tabuleiro vazio
		}
	}
	return m;

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
	j->tabuleiro = alocar_matriz(j->dimensao_tab, j->dimensao_tab);
	for(int i=0;i<j->quant_pedras;i++)
	{
		cin >> p.x >> p.y ;
		j->tabuleiro[p.x-1][p.y-1] = 1; // peças pretas
		j->pretas.push_back(p);
	}
	/*
		Armazenando dados de peças brancas
	*/
	for(int i=0;i<j->quant_pedras;i++)
	{
		cin >> p.x >> p.y;
		j->tabuleiro[p.x-1][p.y-1] = 2; // peças brancas
		j->brancas.push_back(p);
	}
}
int verifica_tabuleiro(jogadores *j, int k, int l, int *cp, int *cb)
{
	if(tabuleiro[k][l] == 0)
		return 0;
	
	else if(tabuleiro[k][l] == -1)
	{
		return -1;
	}

	if(tabuleiro[k][l] == 1) // pretos
	{
		*cp = *cp+1;
		return 1;
	}
	else if(tabuleiro[k][l] == 2) // brancos
	{
		*cb = *cb+1;
		return 1;
	}
	return 0;
}
int calcula_tudo(int d, jogadores *j)
{
	int k, cp = 0, cb = 0, flag_neg = 0;
	int r1, r2, r3, r4;
	coordenadas c;
	//int **m_aux = alocar_matriz(d-1, d-1);
	if(d == 2)
	{
		cout << j->pontuacao_preto + j->pretas.size() << " " 
		<< j->pontuacao_branco + j->brancas.size() << "\n";
		return 0;
	}
	for(int i=0;i<d-1;i++) // calculando pontos de dimensão 2
	{
		cp = 0;
		cb = 0;
		for(k=0;k<d-1;k++)
		{
			c.x_inicial = k; // x controla linhas
			c.x_final = k+1;
			c.y_inicial = i; // y colunas
			c.y_final = i+1;
			r1 = verifica_tabuleiro(j->tabuleiro, c.y_inicial, c.x_inicial, &cp, &cb);//linha 0, coluna 0
			r2 = verifica_tabuleiro(j->tabuleiro, c.y_final, c.x_inicial, &cp, &cb);
			r3 = verifica_tabuleiro(j->tabuleiro, c.y_inicial, c.x_final, &cp, &cb);
			r4 = verifica_tabuleiro(j->tabuleiro, c.y_final, c.x_final, &cp, &cb);
			if(r1 == -1 or r2 == -1 or r3 == -1 or r4 == -1)
			{
				flag_neg = 1;
			}
			if(cp == 0 && cb == 0)
			{
				j->tabuleiro[c.y_inicial][c.x_inicial] = 0;
			}
			else if((flag_neg==1)||(cp > 0 && cb > 0))
			{
				j->tabuleiro[c.y_inicial][c.x_inicial] = -1;
				flag_neg = 0;
			}
			else if(cp > 0)
			{
				j->tabuleiro[c.y_inicial][c.x_inicial] = 1;
				j->pontuacao_preto = j->pontuacao_preto + 1;
			}
			else if(cb > 0)
			{
				j->tabuleiro[c.y_inicial][c.x_inicial] = 2;
				j->pontuacao_branco = j->pontuacao_branco + 1;
			}
			cp = 0;
			cb = 0;
			//cout << r1 << " " << r2 << " " << r3 << " " << r4 << "\n";
		}
	}
	calcula_tudo(d-1, j);
	return 0;
}
void somando_dimensoes(jogadores *j)
{
	/*
		Método responsável por fazer as principais computações que 
		irão definir a pontuação do jogador.
		Para isso é utilizado um quadrado de dimensão N que varia e verifica
		quais são as peças que há nas subáreas quadráticas. 
	*/
	calcula_tudo(j->dimensao_tab, j);
}

int main()
{
	jogadores j;
	leitura_montagem_dados(&j); // também monta o tabuleiro
	somando_dimensoes(&j);
	
	return 0;
}