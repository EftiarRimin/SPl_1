#include <iostream>
#include <limits>
using namespace std;

void draw_board(int *b) {
    int k = 0;
    cout << "----++---++----" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "| ";
            if (b[k] == 0) {
                cout << k + 1 << " |";
            } else {
                if (b[k] == -1) {
                    cout << "X |";
                } else {
                    cout << "O |";
                }
            }
            k++;
        }
        cout << "\n----++---++----" << endl;
    }
}

int win(const int *board) {
    unsigned wins[8][3] = {{0, 1, 2},
                           {3, 4, 5},
                           {6, 7, 8},
                           {0, 3, 6},
                           {1, 4, 7},
                           {2, 5, 8},
                           {0, 4, 8},
                           {2, 4, 6}};
    int i;
    for (i = 0; i < 8; ++i) {
        if (board[wins[i][0]] != 0 &&
            board[wins[i][0]] == board[wins[i][1]] && board[wins[i][1]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}

int minimax(int *board, int player) {
    int winner = win(board);

    if (winner != 0)
        return winner * player;

    int move = -1;
    int score = -2;

    for (int i = 0; i < 9; i++) {

        if (board[i] == 0) {

            board[i] = player;
            int thisScore = -minimax(board, player * -1);

            if (thisScore > score) {
                score = thisScore;
                move = i;
            }
            board[i] = 0; //Reset board after try
        }
    }
    if (move == -1)
        return 0;

    return score;
}

int computerMove(int *board) {
    int move = -1;
    int score = -2;

    for (int i = 0; i < 9; ++i) {

        if (board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;

            if (tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    return move;
}

bool isBoardFull(const int *board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0)
            return false;
    }
    return true;
}

int getPlayerMove(const int *board) {
    int move;
    while (true) {
        cout << "Enter your move (1-9): ";
        cin >> move;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }

        if (move < 1 || move > 9) {
            cout << "Invalid move. Please enter a number between 1 and 9.\n";
            continue;
        }

        if (board[move - 1] != 0) {
            cout << "Illegal move. That position is already occupied.\n";
            continue;
        }

        break;
    }

    return move;
}

void playAgainstComputer() {
    int board[9] = {0};
    int moves = 0, k;

    cout << "\n~~~~~~~~~~~~~ Tic Tac Toe ~~~~~~~~~~~~~\n\n";
    cout << "You are 'X'. Make your move by entering the position number.\n";
    cout << "Here's the board layout:\n";
    draw_board(board);

    while (moves < 9) {
        int mv = getPlayerMove(board);
        board[mv - 1] = -1;
        moves++;

        cout << "\nBoard after your move:\n";
        draw_board(board);

        if (win(board) == 0) {
            if (isBoardFull(board))
                break;

            k = computerMove(board);
            board[k] = 1;
            cout << "\nBoard after computer's move:\n";
            draw_board(board);
            moves++;

            if (win(board) != 0)
                break;
        } else {
            break;
        }
    }

    switch (win(board)) {
        case 0:
            cout << "It's a draw!\n";
            break;
        case 1:
            cout << "You lose!\n";
            break;
        case -1:
            cout << "Congratulations! You beat the unbeatable computer!\n";
            break;
    }
}

void playAgainstHuman() {
    int board[9] = {0};
    int moves = 0;

    cout << "\n~~~~~~~~~~~~~ Tic Tac Toe ~~~~~~~~~~~~~\n\n";
    cout << "Player 1 (X) vs Player 2 (O)\n";
    cout << "Make your moves by entering the position numbers.\n";
    cout << "Here's the board layout:\n";
    draw_board(board);

    while (moves < 9) {
        int mv;
        int player = moves % 2 == 0 ? -1 : 1;
        cout << "\nPlayer " << (player == -1 ? "1" : "2") << "'s move: ";
        cin >> mv;

        if (cin.fail() || mv < 1 || mv > 9 || board[mv - 1] != 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid move. Please enter a number between 1 and 9.\n";
            continue;
        }

        board[mv - 1] = player;
        moves++;

        cout << "\nBoard after the move:\n";
        draw_board(board);

        if (win(board) != 0)
            break;

        if (isBoardFull(board))
            break;
    }

    switch (win(board)) {
        case 0:
            cout << "It's a draw!\n";
            break;
        case 1:
            cout << "Player 2 (O) wins!\n";
            break;
        case -1:
            cout << "Player 1 (X) wins!\n";
            break;
    }
}

int main() {
    int choice;
    do {
        cout << "~~~~~~~~~~~~~ Tic Tac Toe ~~~~~~~~~~~~~\n";
        cout << "Choose an option:\n";
        cout << "1. Play against the computer\n";
        cout << "2. Play against another human player\n";
        cout << "3. Quit\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                playAgainstComputer();
                break;
            case 2:
                playAgainstHuman();
                break;
            case 3:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }

        cout << endl;
    } while (choice != 3);

    return 0;
}



