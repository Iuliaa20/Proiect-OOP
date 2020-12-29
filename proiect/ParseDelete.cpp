#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

char ParseDelete(char check, char* numeTabel, char* numeColoana, char* valoare, char* comanda, int tip_token)
{
	char* p;
	int i;
	p = strtok(comanda, " ");
	if (p != NULL)
	{
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != FROM)
		{
			printf("Eroare: lipsește FROM keyword\n");
			check = 'N';
			return check;
		}
		strcpy(comanda, comanda + 5);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Eroare: lipsește nume tabel\n");
			check = 'N';
			return check;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				numeTabel[i] = p[i];
			}
			numeTabel[i] = '\0';
		}
		strcpy(comanda, comanda + strlen(numeTabel) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != WHERE)
		{
			printf("Eroare: lipsește condiție\n");
			check = 'N';
			return check;
		}
		strcpy(comanda, comanda + 6);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Eroare: lipsește nume coloană\n");
			check = 'N';
			return check;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				numeColoana[i] = p[i];
			}
			numeColoana[i] = '\0';
		}
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != '=')
		{
			printf("Eroare: condiție incompletă\n");
			check = 'N';
			return check;
		}
		strcpy(comanda, comanda + 2);
		tip_comanda(comanda, &tip_token);
		bool isValue = (tip_token == INTEGER_NB || tip_token == FLOAT_NB || tip_token == IDENTIFICATOR);
		if (!isValue)
		{
			printf("Eroare: lipsește valoare\n");
			check = 'N';
			return check;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				valoare[i] = p[i];
			}
			valoare[i] = '\0';
		}
	}
	check = 'Y';
	return check;
}
