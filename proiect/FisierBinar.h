#include <map>
#include <set>
#include <iostream>
using namespace std;
class FisierBinar
{
private:
	char* numbeFile;
	char* info;
public:
	void fileBinaryCreate(char* numeTabel, char* tabelInfo);
	void fileBinaryAfisare(char* numeTabel, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString);
	//void fileBinaryInsert(char* numeTabel, char* values, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString);
	//void deserializare(char* numeTabel);
	void afisare(char* numeTabel);
	void importCSV(char* numeTabel, char* numeCSV, int &rez);
	void checkCSV(char* numeCSV, int &rez);
};

class FisierBinarIesire : public FisierBinar
{
public:
	void fileBinaryInsert(char* numeTabel, char* values, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString);
};