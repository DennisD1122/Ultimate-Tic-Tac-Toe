# Ultimate-Tic-Tac-Toe

## Overview

This is a C++ console application that plays Ultimate Tic-Tac-Toe against the user.
After you make your move, the program will play what it believes to be the best reponse,
determined by a depth-first search using the minimax algorithm with alpha-beta pruning.
The difficulty can be adjusted by specifying the search depth of the algorithm.
Play back and forth until someone (either you or the computer) wins!


## Rules of the game

An Ultimate Tic-Tac-Toe board looks like this:

    . . . | . . . | . . .
    . . . | . . . | . . .
    . . . | . . . | . . .
    ---------------------
    . . . | . . . | . . .
    . . . | . . . | . . .
    . . . | . . . | . . .
    ---------------------
    . . . | . . . | . . .
    . . . | . . . | . . .
    . . . | . . . | . . .

Each dot above represents a square, for a total of 81 squares divided into 9 sections.

Each small 3 x 3 tic-tac-toe board is referred to as a local board,
and the larger 3 x 3 board is referred to as the global board.

The game starts with X playing wherever they want in any of the 81 empty spots.
This move "sends" their opponent to its relative location.
For example, if X played in the top right square of their local board,
then O needs to play next in the local board at the top right of the global board.
O can then play in any one of the nine available spots in that local board,
each move sending X to a different local board.

If a move is played so that it is to win a local board by the rules of normal tic-tac-toe,
then the entire local board is marked as a victory for the player in the global board.

Once a local board is won by a player or it is filled completely, no more moves may be played in that board.
If a player is sent to such a board, then that player may play in any other board.

Game play ends when either a player wins the global board or there are no legal moves remaining,
in which case the game is a draw.

(Source: Wikipedia)


## Instructions for use

You'll first be prompted to play first (the X's) or second (the O's).
Then you'll enter the algorithm's search depth, which in effect will determine how well the computer will play against you.

When making your move, use the integers 1-9, which represent the following locations on the board:

    1 2 3
    4 5 6
    7 8 9

This applies both when choosing the local board and when choosing the individual square.
You will be prompted first for the local board, and then for the square.
However, if you are forced to play in a particular local board, you will only be prompted for the square.

The board will be displayed after every move so you can keep track of how the game is progressing.
Once a local board has been won, a large X or a large O will be displayed in that board, indicating who won that local board.
Your goal is to get three in a row of these large X's or O's.

Have fun!
