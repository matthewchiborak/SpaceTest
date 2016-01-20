#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

class FileManager
{
private:
	std::string players[10];
	std::string scores[10];
	int numberOfEntries;
public:
	//Returns true if file read successfully and stores the information
	FileManager();
	bool readScoreFile(std::string fileName);
	std::string* getPlayers();
	std::string* getScores();
	int* getNumberOfEntries();
	bool save(std::string fileName);
};
#endif
