#pragma once
#include "Die.h"
#include <iostream>

using std::vector;

//Tiles make up the game board
struct Tile
{
	int num;		//The tile number
	int link = 0;	//If the tile is a snake/ladder they will have a number else it will be 0
};

class Player
{
private:

	//The player keeps track of it's position on the board via an iterator
	vector<Tile>::iterator pos;

	//The board is a collection of tiles
	vector<Tile>* board;

public:

	//Cannot have a player without a board so a board is needed to construct
	Player(vector<Tile>*);	
	~Player();

	//Taking a turn
	int takeTurn(void);
	bool isWinner(void);
	int getPos(void);
};

