#include <iostream>
#include <vector>
#include <string>

using namespace std;


class mesa
{
	/*
		Classe responsável armazenar todas as mesas 
		que podem ser compradas por Isabel.
	*/
	public:
		int comprimento = 0;
		int largura = 0;
		/*
			Essa terá que ter duas versões uma normal
			e outra que roda 90º
		*/
		char **matrix_mesa;
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
		int quantidade_mesas = 0;
		char **m;
		vector <mesa> mesas;
};

void alocar_matriz(int linhas, int colunas, casa *c)
{
 	/*
		Método responsável por realizar a alocação dinâmica de uma matriz
 	*/ 	
	c->m = (char**)malloc(linhas * sizeof(char*)); //Aloca um Vetor de Ponteiros
	for (int i = 0; i < linhas; i++)
	{
		/*
			Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		*/
	  	c->m[i] = (char*) malloc(colunas * sizeof(char));
	}

}

void alocar_matriz_mesa(int linhas, int colunas, casa *c, int k)
{
	int i,j;
	c->mesas[k].matrix_mesa = (char**)malloc(linhas * sizeof(char*)); //Aloca um Vetor de Ponteiros
	for (i = 0; i < linhas; i++)
	{ //Percorre as linhas do Vetor de Ponteiros
		/*
			Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		*/
	  	c->mesas[k].matrix_mesa[i] = (char*) malloc(colunas * sizeof(char));
	  	for(j=0; j<colunas; j++)
	  	{
	  		c->mesas[k].matrix_mesa[i][j] = '.';
	  	}
	}
}

void desaloca_matriz(casa *c, int k, int linhas)
{
	for (int i = 0; i < linhas; i++)
	{
        delete[] c->mesas[k].matrix_mesa[i];
    }
    delete[] c->mesas[k].matrix_mesa;
}
void leitura_montagem_casa(vector <char> *buffer, casa *c)
{

	/*
		Realiza a leitura do arquivo de dados e montagem da casa
		A casa será armazenada em uma matriz
		As mesas em um vetor
		Os outros dados serão armazenados em tipos primitivos
	*/
	int i = 0, j = 0, k = 0, valor;
	char valor_aux; // redeclarando valor

	cin >> valor; // lê o comprimento da casa
	c->comprimento_casa = valor;
	cin >> valor; // lê a largura da casa
	c->largura_casa = valor;
	/*
		Alocando a matriz que será a casa
	*/
	alocar_matriz(c->comprimento_casa, c->largura_casa, c);
	while(i < c->largura_casa * c->comprimento_casa)
	{
		/*
			Esta etapa monta o mapa da casa

		*/
		cin >> valor_aux;

		c->m[k][j] = valor_aux;
		i++;
		j++;
		if(j == c->largura_casa)
		{
			j = 0;
			k++;
		}
	}
	cin >> valor; // aqui estou lendo o número total de mesas
	c->quantidade_mesas = valor;
	mesa m; // objeto mesa temporario
	i = 0;
	while(i<c->quantidade_mesas)
	{
		/* Armazenando Mesas */
		cin >> valor;
		m.comprimento = valor; // largura de uma mesa
		cin >> valor;
		m.largura = valor; // comprimento de uma mesa
		c->mesas.push_back(m); // adicionando na lista de mesas
		i++;
	}

}
int main()
{
	casa c; // objeto que irá armazenar a casa da entrada
	vector <char> buffer;
	leitura_montagem_casa(&buffer, &c);
	buffer.clear();//limpando buffer

	for(int i=0; i<c.mesas.size();i++)
	{
		/*
			Iremos testar cada mesa das duas formas
			normal e em 90º
		*/
		alocar_matriz_mesa(c.mesas[i].comprimento, c.mesas[i].largura, &c, i);
		for(int k=0;k<c.mesas[i].comprimento; k++)
		{
			for(int j=0;k<c.mesas[i].largura;j++)
			{
				cout << c.mesas[i].matrix_mesa[k][j];
			}
			cout << "\n";
		}
		exit(1);
		desaloca_matriz(&c, i, c.mesas[i].comprimento);
		// entra aqui caso a mesa não seja igual normal e em 90º
		/*if(c.mesas[i].comprimento != c.mesas[i].largura)
		{
			continue;
		}*/

	}

	return 0;
}
