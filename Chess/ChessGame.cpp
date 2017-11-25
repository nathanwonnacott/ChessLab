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
	cout << "  ABCDEFGH" << endl
		 << " +--------" << endl;
	for (unsigned short row = 8; row >= 1; row--) {
		cout << row << '|';
		
		for (char column = 'A'; column <= 'H'; column++) {
			char square = ' ';
			if ((row + column) % 2 == 0) {
				square = '*';
			}

			Coordinate currentCoord(column, row);
			if (currentState.find(currentCoord) != currentState.end()) {
				//The map contains the current coordinate
				//We want to print the corresponding character
				Piece* piece = currentState.at(currentCoord);
				switch (piece->getPieceType()) {
				case PAWN:
					square = 'P';
					break;
				case ROOK:
					square = 'R';
					break;
				case KNIGHT:
					square = 'H';
					break;
				case BISHOP:
					square = 'B';
					break;
				case KING:
					square = 'K';
					break;
				case QUEEN:
					square = 'Q';
					break;
				default:
					square = '?';
				}

				if (piece->getTeam() == BLACK) {
					square += ('a' - 'A'); //convert to lower case
				}

			}
			cout << square;
		}

		cout << endl;
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

	int foobar;
	cin >> foobar;
	return 0;
}

