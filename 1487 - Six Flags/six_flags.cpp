#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class atracoes{
	public:
		int d; // tempo de duração do brinquedo (peso)
		int p; // pontuação atribuída ao brinquedo 
};
class diversao{
	public:
		int n; // número de atrações
		int t; // tempo em minutos (peso máximo)
		vector <atracoes> a; // responsável por armazenar as atrações de cada instância
};

void leitura(vector <diversao> *div)
{

	/*
		Método responsável pela leitura da entrada.
	*/
	int valor, k, i=0;
	diversao d_aux; // variável auxiliar de diversao 
	atracoes a_aux; // variável auxiliar de atração
	vector <atracoes> a_aux_list; // lista auxiliar de atração
	
	while(cin >> valor)
	{
		d_aux.n = valor; // número de atrações que podem ser visitadas
		cin >> valor;
		d_aux.t = valor; // tempo máximo para visitar todas as atrações
		k = 0;
		
		if(d_aux.n == 0) 
		{
			/*
				Caso o número de atrações a serem visitadas for igual a 0,
				então, sabe-se que não há mais avaliações a serem lidas.
			*/
			break;
		}
		
		while(k < d_aux.n)
		{
			/*
				Armazena o peso e o custo de cada uma das atrações que podem ser utilizados
			*/
			cin >> valor;
			a_aux.d = valor;
			cin >> valor;
			a_aux.p = valor;
			a_aux_list.push_back(a_aux);
			k++;
		}
		/*
			Armazena a nova instância 
			e a nova instância recebe a lista auxiliar que possui os dados de atrações
		*/
		div->push_back(d_aux); // 
		div->at(i).a = a_aux_list; 

		
		a_aux_list.clear(); // limpa o buffer
		i++;
	}

}
void inicializa_vetor_itens(vector <int> *itens)
{
	/*
		Inicializa o vetor onde o peso dos itens é inicialmente 0
	*/
	for(int i=0;i<itens->size();i++)
	{
		itens->at(i) = 0;
	}
}
int mochila_binaria(diversao *d_inst)
{
	/* 
		A solução utilizada para resolução deste problema é baseada em:
		https://www.geeksforgeeks.org/unbounded-knapsack-repetition-items-allowed/

		A solução proposta é de programação dinâmica.
		
		Este problema se resume no Problema da Mochila com repetiação,
		onde temos que otimizar a maior quantidade de diversão, dado um tempo de restrição
		máxima e o tempo gasto de brincar em cada brinquedo.

		A complexidade final dessa implementação é O(np) onde n é o tamanho da entrada e p
		o peso total da mochila. Este tipo de algoritmo é considerado pseudo polinomial, já
		que depende em partes da entrada.

	*/

	vector <int> itens; //vetor de itens
	int j, index = 0;
	itens.resize(d_inst->t + 1); // o tamanho dele será o peso total
	inicializa_vetor_itens(&itens); //inicializando vetor de itens

	for(int i=0;i<=d_inst->t;i++) // vai até o peso total
	{
		for (j=0;j<d_inst->a.size();j++) // vai até o número total de atrações
		{
			if(d_inst->a[j].d <= i)
			{

				/*
					Selecionando os itens que retornam a maior "diversão" possível
					Por isso max(itens[i], e itens[index] + ponto de atribuição do brinquedo)
				*/
				index = i - d_inst->a[j].d;
				itens[i] = max(itens[i], itens[index] + d_inst->a[j].p);
			}
		}
	}
	return itens[d_inst->t]; // a penúltima posição armazena o valor ótimo
}

int main()
{
	vector <diversao> div;
	leitura(&div);
	int s;
	for(int i=0;i<div.size();i++)
	{ 
		/* 
			Este problema se resumo no problema da mochila binária com repetições
		*/
		s = mochila_binaria(&div[i]);
		cout << "Instancia " << i+1 << "\n" << s << "\n\n";
	}


	return 0;
}