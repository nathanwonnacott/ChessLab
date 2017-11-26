/* 
Contains implementations of various types defined in CommonTypes.h as
well as utility methods to operate on them.
Students should not need to modify this file
*/


#include <iostream>
#include <sstream>

#include "CommonTypes.h"

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

istream& operator>>(istream& input, TEAM_COLOR& team) {
	string strColor;
	input >> strColor;

	if (strColor == "WHITE") {
		team = WHITE;
	}
	else if (strColor == "BLACK") {
		team = BLACK;
	}
	else {
		input.setstate(ios_base::failbit);
	}
	return input;
}

istream& operator>>(istream& input, PIECE_TYPE& piece) {
	
	string strPiece;
	input >> strPiece;

	if (strPiece == "PAWN") {
		piece = PAWN;
	}
	else if (strPiece == "ROOK") {
		piece = ROOK;
	}
	else if (strPiece == "KNIGHT") {
		piece = KNIGHT;
	}
	else if (strPiece == "BISHOP") {
		piece = BISHOP;
	}
	else if (strPiece == "KING") {
		piece = KING;
	}
	else if (strPiece == "QUEEN") {
		piece = QUEEN;
	}
	else {
		input.setstate(ios_base::failbit);
	}

	return input;
}

bool Coordinate::operator<(const Coordinate& rhs) const {
	if (this->getColumn() != rhs.getColumn()) {
		return this->getColumn() < rhs.getColumn();
	}
	else {
		return this->getRow() < rhs.getRow();
	}
}

istream& operator>>(istream& input, Coordinate& coord) {
	string str;
	input >> str;

	if (str.length() != 2) {
		input.setstate(ios_base::failbit);
	}
	else {
		try {
			coord.setColumn(str.at(0));
			coord.setRow((int)(str.at(1) - '0'));
		}
		catch (invalid_argument e) {
			input.setstate(ios_base::failbit);
		}
	}

	return input;

}


IllegalMoveException::IllegalMoveException(Move move, string message) {
	stringstream msgStream;
	Coordinate from = move.getFrom();
	Coordinate to = move.getTo();

	msgStream << "Illegal Move: " << from.getColumn() << from.getRow() << "->"
		<< to.getColumn() << to.getRow() << ". "
		<< message;
	fullMessage = msgStream.str();
		
}

const char* IllegalMoveException::what() const noexcept {
	return fullMessage.c_str();
}