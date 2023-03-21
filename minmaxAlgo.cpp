int evaluate(int board[][BOARD_SIZE]) {
    // Check rows for a win
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == 'X') {
                return 10;
            } else if (board[i][0] == 'O') {
                return -10;
            }
        }
    }

    // Check columns for a win
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            if (board[0][j] == 'X') {
                return 10;
            } else if (board[0][j] == 'O') {
                return -10;
            }
        }
    }
