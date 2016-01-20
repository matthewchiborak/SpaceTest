#include "FileManager.h"

FileManager::FileManager()
{
	numberOfEntries = 0;
}

bool FileManager::readScoreFile(std::string fileName)
{
	std::string line;
	std::ifstream myFile(fileName);
	bool isFirst = true;
	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{
			std::stringstream ss(line);
			std::string temp = "";
			char i;
			bool first = true;

			while (ss >> i)
			{
				temp += i;

				if (ss.peek() == '~')
				{
					ss.ignore();

					if (first)
					{
						players[numberOfEntries] = temp;
						first = false;
					}
					else
					{
						scores[numberOfEntries] = temp;
					}

					temp = "";
				}
			}

			numberOfEntries++;
			
		}
		myFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

std::string* FileManager::getPlayers()
{
	return players;
}

std::string* FileManager::getScores()
{
	return scores;
}

int* FileManager::getNumberOfEntries()
{
	return &numberOfEntries;
}

bool FileManager::save(std::string fileName)
{
	std::ofstream newFile;
	newFile.open(fileName);
	std::string fileContents = "";

	for (int i = 0; i < numberOfEntries; i++)
	{
		fileContents = fileContents + players[i] + "~" + scores[i] + "~\n";
	}

	newFile << fileContents;
	newFile.close();

	return true;
}