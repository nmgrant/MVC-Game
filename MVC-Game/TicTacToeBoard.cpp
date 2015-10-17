#include <vector>
#include "TicTacToeBoard.h"

TicTacToeBoard::TicTacToeBoard() : GameBoard() {
	for (int i = 0; i < TTT_BOARD_SIZE; i++) {
		for (int j = 0; j < TTT_BOARD_SIZE; j++) {
			mBoard[i][j] = EMPTY;	
		}
	}
}

bool TicTacToeBoard::hasWon(int row, int col) {
	//check for row victory
	for (int i = 0; i < TTT_BOARD_SIZE; i++) {
		if (mBoard[row][i] != mNextPlayer) {
				break;
		}
		if (i == TTT_BOARD_SIZE - 1) {
			return true;
		}
	}
	
	//check for column victory
	for (int i = 0; i < TTT_BOARD_SIZE; i++) {
		if (mBoard[i][col] != mNextPlayer) {
			break;
		}
		if (i == TTT_BOARD_SIZE - 1) {
			return true;
		}
	}

	//check for diagonal/anti-diagonal victory
	if (row == col) {
		//diagonal victory
		for (int i = 0; i < TTT_BOARD_SIZE; i++) {
			if (mBoard[i][i] != mNextPlayer) {
				break;
			}
			if (i == (TTT_BOARD_SIZE - 1)) {
				return true;
			}
		}
		//anti-diagonal victory		
		for (int i = 0; i < TTT_BOARD_SIZE; i++) {
			if (mBoard[i][(TTT_BOARD_SIZE - 1) - i] != mNextPlayer) {
				break;
			}
			if (i == (TTT_BOARD_SIZE - 1)) {
				return true;
			}
		}
	}

	return false;
}

void TicTacToeBoard::ApplyMove(GameMove *move) {
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(move);
	if (m == nullptr) {
		throw TicTacToeException("Tried to apply a non-TicTacToeMove");
	}
	mHistory.push_back(move);
	
	mBoard[m->mRow][m->mCol] = mNextPlayer;
	
	if (hasWon(m->mRow,m->mCol)) {
		mValue += mNextPlayer;
	}

	(mNextPlayer == O) ? mNextPlayer = X : mNextPlayer = O;
}

void TicTacToeBoard::GetPossibleMoves(std::vector<GameMove*> *list) const {
	for (int i = 0; i < TTT_BOARD_SIZE; i++) {
		for (int j = 0; j < TTT_BOARD_SIZE; j++) {
			if (mBoard[i][j] == EMPTY) {
				TicTacToeMove *move = dynamic_cast<TicTacToeMove*>(CreateMove());
				move->mRow = i;
				move->mCol = j;
				list->push_back(move);
			}
		}
	}
}

void TicTacToeBoard::UndoLastMove() {
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(mHistory.back());
	mBoard[m->mRow][m->mCol] = 0;
	mNextPlayer = -mNextPlayer;
	delete mHistory.back();
	mHistory.pop_back();
}