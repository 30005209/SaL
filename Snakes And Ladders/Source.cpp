#include<iostream>
#include "Die.h"
#include "Player.h"
#include <vector>
#include "console.h"
#include <chrono>
#include <fstream>
#include "gameManager.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::to_string;

int main()
{
	std::ifstream inFile;
	std::ofstream outFile;
	gameManager gM;
	static Console con;
	const int BOARD_SIZE = 25;
	vector<Tile> board;


	//Set the board numbers
	for (int i = 1; i <= BOARD_SIZE; i++)
	{
		board.push_back({ i, NULL });
	}

	//Set the Snakes
	gM.setLink(13, 2, board);
	gM.setLink(19, 6, board);
	gM.setLink(24, 3, board);

	//Set the Ladders
	gM.setLink(4, 17, board);
	gM.setLink(7, 19, board);
	gM.setLink(15, 22, board);


	//Set the player positions at start
	Player one(&board, &con), two(&board, &con);

	//If players have the same colours change the first player's colour
	while (one.getFore() == two.getFore())
	{
		one.decideColourScheme();
	}
	
	//Set names
	while (one.getName() == "unset" || one.getName() == two.getName())
	{
		string name;

		gM.bePlayer(&one);

		std::cin >> name;

		one.setName(name);

		gM.bePlayer(&two);

		std::cin >> name;

		two.setName(name);

		con.clear();
	}


	//While neither player has won keep playing
	while (!gM.gameIsWon(&one, &two))
	{		
		gM.beGameMaster();
		gM.typeWrite(one.getName() + " Vs " + two.getName() + " Round: " + to_string(one.getTurns()+1) + "\n");

		//So long as player two hasn't won - player 2 take a turn
		if (!two.isWinner())
		{
			gM.bePlayer(&one);
			gM.typeWrite(one.getName() + " is on tile " + to_string(one.getPos()));
			gM.typeWrite(" and rolled a " + to_string(one.takeTurn()));
			gM.typeWrite(" so is now on tile: " + to_string(one.getPos()));
			Sleep(Die::roll(100) + 500);
			cout << endl;
		}

		//So long as player two hasn't won - take a turn
		if (!one.isWinner())
		{
			gM.bePlayer(&two);
			gM.typeWrite(two.getName() + " is on tile " + to_string(two.getPos()));
			gM.typeWrite(" and rolled a "+ to_string(two.takeTurn()));
			gM.typeWrite(" so is now on tile: " + to_string(two.getPos()));
			Sleep(Die::roll(100) + 500);
		}

		if (one.getTurns() > 10)
		{

		}


		Sleep(500);

		con.clear();
		}

	//If player one won - declare them the victor
	if (one.isWinner())
	{
		outFile.open("Winner.txt");
		outFile << one.getName() << " with:  " << one.getTurns();
		gM.bePlayer(&one);
		gM.typeWrite("And the winner is..." + one.getName() + "(" + to_string(one.getTurns()) + ")");
	}

	//Otherwise if player two has won - declare them the victor
	else if (two.isWinner())
	{

		outFile.open("Winner.txt");
		outFile << two.getName() << " with:  " << two.getTurns();
		gM.bePlayer(&two);
		gM.typeWrite("And the winner is..." + two.getName() + "(" + to_string(two.getTurns()) + ")");
	}

	cin.ignore();
	cin.get();
	return 0;
}
