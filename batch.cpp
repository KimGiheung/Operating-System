#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	ofstream ofs("batch.out", ios::out | ios::app);
	if (ofs.fail())
	{
		cerr << "Error!" << endl;
	}
	
	ifstream ifs;
	ifs.open("batch.inp",  ios::in);
	if (!ifs)
	{
		cerr << "Error!" << endl;
	}
	
	char line[256];
	int N = 0;
	ifs.getline(line, 256);
	N = stoi(line);
	string A = "";
	
	int idle_time 		= 0;
	int processing_time = 0;
	
	
	
	for(int i = 0; i<N;i++)
	{
		ifs.getline(line, 256);
		stringstream ss(line);
		vector<string> strint;
		int count = 0;
		
		while(getline(ss, A, ' '))
		{
			if(A == "-1") break;
			count++;
			if(count%2 == 1)
			{
				processing_time += stoi(A);
			}
			else
			{
				processing_time += stoi(A);
				idle_time		+= stoi(A);
			}	
		}
	}
	
	ofs << idle_time << " " << processing_time;
}

