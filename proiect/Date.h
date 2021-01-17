#include <fstream>
#include <iostream>
using namespace std;

class Date
{
public:
	virtual void creare(char* nume) = 0;
	virtual void scriere(char* nume, string s) = 0;
};

class DateComenzi : public Date
{
public:
	void creare(char* nume) override
	{
		ofstream f;
		//string numeComanda = nume;
		//numeComanda += ".txt";
		//f.open(numeComanda.c_str());
		f.open(nume);
	}
	void scriere(char* nume, string s) override
	{
		ofstream f;
		//string numeComanda = nume;
		//numeComanda += ".txt";
		//f.open(numeComanda.c_str());
		f.open(nume);
		f << s<<endl;
	}
};

class DateImport : public Date
{
public:
	void creare(char* nume) override
	{
		ofstream f;
		string numeCSV = nume;
		numeCSV += ".csv";
		f.open(numeCSV.c_str());
		//f.open(nume);
	}
	void scriere(char* nume, string s) override
	{
		ofstream f;
		string numeCSV = nume;
		numeCSV += ".csv";
		f.open(numeCSV.c_str());
		//f.open(nume);
		f << s << endl;
	}
};