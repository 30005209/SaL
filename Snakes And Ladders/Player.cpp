#include "Player.h"


Player::Player(vector<Tile>* board, Console* console)
{
	this->board = board;
	this->pos = board->begin();

	this->turnNo = 0;
	this->name = "unset";

	this->con = console;
	decideColourScheme();
}


Player::~Player()
{
}

int Player::takeTurn(void)
{
	//Produce a roll (d6)
	int result = Die::roll();

	//If the result + their current position is less than the last tile
	//Allow the result of the die to be added
	if (pos->num + result <= (board->end()-1)->num)
	{
		pos += result;
	}
	
	//If the link of the tile has been set (not a 0) move there
	if (pos->link)
	{
		pos = board->begin() + pos->link;
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
