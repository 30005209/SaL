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
	//Set up needed info for reading files
	std::ifstream inFile;
	std::ofstream outFile;

	//Intialise a gameManager
	gameManager gM;

	//Make a console
	static Console con;

	//Set the board size
	const int BOARD_SIZE = 25;
	
	//Make a board
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

	gM.beGameMaster();
	gM.typeWrite("PRESS ANY ENTER TO BEGIN");
	cin.get();
	cin.clear();

	//Wipe board completly
	con.setColour(Console::BLACK, Console::BLACK);
	con.clear();
	gM.beGameMaster();

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

	//Ignore anything currently in the buffer
	cin.ignore();

	//Decide whethere player 1 wants to play in advanced mode
	string answer = "n";
	gM.bePlayer(&one);
	gM.typeWrite(one.getName() + " would you like to play in advanced mode (y/n): ");
	cin >> answer;
	one.setIsAdvanced(answer == "y");
	
	//Ignore anything else in the buffer
	cin.ignore();
	
	//Decide whethere player 2 wants to play in advanced mode
	gM.bePlayer(&two);
	answer = "n";
	gM.typeWrite(two.getName() + " would you like to play in advanced mode (y/n): ");
	cin >> answer;
	two.setIsAdvanced(answer == "y");
	

	if (one.getIsAdvanced() || two.getIsAdvanced())
	{
		//Explain rules for snakes
		con.setColour(Console::BLACK, Console::BLACK);
		con.clear();
		gM.beGameMaster();
		gM.typeWrite("In advanced mode Snakes will cause you to get injured\n");
		gM.typeWrite("This will cause your next roll to be ignored\n");


		Sleep(Die::roll(100) + 1000);


		con.setColour(Console::BLACK, Console::BLACK);
		con.clear();
		gM.beGameMaster();

		//Explain rules for ladders
		gM.typeWrite("Also you will get tired from Ladders\n");
		gM.typeWrite("Every 5 tiles you skip will add a -1 to your next roll (min of 0)\n");

		Sleep(Die::roll(100) + 1000);
	}

	gM.beGameMaster();
	gM.typeWrite("Now we're all set - let's begin...by seeing who goes first");
	
	Sleep(Die::roll(100) + 500);

	con.setColour(Console::BLACK, Console::BLACK);
	con.clear();
	gM.beGameMaster();
	
	
	int nOne = 0;
	int nTwo = 0;
	do
	{
		nOne = Die::roll();
		gM.bePlayer(&one);
		gM.typeWrite(one.getName() + " you got a " + to_string(nOne) + "\n");

		nTwo = Die::roll();
		gM.bePlayer(&two);
		gM.typeWrite(two.getName() + " you got a " + to_string(nTwo) +  "\n");

		//If they roll the same roll again
		if (nOne == nTwo)
		{
			Sleep(Die::roll(100) + 500);
			con.clear();
			gM.beGameMaster();
			gM.typeWrite("Lets try that again..\n");
		}

		//If player two rolled larger swap their info
		if (nTwo > nOne)
		{
			string nameSwap = two.getName();
			Console::COLOUR colourSwap = two.getFore();
			
			two.setName(one.getName());
			two.decideColourScheme(one.getFore());

			one.setName(nameSwap);
			one.decideColourScheme(colourSwap);

		}

		Sleep(Die::roll(100) + 500);

	} while (nOne == nTwo); //Don't stop rolling to go first until they have different rolls


	//While neither player has won keep playing
	while (!gM.gameIsWon(&one, &two))
	{	

		//Clear the console ready for next round
		con.clear();
	
		//Check if the game has been going on for longer than 4 turns
		//then on alternate turns speed up within limit
		if (one.getTurns() > 4 && one.getTurns() % 2
			&& !(one.isWinner() || two.isWinner()))
		{
			gM.increaseSpeed();

			Sleep(Die::roll(100) + 500);

			con.setColour(Console::BLACK, Console::BLACK);
			con.clear();
			gM.beGameMaster();
		}
		//Reset the relative starting positions
		int startingPos;

		gM.beGameMaster();
		gM.typeWrite(one.getName() + " Vs " + two.getName() + " Round: " + to_string(one.getTurns()+1) + "\n");

		//If not playing advanced more (i.e basic mode) ignore tiredness/injury
		if (!one.getIsAdvanced())
		{
			one.setTiredness(0);
			one.setIsInjured(false);
		}
		
		//If not playing advanced more (i.e basic mode) ignore tiredness/injury
		if (!two.getIsAdvanced())
		{
			two.setTiredness(0);
			two.setIsInjured(0);
		}
		//So long as player two hasn't won - player 2 take a turn
			if (!two.isWinner())
			{
				startingPos = one.getPos();

				gM.bePlayer(&one);
				gM.typeWrite(one.getName() + " is on tile " + to_string(one.getPos()));
				gM.typeWrite(" and rolled a ");

				//Save roll score to be used for snake/ladder calculation
				int roll = one.takeTurn();
				gM.typeWrite(to_string(roll) + " ");

				one.setTiredness(0);
				one.setIsInjured(false);

				//Has gone backwards - so taken a snake
				if (startingPos > one.getPos())
				{
					gM.beGameMaster(gM.SNAKE);
					gM.typeWrite("-SNAKE on tile " + to_string(startingPos + roll));


					one.setIsInjured(true);

					gM.bePlayer(&one);
					gM.typeWrite(" ");
				}
				//Moved more than 6 - so has hit a ladder
				else if (one.getPos() > startingPos + 6)
				{
					gM.beGameMaster(gM.LADDER);
					gM.typeWrite("-LADDER " + to_string(startingPos + roll));

					one.setTiredness(int((one.getPos() - startingPos) / 5));

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
				gM.typeWrite(" and rolled a ");

				//Save roll score to be used for snake/ladder calculation
				int roll = two.takeTurn();
				gM.typeWrite(to_string(roll) + " ");


				two.setTiredness(0);
				two.setIsInjured(false);

				//Has gone backwards - so taken a snake
				if (startingPos > two.getPos())
				{
					gM.beGameMaster(gM.SNAKE);
					gM.typeWrite("-SNAKE on tile " + to_string(startingPos + roll));

					two.setIsInjured(true);

					gM.bePlayer(&two);
					gM.typeWrite(" ");
				}
				//Moved more than 6 - so has hit a ladder
				else if (two.getPos() > startingPos + 6)
				{
					gM.beGameMaster(gM.LADDER);
					gM.typeWrite("-LADDER " + to_string(startingPos + roll));

					two.setTiredness(int((one.getPos() - startingPos) / 5));

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
