#include "stdafx.h"
#include "Series.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;


void Series::takeData()
{
	TvProgram::takeData();
	int tmpint;
	cout << "Prosze podac co ile tygodni pojawiania sie nowych odcinek w TV" << endl;
	cin >> tmpint;
	setWeeksPerEpisode(tmpint);
	cout << "Prosze podac dlugosc odcinkow (w minutach)" << endl;
	cin >> tmpint;
	setMinutesPerEpisode(tmpint);
	cout << "Prosze podac numer ostatniego widzianego odcinka" << endl;
	cin >> tmpint;
	setLastSeenEpisode(tmpint);
	cout << "Prosze podac numer ostatniego widzianego sezonu" << endl;
	cin >> tmpint;
	setLastSeenSeason(tmpint);
	cout << "Prosze podac ilosc odcinkow przypadajacych na sezon" << endl;
	cin >> tmpint;
	setEpisodesPerSeason(tmpint);
	cout << "Prosze podac Ilosc sezonow" << endl;
	cin >> tmpint;
	setSeasonsNumber(tmpint);
	cout << "Prosze podac ilosc odcinkow w ostatnim sezonie" << endl;
	cin >> tmpint;
	setEpisodesNumberInLastSeason(tmpint);
}
void Series::edit() {
	int choice, editedint;
	string editedstr, answer;
	system("cls");
	cout << "Co chcia³bys edytowac?" << endl;
	cout << "1. Nazwe serialu\n" << "2. Gatunek serialu\n" << "3. Autora serialu\n"
		<< "4. Czestotliwosc pojawiania sie nowych odcinkow w telewizji\n" << "5. Dlugosc odcinkow\n" <<
		"6. Ostatni widziany odcinek\n" << "7. Ostatni widziany sezon\n" << "8. Ilosc odcinkow przypadajacych na sezon\n" <<
		"9. Ilosc sezonow\n" << "10. Ilosc odcinkow w ostatnim sezonie\n" << "11. Ocene serialu\n" << "12. Sledzenie serialu\n" << "13. Wszystko\n";
	cin >> choice;
	system("cls");
	cin.clear(); // unset flags
	cin.ignore(); // cleaning bufor (enters)
	switch (choice) 
	{
	case 1: 
		cout << "Prosze podac nowa nazwe serialu" << endl;
		cin >> editedstr;
		setName(editedstr);
		break;
	case 2:
		cout << "Prosze podac nowy gatunek serialu" << endl;
		cin >> editedstr;
		setType(editedstr);
		break;
	case 3:
		cout << "Prosze podac nowe imie autora serialu" << endl;
		cin >> editedstr;
		setAuthorName(editedstr);
		cout << "Prosze podac nowe nazwisko autora serialu" << endl;
		cin >> editedstr;
		setAuthorSurname(editedstr);
		break;
	case 4:
		cout << "Prosze podac nowa czestotliwosc pojawiania sie nowych odcinkow" << endl;
		cin >> editedint;
		setWeeksPerEpisode(editedint);
		break;
	case 5:
		cout << "Prosze podac nowa dlugosc odcinkow" << endl;
		cin >> editedint;
		setMinutesPerEpisode(editedint);
		break;
	case 6:
		cout << "Prosze podac numer ostatniego widzianego odcinka" << endl;
		cin >> editedint;
		setLastSeenEpisode(editedint);
		break;
	case 7:
		cout << "Prosze podac numer ostatniego widzianego sezonu" << endl;
		cin >> editedint;
		setLastSeenSeason(editedint);
		break;
	case 8:
		cout << "Prosze podac nowa ilosc odcinkow przypadajacych na sezon" << endl;
		cin >> editedint;
		setEpisodesPerSeason(editedint);
		break;
	case 9:
		cout << "Prosze podac Ilosc sezonow" << endl;
		cin >> editedint;
		setSeasonsNumber(editedint);
		break;
	case 10:
		cout << "Prosze podac ilosc odcinkow w ostatnim sezonie" << endl;
		cin >> editedint;
		setEpisodesNumberInLastSeason(editedint);
		break;
	case 11:
		cout << "Prosze podac nowa ocene ( w skali 1-10 )" << endl;
		cin >> editedint;
		setRating(editedint);
		break;
	case 12:
		cout << "Czy chcesz sledzic ten serial?T/N" << endl;
		cin >> answer;
		if (answer == "T" || answer == "Tak" || answer == "t" || answer == "tak") setFollowed(true);
		else setFollowed(false);
	default:
		takeData();
	}
}
void Series::show() 
{
	//printf(%-x.ys",somestring) - mean give string on the left side, x mean take at least space equal to x characters, y mean take max space equal to y characters (cut string if bigger), s is string
	TvProgram::show();
	printf("                ");
	printf("S%02d E%02d", getLastSeenSeason(), getLastSeenEpisode());
	printf("             ");
	printf("S%02d E%02d", getSeasonsNumber(), getEpisodesNumberInLastSeason());
}
void Series::save(fstream &f)
{
	TvProgram::save(f);
	f << " " << getMinutesPerEpisode() << " " << getWeeksPerEpisode() << " ";
	f << getEpisodesPerSeason() << " " << getLastSeenSeason() << " ";
	f << getLastSeenEpisode() << " " << getSeasonsNumber() << " ";
	f << getEpisodesNumberInLastSeason();
}
void Series::load(ifstream &f)
{
	int handleInt;
	string handleStr;
	TvProgram::load(f);
	f >> handleInt;
	setMinutesPerEpisode(handleInt);
	f >> handleInt;
	setWeeksPerEpisode(handleInt);
	f >> handleInt;
	setEpisodesPerSeason(handleInt);
	f >> handleInt;
	setLastSeenSeason(handleInt);
	f >> handleInt;
	setLastSeenEpisode(handleInt);
	f >> handleInt;
	setSeasonsNumber(handleInt);
	f >> handleInt;
	setEpisodesNumberInLastSeason(handleInt);
}
float Series::weeklyTimeForWatching()
{
	if (getFollowed() && getWeeksPerEpisode() != 0)	
		return (float)getMinutesPerEpisode() / (float)getWeeksPerEpisode();
	return 0;
}
int Series::episodesNumber( bool onlySeenEpisodes)
{
	if (onlySeenEpisodes) return (getEpisodesPerSeason() * (getLastSeenSeason() - 1)) + getLastSeenEpisode();
	return (getEpisodesPerSeason() * (getSeasonsNumber() - 1)) + getEpisodesNumberInLastSeason();
}
int Series::allSeenEpisodes()
{
	return getMinutesPerEpisode() * episodesNumber(true);
}
int Series::lostTime()
{
	return getMinutesPerEpisode() * episodesNumber(true);
}