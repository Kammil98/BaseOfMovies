// BazaSeriali.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Set.h"
#include "Movie.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

int main()
{ 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD bufsize = { 150, 40 };
	SetConsoleScreenBufferSize(handle, bufsize);
	SMALL_RECT windowSize = { 0, 0, 150, 40 };
	SetConsoleWindowInfo(handle, true, &windowSize); // set size of window 150 x 40 (40 "spaces" and 150 "enters", not pixels)
	Set<TvProgram> **setTvPrograms = new Set<TvProgram>*[3];
	//Set<TvProgram> *setTvPrograms[3];
	//setTvPrograms[0] = new Set<Series>;
	//Set<TvProgram> *tvProgram = new Set<TvProgram>;
	for (int i = 0; i < 3; i++)setTvPrograms[i] = new Set<TvProgram>;
	setTvPrograms[0]->setFileName("Series.txt");
	setTvPrograms[1]->setFileName("Movies.txt");
	setTvPrograms[2]->setFileName("LiveStreams.txt");
	TvProgram *tmpTvProgram;
	int choice = 0, number;
	//cout << "Jestem1" << endl;
	//system("pause");
	while (choice != 8)
	{
		cout << "Prosze wybrac numer porzadanej operacji.\n1. Dodaj program telewizyjny\n2. Usun program telewizyjny\n"
			<< "3. Edytuj program telewizyjny\n4. Wyswietl statystyki\n5. Wyswietl wszystkie programy telewizyjne\n"
			<< "6. Oblicz czas potrzebny tygodniowo na ogladanie sledzonych seriali\n"
			<< "7. Posortuj wszystkie programy telewizyjne wedlug ocen i wyswietl\n8. Wyjdz\n\n" << endl;
		setTvPrograms[2]->remind();
		cin >> choice;
		cout << endl;
		system("cls");
		switch (choice)
		{
		case 1:
			cout << "Prosze wybrac numer porzadanej operacji.\n1. Dodaj serial\n2. Dodaj film\n"
				<< "3. Dodaj wydarzenie na zywo\n" << "4. Wroc do menu glownego" << endl;
			cin >> choice;
			if (choice != 4)
			{
				system("cls");
				cout << "Ile programow telewizyjnych chcesz dodac?" << endl;
				cin >> number;
				*(setTvPrograms[choice - 1]) += number;
			}
			system("pause");
			break;
		case 2:
			cout << "Prosze wybrac numer porzadanej operacji.\n1. Usun serial\n2. Usun film\n"
				<< "3. Usun wydarzenie na zywo\n" << "4. Wroc do menu glownego" << endl;
			cin >> choice;
			if (choice != 4)
			{
				system("cls");
				setTvPrograms[choice - 1]->showAll();
				cout << "Prosze podac numer porzadkowy programu telewizyjnego do usuniecia" << endl;
				cin >> number;
				tmpTvProgram = setTvPrograms[choice - 1]->getSeries(number - 1);
				*(setTvPrograms[choice - 1]) -= tmpTvProgram->getName();
			}
			system("pause");
			break;
		case 3:
			cout << "Prosze wybrac numer porzadanej operacji.\n1. Edytuj serial\n2. Edytuj film\n"
				<< "3. Edytuj wydarzenie na zywo\n" << "4. Wroc do menu glownego" << endl;
			cin >> choice;
			system("cls");
			if (choice != 4)setTvPrograms[choice - 1]->edit();
			system("pause");
			break;
		case 4:
			setTvPrograms[0]->statistics();
			system("pause");
			break;
		case 5:
			for (int i = 0; i < 3; i++)
				setTvPrograms[i]->showAll();
			system("pause");
			break;
		case 6:
			cout << "Srednio trzeba spedzic " << setTvPrograms[0]->weeklyTimeForWatching()
				<< " minut tygodniowo na oglodanie sledzonych seriali" << endl;
			system("pause");
			break;
		case 7:
			try 
			{
				for (int i = 0; i < 3; i++)
					setTvPrograms[i]->showAllByRating();
			}
			catch (...)
			{
				cout << " Nie udalo sie posortowac wszystkich programow telewizyjnych.\n";
			}
			system("pause");
			break;
		}
		system("cls");
	}
	for (int i = 0; i < 3; i++)
		delete setTvPrograms[i];
	delete[] setTvPrograms;
    return 0;
}

