#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// usando uma solução baseada em : https://www.geeksforgeeks.org/unbounded-knapsack-repetition-items-allowed/

class atracoes{
	public:
		int d; // tempo de duração do brinquedo (peso)
		int p; // pontuação atribuída ao brinquedo 
};
class diversao{
	public:
		int n; // número de atrações
		int t; // tempo em minutos (peso máximo)
		vector <atracoes> a;
};

void leitura(vector <diversao> *div)
{
	int valor, k, i=0;
	diversao d_aux;
	atracoes a_aux;
	vector <atracoes> a_aux_list;
	while(cin >> valor)
	{
		d_aux.n = valor;
		cin >> valor;
		d_aux.t = valor;
		k = 0;
		if(d_aux.n == 0)
		{
			break;
		}
		while(k < d_aux.n)
		{
			cin >> valor;
			a_aux.d = valor;
			cin >> valor;
			a_aux.p = valor;
			a_aux_list.push_back(a_aux);
			k++;
		}
		div->push_back(d_aux);
		div->at(i).a = a_aux_list;
		a_aux_list.clear();
		i++;
	}

}
void inicializa_vetor_itens(vector <int> *itens)
{
	for(int i=0;i<itens->size();i++)
	{
		itens->at(i) = 0;
	}
}
int mochila_binaria(diversao *d_inst)
{
	vector <int> itens;
	itens.resize(d_inst->t + 1);
	int j, index = 0, soma = 0;
	inicializa_vetor_itens(&itens);

	for(int i=0;i<=d_inst->t;i++)
	{
		for (j=0;j<d_inst->a.size();j++)
		{
			if(d_inst->a[j].d <= i)
			{
				itens[i] = max(itens[i], itens[i - d_inst->a[j].d] + d_inst->a[j].p);
				soma = soma + itens[i];
			}
		}
	}
	return itens[d_inst->t];
}

int main()
{
	vector <diversao> div;
	leitura(&div);
	int s;
	for(int i=0;i<div.size();i++)
	{ // este problema se resumo no problema da mochila binária com repetições
		s = mochila_binaria(&div[i]);
		cout << "Instancia " << i+1 << "\n" << s << "\n\n";
	}


	return 0;
}