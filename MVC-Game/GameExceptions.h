#ifndef __GAMEEXCEPTIONS_H
#define __GAMEEXCEPTIONS_H

#include <string>
#include <stdexcept>

class GameException : public std::runtime_error {
public:
   GameException(const std::string &m) : std::runtime_error(m) {}
};

class OthelloException : public GameException {
public:
   OthelloException(const std::string &m) : GameException(m) {}
};

class TicTacToeException : public GameException {
public:
   TicTacToeException(const std::string &m) : GameException(m) {}
};

class ConnectFourException : public GameException {
public:
   ConnectFourException(const std::string &m) : GameException(m) {}
};

#endif