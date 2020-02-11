#include "Player.h"


Player::Player(vector<Tile>* board)
{
	this->board = board;
	this->pos = board->begin();
}


Player::~Player()
{
}

int Player::takeTurn(void)
{
	int result = Die::roll();

	if (pos->num + result <= (board->end()-1)->num)
	{
		pos += result;
	}
	
	if (pos->link)
	{
		pos = board->begin() + pos->next->num-1;
	}

	return result;
}

bool Player::isWinner(void)
{
	return pos->num == (board->end()-1)->num;
}

int Player::getPos(void)
{
	return pos->num;
}
