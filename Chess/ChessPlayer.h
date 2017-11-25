/*
	Contains ChessPlayer class which is a
	virtual class to represent a chess player.

	This abstract class is designed in such a way that the
	player could be controlled by any type of input (AI, human from
	the command line, human via a GUI, or human or AI input from the
	network).

	Students should not need to change this file. They should, however
	implement a sub-class of this class that handles human player
	input from the command line
*/


#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include<map>
#include<iostream>
#include "CommonTypes.h"

using namespace std;

/**
	Pure virtual (abstract) class to represent a chess player.
	Stuends should implement a subtype of this class to represent a human player.
	Students should not need to modify this class. If they do choose to modify this class,
	the must ensure that it does modify the getMove method signature, the constructor, or
	add any new pure virtual methods. Changing any of these things would cause the test
	code to fail to compile
*/
class ChessPlayer {
protected:
	TEAM_COLOR color;

public:

	/**Instantiates a chess player
	@param color the color of the chess player's team (BLACK or WHITE)
	*/
	ChessPlayer(TEAM_COLOR color) : color(color) {}

	virtual ~ChessPlayer() {}

	/**
	Pure virtual method to get a move from the player. This is the most significant method of the 
	class.
	@param currentState A map from coordinates to pieces. This map contains the current location of 
	all pieces on the board
	@param isTryAgain if this is true, then it indicates that the previous call to getMove returned 
	a move that was illegal and the game controller is now attempting for a second time to get a valid
	move. This is useful for indicating to the player that whatever it attempted previously was not valid
	*/
	virtual Move getMove(map<Coordinate, const Piece*> currentState, bool isTryAgain) = 0;

	/**@return the color of this player */
	TEAM_COLOR getColor() const { return color; }
};

#endif