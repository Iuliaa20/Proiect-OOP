#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int ParseCreate2(char* numeTabel, char* tabelInfo, int* dimensiune, char* comanda)
{
	char* p;
	char *pColoana;
	int i,id = 0,tip_token = 0;
	bool ok = false;
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
		strcpy(comanda, comanda +6);
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
		strcpy(comanda, comanda + strlen(numeTabel) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != '(')
		{
			printf("Error ( expected\n");
			return 0;
		}
		
		do
		{
			strcpy(comanda, comanda + strlen(p)+1);
			//pColoana = strtok(comanda, ",");
			tip_comanda(comanda, &tip_token);
			if (tip_token != IDENTIFICATOR)
			{
				printf("Error column name expected ' %s'\n", p);
				return 0;
				//break;
			}
			else
			{
				for (i = 0;i < strlen(p);i++)
				{
					tabelInfo[id + i] = p[i];
				}
				tabelInfo[id + i] = ' ';
				id = id + (int)strlen(p) + 1;
			}
			strcpy(comanda, comanda + strlen(p) + 1);
			tip_comanda(comanda, &tip_token);
			bool isType = false;
			isType = (tip_token == INT || tip_token == FLOAT || tip_token == CHAR);
			if (isType == false)
			{
				printf("Error type column expected '%s'\n", p);
				return 0;
			}
			else
			{
				if (tip_token == CHAR)
				{
					strcpy(comanda,comanda + 5);
					tip_comanda(comanda, &tip_token);
					if (tip_token != '(')
					{
						printf("Error ( expected\n");
						return 0;
					}
					else
					{
						strcpy(comanda, comanda + 2);
						tip_comanda(comanda, &tip_token);
						if (tip_token != INTEGER_NB)
						{
							printf("Error '%d' integer size expected\n", tip_token);
							return 0;
						}
						else
						{
							ok = true;
							strcpy(comanda, comanda+ strlen(p)+1);
							tip_comanda(comanda, &tip_token);
							if (tip_token != ')')
							{
								printf("Error '%d' '%s' ) expected\n", tip_token, p);
								return 0;
							}
						}
					}	
				}
				
			}
			strcpy(comanda, comanda + strlen(p)+1);
			tip_comanda(comanda, &tip_token);
		} while (tip_token==',');
		
	}
	return 1;
}