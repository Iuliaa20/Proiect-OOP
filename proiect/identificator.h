enum Token
{
	IDENTIFICATOR = 128,
	INTEGER_NB,
	FLOAT_NB,
	STRING,

	ALL, CREATE, DELETE, DISPLAY, DROP, EXISTS, FLOAT, FROM, INDEX, INSERT, INT, INTO, NOT, ON, SELECT, SET, CHAR, TABLE, UPDATE, VALUES, WHERE
};

char* citire_comenzi(char* in);
//char* linieComanda(char* input);
void tip_comanda(char* comanda, int* tip_token);