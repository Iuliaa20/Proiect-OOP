#include "FisierBinar.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

void FisierBinar::fileBinaryAfisare(char* numeTabel, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString)
{
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	//fstream fisier(numeBinar, ios::binary);
	ofstream fisier(numeBinar, ios::trunc | ios::binary);
	for (map<string, multiset<int>>::iterator itI = mapInt.begin();itI != mapInt.end();itI++)
		for (multiset<int>::iterator iti = itI->second.begin();iti != itI->second.end();iti++)
			fisier << *iti << " ";
	for (map<string, multiset<float>>::iterator itF = mapFloat.begin();itF != mapFloat.end();itF++)
		for (multiset<float>::iterator itf = itF->second.begin();itf != itF->second.end();itf++)
			fisier << *itf << " ";
	for (map<string, multiset<string>>::iterator itS = mapString.begin();itS != mapString.end();itS++)
		for (multiset<string>::iterator its = itS->second.begin();its != itS->second.end();its++)
			fisier << *its << " ";
	fisier.close();
}

void FisierBinar::afisare(char* numeTabel)
{
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	ifstream fisier;
	fisier.open(numeTabel, ios::binary|ios::in);
	ofstream afisareFile;
	afisareFile.open("afisare.txt");
	int buffer[2];
	while (fisier.read((char*)&buffer, sizeof(buffer)))
	{
		afisareFile << buffer;
		//afisareFile.write((char*)&buffer, sizeof(buffer));
	}
	//afisareFile << numeBinar;
	fisier.close();
	afisareFile.close();
}

void FisierBinar::fileBinaryCreate(char* numeTabel, char* tabelInfo)
{
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	ofstream g(numeBinar, ios::binary);
	g.close();
}

void FisierBinarIesire::fileBinaryInsert(char* numeTabel, char* values, map<string, multiset<int>> mapInt,map<string, multiset<float>> mapFloat,map<string, multiset<string>> mapString)
{
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	ofstream fisier(numeBinar, ios::trunc | ios::binary);
	for (map<string, multiset<int>>::iterator itI = mapInt.begin();itI != mapInt.end();itI++)
		for (multiset<int>::iterator iti = itI->second.begin();iti != itI->second.end();iti++)
			fisier << *iti << " ";
	for (map<string, multiset<float>>::iterator itF = mapFloat.begin();itF != mapFloat.end();itF++)
		for (multiset<float>::iterator itf = itF->second.begin();itf != itF->second.end();itf++)
			fisier << *itf << " ";
	for (map<string, multiset<string>>::iterator itS = mapString.begin();itS != mapString.end();itS++)
		for (multiset<string>::iterator its = itS->second.begin();its != itS->second.end();its++)
			fisier << *its<< " ";
}

void FisierBinar::importCSV(char* numeTabel, char* numeCSV, int &rez)
{
	ifstream fCSV;
	rez = 1;
	
	string text;
	string nume = numeCSV;
	nume += ".csv";
	string numeTabela = numeTabel;
	numeTabela += ".bin";
	ofstream fTXT;
	fTXT.open(numeTabela, ios::out | ios::app | ios::binary);
	fCSV.open(nume, ios::in);
	while(!fCSV.eof())
	{
		//fCSV >> text;
		getline(fCSV, text);
		fTXT << text<<" ";
		//cout << text << " ";
	}




	/*fin.open(nume, ios::in);
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
	fisier.write((char*)&row[0], row.size() + 1);*/
}

void FisierBinar::checkCSV(char* numeCSV, int& rez)
{
	ifstream fCSV;
	string nume = numeCSV;
	nume += ".csv";
	fCSV.open(numeCSV, ios::in|ios::binary);
	string af;
	bool ok = 1;
	while (!fCSV.eof())
	{
		getline(fCSV, af);
		//cout << af << endl;// << " " << af.find(',') << "//";
		char* o;
		o = strtok((char*)af.c_str(), " ");
		while (o != NULL)
		{
			if (o[strlen(o) - 1] == ',')
			{
			//	cout << o << " " << o[strlen(o) - 1] << endl;
				o = strtok(NULL, " ");
			}
			else
			{
				ok = 0;
				break;
			}
		}
//		cout << o << endl;
		string aff;
		aff = af.substr(af.length() - 1);
		//cout << aff << aff.c_str() << endl;

		if (ok == 0)
			if (strcmp(o, aff.c_str()))
				rez = 0;
			else
				rez = 1;
	}
}
/*
void FisierBinar::deserializare(char* numeTabel)
{
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	ifstream fisier;
	fisier.open(numeBinar, ios::trunc | ios::binary);
	int buffer[2];
	fisier.read((char*)&buffer, sizeof(buffer));
	fisier.close();
}*/
