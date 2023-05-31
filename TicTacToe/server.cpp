#include <iostream>
#include <limits>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

const int PORT = 3230;

void draw_board(int *b) {
    int k = 0;
    cout << endl;
    cout << "----++---++----" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "| ";
            if (b[k] == 0) {
                cout << k + 1 << " |";
            } else {
                if (b[k] == -1) {
                    std::cout << "\033[31m";// Change the font color to red
                    cout << "X ";
                    std::cout << "\033[0m"; //set to default color
                    cout << "|";
                } else {
                    std::cout << "\033[32m";//green color
                    cout << "O ";
                    std::cout << "\033[0m"; //set to default color
                    cout << "|";
                }
            }
            k++;
        }
        cout << "\n----++---++----" << endl;
    }
    cout << endl;
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


// Function to send the board array to the client
void sendCurrentBoard(int clientSocket, const int* board) {
    // Get the size of the board array
    size_t boardSize = 9 * sizeof(int);
    // Convert the board size to network byte order
    uint32_t networkSize = htonl(boardSize);
    
    // Send the board size to the client
    int sizeResponse = send(clientSocket, &networkSize, sizeof(networkSize), 0);
    if( sizeResponse < 0) {
        cerr << "\nError sending board size to client" << endl;
    }
    
    // Send the board data to the client
    int boardResponse = send(clientSocket, board, boardSize, 0);
    if(boardResponse < 0){
        cerr << "\nError sending board data" << endl;
    }
}


char getPlayAgain(){
    char playAgain;
    while(true)
    {
        cout << "Do you want to play again? (Y/N): ";
        cin >> playAgain;
        if(playAgain!='Y' && playAgain!='y' && playAgain!='n' && playAgain!='N')
        {
            cout<< "Invalid input..Please enter Y/N or y/n" <<endl;
        }
        else break;
    }
    return playAgain;
}


void playWithTwoPlayers(){
    //create server socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Error in creating server socket" << endl;
        return;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // bind server socket
    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        cerr << "Error in binding socket to IP/Port" << endl;
        return;
    }

    //listen for clients
    if (listen(serverSocket, 2) == -1) {
        cerr << "Error in listening for connections" << endl;
        return;
    }
    cout << "Waiting for players to connect..." << endl;

    //accept client-1 connection request
    int clientSocket1 = accept(serverSocket, nullptr, nullptr);
    if (clientSocket1 == -1) {
        cerr << "Error in accepting client 1 connection" << endl;
        return;
    }

    //send player name for client-1
    char player1 = 'X';
    int bytesSent1 = send(clientSocket1, &player1, sizeof(char), 0);
    if (bytesSent1 < 0) {
        cerr << "Error in sending player information to client 1" << endl;
        return;
    }

    //accept client-2 connection request
    int clientSocket2 = accept(serverSocket, nullptr, nullptr);
    if (clientSocket2 == -1) {
        cerr << "Error in accepting client 2 connection" << endl;
        return;
    }
    
    //send player name for client-2
    char player2 = 'O';
    int bytesSent2 = send(clientSocket2, &player2, sizeof(char), 0);
    if (bytesSent2 < 0) {
        cerr << "Error in sending player information to client 2....." << endl;
        return;
    }
    
    cout << "Two players connected. Starting the game..." << endl;

    char current_player = player1;

    while(true){
        int board[9] = {0};
        int moves = 0;

        while(true){
            cout << "Current state of Board: " << endl;
            draw_board(board);

            sendCurrentBoard(clientSocket1,board);
            sendCurrentBoard(clientSocket2,board);
            
            //send Current player to player-1
            int bytesSent3 = send(clientSocket1 , &current_player, sizeof(char), 0);
            if(bytesSent3 < 0) {
                cerr << "Error in sending current player to client 1" << endl;
            }
            //send Current player to player-2
            int bytesSent4 = send(clientSocket2 , &current_player, sizeof(char), 0);
            if(bytesSent4 < 0) {
                cerr << "Error in sending current player to client 2" << endl;
            }

            if(current_player == player1){
                int move;
                int byteReceived = recv(clientSocket1,&move,sizeof(int),0);
                if(byteReceived < 0) {
                    cout << "Error receiving move from player-1";
                }
                board[move-1] = -1;
                sendCurrentBoard(clientSocket2,board);
                moves++;
            }else{
                int move;
                int byteReceived = recv(clientSocket2,&move,sizeof(int),0);
                if(byteReceived < 0) {
                    cout << "Error receiving move from player-2";
                }
                board[move-1] = 1;
                sendCurrentBoard(clientSocket1,board);
                moves++;
            }

            if (win(board) !=0) {
                draw_board(board);
                cout << "Player " << current_player << " wins!" << endl;
                break;
            } else if (isBoardFull(board)) {
                draw_board(board);
                cout << "It's a draw!" << endl;
                break;
            }

            current_player = (current_player == player1) ? player2 : player1;
        }

        char playAgain = getPlayAgain();

        int bytesSent = send(clientSocket1, &playAgain, sizeof(char), 0);
        if (bytesSent < 0) {
            cerr << "Error in sending play again information to client 1" << endl;
            return;
        }

        bytesSent = send(clientSocket2, &playAgain, sizeof(char), 0);
        if (bytesSent < 0) {
            cerr << "Error in sending play again information to client 2" << endl;
            return;
        }

        if (playAgain != 'Y' && playAgain != 'y') {
            break;
        }
    }
    close(clientSocket1);
    close(clientSocket2);
    close(serverSocket);

}



int main() {
    int choice;
    do {
        cout << "~~~~~~~~~~~~~ Tic Tac Toe ~~~~~~~~~~~~~\n";
        cout << "Choose an option:\n";
        cout << "1. One player(with computer)\n";
        cout << "2. Two player with same device\n";
        cout << "3. Two player with remote device\n";
        cout << "4. Quit\n";
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
                playWithTwoPlayers();
                break;
            case 4:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }

        cout << endl;
    } while (choice != 4);

    return 0;
}
