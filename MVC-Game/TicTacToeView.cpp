#include <iostream>
#include "TicTacToeView.h"

using namespace std;

void TicTacToeView::PrintBoard(std::ostream &s) const {
	cout << endl;
	cout << "- 0 1 2 " << endl;
	
	for (int r = 0; r < TTT_BOARD_SIZE; r++) {
		cout << r << " ";
		for (int c = 0; c < TTT_BOARD_SIZE; c++) {
			if (mTicTacToeBoard->mBoard[r][c] == TicTacToeBoard::Player::X) {
				cout << "X ";
			}
			else if (mTicTacToeBoard->mBoard[r][c] == TicTacToeBoard::Player::O) {
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