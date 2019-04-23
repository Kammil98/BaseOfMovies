#pragma once
#include "TvProgram.h"
#include <ctime>
#ifndef LiveStream_H
#define LiveStream_H
class LiveStream :
	public TvProgram
{
private:
	tm startData;
public:
	void setStartData(tm value) { startData = value; }
	tm getStartData() { return startData; }

	void virtual takeData();
	void virtual show();
	void virtual edit();
	void virtual save(fstream &);
	void virtual load(ifstream &);
	void remind();
};

#endif