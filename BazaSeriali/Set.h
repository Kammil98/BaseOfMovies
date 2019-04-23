#pragma once
#include "Series.h"
#include "Movie.h"
#include "LiveStream.h"
#include <fstream>
#include <vector>

#ifndef Set_H
#define Set_H

template<class T>
class Set
{
	//static const int maxNumber=100;
	std::string fileName;
	int number;
	vector <T*> setOfSeries;


public:
	Set() :number(0)
	{
		load();
	}
	void setFileName(std::string value) { fileName = value; }
	std::string getFileName() { return fileName; }
	void setNumber(int value) { number = value; }
	int getNumber() { return number; }
	void setSeries(int i, T *value) { setOfSeries.insert(setOfSeries.begin() + i, value); }
	T* correctHandle()
	{
		T* handle;
		if (getFileName() == "Series.txt") {
			handle = new Series;
			return handle;
		}
		if (getFileName() == "Movies.txt") {
			handle = new Movie;
			return handle;
		}
		if (getFileName() == "LiveStreams.txt") {
			handle = new LiveStream;
			return handle;
		}
		return NULL;
	}
	T* getSeries(int i) 
	{ 
		T* handle = correctHandle(); //handle to keep encapsulation and operate on another adress
		if (getFileName() == "Series.txt")
			*(dynamic_cast < Series *>(handle)) = *(dynamic_cast < Series *>(setOfSeries[i]));
		if (getFileName() == "Movies.txt")
			*(dynamic_cast < Movie *>(handle)) = *(dynamic_cast < Movie *>(setOfSeries[i]));
		if (getFileName() == "LiveStreams.txt")
			*(dynamic_cast < LiveStream *>(handle)) = *(dynamic_cast < LiveStream *>(setOfSeries[i]));
		return handle;
	}
	void freeMemory(int i) {
		delete setOfSeries[i]; 
		setOfSeries.erase(setOfSeries.begin() + i);
	}
	void qs(int lewy, int prawy)
	{
		int i = lewy, j = prawy, sr;
		T* handle = getSeries((lewy + prawy) / 2);
		sr = handle->getRating();
		delete handle;
		T *pom, *pom2;
		do
		{
			handle = getSeries(i);
			while (handle->getRating() > sr)
			{
				delete handle;
				handle = getSeries(++i);
			}
			delete handle;
			handle = getSeries(j);
			while (handle->getRating() < sr)
			{
				delete handle;
				handle = getSeries(--j);
			}
			delete handle;
			if (i <= j)
			{
				pom = getSeries(i);
				pom2 = getSeries(j);
				freeMemory(i);
				setSeries(i++, pom2);
				freeMemory(j);
				setSeries(j--, pom);
			}
		} while (i <= j);
		if (lewy<j)qs(lewy, j);
		if (i<prawy)qs(i, prawy);
	}
	T* maxEpisodesNumber(bool onlySeenEpisodes = false)
	{
		int max = 0, tmpMax;
		T *maxSeries, *tmpSeries;

		if (getNumber() == 0) return 0;
		else maxSeries = getSeries(0);
		for (int i = 1; i < getNumber(); i++)
		{
			tmpSeries = getSeries(i);
			tmpMax = tmpSeries->episodesNumber(onlySeenEpisodes);
			if (tmpMax > max) 
			{
				max = tmpMax;
				delete maxSeries;
				maxSeries = tmpSeries;
			}
			else delete tmpSeries;
		}
		return maxSeries;
	}
	int lostTime()
	{
		int time = 0;
		T* tmpSeries;
		for (int i = 0; i < getNumber(); i++)
		{
			tmpSeries = getSeries(i);
			time += tmpSeries->lostTime();
			delete tmpSeries;
		}
		return time;
	}
	int findIndex(std::string name)
	{
		T* tmpSeries;
		int index = -1;
		do {
			index++;
			tmpSeries = getSeries(index);
		} while (tmpSeries->getName() != name && index <= getNumber() );
		delete tmpSeries;
		return index;
	}
	void save() {
		fstream f;
		T* tvprogram;
		std::string file = getFileName(), codedStr = "";
		try 
		{
			f.open(file.c_str(), std::ios::out | std::ios::trunc);//c_str change string "To Read" (Add '\0' at the end)
			if (f.bad())
			{
				throw "Nie udalo sie otrzymac dostepu w pliku :(\n";
			}
			f << getNumber() << endl;
			for (int i = 0; i < getNumber(); i++)
			{
				tvprogram = getSeries(i);
				tvprogram->save(f);
				delete tvprogram;
				f << endl;
			}
			f.close();
		}
		catch (std::string errmsg)
		{
			cout << errmsg;
		}
		
	}
	void load() 
	{
		std::ifstream f;
		int handleInt = 0; // = 0 in case file is empty
		std::string handleStr, file = getFileName();
		T* tvprogram;
		
		try 
		{
			f.open(file.c_str(), std::ios::in);
			if (f.bad())
			{
				throw "Nie udalo sie otrzymac dostepu w pliku :(\n";
			}
			while (getNumber() > 0)//free memory, if there was any item inside
			{
				freeMemory(getNumber() - 1);
				setNumber(getNumber() - 1);
			}
			f >> handleInt;
			setNumber(handleInt);
			for (int i = 0; i < this->getNumber(); i++)
			{
				tvprogram = correctHandle();
				tvprogram->load(f);
				setSeries(i, tvprogram);
			}
			f.close();
		}
		catch (std::string errmsg){
			cout << errmsg;
		}
	}	
	Set & operator +=(int howmany)
	{
		T* tmpTvProgram;
		for (int i = 0; i < howmany; i++)
		{
			tmpTvProgram = correctHandle();
			tmpTvProgram->takeData();
			setSeries(getNumber(), tmpTvProgram);
			setNumber(getNumber() + 1);
		}
		save();
		return *this;
	}
	Set & operator -=(std::string nameToRm)
	{
		T *tmpTvProgram;
		int index = findIndex(nameToRm);
		if (getNumber() - 1 != index && index < getNumber() )
		{
			tmpTvProgram = getSeries(getNumber() - 1);
			freeMemory(index);
			setSeries(index, tmpTvProgram);
		}
		if (index >= getNumber()) cout << "Nie znaleziono takiego serialu do usuniecia";
		freeMemory(getNumber() - 1);
		setNumber(getNumber() - 1);
		save();
		return *this;
	}
	void showAll()
	{
		load();
		T* tvProgram;
		cout << "l.p. " << "Nazwa\t\t" << "Typ\t\t   " << "Autor\t\t\t" << "Czy sledzony    " << "Ocena";
		if (getFileName() == "Series.txt")
			cout << "\t\t    Ostatni Widziany    " << "Ostatni Wypuszczony\n" << endl;
		if (getFileName() == "Movies.txt")
			cout << "\t\t    Miejsce w rankingu IMDb\n" << endl;
		if (getFileName() == "LiveStreams.txt")
			cout << "\t\t    Data i godzina rozpoczecia\n" << endl;
		for (int i = 0; i < getNumber(); i++)
		{
			printf("%-5d", i + 1);
			tvProgram = getSeries(i);
			tvProgram->show();
			delete tvProgram;
			cout << endl;
		}
		cout << endl << endl;
	}
	void edit()
	{
		T* handleTvProgram;
		int index;

		showAll();
		cout << "Prosze podac numer porzadkowy programu telewizyjnego do edycji" << endl;
		cin >> index;
		handleTvProgram = getSeries(index-1);
		handleTvProgram->edit();
		freeMemory(index - 1);
		setSeries(index - 1, handleTvProgram);
		save();
	}
	void statistics()
	{
		load();
		T *longestSeries = maxEpisodesNumber(), *longestSeenSeries = maxEpisodesNumber(true), *handle;
		int lostTime = this->lostTime(), followedNumber = 0, allSeenEpisodes = 0;
		cout << "Statystyki" << endl;
		cout << "Laczna ilosc seriali : " << getNumber() << endl;
		for (int i = 0; i < getNumber(); i++)
		{
			handle = getSeries(i);
			if (handle->getFollowed()) 
				followedNumber++;
			delete handle;
		}
		cout << "Ilosc sledzonych seriali : " << followedNumber << endl;
		cout << "Serial z najwieksza iloscia odcinkow : " << longestSeries->getName()
			<< " ( " << "ilosc odcinkow : " << longestSeries->episodesNumber() << " )" << endl;
		cout << "Najwiecej obejrzanych odcinkow : " << longestSeenSeries->getName()
			<< " ( " << "ilosc odcinkow : " << longestSeenSeries->episodesNumber(true) << " )" << endl;
		cout << "Ilosc czasu spedzona na ogladaniu seriali " << lostTime / 60 << " godzin i " << lostTime % 60 << " minut" << endl;
		for (int i = 0; i < getNumber(); i++)
		{
			handle = getSeries(i);
			allSeenEpisodes += handle->allSeenEpisodes();
			delete handle;
		}
			
		cout << "Calkowita ilosc obejrzanych odcinkow ze wszystkich seriali : " << allSeenEpisodes << endl;
		delete longestSeries;
		delete longestSeenSeries;
	}
	float weeklyTimeForWatching()
	{
		T* handle;
		float time = 0;

		load();
		for (int i = 0; i < getNumber(); i++)
		{
			handle = getSeries(i);
			time += handle->weeklyTimeForWatching();
			delete handle;
		}
		return time;
	}
	void showAllByRating()
	{
		load();
		qs(0, getNumber() - 1);
		save();
		showAll();
	}
	void remind()
	{
		T* tvProgram;
		load();
		try 
		{
			if (getNumber() == 0) throw "Nie masz zadnych nadchodzacych wydarzen na zywo.";
			cout << "Pamietaj o wydarzeniach : \n\n";
			for (int i = 0; i < getNumber(); i++)
			{
				tvProgram = getSeries(i);
				tvProgram->remind();
				delete tvProgram;
			}
		}
		catch (std::string msg)
		{
			cout << msg;
		}
	}
	~Set()
	{
		load();
		for (int i = 0; i < getNumber(); i++) 
			freeMemory(0);   //notfreeMemory(i) because every time freeMemory erase item from vector and vector become shorter
	}
};

#endif