#include "GameExceptions.h"
#include "OthelloBoard.h"
#include "OthelloMove.h"
#include "OthelloView.h"
#include "TicTacToeBoard.h"
#include "TicTacToeView.h"
#include "TicTacToeMove.h"
#include "GameBoard.h"
#include "GameView.h"
#include "GameMove.h"
#include "ConnectFourBoard.h"
#include "ConnectFourMove.h"
#include "ConnectFourView.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

	// Initialize variables for game coordination

	// Initialize generic GameBoard to nullptr
	GameBoard *board = nullptr;

	// Initialize generic GameView to nullptr
	GameView *game_view = nullptr; 

	// Used for player's move input
	string user_input; 

	// Tracks possible moves
	vector<GameMove*> possible_moves;

	// Used to determine when the user wishes to exit
	bool exit = false;

	// Used to determine which game a user would like to play
	string choice;

	// Runs program until user wishes to exit
	do {
		// Set initial bool values for determining what user would like to do
		bool quit = false;
		bool valid = true;

		// Loops until user chooses valid choice
		do {
			cout << "\nWhat game do you want to play? \n1) Othello  "
			 << "\n2) Tic Tac Toe \n3) Connect Four \n4) Exit" << endl;

			getline(cin,choice);

			// Parses user's input for choice with validation and 
			// sets the board and view variables appropriate to selected game
			if (choice.find("1") == 0) {
				board = new OthelloBoard();
				game_view = new OthelloView(board);
			}
			else if (choice.find("2") == 0) {
				board = new TicTacToeBoard();
				game_view = new TicTacToeView(board);
			}
			else if (choice.find("3")  == 0) {
				board = new ConnectFourBoard();
				game_view = new ConnectFourView(board);
			}
			else if (choice.find("4") == 0) {
				exit = true;
			}
			else {
				cout << "Invalid choice." << endl;
				valid = false;
			}

		} while (!valid);
		
		// Exit program loop if user chose to exit
		if (exit) {
			break;
		}

		// Otherwise, loop until a player has won
		do {
			// Print the game view
			cout << *game_view << endl;
		
			char current_player = board->GetNextPlayer();
			cout << board->GetPlayerString(current_player) << "'s move." << endl;

			board->GetPossibleMoves(&possible_moves);

			cout << endl << "Possible moves: " << endl;
			for (GameMove *move : possible_moves) {
				cout << move->operator std::string() << " ";
			}

			cout << endl << endl;
			for (GameMove *m : possible_moves) {
				delete m;
			}
			possible_moves.clear();

			do {
				cout << endl << "Enter a command (move *possible move*): ";

				getline(cin,user_input);

				if (user_input.find("showValue") == 0) {
					cout << endl << "Board value: " << board->GetValue() << endl;
				}

				else if (user_input.find("showHistory") == 0) {
				
					cout << endl;
					auto hist = board->GetMoveHistory();
					char player = -current_player;

					for (auto itr = hist->rbegin(); itr != hist->rend(); itr++) {
					
						cout << board->GetPlayerString(player)
						 << ": " << (*itr)->operator std::string() << endl; 

						player = -player;

					}

				}

				else if (user_input.find("move") == 0) {
				
					GameMove *move = board->CreateMove();
					bool isValid = false;

					try {

						*move = user_input.substr(5, user_input.size() - 5);

						board->GetPossibleMoves(&possible_moves);

						for (GameMove *m : possible_moves) {
							if ( *move == *m ) {
								isValid = true;
								break;
							}
						}

						cout << endl << endl;
						for (GameMove *m : possible_moves) {
							delete m;
						}
						possible_moves.clear();
	
						if (isValid) {
							board->ApplyMove(move);
							break;
						}
						else {
							cout << endl << "Not a valid move." << endl;
							delete move;
						}

					} catch (GameException& e) {
						cout << endl << e.what() << endl << endl;
						delete move;
					}

				}

				else if (user_input.find("undo") == 0) {
				
					istringstream iss;
					int undoMoves;

					iss.str(user_input.substr(5, user_input.size() - 5));
					iss >> undoMoves;

					while (undoMoves != 0 && board->GetMoveCount() != 0) {
						board->UndoLastMove();
						undoMoves--;
					}

					break;

				}

				else if (user_input.find("quit") == 0) {
					quit = true;
				}

				else {
					cout << endl << "Invalid input.";
				}

			} while (!quit);

		} while (!board->IsFinished() && !quit); 

		cout << *game_view << endl;

		int value = board->GetValue();
		(value > 0) ? (cout << endl << "Game over. " << 
		 board->GetPlayerString(1) << " wins!\n" << endl) :
		 (value < 0) ? (cout << endl << "Game over. " << 
		 board->GetPlayerString(-1) << " wins!\n" << endl) :
		 (cout << endl << "Game over. We have a tie!\n" << endl);

		delete board;
		delete game_view;
	} while (!exit);
}