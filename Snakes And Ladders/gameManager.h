#pragma once
#include "Player.h"
#include <iostream>

class gameManager
{
private:

	int gameSpeedBase = 90;
	int gameSpeedVar = 30;

public:
	gameManager();
	~gameManager();

	enum { DEFAULT = 0, SNAKE = 1, LADDER = 2};


	bool gameIsWon(Player*, Player*);
	void beGameMaster(int);
	void beGameMaster(void);
	void bePlayer(Player*);
	void randomSlow(void);
	void typeWrite(string);
	void setLink(int, int, vector<Tile>&);
	int getSpeedBase(void);
	int getSpeedVar(void);
	void increaseSpeed(void);

};

