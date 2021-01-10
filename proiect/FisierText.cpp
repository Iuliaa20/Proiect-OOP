#include "FisierText.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

void FisierText:: fileTextCreate(char* numeFile, char* info)
{
	ofstream myFile;
	string nume = numeFile;
	nume += ".txt";
	myFile.open(nume);
	myFile << info;
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
