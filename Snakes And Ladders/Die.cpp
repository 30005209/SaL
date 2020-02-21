#include "Die.h"

//Set default size to 6
Die::Die()
{
	setSize(6);
}


Die::~Die()
{
}

//Set the size to the given size
void Die::setSize(int newSize)
{
	this->size = newSize;
}

//Roll on a six unless specified
int Die::roll(void)
{
	return roll(6);
}

//Create a RNG device if one hasn't been made 
//If one has - use that
int Die::roll(int number)
{
	static std::random_device rd;
	static std::mt19937 mersenne(rd());
	static std::uniform_int_distribution<int> dist(1, number);
	dist(mersenne);

	return dist(mersenne);
}
