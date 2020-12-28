#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int ParseDisplay(char* numeTabel, char* comanda)
{
	char* p;
	int i, tip_token = 0;
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
			return 0;
		}
		//p = strtok(comanda, " ");
		strcpy(comanda, comanda + 6);
		tip_comanda(comanda, &tip_token);
		if (tip_token != IDENTIFICATOR)
		{
			printf("Error table name expected\n");
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
	}
	return 1;
}