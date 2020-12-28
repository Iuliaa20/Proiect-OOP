#include <iostream>
#include "identificator.h"

using namespace std;

int ParseCreate2(char* numeTabel, char* tabelInfo, int* dimensiune, char* comanda);
char ParseDrop(char check, char* numeTabel, char* comanda, int tip_token);
int ParseDisplay(char* numeTabel, char* comanda);


int main()
{
	int rezultat = 0; char check = 'O';
	char numeTabel[100] = { '\0' };
	cout << "Please input your sql command:" << endl;
	char* input; 
	char *token;
	char* linie;
	char in[10000];
	input = citire_comenzi(in);
	//linie = linieComanda(input);
	int tip_token;
	tip_comanda(input, &tip_token);
	switch (tip_token)
	{
		case CREATE:
		{
			char* tabelInfo = new char[10000];
			int* dimensiune = new int[100];
			rezultat = ParseCreate2(numeTabel, tabelInfo, dimensiune, input);
			cout << rezultat;
			break;
		}
		case DROP:
		{
			rezultat = ParseDrop(check, numeTabel, input, tip_token);
			cout << (char)rezultat;
			break;
		}
		case DISPLAY:
		{
			rezultat = ParseDisplay(numeTabel, input);
			cout << rezultat;
			break;
		}
	}
}
