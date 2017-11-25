/*
	Main entry point for CIS 173 Lab 3 (chess Lab)

	Provides the basics of instantiating the chess game and managing the
	overall game flow.

	Students should only have to make minor edits to this file
*/

#include "ChessGame.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

ChessGame::ChessGame(string startupFile, ChessPlayer* whitePlayer, ChessPlayer* blackPlayer) {
	this->whitePlayer = whitePlayer;
	this->blackPlayer = blackPlayer;

	if (startupFile.length() == 0) {
		initBoard();
	}
	else {
		initBoard(startupFile);
	}
}

ChessGame::~ChessGame() {
	for (auto coordIter = currentState.begin(); coordIter != currentState.end(); coordIter++) {
		delete coordIter->second;
	}
}

void ChessGame::runGame() {

	ChessPlayer* currentPlayer = whitePlayer;
	ChessPlayer* otherPlayer = blackPlayer;

	bool gameOver = false;
	while (!gameOver) {
		printBoard();

		bool inCheck = isInCheck(currentPlayer, currentState);

		if (canMove(currentPlayer)) {

			if (inCheck) {
				cout << "CHECK!" << endl;
			}
			handlePlayersTurn(currentPlayer, gameOver);
		}
		else {
			//If the player can't move, the game is over
			if (inCheck) {
				cout << "CHECK MATE! " << otherPlayer->getColor() << " WINS!" << endl;
			}
			else {
				cout << "STALE MATE!" << endl;
			}
			gameOver = true;
		}

		//switch players
		swap(currentPlayer, otherPlayer);
	}
	cout << "Game Over." << endl;
}

void ChessGame::handlePlayersTurn(ChessPlayer* currentPlayer, bool& isGameOver) {
	bool moveCompleted = false;
	bool isTryAgain = false;
	isGameOver = false;

	while (!moveCompleted) {

		try {
			Move move = currentPlayer->getMove(currentState, isTryAgain);

			if (move.isQuit()) {
				isGameOver = true;
				break;
			}

			performMove(currentPlayer, move);
			moveCompleted = true;
		}
		catch (IllegalMoveException exception) {
			cerr << exception.what() << endl;
			isTryAgain = true;
		}
	}
}

bool ChessGame::isInCheck(ChessPlayer* player, const map<Coordinate, Piece*>& boardState) const {
	//TODO to be completed by student
	return false;
}

bool ChessGame::canMove(ChessPlayer* player) const {
	//TODO to be completed by student
	return false;
}

void ChessGame::performMove(ChessPlayer* player, Move move) {
	//TODO to be completed by student
}

void ChessGame::initBoard() {
	initSide(WHITE);
	initSide(BLACK);
}

void ChessGame::initSide(TEAM_COLOR color) {
	int pawnRow = (color == WHITE) ? 2 : 7;

	for (char col = 'A'; col <= 'H'; col++) {
		Coordinate pawnCoord(col, pawnRow);
		currentState.insert(pair<Coordinate, Piece*>(pawnCoord, new Piece(PAWN, color)));
	}

	int backRow = (color == WHITE) ? 1 : 8;

	currentState.insert(pair<Coordinate, Piece*>(Coordinate('A', backRow), new Piece(ROOK, color)));
	currentState.insert(pair<Coordinate, Piece*>(Coordinate('H', backRow), new Piece(ROOK, color)));
	currentState.insert(pair<Coordinate, Piece*>(Coordinate('B', backRow), new Piece(KNIGHT, color)));
	currentState.insert(pair<Coordinate, Piece*>(Coordinate('G', backRow), new Piece(KNIGHT, color)));
	currentState.insert(pair<Coordinate, Piece*>(Coordinate('C', backRow), new Piece(BISHOP, color)));
	currentState.insert(pair<Coordinate, Piece*>(Coordinate('F', backRow), new Piece(BISHOP, color)));
	currentState.insert(pair<Coordinate, Piece*>(Coordinate('D', backRow), new Piece(QUEEN, color)));
	currentState.insert(pair<Coordinate, Piece*>(Coordinate('E', backRow), new Piece(KING, color)));
}

void ChessGame::initBoard(string fileName) {

	ifstream input;
	input.open(fileName);

	if (!input) {
		cerr << "Could not open the file " << fileName << endl
			<< "Reverting to the default chess setup" << endl;
		initBoard();
		return;
	}

	string line;
	while (getline(input, line)) {
		istringstream lineStream(line);
		Coordinate coord('A', 1);
		PIECE_TYPE type;
		TEAM_COLOR color;
		lineStream >> coord >> color >> type;

		if (lineStream.fail()) {
			cerr << "Error reading startup file." << endl
				<< "Failed while reading line \"" << line << "\"" << endl
				<< "Reverting to the default chess setup" << endl;
			currentState.clear();
			initBoard();
			return;
		}

		Piece* piece = new Piece(type, color);
		currentState.insert(pair<Coordinate, Piece*>(coord, piece));
	}

}

void ChessGame::printBoard() const {
	cout << "  |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |" << endl
		 << "--+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
	for (unsigned short row = 8; row >= 1; row--) {

		//Top line of each row contains color of chess
		//board if no piece is present, or text describing
		//color of piece if a piece is present
		cout << "  |";
		
		for (char column = 'A'; column <= 'H'; column++) {
			string output("     ");
			if ((row + column) % 2 == 0) {
				output = "#####";
			}

			auto pieceInSquareIter = currentState.find(Coordinate(column, row));

			if (pieceInSquareIter != currentState.end()) {
				output = (pieceInSquareIter->second->getTeam() == WHITE) ? "White" : "Black";
			}

			cout << output << "|";
		}
		cout << endl;

		//Second line contains the Piece if present
		cout << row << " |";
		for (char column = 'A'; column <= 'H'; column++) {
			string output("     ");
			if ((row + column) % 2 == 0) {
				output = "#####";
			}

			auto pieceInSquareIter = currentState.find(Coordinate(column, row));

			if (pieceInSquareIter != currentState.end()) {
				switch (pieceInSquareIter->second->getPieceType()) {
				case KING:
					output = "King ";
					break;
				case QUEEN:
					output = "Queen";
					break;
				case ROOK:
					output = "Rook ";
					break;
				case BISHOP:
					output = "Bisho";
					break;
				case KNIGHT:
					output = "Knigh";
					break;
				case PAWN:
					output = "Pawn ";
					break;
				}
			}

			cout << output << "|";
		}
		cout << endl;

		//Third line is just the color of the square
		cout << "  |";

		for (char column = 'A'; column <= 'H'; column++) {
			string output("     ");
			if ((row + column) % 2 == 0) {
				output = "#####";
			}
			cout << output << "|";
		}
		cout << endl;

		//Finally draw the gridline
		cout << "--+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;

	}
}


int main(int argc, const char** args) {

	cout << "Enter path to starting conditions file, or \"None\" for standard setup:";

	string startupFileName;
	cin >> startupFileName;

	if (startupFileName == "None" || startupFileName == "none") {
		startupFileName = "";
	}
		
	//TODO replace the arguments with pointers to your human
	//input player class
	//For example:
	//HumanPlayer whitePlayer(WHITE)
	//HumanPlayer blackPlayer(BLACK)
	//ChessGame game(startupFileName, &whitePlayer, &blackPlayer);

	ChessGame game(startupFileName, nullptr, nullptr);

	game.runGame();

	return 0;
}

