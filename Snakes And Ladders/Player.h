#pragma once
#include "Die.h"

using std::vector;

struct Tile
{
	int num;
	Tile* next;
};

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

