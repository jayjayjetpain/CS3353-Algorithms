#include <fstream> 
#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <string>
#include <time.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

void generateRandom(unsigned int, string);
void generateReversed(unsigned int, string);
void generate2080(unsigned int, string);
void generate30Rando(unsigned int, string);
bool reverse(int i, int j) { return (i > j); }

int main()
{
	srand(time(NULL));
	unsigned int toGen;
	unsigned int toSort;

	cout << "How many ints should be in the file?: ";
	cin >> toGen;

	//string name = to_string(toGen) + "random.txt";
	//generateRandom(toGen, name);

	//string name = to_string(toGen) + "reverse.txt";
	//generateReversed(toGen, name);

	//string name = to_string(toGen) + "2080.txt";
	//generate2080(toGen, name);

	string name = to_string(toGen) + "30rando.txt";
	generate30Rando(toGen, name);

}

void generateRandom(unsigned int total, string name)
{
	ofstream output(name);

	for (unsigned int i = 0; i < total; i++)
	{
		unsigned int num = (rand() % total);
		output << num;
		if (i != total - 1)
		{
			output << endl;
		}
	}
	output.close();
}

void generateReversed(unsigned int total, string name)
{
	ofstream output(name);
	vector<int> temp;

	for (unsigned int i = 0; i < total; i++)
	{
		unsigned int num = (rand() % total);
		temp.push_back(num);
	}
	sort(temp.begin(), temp.end(), reverse);

	for (unsigned int j = 0; j < temp.size(); j++)
	{
		output << temp.at(j);
		if (j != total - 1)
		{
			output << endl;
		}
	}
	output.close();
}

void generate2080(unsigned int total, string name)
{
	ofstream output(name);
	set<int> unique;
	vector<int> values;

	while (unique.size() < (total * 0.2))
	{
		unsigned int num = (rand() % total);
		if (unique.count(num) == 1)
		{
		}
		else
		{
			unique.insert(num);
			values.push_back(num);
		}
	}
	int sub = values.size();

	for (unsigned int i = 0; i < total; i++)
	{
		unsigned int num = (rand() % sub);
		output << values.at(num);
		if (i != total - 1)
		{
			output << endl;
		}
	}
}

void generate30Rando(unsigned int total, string name)
{
	ofstream output(name);

	vector<int> temp;

	for (unsigned int i = 0; i < total; i++)
	{
		unsigned int num = (rand() % total);
		temp.push_back(num);
	}

	unsigned int range = (total * 0.3);
	unsigned int low = (rand() % (total - range));
	unsigned int high = low + range;
	sort(temp.begin() + low, temp.begin() + high);

	for (unsigned int j = 0; j < temp.size(); j++)
	{
		output << temp.at(j);
		if (j != total - 1)
		{
			output << endl;
		}
	}
	output.close();
}