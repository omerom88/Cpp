/*
* Knight.h
 *
 *  Created on: Jan 6, 2015
 *      Author: omerom88
 */


#ifndef KNIGHT_H_
#define KNIGHT_H_
#define KNIGHT "\u265E"
#include "Player.h"
using namespace std;

/**
 * Knight class. Inherent from Player.
 */
class Knight : public Player
{
public:
	Knight(int teamColor);
	/**
	 * Function that return the knight string to print on screen.
	 */
	string graphics();
	/**
	 * Function that checks if the knight move is legal.
	 */
	bool validation();
	/**
	 * Knight destructor.
	 */
	~Knight(){};
};


/**
 * Knight constructor. Add to every knight the name and the team color.
 * all the rest are inherited from Player.
 */
Knight::Knight(int teamColor) : Player('k', teamColor)
{
}


/**
 * Function that checks if the knight move is legal.
 */
bool Knight::validation()
{
	if(this->location.second == moveTo.second + 2 || this->location.second == moveTo.second - 2)
	{
		if(this->location.first == moveTo.first + 1 || this->location.first == moveTo.first - 1)
		{
			return true;
		}
	}
	if(this->location.first == moveTo.first + 2 || this->location.first == moveTo.first - 2)
	{
		if(this->location.second == moveTo.second + 1 || this->location.second == moveTo.second - 1)
		{
			return true;
		}
	}
	return false;
}


/**
 * Function that return the knight string to print on screen.
 */
string Knight::graphics()
{
	return KNIGHT;
}


#endif /* KNIGHT_H_ */
