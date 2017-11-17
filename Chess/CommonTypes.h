/**
	This file contains several small types that are shared throughout the
	chess program.

	Students should not need to edit this file, but they may add to it if
	they desire. Students should make sure that no changes modify any of the existing
	functionality of these types.
*/

#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include<stdexcept>

using namespace std;

/**
	Enum to represent each of the types of chess piece
*/
enum PIECE_TYPE {
	KING,
	QUEEN,
	BISHOP,
	KNIGHT,
	ROOK,
	PAWN
};

/**
	Enum to represent the two colors/teams/sides in the chess game
*/
enum TEAM_COLOR {
	WHITE,
	BLACK
};

/**
	Overload of the insertion operator for TEAM_COLOR to output "WHITE" or "BLACK"
*/
ostream& operator<<(ostream& out, TEAM_COLOR team) {
	if (team == WHITE) {
		out << "WHITE";
	}
	else {
		out << "BLACK";
	}
	return out;
}

/**
Represents a square on a chess board (A-1 through H-8)
*/
class Coordinate {

private:
	/*Capital letter representing column (files) on chess board.
	A is white's left side and H is white's right side*/
	char columnLetter;
	/*The number representing the row on the chess board.
	1 is White's back row and 8 is black's back row*/
	unsigned short rowNumber;

public:
	/**
		Instantiates a coordinate
		@param columnLetter - the capital letter (A-H) representing the column of the square
		@param rowNumber - the number (1-8) representing the row of the square

		@throws invalid_argument if the column or row is
		out of the specified ranges
	*/
	Coordinate(char columnLetter, unsigned short rowNumber) {
		this->setRow(rowNumber);
		this->setColumn(columnLetter);
	}

	/** @return the character representing the row */
	char getColumn() const { return columnLetter; }
	/** @return the number representing the colum */
	int getRow() const { return rowNumber; }

	/** sets the column 
		@param columnLetter character 'A'-'H' representing the column
		@throws invalid_argument if the character is not between 'A' and 'H' inclusive
	*/
	void setColumn(char columnLetter) {
		if (columnLetter > 'H' || columnLetter < 'A') {
			throw invalid_argument("Column must be between A and H (inclusive)");
		}
		this->columnLetter = columnLetter;
	}

	/** sets the row
	@param rowNumber number 1-8 representing the column
	@throws invalid_argument if the rowNumber is not between 1 and 8 inclusive
	*/
	void setRow(int rowNumber) {
		if (rowNumber < 1 || rowNumber > 8) {
			throw invalid_argument("Row number must be between 1 and 8 (inclusive)");
		}
		this->rowNumber = rowNumber;
	}
};

/**
	Compares two coordinates. The actual ordering of the coordinates is insignificant. 
	All that matters is that it is consistant and that two equal coordinates always
	return false when passed into this method.
*/
bool operator<(const Coordinate& lhs, const Coordinate& rhs) {
	if (lhs.getColumn() != rhs.getColumn()) {
		return lhs.getColumn() < rhs.getColumn();
	}
	else {
		return lhs.getRow() < rhs.getRow();
	}
}

/**
	Represents a single move from one coordinate to another
*/
class Move {
private:
	const Coordinate fromCoordinate;
	const Coordinate toCoordinate;

public:
	/** Creates a move from one coordinate to another 
		@param fromCoordinate the starting coordinate
		@param toCoordinate the coordinate where the piece ends up
	*/
	Move(Coordinate fromCoordinate, Coordinate toCoordinate) :
		fromCoordinate(fromCoordinate),
		toCoordinate(toCoordinate) {}

	/**@return the starting coordinate for this move*/
	Coordinate getFrom() const { return fromCoordinate; }
	/**@return the destination coordinate for this move */
	Coordinate getTo() const { return toCoordinate; }
};

/**
	This class represents a simplistic view of a piece that is used to interface
	between the ChessGame and the ChessPlayers. It is kept simple for the sake of
	easy implementation of the interface, but individual ChessPlayer implementations
	will probably want to create their own classes to represent chess pieces and only
	use this class when calling methods through the ChessGame/ChessPlayer interface methods.
*/
class Piece {
private:
	PIECE_TYPE pieceType;
	TEAM_COLOR team;

public:
	/**Instantiates a piece type
	@param pieceType the type of the piece (PAWN, BISHOP, etc)
	@param the team/color of the piece (WHITE or BLACK)
	*/
	Piece(PIECE_TYPE pieceType, TEAM_COLOR team) : pieceType(pieceType), team(team) {}
	virtual ~Piece() {}
	/***@return the piece type*/
	PIECE_TYPE getPieceType() { return pieceType; }
	/**@return the piece team */
	TEAM_COLOR getTeam() { return team; }
};

/**
Exception to be thrown whenever a move is attempted that is illegal or invalid
*/
class IllegalMoveException : public exception {
private:
	Move move;
	string message;
public:
	/**
		Instantiates the exception
		@param move the attempted illegal move
		@param message short message explaining why the move was illegal
	*/
	IllegalMoveException(Move move, string message) : move(move), message(message) {}
	/**
	@returns a message consisting of the move attempted and a message explaining why it was illegal
	*/
	virtual const char* what() const;
};

#endif
