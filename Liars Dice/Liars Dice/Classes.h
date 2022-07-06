#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

// A Dice class to simulate a dice
class Dice
{
private:
	// Dice face
	int face;
public:
	// constructor which randomly inializes the face
	Dice()
	{
		face = rand() % 6 + 1;
	}
	// Accessor function for the face
	int getFace()
	{
		return face;
	}
	void shuffle()
	{
		face = rand() % 6 + 1;
	}
};

// A Player class for a player
class Player
{
private:
	// Each player gets 5 dice
	int playerNum;
	Dice dice[5];
public:
	// Setter for player number
	void setPlayer(int n)
	{
		playerNum = n;
	}
	// Function to view all the dices of the players
	void displayDice()
	{
		for (int i = 0; i < 5; i++)
		{
			cout << "|" << dice[i].getFace() << "| ";
		}
		cout << endl;
	}
	// Function to count the occurrences of a number among the rolled dice
	int countOcurrences(int n)
	{
		int count = 0;
		for (int i = 0; i < 5; i++)
			if (dice[i].getFace() == n)
				count++;
		return count;
	}
	void shuffle()
	{
		for (int i = 0; i < 5; i++)
			dice[i].shuffle();
	}
};

// Function to check if the player was lying or not.
bool checkForLiar(Player allPlayers[], int numPlayers, int guess[])
{
	int count = 0;
	for (int i = 0; i < numPlayers; i++)
	{
		count += allPlayers[i].countOcurrences(guess[1]);
	}

	if (count == guess[0])
		return false;
	else return true;
}

int askForCallingBluff(int turn, int numPlayers)
{
	char c;
	cout << endl;
	for (int i = 0; i < numPlayers; i++)
	{
		if (turn != i)
		{
			cout << "Player " << i + 1 << ": Do you want to call bluff or pass (B/P)? ";
			cin >> c;
			if (c == 'b' || c == 'B')
				return i;
		}
	}
	return -1;
}