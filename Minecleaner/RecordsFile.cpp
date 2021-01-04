#include "RecordsFile.h"


RecordsFile::RecordsFile()
{
	fileNamePermanent = "your.recs";
	fileNameTemprorary = "your.recs.txt";
	key = '/';
	initializeRecords();
}

RecordsFile::~RecordsFile()
{
}

void RecordsFile::saveRecord(std::string gameMode, unsigned long time, unsigned long clicks, unsigned long lives)
{
	bool newRecordAcheived = false;

	if (gameMode == "a_Easy" ||
		gameMode == "b_Medium" || 
		gameMode == "c_Hard" )
	{
		auto a_BestTime = allRecords[gameMode]["a_BestTime"]["a_Time"];
		auto b_BestClicks = allRecords[gameMode]["b_BestClicks"]["b_Clicks"];
		auto c_BestLives = allRecords[gameMode]["c_BestLives"]["c_Lives"];

		if ((time < a_BestTime) ||
			((time == a_BestTime) && (clicks < b_BestClicks || lives > c_BestLives) ||
			(a_BestTime == static_cast<unsigned long>(config::game_valueInvalidRecord)) /*empty record*/)
			)
		{
			allRecords[gameMode]["a_BestTime"]["a_Time"] = time;
			allRecords[gameMode]["a_BestTime"]["b_Clicks"] = clicks;
			allRecords[gameMode]["a_BestTime"]["c_Lives"] = lives;
			newRecordAcheived = true;
		}

		if ((clicks < b_BestClicks) ||
			((clicks == b_BestClicks) && (time < a_BestTime || lives > c_BestLives) ||
			(b_BestClicks == static_cast<unsigned long>(config::game_valueInvalidRecord)) /*empty record*/)
			)
		{
			allRecords[gameMode]["b_BestClicks"]["a_Time"] = time;
			allRecords[gameMode]["b_BestClicks"]["b_Clicks"] = clicks;
			allRecords[gameMode]["b_BestClicks"]["c_Lives"] = lives;
			newRecordAcheived = true;
		}

		if ((lives > c_BestLives) ||
			((lives == c_BestLives) && (time < a_BestTime || clicks < b_BestClicks) ||
			(c_BestLives == static_cast<unsigned long>(config::game_valueInvalidRecord)) /*empty record*/)
			)
		{
			allRecords[gameMode]["c_BestLives"]["a_Time"] = time;
			allRecords[gameMode]["c_BestLives"]["b_Clicks"] = clicks;
			allRecords[gameMode]["c_BestLives"]["c_Lives"] = lives;
			newRecordAcheived = true;
		}

		if (newRecordAcheived)
		{
			saveRecordsInFile();
		}
	}
}

std::vector<unsigned long> RecordsFile::getRecords()
{
	std::vector<unsigned long> recordsAsVectorStrings;
	for (auto& mode : allRecords)
	{
		for (auto& best : mode.second)
		{
			for (auto& record : best.second)
			{
				recordsAsVectorStrings.push_back(record.second);
			}
		}
	}
	return recordsAsVectorStrings;
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
	renameFile(fileNamePermanent, fileNameTemprorary);

	file.open(fileNameTemprorary, std::ios::in);

	std::vector<std::string> fileLines;
	if (file.is_open()) { 

		std::string tp;
		while (std::getline(file, tp)) 
		{
			fileLines.push_back(xor_crypt(key, tp));
		}
		file.close();
	}

	if (validateFileContent(fileLines))
	{
		absorbFileContent(fileLines);
		renameFile(fileNameTemprorary, fileNamePermanent);
	}
	else
	{
		std::remove(fileNameTemprorary.c_str());
		initializeFile();
	}

}

void RecordsFile::loadEmptyRecords()
{
	Record emptyRecord = { 
		{"a_Time",static_cast<unsigned long>(config::game_valueInvalidRecord)} ,
		{"b_Clicks",static_cast<unsigned long>(config::game_valueInvalidRecord)} ,
		{"c_Lives",static_cast<unsigned long>(config::game_valueInvalidRecord)}
	};
	DifficultyRecords difficulty = {
		{"a_BestTime",emptyRecord} ,
		{"b_BestClicks",emptyRecord} ,
		{"c_BestLives",emptyRecord}
	};
	allRecords = {
		{"a_Easy",difficulty} ,
		{"b_Medium",difficulty} ,
		{"c_Hard",difficulty} 
	};
}

void RecordsFile::initializeFile()
{
	file.open(fileNameTemprorary, std::ios::out);

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

	renameFile(fileNameTemprorary, fileNamePermanent);
}

void RecordsFile::renameFile(std::string oldName, std::string newName)
{
	if ((std::rename(oldName.c_str(), newName.c_str())) == 0)
	{
		// file renaming successful
	}
}

bool RecordsFile::validateFileContent(const std::vector<std::string>& fileLines)
{
	if (fileLines.size() != config::game_recordedRecordValues)
	{
		return false;
	}

	for (auto& line : fileLines)
	{
		char* end;
		auto num = std::strtoul(line.c_str(),&end,10);
		if (num < 0)
		{
			return false;
		}
	}

	return true;
}


void RecordsFile::absorbFileContent(std::vector<std::string> fileLines)
{
	char* end;
	allRecords["a_Easy"]["a_BestTime"]["a_Time"] = std::strtoul(fileLines.at(0).c_str(),&end,10);
	allRecords["a_Easy"]["a_BestTime"]["b_Clicks"] = std::strtoul(fileLines.at(1).c_str(),&end,10);
	allRecords["a_Easy"]["a_BestTime"]["c_Lives"] = std::strtoul(fileLines.at(2).c_str(),&end,10);
	allRecords["a_Easy"]["b_BestClicks"]["a_Time"] = std::strtoul(fileLines.at(3).c_str(),&end,10);
	allRecords["a_Easy"]["b_BestClicks"]["b_Clicks"] = std::strtoul(fileLines.at(4).c_str(),&end,10);
	allRecords["a_Easy"]["b_BestClicks"]["c_Lives"] = std::strtoul(fileLines.at(5).c_str(),&end,10);
	allRecords["a_Easy"]["c_BestLives"]["a_Time"] = std::strtoul(fileLines.at(6).c_str(),&end,10);
	allRecords["a_Easy"]["c_BestLives"]["b_Clicks"] = std::strtoul(fileLines.at(7).c_str(),&end,10);
	allRecords["a_Easy"]["c_BestLives"]["c_Lives"] = std::strtoul(fileLines.at(8).c_str(),&end,10);
	allRecords["b_Medium"]["a_BestTime"]["a_Time"] = std::strtoul(fileLines.at(9).c_str(),&end,10);
	allRecords["b_Medium"]["a_BestTime"]["b_Clicks"] = std::strtoul(fileLines.at(10).c_str(),&end,10);
	allRecords["b_Medium"]["a_BestTime"]["c_Lives"] = std::strtoul(fileLines.at(11).c_str(),&end,10);
	allRecords["b_Medium"]["b_BestClicks"]["a_Time"] = std::strtoul(fileLines.at(12).c_str(),&end,10);
	allRecords["b_Medium"]["b_BestClicks"]["b_Clicks"] = std::strtoul(fileLines.at(13).c_str(),&end,10);
	allRecords["b_Medium"]["b_BestClicks"]["c_Lives"] = std::strtoul(fileLines.at(14).c_str(),&end,10);
	allRecords["b_Medium"]["c_BestLives"]["a_Time"] = std::strtoul(fileLines.at(15).c_str(),&end,10);
	allRecords["b_Medium"]["c_BestLives"]["b_Clicks"] = std::strtoul(fileLines.at(16).c_str(),&end,10);
	allRecords["b_Medium"]["c_BestLives"]["c_Lives"] = std::strtoul(fileLines.at(17).c_str(),&end,10);
	allRecords["c_Hard"]["a_BestTime"]["a_Time"] = std::strtoul(fileLines.at(18).c_str(),&end,10);
	allRecords["c_Hard"]["a_BestTime"]["b_Clicks"] = std::strtoul(fileLines.at(19).c_str(),&end,10);
	allRecords["c_Hard"]["a_BestTime"]["c_Lives"] = std::strtoul(fileLines.at(20).c_str(),&end,10);
	allRecords["c_Hard"]["b_BestClicks"]["a_Time"] = std::strtoul(fileLines.at(21).c_str(),&end,10);
	allRecords["c_Hard"]["b_BestClicks"]["b_Clicks"] = std::strtoul(fileLines.at(22).c_str(),&end,10);
	allRecords["c_Hard"]["b_BestClicks"]["c_Lives"] = std::strtoul(fileLines.at(23).c_str(),&end,10);
	allRecords["c_Hard"]["c_BestLives"]["a_Time"] = std::strtoul(fileLines.at(24).c_str(),&end,10);
	allRecords["c_Hard"]["c_BestLives"]["b_Clicks"] = std::strtoul(fileLines.at(25).c_str(),&end,10);
	allRecords["c_Hard"]["c_BestLives"]["c_Lives"] = std::strtoul(fileLines.at(26).c_str(),&end,10);
}

void RecordsFile::saveRecordsInFile()
{
	renameFile(fileNamePermanent, fileNameTemprorary);
	initializeFile();
}
