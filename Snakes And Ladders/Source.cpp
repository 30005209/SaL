#include<iostream>
#include "Die.h"
#include "Player.h"
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

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
	board.at(18).next = &board.at(5);
	board.at(23).next = &board.at(2);

	//Set the Ladders
	board.at(3).next = &board.at(16);
	board.at(6).next = &board.at(17);
	board.at(14).next = &board.at(21);
	
	it = board.begin();
	while (it != board.end())
	{
		//Is Snake
		if (it->next->num < it->num)
		{
			cout << it->num << " snake to " << it->next->num << endl;
		}
		//Is Ladder
		else if (it->next->num > it->num)
		{
			cout << it->num << " ladder to " << it->next->num << endl;
		}
		else
		{
			cout << it->num << endl;
		}

		it++;
	}

	cin.ignore();
	cin.get();
	return 0;
}