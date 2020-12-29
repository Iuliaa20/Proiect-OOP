#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int ParseSelect(char* numeTabel, char* comanda, char* coloane)
{
	char* p;
	int i, tip_token = 0;
	bool moreColumns = 0;
	p = strtok(comanda, " ");
	if (p != NULL)
	{
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token == ALL || tip_token == IDENTIFICATOR)
		{
			if (tip_token == ALL)
			{
				strcpy(comanda, comanda + 4);
				tip_comanda(comanda, &tip_token);
				if (tip_token != FROM)
				{
					printf("Eroare: lipseste keyword FROM.\n");
					return 0;
				}
				strcpy(comanda, comanda + 5);
				tip_comanda(comanda, &tip_token);
				if (tip_token != IDENTIFICATOR)
				{
					printf("Eroare: lipseste numele tabelei.\n");
					return 0;
				}
				else
				{
					for (i = 0; i < strlen(p); i++)
					{
						numeTabel[i] = p[i];
					}
					numeTabel[i] = '\0';
				}
				return 2;
			}
			else
			{
				for (i = 0; i < strlen(p); i++)
				{
					coloane[i] = p[i];
				}
				coloane[i] = ' ';
				strcpy(comanda, comanda + strlen(p) + 1);
				tip_comanda(comanda, &tip_token);
				while (tip_token == ',')
				{
					moreColumns = 1;
					strcpy(comanda, comanda + strlen(p) + 1);
					tip_comanda(comanda, &tip_token);
					if (tip_token != IDENTIFICATOR)
					{
						printf("Eroare: lipseste numele coloanei. ' %s'\n", p);
						return 0;
					}
					else
					{
						strcat(coloane, p);
						strcat(coloane, " ");
					}
				}
				if (moreColumns)
				{
					strcpy(comanda, comanda + strlen(p) + 1);
					tip_comanda(comanda, &tip_token);
				}
				coloane[strlen(coloane) + 1] = '\0';
				if (tip_token != FROM)
				{
					printf("Eroare: keyword FROM este scris gresit.\n");
					return 0;
				}
				strcpy(comanda, comanda + strlen(p) + 1);
				tip_comanda(comanda, &tip_token);
				if (tip_token != IDENTIFICATOR)
				{
					printf("Eroare: lipseste numele tabelei.\n");
					return 0;
				}
				else
				{
					for (i = 0; i < strlen(p); i++)
					{
						numeTabel[i] = p[i];
					}
					numeTabel[i] = '\0';
				}
			}
		}
		else
		{
			printf("Eroare: nu exista coloanele selectate.\n");
			return 0;
		}
	}
	return 1;
}
