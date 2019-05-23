#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class entrada{

	/*
		Classe que irá armazenar os valores de entrada.
	*/
	public:
		int num_dias;
		int custo_dia;
		vector <int> lista;
};

void leitura(vector <int> *buffer)
{

	/*
		Método responsável por montar o buffer que será
		utilizado para montar a entrada.
	*/
	int valor;
	while(cin>>valor)
	{
		buffer->push_back(valor);
	}
}
void retira_custo(vector <entrada> *in, int j)
{
	/*
		Método responsável por retirar o custo relacionado 
		a uma entrada do problema de seus valores de benefícios.
	*/
	for(int i=0;i<in->at(j).lista.size();i++)
	{
		in->at(j).lista[i] = in->at(j).lista[i] - in->at(j).custo_dia;
	}
}
vector <entrada> montagem_entrada(vector <int> *buffer)
{
	/*
		Método responsável pelo montagem da entrada e separação em diferentes
		posições de vetor para depois ser realizado apenas o cálculo.
	*/
	vector <entrada> in; // vetor que irá armazenar as instâncias finais
	entrada in_obj; // um objeto que é utilizado como auxiliar
	int cont; // variável contadora que será auxiliar
	for(int i=0;i<buffer->size();i++)
	{
		in_obj.num_dias = buffer->at(i); // armazena o número de dias que irá ficar na cidade
		in_obj.custo_dia = buffer->at(i+1); // armazena o custo de se ficar na cidade
		i=i+2;
		cont = 0;
		while(cont<in_obj.num_dias)
		{ // lê as próximas N linhas que representam os valores de benefício de uma cidade
			in_obj.lista.push_back(buffer->at(i));
			cont++;
			i++;
		}
		in.push_back(in_obj);//armazena o objeto na lista de entradas
		in_obj.lista.clear();//limpo o objeto já que não irei utilizar ele mais
		i--;
	}
	return in;
}
int soma_subvetor(vector <entrada> *in, int j, int final)
{

	/*
		Implementação da maior soma de um subvetor.
		Essa implementação aplica o paradigma de indução.
		A implementação é baseada no código de soma_subvetor 
		do professor Vinicius dado em sala de aula em PAA.
		Dado que a indução funciona provando para n-1 depois
		provando para n. Temos que a chegamos a base da recursão
		e depois retorna-se os valores.
	*/
	if(final == 0) // Passo Base
	{
		/*
			Maior entre o primeiro elemento da lista e 0 
			dado que pode ser negativo, neste caso não ir a cidade
			é a melhor opção.

		*/
		return max(in->at(j).lista[0], 0); 
	}
	int x = soma_subvetor(in, j, final-1); // Passo Indutivo
	int s = 0, i = final;

	/*
		Enquanto i for maior igual que zero ele calcula a maior soma
		contígua do subvetor e a armazena em x enquanto ela for crescente.
	*/

	while(i>=0)  
	{
		s = s + in->at(j).lista[i]; // calculando a soma
		
		if(s>x)
		{
			x = s; // armazenando uma soma crescente em x
		}
		i--;
	}
	return x;
}
int main(int argc, char *argv[])
{
	vector <int> buffer;
	leitura(&buffer); // realiza a leitura do buffer e armazena os valores
	int s; // variável que irá receber a soma a cada iteração
	vector <entrada> in = montagem_entrada(&buffer); // método responsável pela montagem da entrada
	for(int i=0;i<in.size();i++)
	{
		retira_custo(&in, i); // retira o custo de maneira que a saída final já terá débitado os custos de se ficar na cidade
		s = soma_subvetor(&in, i, in[i].lista.size()-1); // chama a função principal
		cout << s << "\n"; // imprime variável de saída
	}
}