#include <iostream>
#include <map>
#include <set>
using namespace std;

class Index
{
public: 
	string nume;
	Index()
	{
		nume = "";
	}
	Index(string nume)
	{
		this->nume = nume;
	}
	virtual void afisare()
	{
		cout << "Acesta este un index de baza" << endl;
	}
	virtual void creare()
	{
		cout << "Acest index a fost creat" << endl;
	}
	virtual void drop()
	{
		cout << "Acest index a fost sters" << endl;
	}
};

class IndexInt : public Index
{
public:
	multiset<int> si;
	map<string, multiset<int>> mapIndexInt;
	IndexInt()
	{

	}
	IndexInt(string nume) :Index(nume)
	{
	}
	void afisare()
	{
		cout << "Acesta este un index pe o coloana int" << endl;
	}
	void creare()
	{
		mapIndexInt.insert(pair<string, multiset<int>>(nume, si));
		cout << "S-a creat indexul " << nume << endl;
		
	}
	void drop()
	{
		mapIndexInt.erase(nume);
		cout << "S-a sters indexul " << nume << endl;
	}
};

class IndexFloat : public Index
{
public:
	multiset<float> sf;
	map<string, multiset<float>> mapIndexFloat;
	IndexFloat()
	{

	}
	IndexFloat(string nume) :Index(nume)
	{

	}
	void afisare()
	{
		cout << "Acesta este un index pe o coloana float" << endl;
	}
		void creare()
		{
			mapIndexFloat.insert(pair<string, multiset<float>>(nume, sf));
			cout << " S-a creat indexul " << nume << endl;
		}
	void drop()
	{
		mapIndexFloat.erase(nume);
		cout << "S-a sters indexul " << nume << endl;
	}

};

class IndexString : public Index
{
public:
	multiset<string> ss;
	map<string, multiset<string>> mapIndexString;
	IndexString()
	{

	}
	IndexString(string nume) :Index(nume)
	{

	}
	void afisare()
	{
		cout << "Acesta este un index pe o coloana string" << endl;
	}
	void creare()
	{
		mapIndexString.insert(pair<string, multiset<string>>(nume, ss));
		cout << "S-a creat indexul " << nume << endl;
	}
	void drop()
	{
		mapIndexString.erase(nume);
		cout << "S-a sters indexul " << nume << endl;
	}
};
