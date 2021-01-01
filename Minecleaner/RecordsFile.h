#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <cstdio>
#include <filesystem>

class RecordsFile
{
public:
	RecordsFile();
	~RecordsFile();

	void saveRecord();

private:
	std::string fileNamePermanent;
	std::string fileNameTemprorary;
	char key;
	std::ofstream file;
	 
	typedef std::unordered_map<std::string, double> Record;
	typedef std::unordered_map<std::string, Record> DifficultyRecords;
	typedef std::unordered_map<std::string, DifficultyRecords> RecordRepo;
	RecordRepo allRecords;

	std::string xor_crypt(const char& key, std::string data);

	void initializeRecords();
	void loadRecordsFromFile();
	void loadEmptyRecords();

	void initializeFile();
};