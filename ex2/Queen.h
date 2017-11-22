/*
 * Queen.h
 *
 *  Created on: Jan 6, 2015
 *      Author: omerom88
 */

#ifndef QUEEN_H_
#define QUEEN_H_
#define QUEEN "\u265B"
#include "Player.h"
using namespace std;


/**
 * Queen class. Inherent from Player.
 */
class Queen: public Player
{
public:
	Queen();
	/**
	 * Queen constructor with 1 params. Add to every queen the name and the team color.
	 * all the rest are inherited from Player.
	 */
	Queen(int teamColor);
	/**
	 * Queen constructor with 2 params. Special ctor for rook and bishop.
	 */
	Queen(char name , int teamColor);
	/**
	 * Function that return the queen string to print on screen.
	 */
	string graphics();
	/**
	 * Function that checks if the pawn move is legal. In that special case - checks
	 * the diagonal move for queen and bishop move.
	 */
	bool validation();
	/**
	 * Function that checks if the pawn move is legal. In that special case - checks
	 * the vertical/horizontal move for queen and rook move.
	 */
	bool validationRook();
	/**
	 * Queen destructor.
	 */
	~Queen(){};
};


/**
 * default constructor.
 */
Queen::Queen(){}


/**
 * Queen constructor with 1 params. Add to every queen the name and the team color.
 * all the rest are inherited from Player.
 */
Queen::Queen(int teamColor) : Player ('Q', teamColor)
{
}


/**
 * Queen constructor with 2 params. Special ctor for rook and bishop.
 */
Queen::Queen(char name, int teamColor) : Player (name, teamColor)
{
}


/**
 * Function that checks if the pawn move is legal. In that special case - checks
 * the diagonal move for queen and bishop move.
 */
bool Queen::validation()
{
	int row, colom;
	if(abs(this->location.first - moveTo.first) != abs(this->location.second - moveTo.second))
	{
		return false;
	}
	//up right
	if(this->location.first - moveTo.first > 0 && this->location.second - moveTo.second < 0)
	{
		row = -1;
		colom = 1;
	}
	//down right
	else if(this->location.first - moveTo.first < 0 && this->location.second - moveTo.second < 0)
	{
		row = 1;
		colom = 1;
	}
	//up left
	else if(this->location.first - moveTo.first > 0 && this->location.second - moveTo.second > 0)
	{
		row = -1;
		colom = -1;
	}
	//down left
	else if(this->location.first - moveTo.first < 0 && this->location.second - moveTo.second > 0)
	{
		row = 1;
		colom = -1;
	}
	//loop for checking possibilities
	int j = 1;
	for(int i = 1; i < abs(this->location.first - moveTo.first); i++)
	{
		if(board[this->location.first + (i * row)][this->location.second + (j * colom)]->getColor()
		   != DEFUALT)
		{
			return false;
		}
		j++;
	}
	return true;
}


/**
 * Function that checks if the pawn move is legal. In that special case - checks
 * the vertical/horizontal move for queen and rook move.
 */
bool Queen::validationRook()
{
	//check the destination cell first
	if (board[moveTo.first][moveTo.second]->getColor() != DEFUALT &&
		board[moveTo.first][moveTo.second]->getColor() == this->getColor())
	{
		return false;
	}
	bool side;
	int destenation, current, currentLoc, destenationLoc;
	//check vertical or horizontal
	if(this->location.second == moveTo.second)
	{
		currentLoc = this->location.first;
		destenationLoc = moveTo.first;
		side = false;
	}
	else if (this->location.first == moveTo.first)
	{
		currentLoc = this->location.second;
		destenationLoc = moveTo.second;
		side = true;
	}
	else
	{
		return false;
	}
	//left-right or up-down checker
	if(currentLoc < destenationLoc)
	{
		current = currentLoc;
		destenation = destenationLoc;
	}
	else
	{
		current = currentLoc;
		destenation = destenationLoc;
	}
	for (current = current + 1; current < destenation; current++)
	{
		if(side)
		{
			if (board[this->location.first][current]->getColor() != DEFUALT)
			{
				return false;
			}
		}
		else
		{
			if (board[current][this->location.second]->getColor() != DEFUALT)
			{
				return false;
			}
		}
	}
	return true;
}


/**
 * Function that return the queen string to print on screen.
 */
string Queen::graphics()
{
	return QUEEN;
}

#endif /* QUEEN_H_ */
