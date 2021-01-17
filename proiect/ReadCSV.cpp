#include <fstream>
#include <iostream>

using namespace std;

void ReadCSV(char* numeCSV)
{
	ifstream fin;
	string nume = numeCSV;
	nume += ".csv";
	fin.open(nume, ios::in);

}