#include "Source.h"
using namespace std;

string VOWELS = "AEIOUYaeiouy";
string DIGITS = "0123456789";

void Feature::inData(ifstream& ifst) 
{
	ifst >> director;
}

void Feature::out(ofstream& ofst) 
{
	ofst << "It is feature film. Director is " << director << endl;
}

void Documentary::inData(ifstream& ifst) 
{
	ifst >> year;
}

void Documentary::out(ofstream& ofst) 
{
	ofst << "It is documentary film. It's year of creation is " << year << endl;
}

void Animation::inData(ifstream& ifst) 
{
	int wocType;
	ifst >> wocType;
	switch (wocType)
	{
	case 1:
		woc = DRAWN;
		break;
	case 2:
		woc = DOLL;
		break;
	case 3:
		woc = STOP_MOTION;
		break;
	}
}

void Animation::out (ofstream& ofst) 
{
	switch (woc)
	{
	case 0:
		ofst << "It is animation film. It's way of creation is drawing." << endl;
		break;
	case 1:
		ofst << "It is animation film. It's way of creation is using dolls" << endl;
		break;
	case 2:
		ofst << "It is animation film. It's way of creation is stop motion" << endl;
		break;
	}
}

int Film::countVowels()
{
	int cnt = 0;
	for (int i = 0; i < name.length(); i++)
	{
		if (VOWELS.find(name[i]) < VOWELS.length())
		{
			cnt++;
		}
	}
	return cnt;
}

Film* Film::in(ifstream& ifst) 
{
	Film* tmpFilm;
	int typeOfFilm;

	ifst >> typeOfFilm;	
	switch (typeOfFilm) 
	{
	case 1:
		tmpFilm = new Feature;
 		break;
	case 2:
		tmpFilm = new Animation;
		break;
	case 3:
		tmpFilm = new Documentary;
		break;
	default:
		return 0;
	}
	
	ifst >> tmpFilm->name;
	tmpFilm->inData(ifst);
	ifst >> tmpFilm->country;

	return tmpFilm;
}

Node::Node(Film* newpic)
{
	pic = newpic;
	next = NULL;
}

Container::Container()
{
	head = NULL;
	head = NULL;
	size = 0;
}

void Container::clear() {
	head = NULL;
	curr = NULL;
	size = 0;
}

void Container::in(ifstream& ifst)
{
	while (!ifst.eof()) {
		Node* newNode;
		newNode = new Node (Film::in(ifst));
		if (head == NULL)
		{
			head = newNode;
			size = 1;
		}
		else
		{
			curr = head;
			while (curr->next != NULL)
			{
				curr = curr->next;
			}
			curr->next = newNode;
			size++;
		}
	}
}
void Container::out(ofstream& ofst) {
	ofst << "Container contents " << size << " elements." << endl;

	int i = 0;
	curr = head;
	while (curr != NULL)
	{
		ofst << i << ": ";
		curr->pic->outName(ofst);
		curr->pic->out(ofst);
		ofst << "The picture was filmed in " << curr->pic->country << ".\n";
		ofst << "Number of vowels = ";
		outCntVowels(ofst);
		ofst << endl;
		
		curr = curr->next;
		i++;
	}
}
void Container::outCntVowels(ofstream& ofst)
{
	ofst << curr->pic->countVowels();
}

bool Film::cmp(Film& f)
{
	return countVowels() < f.countVowels();
}

void Container::sort()
{
	curr = head;
	Node* currj = head;
	while (curr != NULL)
	{
		currj = curr;
		while (currj != NULL)
		{
			if (curr->pic->cmp(*currj->pic))
			{
				swap(curr->pic, currj->pic);
			}
			currj = currj->next;
		}
		curr = curr->next;
	}
}
void Film::outName(ofstream& ofst)
{
	ofst << "This is " << name << ". ";
}
void Feature::outFeature(ofstream& ofst)
{
	out(ofst);
}
void Film::outFeature(ofstream& ofst)
{
	ofst << endl;
}

void Container::outFeature(ofstream& ofst) {
	int i = 0;
	curr = head;
	while (curr != NULL)
	{
		ofst << i << ": ";
		if (curr->pic)
		{
			curr->pic->outFeature(ofst);
		}
		curr = curr->next;
		i++;
	}
}

bool fileCheck(ifstream& ifst)
{
	char lineC[100];
	string lineCPP;

	
	if (!ifst.is_open())
	{
		cout << "Input file was not found.";
		exit(1);
	}

	int cnt = 1;
	while (!ifst.eof())
	{
		ifst.getline(lineC, 100, '\n');//type check
		lineCPP = lineC;
		if (lineCPP == "")
		{
			cout << cnt << " film: The type is a blank string.\n";
			exit(1);
		}
		for (int i = 0; i < lineCPP.length(); i++)
		{
			if (!(DIGITS.find(lineCPP[i]) < DIGITS.length()))
			{
				cout << cnt << " film: Type definition contains incorrect characters.\n";
				exit(1);
			}
		}
		int typeOfFilm = std::stoi(lineCPP);
		if (typeOfFilm <= 0 || typeOfFilm > 3)
		{
			cout << cnt << " film: Type is out of range.\n";
			exit(1);
		}

		ifst.getline(lineC, 100, '\n');//name check
		lineCPP = lineC;
		if (lineCPP == "")
		{
			cout << cnt << " film: The name of the film is a blank string.\n";
			exit(1);
		}

		switch (typeOfFilm)//type's pole check
		{
			int typeOfCreation;
		case 1:
			ifst.getline(lineC, 100, '\n');//director's name check
			lineCPP = lineC;
			if (lineCPP == "")
			{
				cout << cnt << " film: The director's name of the film is a blank string.\n";
				exit(1);
			}
			break;
		case 2:
			ifst.getline(lineC, 100, '\n');//way of creation check
			lineCPP = lineC;
			if (lineCPP == "")
			{
				cout << cnt << " film: The way of creation of the film is a blank string.\n";
				exit(1);
			}
			for (int i = 0; i < lineCPP.length(); i++)
			{
				if (!(DIGITS.find(lineCPP[i]) < DIGITS.length()))
				{
					cout << cnt << " film: The way of creation contains incorrect characters.\n";
					exit(1);
				}
			}
			typeOfCreation = std::stoi(lineCPP);
			if (typeOfCreation <= 0 || typeOfCreation > 3)
			{
				cout << cnt << " film: Way of creation is out of range.\n";
				exit(1);
			}
			break;
		case 3:
			ifst.getline(lineC, 100, '\n');//year check
			lineCPP = lineC;
			if (lineCPP == "")
			{
				cout << cnt << " film: The year of creation of the film is a blank string.\n";
				exit(1);
			}
			for (int i = 0; i < lineCPP.length(); i++)
			{
				if (!(DIGITS.find(lineCPP[i]) < DIGITS.length()))
				{
					cout << cnt << " film: The year of creation contains incorrect characters.\n";
					exit(1);
				}
			}
			int year = std::stoi(lineCPP);
			if (year <= 0 || year > 2022)
			{
				cout << cnt << " film: The year of creation is out of range.\n";
				exit(1);
			}
			break;
		}

		ifst.getline(lineC, 100, '\n'); //country check
		lineCPP = lineC;
		if (lineCPP == "")
		{
			cout << cnt << " film: The film's country is a blank string.\n";
			exit(1);
		}

		cnt++;
	}
	return true;
}