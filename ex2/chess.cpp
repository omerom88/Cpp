//============================================================================
// Name         : ex2.cpp
// Author      : omerom88
// Description :
//============================================================================

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
using namespace std;
#define START_L 65
#define END_L 72
#define START_N 49
#define END_N 56
pair<int, int> whiteKingLoc (7, 4);
pair<int, int> blackKingLoc (0, 4);



/**
 * Function that take the CheckBoard indexes and parse it to our 2D-array
 */
pair<int, int> parser(string moveInput)
{
	pair<int, int>  moveFrom;
	//we need only two iterations.
	for(int i = 0; i < 3; i += 2 )
	{
		if(moveInput.length() != 4 || moveInput[i] < START_L || moveInput[i] > END_L ||
		   moveInput[i + 1] < START_N || moveInput[i + 1] > END_N)
		{
			moveFrom.first = -1;
			return moveFrom;
		}
	}
	moveFrom.first = abs(moveInput[1] - END_N);
	moveFrom.second = moveInput[0] - START_L;
	moveTo.first = abs(moveInput[3] - END_N);
	moveTo.second = moveInput[2] - START_L;
	return moveFrom;
}


/**
 * Function that build the board.
 */
void buildBoard()
{

	int i = 0, j =  0;
	//first and last rows.
	board[i][j] =  new Rook(BLACK);
	board[i][j + 1] = new Knight(BLACK);
	board[i][j + 2] = new Bishop(BLACK);
	board[i][j + 3] = new Queen(BLACK);
	board[i][j + 4] = new King(BLACK);
	board[i][j + 5] = new Bishop(BLACK);
	board[i][j + 6] = new Knight(BLACK);
	board[i][j + 7] = new Rook(BLACK);
	board[TABLE_SIZE - 1][j] = new Rook(WHITE);
	board[TABLE_SIZE - 1][j + 1] = new Knight(WHITE);
	board[TABLE_SIZE - 1][j + 2] = new Bishop(WHITE);
	board[TABLE_SIZE - 1][j + 3] = new Queen(WHITE);
	board[TABLE_SIZE - 1][j + 4] = new King(WHITE);
	board[TABLE_SIZE - 1][j + 5] = new Bishop(WHITE);
	board[TABLE_SIZE - 1][j + 6] = new Knight(WHITE);
	board[TABLE_SIZE - 1][j + 7] = new Rook(WHITE);
	//second and pre-last rows.
	for(; i < TABLE_SIZE; i++)
	{
		board[j + 1][i] = new Pawn(BLACK);
		board[TABLE_SIZE - 2][i] = new Pawn(WHITE);
	}
	//all the rest - empty cells.
	for(i = 2; i < 4; i++)
	{
		for(j = 0; j < TABLE_SIZE; j++)
		{
			board[i][j] = new Player();
			board[TABLE_SIZE - 1 - i][j] = new Player();

		}
	}
	//set locations to the players.
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < TABLE_SIZE; j++)
		{
			board[i][j]->location.first = i;
			board[i][j]->location.second = j;
			board[TABLE_SIZE - 1 - i][j]->location.first = TABLE_SIZE - 1 - i;
			board[TABLE_SIZE - 1- i][j]->location.second = j;
		}
	}
}


/**
 * Helper function for printing the board. Add colors to players on board.
 */
string toString(int i, int j)
{
	ostringstream temp;
	temp << board[i][j]->getColor();
	return temp.str();
}


/**
 * Function that print the board.
 */
void printBoard()
{

	cout << "  ABCDEFGH\n\n";
	for(int i = 0; i < TABLE_SIZE; i++)
	{
		int cnt = (TABLE_SIZE - i);
		if(i % 2 != 0)
		{

			cout << cnt;
			cout << " \33[" << toString(i, 0) << ";42m" << board[i][0]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 1) << ";46m" << board[i][1]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 2) << ";42m" << board[i][2]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 3) << ";46m" << board[i][3]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 4) << ";42m" << board[i][4]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 5) << ";46m" << board[i][5]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 6) << ";42m" << board[i][6]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 7) << ";46m" << board[i][7]->graphics() << "\33[0m ";
			cout << cnt << endl;
		}
		else
		{
			cout << cnt;
			cout << " \33[" << toString(i, 0) << ";46m" << board[i][0]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 1) << ";42m" << board[i][1]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 2) << ";46m" << board[i][2]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 3) << ";42m" << board[i][3]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 4) << ";46m" << board[i][4]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 5) << ";42m" << board[i][5]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 6) << ";46m" << board[i][6]->graphics() << "\33[0m";
			cout << "\33[" << toString(i, 7) << ";42m" << board[i][7]->graphics() << "\33[0m ";
			cout << cnt << endl;
		}
	}
	cout << "\n  ABCDEFGH\n\n";
}


/**
 * Function to win the game. If the king don't have a safe cell to go - there is a Mate and the
 * game are done.
 */
bool mate(pair<int, int> loc)
{
	int directions[TABLE_SIZE * 2] = {-1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};
	for(int i = 0; i < TABLE_SIZE * 2; i += 2)
	{
		if(loc.first + directions[i] < TABLE_SIZE && loc.first + directions[i] >= 0 &&
		   loc.second + directions[i + 1] < TABLE_SIZE && loc.second + directions[i + 1] >= 0 &&
		   (board[loc.first][loc.second]->getColor() !=
		   board[loc.first + directions[i]][loc.second + directions[i + 1]]->getColor()) &&
		   !threat(loc.first + directions[i], loc.second + directions[i + 1],
		   board[loc.first][loc.second]->getColor()))
		{
			return false;
		}
	}
	return true;
}



/**
 * Function that check if the user can make his move, and if it all legal - shell make it.
 */
bool play(pair<int, int> location, int teamColor, pair<int, int> kingLoc)
{
	//remains in the table and doesn't have my tool in destination.
	if(moveTo.first >= TABLE_SIZE || moveTo.first < TABLE_BOTTOM || moveTo.second >= TABLE_SIZE ||
	   moveTo.second < TABLE_BOTTOM || board[moveTo.first][moveTo.second]->getColor() ==
	   board[location.first][location.second]->getColor() ||
	   board[location.first][location.second]->getColor() == DEFUALT ||
	   board[location.first][location.second]->getColor() != teamColor)
	{
		return false;
	}
	bool canMove = false;
	//Checking validation. Check rook first because he have a different function.
	if(board[location.first][location.second]->getName() == 'R')
	{
		Player* tempR = board[location.first][location.second];
		Rook* rook = dynamic_cast<Rook*>(tempR);
		canMove = rook->validationRook();
		if(canMove)
		{
			if(board[location.first][location.second]->getColor() == WHITE)
			{
				whiteRookMoved = true;
			}
			else
			{
				blackRookMoved = true;
			}
		}
	}
	//Checking validation.
	else
	{
		canMove = board[location.first][location.second]->validation();
	}
	//case for Queen
	if(board[location.first][location.second]->getName() == 'Q')
	{
		Player* tempP = board[location.first][location.second];
		Queen* queen = dynamic_cast<Queen*>(tempP);
		canMove = (canMove || queen->validationRook());
	}

	Player* temp;
	if(canMove)
	{
		temp = board[moveTo.first][moveTo.second];
		delete board[moveTo.first][moveTo.second];
		board[moveTo.first][moveTo.second] = board[location.first][location.second];
		board[moveTo.first][moveTo.second]->location.first = moveTo.first;
		board[moveTo.first][moveTo.second]->location.second = moveTo.second;
		board[location.first][location.second] = new Player();
		//updates of rook and king moves, for the castling function
		if(board[moveTo.first][moveTo.second]->getName() == 'K')
		{
			if(teamColor == WHITE)
			{
				whiteKingLoc = moveTo;
				whiteKingMoved = true;
				kingLoc = whiteKingLoc;
			}
			else
			{
				blackKingLoc = moveTo;
				blackKingMoved = true;
				kingLoc = blackKingLoc;
			}
		}
		else if(board[moveTo.first][moveTo.second]->getName() == 'R')
		{
			if(teamColor == WHITE)
			{
				whiteRookMoved = true;
			}
			else
			{
				blackRookMoved = true;
			}
		}
	}
	else
	{
		return false;
	}
	//case of Check - user can move just the king
	if(threat(kingLoc.first, kingLoc.second, teamColor))
	{
		board[location.first][location.second] = board[moveTo.first][moveTo.second];
		board[location.first][location.second]->location.first = location.first;
		board[location.first][location.second]->location.second = location.second;
		board[moveTo.first][moveTo.second] = temp;
		if(board[location.first][location.second]->getName() == 'K')
		{
			if(teamColor == WHITE)
			{
				whiteKingLoc = location;
			}
			else
			{
				blackKingLoc = location;
			}
		}
		return false;
	}
	return true;
}

/**
 * Function that clean the board. Delete every cell.
 */
void cleanBoard()
{
	for(int i = 0; i < TABLE_SIZE; i++)
	{
		for (int j = 0; j < TABLE_SIZE; j++)
		{
			delete board[i][j];
		}
	}
}

/**
 * Main function for the program. runs the game between two users.
 */
int main()
{
	pair<int, int> moveFrom;
	pair<int, int> kingLoc;
	bool chek = false;
	string wUser, bUser, name, moveInput;
	cout << "Enter white player name:\n";
	getline(cin, wUser);
	cout << "Enter black player name:\n";
	getline(cin, bUser);
	cout << "\33[2J";
	buildBoard();
	int teamColor, countRound = 0;

	while(true)
	{
		//odd - black play
		if(countRound % 2 == 0)
		{
			teamColor = WHITE;
			name = wUser;
			kingLoc = whiteKingLoc;
			kingMoved = whiteKingMoved;
			rookMoved = whiteRookMoved;
		}
		else
		{
			teamColor = BLACK;
			name = bUser;
			kingLoc = blackKingLoc;
			kingMoved = blackKingMoved;
			rookMoved = blackRookMoved;
		}
		printBoard();
		if(chek)
		{
			if(mate(kingLoc))
			{
				if(name == bUser)
				{
					cout << wUser << " won!\n";
				}
				else
				{
					cout << bUser << " won!\n";
				}
				break;
			}
			cout << "\33[37;41mCheck!\33[0m" << endl;
		}
		cout << name << ": Please enter your move:\n";
		cin >> moveInput;
		moveFrom = parser(moveInput);
		bool round = play(moveFrom, teamColor, kingLoc);
		if(moveFrom == moveTo || moveFrom.first == -1 ||
		   (chek && (moveFrom.first != kingLoc.first || moveFrom.second != kingLoc.second))
		   || !round)
		{
			cout << "\33[37;41millegal move\33[0m" << endl;
		}
		else
		{
			if(board[moveTo.first][moveTo.second]->getName() == 'K')
			{
				chek = false;
			}
			if(threat(whiteKingLoc.first, whiteKingLoc.second, WHITE) ||
			   threat(blackKingLoc.first, blackKingLoc.second, BLACK))
			{
				chek = true;
			}
			countRound++;
		}
		cout << "\33[2J";
	}
	cleanBoard();
	return 0;
}
