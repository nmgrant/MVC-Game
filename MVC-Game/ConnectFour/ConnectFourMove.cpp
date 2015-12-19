#include <sstream>
#include <string>

using namespace std;

#include "ConnectFourMove.h"
#include "ConnectFourBoard.h"
#include "GameMove.h"
#include "GameExceptions.h"

int ConnectFourMove::m_on_heap_ = 0;

// Default ConnectFourMove
ConnectFourMove::ConnectFourMove() {
}

// Instantiates a ConnectFourMove with given row and column
ConnectFourMove::ConnectFourMove(int row, int col) : m_row_(row), m_col_(col) {
}

// Allows for assignment operator using string (move (2,3)) for instantiation 
GameMove& ConnectFourMove::operator=(const string &rhs)  {
	istringstream iss(rhs);
	char col;

	iss >> col;

	// Checks which character the user entered after "move" (e.g. move A => mCol = 0)
	this->m_col_ = col == 'A' ? 0
				  : col == 'B' ? 1
				  : col == 'C' ? 2
				  : col == 'D' ? 3
				  : col == 'E' ? 4
				  : col == 'F' ? 5
				  : col == 'G' ? 6
				  : throw ConnectFourException("Invalid move!");
	this->m_row_ = 0;

	// Returns this ConnectFourMove for instantiation
	return *this;
}

// Allows for string representation for a ConnectFourMove 
ConnectFourMove::operator std::string() const {
	ostringstream o;

	string move = m_col_ == ConnectFourBoard::A ? "A"
				   : m_col_ == ConnectFourBoard::B ? "B"
				   : m_col_ == ConnectFourBoard::C ? "C"
					: m_col_ == ConnectFourBoard::D ? "D"
					: m_col_ == ConnectFourBoard::E ? "E"
					: m_col_ == ConnectFourBoard::F ? "F"
					: "G";
	o << move;
	return o.str();
}

// Allows for comparing two ConnectFourMoves
bool ConnectFourMove::Equals(const GameMove &other) const {
	const ConnectFourMove &casted = dynamic_cast<const ConnectFourMove&>(other);
	return (m_row_ == casted.m_row_ && m_col_ == casted.m_col_);
}