#include <sstream>
#include <string>

using namespace std;

#include "OthelloMove.h"
#include "OthelloBoard.h"
#include "GameMove.h"
#include "GameExceptions.h"

int OthelloMove::m_on_heap_ = 0;

// Constructor for a "pass" move
OthelloMove::OthelloMove() : m_row_(-1), m_col_(-1) {
}

// Constructor for a move using a given row and column
OthelloMove::OthelloMove(int row, int col) : m_row_(row), m_col_(col) {
}

/*
This assignment operator takes a string representation of an Othellomove
and uses it to initialize the move. The string is in the format
(r, c); OR is the string "pass". 
*/
GameMove& OthelloMove::operator=(const string &rhs)  {
	istringstream iss(rhs);
	char buff;

	// If the user entered "move pass", sets the OthelloMove to a pass
	if (rhs == "pass") {
		this->m_row_ = -1;
		this->m_col_ = -1;
	}
	// Else, parse the row and column from the user's entered move (e.g. move (2,3) => row = 2, col = 3)
	else {
		iss >> buff >> this->m_row_ >> buff >> this->m_col_;

		// Throws exception if invalid move (not in bounds)
		if (!OthelloBoard::InBounds(this->m_row_, this->m_col_)) {
			throw OthelloException("Invalid move!");
		}

	}

	// Return this OthelloMove for instantiation
	return *this;
}

// Converts the OthelloMove into a string representation, one that could be
// used correctly with operator=(string). Returns "pass" if move is a pass.
OthelloMove::operator std::string() const {
	ostringstream o;

	o << "(" << m_row_ << "," << m_col_ << ")";
	return (IsPass()) ? "pass" : o.str();
}

// Compares two OthelloMove objects for equality.
bool OthelloMove::Equals(const GameMove &other) const {
	const OthelloMove &casted = dynamic_cast<const OthelloMove&>(other);
	return (m_row_ == casted.m_row_ && m_col_ == casted.m_col_);
}