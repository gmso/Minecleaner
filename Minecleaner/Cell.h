#pragma once

class Cell
{
public:
	Cell();
	~Cell();

	enum class cellType { empty, number, mine };
	enum class markType{ none, flag, question, saved};
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
	bool reveal(unsigned int livesRemaining = 0);
	void hide();
	void hover();
	void unhover();
	bool isBeingHovered();
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
	unsigned int getTotalNeighbors();
	void toggleMark();
	bool markIsFlag();
	bool markIsSaved();
	bool markIsQuestion();
	bool markIsNone();

private:
	cellType type;
	markType mark;
	bool revealed;
	bool hovered;
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
	unsigned int totalNeighbors;
};
