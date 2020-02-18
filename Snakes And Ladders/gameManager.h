#pragma once
#include "Player.h"
#include <iostream>

class gameManager
{
public:
	gameManager();
	~gameManager();

	bool gameIsWon(Player*, Player*);
	void beGameMaster(void);
	void bePlayer(Player*);
	void randomSlow(void);
	void typeWrite(string);
	void setLink(int, int, vector<Tile>&);

};

