/*
 * Bishop.h
 *
 *  Created on: Jan 6, 2015
 *      Author: omerom88
 */

#ifndef BISHOP_H_
#define BISHOP_H_
#define BISHOP "\u265D"
#include "Queen.h"
using namespace std;

/**
 * Bishop class. Inherent from queen.
 */
class Bishop: public Queen
{
public:
	Bishop(int teamColor);
	/**
	 * Function that return the bishop string to print on screen.
	 */
	string graphics();
	/**
	 * Bishop destructor.
	 */
	~Bishop(){};
};


/**
 * Book constructor. Send to Queen constructor to add name and team color.
 * all the rest are inherited from Player.
 */
Bishop::Bishop(int teamColor) : Queen('B', teamColor)
{
}


/**
 * Function that return the bishop string to print on screen.
 */
string Bishop::graphics()
{
	return BISHOP;
}

#endif /* BISHOP_H_ */
