class FisierBinar
{
private:
	char* numeFisier;
	char* info;
public:
	void fileBinaryCreate(char* numeTabel, char* tabelInfo);
	void fileBinaryAfisare(char* numeTabel, char* tabelInfo);
	void fileBinaryInsert(char* numeTabel, char* values);
	void deserializare(char* numeTabel);
	void afisare(char* numeTabel);
	void importCSV(char* numeTabel, char* numeCSV, int &rez);
};

