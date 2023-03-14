// Romeo and Juliet - main

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

const int maxItems = 10, maxRounds = 30;

int items = 8, rounds = 1;
int tries = 3;
int bestScore = 0;
int shuffleDelayMs = 700;

void instructions();
void generateEasyShuffle(int arr[maxRounds][maxItems], int items, int rounds);
void runShuffle(int arr[maxRounds][maxItems], int items, int rounds, string &result, string symbol, int rows);
void printCoordinate(string arr[maxItems][maxItems], int rows, int cols, int defaultLength);
void checkWin(string correctAns, string response);
string fillStringLength(string str, int fullLength, char fillSymbol = ' ');
void clearScreen();

int main() {
    // Speed up
    ios::sync_with_stdio(0),
    cin.tie(0), cout.tie(0);

    // Program
    instructions();
    int shuffleArr[maxRounds][maxItems];
    while (true) {
        // Generate and run shuffle
        generateEasyShuffle(shuffleArr, items, rounds);
        string result;
        cout << '\n';
        runShuffle(shuffleArr, items, rounds, result, "o", 4);

        // User input answer
        cout << '\n';
        cout << " What's the answer? (enter the character of the key) \n";
        cout << " > " << flush;
        string response;
        getline(cin, response);

        // Response
        checkWin(result, response);

        // Continue
        cout << '\n';
        cout << " Do you want to continue? (y/n)\n";
        cout << " > " << flush;
        getline(cin, response);
        while (true) {
            if (response != "y" && response != "n") {
                cout << " > " << flush;
                getline(cin, response);
            } else {
                break;
            }
        }
        if (response == "y") {
            continue;
        } else {
            break;
        }
    }
    cout << " _Quit\n" << flush;
    this_thread::sleep_for(chrono::seconds(1));
    if (bestScore == 1) {
        cout << " Your best score was " << bestScore << " round.\n\n" << flush;
    } else {
        cout << " Your best score was " << bestScore << " rounds.\n\n" << flush;
    }
}

void instructions() {
    cout << "\n";
    cout << " - - - - - ROMEO AND JULIET - STELLAR SHUFFLE - - - - - \n";
    cout << " Welcome to Romeo and Juliet!\n";
    cout << " This is a game about tracking \"quickly-shuffled\" objects!\n";
    cout << " It is an analogy to the idea that Fate often leads to tragedies.\n";
    cout << "\n";
    cout << " >> Press ENTER to start <<" << flush;
    string tmp;
    getline(cin, tmp);
}

void generateEasyShuffle(int arr[maxRounds][maxItems], int items, int rounds) {
    // For each round i, perform an easy shuffle on the previous round
    srand(time(0));
    for (int round = 0; round < rounds; round++) {
        vector<int> unused(items);
        for (int i = 1; i <= items; i++) unused[i - 1] = i;
        for (int item = 0; item < items; item++) {
            int id = rand() % unused.size();
            arr[round][item] = unused[id];
            swap(unused[id], unused.back());
            unused.pop_back();
        }
    }
}

void runShuffle(int arr[maxRounds][maxItems], int items, int rounds, string &resultStr, string symbol, int rows) {
    // Choose the answer
    srand(time(0));
    int result = rand() % items + 1;

    // Initialize display array
    int cols = items / rows + (items % rows > 0 ? 1 : 0);
    string displayArr[maxItems][maxItems];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (cols * i + j + 1 == result) {
                displayArr[i][j] = "\"" + symbol + "\"";
            } else {
                displayArr[i][j] = symbol;
            }
        }
    }

    // Perform shuffling
    int defaultLength = max((int) symbol.length() + 2, 6);
    clearScreen();
    cout << fillStringLength("", defaultLength * 1.5) << "Round 0\n";
    printCoordinate(displayArr, rows, cols, defaultLength);
    this_thread::sleep_for(chrono::seconds(1));
    for (int round = 0; round < rounds; round++) {
        // Override display
        clearScreen();
        cout << fillStringLength("", defaultLength * 1.5) << "Round " << round + 1 << '\n';
        for (int item = 0; item < items; item++) {
            int oldPos = item;
            int oldRow = oldPos / cols;
            int oldCol = oldPos % cols;
            int newPos = arr[round][item] - 1;
            int newRow = newPos / cols;
            int newCol = newPos % cols;
            displayArr[oldRow][oldCol] = string(1, (char) ('A' + newRow)) + to_string(newCol + 1);
        }
        result = arr[round][result - 1];
        printCoordinate(displayArr, rows, cols, defaultLength);
        // Wait 0.7 seconds
        this_thread::sleep_for(chrono::milliseconds(shuffleDelayMs));
    }

    // Show symbol array
    clearScreen();
    cout << fillStringLength("", defaultLength * 1.5) << "Round End\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            displayArr[i][j] = symbol;
        }
    }
    printCoordinate(displayArr, rows, cols, defaultLength);
    this_thread::sleep_for(chrono::milliseconds(1000));

    // Show character array
    clearScreen();
    cout << fillStringLength("", defaultLength * 1.5) << "Result\n";
    int charId = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            displayArr[i][j] = string(1, (char) ('a' + charId));
            charId++;
        }
    }
    printCoordinate(displayArr, rows, cols, defaultLength);
    this_thread::sleep_for(chrono::milliseconds(500));

    // Result
    int resultRow = (result - 1) / cols;
    int resultCol = (result - 1) % cols;
    // resultStr = string(1, (char) ('A' + resultRow) + to_string(resultCol);
    resultStr = displayArr[resultRow][resultCol];
}

void printCoordinate(string arr[maxItems][maxItems], int rows, int cols, int defaultLength) {
    // First row
    for (int col = 0; col <= cols; col++) {
        if (col == 0) {
            cout << string(defaultLength, ' ');
        } else {
            cout << fillStringLength(to_string(col), defaultLength);
        }
    }
    cout << '\n';
    // Rest of the rows
    for (int row = 0; row < rows; row++) {
        // First column
        string character = string(1, (char) ('A' + row));
        cout << fillStringLength(character, defaultLength);
        // Rest of the columns
        for (int col = 0; col < cols; col++) {
            cout << fillStringLength(arr[row][col], defaultLength);
        }
        cout << '\n';
    }
    cout << flush;
}

void checkWin(string correctAns, string response) {
    if (correctAns != response) {
        // Wrong guess
        cout << "_Wrong.\n";
        this_thread::sleep_for(chrono::seconds(1));
        tries--;
        if (tries == 0) {
            cout << " Oops! You ran out of tries!\n" << flush;
            this_thread::sleep_for(chrono::seconds(1));
            if (rounds - 2 == 1) {
                cout << " Your final score was " << rounds - 2 << " round.\n" << flush;
            } else {
                cout << " Your final score was " << max(0, rounds - 2) << " rounds.\n" << flush;
            }
            rounds = 1;
            tries = 3;
        } else {
            if (tries == 1) {
                cout << " You have " << tries << " try left\n" << flush;
            } else {
                cout << "You have " << tries << " tries left\n" << flush;
            }
        }
    } else {
        // Correct guess
        cout << "_Correct!\n" << flush;
        this_thread::sleep_for(chrono::seconds(1));
        if (rounds == 1) {
            cout << " Your current score is " << rounds << " round.\n" << flush;
        } else {
            cout << " Your current score is " << rounds << " rounds.\n" << flush;
        }
        if (rounds > bestScore) {
            bestScore = rounds;
        }
        rounds += 2;
    }
    this_thread::sleep_for(chrono::seconds(1));
}

string fillStringLength(string str, int fullLength, char fillSymbol) {
    int moreFill = fullLength - str.length();
    int leftFill = moreFill / 2;
    return string(leftFill, fillSymbol) + str + string(moreFill - leftFill, fillSymbol);
}

void clearScreen() {
    cout << string(1000, '\n');
}