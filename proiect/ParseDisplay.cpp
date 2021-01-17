#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int ParseDisplay(char* numeTabel, char* comanda)
{
	char* p;
	int i, tip_token = 0;
	p = strtok(comanda, " ");
	if (p != NULL)
	{
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != TABLE)
		{
			printf("Eroare: lipseste sau este scris gresit keyword TABLE.\n");
			return 0;
		}
		strcpy(comanda, comanda + 6);
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
	}
	return 1;
}
