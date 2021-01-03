#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <cstdio>
#include <filesystem>

#include "config.h"

class RecordsFile
{
public:
	RecordsFile();
	~RecordsFile();

	void saveRecord(
		std::string gameMode, 
		unsigned long time, 
		unsigned long clicks, 
		unsigned long lives);

	std::vector<unsigned long> getRecords();

private:
	std::string fileNamePermanent;
	std::string fileNameTemprorary;
	char key;
	std::fstream file;
	 
	typedef std::map<std::string, unsigned long> Record;
	typedef std::map<std::string, Record> DifficultyRecords;
	typedef std::map<std::string, DifficultyRecords> RecordRepo;
	RecordRepo allRecords;

	std::string xor_crypt(const char& key, std::string data);

	void initializeRecords();
	void loadRecordsFromFile();
	void loadEmptyRecords();

	void initializeFile();
	void renameFile(std::string oldName, std::string newName);
	bool validateFileContent(const std::vector<std::string>& fileLines);
	void absorbFileContent(std::vector<std::string> fileLines);
	void saveRecordsInFile();
};