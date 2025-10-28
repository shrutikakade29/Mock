#include <iostream>
#include <cctype>
using namespace std;

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

void printBoard() {
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

bool hasWon(char player) {
    for (int i = 0; i < 3; i++) {
        // horizontal
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        // vertical
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    // left diagonal
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    // right diagonal
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

bool isBoardFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

void playTicTacToe(string player1Name, string player2Name,
                   char player1Symbol, char player2Symbol,
                   string currentPlayer, char currentSymbol) {
    bool gameEnded = false;

    while (!gameEnded) {
        cout << currentPlayer << "'s turn (" << currentSymbol << "). Enter your move (row and column: eg. 0 1): ";
        int row, col;
        cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[row][col] = currentSymbol;
        printBoard();

        if (hasWon(currentSymbol)) {
            cout << currentPlayer << " wins!\n";
            gameEnded = true;
        } else if (isBoardFull()) {
            cout << "It's a draw!\n";
            gameEnded = true;
        } else {
            // Switch players
            if (currentPlayer == player1Name) {
                currentPlayer = player2Name;
                currentSymbol = player2Symbol;
            } else {
                currentPlayer = player1Name;
                currentSymbol = player1Symbol;
            }
        }
    }
}

int main() {
    string player1Name = "Player 1";
    string player2Name = "Player 2";
    char player1Symbol, player2Symbol;
    string currentPlayer;
    char currentSymbol;

    // Player 1 chooses symbol
    while (true) {
        cout << player1Name << ", choose your symbol (X or O): ";
        cin >> player1Symbol;
        player1Symbol = toupper(player1Symbol);
        if (player1Symbol == 'X' || player1Symbol == 'O') {
            break;
        }
        cout << "Invalid choice. Please choose X or O.\n";
    }

    player2Symbol = (player1Symbol == 'X') ? 'O' : 'X';

    if (player1Symbol == 'X') {
        currentPlayer = player1Name;
        currentSymbol = player1Symbol;
    } else {
        currentPlayer = player2Name;
        currentSymbol = player2Symbol;
    }

    cout << player1Name << " is '" << player1Symbol << "' and "
         << player2Name << " is '" << player2Symbol << "'.\n";
    cout << "Player with 'X' goes first: " << currentPlayer << "\n";
    printBoard();

    playTicTacToe(player1Name, player2Name, player1Symbol, player2Symbol, currentPlayer, currentSymbol);

    return 0;
}
