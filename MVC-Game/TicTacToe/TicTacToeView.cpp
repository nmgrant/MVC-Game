#include <iostream>
#include "TicTacToeView.h"

using namespace std;

// Prints the TicTacToe board and its game state
void TicTacToeView::PrintBoard(std::ostream &s) const {
	cout << endl;
	// Prints column number
	cout << "- 0 1 2 " << endl;
	
	// For every (row, col), print 'X' if tile belongs to Player X,
	// 'O' if tile belongs to Player O, or '.' if tile is empty
	for (int r = 0; r < TTT_BOARD_SIZE; r++) {
		cout << r << " ";
		for (int c = 0; c < TTT_BOARD_SIZE; c++) {
			if (mTicTacToeBoard->m_board_[r][c] == TicTacToeBoard::Player::X) {
				cout << "X ";
			}
			else if (mTicTacToeBoard->m_board_[r][c] == TicTacToeBoard::Player::O) {
				cout << "O ";
			}
			else {
				cout << ". ";
			}
		}
		cout << endl;
	}
	cout << endl;
}