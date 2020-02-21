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
	
	//Set the title to be Snakes and Ladders
	con.setWindowTitle("Snakes and Ladders");
	con.setWindowPosition(0, 0);
	con.setWindowSize(150, 750);

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

		gM.beGameMaster();

		gM.typeWrite("What would you like to be called Player 1:");

		string name;

		gM.bePlayer(&one);

		gM.typeWrite(" ");

		std::cin >> name;

		one.setName(name);


		gM.beGameMaster();

		gM.typeWrite("What would you like to be called Player 2:");


		gM.bePlayer(&two);

		gM.typeWrite(" ");

		std::cin >> name;

		two.setName(name);

		con.clear();
	}


	//While neither player has won keep playing
	while (!gM.gameIsWon(&one, &two))
	{	
		int startingPos;

		gM.beGameMaster();
		gM.typeWrite(one.getName() + " Vs " + two.getName() + " Round: " + to_string(one.getTurns()+1) + "\n");

		//So long as player two hasn't won - player 2 take a turn
		if (!two.isWinner())
		{
			startingPos = one.getPos();

			gM.bePlayer(&one);
			gM.typeWrite(one.getName() + " is on tile " + to_string(one.getPos()));
			gM.typeWrite(" and rolled a " + to_string(one.takeTurn()) + " ");
			
			//Has gone backwards - so taken a snake
			if (startingPos > one.getPos())
			{
				gM.beGameMaster(gM.SNAKE);
				gM.typeWrite("-SNAKE-");

				gM.bePlayer(&one);
				gM.typeWrite(" ");
			}
			//Moved more than 6 - so has hit a ladder
			else if (one.getPos() > startingPos + 6)
			{
				gM.beGameMaster(gM.LADDER);
				gM.typeWrite("-LADDER-");

				gM.bePlayer(&one);
				gM.typeWrite(" ");
			}
			else
			{
				gM.bePlayer(&one);
			}


			gM.typeWrite("so is now on tile: " + to_string(one.getPos()));
			Sleep(Die::roll(100) + 500);
			cout << endl;
		}

		//So long as player two hasn't won - take a turn
		if (!one.isWinner())
		{
			startingPos = two.getPos();
			gM.bePlayer(&two);
			gM.typeWrite(two.getName() + " is on tile " + to_string(two.getPos()));
			gM.typeWrite(" and rolled a " + to_string(two.takeTurn()) + " ");


			//Has gone backwards - so taken a snake
			if (startingPos > two.getPos())
			{
				gM.beGameMaster(gM.SNAKE);
				gM.typeWrite("-SNAKE-");

				gM.bePlayer(&two);
				gM.typeWrite(" ");
			}
			//Moved more than 6 - so has hit a ladder
			else if (two.getPos() > startingPos + 6)
			{
				gM.beGameMaster(gM.LADDER);
				gM.typeWrite("-LADDER-");

				gM.bePlayer(&two);
				gM.typeWrite(" ");
			}
			else
			{
				gM.bePlayer(&two);
			}

			gM.typeWrite("so is now on tile: " + to_string(two.getPos()));
			Sleep(Die::roll(100) + 500);
		}


		//Leave time to read the result
		Sleep(500);

		//Clear the console ready for next round
		con.clear();
		
		
		//Check if the game has been going on for longer than 4 turns
		//then on alternate turns speed up within limit
		if (one.getTurns() > 4 && one.getTurns() %2)
		{
			gM.beGameMaster();
			gM.typeWrite("SPEED UP ! \n");
			gM.increaseSpeed();
		}
	}

	//If player one won - declare them the victor
	if (one.isWinner())
	{
		outFile.open("Winner.txt");
		outFile << one.getName() << " with:  " << one.getTurns();
		gM.bePlayer(&one);
		gM.typeWrite("And the winner is..." + one.getName() + " in " + to_string(one.getTurns()) + " turns");
	}

	//Otherwise if player two has won - declare them the victor
	else if (two.isWinner())
	{
		outFile.open("Winner.txt");
		outFile << two.getName() << " with:  " << two.getTurns();
		gM.bePlayer(&two);
		gM.typeWrite("And the winner is..." + two.getName() + " in " + to_string(two.getTurns()) + " turns");
	}

	cin.ignore();
	cin.get();
	return 0;
}
