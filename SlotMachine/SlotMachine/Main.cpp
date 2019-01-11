#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

int AskQuestion(string message, vector<string> options = { "Yes", "No" });
int TakeDeposit(vector<int> options);
int PerformBet(int& money);
int ReturnWinnings(int bet, int points, int size);
int PlayGame(int bet);

int main() {
    srand(time(0));

    // Initializing variables
    int gameAccount = 0;
    bool wantToPlayAgain = false;
    vector<int> depositOptions = { 100, 300, 500 };

    // Game loop
    do {
        // Check if user needs to deposit
        if (gameAccount > 0) {
            int wantToDepositOption = AskQuestion("You have enough money on your account to make a bet, would you still like to make a deposit?");
            bool wantToDeposit = (wantToDepositOption == 1 ? true : false);

            // If user wants to deposit, let them [Function at bottom]
            if (wantToDeposit) gameAccount += TakeDeposit(depositOptions);
        }
        else
        {
            // Force user to deposit [Function at bottom]
            cout << "Before we get started you will need to deposit some money." << endl;
            gameAccount += TakeDeposit(depositOptions);
        }

        // Force user to make a bet [Function at bottom]
        int bet = PerformBet(gameAccount);
        // Play the game [Function at bottom]
        gameAccount += PlayGame(bet);

        cout << "Your new account balance is: " << gameAccount << endl;
        
        // Ask user if they want to play again [Function at bottom]
        int wantToPlayAgainOption = AskQuestion("Would you like to play again?");
        wantToPlayAgain = (wantToPlayAgainOption == 1 ? true : false);
    } while (wantToPlayAgain);

    return 0;
}

// Check SCIO for requirements about winnings?
int ReturnWinnings(int bet, int points, int size) {
    // Initialize variable
    int multiplier = 0;

    // If conditions are true, assing new value to multiplier
    if (points == size * 2 + 2) multiplier = (size == 3 ? 10 : 10 + size);
    else if (points > 0 && points < 5) multiplier = points + 1;
    else if (points >= 5 && points < size * 2 + 2) multiplier = points + 2;
    
    // Initialize variable
    int moneyWon = bet * multiplier;
    
    // Print if the user lost or won
    if (moneyWon == 0) cout << "You have lost [" << bet << "] with " << points << " correct rows!" << endl;
    else cout << "You have won [" << moneyWon << "] with " << points << " correct rows!" << endl;

    return moneyWon;
}

int PlayGame(int bet) {
    // Initialize variables
    const int size = 3;
    int points = 0;

    char matrix[size][size];
    char characters[3] = { 'A', 'O', 'X' };

    bool isLeftDiagonalRow = true, isRightDiagonalRow = true;
    bool isVerticalRow[size] = { 0 };
    
    // Set all to true
    for (int index = 0; index < size; index++) isVerticalRow[index] = true;
    
    // Set values of the matrix, start loop for rows
    for (int row = 0; row < size; row++) {
        // Initialize temporary variable to check the current row
        bool isHorizontalRow = true;

        // Start loop for columns
        for (int column = 0; column < size; column++) {
            // Set value for current row and column based on random value from characters
            matrix[row][column] = characters[rand() % 3];
            cout << "[ " << matrix[row][column] << " ]";

            // Check horizontal, vertical and diagonal rows
            if (isHorizontalRow && matrix[row][column] != matrix[row][0]) isHorizontalRow = false;
            if (isVerticalRow[column] && matrix[row][column] != matrix[0][column]) isVerticalRow[column] = false;
            if (isLeftDiagonalRow && row > 0 && column == row) isLeftDiagonalRow = (matrix[row][row] == matrix[0][0]);
            if (isRightDiagonalRow && row > 0 && column == size - row - 1) isRightDiagonalRow = (matrix[row][size - row - 1] == matrix[0][size - 1]);
        }
        cout << endl << endl;

        // Give point if full horizontal row
        if (isHorizontalRow) points++;
    }
    cout << endl;

    // Give points if vertical rows or diagonal rows
    for (bool columnIsTrue : isVerticalRow) if (columnIsTrue) points++;
    if (isLeftDiagonalRow && isRightDiagonalRow) points += 2;
    else if (isLeftDiagonalRow || isRightDiagonalRow) points++;

    cout << "You have [" << points << "] completed rows." << endl;

    // Get the amount of money the user lost or won
    return ReturnWinnings(bet, points, size);
}

int PerformBet(int& money) {
    // Initialize variables
    int min = 1, bet = 0;

    // Print range which the user can deposit within
    cout << "You can bet anything between " << min << "-" << money << endl;
    cout << "How much would you like to bet?" << endl;

    // Make sure the user deposits a valid amount
    do {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> bet;
    } while (!cin.good() || (bet < min || bet > money));

    // Remove money from gameAccount (money = reference variable)
    money -= bet;
    cout << "You have betted " << bet << " and it has been taken from your account and placed in the pot, your account is now at " << money << endl;

    return bet;
}

int TakeDeposit(vector<int> options) {
    // Declare new vector of strings
    vector<string> stringOptions;
    
    // Fill vector with values
    for (auto option : options) stringOptions.push_back(to_string(option));

    // Ask question and get int back, do -1 so it can be used as an index for the options[] array.
    int depositOption = AskQuestion("How much would you like to deposit?", stringOptions) - 1;
    // Get the value at selected index to set deposited money
    int depositedMoney = options[depositOption];

    cout << "You have deposited " << depositedMoney << ", lets continue!" << endl;
    return depositedMoney;
}

int AskQuestion(string question, vector<string> options) {
    // Declare variable
    int option;
    // Initialize variable
    int counter = 1;
    // Declare variable
    string optionString;
    
    // Create option string, example: 1. Yes, concatenate with line break
    for (auto option : options) {
        optionString += to_string(counter) + ". " + option + "\n";
        // Count up so the next option wont have the same reference number
        counter++;
    }
    
    // Ask question
    cout << question << endl << optionString;
    // Get answer
    cin >> option;

    // Check so its a valid answer
    while (!cin.good() || (option < 1 || option >= counter)) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> option;
    }

    return option;
}
