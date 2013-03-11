/**
 * author: Henry West (with the antics of Eric Manley for game commentary)
 * date: 27 February, 2013
 * description: A simple game of Tic Tac Toe with cheeky AI to keep the user entertained
 * proposed score: [50/50] (unless the AI isn't perfect, it may occasionally forget to take good spots,
 * but I think I fixed that)
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * parameters: none
 * return: none
 * i/o: outputs instructions
 * print_instructions prints the game instructions to the console
 **/
void print_instructions() {
    cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
    cout << "--where human brain is pit against silicon processor\n\n";

    cout << "Make your move known by entering a number, 0 - 8.  The number\n";
    cout << "corresponds to the desired board position, as illustrated:\n\n";

    cout << "       0 | 1 | 2\n";
    cout << "       ---------\n";
    cout << "       3 | 4 | 5\n";
    cout << "       ---------\n";
    cout << "       6 | 7 | 8\n\n";

    cout << "Prepare yourself, human.  The battle is about to begin.\n\n";
}
/**
 *parameters: board - array containing game board
 * return: none
 * i/o: none 
 * initialize_board sets all elements of board to a space
 */
void initialize_board(char * board) {
    for (int i = 0; i < 9; i++) {
        *(board + i) = ' ';
    }
}
/**
 * parameters: board - array containing game board
 * return: none
 * i/o: outputs game board
 * display_board prints the game board to the console
 */
void display_board(char * board) {
    for (int i = 0; i < 9; i++) {
        if (i%3 == 0) {
            cout << " " << *(board + i) << " | ";
        }
        else if (i%3 == 1) {
            cout << *(board + i) << " | ";
        }
        else if (i%3 == 2) {
            cout << *(board + i);
            if (i != 8) {
                cout << "\n-----------\n";
            }
        }
    }
    cout << endl;
}
/**
 * parameters:
 * board - array containing game board
 * position - proposed position for a move
 * return: bool
 * i/o: none
 * check_if_legal verifies that a move is allowed and if so, returns true
 */
bool check_if_legal(char * board, int position) {
    if (*(board + position) == ' ') {
        return true;
    }
    else {
        return false;
    }
}
/**
 * parameters: board - arrray containing the game board
 * return: char
 * i/o: none
 * check_winner determines the winner of the game (if there is one)
 */
char check_winner(char * board) {
    bool continue_game = false;
    if (*board == *(board + 4) && *board == *(board + 8)) {
        return *board;
    }
    else if (*(board + 2) == *(board + 4) && *(board + 4) == *(board + 6)) {
        return *(board + 2);
    }
    for (int i = 0; i < 6; i += 3) {
        if (*(board + i) == *(board + i + 1) && *(board + i) == *(board + i + 2)) {
            return *(board + i);
        }
    }
    for (int i = 0; i < 3; i++) {
        if (*(board + i) == *(board + i + 3) && *(board + i) == *(board + i + 6)) {
            return *(board + i);
        }
    }
    for (int i = 0; i < 9; i++) {
        if (check_if_legal(board, i)) {
            continue_game = true;
            
        }
        if (i == 8 && !continue_game) {
            return '_';
        }
    }
    return ' ';
}
/**
 * parameters: board - array containing game board
 * return: none
 * i/o: prompts user for move
 * human_move allows the user to make a move, will also redirect proposed move to check_if_legal()
 */
void human_move(char * board) {
    bool legal_move = false;
    int test_move;
    while(!legal_move)
    {
        cout << "Enter a move (integer 0-8) >>> ";
        cin >> test_move;
        if( check_if_legal(board, test_move) )
        {
            cout << "I shall take square number " << test_move << endl;
            *(board+test_move) = 'X'; //This is the space corresponding to
                                     //the generated move in the board array
            legal_move = true; //allows us to break out of the loop
        }
    }
}
/**
 * parameters:
 * board - array containing game board
 * turn - integer value representing numerical turn of computer
 * return: none
 * i/o: informs user of move
 * comp_move contains all of the AI in the game, judged at about the same skill level as me (not terribly impressive)
 */
void comp_move(char * board, int turn) {
    bool legal_move = false;
    while(!legal_move) {
        //First turn for AI
        if (turn == 0) {
            //Take center space
            if( check_if_legal(board, 4) ) {
                cout << "I shall take square number " << 4 << endl;
                *(board + 4) = 'O';
                legal_move = true;
            }
            //take upper left space
            else if (check_if_legal(board, 0)) {
                cout << "I shall take square number " << 0 << endl;
                *(board+0) = 'O';
                legal_move = true;
            }
        }
        //Second AI turn
        else if (turn == 1) {
            //check for remaining corners of board
            if (check_if_legal(board, 2)) {
                    cout << "I shall take square number " << 2 << endl;
                    *(board+2) = 'O';
                    legal_move = true;
            }
            else if (check_if_legal(board, 6)) {
                    cout << "I shall take square number " << 6 << endl;
                    *(board+6) = 'O';
                    legal_move = true;
            }
            else if (check_if_legal(board, 8)) {
                    cout << "I shall take square number " << 8 << endl;
                    *(board+8) = 'O';
                    legal_move = true;
            }
            //see if human player has two in a row anywhere
            else {
                //checks for diagonal
                if (*board == *(board + 4) || *board == *(board + 8)) {
                    if (check_if_legal(board, 8)) {
                        cout << "I shall take square number " << 8 << endl;
                        *(board+8) = 'O';
                        legal_move = true;
                    }
                }
                //check for other diagonal
                else if (*(board + 2) == *(board + 4) || *(board + 4) == *(board + 6)) {
                    if (check_if_legal(board, 2)) {
                        cout << "I shall take square number " << 2 << endl;
                        *(board + 2) = 'O';
                        legal_move = true;
                    }
                    else if (check_if_legal(board, 6)) {
                        cout << "I shall take square number " << 6 << endl;
                        *(board + 6) = 'O';
                        legal_move = true;
                    }
                }
                //checks each row
                for (int i = 0; i < 6; i += 3) {
                    if (*(board + i) == *(board + i + 1) || *(board + i) == *(board + i + 2) || *(board + i + 2) == *(board + i + 1)) {
                        if (check_if_legal(board, i)) {
                            cout << "I shall take square number " << i << endl;
                            *(board + i) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 1))) {
                            cout << "I shall take square number " << (i + 1) << endl;
                            *(board + i + 1) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 2))) {
                            cout << "I shall take square number " << (i + 2) << endl;
                            *(board + i + 2) = 'O';
                            legal_move = true;
                            break;
                        }
                    }
                }
                //checks for columns
                for (int i = 0; i < 3; i++) {
                    if (*(board + i) == *(board + i + 3) || *(board + i) == *(board + i + 6) || *(board + i + 3) == *(board + i + 6)) {
                        if (check_if_legal(board, i)) {
                            cout << "I shall take square number " << i << endl;
                            *(board + i) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 3))) {
                            cout << "I shall take square number " << (i + 3) << endl;
                            *(board + i + 3) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 6))) {
                            cout << "I shall take square number " << (i + 6) << endl;
                            *(board + i + 6) = 'O';
                            legal_move = true;
                            break;
                        }
                    }
                }
            }
        }
        else if (turn == 2) {
            if (!legal_move) {
                if (*board == *(board + 4) || *board == *(board + 8)) {
                    if (check_if_legal(board, 8)) {
                        cout << "I shall take square number " << 8 << endl;
                        *(board+8) = 'O';
                        legal_move = true;
                    }
                    else if (check_if_legal(board, 4)) {
                        cout << "I shall take square number " << 4 << endl;
                        *(board+4) = 'O';
                        legal_move = true;
                    }
                }
            }
            if (*(board + 2) == *(board + 4) || *(board + 4) == *(board + 6)) {
                if (check_if_legal(board, 2)) {
                    cout << "I shall take square number " << 2 << endl;
                    *(board + 2) = 'O';
                    legal_move = true;
                }
                else if (check_if_legal(board, 6)) {
                    cout << "I shall take square number " << 6 << endl;
                    *(board + 6) = 'O';
                    legal_move = true;
                }
            }
            if (!legal_move) {
                for (int i = 0; i < 6; i += 3) {
                    if (*(board + i) == *(board + i + 1) || *(board + i) == *(board + i + 2) || *(board + i + 2) == *(board + i + 1)) {
                        if (check_if_legal(board, i)) {
                            cout << "I shall take square number " << i << endl;
                            *(board + i) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 1))) {
                            cout << "I shall take square number " << (i + 1) << endl;
                            *(board + i + 1) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 2))) {
                            cout << "I shall take square number " << (i + 2) << endl;
                            *(board + i + 2) = 'O';
                            legal_move = true;
                            break;
                        }
                    }
                }
            }
            if (!legal_move) {
                for (int i = 0; i < 3; i++) {
                    if (*(board + i) == *(board + i + 3) || *(board + i) == *(board + i + 6) || *(board + i + 3) == *(board + i + 6)) {
                        if (check_if_legal(board, i)) {
                            cout << "I shall take square number " << i << endl;
                            *(board + i) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 3))) {
                            cout << "I shall take square number " << (i + 3) << endl;
                            *(board + i + 3) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 6))) {
                            cout << "I shall take square number " << (i + 6) << endl;
                            *(board + i + 6) = 'O';
                            legal_move = true;
                            break;
                        }
                    }
                }
            }
        }
        else if (turn == 3) {
            if (*board == *(board + 4) || *board == *(board + 8)) {
                if (check_if_legal(board, 8)) {
                    cout << "I shall take square number " << 8 << endl;
                    *(board+8) = 'O';
                    legal_move = true;
                }
                else if (check_if_legal(board, 4)) {
                    cout << "I shall take square number " << 4 << endl;
                    *(board+4) = 'O';
                    legal_move = true;
                }
            }
            else if (*(board + 2) == *(board + 4) || *(board + 4) == *(board + 6)) {
                if (check_if_legal(board, 2)) {
                    cout << "I shall take square number " << 2 << endl;
                    *(board + 2) = 'O';
                    legal_move = true;
                }
                else if (check_if_legal(board, 6)) {
                    cout << "I shall take square number " << 6 << endl;
                    *(board + 6) = 'O';
                    legal_move = true;
                }
            }
            if (!legal_move) {
                for (int i = 0; i < 6; i += 3) {
                    if (*(board + i) == *(board + i + 1) || *(board + i) == *(board + i + 2) || *(board + i + 2) == *(board + i + 1)) {
                        if (check_if_legal(board, i)) {
                            cout << "I shall take square number " << i << endl;
                            *(board + i) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 1))) {
                            cout << "I shall take square number " << (i + 1) << endl;
                            *(board + i + 1) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 2))) {
                            cout << "I shall take square number " << (i + 2) << endl;
                            *(board + i + 2) = 'O';
                            legal_move = true;
                            break;
                        }
                    }
                }
            }
            if (!legal_move) {
                for (int i = 0; i < 3; i++) {
                    if (*(board + i) == *(board + i + 3) || *(board + i) == *(board + i + 6) || *(board + i + 3) == *(board + i + 6)) {
                        if (check_if_legal(board, i)) {
                            cout << "I shall take square number " << i << endl;
                            *(board + i) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 3))) {
                            cout << "I shall take square number " << (i + 3) << endl;
                            *(board + i + 3) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 6))) {
                            cout << "I shall take square number " << (i + 6) << endl;
                            *(board + i + 6) = 'O';
                            legal_move = true;
                            break;
                        }
                    }
                }
            }
        }
        else if (turn >= 4) {
            if (*board == *(board + 4) || *board == *(board + 8)) {
                if (check_if_legal(board, 8)) {
                    cout << "I shall take square number " << 8 << endl;
                    *(board+8) = 'O';
                    legal_move = true;
                }
                else if (check_if_legal(board, 4)) {
                    cout << "I shall take square number " << 4 << endl;
                    *(board+4) = 'O';
                    legal_move = true;
                }
            }
            else if (*(board + 2) == *(board + 4) || *(board + 4) == *(board + 6)) {
                if (check_if_legal(board, 2)) {
                    cout << "I shall take square number " << 2 << endl;
                    *(board + 2) = 'O';
                    legal_move = true;
                }
                else if (check_if_legal(board, 6)) {
                    cout << "I shall take square number " << 6 << endl;
                    *(board + 6) = 'O';
                    legal_move = true;
                }
            }
            else if (!legal_move) {
                for (int i = 0; i < 6; i += 3) {
                    if (*(board + i) == *(board + i + 1) || *(board + i) == *(board + i + 2) || *(board + i + 2) == *(board + i + 1)) {
                        if (check_if_legal(board, i)) {
                            cout << "I shall take square number " << i << endl;
                            *(board + i) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 1))) {
                            cout << "I shall take square number " << (i + 1) << endl;
                            *(board + i + 1) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 2))) {
                            cout << "I shall take square number " << (i + 2) << endl;
                            *(board + i + 2) = 'O';
                            legal_move = true;
                            break;
                        }
                    }
                }
            }
            else if (!legal_move) {
                for (int i = 0; i < 3; i++) {
                    if (*(board + i) == *(board + i + 3) || *(board + i) == *(board + i + 6) || *(board + i + 3) == *(board + i + 6)) {
                        if (check_if_legal(board, i)) {
                            cout << "I shall take square number " << i << endl;
                            *(board + i) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 3))) {
                            cout << "I shall take square number " << (i + 3) << endl;
                            *(board + i + 3) = 'O';
                            legal_move = true;
                            break;
                        }
                        else if (check_if_legal(board, (i + 6))) {
                            cout << "I shall take square number " << (i + 6) << endl;
                            *(board + i + 6) = 'O';
                            legal_move = true;
                            break;
                        }
                    }
                }
            }
            for (int i = 0; i < 9; i++) {
                if (check_if_legal(board, i)) {
                    cout << "I shall take square number " << i << endl;
                    *(board + i) = 'O';
                    legal_move = true;
                    break;
                }
            }
        }
    }
}
/**
 * parameters: winner - holds char value of the game winner, using a space if there is no winner
 * return: none
 * i/o: general info on winner
 * announce_winner prints the game winner to the console, or a tie in the event of a tie
 */
void announce_winner(char winner) {
    if (winner == 'O')
    {
        cout << winner << "'s won!\n";
        cout << "As I predicted, human, I am triumphant once more -- proof\n";
        cout << "that computers are superior to humans in all regards.\n";
    }

    else if (winner == 'X')
    {
        cout << winner << "'s won!\n";
        cout << "No, no!  It cannot be!  Somehow you tricked me, human.\n";
        cout << "But never again!  I, the computer, so swear it!\n";
    }

    else
    {
        cout << "It's a tie.\n";
        cout << "You were most lucky, human, and somehow managed to tie me.\n";
        cout << "Celebrate... for this is the best you will ever achieve.\n";
    }
}

/* main function
 parameters: none
 return: return of 0 to system on successful completion
 input/output: dialogue on who moves first in the Tic-Tac-Toe game
 
 This is the entry point of the program.
*/
int main() {
    //The Tic-Tac-Toe board - a 9 character array
    //Each character can be an X, O, or a space
    //The space represents an open space on the board
    char * game_board = new char[9];
    char response; //User's response
    char turn; //keeps track of who's turn it is
    //keeps track of how many moves the computer has made
    int turn_number = 0;
    //display initial board and game rules for user
    print_instructions();
    initialize_board(game_board); // fills the board with spaces


    //Let the user decide who goes first
    //Keep trying until they type correct input
    do {
        cout << "Do you want to go first? (y/n): ";
        cin >> response;
    } while (response != 'y' && response != 'n');

    if (response == 'y') {
        cout << "\nThen take the first move.  You will need it.\n";
        turn = 'X';
    }
    else {
        cout << "\nYour bravery will be your undoing... I will go first.\n";
        turn = 'O';
    }
    //The main game loop
    turn_number = 0;
    //display_board(game_board);
    // while there is no winner yet 
    while (check_winner(game_board) == ' ') {
        if (turn == 'X') {
            human_move(game_board);
            turn = 'O';
        }
        else {
            comp_move(game_board, turn_number); //computer's turn
            turn = 'X';
            turn_number++;
        }
        
        display_board(game_board);
        
        
    }

    //If we got here, it means the game is over
    //we'll announce the winner (or the tie)
    announce_winner(check_winner(game_board));


    return 0;
}



