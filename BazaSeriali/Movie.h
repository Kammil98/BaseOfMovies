#pragma once
#include "TvProgram.h"
#ifndef Movie_H
#define Movie_H
class Movie :
	public TvProgram
{
private:
	int imdbRanking;
public:
	void setImdbRanking(int value) { imdbRanking = value; }
	int getImdbRanking() { return imdbRanking; }
	void virtual takeData();
	void virtual edit();
	void virtual show();
	void virtual save(std::fstream &);
	void virtual load(std::ifstream &);
};
#endif
