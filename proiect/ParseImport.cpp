#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int ParseImport(char* numeTabel, char* comanda, char* numeFisier)
{
	char* p;
	int i, tip_token;
	bool ok = 0, isValue = 0;
	p = strtok(comanda, " ");
	if (p != NULL)
	{
		strcpy(comanda, comanda + strlen(p) + 1);
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
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Eroare: lipseste nume fisier\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				numeFisier[i] = p[i];
			}
			numeFisier[i] = '\0';
		}
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != '.')
		{
			printf("Eroare: lipseste . \n");
			return 0;
		}
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != CSV)
		{
			printf("Eroare fisierul nu e denumit CSV\n");
			return 0;
		}
		
	}
	return 1;
}
