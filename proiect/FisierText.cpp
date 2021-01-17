#include "FisierText.h"
#include "identificator.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


using namespace std;
/*
int ParseCreate(char* numeTabel, char* tabelInfo, int* dimensiune, char* comanda);
int ParseDrop(char* numeTabel, char* comanda, int tip_token);
int ParseDisplay(char* numeTabel, char* comanda);
char ParseDelete(char check, char* numeTabel, char* numeColoanaWhere, char* valoareWhere, char* comanda, int tip_token);
int ParseUpdate(char* numeTabel, char* numeColoanaSet, char* valoareSet, char* numeColoanaWhere, char* valoareWhere, char* comanda, char* tabelInfo);
int ParseSelect(char* numeTabel, char* comanda, char* coloane);
int ParseInsert(char* numeTabel, char* comanda, char* values);
int ParseImport(char* numeTabel, char* comanda, char* numeFisier);
int ParseDropIndex(char* comanda, char* numeTabel, char* numeIndex, int tip_token);
int ParseCreateIndex(char* numeTabel, char* numeIndex, char* numeColoana, char* comanda);
*/
void FisierText:: fileTextCreate(char* numeFile, char* info)
{
	ofstream myFile;
	string nume = numeFile;
	nume += ".txt";
	myFile.open(nume);
	myFile << info;
	myFile << endl;
}

void FisierText::fileTextDrop(char* numeFile, int &rez)
{
	string numeText = numeFile;
	numeText+=".txt";
	string numeBinar = numeFile;
	numeBinar += ".bin";
	if (remove(numeText.c_str()) == 0)
		rez = 1;
	remove(numeText.c_str());
	remove(numeBinar.c_str());
}

void FisierText:: fileTextDisplay(char* numeFile, char* info)
{
	string numeText = numeFile;
	numeText += ".txt";
	ifstream f(numeText);
	char tabelInfo[100] = { '\0' };
	while (!f.eof())
	{
		f >> info;
		strcat(tabelInfo, info);
		strcat(tabelInfo, " ");
	}
	strcpy(info, tabelInfo);
}

char* FisierText:: getNumeFisier()
{
	return numeFisier;
}

void FisierText::setNumeFisier(char* numeFisier)
{
	strcpy(this->numeFisier, numeFisier);
}

char* FisierText::getInfo()
{
	return info;
}
void FisierText::deserializare( char* numeFile, char* info)
{
	string numeBinar = numeFile;
	numeBinar += ".bin";
	ifstream g(numeBinar, ios::binary);
	int length=0;
	g.read((char*)&length, sizeof(length));
	delete[] info;
	info = new char[length + 1];
	g.read(info, length + 1);
	g.close();
}

void FisierTextComenzi::fileTextCitire(int argc, char* argv[], int i)
{
		//for (int i = 1;i < argc;i++)
		//{
	
			string nume = argv[i];
			fstream fcomenzi;
			fcomenzi.open(nume, ios::in);string tmp;
			cout << "Ai afisat continutul: " << argv[i] << endl;
			while (!fcomenzi.eof())
			{
				getline(fcomenzi, tmp);
				cout << tmp << endl;
			}
			fcomenzi.close();
		//}
}