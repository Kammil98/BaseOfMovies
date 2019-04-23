#include "stdafx.h"
#include "TvProgram.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


void TvProgram::takeData()
{
	int tmpint;
	string answer;
	string tmpstr = "";
	cout << "Prosze podac nazwe programu telewizyjnego" << endl;
	cin.clear(); // unset flags
	cin.ignore(); // cleaning bufor (enters)
	getline(cin, tmpstr);
	setName(tmpstr);
	cout << "Czy chcesz sledzic ten program telewizyjny?T/N" << endl;
	cin >> answer;
	if (answer == "T" || answer == "Tak" || answer == "t" || answer == "tak") setFollowed(true);
	else setFollowed(false);
	cout << "Prosze podac gatunek programu telewizyjnego" << endl;
	cin.clear();
	cin.ignore();
	getline(cin, tmpstr);
	setType(tmpstr);
	cout << "Prosze podac imie autora programu telewizyjnego" << endl;
	getline(cin, tmpstr);
	setAuthorName(tmpstr);
	cout << "Prosze podac nazwisko autora programu telewizyjnego" << endl;
	getline(cin, tmpstr);
	setAuthorSurname(tmpstr);
	cout << "Prosze podac ocene serialu ( w skali 1-10 )" << endl;
	cin >> tmpint;
	setRating(tmpint);
}
void TvProgram::show()
{
	//printf(%-x.ys",somestring) - mean give string on the left side, x mean take at least space equal to x characters, y mean take max space equal to y characters (cut string if bigger), s is string
	if (getName().length() > 15)printf("%-12.12s...    ", getName().c_str());
	else printf("%-19.15s", getName().c_str());
	if (getType().length() > 15)printf("%-12.12s...    ", getType().c_str());
	else printf("%-19.15s", getType().c_str());
	if (getAuthorName().length() + getAuthorSurname().length() > 25)printf("%s %.*s...    ", getAuthorName().c_str(), 21 - getAuthorName().length(), getAuthorSurname().c_str());
	else printf("%s %-*s", getAuthorName().c_str(), 28 - getAuthorName().length(), getAuthorSurname().c_str());
	if (getFollowed())printf("Tak");
	else printf("Nie");
	printf("%14d/10", getRating());
}
string TvProgram::codeToFile(string nameWithSpace)
{
	std::string nameWithoutSpace = "";
	for (unsigned int i = 0; i < nameWithSpace.length(); i++)
	{
		if (nameWithSpace[i] == ' ') nameWithoutSpace += "_";
		else nameWithoutSpace += nameWithSpace[i];
	}
	return nameWithoutSpace;
}
string TvProgram::decodeFromFile(string nameWithoutSpace)
{
	string nameWithSpace = "";
	for (unsigned int i = 0; i < nameWithoutSpace.length(); i++)
	{
		if (nameWithoutSpace[i] == '_') nameWithSpace += " ";
		else nameWithSpace += nameWithoutSpace[i];
	}
	return nameWithSpace;
}
void TvProgram::save(fstream &f)
{
	string codedStr = "";
	codedStr = codeToFile(getName());
	f << codedStr << " ";
	codedStr = codeToFile(getType());
	f << codedStr << " ";
	f << getAuthorName() << " " << getAuthorSurname() << " ";
	f << getRating() << " ";
	if (getFollowed()) f << 1;
	else f << 0;
}
void TvProgram::load(ifstream &f)
{
	int handleInt;
	string handleStr;
	f >> handleStr;
	handleStr = decodeFromFile(handleStr);
	setName(handleStr);
	f >> handleStr;
	handleStr = decodeFromFile(handleStr);
	setType(handleStr);
	f >> handleStr;
	setAuthorName(handleStr);
	f >> handleStr;
	setAuthorSurname(handleStr);
	f >> handleInt;
	setRating(handleInt);
	f >> handleInt;
	setFollowed(handleInt == 1);
}
