#include <iostream>
#include "ConnectFourView.h"

using namespace std;

void ConnectFourView::PrintBoard(std::ostream &s) const {
	cout << endl;
	cout << "  A B C D E F G " << endl;
	
	for (int r = 0; r < CF_ROWS; r++) {
		cout << "  ";
		for (int c = 0; c < CF_COLS; c++) {
			if (mConnectFourBoard->mBoard[r][c] == 
			 ConnectFourBoard::Player::YELLOW) {
				cout << "Y ";
			}
			else if (mConnectFourBoard->mBoard[r][c] == 
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