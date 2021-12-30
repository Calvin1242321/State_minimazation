#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

typedef struct sh
{
	string f0;
	string f1;
	bool remove = true;
	bool keep = false;
}Cell;

//void save(string fileName, string filetitle, node* n, int size)
//void readfile(ifstream&);

void save(char** arr, int size, char* alphalist, bool* alphasave, int size2, char startp);

int convertEngInt(char input);
int readfile();

int main(int argc, char** argv)
{
	/*if (argc == 2)
	{
		ifstream fin(argv[1]);
		if (!fin)
		{
			cout << "file error!" << endl;
			return -1;
		}
		else
			readfile(fin);


	}
	else
		return -1;*/
	readfile();
}

//void readfile(ifstream& fin)

int readfile()
{
	string s;
	int inputN = 0;				// 1 ~ 2
	int outputN = 0;			// 1
	int statementN = 0;			// 4 ~ 6
	int alphabetN = 0;
	char startP;
	cin >> s;
	cin >> s;		
	cin >> inputN;	//i
	cin >> s;		
	cin >> outputN;	//o
	cin >> s;		
	cin >> statementN;	//p
	cin >> s;		
	cin >> alphabetN;	//s
	cin >> s;		
	cin >> startP;		//r

	char** state_arr = new char* [statementN];
	for (int i = 0;i < statementN;i++)
		state_arr[i] = new char[4];

	char* alphalist = new char[alphabetN];
	for (int i = 0;i < alphabetN;i++)
	{
		switch (i)
		{
		case 0:
			alphalist[i] = 'a';
			break;
		case 1:
			alphalist[i] = 'b';
			break;
		case 2:
			alphalist[i] = 'c';
			break;
		case 3:
			alphalist[i] = 'd';
			break;
		case 4:
			alphalist[i] = 'e';
			break;
		case 5:
			alphalist[i] = 'f';
			break;
		case 6:
			alphalist[i] = 'g';
			break;
		case 7:
			alphalist[i] = 'h';
			break;
		default:
			cout << "out of range ( varible 0 to 8 )\n";
			return -1;
			break;
		}	
	}

	bool* alphasave = new bool[alphabetN];
	for (int i = 0;i < alphabetN;i++)
		alphasave[i] = true;

	for (int i = 0;i < statementN;i++)
		for (int j = 0;j < 4;j++)	cin >> state_arr[i][j];
			
	

	char** sheet = new char* [alphabetN];
	for (int i = 0;i < alphabetN;i++)
		sheet[i] = new char[5];

	for (int i = 0, j = 0;i < alphabetN, j < statementN;i++, j = j + 2)
	{
		sheet[i][0] = state_arr[j][1];
		sheet[i][1] = state_arr[j][2];
		sheet[i][2] = state_arr[j][3];
	}
	for (int i = 0, j = 1;i < alphabetN, j < statementN;i++, j = j + 2)
	{
		sheet[i][3] = state_arr[j][2];
		sheet[i][4] = state_arr[j][3];
	}
	cout << "sheet" << endl;
	for (int i = 0;i < alphabetN;i++)
		cout << sheet[i][0] << " " << sheet[i][1]<< " " << sheet[i][2] << " " <<  sheet[i][3] << " " << sheet[i][4] << endl;
	
	cin >> s;	//end_kiss

	save(state_arr, statementN, alphalist, alphasave, alphabetN, startP);

	// simplize

	Cell** cell = new Cell* [alphabetN - 1];
	for(int i = 0;i < alphabetN - 1;i++)
		cell[i] = new Cell[alphabetN - 1];
	
	// initial
	for (int i = 0;i < alphabetN - 1;i++)
	{
		for (int j = 0;j <= i;j++)
		{
			cell[i][j].remove = false;
			cell[i][j].keep = false;
			cell[i][j].f0.clear();
			cell[i][j].f1.clear();
		}
	}
	
	//	setting	
	for (int i = 0;i < alphabetN - 1;i++)
	{
		for (int j = 0;j < alphabetN - 1;j++)
		{
			if (cell[i][j].remove)	continue;
			cell[i][j].f0 += sheet[i + 1][1];
			cell[i][j].f1 += sheet[i + 1][3];
		}
		for (int j = 0;j < alphabetN - 1;j++)
		{
			if (cell[i][j].remove)	continue;
			cell[i][j].f0 += sheet[j][1];
			cell[i][j].f1 += sheet[j][3];
		}
	}

	//	same pair
	for (int i = 0;i < alphabetN - 1;i++)
	{
		for (int j = 0;j < alphabetN - 1;j++)
		{
			if (cell[i][j].remove)	continue;
			if (cell[i][j].f0[0] == cell[i][j].f0[1] && cell[i][j].f1[0] == cell[i][j].f1[1])
				cell[i][j].keep = true;	
		}
	}

	//  save coordinates.	ex ge
	vector<string> vec_k;
	for (int i = 0;i < alphabetN - 1;i++)
	{
		for (int j = 0;j < alphabetN - 1;j++)
		{
			if (cell[i][j].keep)
			{
				string t;
				t.push_back(alphalist[i + 1]);
				t.push_back(alphalist[j]);
				vec_k.push_back(t);
			}
		}
	}
	
	//	reserve
	for (int i = 0;i < vec_k.size();i++)
	{
		string checker = vec_k.at(i);
		//cout << vec_k.at(i) << endl;
		int i0 = 0;
		int i1 = 0;
		for (int j = 0;j < alphabetN - 1;j++)
		{
			for (int k = 0;k < alphabetN - 1;k++)
			{
				if (cell[j][k].remove)	continue;
				if (checker == cell[j][k].f0)
				{
					switch (cell[j][k].f1[0])
					{
					case 'b':
						i0 = 0;
						break;
					case 'c':
						i0 = 1;
						break;
					case 'd':
						i0 = 2;
						break;
					case 'e':
						i0 = 3;
						break;
					case 'f':
						i0 = 4;
						break;
					case 'g':
						i0 = 5;
						break;
					}
					switch (cell[j][k].f1[1])
					{
					case 'a':
						i1 = 0;
						break;
					case 'b':
						i1 = 1;
						break;
					case 'c':
						i1 = 2;
						break;
					case 'd':
						i1 = 3;
						break;
					case 'e':
						i1 = 4;
						break;
					case 'f':
						i1 = 5;
						break;
					}
					if (!cell[i0][i1].remove || (cell[j][k].f1[0] == cell[j][k].f1[1]))
						cell[j][k].keep = true;
				}			
				if (checker == cell[j][k].f1)
				{
					switch (cell[j][k].f0[0])
					{
					case 'b':
						i0 = 0;
						break;
					case 'c':
						i0 = 1;
						break;
					case 'd':
						i0 = 2;
						break;
					case 'e':
						i0 = 3;
						break;
					case 'f':
						i0 = 4;
						break;
					case 'g':
						i0 = 5;
						break;
					}
					switch (cell[j][k].f0[1])
					{
					case 'a':
						i1 = 0;
						break;
					case 'b':
						i1 = 1;
						break;
					case 'c':
						i1 = 2;
						break;
					case 'd':
						i1 = 3;
						break;
					case 'e':
						i1 = 4;
						break;
					case 'f':
						i1 = 5;
						break;
					}
					if (!cell[i0][i1].remove)
						cell[j][k].keep = true;	
				}
			}
		}
	}
	// print table
	for (int i = 0;i < alphabetN - 1;i++)
	{
		for (int j = 0;j < alphabetN - 1;j++)
		{
			if (cell[i][j].remove)	continue;
			cout << cell[i][j].f0 << " ";
		}
		cout << endl;
		for (int j = 0;j < alphabetN - 1;j++)
		{
			if (cell[i][j].remove)	continue;
			cout << cell[i][j].f1 << " ";
		}
		cout << endl;
	}
	// Deletes rows with varible output.
	for (int i = 0;i < alphabetN;i++)
	{
		if (sheet[i][2] != sheet[i][4])
		{
			for (int j = 0;j < alphabetN - 1;j++)
			{
				if (!cell[i - 1][j].keep)
					cell[i - 1][j].remove = true;
				if (!cell[j][i].keep)
					cell[j][i].remove = true;
			}
		}
	}

	//  remove element
	bool needagain = true;
	while (needagain)
	{
		needagain = false;
		for (int i = 0;i < alphabetN - 1;i++)
		{
			for (int j = 0;j < alphabetN - 1;j++)
			{
				if (cell[i][j].remove)	continue;
				if (cell[i][j].keep)	continue;
				if (cell[i][j].f0[0] == cell[i][j].f0[1] && cell[i][j].f1[0] == cell[i][j].f1[1])	continue;

				if (cell[i][j].f0[0] != cell[i][j].f0[1])
				{
					string pt;
					pt.clear();
					pt = cell[i][j].f0;
					if (cell[i][j].f0[0] == 'a')
					{
						char sw = pt[0];
						pt[0] = pt[1];
						pt[1] = sw;
					}

					if (cell[convertEngInt(pt[0]) - 1][convertEngInt(pt[1])].remove)
					{
						cell[i][j].remove = true;
						needagain = true;
					}			
				}
				if (cell[i][j].f1[0] != cell[i][j].f1[1])
				{
					string pt;
					pt.clear();
					pt = cell[i][j].f1;
					if (cell[i][j].f1[0] == 'a')
					{
						char sw = pt[0];
						pt[0] = pt[1];
						pt[1] = sw;
					}

					if (cell[convertEngInt(pt[0]) - 1][convertEngInt(pt[1])].remove)
					{
						cell[i][j].remove = true;
						needagain = true;
					}
						
				}
			}
		}
	}
	
	//  Delete rows on the sheet
	int statmentNumAfterDeleted = alphabetN;
	for (int i = 0;i < alphabetN - 1;i++)
	{
		for (int j = 0;j < alphabetN - 1;j++)
		{
			if (cell[i][j].remove)	continue;
			char c1 = alphalist[i + 1];
			char c2 = alphalist[j];
			alphasave[j] = false;
			statmentNumAfterDeleted--;
			for (int i = 0;i < alphabetN;i++)
			{
				if (sheet[i][1] == c2)
					sheet[i][1] = c1;
				if (sheet[i][3] == c2)
					sheet[i][3] = c1;
			}
		}
	}
	cout << "123:"<< statmentNumAfterDeleted << endl;
	char** state_arr_del = new char* [statmentNumAfterDeleted * 2];
	for (int i = 0;i < statmentNumAfterDeleted * 2;i++)
		state_arr_del[i] = new char[4];

	//	turns the sheet into input format
	for (int i = 0, j = 0;i < alphabetN;i++)
	{
		if (alphasave[i] == false)	continue;
		state_arr_del[j][0] = '0';
		state_arr_del[j + 1][0] = '1';
		state_arr_del[j][1] = alphalist[i];
		state_arr_del[j + 1][1] = alphalist[i];
		state_arr_del[j][2] = sheet[i][1];
		state_arr_del[j + 1][2] = sheet[i][3];
		state_arr_del[j][3] = sheet[i][2];
		state_arr_del[j + 1][3] = sheet[i][4];
		j = j + 2;
	}
	for (int i = 0;i < statmentNumAfterDeleted * 2; i++)
		cout << state_arr_del[i][0] << " "<< state_arr_del[i][1] << " " << state_arr_del[i][2] << " " << state_arr_del[i][3] << endl;

	cout << "remove" << endl;
	for (int i = 0;i < alphabetN - 1;i++)
	{
		for (int j = 0;j < alphabetN - 1;j++)	cout << cell[i][j].remove << " ";
		cout << "\n";
	}
	cout << "keep" << endl;
	for (int i = 0;i < alphabetN - 1;i++)
	{
		for (int j = 0;j < alphabetN - 1;j++)	cout << cell[i][j].keep << " ";
		cout << "\n";
	}

	cout << "sheet after simplize.\n";
	for (int i = 0;i < alphabetN;i++)
	{
		if(alphasave[i])
			cout << sheet[i][0] << " " << sheet[i][1] << " " << sheet[i][2] << " " << sheet[i][3] << " " << sheet[i][4] << endl;
	}
	save(state_arr_del, statmentNumAfterDeleted * 2, alphalist, alphasave, alphabetN, startP);
}

//void save(string fileName, char** arr, int size, char* alphalist, int size2, char startp);
//save(state_arr, statementN, alphalist, alphabetN, startP);
void save(char** arr, int size, char* alphalist, bool* alphasave, int size2, char startp)
{
	//ofstream fout(fileName, ofstream::out);
	cout << "digraph STG{\n\t" << "rankdir = LR;" << endl;
	cout << "\tINIT[shape = point];" << endl;
	for (int i = 0;i < size2;i++)
	{
		if(alphasave[i])
			cout << "\t" << alphalist[i] << " [label=\"" << alphalist[i] << "\"];" << endl;
	}
		

	cout << "\n\tINIT -> " << startp << ";" << endl;
	
	for (int i = 0;i < size;i++)
	{
		char t = arr[i][0];
		char t1 = arr[i][3];
		cout << "\t" << arr[i][1] << " -> " << arr[i][2] << " [label=\"" << t << "/" << t1 << "\"];" << endl;
	}
	cout << "}\n";
}
//save("robdd.dot");

int convertEngInt(char input)
{
	switch (input)
	{
	case 'a':
		return 0;
		break;
	case 'b':
		return 1;
		break;
	case 'c':
		return 2;
		break;
	case 'd':
		return 3;
		break;
	case 'e':
		return 4;
		break;
	case 'f':
		return 5;
		break;
	case 'g':
		return 6;
		break;
	case 'h':
		return 7;
		break;
	default:
		return -1;
		break;
	}
}


