#include "stdafx.h"
#include "LiveStream.h"
#include <iostream>
#include <fstream>


void LiveStream::takeData()
{
	tm timeHandle;
	TvProgram::takeData();
	cout << "Prosze podac rok, w ktorym wystepuje wydarzenie na zywo" << endl;
	cin >> timeHandle.tm_year;
	cout << "Prosze podac miesiac, w ktorym wystepuje wydarzenie na zywo" << endl;
	cin >> timeHandle.tm_mon;
	cout << "Prosze podac dzien, w ktorym wystepuje wydarzenie na zywo" << endl;
	cin >> timeHandle.tm_mday;
	cout << "Prosze podac godzine, o ktorej rozpoczyna sie wydarzenie na zywo" << endl;
	cin >> timeHandle.tm_hour;
	cout << "Prosze podac minute, o ktorej rozpoczyna sie wydarzenie na zywo" << endl;
	cin >> timeHandle.tm_min;
	setStartData(timeHandle);
}
void LiveStream::edit() {
	int choice, editedint;
	tm timeHandle;
	string editedstr, answer;
	system("cls");
	cout << "Co chcia³bys edytowac?" << endl;
	cout << "1. Nazwe wydarzenia na zywo\n" << "2. Gatunek wydarzenia na zywo\n" << "3. Autora wydarzenia na zywo\n"
		<< "4. Date wydarzenia na zywo\n" << "5. Ocene wydarzenia na zywo\n" << "6. Sledzenie wydarzenia na zywo\n" << "7. Wszystko\n";
	cin >> choice;
	system("cls");
	cin.clear(); // unset flags
	cin.ignore(); // cleaning bufor (enters)
	switch (choice)
	{
	case 1:
		cout << "Prosze podac nowa nazwe wydarzenia na zywo" << endl;
		cin >> editedstr;
		setName(editedstr);
		break;
	case 2:
		cout << "Prosze podac nowy gatunek wydarzenia na zywo" << endl;
		cin >> editedstr;
		setType(editedstr);
		break;
	case 3:
		cout << "Prosze podac nowe imie autora wydarzenia na zywo" << endl;
		cin >> editedstr;
		setAuthorName(editedstr);
		cout << "Prosze podac nowe nazwisko autora wydarzenia na zywo" << endl;
		cin >> editedstr;
		setAuthorSurname(editedstr);
		break;
	case 4:
		cout << "Prosze podac nowy rok, w ktorym wystepuje wydarzenie na zywo" << endl;
		cin >> timeHandle.tm_year;
		cout << "Prosze podac nowy miesiac, w ktorym wystepuje wydarzenie na zywo" << endl;
		cin >> timeHandle.tm_mon;
		cout << "Prosze podac nowy dzien, w ktorym wystepuje wydarzenie na zywo" << endl;
		cin >> timeHandle.tm_mday;
		cout << "Prosze podac nowa godzine, o ktorej rozpoczyna sie wydarzenie na zywo" << endl;
		cin >> timeHandle.tm_hour;
		cout << "Prosze podac nowa minute, o ktorej rozpoczyna sie wydarzenie na zywo" << endl;
		cin >> timeHandle.tm_min;
		setStartData(timeHandle);
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
void LiveStream::show()
{
	tm timeHandle = getStartData();
	//printf(%-x.ys",somestring) - mean give string on the left side, x mean take at least space equal to x characters, y mean take max space equal to y characters (cut string if bigger), s is string
	TvProgram::show();
	printf("                ");
	printf("%d:%d   %d.%d.%dr", timeHandle.tm_hour, timeHandle.tm_min, timeHandle.tm_mday, timeHandle.tm_mon, timeHandle.tm_year);
}
void LiveStream::save(fstream &f)
{
	tm timeHandle = getStartData();
	TvProgram::save(f);
	f << " " << timeHandle.tm_year << " " << timeHandle.tm_mon << " " 
		<< timeHandle.tm_mday << " " << timeHandle.tm_hour << " " << timeHandle.tm_min;
}
void LiveStream::load(ifstream &f)
{
	tm handleTime;
	TvProgram::load(f);
	f >> handleTime.tm_year;
	f >> handleTime.tm_mon;
	f >> handleTime.tm_mday;
	f >> handleTime.tm_hour;
	f >> handleTime.tm_min;
	setStartData(handleTime);
}
void LiveStream::remind()
{
	tm handle = getStartData();
	cout << getName() << " o godzinie " << handle.tm_hour << ":" << handle.tm_min
		<< " dnia " << handle.tm_mday << "." << handle.tm_mon << "." << handle.tm_year
		<< "r" << endl;
}