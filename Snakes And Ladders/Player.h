#ifndef _PLAYER
#define _PLAYER

#include "Die.h"
#include <iostream>
#include "console.h"

using std::vector;
using std::string;

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

	//The console the player is playing on
	Console* con;

	//The player has a colour scheme
	Console::COLOUR foreCol;

	//The player's name
	string name = "unset";

	//Number of turns taken
	int turnNo;

public:

	//Cannot have a player without a board or a console
	Player(vector<Tile>*, Console*);	
	~Player();

	//Taking a turn
	int takeTurn(void);
	bool isWinner(void);
	int getPos(void);
	Console::COLOUR getFore(void);
	void decideColourScheme(void);
	void decideColourScheme(Console::COLOUR);
	void setName(string);
	string getName(void);
	int getTurns(void);
};

#endif