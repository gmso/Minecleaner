#pragma once

class Cell
{
public:
	Cell();
	~Cell();

	enum class cellType{empty,number,mine};
	bool hasMine();
	void addMine();

private:
	cellType type;
	bool revealed;
	unsigned int adjacentBombs;
};
