#include <iostream>
#include <sstream>
#include <iomanip>
#include "identificator.h"
#include <fstream>
#include "FisierText.h"
#include "FisierBinar.h"
using namespace std;

int ParseCreate(char* numeTabel, char* tabelInfo, int* dimensiune, char* comanda);
int ParseDrop( char* numeTabel, char* comanda, int tip_token);
int ParseDisplay(char* numeTabel, char* comanda);
char ParseDelete(char check, char* numeTabel, char* numeColoanaWhere, char* valoareWhere, char* comanda, int tip_token);
int ParseUpdate(char* numeTabel, char* numeColoanaSet, char* valoareSet, char* numeColoanaWhere, char* valoareWhere, char* comanda, char* tabelInfo);
int ParseSelect(char* numeTabel, char* comanda, char* coloane);
int ParseInsert(char* numeTabel, char* comanda, char* values);
int ParseImport(char* numeTabel, char* comanda, char* numeFisier);
int ParseDropIndex(char* comanda, char* numeTabel, char* numeIndex, int tip_token);
int ParseCreateIndex(char* numeTabel, char* numeIndex, char* numeColoana, char* comanda);
void CreateBinary(char* numeTabel, char* tabelInfo);


int main()
{
	char* input, token;
	char* p;
	char* linie;
	char in[10000];
	int tip_token, existed;
	FisierText f;FILE* e;FisierBinar k;

	int rezultat = 0; char check = 'O'; bool moreCommands = 0;
	char tabelInfo[100] = { '\0' };
	char numeTabel[100] = { '\0' };
	char numeIndex[100] = { '\0' };
	char numeFisier[100] = { '\0' };
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
				//char* tabelInfo = new char[10];
				int* dimensiune = new int[100];
				rezultat = ParseCreate(numeTabel, tabelInfo, dimensiune, input);
				if (rezultat)
				{
					string nume = numeTabel;
					nume += ".txt";
					ifstream h(nume.c_str());
						if(h.good())
							cout <<"Error file exists";
					else {
					    cout << "Ai creat tabela " << numeTabel << " cu coloanele " << tabelInfo << endl;
						f.fileTextCreate(numeTabel, tabelInfo);
						h.open(nume, ios::in);
						k.fileBinaryCreate(numeTabel, tabelInfo);
						
						k.fileBinaryAfisare(numeTabel, tabelInfo);
					}
				}
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
				if (rezultat)
				{
					
					if (remove(numeTabel) != 0)
					{
	
						f.fileTextDrop(numeTabel, existed);
						cout << existed;
						if (existed==1)
							cout << "Sters"<<endl;
						else
							cout << "NU EXISTA"<<endl;
					}
					
				}
				
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
			{
				string nume = numeTabel;
				nume += ".txt";
				ifstream h(nume.c_str());
				if (!h.good())
					cout << "Error file DOES NOT  exist";
				else
				{
					cout << "Ai afisat tabela: " << numeTabel << endl;
					f.fileTextDisplay(numeTabel, tabelInfo);
					cout << tabelInfo;
				}
			}
			break;
		}
		case DELETE:
		{
			rezultat = ParseDelete(check, numeTabel, numeColoanaWhere, valoareWhere, input, tip_token);
			if ((char)rezultat == 'Y')
			{
				string nume = numeTabel;
				nume += ".txt";
				ifstream h(nume.c_str());
				if (!h.good())
					cout << "Error file DOES NOT  exist";
				else
					cout << "Ai sters inregistrarile din tablea " << numeTabel << " unde coloana " << numeColoanaWhere << " are valoarea " << valoareWhere << endl;
			}
			break;
		}
		case UPDATE:
		{
			char* tabelInfo = new char[10000];
			rezultat = ParseUpdate(numeTabel, numeColoanaSet, valoareSet, numeColoanaWhere, valoareWhere, input, tabelInfo);
			if (rezultat)
			{
				string nume = numeTabel;
				nume += ".txt";
				ifstream h(nume.c_str());
				if (!h.good())
					cout << "Error file DOES NOT  exist";
				else
					cout << "Ai updatat tabela " << numeTabel << " modificand coloana " << numeColoanaSet << " cu valoarea " << valoareSet << " unde coloana " << numeColoanaWhere << " are valoarea " << valoareWhere << endl;
			}
			break;
		}
		case SELECT:
		{
			rezultat = ParseSelect(numeTabel, input, coloane);
			string nume = numeTabel;
			nume += ".txt";
			ifstream h(nume.c_str());
			if (!h.good())
				cout << "Error file DOES NOT  exist";
			else
			{
				if (rezultat == 2)
				{
					cout << "Ai selectat toate coloanele din tabela " << numeTabel << endl;
					f.fileTextDisplay(numeTabel, tabelInfo);
					cout << tabelInfo;
				}
				else
				{
					if (rezultat == 1)
						cout << "Ai selectat " << coloane << "din tabela " << numeTabel << endl;
				}
			}
			break;
		}
		case INSERT:
		{
			rezultat = ParseInsert(numeTabel, input, values);
			if (rezultat)
			{
				string nume = numeTabel;
				nume += ".txt";
				ifstream h(nume.c_str());
				if (!h.good())
					cout << "Error file DOES NOT  exist";
				else
				{
					cout << "Ai inserat in tabela " << numeTabel << " valorile " << values << endl;
					k.fileBinaryInsert(numeTabel, values);
				}
			}
			break;
		}
		case IMPORT:
		{
			rezultat = ParseImport(numeTabel, input, numeFisier);
			if (rezultat)
			{
				string nume = numeTabel;
				nume += ".txt";
				ifstream h(nume.c_str());
				if (!h.good())
					cout << "Error file DOES NOT  exist";
				else
				{
					
					k.importCSV(numeTabel, numeFisier, existed);
					if (existed != 1)
						cout << "Nu se foloseste separatorul corect";
					else	
						cout << "Ai importat in tabela " << numeTabel << " valorile din fisierul CSV: " << numeFisier << endl;
				}
			}
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
