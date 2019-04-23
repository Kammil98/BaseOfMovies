#pragma once
#include <string>
#ifndef TvProgram_H
#define TvProgram_H

using namespace std;

class TvProgram
{
	string type;
	string name;
	bool followed;
	string authorName;
	string authorSurname;
	int rating;
public:
	void setType(std::string value) { type = value; }
	std::string getType() { return type; }
	void setName(std::string value) { name = value; }
	std::string getName() { return name; }
	void setFollowed(bool value) { followed = value; }
	bool getFollowed() { return followed; }
	void setAuthorName(std::string value) { authorName = value; }
	std::string getAuthorName() { return authorName; }
	void setAuthorSurname(std::string value) { authorSurname = value; }
	std::string getAuthorSurname() { return authorSurname; }
	void setRating(int value) { rating = value; }
	int getRating() { return rating; }

	void virtual takeData();
	void virtual show();
	virtual void edit() = 0;
	std::string codeToFile(std::string);
	std::string decodeFromFile(std::string);
	void virtual save(fstream &);
	void virtual load(ifstream &);
	void virtual remind(){}
	float virtual weeklyTimeForWatching() { return 0; }
	int virtual allSeenEpisodes() { return 0; }
	int virtual episodesNumber(bool = false) { return 0; }
	int virtual lostTime() { return 0; }
};

#endif