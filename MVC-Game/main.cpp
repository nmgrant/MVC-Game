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
	GameBoard *board = nullptr;
	GameView *v = nullptr; 
	string userInput; 
	vector<GameMove*> possMoves; 
	bool exit = false;
	string choice;

	do {
		bool quit = false;
		bool valid = true;
		do {
			cout << "\nWhat game do you want to play? \n1) Othello  "
			 << "\n2) Tic Tac Toe \n3) Connect Four \n4) Exit" << endl;

			getline(cin,choice);

			if (choice.find("1") == 0) {
				board = new OthelloBoard();
				v = new OthelloView(board);
			}
			else if (choice.find("2") == 0) {
				board = new TicTacToeBoard();
				v = new TicTacToeView(board);
			}
			else if (choice.find("3")  == 0) {
				board = new ConnectFourBoard();
				v = new ConnectFourView(board);
			}
			else if (choice.find("4") == 0) {
				exit = true;
			}
			else {
				cout << "Invalid choice." << endl;
				valid = false;
			}

		} while (!valid);
		
		if (exit) {
			break;
		}

		do {
		
			cout << *v << endl;
		
			char currentPlayer = board->GetNextPlayer();
			cout << board->GetPlayerString(currentPlayer) << "'s move." << endl;

			board->GetPossibleMoves(&possMoves);

			cout << endl << "Possible moves: " << endl;
			for (GameMove *move : possMoves) {
				cout << move->operator std::string() << " ";
			}

			cout << endl << endl;
			for (GameMove *m : possMoves) {
				delete m;
			}
			possMoves.clear();

			do {
				cout << endl << "Enter a command (move *possible move*): ";

				getline(cin,userInput);

				if (userInput.find("showValue") == 0) {
					cout << endl << "Board value: " << board->GetValue() << endl;
				}

				else if (userInput.find("showHistory") == 0) {
				
					cout << endl;
					auto hist = board->GetMoveHistory();
					char player = -currentPlayer;

					for (auto itr = hist->rbegin(); itr != hist->rend(); itr++) {
					
						cout << board->GetPlayerString(player)
						 << ": " << (*itr)->operator std::string() << endl; 

						player = -player;

					}

				}

				else if (userInput.find("move") == 0) {
				
					GameMove *move = board->CreateMove();
					bool isValid = false;

					try {

						*move = userInput.substr(5, userInput.size() - 5);

						board->GetPossibleMoves(&possMoves);

						for (GameMove *m : possMoves) {
							if ( *move == *m ) {
								isValid = true;
								break;
							}
						}

						cout << endl << endl;
						for (GameMove *m : possMoves) {
							delete m;
						}
						possMoves.clear();
	
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

				else if (userInput.find("undo") == 0) {
				
					istringstream iss;
					int undoMoves;

					iss.str(userInput.substr(5, userInput.size() - 5));
					iss >> undoMoves;

					while (undoMoves != 0 && board->GetMoveCount() != 0) {
						board->UndoLastMove();
						undoMoves--;
					}

					break;

				}

				else if (userInput.find("quit") == 0) {
					quit = true;
				}

				else {
					cout << endl << "Invalid input.";
				}

			} while (!quit);

		} while (!board->IsFinished() && !quit); 

		cout << *v << endl;

		int value = board->GetValue();
		(value > 0) ? (cout << endl << "Game over. " << 
		 board->GetPlayerString(1) << " wins!\n" << endl) :
		 (value < 0) ? (cout << endl << "Game over. " << 
		 board->GetPlayerString(-1) << " wins!\n" << endl) :
		 (cout << endl << "Game over. We have a tie!\n" << endl);

		delete board;
		delete v;
	} while (!exit);
}