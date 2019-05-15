#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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
void retira_custo(vector <int> *buffer, int custo_dia)
{
	for(int i=0;i<buffer->size();i++)
	{
		buffer->at(i) = buffer->at(i) - custo_dia;
	}
}
int soma_subvetor(vector <int> *buffer, int num_dias, int inicial, int final)
{
	int x = 0;
	if(final-inicial==1)
	{
		if (buffer->at(0) > 0)
		{
			return buffer->at(0);
		}
		else
		{
			return 0;
		}
	}
	x = soma_subvetor(buffer, num_dias, inicial, final-1);
	int s = 0;
	int i = final-inicial;

	if(final-inicial <= num_dias)
	{
		while(i>0)
		{
			s = s + buffer->at(i);
			if(s>x)
			{
				x = s;
			}
			i--;
		}
	}
	return x;
}

int main()
{
	vector <int> buffer;
	leitura("entrada.txt", &buffer);
	int num_dias = buffer[0];
	int custo_dia = buffer[1];
	buffer.erase(buffer.begin()); //removendo elemento
	buffer.erase(buffer.begin()); // removendo elemento
	retira_custo(&buffer, custo_dia);
	int s = soma_subvetor(&buffer, num_dias, 0, buffer.size()-1);
	cout << s << "\n";
}