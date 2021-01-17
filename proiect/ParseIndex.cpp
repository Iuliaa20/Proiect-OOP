#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int ParseDropIndex(char* comanda, char* numeTabel, char* numeIndex,  int tip_token)
{
	char* p;
	int i;
	p = strtok(comanda, " ");
	if (p != NULL)
	{
		strcpy(comanda, comanda + 11);
		tip_comanda(comanda, &tip_token);
			if (tip_token != IDENTIFICATOR)
			{
				printf("Eroare: lipseste nume index\n");
				return 0;
			}
			else
			{
				for (i = 0; i < strlen(p);i++)
				{
					numeIndex[i] = p[i];
				}
				numeIndex[i] = '\0';
				
			}
			strcpy(comanda, comanda + strlen(p) + 1);
	}
	return 1;
}

int ParseCreateIndex(char* numeTabel, char* numeIndex, char* numeColoana, char* comanda)
{
	char* p;
	char* pColoana;
	int i, id = 0, tip_token = 0;
	bool ok = false;
	p = strtok(comanda, " ");
	if (p != NULL)
	{
		strcpy(comanda, comanda +13);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Eroare: se asteapta numele'%d' '%s'\n", tip_token, p);
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				numeIndex[i] = p[i];
			}
			numeIndex[i] = '\0';
		}
		strcpy(comanda, comanda + strlen(numeIndex) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != ON)
		{
			printf("Eroare: lipseste ON \n");
			return 0;
		}
		strcpy(comanda, comanda + 3);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Eroare: lipseste nume tabel\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				numeTabel[i] = p[i];
			}
			numeTabel[i] = '\0';
		}
		strcpy(comanda, comanda + strlen(p)+1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != '(')
		{
			printf("Eroare: se asteapta (\n");
			return 0;
		}
		strcpy(comanda, comanda + 2);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Eroare: lipseste nume coloana\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				numeColoana[i] = p[i];
			}
			numeColoana[i] = '\0';
		}
		strcpy(comanda, comanda + strlen(p)+1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != ')')
		{
			printf("Eroare: se asteapta )\n");
			return 0;
		}
		strcpy(comanda, comanda + 2);
	}
	return 1;
}
