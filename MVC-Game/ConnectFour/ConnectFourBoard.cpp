#include <vector>
#include "ConnectFourBoard.h"

ConnectFourBoard::ConnectFourBoard() : GameBoard() {
	for (int i = 0; i < CF_ROWS; i++) {
		for (int j = 0; j < CF_COLS; j++) {
			m_board_[i][j] = EMPTY;
		}
	}
}

// Determines if there exists a winner from a specific row and column
bool ConnectFourBoard::hasWon(int row, int col) {

	// Looks for four straight chips of the same color
	// in any direction from the given chip by using row and column 
	// differences between -1 and 1.
	for (int rD = -1; rD <= 1; rD++) {
		for (int cD = -1; cD <= 1; cD++) {

			int r = row;
			int c = col;
			int matched = 1;
			
			// Applies ConnectFour algorithm unless row and column
			// difference is (0, 0)
			if (rD != 0 || cD != 0) {

				// Keep checking row/column using row and column
				// difference until the chip in current slot doesn't
				// match that of the given row/column. Increments matched amount
				// each time
				while (InBounds(r + rD, c + cD) &&
					(m_board_[r + rD][c + cD] == m_next_player_)) {
					r += rD;
					c += cD;
					matched++;
				}

				// If a row/column/diagonal of 4 was found, return true,
				// else keep searching
				if (matched == 4) {
					return true;
				}
			}
		}
	}
	// No row/column/diagonal of 4 was found
	return false;
}

// Applies the user's given move
void ConnectFourBoard::ApplyMove(GameMove *move) {
	// Cast given GameMove to ConnectFourMove
	ConnectFourMove *m = dynamic_cast<ConnectFourMove*>(move);

	// Exception handling for null moves
	if (m == nullptr) {
		throw ConnectFourException("Tried to apply a non-ConnectFourMove");
	}

	// Places the move into move history
	m_history_.push_back(move);

	// Gets desired column
	int col = m->m_col_;
	int i = -1;

	// Looks for open row in column
	while (m_board_[i + 1][col] == 0 && i < CF_ROWS - 1) {
		i++;
	}

	// Sets the move's row to found open row
	m->m_row_ = i;

	// Set the (row, column) to player's color
	m_board_[m->m_row_][m->m_col_] = m_next_player_;

	// Check if the move won
	if (hasWon(m->m_row_, m->m_col_)) {
		m_value_ += m_next_player_;
	}

	// Sets the next player
	(m_next_player_ == RED) ? m_next_player_ = YELLOW : m_next_player_ = RED;
}


// Finds all columns with an empty space
void ConnectFourBoard::GetPossibleMoves(std::vector<GameMove*> *list) const {
	// Iterate through each column
	for (int i = 0; i < CF_COLS; i++) {
		// If the first row is empty, add it to the possible moves
		if (m_board_[0][i] == EMPTY) {
			ConnectFourMove *move = dynamic_cast<ConnectFourMove*>(CreateMove());
			move->m_col_ = i;
			move->m_row_ = 0;
			list->push_back(move);
		}
	}
}

// Removes the last move played from the list and sets that moves row and column to 0
void ConnectFourBoard::UndoLastMove() {
	ConnectFourMove *m = dynamic_cast<ConnectFourMove*>(m_history_.back());
	m_board_[m->m_row_][m->m_col_] = 0;
	m_next_player_ = -m_next_player_;
	delete m_history_.back();
	m_history_.pop_back();
}