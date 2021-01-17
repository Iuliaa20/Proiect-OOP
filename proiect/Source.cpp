#include <iostream>
#include <sstream>
#include <iomanip>
#include "identificator.h"
#include <fstream>
#include "FisierText.h"
#include "FisierBinar.h"
#include "Date.h"
#include "Coloana.h"
#include <vector>
#include <iterator>
#include <list>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <exception>
#include "Index.h"
using namespace std;

int ParseCreate(char* numeTabel, char* tabelInfo, list<string> &coloane, int* dimensiune, char* comanda, list<string> &tipColoane);
int ParseDrop( char* numeTabel, char* comanda, int tip_token);
int ParseDisplay(char* numeTabel, char* comanda);
char ParseDelete(char check, char* numeTabel, char* numeColoanaWhere, char* valoareWhere,int &tipWhere, char* comanda, int tip_token);
int ParseUpdate(char* numeTabel, char* numeColoanaSet, char* valoareSet, int &tipSet, char* numeColoanaWhere, char* valoareWhere, int &tipWhere, char* comanda, char* tabelInfo);
int ParseSelect(char* numeTabel, char* comanda, char* coloane);
int ParseInsert(char* numeTabel, char* comanda, char* values, vector<int> &tipValues);
int ParseImport(char* numeTabel, char* comanda, char* numeFisier);
int ParseDropIndex(char* comanda, char* numeTabel, char* numeIndex, int tip_token);
int ParseCreateIndex(char* numeTabel, char* numeIndex, char* numeColoana, char* comanda);
void CreateBinary(char* numeTabel, char* tabelInfo);

int main(int argc, char* argv[])
{
	map<string, list<string>> mapColoaneBD, mapTipBD;
	map<string, multiset<int>> mapInt;
	map<string, multiset<float>> mapFloat;
	map<string, multiset<string>> mapString;
	map<string, multiset<int>> mapIndexInt;
	map<string, multiset<float>> mapIndexFloat;
	map<string, multiset<string>> mapIndexString;
	multiset<int> setInt; multiset<float> setFloat; multiset<string> setString;
	char* input, token;
	char* p;
	char* line;
	char* linie;
	char in[10000];
	int tip_token, existed, tip, sel =0, tipSet, tipWhere;
	FisierText f; FILE* e; FisierBinar k; Coloana c; FisierBinarIesire z; FisierTextComenzi hComenzi;
	
	int rezultat = 0; char check = 'O'; 
	char tabelInfo[100] = { '\0' };
	char numeTabel[100] = { '\0' };
	char numeIndex[100] = { '\0' };
	char numeImport[100] = { '\0' };
	char numeColoanaWhere[100] = { '\0' };
	char numeColoana[100] = { '\0' };
	char numeColoanaSet[100] = { '\0' };
	char coloane[1000] = { '\0' };
	char values[1000] = { '\0' };
	char valoareWhere[100] = { '\0' };
	char valoareSet[100] = { '\0' };
	
	
	if (argc > 6)
	{
		printf("Error too many files for input in main");
		return 0;
	}
	else
	{
		if (argc == 1)
		{
			/*string fi = "BINAR.bin",af;
			fstream w;bool ok = 1;
			w.open(fi, ios::in | ios::binary);
			//while (!w.eof())
			while (!w.eof())
			{
				getline(w, af);
				cout << af;
			}
			 /*string fi = "DATA.csv", af;
			 fstream w;bool ok = 1;
			 w.open(fi, ios::in | ios::binary);
			 //while (!w.eof())
			 while (!w.eof())
			 {
				 getline(w, af);
				 cout << af<<endl;// << " " << af.find(',') << "//";
				 char* o;
				 o = strtok((char*)af.c_str(), " ");
				 while (o != NULL)
				 {
					 if (o[strlen(o) - 1] == ',')
					 {
						 cout << o << " " << o[strlen(o) - 1]<<endl;
						 o = strtok(NULL, " ");
					 }
					 else
					 {
						// cout << "another found";
						 ok = 0;
						 break;
					 }
				 }
				 cout << o<<endl;
				 string aff;
				 aff = af.substr(af.length() - 1);
				cout << aff<<aff.c_str()<<endl;

				if (ok == 0)
					if (strcmp(o, aff.c_str()))
						cout << "altull";
					else
						cout << "reusit";
				//if (strcmp(o, aff.c_str()) != 0)
				//	cout << "another delimiter found";
			 }
			 w.close();
			//w.open(fi, ios::out | ios::trunc | ios::binary);
			//w << fi<<endl;
			//w << 2;
			//w.close();
			//while (w.is_open())
				  //while (getline(w, af))
				//for (int i = 0; i < 5;i++)*/
			/*string tastatura, tastaturaComenzi;
			cout << "Introdu numele fisierului in care vei stoca comenzile"<<endl;
			getline(std::cin, tastatura);
			DateComenzi dateComenzi;

			Date** pointers = nullptr;
			pointers = new Date* [4];
			pointers[0] = &dateComenzi;
			pointers[0]->creare((char*)tastatura.c_str());
			//dateComenzi.creare((char*)tastatura.c_str());

			cout << "Introdu comenzile pe care le vrei"<<endl;
			getline(std::cin, tastaturaComenzi);
			DateComenzi dateComenziScriere;
			pointers[1] = &dateComenziScriere;
			pointers[1]->scriere((char*)tastatura.c_str(), tastaturaComenzi);
			//dateComenziScriere.scriere((char*)tastatura.c_str(), tastaturaComenzi);
			//TESTARE CITIRE DATE COMENZI*/
			// Testare Date Import
			/*cout << "Introdu numele fisierului csv " << endl;
			getline(std::cin, tastatura);
			DateImport dateImport;
			pointers[2] = &dateImport;
			pointers[2]->creare((char*)tastatura.c_str());
			//dateImport.creare((char*)tastatura.c_str());

			cout << "Introdu valorile pe care le vrei" << endl;
			getline(std::cin, tastaturaComenzi);
			DateImport dateImportScriere;
			pointers[3] = &dateImportScriere;
			pointers[3]->scriere((char*)tastatura.c_str(), tastaturaComenzi);
			//dateImportScriere.scriere((char*)tastatura.c_str(), tastaturaComenzi);*/

			std::cout << "Please input your sql command:" << endl;
			string tmp;
			while (std::getline(std::cin, tmp))
			{
				if (tmp.empty())
					break;
				else
				{
					bool moreCommands = 0;
					transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
					input = (char*)tmp.c_str();
					p = strtok(input, " ");
					do
					{
						if (moreCommands)
						{
							input = strtok(NULL, " ");
							if (!input)
							{
								break;
							}
						}
						tip_comanda(input, &tip_token);
						switch (tip_token)
						{
						case CREATE:
						{
							list<string> listaColoane, listaTip;
							tip_comanda(input + 7, &tip_token);
							if (tip_token == TABLE)
							{
								int* dimensiune = new int[100];
								rezultat = ParseCreate(numeTabel, tabelInfo, listaColoane, dimensiune, input, listaTip);
								if (rezultat)
								{
									string nume = numeTabel;
									nume += ".txt";
									fstream h(nume.c_str(), ios::in);
									if (h.good())
										std::cout << "Error file exists";
									else {
										std::cout << "Ai creat tabela " << numeTabel << " cu coloanele " << tabelInfo << endl;
										f.fileTextCreate(numeTabel, tabelInfo);
										h.close();
										h.open(nume.c_str(), ios::out | ios::app);
										mapColoaneBD.insert(pair<string, list<string>>(numeTabel, listaColoane));
										mapTipBD.insert(pair<string, list<string>>(numeTabel, listaTip));
										for (list<string>::iterator it1 = listaColoane.begin(), it2 = listaTip.begin(); it1 != listaColoane.end() && it2 != listaTip.end();it1++, it2++)
										{
											h << *it2 << " ";
										}
										h.close();
										h.open(nume, ios::in);
										k.fileBinaryCreate(numeTabel, tabelInfo);
										/*for (map<string, list<string>>::iterator it = mapColoaneBD.begin();it != mapColoaneBD.end();it++)
										{
											std::cout << it->first << " lista coloane" << endl;
										}
										
										for (map<string, list<string>>::iterator it = mapTipBD.begin();it != mapTipBD.end();it++)
										{
											std::cout << it->first << " lista tip" << endl;
										}*/
										for (list<string>::iterator it1 = listaColoane.begin(), it2 = listaTip.begin();it1 != listaColoane.end(), it2 != listaTip.end();it1++, it2++)
										{
											if (*it2 == "INT")
											{
												string name = *it1;
												name += ".";
												name += numeTabel;
												mapInt.insert(pair<string, multiset<int>>(name, setInt));
											}
											else
												if (*it2 == "FLOAT")
												{
													string name = *it1;
													name += ".";
													name += numeTabel;
													mapFloat.insert(pair<string, multiset<float>>(name, setFloat));
												}
												else
													if (*it2 == "CHAR")
													{
														string name = *it1;
														name += ".";
														name += numeTabel;
														mapString.insert(pair<string, multiset<string>>(name, setString));

													}
										}
										
										//k.fileBinaryAfisare(numeTabel, tabelInfo);
										//ColoanaInt* pint = (ColoanaInt*)&c;
										//pint->afisare(tabelInfo, 
										/*if (tip == 1)
											cout << "Coloana int";
										else
											if (tip == 2)
												cout << "Coloana float";
											else
												if (tip == 3)
													cout << "Coloana string";*/
									}
								}
								break;
							}
							else
							{
								if (tip_token == INDEX)
								{
									rezultat = ParseCreateIndex(numeTabel, numeIndex, numeColoana, input);
									if (rezultat)
									{
										string nume = numeTabel;
										nume += ".txt";
										ifstream h(nume.c_str());
										if (!h.good())
											cout << "Error tabela DOES NOT  exist" << endl;
										else
										{
											string numeC = numeColoana, type;bool isColoana = 0;
											map<string, list<string>>::iterator it1 = mapColoaneBD.find(numeTabel);
											map<string, list<string>>::iterator it2 = mapTipBD.find(numeTabel);
											list<string>::iterator ic=it1->second.begin(), it=it2->second.begin();
											while (ic != it1->second.end() && it != it2->second.end())
											{
												if (*ic == numeC)
												{
													type = *it;
													isColoana = 1;
													break;
												}
												ic++;it++;
											}
											if (isColoana == 0)
												cout << "Nu exista coloana in tabel" << endl;
											else
											{
												IndexInt indI(numeIndex);IndexFloat indF(numeIndex); IndexString indS(numeIndex);
												if (type == "INT")
												{
													//Index* ind =&indI;
													//ind->creare();
													indI.creare();
													auto it = indI.mapIndexInt.find(numeIndex);
													mapIndexInt.insert(pair<string, multiset<int>>(numeIndex,it->second));
												}
												else
													if (type == "FLOAT")
													{
														//Index& ind = indF;
														indF.creare();
														auto it = indF.mapIndexFloat.find(numeIndex);
														mapIndexFloat.insert(pair<string, multiset<float>>(numeIndex, it->second));

													}
													else
														if (type == "CHAR")
														{
															//Index& ind = indS;
															indS.creare();
															auto it = indS.mapIndexString.find(numeIndex);
															mapIndexString.insert(pair<string, multiset<string>>(numeIndex, it->second));

														}
											}
											//cout << "Ai creat indexul " << numeIndex << " pentru coloana " << numeColoana << " din tabela " << numeTabel << endl;

										}
									}
									break;
								}
								else
								{
									cout << "Error TABLE or INDEX  missing\n";
									break;
								}
							}
						}
						case DROP:
						{

							tip_comanda(input + 5, &tip_token);
							if (tip_token == TABLE)
							{
								rezultat = ParseDrop(numeTabel, input, tip_token);
								if (rezultat)
								{
									if (remove(numeTabel) != 0)
									{
										f.fileTextDrop(numeTabel, existed);
										if (existed == 1)
										{
											string nume = numeTabel;
											map<string, list<string>>::iterator it = mapColoaneBD.find(nume);
											if (it != mapColoaneBD.end())
											{
												cout << it->first << endl;
												mapColoaneBD.erase(nume);
												mapTipBD.erase(nume);
											}
											cout << "Sters" << endl;
										}
										else
											cout << "NU EXISTA" << endl;
									}

								}

								break;
							}
							else
							{
								if (tip_token == INDEX)
								{
									rezultat = ParseDropIndex(input, numeTabel, numeIndex, tip_token);
									if (rezultat)
									{
										IndexInt indI(numeIndex);IndexFloat indF(numeIndex); IndexString indS(numeIndex);
										//cout << "Ai sters indexul: " << numeIndex << endl;
										//Index ind;
										//string numeC = numeColoana, type;bool isColoana = 0;
										//map<string, list<string>>::iterator it1 = mapColoaneBD.find(numeTabel);
										//map<string, list<string>>::iterator it2 = mapTipBD.find(numeTabel);
										map<string, multiset<int>>::iterator iti = mapIndexInt.find(numeIndex);
										//IndexInt indI(numeIndex);IndexFloat indF(numeIndex); IndexString indS(numeIndex);

										if (iti != mapIndexInt.end())
										{
											Index& ind = indI;
											ind.drop();
										}
										else
										{
											map<string, multiset<float>>::iterator itf = mapIndexFloat.find(numeIndex);
											if (itf != mapIndexFloat.end())
											{
												Index& ind = indF;
												ind.drop();
											}
											else
											{
												map<string, multiset<string>>::iterator its = mapIndexString.find(numeIndex);
												if (its != mapIndexString.end())
												{
													Index& ind = indS;
													ind.drop();
												}
												else
													cout << "Indexul de sters nu exista" << endl;
											}
										}
										
									}
									break;
								}
								else
								{
									cout << "Error TABLE or INDEX  missing\n";
									break;
								}
							}
						}
						case DISPLAY:
						{
							rezultat = ParseDisplay(numeTabel, input);
							if (rezultat)
							{
								string nume = numeTabel;
								nume += ".txt";
								ifstream h(nume.c_str());
								if (!h.good())
									cout << "Error file DOES NOT  exist";
								else
								{
									cout << "Ai afisat tabela: " << numeTabel << endl;
									f.fileTextDisplay(numeTabel, tabelInfo);
									string af;
									while (!h.eof())
									{
										getline(h, af);
										cout << af << endl;
									}
								}
							}
							break;
						}
						case DELETE:
						{
							rezultat = ParseDelete(check, numeTabel, numeColoanaWhere, valoareWhere, tipWhere, input, tip_token);
							if ((char)rezultat == 'Y')
							{
								string nume = numeTabel;
								nume += ".txt";
								ifstream h(nume.c_str());
								if (!h.good())
									cout << "Error file DOES NOT  exist";
								else
								{
									map<string, list<string>>::iterator it1 = mapColoaneBD.find(numeTabel);
									map<string, list<string>>::iterator it2 = mapTipBD.find(numeTabel);
									string type, numeC = "",aux = "";
									for (int i = 0;i < strlen(numeColoanaWhere);i++)
									{
										numeC += numeColoanaWhere[i];
										aux += numeColoanaWhere[i];
									}
									bool found = 0;
									for (list<string>::iterator ic = it1->second.begin(), it = it2->second.begin();ic != it1->second.end(), it != it2->second.end();ic++, it++)
									{
										if (numeC == *ic)
										{
											found = 1;
											type = *it;
											break;
										}
									}
									if (found == 0)
										cout << "Coloana de sters nu exista in tabela" << endl;
									else
									{
										bool deleted = 0, isType = 1;
										if (tipWhere == INTEGER_NB)
											if (type != "INT")
												isType = 0;
											else
												if (tipWhere == FLOAT_NB)
												{
													if (type != "FLOAT")
														isType = 0;
												}
												else
													if (tipWhere == IDENTIFICATOR)
														if (type != "CHAR")
															isType = 0;
										if (isType == 0)
											cout << "Valoarea de sters nu este tipul corespunzator coloanei" << endl;
										else
										{
											numeC += ".";
											numeC += numeTabel;

											int index = 0, ind = 0;
											if (type == "INT")
											{
												map<string, multiset<int>>::iterator itI = mapInt.find(numeC);
												multiset<int>::iterator iti;
												for (iti = itI->second.begin();iti != itI->second.end();iti++)
												{
													index++;
													if (atoi(valoareWhere) == *iti)
													{
														itI->second.erase(*iti);
														deleted = 1;
														break;
													}
												}
												for (list<string>::iterator iter1 = it1->second.begin(), iter2 = it2->second.begin();iter1 != it1->second.end(), iter2 != it2->second.end();iter1++, iter2++)
												{
													if (*iter1 != aux)
													{
														string numec = *iter1;
														numec += ".";
														numec += numeTabel;
														if (*iter2 == "INT")
														{
															map<string, multiset<int>>::iterator itInt = mapInt.find(numec);
															multiset<int>::iterator itint = itInt->second.begin();
															while (itint != itInt->second.end())
															{
																ind++;
																if (ind == index)
																{
																	itInt->second.erase(*itint);
																	break;
																}
																itint++;
															}
														}
														else
															if (*iter2 == "FLOAT")
															{
																map<string, multiset<float>>::iterator itFloat = mapFloat.find(numec);
																multiset<float>::iterator itfloat = itFloat->second.begin();
																while (itfloat != itFloat->second.end())
																{
																	ind++;
																	if (ind == index)
																	{
																		itFloat->second.erase(*itfloat);
																		break;
																	}
																	itfloat++;
																}
															}
															else
																if (*iter2 == "CHAR")
																{
																	map<string, multiset<string>>::iterator itString = mapString.find(numec);
																	multiset<string>::iterator itstring = itString->second.begin();
																	while (itstring != itString->second.end())
																	{
																		ind++;
																		if (ind == index)
																		{
																			itString->second.erase(*itstring);
																			break;
																		}
																		itstring++;
																	}
																}
													}
												}
											}
											else
												if (type == "FLOAT")
												{
													map<string, multiset<float>>::iterator itF = mapFloat.find(numeC);
													multiset<float>::iterator itf;
													for (itf = itF->second.begin(); itf != itF->second.end();itf++)
													{
														index++;
														if (atof(valoareWhere) == *itf)
														{
															itF->second.erase(*itf);
															deleted = 1;
															break;
														}
													}
													for (list<string>::iterator iter1 = it1->second.begin(), iter2 = it2->second.begin();iter1 != it1->second.end(), iter2 != it2->second.end();iter1++, iter2++)
													{
														if (*iter1 != aux)
														{
															string numec = *iter1;
															numec += ".";
															numec += numeTabel;
															if (*iter2 == "INT")
															{
																map<string, multiset<int>>::iterator itInt = mapInt.find(numec);
																multiset<int>::iterator itint = itInt->second.begin();
																while (itint != itInt->second.end())
																{
																	ind++;
																	if (ind == index)
																	{
																		itInt->second.erase(*itint);
																		break;
																	}
																	itint++;
																}
															}
															else
																if (*iter2 == "FLOAT")
																{
																	map<string, multiset<float>>::iterator itFloat = mapFloat.find(numec);
																	multiset<float>::iterator itfloat = itFloat->second.begin();
																	while (itfloat != itFloat->second.end())
																	{
																		ind++;
																		if (ind == index)
																		{
																			itFloat->second.erase(*itfloat);
																			break;
																		}
																		itfloat++;
																	}
																}
																else
																	if (*iter2 == "CHAR")
																	{
																		map<string, multiset<string>>::iterator itString = mapString.find(numec);
																		multiset<string>::iterator itstring = itString->second.begin();
																		while (itstring != itString->second.end())
																		{
																			ind++;
																			if (ind == index)
																			{
																				itString->second.erase(*itstring);
																				break;
																			}
																			itstring++;
																		}
																	}
														}
													}
												}
												else
													if (type == "CHAR")
													{
														map<string, multiset<string>>::iterator itS = mapString.find(numeC);
														multiset<string>::iterator its;
														for (its = itS->second.begin();its != itS->second.end();its++)
														{
															index++;
															string val = "";
															for (int i = 0;i < strlen(valoareWhere);i++)
																val += valoareWhere[i];
															if (val == *its)
															{
																itS->second.erase(*its);
																deleted = 1;
																break;
															}
														}
														for (list<string>::iterator iter1 = it1->second.begin(), iter2 = it2->second.begin();iter1 != it1->second.end(), iter2 != it2->second.end();iter1++, iter2++)
														{
															if (*iter1 != aux)
															{
																string numec = *iter1;
																numec += ".";
																numec += numeTabel;
																if (*iter2 == "INT")
																{
																	map<string, multiset<int>>::iterator itInt = mapInt.find(numec);
																	multiset<int>::iterator itint = itInt->second.begin();
																	while (itint != itInt->second.end())
																	{
																		ind++;
																		if (ind == index)
																		{
																			itInt->second.erase(*itint);
																			break;
																		}
																		itint++;
																	}
																}
																else
																	if (*iter2 == "FLOAT")
																	{
																		map<string, multiset<float>>::iterator itFloat = mapFloat.find(numec);
																		multiset<float>::iterator itfloat = itFloat->second.begin();
																		while (itfloat != itFloat->second.end())
																		{
																			ind++;
																			if (ind == index)
																			{
																				itFloat->second.erase(*itfloat);
																				break;
																			}
																			itfloat++;
																		}
																	}
																	else
																		if (*iter2 == "CHAR")
																		{
																			map<string, multiset<string>>::iterator itString = mapString.find(numec);
																			multiset<string>::iterator itstring = itString->second.begin();
																			while (itstring != itString->second.end())
																			{
																				ind++;
																				if (ind == index)
																				{
																					itString->second.erase(*itstring);
																					break;
																				}
																				itstring++;
																			}
																		}
															}
														}
													}
											if (deleted == 1)
											{
												cout << "Ai sters inregistrarile din tabela " << numeTabel << " unde coloana " << numeColoanaWhere << " are valoarea " << valoareWhere << endl;
												k.fileBinaryAfisare(numeTabel, mapInt, mapFloat, mapString);
											}
											else
												cout << "Valoarea cautata de sters nu exista in tabela"<<endl;
										}
										
									}
								}
							}
							break;
						}
						case UPDATE:
						{
							char* tabelInfo = new char[10000];
							rezultat = ParseUpdate(numeTabel, numeColoanaSet, valoareSet, tipSet, numeColoanaWhere, valoareWhere,tipWhere, input, tabelInfo);
							if (rezultat)
							{
								string nume = numeTabel;
								nume += ".txt";
								ifstream h(nume.c_str());
								if (!h.good())
									cout << "Error file DOES NOT  exist";
								else
								{
									map<string, list<string>>::iterator it1 = mapColoaneBD.find(numeTabel);
									map<string, list<string>>::iterator it2 = mapTipBD.find(numeTabel);
									string typeC, typeS, numeC = "", aux = "", numeS="";
									for (int i = 0;i < strlen(numeColoanaWhere);i++)
										numeC += numeColoanaWhere[i];
									for (int i = 0;i < strlen(numeColoanaSet);i++)
										numeS += numeColoanaSet[i];
									bool foundC = 0, foundS=0;
									for (list<string>::iterator ic = it1->second.begin(), it = it2->second.begin();ic != it1->second.end(), it != it2->second.end();ic++, it++)
									{
										if (numeC == *ic)
										{
											foundC = 1;
											typeC = *it;
											break;
										}
									}
									if (foundC == 0)
										cout << "Coloana care conditioneaza nu exista in tabela" << endl;
									else
									{

										for (list<string>::iterator ic = it1->second.begin(), it = it2->second.begin();ic != it1->second.end(), it != it2->second.end();ic++, it++)
										{
											if (numeS == *ic)
											{
												foundS = 1;
												typeS = *it;
												break;
											}
										}
										if (foundS == 0)
											cout << "Coloana de updatat nu exista in tabela" << endl;
										else
										{
											bool isType = 1;
											if (tipWhere == INTEGER_NB)
											{
												if (typeC != "INT")
													isType = 0;
											}
											else
												if (tipWhere == FLOAT_NB)
												{
													if (typeC != "FLOAT")
														isType = 0;
												}
												else
													if (tipWhere == IDENTIFICATOR)
													{
														if (typeC != "CHAR")
															isType = 0;
													}
											if (isType == 0)
												cout << "Valoarea coloanei cautate nu este tipul corespunzator" << endl;
											else
											{
												bool isTypeS = 1;
												if (tipSet == INTEGER_NB)
												{
													if (typeS != "INT")
														isTypeS = 0;
												}
												else
													if (tipSet == FLOAT_NB)
													{
														if (typeS != "FLOAT")
															isTypeS = 0;
													}
													else
														if (tipSet == IDENTIFICATOR)
														{
															if (typeS != "CHAR")
																isTypeS = 0;
														}
												if (isTypeS == 0)
													cout << "Valoarea coloanei de updatat nu este tipul corespunzator" << endl;
												else
												{
													numeC += "."; numeS += ".";
													numeC += numeTabel; numeS += numeTabel;
													bool isSet = 1;
													if (typeC == "INT")
													{
														map<string, multiset<int>>::iterator itI = mapInt.find(numeC);
														multiset<int>::iterator iti = itI->second.find(atoi(valoareWhere));
														int x = distance(itI->second.begin(), iti);
														if (typeS == "INT")
														{
															map<string, multiset<int>>::iterator itIS = mapInt.find(numeS);
															multiset<int>::iterator itis = itIS->second.begin();
															advance(itis, x);
															if (itis != itIS->second.end())
															{
																itIS->second.erase(*itis);
																itIS->second.insert(atoi(valoareSet));
															}
															else
																isSet = 0;
														}
														else
															if (typeS == "FLOAT")
															{
																map<string, multiset<float>>::iterator itFS = mapFloat.find(numeS);
																multiset<float>::iterator itfs = itFS->second.begin();
																advance(itfs, x);
																if (itfs != itFS->second.end())
																{
																	itFS->second.erase(*itfs);
																	itFS->second.insert(atof(valoareSet));
																}
																else
																	isSet = 0;
															}
															else
																if (typeS == "CHAR")
																{
																	map<string, multiset<string>>::iterator itSS = mapString.find(numeS);
																	multiset<string>::iterator itss = itSS->second.begin();
																	advance(itss, x);
																	if (itss != itSS->second.end())
																	{
																		itSS->second.erase(*itss);
																		itSS->second.insert(valoareSet);
																	}
																	else
																		isSet = 0;
																}
													}
													else
														if (typeC == "FLOAT")
														{
															map<string, multiset<float>>::iterator itF = mapFloat.find(numeC);
															multiset<float>::iterator itf = itF->second.find(atof(valoareWhere));
															int x = distance(itF->second.begin(), itf);
															if (typeS == "INT")
															{
																map<string, multiset<int>>::iterator itIS = mapInt.find(numeS);
																multiset<int>::iterator itis = itIS->second.begin();
																advance(itis, x);
																if (itis != itIS->second.end())
																{
																	itIS->second.erase(*itis);
																	itIS->second.insert(atoi(valoareSet));
																}
																else
																	isSet = 0;
															}
															else
																if (typeS == "FLOAT")
																{
																	map<string, multiset<float>>::iterator itFS = mapFloat.find(numeS);
																	multiset<float>::iterator itfs = itFS->second.begin();
																	advance(itfs, x);
																	if (itfs != itFS->second.end())
																	{
																		itFS->second.erase(*itfs);
																		itFS->second.insert(atof(valoareSet));
																	}
																	else
																		isSet = 0;
																}
																else
																	if (typeS == "CHAR")
																	{
																		map<string, multiset<string>>::iterator itSS = mapString.find(numeS);
																		multiset<string>::iterator itss = itSS->second.begin();
																		advance(itss, x);
																		if (itss != itSS->second.end())
																		{
																			itSS->second.erase(*itss);
																			itSS->second.insert(valoareSet);
																		}
																		else
																			isSet = 0;
																	}
														}
														else
															if (typeC == "CHAR")
															{
																map<string, multiset<string>>::iterator itS = mapString.find(numeC);
																multiset<string>::iterator its = itS->second.find(valoareWhere);
																int x = distance(itS->second.begin(), its);
																if (typeS == "INT")
																{
																	map<string, multiset<int>>::iterator itIS = mapInt.find(numeS);
																	multiset<int>::iterator itis = itIS->second.begin();
																	advance(itis, x);
																	if (itis != itIS->second.end())
																	{
																		itIS->second.erase(*itis);
																		itIS->second.insert(atoi(valoareSet));
																	}
																	else
																		isSet = 0;
																}
																else
																	if (typeS == "FLOAT")
																	{
																		map<string, multiset<float>>::iterator itFS = mapFloat.find(numeS);
																		multiset<float>::iterator itfs = itFS->second.begin();
																		advance(itfs, x);
																		if (itfs != itFS->second.end())
																		{
																			itFS->second.erase(*itfs);
																			itFS->second.insert(atof(valoareSet));
																		}
																		else
																			isSet = 0;
																	}
																	else
																		if (typeS == "CHAR")
																		{
																			map<string, multiset<string>>::iterator itSS = mapString.find(numeS);
																			multiset<string>::iterator itss = itSS->second.begin();
																			advance(itss, x);
																			if (itss != itSS->second.end())
																			{
																				itSS->second.erase(*itss);
																				itSS->second.insert(valoareSet);
																			}
																			else
																				isSet = 0;
																		}
															}
													if (isSet == 0)
														cout << "Valoarea care conditioneaza nu exista" << endl;
													else
													{
														cout << "Ai updatat tabela " << numeTabel << " modificand coloana " << numeColoanaSet << " cu valoarea " << valoareSet << " unde coloana " << numeColoanaWhere << " are valoarea " << valoareWhere << endl;
														k.fileBinaryAfisare(numeTabel, mapInt, mapFloat, mapString);
													}
												}
											}
											
										}

									}

								}
							}
							break;
						}
						case SELECT:
						{
							
							rezultat = ParseSelect(numeTabel, input, coloane);
							string nume = numeTabel;
							nume += ".txt";
							ifstream h(nume.c_str());
							if (!h.good())
								cout << "Error file DOES NOT  exist";
							else
							{
								if (rezultat == 2)
								{
									sel++;
									string numeSelect = "SELECT_";
									numeSelect += to_string(sel);
									numeSelect += ".txt";
									ofstream fileSelect;
									fileSelect.open(numeSelect, ios::out);
									cout << "Ai selectat toate coloanele din tabela " << numeTabel << endl;
									map<string, list<string>>::iterator it1 = mapColoaneBD.find(numeTabel);
									map<string, list<string>>::iterator it2 = mapTipBD.find(numeTabel);
									for (list<string>::iterator itC = it1->second.begin(), itT = it2->second.begin();itC != it1->second.end(), itT != it2->second.end();itC++, itT++)
									{
										string name = *itC;
										name += ".";
										name += numeTabel;
										cout << "Valorile coloanei " << *itC << endl;
										if (*itT == "INT")
										{
											map < string, multiset<int>>::iterator iter;
											iter = mapInt.find(name);
											for (multiset<int>::iterator iti = iter->second.begin();iti != iter->second.end();iti++)
											{
												cout << *iti << " ";
												fileSelect << *iti << " ";
											}
											cout << endl;
											fileSelect << endl;
										}
										else
											if (*itT == "FLOAT")
											{
												map < string, multiset<float>>::iterator iter;
												iter = mapFloat.find(name);
												for (multiset<float>::iterator itf = iter->second.begin();itf != iter->second.end();itf++)
												{
													cout << *itf << " ";
													fileSelect << *itf << " ";
												}
												cout << endl;
												fileSelect << endl;
											}
											else
												if (*itT == "CHAR")
												{
													map < string, multiset<string>>::iterator iter;
													iter = mapString.find(name);
													for (multiset<string>::iterator its = iter->second.begin();its != iter->second.end();its++)
													{
														cout << *its << " ";
														fileSelect << *its << " ";
													}
													cout << endl;
													fileSelect << endl;
												}
										
									}
								}
								else
								{
									if (rezultat == 1)
									{
										bool cont = 1;
										map<string, list<string>>::iterator it1 = mapColoaneBD.find(numeTabel);
										p = strtok(coloane, " ");
										while (p != NULL)
										{
											string numeC = "";
											for (int i = 0;i < strlen(p);i++)
												numeC += p[i];
											bool found = 0;
											for (list<string>::iterator it = it1->second.begin();it != it1->second.end();it++)
											{
												if (numeC == *it)
												{
													found = 1;
													break;
												}
											}
											if (found == 0)
											{
												cont = 0;
												break;
											}
											p = strtok(NULL, " ");
										}
										if (cont == 0)
											std::cout << "Coloana cautata nu exista in tabel" << endl;
										else
										{
											
											sel++;
											string numeSelect = "SELECT_";
											numeSelect += to_string(sel);
											numeSelect += ".txt";
											ofstream fileSelect;
											fileSelect.open(numeSelect, ios::out);
											std::cout << "Ai selectat " << coloane << "din tabela " << numeTabel << endl;
											map<string, list<string>>::iterator it2 = mapTipBD.find(numeTabel);
											char *q;
											q = strtok(coloane, " ");
											while (q != NULL)
											{
												string numeC = "";
												for (int i = 0;i < strlen(q);i++)
													numeC += q[i];
												string tip;
												//map<string, list<string>>::iterator it2 = mapTipBD.find(numeTabel);
												for (list<string>::iterator ic = it1->second.begin(), it = it2->second.begin();ic != it1->second.end(), it != it2->second.end();ic++, it++)
													if (*ic == numeC)
														tip = *it;
												numeC += ".";
												numeC += numeTabel;
												if (tip == "INT")
												{
														map < string, multiset<int>>::iterator iter;
														iter = mapInt.find(numeC);
														for (multiset<int>::iterator iti = iter->second.begin();iti != iter->second.end();iti++)
														{
															cout << *iti << " ";
															fileSelect << *iti << " ";
														}
														cout << endl;
														fileSelect << endl;
														//if (itC == it1->second.begin())
														//	cout << *iti<<" ";
														//else
												}
													else
														if (tip == "FLOAT")
														{
															map < string, multiset<float>>::iterator iter;
															iter = mapFloat.find(numeC);
															for (multiset<float>::iterator itf = iter->second.begin();itf != iter->second.end();itf++)
															{
																cout << *itf << " ";
																fileSelect << *itf << " ";
															}
															cout << endl;
															fileSelect << endl;
															//if (itC == it1->second.begin())
															//	cout << *itf << " ";
															//else
															//{
															//cout << *itf << " ";
															//itf++;
															//}
														}
														else
															if (tip == "CHAR")
															{
																map < string, multiset<string>>::iterator iter;
																iter = mapString.find(numeC);
																for (multiset<string>::iterator its = iter->second.begin();its != iter->second.end();its++)
																{
																	cout << *its << " ";
																	fileSelect << *its << " ";
																}
																cout << endl;
																fileSelect << endl;
																//if (itC == it1->second.begin())
																//	cout << *its << " ";
																//else
																//{
																//	cout << *its << " ";
																//	its++;
																//}
															}
											 q = strtok(NULL, " ");
											}
										}
									}
								}
							}
							break;
						}
						case INSERT:
						{
							vector<int> listaTipValues;
							rezultat = ParseInsert(numeTabel, input, values, listaTipValues);
							if (rezultat)
							{
								string nume = numeTabel;
								nume += ".txt";
								fstream h(nume.c_str(), ios::in);
								if (!h.good())
									std::cout << "Error file DOES NOT  exist";
								else
								{
									string numeaux = numeTabel;
									map<string, list<string>>::iterator it = mapTipBD.find(numeaux);
									std::cout << it->first;
									int nrColoaneTabel = it->second.size();
									int nrValori = listaTipValues.size();
									std::cout << nrColoaneTabel << " " << nrValori<<endl;
									if (nrColoaneTabel != nrValori)
										std::cout << "Numarul de valori inserate nu coincide cu numarul de coloane" << endl;
									else
									{
										int val;bool introdus = 1;
										list<string>::iterator itBD = it->second.begin();
										vector<int>::iterator itValues = listaTipValues.begin();
										while (itValues != listaTipValues.end())
										{
											if (*itBD == "INT")
											{
												val = INTEGER_NB;
											}
											else
											{
												if (*itBD == "FLOAT")
													val = FLOAT_NB;
												else
													if (*itBD == "CHAR")
														val = IDENTIFICATOR;
											}
											if (val != *itValues)
											{
												introdus = 0;
												break;
											}
											itBD++;itValues++;
										}
										if (introdus)
										{
											std::cout << "Ai inserat in tabela " << numeTabel << " valorile " << values << endl;
											char* p;
											p = strtok(values, " ");
											
												for (map<string, list<string>>::iterator it1 = mapColoaneBD.begin(), it2 = mapTipBD.begin();it1 != mapColoaneBD.end(), it2 != mapTipBD.end();it1++, it2++)
												{
													list<string>::iterator itC = it1->second.begin(), itL = it2->second.begin();
													while (p != NULL&& itC != it1->second.end()&& itL != it2->second.end())
													{
														string name = *itC;
														name += ".";
														name += numeTabel;

														if (*itL == "INT")
															setInt.insert(atoi(p));
														else
															if (*itL == "FLOAT")
																setFloat.insert(atof(p));
															else
																if (*itL == "CHAR")
																{
																	string s = "";
																	for (int i = 0;i < strlen(p);i++)
																		s += p[i];
																	setString.insert(s);
																}
														itC++;itL++;p = strtok(NULL, " ");

													}
													for (list<string>::iterator itc = it1->second.begin(), itl=it2->second.begin();itc != it1->second.end(),itl!=it2->second.end();itc++,itl++)
													{
														string name = *itc;
														name += ".";
														name += numeTabel;
														if (*itl == "INT")
														{
															map<string, multiset<int>>::iterator iter;
															iter = mapInt.find(name);
															if(iter!=mapInt.end())
																mapInt.erase(iter);
															mapInt.insert(pair<string, multiset<int>>(name, setInt));
														}
														else
														{
															if (*itl == "FLOAT")
															{
																map<string, multiset<float>>::iterator iter;
																iter = mapFloat.find(name);
																if (iter != mapFloat.end())
																	mapFloat.erase(iter);
																mapFloat.insert(pair<string, multiset<float>>(name, setFloat));
															}
															else
																if (*itl == "CHAR")
																{
																	map<string, multiset<string>>::iterator iter;
																	iter = mapString.find(name);
																	if (iter != mapString.end())
																		mapString.erase(iter);
																	mapString.insert(pair<string, multiset<string>>(name, setString));
																}
														}
													}
												}
											z.fileBinaryInsert(numeTabel, values, mapInt, mapFloat, mapString);
										}
										else
											std::cout << "Valoarile introduse nu coincid cu tipul coloanelor" << endl;
									}
								}
							}
							break;
						}
						case IMPORT:
						{
							rezultat = ParseImport(numeTabel, input, numeImport);
							if (rezultat)
							{
								string nume = numeTabel;
								nume += ".txt";
								ifstream h(nume.c_str());
								if (!h.good())
									cout << "Error file DOES NOT  exist";
								else
								{
									string nume = numeImport;
									nume += ".csv";
									string af;
									fstream w;bool ok = 1, okk = 1;
									w.open(nume, ios::in | ios::binary);
									//while (!w.eof())
									while (!w.eof())
									{
										getline(w, af);
										cout << af << endl;// << " " << af.find(',') << "//";
										char* o;
										o = strtok((char*)af.c_str(), " ");
										while (o != NULL)
										{
											if (o[strlen(o) - 1] == ',')
											{
												cout << o << " " << o[strlen(o) - 1] << endl;
												o = strtok(NULL, " ");
											}
											else
											{
												// cout << "another found";
												ok = 0;
												break;
											}
										}
										cout << o << endl;
										string aff;
										aff = af.substr(af.length() - 1);
										cout << aff << aff.c_str() << endl;

										if (ok == 0)
											if (strcmp(o, aff.c_str()))
											{
												okk = 0;
												cout << "altull";
											}
											else
												cout << "reusit";
									}
									k.importCSV(numeTabel, numeImport, existed);
									if (okk == 0)
										cout << "Nu se foloseste separatorul corect";
									else
									{
										cout << "Ai importat in tabela " << numeTabel << " valorile din fisierul CSV: " << numeImport << endl;


									}
								}
							}
							break;
						}
						default:
							{
								cout << "Error illegal command\n";
								break;
							}
						}
						//strcpy(input, input + 2);
						tip_comanda(input, &tip_token);
						if (tip_token == ';')
						{
							moreCommands = 1;
						}
					} while (tip_token == ';');
				}
			}
			
		}
		else
		{
			if (argc >= 2 && argc <= 6)
			{
				bool txt = 1;
				for (int i = 1;i < argc;i++)
				{
					if (strstr(argv[i], ".txt") == NULL)
					{
						cout << "Error not all text files";
						txt = 0;
						break;
					}
				}
				if (txt)
				{
					for (int i = 1;i < argc;i++)
					{
						ifstream h(argv[i]);
						if (!h.good())
							cout << "Error file DOES NOT  exist, so it cannot be used as an argument";
						else
						{
							hComenzi.fileTextCitire(argc, argv, i);
						}
					}
				}
			}
		}
	}
}