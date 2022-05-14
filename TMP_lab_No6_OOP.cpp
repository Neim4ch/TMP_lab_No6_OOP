// TMP_lab_No6_OOP.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Source.h"
using namespace std;
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "incorrect command line! Waited: command in_file out_file" << endl;
		exit(1);
	}
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);

	fileCheck(ifst);
	ifst.close();
	ifst.open(argv[1]);

	cout << "Start" << endl;
	
	Container films;
	films.in(ifst);
	ofst << "Filled container. " << endl;
	ofst << "Unsorted cont. " << endl;
	films.out(ofst);
	ofst << endl << endl;

	films.sort();
	films.out(ofst);
	ofst <<"Sorted container." << endl << endl;

	films.outFeature(ofst);
	films.clear();
	ofst << "Empty container. " << endl << endl;
	films.out(ofst);

	cout << "Stop" << endl;
	return 0;
}