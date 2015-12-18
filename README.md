# MVC-Game
A C++ console implementation of Othello, Connect Four, and Tic-Tac-Toe using MVC and polymorphism.

This program includes a set of generic Game classes for the Model, the View, and the Controller (Board, View, Move).

Using each Game class as a parent class, the three games (Othello, Connect Four, and Tic-Tac-Toe) are 
implemented in separate child classes.

The main program begins by asking the user to select the game they wish to play. The appropriate game is then
initialized and the initial board is printed. Below the board is a list of possible moves.

The program then prompts the user for their move with an input pattern specific to each game. All input uses
input validation based on the possible moves.

Once the game finishes, the user may play again or exit.
