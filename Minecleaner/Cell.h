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
	bool isRevealed();
	bool reveal();
	bool isNumber();
	bool isEmpty();
	unsigned int getAdjacentBombs();
	void initializeNeighbors(
		bool leftTop,
		bool leftCenter,
		bool leftBottom,
		bool top,
		bool bottom,
		bool rightTop,
		bool rightCenter,
		bool rightBottom);
	bool neighborExists(int offsetRow, int offsetCol);

private:
	cellType type;
	bool revealed;
	unsigned int adjacentBombs;
	struct neighbors
	{
		bool leftTop;
		bool leftCenter;
		bool leftBottom;
		bool top;
		bool bottom;
		bool rightTop;
		bool rightCenter;
		bool rightBottom;
		neighbors()
		{
			leftTop = false;
			leftCenter = false;
			leftBottom = false;
			top = false;
			bottom = false;
			rightTop = false;
			rightCenter = false;
			rightBottom = false;
		}
	} existingNeighbors;

};
