#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"
#include <vector>
using namespace std;

int ParseInsert(char* numeTabel, char* comanda, char* values, vector<int> &tipValues)
{
	char* p;
	int i, tip_token;
	bool ok = 0, isValue = 0;
	strcpy(values, "");
	p = strtok(comanda, " ");
	if (p != NULL)
	{
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != INTO)
		{
			printf("Eroare: lipsește keyword INTO\n");
			return 0;
		}
		strcpy(comanda, comanda + 5);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Eroare: lipsește nume tabel\n");
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
		if (tip_token != VALUES)
		{
			printf("Eroare: lipsește keyword VALUES\n");
			return 0;
		}
		strcpy(comanda, comanda + strlen(p)+1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != '(')
		{
			printf("Eroare: lipseste ( \n");
			return 0;
		}
		do
		{
			strcpy(comanda, comanda + strlen(p) + 1);
			tip_comanda(comanda, &tip_token);
			isValue = (tip_token == INTEGER_NB || tip_token == FLOAT_NB || tip_token == IDENTIFICATOR);
			if (isValue == 0)
			{
				printf("Eroare: '%d' '%s' valori asteptate\n", tip_token, p);
				return 0;
			}
			else
			{
				strcat(values, p);
				tipValues.push_back(tip_token);
				strcat(values, " ");
			}
			strcpy(comanda, comanda + strlen(p) + 1);
			tip_comanda(comanda, &tip_token);
			if (tip_token == ')')
			{
				ok = 1;
				strcpy(comanda, comanda + 2);
				break;
			}
		} while (tip_token == ',');
		values[strlen(values) + 1] = '\0';
		if (!ok)
		{
			printf("Eroare: lipseste ) \n");
			return 0;
		}
	}
	return 1;
}
