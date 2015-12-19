#ifndef __GAMEBOARD_H
#define __GAMEBOARD_H

#include "GameMove.h"
#include "GameExceptions.h"
#include <vector>

class GameBoard {
public:
   virtual ~GameBoard() {
      // Any moves owned by the game board are freed from the heap when the board is destructed.
		for (GameMove *m : m_history_) {
			delete m;
		}
		m_history_.clear();
   }

   // Initializes a GameBoard with a NextPlayer of 1, and a Value of 0
   GameBoard() : m_next_player_(1), m_value_(0) {}

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

   // Undoes the most recent move applied to the board.
   virtual void UndoLastMove() = 0;

   // Creates an appropriate GameMove-derived object representing a "blank" move
   //on this type of board. This object can be assigned to with a string.
   virtual GameMove *CreateMove() const = 0;
   
   // Returns true if the game board is "finished", e.g., if one player has won
   // and no more moves should be allowed.
   virtual bool IsFinished() const = 0;

   // Gets the value of the board indicating who is winning.
   inline int GetValue() const {return m_value_;}

   // Gets the player whose turn it is; that is, which player will the next move
   // belong to?
   inline int GetNextPlayer() const {return m_next_player_;}

   // Gets a vector of all moves applied to this board. The last move in the vector
   // is the most recent move applied to the board.
   inline const std::vector<GameMove *>* GetMoveHistory() const {
      return &m_history_;
   }

   // Gets number of moves from 
   inline int GetMoveCount() const {
      return m_history_.size();
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
   
   // Every two-player board game needs to keep track of the next player, the 
   // board's value, and the history of moves applied to the board.
   char m_next_player_;
   int m_value_;
   std::vector<GameMove *> m_history_;
};

#endif