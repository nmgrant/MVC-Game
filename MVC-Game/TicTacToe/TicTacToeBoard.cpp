#include <vector>
#include "TicTacToeBoard.h"

// Constructor for a TicTacToeBoard and its initial state
TicTacToeBoard::TicTacToeBoard() : GameBoard() {
	for (int i = 0; i < TTT_BOARD_SIZE; i++) {
		for (int j = 0; j < TTT_BOARD_SIZE; j++) {
			m_board_[i][j] = EMPTY;	
		}
	}
}

// Checks if a player has won by checking each condition
bool TicTacToeBoard::hasWon(int row, int col) {
	//check for row victory
	for (int i = 0; i < TTT_BOARD_SIZE; i++) {
		if (m_board_[row][i] != m_next_player_) {
				break;
		}
		if (i == TTT_BOARD_SIZE - 1) {
			return true;
		}
	}
	
	//check for column victory
	for (int i = 0; i < TTT_BOARD_SIZE; i++) {
		if (m_board_[i][col] != m_next_player_) {
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
			if (m_board_[i][i] != m_next_player_) {
				break;
			}
			if (i == (TTT_BOARD_SIZE - 1)) {
				return true;
			}
		}
		//anti-diagonal victory		
		for (int i = 0; i < TTT_BOARD_SIZE; i++) {
			if (m_board_[i][(TTT_BOARD_SIZE - 1) - i] != m_next_player_) {
				break;
			}
			if (i == (TTT_BOARD_SIZE - 1)) {
				return true;
			}
		}
	}

	return false;
}

// Applies the user's givne move
void TicTacToeBoard::ApplyMove(GameMove *move) {

	// Casts the GameMove to TicTacToeMove
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(move);

	// If the move is invalid, throw exception
	if (m == nullptr) {
		throw TicTacToeException("Tried to apply a non-TicTacToeMove");
	}

	// Otherwise, put the move into move history
	m_history_.push_back(move);
	
	// Set the (row, col) to the player 
	m_board_[m->m_row_][m->m_col_] = m_next_player_;
	
	// Check if the player has won
	if (hasWon(m->m_row_,m->m_col_)) {
		m_value_ += m_next_player_;
	}

	// Change player
	(m_next_player_ == O) ? m_next_player_ = X : m_next_player_ = O;
}

// Gets all possible moves by searching for empty spaces
void TicTacToeBoard::GetPossibleMoves(std::vector<GameMove*> *list) const {
	for (int i = 0; i < TTT_BOARD_SIZE; i++) {
		for (int j = 0; j < TTT_BOARD_SIZE; j++) {
			if (m_board_[i][j] == EMPTY) {
				TicTacToeMove *move = dynamic_cast<TicTacToeMove*>(CreateMove());
				move->m_row_ = i;
				move->m_col_ = j;
				list->push_back(move);
			}
		}
	}
}

// Undoes the last move
void TicTacToeBoard::UndoLastMove() {
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(m_history_.back());

	// Set last move to empty
	m_board_[m->m_row_][m->m_col_] = 0;

	// Change to previous player
	m_next_player_ = -m_next_player_;

	// Remove the move from move history
	delete m_history_.back();
	m_history_.pop_back();
}