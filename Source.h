#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <utility>
using namespace std;

class Film {
	string name;
public:
	string country;

	static Film* in(ifstream& ifst);
	virtual void inData(ifstream& ifst) = 0;
	virtual void out(ofstream& ofst) = 0;
	int countVowels();
	void outName(ofstream& ofst);
	bool cmp(Film& f);
	virtual void outFeature(ofstream& ofst);
};

class Node {
public:
	Film* pic;
	Node* next;
	Node(Film* newfigure);
};

class Feature : public Film {
	string director;
public:
	void inData(ifstream& ifst);
	void out(ofstream& ofst); 
	void outFeature(ofstream& ofst);
	Feature() {}
};

class Animation : public Film {
	enum way { DRAWN, DOLL, STOP_MOTION };
	way woc;
public:
	void inData(ifstream& ifst);
	void out(ofstream& ofst);
	Animation() {}
};

class Documentary : public Film {
	int year;
public:
	void inData(ifstream& ifst);
	void out(ofstream& ofst);
	Documentary() {}
};

class Container {
public:
	Node* head;
	Node* curr;
	int size;

	void in(ifstream& ifst); 
	void out(ofstream& ofst);
	void outFeature(ofstream& ofst); 
	void outCntVowels(ofstream& ofst);
	void clear();
	void sort();
	Container(); 
	~Container() { clear(); } 
};

bool fileCheck(ifstream& ifst);
