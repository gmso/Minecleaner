#include "RecordsFile.h"


RecordsFile::RecordsFile()
{
	fileNamePermanent = "your.recs";
	fileNameTemprorary = "your.recs.txt";
	key = 'P';
	initializeRecords();
}

RecordsFile::~RecordsFile()
{
}

std::string RecordsFile::xor_crypt(const char& key, std::string data)
{
	for (auto& c : data)
	{
		c ^= key;
	}
	return data;
}

void RecordsFile::initializeRecords()
{
	loadEmptyRecords();

	if (std::filesystem::exists(fileNamePermanent))
	{
		loadRecordsFromFile();
	}
	else
	{
		initializeFile();
	}
}

void RecordsFile::loadRecordsFromFile()
{
	//rename file, open it, read it, save information to allRecords, close and rename file back again
}

void RecordsFile::loadEmptyRecords()
{
	Record emptyRecord = { 
		{"Time",0} ,
		{"Clicks",0} ,
		{"Lives",0} 
	};
	DifficultyRecords difficulty = {
		{"BestTime",emptyRecord} ,
		{"BestClicks",emptyRecord} ,
		{"BestLives",emptyRecord}
	};
	allRecords = {
		{"Easy",difficulty} ,
		{"Medium",difficulty} ,
		{"Hard",difficulty} 
	};
}

void RecordsFile::initializeFile()
{
	file.open(fileNameTemprorary);

	for (auto& mode : allRecords)
	{
		for (auto& best : mode.second)
		{
			for (auto& record : best.second)
			{
				auto rec = std::to_string(record.second);
				auto str = xor_crypt(key, rec);
				file << str << "\n";
			}
		}
	}

	file.close();

	std::rename(fileNameTemprorary.c_str(), fileNamePermanent.c_str());
}
