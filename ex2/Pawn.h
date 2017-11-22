/*
* Pawn.h
 *
 *  Created on: Jan 6, 2015
 *      Author: omerom88
 */

#ifndef PAWN_H_
#define PAWN_H_
#define PAWN "\u265F"
#include "Queen.h"
using namespace std;

/**
 * Pawn class. Inherent from Player.
 */
class Pawn : public Player
{
public:
	Pawn(int teamColor);
	/**
	 * Function that return the pawn string to print on screen.
	 */
	string graphics();
	/**
	 * Special case of pawn rich to the end of the board and become a queen.
	 */
	void switch2Queen();
	/**
	 * Function that checks if the pawn move is legal.
	 */
	bool validation();
	/**
	 * Pawn destructor.
	 */
	~Pawn(){};
};

/**
 * Pawn constructor. Add to every pawn the name and the team getColor().
 * all the rest are inherited from Player.
 */
Pawn::Pawn(int teamColor) : Player('P', teamColor)
{
}

/**
 * Special case of pawn rich to the end of the board and become a queen.
 */
void Pawn::switch2Queen()
{
	if(moveTo.first == TABLE_SIZE - 1 || moveTo.first == 0)
	{
		board[this->location.first][this->location.second] = new Queen(this->getColor());
	}
}

/**
 * Function that checks if the pawn move is legal.
 */
bool Pawn::validation()
{
	int direction;
	if(this->getColor() == BLACK)
	{
		direction = 1;
	}
	else
	{
		direction = -1;
	}
	if(this->location.second == moveTo.second)
	{
		if(this->location.first +  direction == moveTo.first &&
		   board[moveTo.first][moveTo.second]->getColor() == DEFUALT)
		{
			this->switch2Queen();
			return true;
		}
		//check conditions for switching to queen
		else if((this->location.first == TABLE_SIZE - 2 ||  this->location.first == 1) &&
				this->location.first + 2 * direction == moveTo.first &&
				board[this->location.first + direction][this->location.second]->getColor() == DEFUALT
				&& board[moveTo.first][moveTo.second]->getColor() == DEFUALT)
		{
			this->switch2Queen();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if((this->location.second - 1  == moveTo.second ||
		   this->location.second + 1  == moveTo.second) &&
		   (this->location.first +  direction  == moveTo.first))
		{
			//check conditions for switching to queen
			if(board[moveTo.first][moveTo.second]->getColor() != this->getColor() &&
			   board[moveTo.first][moveTo.second]->getColor() != DEFUALT)
			{
				switch2Queen();
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
}


/**
 * Function that return the pawn string to print on screen.
 */
string Pawn::graphics()
{
	return PAWN;
}


#endif /* PAWN_H_ */
