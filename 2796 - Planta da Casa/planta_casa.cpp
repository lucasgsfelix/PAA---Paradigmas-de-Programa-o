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

char ** alocar_matriz(int linhas, int colunas)
{
 	/*
		Método responsável por realizar a alocação dinâmica de uma matriz
 	*/ 	
  	int i,j;
	char **m = (char**)malloc(linhas * sizeof(char*)); //Aloca um Vetor de Ponteiros
	for (i = 0; i < linhas; i++)
	{ //Percorre as linhas do Vetor de Ponteiros
		/*
			Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		*/
	  	m[i] = (char*) malloc(colunas * sizeof(char));
	}

	return m; //Retorna o Ponteiro para a Matriz Alocada
}

char **inicializa_mesas(int linhas, int colunas, char **m)
{

	/*
		Método responsável por  inicializar a matriz de mesas com '.'
		a partir disso será feito o casamento de caracteres
	*/
	for(int i=0;i<linhas;i++)
	{
		for(int j=0;j<colunas;j++)
		{
			m[i][j] = '.';
			cout << m[i][j];
		}
	}
	return m;

}
char **desaloca_matriz(char **mesa, int linhas)
{
	for (int i = 0; i < linhas; i++)
	{
        delete[] mesa[i];
    }
    delete[] mesa;
    return mesa;
}
void leitura_montagem_casa(vector <char> *buffer, casa *c)
{

	/*
		Realiza a leitura do arquivo de dados e montagem da casa
		A casa será armazenada em uma matriz
		As mesas em um vetor
		Os outros dados serão armazenados em tipos primitivos
	*/
	int cont = 0, i = 0, j = 0, k = 0, valor;
	char valor_aux; // redeclarando valor

	cin >> valor; // lê o comprimento da casa
	c->comprimento_casa = valor;
	cin >> valor; // lê a largura da casa
	c->largura_casa = valor;
	/*
		Alocando a matriz que será a casa
	*/
	c->m = alocar_matriz(c->comprimento_casa, c->largura_casa);
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
		c.mesas[i].matrix_mesa = alocar_matriz(c.mesas[i].comprimento, c.mesas[i].largura);
		c.mesas[i].matrix_mesa = inicializa_mesas(c.mesas[i].comprimento, 
								c.mesas[i].largura, c.mesas[i].matrix_mesa);
		// entra aqui caso a mesa não seja igual normal e em 90º
		if(c.mesas[i].comprimento != c.mesas[i].largura)
		{
			c.mesas[i].matrix_mesa = desaloca_matriz(c.mesas[i].matrix_mesa, c.mesas[i].comprimento);
			c.mesas[i].matrix_mesa = alocar_matriz(c.mesas[i].largura, c.mesas[i].comprimento);
			c.mesas[i].matrix_mesa = inicializa_mesas(c.mesas[i].largura, 
								c.mesas[i].comprimento, c.mesas[i].matrix_mesa);
		}

	}

	return 0;
}
