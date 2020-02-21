#include "gameManager.h"



gameManager::gameManager()
{
}


gameManager::~gameManager()
{
}

//Check if either player has won
bool gameManager::gameIsWon(Player *a, Player *b)
{

	if (a->isWinner())
	{
		return true;
	}
	else if (b->isWinner())
	{
		return true;
	}
	else

	{
		return false;
	}
}

void gameManager::beGameMaster(int type)
{
	static Console con;

	switch (type)
	{
	case DEFAULT:
		con.setColour(Console::BLACK, Console::WHITE);
		break;

	case SNAKE:
		con.setColour(Console::RED, Console::WHITE);
		break;

	case LADDER:
		con.setColour(Console::BLUE, Console::WHITE);
		break;
	}
}

void gameManager::beGameMaster(void)
{
	beGameMaster(DEFAULT);
}

void gameManager::bePlayer(Player* player)
{
	static Console con;

	con.setColour(player->getFore());
}


void gameManager::randomSlow(void)
{
	Sleep(Die::roll(getSpeedVar()) + getSpeedBase());
}

void gameManager::typeWrite(string text)
{
	for (int i = 0; i < text.length(); i++)
	{
		randomSlow();
		std::cout << text[i];
	}
}

void gameManager::setLink(int source, int linked, vector<Tile>& board)
{
	board.at(source - 1).link = linked - 1;
}

int gameManager::getSpeedBase(void)
{
	return gameSpeedBase;
}

int gameManager::getSpeedVar(void)
{
	return gameSpeedVar;
}

void gameManager::increaseSpeed(void)
{
	if (getSpeedBase() > 40)
	{
		gameSpeedBase -= 40;
	}
}
