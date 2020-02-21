#include "Player.h"

Player::Player(vector<Tile>* board, Console* console)
{
	//Set the board pointer
	this->board = board;
	
	//Set their position to the start of the board
	this->pos = board->begin();

	//Set their turn number to 0
	this->turnNo = 0;

	//Make their name "unset"
	setName("unset");

	//Give them the console pointer
	this->con = console;

	//Decide on a random colour scheme
	decideColourScheme();

	//Set advanced to false by default
	setIsAdvanced(false);

	//Set tiredness to 0 by default
	setTiredness(0);

	//Set injury to false by default
	setIsInjured(false);
}


Player::~Player()
{
}

int Player::takeTurn(void)
{
	//Produce a roll (d6)
	int result = Die::roll();

	//Check if tired if so adjust die within range
	if (howTired())
	{
		result = result - tiredness;

		if (result < 0)
		{
			result = 0;
		}
	}

	if (!isInjured())
	{
		//If the result + their current position is less than the last tile
		//Allow the result of the die to be added
		if (pos->num + result <= (board->end() - 1)->num)
		{
			pos += result;
		}

		//If the link of the tile has been set (not a 0) move there
		if (pos->link)
		{
			pos = board->begin() + pos->link;
		}
	}
	else
	{
		result = 0;
	}
	turnNo++;

	//Return the dice roll
	return result;
}

bool Player::isWinner(void)
{
	//If the player's position is on the last tile they win
	return getPos() == (board->end() - 1)->num;
}

int Player::getPos(void)
{
	//Show the number of the tile they are on
	return pos->num;
}

Console::COLOUR Player::getFore(void)
{
	return foreCol;
}

void Player::decideColourScheme(void)
{
	this->foreCol = Console::COLOUR(Die::roll(6)+8);
}

void Player::decideColourScheme(Console::COLOUR fore)
{
	this->foreCol = fore;
}

void Player::setName(string name)
{
	this->name = name;
}

string Player::getName(void)
{
	return name;
}

int Player::getTurns(void)
{
	return turnNo;
}

void Player::setIsAdvanced(bool setting)
{
	this->isAdvanced = setting;
}

bool Player::getIsAdvanced(void)
{
	return isAdvanced;
}

void Player::setIsInjured(bool setting)
{
	injured = setting;
}

void Player::setTiredness(int amount)
{
	tiredness = amount;
}

bool Player::isInjured(void)
{
	return injured;
}

int Player::howTired(void)
{
	return tiredness;
}