#ifndef __GAMEVIEW_H
#define __GAMEVIEW_H
#include "GameBoard.h"
#include <iostream>

class GameView {
private:
   // Prints the View's member GameBoard to the ostream parameter.
   virtual void PrintBoard(std::ostream &s) const = 0;


public:
   virtual ~GameView() {}
	/*
   Helper method for doing operator<< on derived GameView types. This method
   will be called any time you use << to output a GameView object; the 
   operator will in turn call the virtual PrintBoard method to support base-class
   output.
   */
   friend std::ostream& operator<< (std::ostream &os, const GameView &v) {
      v.PrintBoard(os);
      return os;
   }
};

#endif