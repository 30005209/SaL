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

	//Tracks whether playing with tiredness / injury
	bool isAdvanced;

	//Tiredness
	int tiredness;

	//Injury
	bool injured;


public:

	//Cannot have a player without a board or a console
	Player(vector<Tile>*, Console*);	
	~Player();

	//Taking a turn
	int takeTurn(void);
	
	//See if player has won
	bool isWinner(void);
	
	//Get the position of the current tile
	int getPos(void);

	//Get the colour of the player (foreground)
	Console::COLOUR getFore(void);
	
	//Decide on colour scheme if colour not given
	void decideColourScheme(void);

	//Set colour scheme if colour given
	void decideColourScheme(Console::COLOUR);

	//Set the name of the  player
	void setName(string);

	//Get the name of the player
	string getName(void);
	
	//Get how many turns they have had
	int getTurns(void);


	//Set whether to make them play on advanced mode
	void setIsAdvanced(bool);

	//See if they are on advanced mode
	bool getIsAdvanced(void);


	//Set injury
	void setIsInjured(bool);

	//See if injured
	bool isInjured(void);
	   
	//Set how tired they are
	void setTiredness(int);

	//See how tired they are
	int howTired(void);
};

#endif