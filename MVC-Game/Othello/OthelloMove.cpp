#include <sstream>
#include <string>

using namespace std;

#include "OthelloMove.h"
#include "OthelloBoard.h"
#include "GameMove.h"
#include "GameExceptions.h"

int OthelloMove::mOnHeap = 0;

OthelloMove::OthelloMove() : mRow(-1), mCol(-1) {
}

OthelloMove::OthelloMove(int row, int col) : mRow(row), mCol(col) {
}

GameMove& OthelloMove::operator=(const string &rhs)  {
	istringstream iss(rhs);
	char buff;

	if (rhs == "pass") {
		this->mRow = -1;
		this->mCol = -1;
	} 
	else {
		iss >> buff >> this->mRow >> buff >> this->mCol;

		if (!OthelloBoard::InBounds(this->mRow, this->mCol)) {
			throw OthelloException("Invalid move!");
		}

	}
	return *this;
}

OthelloMove::operator std::string() const {
	ostringstream o;

	o << "(" << mRow << "," << mCol << ")";
	return (IsPass()) ? "pass" : o.str();
}

bool OthelloMove::Equals(const GameMove &other) const {
	const OthelloMove &casted = dynamic_cast<const OthelloMove&>(other);
	return (mRow == casted.mRow && mCol == casted.mCol);
}