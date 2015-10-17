#include <iostream>
#include "OthelloView.h"

using namespace std;

void OthelloView::PrintBoard(std::ostream &s) const {
	cout << endl;
	cout << "- 0 1 2 3 4 5 6 7" << endl;

	for (int r = 0; r < BOARD_SIZE; r++) {
		cout << r << " ";
		for (int c = 0; c < BOARD_SIZE; c++) {
			if (mOthelloBoard->mBoard[r][c] == OthelloBoard::Player::BLACK) {
				cout << "B ";
			}
			else if (mOthelloBoard->mBoard[r][c] == OthelloBoard::Player::WHITE) {
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