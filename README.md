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


# Examples

Othello

![othello](https://cloud.githubusercontent.com/assets/10593907/11891532/5272002c-a514-11e5-9024-1ef794c0b375.png)

Connect Four

![connectfour](https://cloud.githubusercontent.com/assets/10593907/11891533/52753116-a514-11e5-86c6-52f4dafd1e81.png)

TicTacToe

![tictactoe](https://cloud.githubusercontent.com/assets/10593907/11891534/5276c0ee-a514-11e5-8bdb-2aade361c998.png)
