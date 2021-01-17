#include <fstream>
#include <iostream>
#include <set>
using namespace std;

class Coloana
{
public:
	set<int> sint;
	set<float> sfloat;
	set<string> sstring;

	/*virtual void creareColoana(char* numeColoana)
	{
		cout << "Nu ar trebui sa se apeleze asta";
	}*/
	virtual void inserare(char* numeColoana, char* values)
	{
		cout << "Nu ar trebui sa se apeleze asta";
	}

};

class ColoanaInt : public Coloana
{
public:
	set<int> creareColoanaInt(char* numeColoana)
	{
		set<int> s;
		return s;
	}
	void inserare(char* numeColoana, char* values) override
	{
		set<int> s;
		int l = strlen(values);
		int numar;
		char *p;
		p = strtok(values, " ");
		while (p != NULL)
		{
			int nrCifre = strlen(p);
			for (int i = 0;i < nrCifre;i++)
			{
				int cifra = p[i] - '0';
				numar += cifra * pow(10, i);
			}
			s.insert(numar);
			p = strtok(NULL, " ");
		}
		
	}
	void afisare(char* numeColoana, set<int> s)
	{
		for (set<int>::iterator it = s.begin();it != s.end();it++)
		{
			cout << *it<<" ";
		}
	}
};

class ColoanaFloat : public Coloana
{
	set<float> creareColoanaFloat(char* numeColoana)
	{
		set<float> s;
		return s;
	}

};

class ColoanaString : public Coloana
{
	set<string> creareColoanaString(char* numeColoana)
	{
		set<string> s;
		return s;
	}
};