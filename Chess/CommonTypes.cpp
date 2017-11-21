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

bool Coordinate::operator<(const Coordinate& rhs) const {
	if (this->getColumn() != rhs.getColumn()) {
		return this->getColumn() < rhs.getColumn();
	}
	else {
		return this->getRow() < rhs.getRow();
	}
}


IllegalMoveException::IllegalMoveException(Move move, string message) {
	stringstream msgStream;
	Coordinate from = move.getFrom();
	Coordinate to = move.getTo();

	msgStream << "Illegal Move: " << from.getColumn() << from.getRow() << "-> "
		<< to.getColumn() << to.getRow() << ". "
		<< message;
	fullMessage = msgStream.str();

}

const char* IllegalMoveException::what() const {
	return fullMessage.c_str();
}