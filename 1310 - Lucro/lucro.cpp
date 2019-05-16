#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class entrada{

	public:
		int num_dias;
		int custo_dia;
		vector <int> lista;
};

void leitura(const char* nome_arquivo, vector <int> *buffer)
{
	ifstream file;
	file.open(nome_arquivo);
	int valor;
	while(file>>valor)
	{
		buffer->push_back(valor);
	}
	file.close();
}
void retira_custo(vector <entrada> *in, int j)
{
	for(int i=0;i<in->at(j).lista.size();i++)
	{
		in->at(j).lista[i] = in->at(j).lista[i] - in->at(j).custo_dia;	
	}
}
int soma_subvetor(vector <entrada> *in, int j, int inicial, int final)
{
	int x = 0;
	if(final-inicial==1)
	{
		if (in->at(j).lista[0] > 0)
		{
			return in->at(j).lista[0];
		}
		else
		{
			return 0;
		}
	}
	x = soma_subvetor(in, j, inicial, final-1);
	
	int s = 0;
	int i = final-inicial;
	while(i>0)
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
		i--;
		in.push_back(in_obj);
		in_obj.lista.clear();
	}
	return in;
}
int main()
{
	vector <int> buffer;
	leitura("entrada3.txt", &buffer);
	vector <entrada> in = montagem_entrada(&buffer);
	int s;
	for(int i=0;i<in.size();i++)
	{
		retira_custo(&in, i);
		s = soma_subvetor(&in, i, 0, in[i].lista.size()-1);
		cout << s << "\n";

	}

}