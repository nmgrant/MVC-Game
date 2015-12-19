#include <sstream>
#include <string>

using namespace std;

#include "TicTacToeMove.h"
#include "TicTacToeBoard.h"
#include "GameMove.h"
#include "GameExceptions.h"

int TicTacToeMove::m_on_heap_ = 0;

// Default constructor for TicTacToeMove
TicTacToeMove::TicTacToeMove() {
}

// 2-parameter constructor: initializes this move with the given 
// row and column.
TicTacToeMove::TicTacToeMove(int row, int col) : m_row_(row), m_col_(col) {
}

/*
This assignment operator takes a string representation of an TicTacToeMove
and uses it to initialize the move. The string is in the format
(r, c)
*/
GameMove& TicTacToeMove::operator=(const string &rhs)  {
	istringstream iss(rhs);
	char buff;

	// Parses the user's input for row and column
	iss >> buff >> this->m_row_ >> buff >> this->m_col_;

	// If the move is invalid, throws exception
	if (!TicTacToeBoard::InBounds(this->m_row_, this->m_col_)) {
		throw TicTacToeException("Invalid move!");
	}

	// Return this OthelloMove for instantiation
	return *this;
}

// Converts the TicTacToeMove into a string representation, one that could be
// used correctly with operator=(string). Returns "pass" if move is a pass.
TicTacToeMove::operator std::string() const {
	ostringstream o;

	o << "(" << m_row_ << "," << m_col_ << ")";
	return o.str();
}

// Compares two TicTacToeMove objects for equality.
bool TicTacToeMove::Equals(const GameMove &other) const {
	const TicTacToeMove &casted = dynamic_cast<const TicTacToeMove&>(other);
	return (m_row_ == casted.m_row_ && m_col_ == casted.m_col_);
}