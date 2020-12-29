#include <iostream>
#include "identificator.h"
#include <cstring>
#include <string>

using namespace std;

char* citire_comenzi(char* input)
{
	*input = '\0';
	string tmp;
	std::getline(std::cin, tmp);
	strcat(input, tmp.c_str());
	return input;
}

/*char* linieComanda(char* input)
{
	char* linieComanda;
	char *newLinieComanda;
	linieComanda = strtok(input, ";");
	newLinieComanda = input + strlen(linieComanda);
	return newLinieComanda;
}*/

void tip_comanda(char* comanda, int* tip_token)
{
	char* p;
	p = strtok(comanda, " ");
	if (p != NULL)
	{
		if (strlen(p) == 1)
		{
			if (isdigit(*p))
				*tip_token = INTEGER_NB;
			else if (isalpha(*p))
				*tip_token = IDENTIFICATOR;
			else
				*tip_token = *p;
		}
		else {
			if (isalpha(*p))
			{
				int totalCaractere = 0;
				int totalNumere = 0;
				int poz = 0;
				for (int i = 0;i < strlen(p);i++)
				{
					if (isalpha(*(p + i)))
						totalCaractere++;
					else if (isdigit(*(p + i)))
						totalNumere++;
				}
				if (totalCaractere == strlen(p))
				{
					if (strcmp(p, "CREATE") == 0)
						*tip_token = CREATE;
					else if (strcmp(p, "DELETE") == 0)
						*tip_token = DELETE;
					else if (strcmp(p, "DISPLAY") == 0)
						*tip_token = DISPLAY;
					else if (strcmp(p, "DROP") == 0)
						*tip_token = DROP;
					else if (strcmp(p, "SELECT") == 0)
						*tip_token = SELECT;
					else if (strcmp(p, "UPDATE") == 0)
						*tip_token = UPDATE;
					else if (strcmp(p, "TABLE") == 0)
						*tip_token = TABLE;
					else if (strcmp(p, "INT") == 0)
						*tip_token = INT;
					else if (strcmp(p, "FLOAT") == 0)
						*tip_token = FLOAT;
					else if (strcmp(p, "CHAR") == 0)
						*tip_token = CHAR;
					else if (strcmp(p, "INSERT") == 0)
						*tip_token = INSERT;
					else if (strcmp(p, "INTO") == 0)
						*tip_token = INTO;
					else if (strcmp(p, "VALUES") == 0)
						*tip_token = VALUES;
					else if (strcmp(p, "FROM") == 0)
						*tip_token = FROM;
					else if (strcmp(p, "WHERE") == 0)
						*tip_token = WHERE;
					else if (strcmp(p, "SET") == 0)
						*tip_token = SET;
					else if (strcmp(p, "ALL") == 0)
						*tip_token = ALL;
					else if (strcmp(p, "INDEX") == 0)
						*tip_token = INDEX;
					else if (strcmp(p, "ON") == 0)
						*tip_token = ON;
					else
						*tip_token = IDENTIFICATOR;
				}
			}
			else if (isdigit(*p))
			{
				int decimal = 0;
				int poz = 1;
				for (int i = 1;i < strlen(p);i++)
				{
					if (!isdigit(*(p + i)) && decimal < 1)
					{
						if (*(p + i) == '.')
						{
							decimal++;
							poz++;
						}
						else
						{
							*(p + i) = '\0';
							break;
						}
					}
					else if (!isdigit(*(p + i)) && decimal == 1)
					{
						*(p + i) = '\0';
						break;
					}
					else
						poz++;
				}
				if (poz == 1)
					*tip_token = INTEGER_NB;
				else if (decimal != 0)
					*tip_token = FLOAT_NB;
				else
					*tip_token = INTEGER_NB;
			}
		}
	}
}