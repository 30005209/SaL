#ifndef _gameManager
#define _gameManager

#include "Player.h"
#include <iostream>

class gameManager
{
private:

	//Base typing speed
	int gameSpeedBase = 90;
	
	//How much the typing speed can vary by
	int gameSpeedVar = 30;

public:
	gameManager();
	~gameManager();

	//enum to help legibility for colour sets
	enum { DEFAULT = 0, SNAKE = 1, LADDER = 2};


	//See if either player has won
	bool gameIsWon(Player*, Player*);
	
	//Change colour scheme to as set value
	void beGameMaster(int);

	//Change colour scheme to game Master by default
	void beGameMaster(void);

	//Change colour scheme to that of a player
	void bePlayer(Player*);

	//Randomly slow down text
	void randomSlow(void);
	
	//Write a given string in the "typwriter" fashion
	void typeWrite(string);

	//Create a link between two tiles (snake/ladder)
	void setLink(int, int, vector<Tile>&);

	//Get the base typing speed
	int getSpeedBase(void);

	//Get the potential max variance in typing speed
	int getSpeedVar(void);

	//Increase the typing speed within preset bounds
	void increaseSpeed(void);

};

#endif
