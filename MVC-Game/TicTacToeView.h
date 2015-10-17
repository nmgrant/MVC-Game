#ifndef __TicTacToeVIEW_H
#define __TicTacToeVIEW_H
#include "TicTacToeBoard.h"
#include "GameView.h"
#include <iostream>

class TicTacToeView : public GameView {
private:
	TicTacToeBoard *mTicTacToeBoard;
	virtual void PrintBoard(std::ostream &s) const;

public:
	virtual ~TicTacToeView() {}
   TicTacToeView(GameBoard *b) : mTicTacToeBoard(dynamic_cast<TicTacToeBoard*>(b)) {}
};
#endif