#include <iostream>

using namespace std;

// Class representing the Tic-Tac-Toe board
class Board {
public:
    Board() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = ' ';
            }
        }
    }

    void display() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout << "---------\n";
        }
    }

    bool makeMove(int row, int col, char symbol) {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = symbol;
            return true;
        }
        return false;
    }

    bool checkWin(char symbol) {
        // Check rows and columns
        for (int i = 0; i < 3; ++i) {
            if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
                (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)) {
                return true;
            }
        }
        // Check diagonals
        if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
            (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) {
            return true;
        }
        return false;
    }

    bool isFull() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

private:
    char board[3][3];
};

// Class representing a player
class Player {
public:
    Player(char symbol) : symbol(symbol) {}

    char getSymbol() const {
        return symbol;
    }

private:
    char symbol;
};

// Class managing the game logic
class Game {
public:
    Game() : player1('X'), player2('O'), currentPlayer(&player1), board() {}

    void play() {
        while (true) {
            board.display();
            int row, col;
            cout << "Player " << currentPlayer->getSymbol() << ", enter your move (row and column): ";
            cin >> row >> col;

            if (board.makeMove(row - 1, col - 1, currentPlayer->getSymbol())) {
                if (board.checkWin(currentPlayer->getSymbol())) {
                    board.display();
                    cout << "Player " << currentPlayer->getSymbol() << " wins!\n";
                    break;
                }
                else if (board.isFull()) {
                    board.display();
                    cout << "The game is a draw!\n";
                    break;
                }
                switchPlayer();
            }
            else {
                cout << "Invalid move. Try again.\n";
            }
        }
    }

private:
    void switchPlayer() {
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }

    Player player1;
    Player player2;
    Player* currentPlayer;
    Board board;
};

int main() {
    Game game;
    game.play();
    return 0;
}
