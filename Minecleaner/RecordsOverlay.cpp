#include "RecordsOverlay.h"

RecordsOverlay::RecordsOverlay()
{
	displayed = false;
	posX = config::window_width_easy / 2 - ((config::window_width_easy - 100) / 2);
	posY = config::window_height_easy / 2 - ((config::window_height_easy - 10) / 2);
	posX_BR = posX + config::window_width_easy - 100;
	posY_BR = posY + config::window_height_easy - 10;
	lastValidRecords.assign(
		config::game_recordedRecordValues, 
		static_cast<unsigned long>(config::game_valueInvalidRecord));
	initializeRecordsTable();
	initializeTextOfTable();
}

RecordsOverlay::~RecordsOverlay()
{
}

void RecordsOverlay::draw(sf::RenderWindow& window)
{
	if (displayed)
	{
		window.draw(assets::shapes_records_background_overlay);
		//window.draw(assets::shapes_records_background_box_border);
		window.draw(assets::shapes_records_background_box);

		for (const auto& shape : recordsTable_Circle)
		{
			window.draw(shape);
		}

		for (const auto& shape : recordsTable)
		{
			window.draw(shape);
		}

		for (const auto& shape : recordsTable_Convex)
		{
			window.draw(shape);
		}
		window.draw(localFlagShape);

		for (const auto& text : textOfTable)
		{
			window.draw(text);
		}
	
		btnClose.draw(window);
	}
}

void RecordsOverlay::processMousePosition(int x, int y)
{
	auto mouseClose = btnClose.processMousePosition(x, y);

}

bool RecordsOverlay::processLeftClick(int x, int y)
{
	auto clickClose = btnClose.processLeftClick(x, y);
	if (clickClose == Button::State::Clicked)
	{
		btnClose.deactivate(); //so button is deactivated after re-opening records overlay
	}
	return (clickClose == Button::State::Clicked);
}

void RecordsOverlay::display(std::vector<unsigned long> records)
{
	displayed = true;
	lastValidRecords.assign(records.begin(), records.end());
	initializeTextOfTable();
}

void RecordsOverlay::hide()
{
	displayed = false;
}

bool RecordsOverlay::isDisplayed()
{
	return displayed;
}

void RecordsOverlay::updatePosition(unsigned int newGameMode)
{
	auto window_width = config::window_width_easy;
	auto window_height = config::window_height_easy;
	switch (newGameMode)
	{
	case 0: // Easy
		//do nothing
		break;
	case 1: // Medium
		window_width = config::window_width_medium;
		window_height = config::window_height_medium;
		break;
	case 2: // Hard
		window_width = config::window_width_hard;
		window_height = config::window_height_hard;
		break;
	default:
		break;
	}

	posX = window_width / 2 - ((config::window_width_easy - 100) / 2);
	posY = window_height / 2 - ((config::window_height_easy - 10) / 2);
	posX_BR = posX + config::window_width_easy - 100;
	posY_BR = posY + config::window_height_easy - 10;

	btnClose.setPositionX(window_width / 2 + ((config::window_width_easy - 100) / 2) - 45);
	btnClose.setPositionY(window_height / 2 - ((config::window_height_easy - 10) / 2) + 10);

	initializeRecordsTable();
	initializeTextOfTable();
}

void RecordsOverlay::initializeRecordsTable()
{
	recordsTable.clear();
	recordsTable_Circle.clear();
	recordsTable_Convex.clear();

	float localX_UL = static_cast<float>(posX + 10);
	float localY_UL = static_cast<float>(posY + 80);
	float localX_BR = static_cast<float>(posX_BR - 10);
	float localY_BR = static_cast<float>(posY_BR - 10);
	float localY_offset = (localY_BR - localY_UL) / 3;

	sf::RectangleShape bg_difficulty;

	bg_difficulty.setSize(sf::Vector2f(
		localX_BR - localX_UL,
		localY_offset));
	bg_difficulty.setFillColor(assets::color_blue_dark_semitransparent);
	bg_difficulty.setPosition(localX_UL, localY_UL);
	recordsTable.push_back(bg_difficulty);

	bg_difficulty.setFillColor(assets::color_orange_semitransparent);
	bg_difficulty.setPosition(localX_UL, localY_UL + localY_offset);
	recordsTable.push_back(bg_difficulty);

	bg_difficulty.setFillColor(assets::color_red_dark_semitransparent);
	bg_difficulty.setPosition(localX_UL, localY_UL + 2 * localY_offset);
	recordsTable.push_back(bg_difficulty);

	bg_difficulty.setSize(sf::Vector2f(
		localX_BR - localX_UL - 30,
		localY_offset - 10));
	bg_difficulty.setFillColor(assets::color_grey_dark);
	bg_difficulty.setPosition(localX_UL + 35, localY_UL + 5);
	recordsTable.push_back(bg_difficulty);
	bg_difficulty.setPosition(localX_UL + 35, localY_UL + 5 + localY_offset);
	recordsTable.push_back(bg_difficulty);
	bg_difficulty.setPosition(localX_UL + 35, localY_UL + 5 + 2 * localY_offset);
	recordsTable.push_back(bg_difficulty);

	localX_UL += 35;
	localY_UL += 5;
	localY_BR -= 2 * localY_offset + 5;
	float localX_offset = (localX_BR - localX_UL) / 3;
	localY_offset = (localY_BR - localY_UL) / 3;
	bg_difficulty.setSize(sf::Vector2f(localX_offset, localY_offset));
	bg_difficulty.setFillColor(assets::color_yellow_semitransparent);
	sf::RectangleShape fill = bg_difficulty;
	fill.setSize(sf::Vector2f(localX_offset - 6, localY_offset - 6));
	fill.setFillColor(assets::color_grey_dark);
	for (size_t d = 0; d < 3; d++)
	{
		for (size_t r = 0; r < 3; r++)
		{
			bg_difficulty.setPosition(
				localX_UL + localX_offset * r,
				localY_UL + localY_offset * r + 10 * d + localY_offset * 3 * d);
			recordsTable.push_back(bg_difficulty);
			fill.setPosition(
				localX_UL + localX_offset * r + 3,
				localY_UL + localY_offset * r + 10 * d + localY_offset * 3 * d + 3);
			recordsTable.push_back(fill);
		}
	}

	sf::CircleShape circ = assets::shapes_stopclock_border;
	circ.setPosition(
		localX_UL + localX_offset / 2 - 10,
		localY_UL - 37);
	recordsTable_Circle.push_back(circ);
	circ = assets::shapes_stopclock_body;
	circ.setFillColor(assets::color_grey_dark);
	circ.setPosition(
		localX_UL + localX_offset / 2 - 7,
		localY_UL - 34);
	recordsTable_Circle.push_back(circ);
	sf::RectangleShape rect = assets::shapes_stopclock_top_1;
	rect.setPosition(
		localX_UL + localX_offset / 2 + 1,
		localY_UL - 41);
	recordsTable.push_back(rect);
	rect = assets::shapes_stopclock_top_2;
	rect.setPosition(
		localX_UL + localX_offset / 2 - 2,
		localY_UL - 43);
	recordsTable.push_back(rect);
	rect = assets::shapes_stopclock_needle;
	rect.setPosition(
		localX_UL + localX_offset / 2 + 3,
		localY_UL - 28);
	recordsTable.push_back(rect);

	sf::ConvexShape conv = assets::shapes_pointer_arrow;
	conv.setPosition(
		localX_UL + localX_offset * 3 / 2 - 5,
		localY_UL - 40);
	recordsTable_Convex.push_back(conv);
	rect = assets::shapes_pointer_arrowTail;
	rect.setPosition(
		localX_UL + localX_offset * 3 / 2 - 2,
		localY_UL - 28);
	recordsTable.push_back(rect);

	circ = assets::shapes_flag_flagBorder;
	circ.setPosition(
		localX_UL + localX_offset * 5 / 2 + 5 - config::game_cellSizeSide * 0.32,
		localY_UL - 36 + config::game_cellSizeSide * 0.37);
	recordsTable_Circle.push_back(circ);
	rect = assets::shapes_flag_pole;
	rect.setPosition(
		localX_UL + localX_offset * 5 / 2 + 5,
		localY_UL - 36);
	recordsTable.push_back(rect);
	circ = assets::shapes_flag_flag;
	circ.setFillColor(assets::color_yellow);
	circ.setPosition(
		localX_UL + localX_offset * 5 / 2 + 5 - config::game_cellSizeSide * 0.24,
		localY_UL - 36 + config::game_cellSizeSide * 0.3);
	localFlagShape = circ;

	rect = assets::shapes_status_bar;
	rect.setFillColor(assets::color_yellow_semitransparent);
	rect.setSize(sf::Vector2f(
		static_cast<float>((posX_BR - posX) / 20 * 7), 5.0f));
	rect.setPosition(
		static_cast<float>(posX_BR - (posX_BR - posX) / 2 - (posX_BR - posX) / 20 * 7 / 2),
		static_cast<float>(posY) + 30.0f);
	recordsTable.push_back(rect);

	/*localX_UL += 40;
	localY_UL -= 40;
	bg_difficulty.setSize(sf::Vector2f(
		localX_BR - localX_UL,
		localY_BR - localY_UL));
	bg_difficulty.setFillColor(assets::color_grey_darkest_semitransparent);
	bg_difficulty.setPosition(localX_UL, localY_UL);
	//recordsTable.push_back(bg_difficulty);
	*/
}

void RecordsOverlay::initializeTextOfTable()
{
	textOfTable.clear();

	float localX_UL = static_cast<float>(posX + 45);
	float localY_UL = static_cast<float>(posY + 85);
	float localX_BR = static_cast<float>(posX_BR - 10);
	float localY_BR = static_cast<float>(posY_BR - 10);
	float localY_offset = (localY_BR - localY_UL) / 3;
	localY_BR -= 2 * localY_offset + 5;
	float localX_offset = (localX_BR - localX_UL) / 3;
	localY_offset = (localY_BR - localY_UL) / 3;

	auto text = assets::clickCounter;
	for (size_t d = 0; d < lastValidRecords.size() / 3; d++)
	{
		const auto y = localY_UL + localY_offset * d + 7 * (d / 3);
		bool invalidRecord = (
			(lastValidRecords.at(d * 3 + 0) == config::game_valueInvalidRecord) &&
			(lastValidRecords.at(d * 3 + 1) == config::game_valueInvalidRecord) &&
			(lastValidRecords.at(d * 3 + 2) == config::game_valueInvalidRecord)
			);
		for (size_t r = 0; r < 3; r++)
		{
			const auto x = localX_UL + localX_offset * r;
			const auto recordAsNum = lastValidRecords.at(d * 3 + r);
			std::string recordAsStr;
			if (invalidRecord)
			{
				recordAsStr = "N/A";
				text.setFillColor(assets::color_grey_medium_dark);
			}
			else
			{
				recordAsStr = (r == 0) ?
					timeAsStr(recordAsNum) :
					std::to_string(recordAsNum);
				text.setFillColor(assets::color_grey_lightest);
			}
			text.setString(recordAsStr);
			assets::centerText(text, x, y,
				x + localX_offset, y + localY_offset);
			textOfTable.push_back(text);
		}
	}

	localX_UL = static_cast<float>(posX + 10);
	localY_UL = static_cast<float>(posY + 80);
	localX_BR = static_cast<float>(posX + 45);
	localY_BR = static_cast<float>(posY_BR - 10);
	localY_offset = (localY_BR - localY_UL) / 3;
	text = assets::clickCounter;
	text.setFillColor(assets::color_grey_lightest);
	std::vector<std::string> diffs{ "E","M","H" };
	std::vector<float> offsetsX{ 10,-5,0};
	for (size_t i = 0; i < diffs.size(); i++)
	{
		assets::centerText(text, 
			localX_UL, localY_UL + localY_offset * i,
			localX_BR, localY_UL + localY_offset * (i + 1));
		text.move(offsetsX.at(i), 0);
		text.setString(diffs.at(i));
		textOfTable.push_back(text);
	}

	text = assets::restartButton;
	text.setString("Your records");
	text.setFillColor(assets::color_grey_lightest);
	assets::centerText(text,
		static_cast<float>(posX), static_cast<float>(posY),
		static_cast<float>(posX_BR), static_cast<float>(posY + 40));
	textOfTable.push_back(text);

	/*text.setString("000000");
	assets::centerText(text,
		localX_UL, localY_UL,
		localX_UL + localX_offset, localY_UL + localY_offset);
	textOfTable.push_back(text);*/
}

template<class T>
std::string RecordsOverlay::timeAsStr(T timeInMs)
{
	auto ds = timeInMs / 100;
	const auto min = ds / (10 * 60);
	const auto sec = (ds - min * (10 * 60)) / 10;
	ds = ds - sec * 10 - min * (10 * 60);
	auto str =
		std::to_string(min) + " : " +
		std::to_string(sec) + " ' " +
		std::to_string(ds);
	return str;
}
