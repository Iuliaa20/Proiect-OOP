enum Token
{
	IDENTIFICATOR = 128,
	INTEGER_NB,
	FLOAT_NB,
	STRING,

	ALL, CREATE, DELETE, DROP, EXISTS, FROM, INDEX, INTO, NOT, SELECT, SET, TABLE, UPDATE, VALUES, WHERE
};

int citire_comanda(char* input);
char* identifica(char* poz_curenta, char* token, int* tip_token);