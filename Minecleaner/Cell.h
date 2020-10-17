#pragma once

class Cell
{
public:
	Cell();
	~Cell();

	enum class cellType{empty,number,mine};
	bool hasMine();
	void addMine();
	void addNumber(
		unsigned int leftTop, 
		unsigned int leftCenter, 
		unsigned int leftBottom,
		unsigned int top,
		unsigned int bottom,
		unsigned int rightTop,
		unsigned int rightCenter,
		unsigned int rightBottom
		);

private:
	cellType type;
	bool revealed;
	unsigned int adjacentBombs;
};
