#include <iostream>
#include <cstdlib>  // Thư viện cần thiết cho srand() và rand()
#include <ctime>    // Thư viện cần thiết cho time()

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
        system("cls");  // Xóa màn hình trên Windows
        cout << "  1   2   3\n";
     
        for (int i = 0; i < 3; ++i) {
            cout << i + 1 << " ";
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout << " ---+---+---\n";
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

    char getSymbolAt(int row, int col) const {
        return board[row][col];
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

    virtual void makeMove(Board& board) = 0;  // Lớp cơ sở không cần định nghĩa chi tiết

protected:
    char symbol;
};

// Class representing a human player
class Human : public Player {
public:
    Human(char symbol) : Player(symbol) {}

    void makeMove(Board& board) override {
        int row, col;
        while (true) {
            cout << "Player " << symbol << ", enter your move (row and column): ";
            cin >> row >> col;
            if (board.makeMove(row - 1, col - 1, symbol)) {
                break;
            }
            else {
                cout << "Invalid move. Try again.\n";
            }
        }
    }
};

// Base class representing a robot player
class Robot : public Player {
public:
    Robot(char symbol) : Player(symbol) {}

    void makeMove(Board& board) override {
        // Abstract method to be overridden by specific difficulty levels
    }
};

// Easy-level robot (random moves)
class EasyRobot : public Robot {
public:
    EasyRobot(char symbol) : Robot(symbol) {
        srand(time(0));
    }

    void makeMove(Board& board) override {
        int row, col;
        while (true) {
            row = rand() % 3;
            col = rand() % 3;
            if (board.makeMove(row, col, symbol)) {
                cout << "Robot " << symbol << " plays at (" << row + 1 << ", " << col + 1 << ").\n";
                break;
            }
        }
    }
};

// Medium-level robot (alternates between random and blocking moves)
class MediumRobot : public Robot {
public:
    MediumRobot(char symbol) : Robot(symbol), moveCount(0) {
        srand(time(0));
    }

    void makeMove(Board& board) override {
        if (moveCount % 2 == 0) {
            makeRandomMove(board);
        }
        else {
            if (!tryBlockingMove(board)) {
                makeRandomMove(board);
            }
        }
        moveCount++;
    }

private:
    int moveCount;

    void makeRandomMove(Board& board) {
        int row, col;
        while (true) {
            row = rand() % 3;
            col = rand() % 3;
            if (board.makeMove(row, col, symbol)) {
                cout << "Robot " << symbol << " plays at (" << row + 1 << ", " << col + 1 << ").\n";
                break;
            }
        }
    }

    bool tryBlockingMove(Board& board) {
        // Check rows, columns, and diagonals for potential player win and block
        for (int i = 0; i < 3; ++i) {
            // Check rows
            if (board.getSymbolAt(i, 0) == 'X' && board.getSymbolAt(i, 1) == 'X' && board.getSymbolAt(i, 2) == ' ') {
                board.makeMove(i, 2, symbol);
                return true;
            }
            if (board.getSymbolAt(i, 0) == ' ' && board.getSymbolAt(i, 1) == 'X' && board.getSymbolAt(i, 2) == 'X') {
                board.makeMove(i, 0, symbol);
                return true;
            }
            if (board.getSymbolAt(i, 0) == 'X' && board.getSymbolAt(i, 1) == ' ' && board.getSymbolAt(i, 2) == 'X') {
                board.makeMove(i, 1, symbol);
                return true;
            }

            // Check columns
            if (board.getSymbolAt(0, i) == 'X' && board.getSymbolAt(1, i) == 'X' && board.getSymbolAt(2, i) == ' ') {
                board.makeMove(2, i, symbol);
                return true;
            }
            if (board.getSymbolAt(0, i) == ' ' && board.getSymbolAt(1, i) == 'X' && board.getSymbolAt(2, i) == 'X') {
                board.makeMove(0, i, symbol);
                return true;
            }
            if (board.getSymbolAt(0, i) == 'X' && board.getSymbolAt(1, i) == ' ' && board.getSymbolAt(2, i) == 'X') {
                board.makeMove(1, i, symbol);
                return true;
            }
        }

        // Check diagonals
        if (board.getSymbolAt(0, 0) == 'X' && board.getSymbolAt(1, 1) == 'X' && board.getSymbolAt(2, 2) == ' ') {
            board.makeMove(2, 2, symbol);
            return true;
        }
        if (board.getSymbolAt(0, 0) == ' ' && board.getSymbolAt(1, 1) == 'X' && board.getSymbolAt(2, 2) == 'X') {
            board.makeMove(0, 0, symbol);
            return true;
        }
        if (board.getSymbolAt(0, 0) == 'X' && board.getSymbolAt(1, 1) == ' ' && board.getSymbolAt(2, 2) == 'X') {
            board.makeMove(1, 1, symbol);
            return true;
        }

        if (board.getSymbolAt(0, 2) == 'X' && board.getSymbolAt(1, 1) == 'X' && board.getSymbolAt(2, 0) == ' ') {
            board.makeMove(2, 0, symbol);
            return true;
        }
        if (board.getSymbolAt(0, 2) == ' ' && board.getSymbolAt(1, 1) == 'X' && board.getSymbolAt(2, 0) == 'X') {
            board.makeMove(0, 2, symbol);
            return true;
        }
        if (board.getSymbolAt(0, 2) == 'X' && board.getSymbolAt(1, 1) == ' ' && board.getSymbolAt(2, 0) == 'X') {
            board.makeMove(1, 1, symbol);
            return true;
        }

        return false;
    }
};

// Hard-level robot (aggressively blocks potential winning moves)
class HardRobot : public Robot {
public:
    HardRobot(char symbol) : Robot(symbol) {
        srand(time(0));
    }

    void makeMove(Board& board) override {
        if (!tryBlockingMove(board)) {
            makeRandomMove(board);
        }
    }

private:
    void makeRandomMove(Board& board) {
        int row, col;
        while (true) {
            row = rand() % 3;
            col = rand() % 3;
            if (board.makeMove(row, col, symbol)) {
                cout << "Robot " << symbol << " plays at (" << row + 1 << ", " << col + 1 << ").\n";
                break;
            }
        }
    }

    bool tryBlockingMove(Board& board) {
        // Same as MediumRobot's tryBlockingMove
        // Reuse the same logic for blocking
        for (int i = 0; i < 3; ++i) {
            // Check rows
            if (board.getSymbolAt(i, 0) == 'X' && board.getSymbolAt(i, 1) == 'X' && board.getSymbolAt(i, 2) == ' ') {
                board.makeMove(i, 2, symbol);
                return true;
            }
            if (board.getSymbolAt(i, 0) == ' ' && board.getSymbolAt(i, 1) == 'X' && board.getSymbolAt(i, 2) == 'X') {
                board.makeMove(i, 0, symbol);
                return true;
            }
            if (board.getSymbolAt(i, 0) == 'X' && board.getSymbolAt(i, 1) == ' ' && board.getSymbolAt(i, 2) == 'X') {
                board.makeMove(i, 1, symbol);
                return true;
            }

            // Check columns
            if (board.getSymbolAt(0, i) == 'X' && board.getSymbolAt(1, i) == 'X' && board.getSymbolAt(2, i) == ' ') {
                board.makeMove(2, i, symbol);
                return true;
            }
            if (board.getSymbolAt(0, i) == ' ' && board.getSymbolAt(1, i) == 'X' && board.getSymbolAt(2, i) == 'X') {
                board.makeMove(0, i, symbol);
                return true;
            }
            if (board.getSymbolAt(0, i) == 'X' && board.getSymbolAt(1, i) == ' ' && board.getSymbolAt(2, i) == 'X') {
                board.makeMove(1, i, symbol);
                return true;
            }
        }

        // Check diagonals
        if (board.getSymbolAt(0, 0) == 'X' && board.getSymbolAt(1, 1) == 'X' && board.getSymbolAt(2, 2) == ' ') {
            board.makeMove(2, 2, symbol);
            return true;
        }
        if (board.getSymbolAt(0, 0) == ' ' && board.getSymbolAt(1, 1) == 'X' && board.getSymbolAt(2, 2) == 'X') {
            board.makeMove(0, 0, symbol);
            return true;
        }
        if (board.getSymbolAt(0, 0) == 'X' && board.getSymbolAt(1, 1) == ' ' && board.getSymbolAt(2, 2) == 'X') {
            board.makeMove(1, 1, symbol);
            return true;
        }

        if (board.getSymbolAt(0, 2) == 'X' && board.getSymbolAt(1, 1) == 'X' && board.getSymbolAt(2, 0) == ' ') {
            board.makeMove(2, 0, symbol);
            return true;
        }
        if (board.getSymbolAt(0, 2) == ' ' && board.getSymbolAt(1, 1) == 'X' && board.getSymbolAt(2, 0) == 'X') {
            board.makeMove(0, 2, symbol);
            return true;
        }
        if (board.getSymbolAt(0, 2) == 'X' && board.getSymbolAt(1, 1) == ' ' && board.getSymbolAt(2, 0) == 'X') {
            board.makeMove(1, 1, symbol);
            return true;
        }

        return false;
    }
};


// Class managing the game logic
class Game {
public:
    Game() {
        cout << "Choose mode:\n";
        cout << "1. Play with another human\n";
        cout << "2. Play with robot\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            player1 = new Human('X');
            player2 = new Human('O');
        }
        else {
            cout << "Choose difficulty:\n";
            cout << "1. Easy\n";
            cout << "2. Medium\n";
            cout << "3. Hard\n";
            int difficulty;
            cin >> difficulty;

            player1 = new Human('X');
            switch (difficulty) {
            case 1: player2 = new EasyRobot('O'); break;
            case 2: player2 = new MediumRobot('O'); break;
            case 3: player2 = new HardRobot('O'); break;
            default: player2 = new EasyRobot('O'); break;
            }
        }

        currentPlayer = player1;
    }

    ~Game() {
        delete player1;
        delete player2;
    }

    void play() {
        while (true) {
            board.display();
            currentPlayer->makeMove(board);

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
    }

private:
    void switchPlayer() {
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }

    Player* player1;
    Player* player2;
    Player* currentPlayer;
    Board board;
};

int main() {
    Game game;
    game.play();
    return 0;
}
