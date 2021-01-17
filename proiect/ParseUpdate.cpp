#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"
using namespace std;

int ParseUpdate(char* numeTabel, char* numeColoanaSet, char* valoareSet, int &tipSet, char* numeColoanaWhere, char* valoareWhere, int &tipWhere, char* comanda, char* tabelInfo)
{
	char* p;
	int i, tip_token = 0; 
	p = strtok(comanda, " ");
	if (p != NULL)
	{
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Eroare: lipseste numele tabelei.\n");
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
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != SET)
		{
			printf("Eroare: lipseste keyword SET.\n");
			return 0;
		}
		strcpy(comanda, comanda + 4);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Eroare: lipseste numele coloanei care trebuie modificata.\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				numeColoanaSet[i] = p[i];
			}
			numeColoanaSet[i] = '\0';
		}
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != '=')
		{
			printf("Eroare: lipseste semnul = .\n");
			return 0;
		}
		strcpy(comanda, comanda + 2);
		tip_comanda(comanda, &tip_token);
		bool isValue = (tip_token == INTEGER_NB || tip_token == FLOAT_NB || tip_token == IDENTIFICATOR);
		if (!isValue)
		{
			printf("Eroare: lipseste valoarea care trebuie inlocuita.\n");
			return 0;
		}
		else
		{
			tipSet = tip_token;
			for (i = 0; i < strlen(p);i++)
			{
				valoareSet[i] = p[i];
			}
			valoareSet[i] = '\0';
		}
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != WHERE)
		{
			printf("Eroare: lipseste conditia.\n");
			return 0;
		}
		strcpy(comanda, comanda + 6);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Eroare: lipseste numele coloanei.\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				numeColoanaWhere[i] = p[i];
			}
			numeColoanaWhere[i] = '\0';
		}
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != '=')
		{
			printf("Eroare: conditia este incompleta.\n");
			return 0;
		}
		strcpy(comanda, comanda + 2);
		tip_comanda(comanda, &tip_token);
		isValue = (tip_token == INTEGER_NB || tip_token == FLOAT_NB || tip_token == IDENTIFICATOR);
		if (!isValue)
		{
			printf("Eroare: lipseste valoarea.\n");
			return 0;
		}
		else
		{
			tipWhere = tip_token;
			for (i = 0; i < strlen(p);i++)
			{
				valoareWhere[i] = p[i];
			}
			valoareWhere[i] = '\0';
		}
		strcpy(comanda, comanda + strlen(p) + 1);
	}
	return 1;
}
