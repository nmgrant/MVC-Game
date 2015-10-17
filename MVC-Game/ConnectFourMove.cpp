#include <sstream>
#include <string>

using namespace std;

#include "ConnectFourMove.h"
#include "ConnectFourBoard.h"
#include "GameMove.h"
#include "GameExceptions.h"

int ConnectFourMove::mOnHeap = 0;

ConnectFourMove::ConnectFourMove() {
}

ConnectFourMove::ConnectFourMove(int row, int col) : mRow(row), mCol(col) {
}

GameMove& ConnectFourMove::operator=(const string &rhs)  {
	istringstream iss(rhs);
	char col;

	iss >> col;

	this->mCol = col == 'A' ? 0
				  : col == 'B' ? 1
				  : col == 'C' ? 2
				  : col == 'D' ? 3
				  : col == 'E' ? 4
				  : col == 'F' ? 5
				  : col == 'G' ? 6
				  : throw ConnectFourException("Invalid move!");
	this->mRow = 0;
	return *this;
}

ConnectFourMove::operator std::string() const {
	ostringstream o;

	string move = mCol == ConnectFourBoard::A ? "A"
				   : mCol == ConnectFourBoard::B ? "B"
				   : mCol == ConnectFourBoard::C ? "C"
					: mCol == ConnectFourBoard::D ? "D"
					: mCol == ConnectFourBoard::E ? "E"
					: mCol == ConnectFourBoard::F ? "F"
					: "G";
	o << move;
	return o.str();
}

bool ConnectFourMove::Equals(const GameMove &other) const {
	const ConnectFourMove &casted = dynamic_cast<const ConnectFourMove&>(other);
	return (mRow == casted.mRow && mCol == casted.mCol);
}