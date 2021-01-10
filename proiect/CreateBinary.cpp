#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

void CreateBinary( char* numeTabel, char* tabelInfo)
{
	string numeBinar = numeTabel;
	numeBinar += ".bin";
	ofstream g(numeBinar, ios::binary);
	int length = strlen(tabelInfo);
	g.write((char*)&length, sizeof(length));
	g.write(tabelInfo, length + 1);
	g.close();

}