#ifndef __ConnectFourVIEW_H
#define __ConnectFourVIEW_H
#include "ConnectFourBoard.h"
#include "GameView.h"
#include <iostream>

class ConnectFourView : public GameView {
private:
	ConnectFourBoard *mConnectFourBoard;
	virtual void PrintBoard(std::ostream &s) const;

public:
	virtual ~ConnectFourView() {}
   ConnectFourView(GameBoard *b) : mConnectFourBoard(dynamic_cast<ConnectFourBoard*>(b)) {}
};
#endif