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
	int result = Die::roll();

	std::cout << "Rolled a " << result << std::endl;

	if (pos->num + result <= (board->end()-1)->num)
	{
		pos += result;
	}
	
	if (pos->link)
	{
		std::cout << "LINK" << std::endl;
	}

}

bool Player::isWinner(void)
{
	return pos->num == (board->end()-1)->num;
}

int Player::getPos(void)
{
	return pos->num;
}
