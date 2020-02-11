#include<iostream>
#include "Die.h"
#include "Player.h"
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

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

int main()
{
	const int BOARD_SIZE = 25;
	vector<Tile> board;

	//Set the board numbers
	for (int i = 1; i <= BOARD_SIZE; i++)
	{
		board.push_back({ i, NULL });
	}

	//Set the next to self
	vector<Tile>::iterator it = board.begin();
	int i = 0;
	while (it != board.end())
	{
		if (i >= BOARD_SIZE)
		{
			it->next = NULL;
		}
		else
		{
			it->next = &board.at(i++);
		}
		it++;
	}
	

	//Set the Snakes
	board.at(12).next = &board.at(1);
	board.at(12).link = true;

	board.at(18).next = &board.at(5);
	board.at(18).link = true;

	board.at(23).next = &board.at(2);
	board.at(23).link = true;

	//Set the Ladders
	board.at(3).next = &board.at(16);
	board.at(3).link = true;

	board.at(6).next = &board.at(17);
	board.at(6).link = true;

	board.at(14).next = &board.at(21);
	board.at(14).link = true;
	

	//Set the player positions at start
	Player one(&board), two(&board);

	while (!gameIsWon(one, two))
	{
		if (!two.isWinner())
		{
			one.takeTurn();
			cout << "Player 1 is on tile: " << one.getPos() << endl;
		}

		if (!one.isWinner())
		{
			two.takeTurn();
			cout << "Player 2 is on tile: " << two.getPos() << endl;
		}
	}

	if (one.isWinner())
	{
		cout << "Player one has won " << endl;
	}
	else if (two.isWinner())
	{
		cout << "Player two has won " << endl;
	}


	cin.ignore();
	cin.get();
	return 0;
}
