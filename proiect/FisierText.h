class FisierText
{
private:
	char* numeFisier;
	char* info;
public:
	void fileTextCreate(char* numeFile, char* info);
	void fileTextDrop(char* numeFile, int &rez);
	void fileTextDisplay(char* numeFile, char* info);
	char* getNumeFisier();
	void setNumeFisier(char* numeFisier);
	char* getInfo();
	void deserializare(char* numeFile, char* info);
};
