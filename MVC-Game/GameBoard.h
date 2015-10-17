#ifndef __GAMEBOARD_H
#define __GAMEBOARD_H

#include "GameMove.h"
#include "GameExceptions.h"
#include <vector>

class GameBoard {
public:
   // WRITE THIS FUNCTION!!!
   virtual ~GameBoard() {
      // You must write this function so that any moves owned by the game board
      // are freed from the heap when the board is destructed.
		for (GameMove *m : mHistory) {
			delete m;
		}
		mHistory.clear();
      // remove the following line once you have finished this function.
      // This exception is just a reminder to write this function.
   }

   // Initializes a GameBoard with a NextPlayer of 1, and a Value of 0
   GameBoard() : mNextPlayer(1), mValue(0) {}

   /*
   Fills in a vector with all possible moves that are valid for the current 
   board state. The board is not responsible for deleting the move pointers
   returned from this function.
   */
   virtual void GetPossibleMoves(std::vector<GameMove *> *list) const = 0;

   /*
   Applies a given move to the board, updating its game state and history
   accordingly. The board takes ownership of the move pointer given. The 
   GameMove must an appropriate type for this GameBoard.
   */
   virtual void ApplyMove(GameMove *move) = 0;

   /*
   Undoes the most recent move applied to the board.
   */
   virtual void UndoLastMove() = 0;

   /*
   Creates an appropriate GameMove-derived object representing a "blank" move
   on this type of board. This object can be assigned to with a string.
   */
   virtual GameMove *CreateMove() const = 0;
   
   /*
   Returns true if the game board is "finished", e.g., if one player has won
   and no more moves should be allowed.
   */
   virtual bool IsFinished() const = 0;

   /*
   Gets the value of the board indicating who is winning.
   */
   inline int GetValue() const {return mValue;}

   /*
   Gets the player whose turn it is; that is, which player will the next move
   belong to?
   */
   inline int GetNextPlayer() const {return mNextPlayer;}

   /*
   Gets a vector of all moves applied to this board. The last move in the vector
   is the most recent move applied to the board.
   */
   inline const std::vector<GameMove *>* GetMoveHistory() const {
      return &mHistory;
   }

   inline int GetMoveCount() const {
      return mHistory.size();
   }

   /*
   Returns a string representation for the given player value. For most games 
   this should be "Black" or "White", but this can be customized, e.g. for 
   Tic-Tac-Toe.
   */
   virtual std::string GetPlayerString(char player) {
      return (player == 1 ? "Black" : "White");
   }

protected:
   /*
   Every two-player board game needs to keep track of the next player, the 
   board's value, and the history of moves applied to the board.
   */
   char mNextPlayer;
   int mValue;
   std::vector<GameMove *> mHistory;
};

#endif