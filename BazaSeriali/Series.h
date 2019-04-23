#pragma once

#ifndef Series_H
#define Series_H
#include <string> 
#include <fstream>
#include "TvProgram.h"
class Series :
	public TvProgram
{
private:
	int weeksPerEpisode;
	int minutesPerEpisode;
	int lastSeenEpisode;
	int lastSeenSeason;
	int episodesPerSeason;
	int seasonsNumber;
	int episodesNumberInLastSeason;
public:
	void setWeeksPerEpisode(int value) { weeksPerEpisode = value; }
	int getWeeksPerEpisode() { return weeksPerEpisode; }
	void setMinutesPerEpisode(int value) { minutesPerEpisode = value; }
	int getMinutesPerEpisode() { return minutesPerEpisode; }
	void setLastSeenEpisode(int value) { lastSeenEpisode = value; }
	int getLastSeenEpisode() { return lastSeenEpisode; }
	void setLastSeenSeason(int value) { lastSeenSeason = value; }
	int getLastSeenSeason() { return lastSeenSeason; }
	void setEpisodesPerSeason(int value) { episodesPerSeason = value; }
	int getEpisodesPerSeason() { return episodesPerSeason; }
	void setSeasonsNumber(int value) { seasonsNumber = value; }
	int getSeasonsNumber() { return seasonsNumber; }
	void setEpisodesNumberInLastSeason(int value) { episodesNumberInLastSeason = value; }
	int getEpisodesNumberInLastSeason() { return episodesNumberInLastSeason; }

	void virtual takeData();
	void virtual edit();
	void virtual show();
	void virtual save(std::fstream &);
	void virtual load(std::ifstream &);
	float virtual weeklyTimeForWatching();
	int virtual allSeenEpisodes();
	int virtual episodesNumber(bool = false);
	int virtual lostTime();
};
#endif


