#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

int AskQuestion(string message, vector<string> options = { "Yes", "No" });
int TakeDeposit(vector<int> options);
int PerformBet(int& money);
int CheckRow(char row[], int length);

int main() {
	srand(time(0));

	int depositedMoney = 0;
	bool wantToPlayAgain = false;
	char characters[3] = { 'A', 'O', 'X' };
	vector<int> depositOptions = { 100, 300, 500 };

	do {
		if (depositedMoney > 0) {
			int wantToDepositOption = AskQuestion("You have enough money on your account to make a bet, would you still like to make a deposit?");
			bool wantToDeposit = (wantToDepositOption == 1 ? true : false);

			if (wantToDeposit) depositedMoney += TakeDeposit(depositOptions);
		}
		else
		{
			cout << "Before we get started you will need to deposit some money." << endl;
			depositedMoney += TakeDeposit(depositOptions);
		}

		int bet = PerformBet(depositedMoney);

		// Move to function later
		int points = 0;
		const int size = 3; // This can't be an even number.
		char matrix[size][size] = { 
			{ 'X', 'A', 'X' },
			{ 'A', 'X', 'X' },
			{ 'X', 'O', 'X' }
		};
		char diagonalChecker[2];

		bool isLeftDiagonalRow = true;
		bool isRightDiagonalRow = true;

		for (int row = 0; row < size; row++) {
			bool isFullRow = true;

			for (int column = 0; column < size; column++) {
				// matrix[row][column] = characters[rand() % 3];
				cout << "[ " << matrix[row][column] << " ]";
				// cout << "[ " << row << "," << column << " ]";

				if (matrix[row][column] != matrix[row][0] && isFullRow) isFullRow = false;
				if (row > 0 && isLeftDiagonalRow) isLeftDiagonalRow = (matrix[row][row] == diagonalChecker[0]);
				if (row > 0 && isRightDiagonalRow) isRightDiagonalRow = (matrix[row][size - row - 1] == diagonalChecker[1]);
			}
			cout << endl << endl;

			if (isFullRow) points++;
			if (row == 0) { 
				diagonalChecker[0] = matrix[row][0];
				diagonalChecker[1] = matrix[row][size - 1];
			}
		}
		cout << endl;
	    cout << (isLeftDiagonalRow && isRightDiagonalRow ? "Double diagonal row found!" : (isLeftDiagonalRow ? "Left diagonal row found" : (isRightDiagonalRow ? "Right diagonal row found" : "No diagonal row found!"))) << endl;

		cout << "You got " << points << " points!" << endl;

		// End of "move to function later"

		int wantToPlayAgainOption = AskQuestion("Would you like to play again?");
		wantToPlayAgain = (wantToPlayAgainOption == 1 ? true : false);
	} while (wantToPlayAgain);

	return 0;
}

int PerformBet(int& money) {
	int min = 1, bet = 0;

	cout << "You can bet anything between " << min << "-" << money << endl;
	cout << "How much would you like to bet?" << endl;

	do {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> bet;
	} while (!cin.good() || (bet < min || bet > money));

	money -= bet;
	cout << "You have betted " << bet << " and it has been taken from your account and placed in the pot, your account is now at " << money << endl;

	return bet;
}

int TakeDeposit(vector<int> options) {
	vector<string> stringOptions;
	for (auto option : options) stringOptions.push_back(to_string(option));

	int depositOption = AskQuestion("How much would you like to deposit?", stringOptions) - 1;
	int depositedMoney = options[depositOption];

	cout << "You have deposited " << depositedMoney << ", lets continue!" << endl;
	return depositedMoney;
}

int AskQuestion(string question, vector<string> options) {
	int option;
	int counter = 1;
	string optionString;

	for (auto option : options) {
		optionString += to_string(counter) + ". " + option + "\n";
		counter++;
	}

	cout << question << endl << optionString;
	cin >> option;

	while (!cin.good() || (option < 1 || option >= counter)) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> option;
	}

	return option;
}