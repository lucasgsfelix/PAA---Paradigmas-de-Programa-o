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
void calcula_pontos_dim_2(vector <coordenadas> *c_list, int d)
{
	int aux_linha = 1, aux_coluna=1, j;
	coordenadas c;
	for(int i=0;i<d-1;i++) // calculando pontos de dimensão 2
	{
		aux_coluna = 1;
		for(j=0;j<d;j++)
		{
			c.y_inicial = j;
			c.y_final = j+aux_coluna;
			c.x_inicial = i;
			c.x_final = i+aux_linha;

			if((c.y_final - c.y_inicial == 1 &&
				c.x_final - c.x_inicial ==  1))
			{

				cout <<"Linhas: "<< c.x_inicial << " " << c.x_final << "\n";
				cout << "Colunas: "<< c.y_inicial << " " << c.y_final << "\n";
				c_list->push_back(c); // adicionando na lista de coordenadas
			}
		}
	}

	exit(1);
}
int verifica(int linha, int coluna, jogadores *j)
{
	return j->tabuleiro[linha][coluna];
}
int calcula_matrizes(vector <coordenadas> *c_list, int d, jogadores *j)
{
	//int **m_aux = alocar_matriz(d-1, d-1);
	if(d == 2)
	{
		cout << j->pontuacao_preto + j->pretas.size() << " " 
		<< j->pontuacao_branco + j->brancas.size() << "\n";
		return 0;
	}
	else
	{
		int i, k, l, soma_pretos=0, soma_brancos=0;
		int flag, flag_soma=0;
		for(i=0;i<d-1;i++)
		{
			soma_pretos = 0;
			soma_brancos = 0;
			flag_soma = 0;
			for(k=0;k<d;k++)
			{
				for(l=0;l<d;l++)
				{
					if((i+k - k == 1 && i+l - i ==  1))
					{
						// tem k é linha
						// tem l é coluna
						cout << verifica(k, l, j) << "\n";
						cout << verifica(k, l+i, j) << "\n";
						cout << verifica(k+i, l, j)<< "\n"; // segunda linha
						cout << verifica(k+i, l+i, j)<< "\n"; //segunda linha
					/*c.y_inicial = k;
					c.y_final = i+k;
					c.x_inicial = l;
					c.x_final = i+l;*/
						//cout << k << " " << i+k << "\n";
					}
					//cout << l << " " << i+l << "\n";
					//cout << verifica(l, i+l, j) << "\n";
					/*if(j->tabuleiro[k][l] == 0)
						continue;
					
					else if(j->tabuleiro[k][l] == -1)
					{
						flag = 1;
						continue;
					}
					if(soma_brancos > 1 && soma_pretos > 1)
					{
						break;
					}

					if(j->tabuleiro[k][l] == 1) // pretos
					{
						soma_pretos++;
					}
					else if(j->tabuleiro[k][l] == 2) // brancos
					{
						soma_brancos++;
					}
					if(flag_soma == 1 or flag == 1)
					{
						break;
					}*/
				}
			}
			/*if(soma_pretos == 0 && soma_brancos == 0)
			{
				j->tabuleiro[c_list->at(i).x_inicial][c_list->at(i).y_inicial] = 0;
			}
			else if((flag==1)||(soma_pretos > 0 && soma_brancos > 0))
			{
				j->tabuleiro[c_list->at(i).x_inicial][c_list->at(i).y_inicial] = -1;
				flag = 0;
			}
			else if(soma_pretos > 0)
			{
				j->tabuleiro[c_list->at(i).x_inicial][c_list->at(i).y_inicial] = 1;
				j->pontuacao_preto = j->pontuacao_preto + 1;
			}
			else if(soma_brancos > 0)
			{
				j->tabuleiro[c_list->at(i).x_inicial][c_list->at(i).y_inicial] = 2;
				j->pontuacao_branco = j->pontuacao_branco + 1;
			}*/
		}
		exit(1);
	}
	calcula_matrizes(c_list, d-1, j);

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
	int k, l;
	vector <coordenadas> c_list;
	calcula_pontos_dim_2(&c_list, j->dimensao_tab);
	calcula_matrizes(&c_list, j->dimensao_tab, j);
}

int main()
{
	jogadores j;
	leitura_montagem_dados(&j); // também monta o tabuleiro
	somando_dimensoes(&j);
	
	return 0;
}