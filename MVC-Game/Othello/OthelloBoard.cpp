#include <vector>
#include "OthelloBoard.h"

// Constructor for an Othello Board with an initial game state
OthelloBoard::OthelloBoard() : GameBoard(), m_pass_count_(0) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			m_board_[i][j] = 0;	
		}
	}
	m_board_[3][3] = WHITE;
	m_board_[3][4] = BLACK;
	m_board_[4][3] = BLACK;
	m_board_[4][4] = WHITE;
 }

// Applies the user's move and flips any other pieces if necessary
 void OthelloBoard::ApplyMove(GameMove *move) {
	// Casts given move from GameMove to OthelloMove
	OthelloMove *m = dynamic_cast<OthelloMove*>(move);

	// Handles exceptions for invalid moves
	if (m == nullptr) {
		throw OthelloException("Tried to apply a non-OthelloMove");
	}

	// Place move into move history
	m_history_.push_back(move);

	// If the move is a pass, increment number of passes
	if ( m->IsPass() ) {
		m_pass_count_++;
	}

	// Else, apply the move
	else {
	
    // Reset pass count
	m_pass_count_ = 0;

	// Set the desired (row, col) to the player
	m_board_[m->m_row_][m->m_col_] = m_next_player_;

	// Add a point to the player's score
	m_value_ += m_next_player_;
		
		// Check all rows, columns, and diagonals around the given (row, col)
	    // to see if the played move "captures" any enemy pieces
		for (int rD = -1; rD <= 1; rD++) {
			for (int cD = -1; cD <= 1; cD++) {
				
				// Set initial values to check
				int r = m->m_row_;
				int c = m->m_col_;	
				int flipped = 0;

				// Keep searching in the (rD, cD) direction while enemy tiles are found
				while (InBounds(r + rD, c + cD) && (m_board_[r + rD][c + cD] != 0 && 
				 m_board_[r + rD][c + cD] != m_next_player_)) {
					r += rD; 
					c += cD;
				}

				// If the tile search ended on the player that made the move's tile,
				// the move has successfully captured pieces. Flip the captured pieces
				if (InBounds(r + rD, c+ cD) && m_board_[r + rD][c + cD] ==
				 m_next_player_ && (r != m->m_row_ || c != m->m_col_)) {

					// While the tile to flip is not the initial (row, column), keep flipping tiles
					while (r != m->m_row_ || c != m->m_col_) {
						m_board_[r][c] = m_next_player_;
						flipped++;
						
						// Add twice the value of the player to the game value (one for gaining a new piece, one for the other
						// player losing a piece)
						m_value_ += 2*m_next_player_; 
						r -= rD;
						c -= cD;
					}

					// Add the number of tiles flipped and the (rD, cD) direction to the FlipSet of the played move
					m->AddFlipSet(OthelloMove::FlipSet(flipped, rD, cD));
				}

			}
		}
	}

	// Change to next player
	(m_next_player_ == WHITE) ? m_next_player_ = BLACK : m_next_player_ = WHITE;
}


// In Othello, only moves that capture other pieces can be made
// This algorithm searches for moves that will capture enemy pieces
void OthelloBoard::GetPossibleMoves(std::vector<GameMove*> *list) const {
	// Looks through each (row, column)
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			
			// Initialize possibleMove value to false
			bool possibleMove = false;

			// If the current (row, col) is empty, apply the algorithm
			if ( m_board_[i][j] == 0 ) {
				
				// Apply the same algorithm used in ApplyMove, but just check
				// for possible move instead
				for (int rD = -1; rD <= 1; rD++) {
					for (int cD = -1; cD <= 1; cD++) {
						
						int row = i;
						int col = j;

						
						if (!(rD == 0 && cD == 0 )) {

							// Keep searching in the (rD, cD) direction while enemy tiles are found
							while (InBounds(row + rD, col + cD) && 
							 (m_board_[row + rD][col + cD] != 0 && 
							 m_board_[row + rD][col + cD] != m_next_player_)) {
								row += rD;
								col += cD;
							}

							// If the tile search ended on the player that made the move's tile,
							// the move has successfully captured pieces. Flip the captured pieces
							if (InBounds(row + rD, col + cD) && 
							 m_board_[row + rD][col + cD] == m_next_player_ 
							 && (row != i || col != j)) {
								possibleMove = true;
								break;		
							}

						}
					}

					// If the move is possible, add it to possibleMoves list and stop searching from 
					// that (row, col)
					if (possibleMove) {
						OthelloMove *move = dynamic_cast<OthelloMove*>(CreateMove());
						move->m_row_ = i;
						move->m_col_ = j;
						list->push_back(move);
						break;
					}

				}
			}
		}
	}

	// If no move exists in the possible moves, add a "pass" to possible moves
	if (list->size() == 0) {
		list->push_back(dynamic_cast<OthelloMove*>(CreateMove()));
	}

}

// Undoes the last move by using its FlipSet
void OthelloBoard::UndoLastMove() {
	// Gets the last move from move history
	OthelloMove *m = dynamic_cast<OthelloMove*>(m_history_.back());

	// If the move was a pass, decrement pass count
	if ( m->IsPass() ) {
		m_pass_count_--;
	}

	// Else, apply the undo algorithm
	else {

		// Get the FlipSet from the last move
		auto flips = m->m_flips_;

		// Lower the player owning that last move score by 1
		m_value_ -= m_board_[m->m_row_][m->m_col_];

		// Set the last move to empty
		m_board_[m->m_row_][m->m_col_] = 0;

		// For every flip in the move's flipset, apply the unflip algorithm
		for (auto itr = flips.begin(); itr != flips.end(); itr++) {
			
			// gets the number of enemy pieces flipped
			int flipped = itr->switched;

			int r = m->m_row_;
			int c = m->m_col_;

			// For every flip applied when the move was played, unflip the pieces flipped
			for (flipped; flipped != 0; flipped--) {
				r += itr->row_delta_;
				c += itr->col_delta_;
				// Flip the piece
				m_board_[r][c] = -m_board_[r][c];

				// Add twice the value of the unflipped piece to the game score
				// (One for the player losing a piece, another for the other player gaining a piece)
				m_value_ += 2*m_board_[r][c];
			}

		}

	}

	// Set player to previous
	m_next_player_ = -m_next_player_;

	// Delete the move from history
	delete m_history_.back();
	m_history_.pop_back();
}
