#include <vector>
#include "ConnectFourBoard.h"

ConnectFourBoard::ConnectFourBoard() : GameBoard() {
	for (int i = 0; i < CF_ROWS; i++) {
		for (int j = 0; j < CF_COLS; j++) {
			mBoard[i][j] = EMPTY;	
		}
	}
}

bool ConnectFourBoard::hasWon(int row, int col) {
	
	for (int rD = -1; rD <= 1; rD++) {
			for (int cD = -1; cD <= 1; cD++) {
				
				int r = row;
				int c = col;	
				int matched = 1;

				if (rD != 0 || cD != 0) {
					while (InBounds(r + rD, c + cD) && 
					 (mBoard[r + rD][c + cD] == mNextPlayer)) {
						r += rD; 
						c += cD;
						matched++;
					}

					if (matched == 4) {
						return true;
					}
					else {
						r = row;
						c = col;
						while (InBounds(r - rD, c - cD) && 
						 (mBoard[r - rD][c - cD] == mNextPlayer)) {
							r -= rD; 
							c -= cD;
							matched++;
						}
					}
					
					if (matched == 4) {
						return true;
					}
				}
			}
		}

	return false;
}

void ConnectFourBoard::ApplyMove(GameMove *move) {
	ConnectFourMove *m = dynamic_cast<ConnectFourMove*>(move);
	if (m == nullptr) {
		throw ConnectFourException("Tried to apply a non-ConnectFourMove");
	}
	mHistory.push_back(move);

	int col = m->mCol;
	int i = -1;
	
	while (mBoard[i + 1][col] == 0 && i < CF_ROWS - 1) {
		i++;
	}
	m->mRow = i;

	mBoard[m->mRow][m->mCol] = mNextPlayer;
	
	if (hasWon(m->mRow,m->mCol)) {
		mValue += mNextPlayer;
	}

	(mNextPlayer == RED) ? mNextPlayer = YELLOW : mNextPlayer = RED;
}

void ConnectFourBoard::GetPossibleMoves(std::vector<GameMove*> *list) const {
	for (int i = 0; i < CF_COLS; i++) {
		if (mBoard[0][i] == EMPTY) {
			ConnectFourMove *move = dynamic_cast<ConnectFourMove*>(CreateMove());
			move->mCol = i;
			move->mRow = 0;
			list->push_back(move);
		}
	}
}

void ConnectFourBoard::UndoLastMove() {
	ConnectFourMove *m = dynamic_cast<ConnectFourMove*>(mHistory.back());
	mBoard[m->mRow][m->mCol] = 0;
	mNextPlayer = -mNextPlayer;
	delete mHistory.back();
	mHistory.pop_back();
}