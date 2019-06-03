#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;


/*vector <string> split(string entrada, string del)
{
	vector <string> aux;


	return aux;
}*/
size_t split(const string &txt, vector<string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;
        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
void leitura(vector <int> *buffer)
{

	int valor, i=0;
	char valor_char;
	ios_base::sync_with_stdio(false); // Toggle off synchronization of all the C++ standard streams
    cin.tie(NULL);                    // Disable the flushing of std::cout before std::cin accepts an input
	
	cin >> valor >> i;
	buffer->push_back(valor);
	buffer->push_back(i);
	i=0;
	while(cin >> valor_char)
	{
		if(valor_char == '.')
		{
			buffer->push_back(1);
		}
		else
		{
			buffer->push_back(0);
		}
		if(buffer->at(0) * buffer->at(1) == i+1)
			break;
		i++;

	}
	string valor_teste;
	vector <string> teste_buffer;
	while(getline(cin, valor_teste))
	{
		teste_buffer.push_back(valor_teste);
	}
	vector <string> teste;
	int j=0;
	for(i=2;i<teste_buffer.size();i++)
	{
		//*aux = const_cast<char*>(teste_buffer[i].c_str());
		split(teste_buffer[i], teste, ' ');
		for(j=0;j<teste.size();j++)
		{
			buffer->push_back(stoi(teste[j]));
		}
	}
	teste_buffer.clear();
	cout << "Size:" << buffer->size() << "\n";
	exit(1);
}


int main()
{

	vector <int> buffer;
	leitura(&buffer);
	cout << buffer[0];

	return 0;
}