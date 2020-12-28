#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

char ParseDrop(char check, char* numeTabel, char* comanda, int tip_token)
{
	char* p;
	int i;
	p = strtok(comanda, " ");
	//p = strtok(NULL, " ");
	if (p != NULL)
	{
		//p = identifyOtherKeywords(comanda, &tip_token);
		strcpy(comanda, comanda + strlen(p) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != TABLE)
		{
			printf("Error keyword TABLE expected\n");
			check = 'N';
			return check;
		}
		//p = strtok(comanda, " ");
		strcpy(comanda, comanda + 6);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Error table name expected\n");
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
			return check = 'Y';
		}
	}
}