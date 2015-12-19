#include <iostream>
#include "ConnectFourView.h"

using namespace std;

// Prints the board for ConnectFour
void ConnectFourView::PrintBoard(std::ostream &s) const {
	cout << endl;

	// Prints character value representing each column
	cout << "  A B C D E F G " << endl;
	
	// For every (row, column), print a 'Y' if the chip is Yellow, an 'R' if the chip is Red
	// and '.' if no chip has been placed there
	for (int r = 0; r < CF_ROWS; r++) {
		cout << "  ";
		for (int c = 0; c < CF_COLS; c++) {
			if (mConnectFourBoard->m_board_[r][c] == 
			 ConnectFourBoard::Player::YELLOW) {
				cout << "Y ";
			}
			else if (mConnectFourBoard->m_board_[r][c] == 
			 ConnectFourBoard::Player::RED) {
				cout << "R ";
			}
			else {
				cout << ". ";
			}
		}
		cout << endl;
	}
	cout << endl;
}