#include<iostream>
#include "Die.h"
#include "Player.h"
#include <vector>
#include "console.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

bool gameIsWon(Player, Player);

int main()
{
	const int BOARD_SIZE = 25;
	vector<Tile> board;

	//Set the board numbers
	for (int i = 1; i <= BOARD_SIZE; i++)
	{
		board.push_back({ i, NULL });
	}	

	//When setting snakes/ladders the link number is the tile -1

	//Set the Snakes
	board.at(12).link = 1;
	board.at(18).link = 5;
	board.at(23).link = 2;

	//Set the Ladders
	board.at(3).link = 16;
	board.at(6).link = 18;
	board.at(14).link = 21;
	

	//Set the player positions at start
	Player one(&board), two(&board);

	//While neither player has won keep playing
	while (!gameIsWon(one, two))
	{
		//So long as player two hasn't won - player 2 take a turn
		if (!two.isWinner())
		{
			cout << "John is on tile: " << one.getPos();
			cout << " and rolled a " << one.takeTurn();
			cout << " so is now on tile: " << one.getPos() << endl << endl;
		}

		//So long as player two hasn't won - take a turn
		if (!one.isWinner())
		{
			cout << "Jane is on tile: " << two.getPos();
			cout << " and rolled a " << two.takeTurn();
			cout << " so is now on tile: " << two.getPos() << endl << endl;
		}
	}

	//If player one won - declare them the victor
	if (one.isWinner())
	{
		cout << "John has won " << endl;
	}

	//Otherwise if player two has won - declare them the victor
	else if (two.isWinner())
	{
		cout << "Jane has won " << endl;
	}


	cin.ignore();
	cin.get();
	return 0;
}



//Check if either player has won
bool gameIsWon(Player a, Player b)
{
	if (a.isWinner())
	{
		return true;
	}
	else if (b.isWinner())
	{
		return true;
	}
	else

	{
		return false;
	}
}