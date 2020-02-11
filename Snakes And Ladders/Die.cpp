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
	static std::random_device rd;
	static std::mt19937 mersenne(rd());
	static std::uniform_int_distribution<int> dist(1, 6);
	dist(mersenne);

	return dist(mersenne);
}
