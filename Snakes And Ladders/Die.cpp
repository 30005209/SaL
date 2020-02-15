#include "Die.h"

Die::Die()
{
	setSize(6);
}


Die::~Die()
{
}

void Die::setSize(int newSize)
{
	this->size = newSize;
}

int Die::roll(void)
{
	return roll(6);
}

int Die::roll(int number)
{
	static std::random_device rd;
	static std::mt19937 mersenne(rd());
	static std::uniform_int_distribution<int> dist(1, number);
	dist(mersenne);

	return dist(mersenne);
}
