/*
 * King.h
 *
 *  Created on: Jan 6, 2015
 *      Author: omerom88
 */

#ifndef KING_H_
#define KING_H_
#define KING "\u265A"
#include "Player.h"
using namespace std;

/**
 * Helper function to the function threat. Checks the first step on diagonal search.
 */
bool checkFirst(int i, int j , int rows, int addToI, int addToJ)
{
	if (i == rows)
	{
		if (board[i + addToI][j + addToJ]->getName() == 'K' ||
			board[i + addToI][j + addToJ]->getName() == 'P')
		{
			return true;
		}
	}
	return false;
}

/**
 * Threat function. Checks threats on a given cell in the board.
 */
bool threat(int rows, int coloms, int color)
{
	//check vertical threat - down
	if (rows + 1 <= TABLE_SIZE)
	{
		for (int i = rows + 1; i < TABLE_SIZE && board[i][coloms]->getColor() != color; i++)
		{
			//checks the first cell for threat from king and pawn.
			if (i == rows + 1 )
			{
				if (board[i][coloms]->getName() == 'K')
				{
					return true;
				}
				if (color == BLACK)
				{
					if ((board[i][coloms + 1]->getName() == 'P' && board[i][coloms + 1]->getColor() != color)
						|| (board[i][coloms - 1]->getName() == 'P' && board[i][coloms - 1]->getColor() != color))
					{
						return true;
					}
				}
			}
			if (board[i][coloms]->getColor() != DEFUALT)
			{
				if (board[i][coloms]->getName() == 'R' || board[i][coloms]->getName() == 'Q')
				{
					return true;
				}
				break;
			}
		}
	}
	//check vertical threat - up
	if (rows - 1 >= TABLE_BOTTOM)
	{
		for(int i = rows - 1; i >= TABLE_BOTTOM && board[i][coloms]->getColor() != color; i--)
		{
			//checks the first cell for threat from king and pawn.
			if (i == rows - 1)
			{
				if (board[i][coloms]->getName() == 'K')
				{
					return true;
				}
				if (color == WHITE)
				{
					if ((board[i][coloms + 1]->getName() == 'P' && board[i][coloms + 1]->getColor() != color)
						|| (board[i][coloms - 1]->getName() == 'P' && board[i][coloms - 1]->getColor() != color))
					{
						return true;
					}
				}
			}
			if (board[i][coloms]->getColor() != DEFUALT)
			{
				if (board[i][coloms]->getName() == 'R' || board[i][coloms]->getName() == 'Q')
				{
					return true;
				}
				break;
			}
		}
	}
	//check horizontal threat - right
	if (coloms + 1 <= TABLE_SIZE)
	{
		for (int j = coloms + 1; j < TABLE_SIZE && board[rows][j]->getColor() != color; j++)
		{
			if (j == coloms + 1)
			{
				if (board[rows][j]->getName() == 'K')
				{
					return true;
				}
			}
			if (board[rows][j]->getColor() != DEFUALT)
			{
				if (board[rows][j]->getName() == 'R' || board[rows][j]->getName() == 'Q')
				{
					return true;
				}
				break;
			}
		}
	}
	//check horizontal threat - left
	if (coloms - 1 >= TABLE_BOTTOM)
	{
		for (int j = coloms - 1; j >= TABLE_BOTTOM && board[rows][j]->getColor() != color; j--)
		{
			if (j == coloms - 1)
			{
				if (board[rows][j]->getName() == 'K')
				{
					return true;
				}
			}
			if (board[rows][j]->getColor() != DEFUALT)
			{
				if (board[rows][j]->getName() == 'R' || board[rows][j]->getName() == 'Q')
				{
					return true;
				}
				break;
			}
		}
	}
	//check the diagonal threats
	int listOpt[TABLE_SIZE] = {1, 1, 1, -1, -1, 1, -1, -1};
	for(int count = 0; count < 7 ; count += 2)
	{
		for(int i = rows + listOpt[count], j = coloms + listOpt[count + 1]; i < TABLE_SIZE &&
			j < TABLE_SIZE && i >= TABLE_BOTTOM && j >= TABLE_BOTTOM && board[i][j]->getColor()
			!= color; i += listOpt[count])
		{
			if (board[i][j]->getColor() != DEFUALT)
			{
				if (board[i][j]->getName() == 'B' || board[i][j]->getName() == 'Q')
				{
					return true;
				}
				break;
				if (checkFirst(i, j, rows, listOpt[count], listOpt[count + 1]))
				{
					return true;
				}
				break;
			}
			j += listOpt[count + 1];
		}

		//check knight threat
		if (rows + 2 * listOpt[count] < TABLE_SIZE && rows + 2 * listOpt[count] >= TABLE_BOTTOM &&
			coloms + 1 * (listOpt[count + 1]) < TABLE_SIZE && coloms + 1 * (listOpt[count + 1]) >=
			TABLE_BOTTOM)
		{
			if (board[rows + 2 * listOpt[count]][coloms + 1 * (listOpt[count + 1])]->getName() == 'k'
				&& board[rows + 2 * listOpt[count]][coloms + 1 * (listOpt[count + 1])]-> getColor() != color)
			{
				return true;
			}
			if (board[rows + 1 * listOpt[count]][coloms + 2 * listOpt[count + 1]]->getName() == 'k'
				&& board[rows + 2 * listOpt[count]][coloms + 1 * listOpt[count + 1]]-> getColor() != color)
			{
				return true;
			}
		}
	}
	return false;
}


/**
 * King class. inherent from Player.
 */

class King : public Player
{
public:
	King(int teamColor);
	/**
	 * Function that return the king string to print on screen.
	 */
	string graphics();
	/**
	 * Function that checks if the king move is legal.
	 */
	bool validation();
	/**
	 * Special move that the king have. Check the conditions for that move.
	 */
	bool castling();
	/**
	 * King detructor.
	 */
	~King(){};
};


/**
 * King constructor. Add to every king the name and the team color.
 * all the rest are inherited from Player.
 */
King::King(int teamColor) : Player ('K', teamColor)
{
}


/**
 * Special move that the king have. Check the conditions for that move.
 */
bool King::castling()
{
	//check if moved before
	if(kingMoved || rookMoved)
	{
		return false;
	}
	//loops for checking threats
	if (moveTo.second > this->location.second)
	{
		for(int i = this->location.second; i < TABLE_SIZE - 1; i++)
		{
			if((i != this->location.second && board[this->location.first][i]->getColor() != DEFUALT) ||
			   threat(this->location.first, i, this->getColor()))
			{
				return false;
			}
		}
	}
	else
	{
		for(int i = this->location.second; i > 1; i--)
		{
			if((i != this->location.second && board[this->location.first][i]->getColor() != DEFUALT) ||
			   threat(this->location.first, i, this->getColor()))
			{
				return false;
			}
		}
	}
	//move the rook
	if (moveTo.second > this->location.second)
	{
		board[this->location.first][this->location.second + 1] =
		    board[moveTo.first][moveTo.second + 1];
		board[this->location.first][this->location.second + 1]->location.second =
			this->location.second + 1;
		board[moveTo.first][moveTo.second + 1] = new Player();
	}
	else if (moveTo.second < this->location.second)
	{
		board[this->location.first][this->location.second - 1] =
			board[moveTo.first][moveTo.second - 2];
		board[this->location.first][this->location.second - 1]->location.second =
			this->location.second - 1;
		board[moveTo.first][moveTo.second - 2] = new Player();
	}
	return true;
}


/**
 * Function that checks if the king move is legal.
 */
bool King::validation()
{
	if(this->location.second == moveTo.second || this->location.second == moveTo.second + 1 ||
	   this->location.second == moveTo.second - 1)
	{
		if(this->location.first == moveTo.first + 1 || this->location.first == moveTo.first - 1 ||
		   this->location.first == moveTo.first)
		{
			return true;
		}
		return false;
	}
	//case of castling.
	else if ((this->location.second == moveTo.second + 2 ||
			 this->location.second == moveTo.second - 2) &&
			 this->location.first == moveTo.first)
	{
		if (!threat(this->location.first, this->location.second, this->getColor()) && castling())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


/**
 * Function that return the king string to print on screen.
 */
string King::graphics()
{
	return KING;
}

#endif /* KING_H_ */
