enum Token
{
	IDENTIFICATOR = 128,
	INTEGER_NB,
	FLOAT_NB,
	STRING,

	ALL, CREATE, DELETE, DISPLAY, DROP, EXISTS, FLOAT, FROM, INDEX, INT, INTO, NOT, SELECT, SET, CHAR, TABLE, UPDATE, VALUES, WHERE
};

int citire_comanda(char* input);
char* identifica(char* poz_curenta, char* token, int* tip_token);

char* citire_comenzi(char* in);
char* linieComanda(char* input);
void tip_comanda(char* comanda, int* tip_token);
void identifyOtherKeywords(char* comanda, int* tip_token);


