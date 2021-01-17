#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int ParseDrop( char* numeTabel, char* comanda, int tip_token)
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
			printf("Eroare: lipseste nume tabela\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				numeTabel[i] = p[i];
			}
			numeTabel[i] = '\0';
			//return 1;
		}
		strcpy(comanda, comanda + strlen(p) + 1);
	}
	return 1;
}
