#ifndef __TicTacToeMOVE_H
#define __TicTacToeMOVE_H
#include "GameMove.h"
#include <string>
#include <vector>
#include <iostream>
/*
An TicTacToeMove encapsulates a single potential move on an TicTacToeBoard. It
is represented internally by a row and column, both 0-based.
*/
class TicTacToeMove : public GameMove {
private:
   // TicTacToeBoard is a friend so it can access mRow and mCol.
	friend class TicTacToeBoard;
	
   /*
   A FlipSet tracks a direction and # of pieces that got flipped when this 
   move was applied. See spec.
   */
   
   int m_row_, m_col_;

   // Default constructor
   TicTacToeMove();
   // 2-parameter constructor: initializes this move with the given 
   // row and column.
   TicTacToeMove(int row, int col);

public:
   static int m_on_heap_;

   static void* operator new(std::size_t sz){
      m_on_heap_++;
      return ::operator new(sz);
   }

      static void operator delete(void* ptr, std::size_t sz) {
      m_on_heap_--;
      ::operator delete(ptr);
   }

	virtual ~TicTacToeMove() {}
   /*
   This assignment operator takes a string representation of an TicTacToeMove
   and uses it to initialize the move. The string is in the format
   (r, c)
   */
	virtual GameMove& operator=(const std::string &);

   // Compares two TicTacToeMove objects for equality.
   virtual bool Equals(const GameMove &other) const;
   
   // Converts the TicTacToeMove into a string representation, one that could be
   // used correctly with operator=(string). Returns "pass" if move is a pass.
   virtual operator std::string() const;

};

#endif