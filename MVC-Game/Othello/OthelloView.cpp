#include <iostream>
#include "OthelloView.h"

using namespace std;

// Prints the board to console with current game state
void OthelloView::PrintBoard(std::ostream &s) const {
	cout << endl;

	// Represents the column number
	cout << "- 0 1 2 3 4 5 6 7" << endl;

	// For every (row, col), print a 'B' if that tile belongs to the Black player,
	// 'W' if that tile belongs to the White player, or '.' if it is empty
	for (int r = 0; r < BOARD_SIZE; r++) {
		cout << r << " ";
		for (int c = 0; c < BOARD_SIZE; c++) {
			if (mOthelloBoard->m_board_[r][c] == OthelloBoard::Player::BLACK) {
				cout << "B ";
			}
			else if (mOthelloBoard->m_board_[r][c] == OthelloBoard::Player::WHITE) {
				cout << "W ";
			}
			else {
				cout << ". ";
			}
		}
		cout << endl;
	}
	cout << endl;
}