#ifndef __OTHELLOVIEW_H
#define __OTHELLOVIEW_H
#include "OthelloBoard.h"
#include "GameView.h"
#include <iostream>

// Same code as before; but now you just implement PrintBoard, and not
// operator<<.
class OthelloView : public GameView {
private:
	OthelloBoard *mOthelloBoard;
	virtual void PrintBoard(std::ostream &s) const;

public:
	virtual ~OthelloView() {}
   OthelloView(GameBoard *b) : mOthelloBoard(dynamic_cast<OthelloBoard*>(b)) {}
};
#endif