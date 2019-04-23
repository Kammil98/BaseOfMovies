#include "stdafx.h"
#include "Movie.h"
#include "Series.h"
#include<iostream>
using namespace std;


void Movie::takeData()
{
	int tmpint;
	TvProgram::takeData();
	cout << "Prosze podac miejsce filmu w rankingu IMDb" << endl;
	cin >> tmpint;
	setImdbRanking(tmpint);
}
void Movie::edit() {
	int choice, editedint;
	string editedstr, answer;
	system("cls");
	cout << "Co chcia³bys edytowac?" << endl;
	cout << "1. Nazwe filmu\n" << "2. Gatunek filmu\n" << "3. Autora filmu\n"
		<< "4. Miejsce w rankingu IMDb\n" << "5. Ocene filmu\n" << "6. Sledzenie filmu\n" << "7. Wszystko\n";
	cin >> choice;
	system("cls");
	cin.clear(); // unset flags
	cin.ignore(); // cleaning bufor (enters)
	switch (choice)
	{
	case 1:
		cout << "Prosze podac nowa nazwe filmu" << endl;
		cin >> editedstr;
		setName(editedstr);
		break;
	case 2:
		cout << "Prosze podac nowy gatunek filmu" << endl;
		cin >> editedstr;
		setType(editedstr);
		break;
	case 3:
		cout << "Prosze podac nowe imie autora filmu" << endl;
		cin >> editedstr;
		setAuthorName(editedstr);
		cout << "Prosze podac nowe nazwisko autora filmu" << endl;
		cin >> editedstr;
		setAuthorSurname(editedstr);
		break;
	case 4:
		cout << "Prosze podac nowe miejsce w rankingu IMDb" << endl;
		cin >> editedint;
		setImdbRanking(editedint);
		break;
	case 5:
		cout << "Prosze podac nowa ocene ( w skali 1-10 )" << endl;
		cin >> editedint;
		setRating(editedint);
		break;
	case 6:
		cout << "Czy chcesz sledzic ten serial?T/N" << endl;
		cin >> answer;
		if (answer == "T" || answer == "Tak" || answer == "t" || answer == "tak") setFollowed(true);
		else setFollowed(false);
	default:
		takeData();
	}
}
void Movie::show()
{
	//printf(%-x.ys",somestring) - mean give string on the left side, x mean take at least space equal to x characters, y mean take max space equal to y characters (cut string if bigger), s is string
	TvProgram::show();
	printf("                ");
	printf("%-11d", getImdbRanking());
}
void Movie::save(fstream &f)
{
	TvProgram::save(f);
	f << " " << getImdbRanking();
}
void Movie::load(ifstream &f)
{
	int handleInt;
	TvProgram::load(f);
	f >> handleInt;
	setImdbRanking(handleInt);
}