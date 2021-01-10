#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int ParseCreate(char* numeTabel, char* tabelInfo, int* dimensiune, char* comanda)
{
	char* p;
	int i,id = 0,tip_token = 0;
	bool ok = false;
	p = strtok(comanda, " ");
	if (p != NULL)
	{
		strcpy(comanda, comanda + 13);
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
		strcpy(comanda, comanda + strlen(numeTabel) + 1);
		tip_comanda(comanda, &tip_token);
		if (tip_token != '(')
		{
			printf("Eroare lipseste ( \n");
			return 0;
		}
		
		do
		{
			strcpy(comanda, comanda + strlen(p)+1);
			tip_comanda(comanda, &tip_token);
			if (tip_token != IDENTIFICATOR)
			{
				printf("Eroare: lipseste nume coloana ' %s'\n", p);
				return 0;
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
				printf("Eroare: se asteapta tipul coloanei '%s' \n", p);
				return 0;
			}
			else
			{
				if (tip_token == INT)
				{
					tabelInfo[id] = 'I';
					tabelInfo[id + 1] = ' ';
					id = id + 2;
				}
				else
				{
					if (tip_token == FLOAT)
					{
						tabelInfo[id] = 'F';
						tabelInfo[id+1] = ' ';
						id = id + 2;
					}
					else
						if (tip_token == CHAR)
						{
							strcpy(comanda, comanda + 5);
							tip_comanda(comanda, &tip_token);
							if (tip_token != '(')
							{
								printf("Eroare: lipseste ( \n");
								return 0;
							}
							else
							{
								strcpy(comanda, comanda + 2);
								tip_comanda(comanda, &tip_token);
								if (tip_token != INTEGER_NB)
								{
									printf("Eroare: se asteapta dimensiune '%d' integer \n", tip_token);
									return 0;
								}
								else
								{
									tabelInfo[id] = 'C';
									tabelInfo[id + 1] = ' ';
									id = id + 2;
									strcpy(comanda, comanda + strlen(p) + 1);
									tip_comanda(comanda, &tip_token);
									if (tip_token != ')')
									{
										printf("Eroare: lipseste '%d' '%s' ) \n", tip_token, p);
										return 0;
									}
								}
							}
						}
				}
				
			}
			strcpy(comanda, comanda + strlen(p)+1);
			tip_comanda(comanda, &tip_token);
			if (tip_token == ')')
			{
				ok = 1;
				break;
			}
			
		} while (tip_token==',');
		if (!ok)
		{
			printf("Eroare: lipseste ) \n");
			return 0;
		}
		
	}
	return 1;
}
