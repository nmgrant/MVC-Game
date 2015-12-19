#ifndef __OTHELLOMOVE_H
#define __OTHELLOMOVE_H
#include "GameMove.h"
#include <string>
#include <vector>
#include <iostream>
/*
An OthelloMove encapsulates a single potential move on an OthelloBoard. It
is represented internally by a row and column, both 0-based.
*/
class OthelloMove : public GameMove {
private:
   // OthelloBoard is a friend so it can access mRow and mCol.
	friend class OthelloBoard;
	
   // A FlipSet tracks a direction and # of pieces that got flipped when this 
   // move was applied.
   class FlipSet {
   public:
      FlipSet(char sw, char row, char col) : switched(sw), row_delta_(row), 
       col_delta_(col) {}

      char switched;
      char row_delta_, col_delta_;
   };
   
   int m_row_, m_col_;
   std::vector<FlipSet> m_flips_;

   // Default constructor: initializes this move as a PASS.
   OthelloMove();
   // 2-parameter constructor: initializes this move with the given 
   // row and column.
   OthelloMove(int row, int col);
   
   // Used to track pieces that were flipped upon a successful move
   void AddFlipSet(FlipSet set) {m_flips_.push_back(set);}
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

	virtual ~OthelloMove() {}
   /*
   This assignment operator takes a string representation of an Othellomove
   and uses it to initialize the move. The string is in the format
   (r, c); OR is the string "pass". 
   */
	virtual GameMove& operator=(const std::string &);

   // Compares two OthelloMove objects for equality.
   virtual bool Equals(const GameMove &other) const;
   
   // Converts the OthelloMove into a string representation, one that could be
   // used correctly with operator=(string). Returns "pass" if move is a pass.
   virtual operator std::string() const;

   // Returns true if the move represents a Pass.
   // TO DO: fill in this method.
	inline bool IsPass() const {return m_row_ == -1 && m_col_ == -1;}
};

#endif