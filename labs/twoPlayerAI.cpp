#include <iostream>
#include <cctype>
#include <climits>
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
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
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

int minimax(char b[3][3], int depth, bool isMaximizing, char ai, char human) {
    if (hasWon(ai)) return 10 - depth;
    if (hasWon(human)) return depth - 10;
    if (isBoardFull()) return 0;

    if (isMaximizing) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == ' ') {
                    b[i][j] = ai;
                    best = max(best, minimax(b, depth + 1, false, ai, human));
                    b[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == ' ') {
                    b[i][j] = human;
                    best = min(best, minimax(b, depth + 1, true, ai, human));
                    b[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(char b[3][3], char ai, char human) {
    int bestScore = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == ' ') {
                b[i][j] = ai;
                int score = minimax(b, 0, false, ai, human);
                b[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

void playTicTacToe(string player1Name, string player2Name,
                   char player1Symbol, char player2Symbol,
                   string currentPlayer, char currentSymbol) {
    bool gameEnded = false;

    while (!gameEnded) {
        if (currentPlayer == player2Name) {
            cout << "AI (" << currentSymbol << ") is making a move...\n";
            pair<int, int> move = findBestMove(board, player2Symbol, player1Symbol);
            board[move.first][move.second] = currentSymbol;
        } else {
            cout << currentPlayer << "'s turn (" << currentSymbol << "). Enter your move (row col): ";
            int row, col;
            cin >> row >> col;

            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
                cout << "Invalid move. Try again.\n";
                continue;
            }
            board[row][col] = currentSymbol;
        }

        printBoard();

        if (hasWon(currentSymbol)) {
            cout << currentPlayer << " wins!\n";
            gameEnded = true;
        } else if (isBoardFull()) {
            cout << "It's a draw!\n";
            gameEnded = true;
        } else {
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
    string player2Name = "AI";
    char player1Symbol, player2Symbol;
    string currentPlayer;
    char currentSymbol;

    while (true) {
        cout << player1Name << ", choose your symbol (X or O): ";
        cin >> player1Symbol;
        player1Symbol = toupper(player1Symbol);
        if (player1Symbol == 'X' || player1Symbol == 'O') break;
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
