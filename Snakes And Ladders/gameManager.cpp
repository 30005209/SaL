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

void gameManager::beGameMaster(void)
{
	static Console con;

	con.setColour(Console::BLACK, Console::YELLOW);
}

void gameManager::bePlayer(Player* player)
{
	static Console con;

	con.setColour(player->getFore());
}


void gameManager::randomSlow(void)
{
	Sleep(Die::roll(20) + 50);
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
