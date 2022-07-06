//Welcome to my Liar's Dice Program! The goal of the game is to
//guess the amount of die faces in play between all
//players participating. Bluffing is encouraged have fun!

#include "Classes.h"

int main()
{
	// Read rules from file and display
	ifstream fin("LiarDiceRule.txt");
	string line;
	while (getline(fin, line))
		cout << line << endl;

	srand(time(0));
	// Declare local variables
	int numPlayers, turn = 0, prevTurn, choice;
	int currGuess[2], guess[2];
	bool round = false;
	char c = 'Y';

	// Ask the user for the number of players
	cout << endl << "Enter the number of players: ";
	cin >> numPlayers;

	// Must be more than 1 player
	while (numPlayers < 2)
	{
		cout << "Enter a valid number of players (more than 2) : ";
		cin >> numPlayers;
	}

	// Create the player objects for the number of players entered
	Player* players = new Player[numPlayers];
	int* scores = new int [numPlayers] { 0 };

	// Assign each player a number
	for (int i = 0; i < numPlayers; i++)
		players[i].setPlayer(i + 1);

	do
	{
		// The turn of player 1 at the start of every round
		round = false;
		turn = 0;
		cout << endl << "Player# " << turn + 1 << "'s turn" << endl;
		cout << "1 - See your dice" << endl;
		cout << "2 - Make a guess" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:	// if the player wants to see the dice before the guess
			players[turn].displayDice();
		case 2:	// Make the player make a guess
			cout << endl << "Make your guess" << endl;
			cout << "[number of dice]" << endl;
			cin >> currGuess[0];
			cout << "[dice face(1 - 6)]" << endl;
			cin >> currGuess[1];
		}

		int bluff = askForCallingBluff(turn, numPlayers);
		if (bluff != -1)
		{
			// If the user wants to call the previous player a liar
			cout << endl << "Player " << bluff + 1 << " called Player " << turn + 1 << " a liar." << endl;
			cout << "Checking..." << endl;

			// Check if previous player who made the last guess is lying
			if (checkForLiar(players, numPlayers, guess))
			{
				// Declare the player, who called the previous player a liar, the winner 
				cout << "Player " << turn + 1 << " was lying" << endl;
				cout << "Player " << bluff + 1 << " is the winner" << endl;
				scores[bluff]++;
			}
			else	// If the previous player was telling the truth
			{
				// Declare the previous player, who was called a liar, the winner 
				cout << "Player " << turn + 1 << " was not lying" << endl;
				cout << "Player " << turn + 1 << " is the winner" << endl;
				scores[turn] ++;
			}

			// set the round flag to true because the round has finished
			turn = 0;
			round = true;
		}

		// Changes the turns
		prevTurn = turn++;

		if (!round)
		{
			do
			{
				// Turn indicator
				cout << endl << "Player# " << turn + 1 << "'s turn" << endl;
				cout << "1 - See your dice" << endl;
				cout << "2 - Make guess" << endl;
				cout << "Enter your choice: ";
				cin >> choice;

				switch (choice)
				{
				case 1:	// If player would like to check own dice
					players[turn].displayDice();
				case 2:
					// If the user wants to make a guess
					cout << endl << "Make your guess" << endl;
					cout << "[number of dice]" << endl;
					cin >> currGuess[0];
					cout << "[dice face(1 - 6)]" << endl;
					cin >> currGuess[1];

					// check if the guess is valid
					while (currGuess[0] <= guess[0] || currGuess[1] > 6)
					{
						cout << endl << "Guess must be higher than previous total die" << endl;
						cout << "[number of dice]" << endl;
						cin >> currGuess[0];
						cout << "[dice face(1 - 6)]" << endl;
						cin >> currGuess[1];
					}
					// Update the guess
					guess[0] = currGuess[0];
					break;
				}

				int bluff = askForCallingBluff(turn, numPlayers);
				if (bluff != -1)
				{
					// If the user wants to call the bluff
					cout << endl << "Player " << bluff + 1 << " called Player " << turn + 1 << " a liar." << endl;
					cout << "Checking..." << endl;

					// Check if previous player who made the last guess was lying
					if (checkForLiar(players, numPlayers, guess))
					{
						// Declare the player, who called the previous player a liar, the winner 
						cout << "Player " << turn + 1 << " was lying" << endl;
						cout << "Player " << bluff + 1 << " is the winner" << endl;
						scores[bluff]++;
					}
					else	// If the previous player telling the turth
					{
						// Declare the previous player, who was called a liar, the winner 
						cout << "Player " << turn + 1 << " was not lying" << endl;
						cout << "Player " << turn + 1 << " is the winner" << endl;
						scores[turn] ++;
					}

					// set the round flag to true because the round has finished
					turn = 0;
					break;
				}

				// Update the turn
				prevTurn = turn++;

				if (turn == numPlayers)
					turn = 0;

			} while (!round);	// Loop until round is finished
		}
		// Updates score card and displays

		cout << endl << "\nThe final scores are: " << endl;
		for (int i = 0; i < numPlayers; i++)
		{
			cout << "Player " << i + 1 << "    " << scores[i] << endl;
			players[i].shuffle();
		}
		// Ask user if they would like to play another round
		cout << endl << "Do you want to play the next round (y / n): ";
		cin >> c;

	} while (c == 'y' || c == 'Y');

	return 0;
}