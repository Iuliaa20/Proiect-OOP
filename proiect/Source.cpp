#include <iostream>
#include "identificator.h"

using namespace std;

int ParseCreate(char* numeTabel, char* tabelInfo, int* dimensiune, char* comanda);
int ParseDrop( char* numeTabel, char* comanda, int tip_token);
int ParseDisplay(char* numeTabel, char* comanda);
char ParseDelete(char check, char* numeTabel, char* numeColoanaWhere, char* valoareWhere, char* comanda, int tip_token);
int ParseUpdate(char* numeTabel, char* numeColoanaSet, char* valoareSet, char* numeColoanaWhere, char* valoareWhere, char* comanda, char* tabelInfo);
int ParseSelect(char* numeTabel, char* comanda, char* coloane);
int ParseInsert(char* numeTabel, char* comanda, char* values);
int ParseDropIndex(char* comanda, char* numeTabel, char* numeIndex, int tip_token);
int ParseCreateIndex(char* numeTabel, char* numeIndex, char* numeColoana, char* comanda);

int main()
{
	char* input, token;
	char* p;
	char* linie;
	char in[10000];
	int tip_token;

	int rezultat = 0; char check = 'O'; bool moreCommands = 0;
	char tabelInfo[10000] = { '\0' };
	char numeTabel[100] = { '\0' };
	char numeIndex[100] = { '\0' };
	char numeColoanaWhere[100] = { '\0' };
	char numeColoana[100] = { '\0' };
	char numeColoanaSet[100] = { '\0' };
	char coloane[1000] = { '\0' };
	char values[1000] = { '\0' };
	char valoareWhere[100] = { '\0' };
	char valoareSet[100] = { '\0' };

	cout << "Please input your sql command:" << endl;
	input = citire_comenzi(in);
	p = strtok(input, " ");
	do
	{
		if (moreCommands)
		{
			input = strtok(NULL, " ");
			if (!input)
			{
				break;
			}
		}
		tip_comanda(input, &tip_token);
		switch (tip_token)
		{
		case CREATE:
		{
			tip_comanda(input + 7, &tip_token);
			if (tip_token == TABLE)
			{
				//char* tabelInfo = new char[10000];
				int* dimensiune = new int[100];
				rezultat = ParseCreate(numeTabel, tabelInfo, dimensiune, input);
				if(rezultat)
					cout << "Ai creat tabela "<<numeTabel<< " cu coloanele "<<tabelInfo<<endl;
				break;
			}
			else
			{
				if (tip_token == INDEX)
				{
					rezultat = ParseCreateIndex(numeTabel, numeIndex, numeColoana, input);
					if(rezultat)
						cout << "Ai creat indexul "<<numeIndex<<" pentru coloana "<<numeColoana<<" din tabela "<<numeTabel<<endl;
					break;
				}
				else
				{
					cout << "Error TABLE or INDEX  missing\n";
					break;
				}
			}
		}
		case DROP:
		{
			tip_comanda(input+5, &tip_token);
			if(tip_token == TABLE)
			{
				rezultat = ParseDrop(numeTabel, input, tip_token);
				if(rezultat)
					cout << "Ai sters tabela: "<<numeTabel<<endl;
				break;
			}
			else
			{
				if (tip_token == INDEX)
				{
					rezultat = ParseDropIndex(input, numeTabel, numeIndex, tip_token);
					if(rezultat)
						cout << "Ai sters indexul: "<<numeIndex<<endl;
					break;
				}
				else
				{
					cout << "Error TABLE or INDEX  missing\n";
					break;
				}
			}
		}
		case DISPLAY:
		{
			rezultat = ParseDisplay(numeTabel, input);
			if (rezultat)
				cout <<"Ai afisat tabela: "<<numeTabel<<endl;
			break;
		}
		case DELETE:
		{
			rezultat = ParseDelete(check, numeTabel, numeColoanaWhere, valoareWhere, input, tip_token);
			if((char)rezultat == 'Y')
				cout << "Ai sters inregistrarile din tablea "<<numeTabel<<" unde coloana "<<numeColoanaWhere<<" are valoarea "<<valoareWhere<<endl;
			break;
		}
		case UPDATE:
		{
			char* tabelInfo = new char[10000];
			rezultat = ParseUpdate(numeTabel, numeColoanaSet, valoareSet, numeColoanaWhere, valoareWhere, input, tabelInfo);
			if(rezultat)
				cout << "Ai updatat tabela "<<numeTabel<<" modificand coloana "<<numeColoanaSet<<" cu valoarea "<<valoareSet<<" unde coloana "<<numeColoanaWhere<<" are valoarea "<<valoareWhere<<endl;
			break;
		}
		case SELECT:
		{
			rezultat = ParseSelect(numeTabel, input, coloane);
			if(rezultat == 2)
				cout << "Ai selectat toate coloanele din tabela "<<numeTabel<<endl;
			else
			{
				if (rezultat == 1)
					cout << "Ai selectat "<<coloane<<"din tabela " << numeTabel<<endl;
			}
			break;
		}
		case INSERT:
		{
			rezultat = ParseInsert(numeTabel, input, values);
			if(rezultat)
				cout <<"Ai inserat in tabela "<<numeTabel<<" valorile "<<values<<endl;
			break;
		}
		default:
			cout << "Error illegal command\n";
		}
		strcpy(input, input + 2);
		tip_comanda(input, &tip_token);
		if (tip_token == ';')
		{
			moreCommands = 1;
		}
	} while (tip_token == ';');
}
