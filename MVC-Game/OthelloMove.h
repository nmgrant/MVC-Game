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
	
   /*
   A FlipSet tracks a direction and # of pieces that got flipped when this 
   move was applied. See spec.
   */
   class FlipSet {
   public:
      FlipSet(char sw, char row, char col) : switched(sw), rowDelta(row), 
       colDelta(col) {}

      char switched;
      char rowDelta, colDelta;
   };
   
   int mRow, mCol;
   std::vector<FlipSet> mFlips;

   // KEEP THESE CONSTRUCTORS PRIVATE.
   // Default constructor: initializes this move as a PASS.
   OthelloMove();
   /*
   2-parameter constructor: initializes this move with the given 
   row and column.
   */
   OthelloMove(int row, int col);
   
   void AddFlipSet(FlipSet set) {mFlips.push_back(set);}
public:
   static int mOnHeap;

   static void* operator new(std::size_t sz){
      mOnHeap++;
      return ::operator new(sz);
   }

      static void operator delete(void* ptr, std::size_t sz) {
      mOnHeap--;
      ::operator delete(ptr);
   }

	virtual ~OthelloMove() {}
   /*
   This assignment operator takes a string representation of an Othellomove
   and uses it to initialize the move. The string is in the format
   (r, c); OR is the string "pass". [The user will not enter (-1,-1) to pass
   anymore.]
   */
	virtual GameMove& operator=(const std::string &);

   /*
   Compares two OthelloMove objects for equality.
   */
   virtual bool Equals(const GameMove &other) const;
   
   // Converts the OthelloMove into a string representation, one that could be
   // used correctly with operator=(string). Returns "pass" if move is a pass.
   virtual operator std::string() const;

   // Returns true if the move represents a Pass.
   // TO DO: fill in this method.
	inline bool IsPass() const {return mRow == -1 && mCol == -1;}
};

#endif