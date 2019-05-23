#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class data{
	public:
		long long int t;
		long long int m;
		long long int n;
		long long int p = 0; // atributo que irá receber a quantidade de combinações válidas possíveis
};
void leitura(data *d)
{
	long long int valor;
	cin >> valor;
	d->t = valor; // tamanho da combinação, nº de minutos
	cin >> valor;
	d->m = valor; // valor de dificuldade mínima
	cin >> valor;
	d->n = valor; // valor de dificuldade máxima
}
int ginastica_pd(data *d, int i, int t)
{

	if(i < d->m || i > d->n) // aqui vai além dos limites do problema
	{
		return 0;
	}

	if(t == 1)
	{
		return 1;
	}
	long long int soma = (ginastica_pd(d, i-1, t-1) + ginastica_pd(d, i+1, t-1));
	return soma;
	
}
int main()
{
	data d;
	leitura(&d);
	long long int soma = 0;
	if(! d.t < 1 or d.t>50 or d.m < 1 or d.n < 1 or d.m > pow(10, 5) or d.n > pow(10, 5))
	{
		for(int i=d.m; i<=d.n; i++)
		{
			soma = ginastica_pd(&d, i, d.t) + soma;
			cout << soma << "\n";
		}
	}
	
	cout << soma << "\n";
	return 0;
}