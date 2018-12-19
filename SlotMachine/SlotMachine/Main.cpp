#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

int AskQuestion(string message, vector<string> options = { "Yes", "No" });
int TakeDeposit(vector<int> options);
int PerformBet(int& money);
int CheckRow(char row[]);

int main() {
	srand(time(0));

	int depositedMoney = 0;
	bool wantToPlayAgain = false;
	char items[3] = { 'A', 'O', 'X' };
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
		int correctRows = 0;
		char matrix[3][3];

		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				matrix[y][x] = items[rand() % 3];
				cout << "[ " << matrix[y][x] << " ]";
			}
			cout << endl;

			correctRows += CheckRow(matrix[y]);
		}

		cout << endl;
		cout << "Correct Rows: " << correctRows << endl;

		// End of "move to function later"

		int wantToPlayAgainOption = AskQuestion("Would you like to play again?");
		wantToPlayAgain = (wantToPlayAgainOption == 1 ? true : false);
	} while (wantToPlayAgain);

	return 0;
}

int CheckRow(char row[]) {
	
	int rowLength = sizeof(row) / sizeof(row[0]); // kms
	cout << "| " << sizeof(row) << " |" << sizeof(row[0]) << " " << sizeof(row[1]) << " " << sizeof(row[2]) << endl; // kms life is hard

	int index = 0;
	bool isMatch = true;

	do {
		if (row[index] == row[index + 1]) {
			cout << "MATCH" << endl;
			if (index + 1 == rowLength - 1) break;
		}
		else
		{
			cout << "NO MATCH (BREAK)" << endl;
			isMatch = false;
		}
		index++;
	} while ((index + 1) < rowLength && isMatch);
	
	return isMatch ? 1 : 0;
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