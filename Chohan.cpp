#include <iostream>;
#include <string>;
#include <time.h>;

//ASK HOW TO DEAL WITH SPACES SINCE WE ARE USING string
//AS WELL AS LIMITING THE USER INPUT TO THE CORRECT DATA TYPE

// include the standard library 
using namespace std;

//prototype for gamePlay()
void gamePlay();

// the name of the user
string name;

// Store the number of AI players
int numPlayers=0;

// Keep track of the players still in the game
int playerCount;

// how much money the player has
double playerMoney=500;

// the max number of players
const int MAX_PLAYERS=9;

// the money of the AI players
double arrayPlayersMoney[MAX_PLAYERS];

// the main method for running the cho-han game 
int main() {

	// Introduction
	cout << "\n\n\n\nHello friend!\n\n" 
		<< "Would you care to try your luck with the yakuza?";

	// Ask the user their name
	cout << "\n\nWhat do you go by?\n";

	// user input for name
	cin >> name;

	// Ask the user for the number of opponents in the game
	cout << "\n\n\nWelcome to Cho-han " << name << "!\n\n" 
		<< "How many players do you want to face?\n";

	// Ensure that the number of AI players in the range: 1 < # < 10
	while ((numPlayers < 2) || (numPlayers > 9)) {
		cout << "Please choose a number between 2 and 9 inclusive!\n";
		cin >> numPlayers;
	}

	// Initialize the player count
	playerCount = numPlayers;

	// add money only to AI players in the game
	for (int n=0; n<MAX_PLAYERS; n++) {
		if (n<numPlayers)
		arrayPlayersMoney[n] = 500;
		else arrayPlayersMoney[n] = -1;
	}

	// run the game rounds
	gamePlay();

	// Ask if the player wants to play again
	cout << "\nWould you like to start over?\n\n";

		// the player's answer
		string answer;

		// Ensure that the response is yes or no,
		// If yes run game again, if no terminate
		while (answer != "yes") {
			cout << "Please answer yes or no. Don't test me!\n";
			cin >> answer;
			if (answer == "no")
				break;
			if (answer == "yes")
			main();
		}

	// Default return for main method
	return 0;
}


// simulate the rounds of cho-han
void gamePlay() {

	// Adjust the number of players in the game if an AI has
	// insufficient funds
	for (int n=0; n<numPlayers; n++) {
		if (arrayPlayersMoney[n] >= 0 &&
			arrayPlayersMoney[n] < 50) {
			playerCount--;
			arrayPlayersMoney[n] = -1;
		}

	}

	// only play if the player has at least 50 dollars
	if (playerMoney >= 50 && playerCount > 0) {

		// AI bet decisions
		int arrayDecision[MAX_PLAYERS];

		// AI bet placement for 1 round
		for (int n=0; n<numPlayers; n++) {
			arrayDecision[n] = rand() % 2;
		}

		// Ask player what his bet decision will be
		cout << "\n\nExcellent! Now that we have all "
			"the players ready, lets get started.\n" <<
		"Will you bet?\n";

		// the bet decision
		string decision;

		// Ensure that the player makes a valid decision
		do {
			cout << "Please answer exactly either: cho, han, or pass\n";
			cin >> decision;
		}
		while (!(decision == "cho" ||decision == "han" || decision == "pass"));

		// Place a bet of $50
		if (decision != "pass")
		playerMoney -= 50;

		// Place $50 bets for all AIs that have money
		for (int n= 0; n<numPlayers; n++) {
			if (arrayPlayersMoney[n] >= 50)
				arrayPlayersMoney[n] -= 50;
		}

		// dice 1 and 2
		int dice1, dice2;

		// pseudo-random # generator
		srand(time(0));

		// roll the dice
		dice1 = (rand() % 6 + 1);
		dice2 = (rand() % 6 + 1);

		// Display roll
		cout << "\n\n\nThe roll was: " << dice1 << " and " << dice2 << "\n\n";

		// sum of dice modded
		int moddicesum = (dice1 + dice2) % 2;

		// Display cho 
		if (moddicesum == 0)
			cout << "CHO!\n\n";

		// Display han
		if (moddicesum == 1)
			cout << "HAN!\n\n";


		// how many AI's had winning bets
		double winningAIs=0;

		// count total winning AI's
		for (int n=0; n<numPlayers; n++) {
			if ((arrayPlayersMoney[n] >= 0) && 
				(arrayDecision[n] == moddicesum))
				winningAIs++;
		}

		// Display the number of winning AI's this round
		cout << winningAIs << " AI players won this round!\n\n";

		// Check if the player won
		if ((decision == "cho" && moddicesum == 0) ||
			(decision == "han" && moddicesum == 1)) {
				winningAIs++;
				playerMoney += ((1 + numPlayers) * 50)
					           / winningAIs;
				cout << "You won $" 
					<< (((1 + playerCount) * 50)/ winningAIs) - 50
					<< "! Your total earnings are: $" 
					<< playerMoney << "\n\n";
		}

		// Check the AI's for winning bets, 
		// and add to the winners money
		// or subtracts losers money
		for (int n=0; n<numPlayers; n++) {
			// without pass
			if ((arrayPlayersMoney[n] >= 0) 
				&& decision != "pass" 
				&& (arrayDecision[n] == moddicesum)) {
				// update nth AI's money
				arrayPlayersMoney[n] += 
					((1 + playerCount) * 50)/winningAIs;
				// display nth AI's earnings
				cout << "Player" << n + 1 << " won $" << 
					(((1 + playerCount) * 50) / winningAIs) - 50 
					<< "!\n" << "His earnings are: $" 
					<< arrayPlayersMoney[n] << "\n\n";
			}
			// If the player passes earnings reduced by 50
			else if ((arrayPlayersMoney[n] >= 0) 
				&& decision == "pass" 
				&& (arrayDecision[n] == moddicesum)) {
				// update nth AI's money
				arrayPlayersMoney[n] += 
					(playerCount * 50)/winningAIs;
				// display nth AI's earnings
				cout << "Player" << n + 1 << " won $" << 
					((playerCount * 50) / winningAIs) - 50 
					<< "!\n" << "His earnings are: $" 
					<< arrayPlayersMoney[n] << "\n\n";
			}
			// If the player loses money, but can still bet
			else if (arrayPlayersMoney[n] >= 50) {
				//display nth AI's earnings loss
				cout << "Player" << n + 1 
					<< " lost $50. His earnings are: $"
					<< arrayPlayersMoney[n] << "\n\n";
			}

			// if the player loses money and cannot bet again
			else if (arrayPlayersMoney[n] >= 0) {
				//display nth player is out of the game!
				cout << "Player" << n + 1 << "lost $50."
					<< "With only $" << arrayPlayersMoney[n] 
					<< " left, he can't bet anymore!" << "\n\n";
			}
		}

		// If the player makes a bad bet they lose money
		if ((decision == "cho" && moddicesum == 1) ||
			(decision == "han" && moddicesum == 0)) {
			cout << "Dang! You lost $50! " 
				<< "Your earnings now are: $" 
				<< playerMoney << "\n\n";
		}

		// If the player passes let them know
		if (decision == "pass")
			cout << "You pass your turn. Your earnings are: $" 
			<< playerMoney << "\n\n";

		// Display winnings if at least 1 player wins
		if (winningAIs != 0) {
			// Display the jackpot if player does not pass
			if (decision != "pass")
			cout << "\nThe Pool was: $" 
				<< (playerCount + 1) * 50 << "\n"
				<< "With " << winningAIs 
				<< " winner(s), each net gain is roughly: $"
				<< (((playerCount + 1) * 50) / winningAIs) - 50 << "\n\n";
			// Diplay the jackpot; is 1 less if the player passes
			if (decision == "pass")
				cout << "\nThe Pool was: $" 
				<< playerCount * 50 << "\n"
				<< "With " << winningAIs 
				<< " winner(s), each net gain is roughly: $"
				<< ((playerCount * 50) / winningAIs) - 50 << "\n\n";
		}

		// If no players win, everyone loses their money?
		if (winningAIs == 0) {
			if (decision != "pass")
			cout << "\nThe Pool was: $" 
				<< (playerCount + 1) * 50 << "\n"
				<< "With " << winningAIs 
				<< " winner(s), everyone lost their $50 bet!\n\n";
			// Diplay the loss; is 1 less if the player does not bet
			if (decision == "pass")
				cout << "\nThe Pool was: $" 
				<< playerCount * 50 << "\n"
				<< "With " << winningAIs 
				<< " winner(s), everyone lost their $50 bet!\n\n";
			
		}

		// Start the next round
		gamePlay();
	}

	// You won!
	else if (playerMoney >= 50)
		cout << "\n\nAll other players are without money. "
		<< "You are the Cho-han master! Unfortunately, " 
		<< name << " we must kill you. YAKUZAAA!!\n";

	// You Lost!
	else cout << "\n\nAw, out of money!\n\n "
		<< "The Yakuza are waiting for you...\n";
}
