#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class entrada{

	public:
		int num_dias;
		int custo_dia;
		vector <int> lista;
};

void leitura(const char* nome_arquivo, vector <int> *buffer)
{
	int valor;
	while(cin>>valor)
	{
		buffer->push_back(valor);
	}
}
void retira_custo(vector <entrada> *in, int j)
{
	for(int i=0;i<in->at(j).lista.size();i++)
	{
		in->at(j).lista[i] = in->at(j).lista[i] - in->at(j).custo_dia;	
	}
}
vector <entrada> montagem_entrada(vector <int> *buffer)
{
	vector <entrada> in;
	entrada in_obj;
	int cont;
	for(int i=0;i<buffer->size();i++)
	{
		in_obj.num_dias = buffer->at(i);
		in_obj.custo_dia = buffer->at(i+1);
		i=i+2;
		cont = 0;
		while(cont<in_obj.num_dias)
		{
			in_obj.lista.push_back(buffer->at(i));
			cont++;
			i++;
		}
		in.push_back(in_obj);
		in_obj.lista.clear();
		i--;
	}
	return in;
}
int soma_subvetor(vector <entrada> *in, int j, int final)
{
	int x = 0;
	if(final == 0)
	{
		return max(in->at(j).lista[0], 0);
	}
	x = soma_subvetor(in, j, final-1);
	
	int s = 0;
	int i = final;
	while(i>=0)
	{
		s = s + in->at(j).lista[i];
		if(s>x)
		{
			x = s;
		}
		i--;
	}
	return x;
}
int main(int argc, char *argv[])
{
	vector <int> buffer;
	leitura(argv[1], &buffer);
	int s;
	vector <entrada> in = montagem_entrada(&buffer);
	for(int i=0;i<in.size();i++)
	{
		retira_custo(&in, i);
		s = soma_subvetor(&in, i, in[i].lista.size()-1);
		/*if((in[i].custo_dia >= 0 && in[i].custo_dia < 1000) && (in[i].num_dias > 1 && in[i].num_dias <= 50)) 
		{
			retira_custo(&in, i);
			s = soma_subvetor(&in, i, in[i].lista.size()-1);
		}
		else
		{
			s = 0;
		}*/
		cout << s << "\n";
	}
}