#include <string>
#include <iostream>

using namespace std;

class FisierText
{
private:
	char* numeFisier;
	char* info;
public:
	/*FisierText()
	{
		numeFisier = nullptr;
		info = nullptr;
	}
	FisierText(char* numeFisier)
	{
		this->numeFisier = new char[strlen(numeFisier) + 1];
		strcpy(this->numeFisier, numeFisier);
	}*/
	void fileTextCreate(char* numeFile, char* info);
	void fileTextDrop(char* numeFile, int &rez);
	void fileTextDisplay(char* numeFile, char* info);
	char* getNumeFisier();
	void setNumeFisier(char* numeFisier);
	char* getInfo();
	void deserializare(char* numeFile, char* info);
};

class FisierTextComenzi : public FisierText
{
public:
	void fileTextCitire(int argc, char* argv[], int i);
};
