#pragma once
#include "Die.h"
#include <iostream>

using std::vector;

struct Tile
{
	int num;
	Tile* next;
	bool link = false;
};
//
//bool operator==(Tile self, Tile other)
//{
//	return self.num == other.num;
//}
//
//bool operator!=(Tile self, Tile other)
//{
//	return !(self == other);
//}

class Player
{
private:
	vector<Tile>::iterator pos;
	vector<Tile>* board;

public:
	Player(vector<Tile>*);
	~Player();

	void takeTurn(void);
	bool isWinner(void);
	int getPos(void);
};

