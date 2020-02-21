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

	//Change based on given parameters (should be enum type)
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

//By default set to the default style
void gameManager::beGameMaster(void)
{
	beGameMaster(DEFAULT);
}

//Change colout to a players colours
void gameManager::bePlayer(Player* player)
{
	static Console con;

	con.setColour(player->getFore());
}


//Sleep by a dice roll which is the variance + a base speed
//To stop it being too slow/too long
void gameManager::randomSlow(void)
{
	Sleep(Die::roll(getSpeedVar()) + getSpeedBase());
}

//Randomly slow between each character in a given string
void gameManager::typeWrite(string text)
{
	for (int i = 0; i < text.length(); i++)
	{
		randomSlow();
		std::cout << text[i];
	}
}

//Make a link between two tiles
void gameManager::setLink(int source, int linked, vector<Tile>& board)
{
	board.at(source - 1).link = linked - 1;
}

//Get base typing speed
int gameManager::getSpeedBase(void)
{
	return gameSpeedBase;
}

//Get max typing speed varience
int gameManager::getSpeedVar(void)
{
	return gameSpeedVar;
}

//Increase typing speed
void gameManager::increaseSpeed(void)
{
	//So long as the base spee isn't below 40
	//So that it doesn't become negative
	if (getSpeedBase() > 40)
	{
		//Be the game master and inform that the speed has increased
		this->beGameMaster();
		this->typeWrite("SPEED UP\n");
	
		//Reduce by 40
		gameSpeedBase -= 40;
	}
}
