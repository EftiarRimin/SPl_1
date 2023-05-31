#include <iostream>
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

bool isBoardFull(const int *board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0)
            return false;
    }
    return true;
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


// Function to receive the board array from the server
void receiveBoard(int serverSocket, int* board) {
   // Receive the board size from the server
    uint32_t networkSize;
    int bytesReceived = recv(serverSocket, &networkSize, sizeof(networkSize), 0);
    if(bytesReceived < 0){
        cerr << "\nError in receiving network size" << endl;
    }
    
    // Convert the board size from network byte order to host byte order
    size_t boardSize = ntohl(networkSize);
    
    // Receive the board data from the server
    int response = recv(serverSocket, board, boardSize, 0);
    if( response < 0 ) {
        cerr << "\nError receiving board state" << endl;
    }
}



void playWithTwoPlayers(){
    //create client socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        cerr << "Error in creating client socket" << endl;
        return;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    //connect request to the server socket
    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        cerr << "Error in connecting to server" << endl;
        return;
    }

    //receive the name the client player
    char player;
    int bytesReceived = recv(clientSocket, &player, sizeof(char), 0);
    if (bytesReceived < 0) {
        cerr << "Error in receiving player information from server" << endl;
        return;
    }

    cout << "You are Player " << player << endl;

    while(true){
        int board[9] = {1};
        int moves = 0;

        while(true){
            //receive current board state
            receiveBoard(clientSocket,board);

            cout << "Current Board State: " << endl;
            draw_board(board);

            char current_player;
            //receive current player
            int bytesReceived2 = recv(clientSocket , &current_player, sizeof(char), 0);
            if(bytesReceived2 < 0) {
                cerr << "Error in receiving current player from server" << endl;
            }

            //if current palyer then send player move or wait for the other player
            if(current_player == player){
                int move = getPlayerMove(board);
                board[move-1] = (player == 'X') ? -1 : 1;
                int bytesSent = send(clientSocket, &move, sizeof(int), 0);
                if (bytesSent < 0) {
                    cerr << "Error in sending move to server" << endl;
                    return;
                }
            }else{
                cout << "Waiting for other player's move.." << endl;
                receiveBoard(clientSocket, board);
            }

            if (win(board) !=0) {
                draw_board(board);
                cout << "Player " << current_player << " wins!" << endl;
                break;
            } else if (isBoardFull(board)) {
                draw_board(board);
                cout << "It's a tie!" << endl;
                break;
            }
        }

        char playAgain;
        int bytesReceived = recv(clientSocket, &playAgain, sizeof(char), 0);
        if (bytesReceived < 0) {
            cerr << "Error in receiving play again information from server" << endl;
            return;
        }

        if (playAgain != 'Y' && playAgain != 'y') {
            break;
        }

    }
    close(clientSocket);
}

int main(){
    playWithTwoPlayers();
}