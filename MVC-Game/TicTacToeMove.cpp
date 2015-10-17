#include <sstream>
#include <string>

using namespace std;

#include "TicTacToeMove.h"
#include "TicTacToeBoard.h"
#include "GameMove.h"
#include "GameExceptions.h"

int TicTacToeMove::mOnHeap = 0;

TicTacToeMove::TicTacToeMove() {
}

TicTacToeMove::TicTacToeMove(int row, int col) : mRow(row), mCol(col) {
}

GameMove& TicTacToeMove::operator=(const string &rhs)  {
	istringstream iss(rhs);
	char buff;

	iss >> buff >> this->mRow >> buff >> this->mCol;

	if (!TicTacToeBoard::InBounds(this->mRow, this->mCol)) {
		throw TicTacToeException("Invalid move!");
	}

	return *this;
}

TicTacToeMove::operator std::string() const {
	ostringstream o;

	o << "(" << mRow << "," << mCol << ")";
	return o.str();
}

bool TicTacToeMove::Equals(const GameMove &other) const {
	const TicTacToeMove &casted = dynamic_cast<const TicTacToeMove&>(other);
	return (mRow == casted.mRow && mCol == casted.mCol);
}