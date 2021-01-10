#include "FisierBinar.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void FisierBinar::fileBinaryCreate(char* numeTabel, char* tabelInfo)
{
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	ofstream g(numeBinar, ios::binary);
	g.close();
}

void FisierBinar::fileBinaryAfisare(char* numeTabel, char* tabelInfo)
{
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	fstream fisier(numeBinar, ios::binary);

	fisier.seekg(0, ios::end);
	fisier.read((char*)&tabelInfo, sizeof(char*));
	printf("%s", tabelInfo);
	//cout << tabelInfo << endl;
	fisier.close();
}

void FisierBinar::afisare(char* numeTabel)
{
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	ifstream fisier;
	fisier.open(numeBinar, ios::binary|ios::in);
	ofstream afisareFile;
	afisareFile.open("afisare.txt");
	int buffer[2];
	while (fisier.read((char*)&buffer, sizeof(buffer)))
	{
		afisareFile << buffer;
		//afisareFile.write((char*)&buffer, sizeof(buffer));
	}
	fisier.close();
	afisareFile.close();
}

void FisierBinar::deserializare(char* numeTabel)
{
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	ifstream fisier;
	fisier.open(numeBinar, ios::binary);
	int buffer[2];
	fisier.read((char*)&buffer, sizeof(buffer));
	fisier.close();
}

void FisierBinar::fileBinaryInsert(char* numeTabel, char* values)
{
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	ofstream fisier(numeBinar, ios::app | ios::binary);
	fisier.seekp(0, ios::end);
	int length = strlen(values);
	fisier.write((char*)&length, sizeof(length));
	fisier.write(values, length + 1);
}

void FisierBinar::importCSV(char* numeTabel, char* numeCSV, int &rez)
{
	ifstream fin;
	string nume = numeCSV;
	nume += ".csv";
	fin.open(nume, ios::in);
	vector<string> row;
	string line, word, temp;
	ofstream myFile;
	myFile.open("inserabil.txt");

	while (fin >> temp)
	{
		
		row.clear();
		getline(fin, line);
		stringstream s(line);
		while (getline(s, word, ','))
		{
			myFile << word;
			row.push_back(word);
			rez = 1;
		}
		
	}
	
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	ofstream fisier(numeBinar, ios::app | ios::binary);
	fisier.seekp(0, ios::end);
	fisier.write((char*)&row[0], row.size() + 1);
}