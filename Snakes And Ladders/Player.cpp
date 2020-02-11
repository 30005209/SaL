#include "Player.h"


Player::Player(vector<Tile>* board)
{
	this->board = board;
	this->pos = board->begin();
}


Player::~Player()
{
}

void Player::takeTurn(void)
{
	pos = pos + Die::roll();
}

bool Player::isWinner(void)
{
	return pos == board->end();
}

int Player::getPos(void)
{
	return pos->num;
}
