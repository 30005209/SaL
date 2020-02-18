#include<iostream>
#include "Die.h"
#include "Player.h"
#include <vector>
#include "console.h"
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::to_string;

bool gameIsWon(Player*, Player*);
void beGameMaster(void);
void bePlayer(Player*);
void randomSlow(void);
void typeWrite(string);
void setLink(int, int, vector<Tile>&);


int main()
{
	static Console con;

	const int BOARD_SIZE = 25;
	static vector<Tile> board;

	//Set the board numbers
	for (int i = 1; i <= BOARD_SIZE; i++)
	{
		board.push_back({ i, NULL });
	}

	//Set the Snakes
	setLink(13, 2, board);
	setLink(19, 6, board);
	setLink(24, 3, board);

	//Set the Ladders
	setLink(4, 17, board);
	setLink(7, 19, board);
	setLink(15, 22, board);


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

		bePlayer(&one);

		std::cin >> name;

		one.setName(name);

		bePlayer(&two);

		std::cin >> name;

		two.setName(name);
	}

	//While neither player has won keep playing
	while (!gameIsWon(&one, &two))
	{		
		//So long as player two hasn't won - player 2 take a turn
		if (!two.isWinner())
		{
			bePlayer(&one);
			typeWrite(one.getName() + " is on tile " + to_string(one.getPos()));
			typeWrite(" and rolled a " + to_string(one.takeTurn()));
			typeWrite(" so is now on tile: " + to_string(one.getPos()) + "\n");
		}

		//So long as player two hasn't won - take a turn
		if (!one.isWinner())
		{
			bePlayer(&two);
			typeWrite(two.getName() + " is on tile " + to_string(two.getPos()));
			typeWrite(" and rolled a " + to_string(two.takeTurn()));
			typeWrite(" so is now on tile: " + to_string(two.getPos()) + "\n");
		}
	}


	//If player one won - declare them the victor
	if (one.isWinner())
	{
		bePlayer(&one);
		typeWrite("And the winner is..." + one.getName());
	}

	//Otherwise if player two has won - declare them the victor
	else if (two.isWinner())
	{
		bePlayer(&two);
		typeWrite("And the winner is..." + two.getName());
	}

	cin.ignore();
	cin.get();
	return 0;
}

//Check if either player has won
bool gameIsWon(Player* a, Player* b)
{
	if (a->isWinner())
	{
		return true;
	}
	else if (b->isWinner())
	{
		return true;
	}
	else

	{
		return false;
	}
}

void beGameMaster(void)
{
	static Console con;
	
	con.setColour(Console::BLACK, Console::YELLOW);
}

void bePlayer(Player* player)
{
	static Console con;

	con.setColour(player->getFore());
}


void randomSlow(void)
{
	static std::random_device rd;
	static std::mt19937 mersenne(rd());
	static std::uniform_int_distribution<int> dist(50, 80);
	dist(mersenne);

	Sleep(dist(mersenne));

}

void typeWrite(string text)
{
	for (int i = 0; i < text.length(); i++)
	{
		randomSlow();
		cout << text[i];
	}
}

void setLink(int source, int linked, vector<Tile>& board)
{
	board.at(source-1).link = linked - 1;
}