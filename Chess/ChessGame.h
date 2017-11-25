/*
	Contains ChessGame class.
	This class manages the overall flow of the game.

	Students should not need to make any modifications to this file

*/

#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "ChessPlayer.h"
#include "CommonTypes.h"


/**
The main game controller for the chess program
*/
class ChessGame {

private:
	ChessPlayer* whitePlayer;
	ChessPlayer* blackPlayer;

	/** Map from coordinates on the board to the piece contained on each coordinate.
	This contains every piece currently on the board
	*/
	map<Coordinate, Piece*> currentState;

public:
	/**
		Instantiates a chess game with the specified players
		@param startupFile file containing starting conditions for game. Empty string for default conditions
		@param whitePlayer the white player (note that whitePlayer->getColor() must return WHITE)
		@param blackPlayer the black player (note that blackPlayer->getColor() must return BLACK)
	*/
	ChessGame(string startupFile, ChessPlayer* whitePlayer, ChessPlayer* blackPlayer);

	virtual ~ChessGame();

	/**
		Starts the chess game and runs it to completion
		@param printBoard if true, print board between each turn for debugging purposes
	*/
	void runGame();

private:


	/**
		Determines if the player is in check based on the specified board state.
		Note that the reason that a board state is passed in rather than just using
		the current board state is because this method could be used to evaluate potential
		moves in order to determine if they would put the moving player in check

		@param player the player to evaluate
		@param the state of the board to evaluate
		@return true if the specified player is currently in check
	*/
	bool isInCheck(ChessPlayer* player, const map<Coordinate, Piece*>& boardState) const;

	/**
		@return true if the specified player can move (note that a player may not
		perform any moves that put his/her king in check)
	*/
	bool canMove(ChessPlayer* player) const;

	/**
		executes one turn for the specified player
		@param player the player whose turn it is
		@param isGameOver set to true if the player chose to quit the game
	*/
	void handlePlayersTurn(ChessPlayer* player, bool& isGameOver);

	/**
		Attempts to perform the specified move for the specified player
		@throws IllegalMoveException if the move is invalid.
		Note that moves are considered invalid if they move a piece off the board,
		if they violate the way that a piece moves, if the piece to move does not belong
		to the specified player, if no piece exists on the starting coordinate of the move,
		of if the move results in the specified player's king being put in check
	*/
	void performMove(ChessPlayer* player, Move move);

	/**
		Sets up the initial positions of the pieces on the board
	*/
	void initBoard();

	/**
		Sets up the initial positions of the pieces for an individual side
	*/
	void initSide(TEAM_COLOR color);

	/**
		Initializes the board based on the contents of the specified file
	*/
	void initBoard(string fileName);

	/*
	Displays an ASCII representation of the chess board
	*/
	void printBoard() const;
	
};

#endif
