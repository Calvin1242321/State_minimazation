#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;


void readfile(ifstream&);
int main(int argc, char** argv)
{
	if (argc == 2)
	{
		ifstream fin(argv[1]);
		if (!fin)
		{
			cout << "file error!" << endl;
			return -1;
		}
		else
		{
			readfile(fin);
		}
	}
	else
		return -1;
}

void readfile(ifstream& fin)
{
}