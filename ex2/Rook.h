/*
 * Rook.h
 *
 *  Created on: Jan 6, 2015
 *      Author: omerom88
 */

#ifndef ROOK_H_
#define ROOK_H_
#define ROOK "\u265C"
#include "Queen.h"
using namespace std;


/**
 * Queen class. Inherent from Queen.
 */
class Rook: public Queen
{
public:
	Rook(int teamColor);
	/**
	 * Function that return the rook string to print on screen.
	 */
	string graphics();
	/**
	 * Rook destructor.
	 */
	~Rook(){};
};

/**
 * Rook constructor. Send to Queen constructor to add name and team color.
 * all the rest are inherited from Player.
 */
Rook::Rook(int teamColor) : Queen('R', teamColor)
{
}

/**
 * Function that return the rook string to print on screen.
 */
string Rook::graphics()
{
	return ROOK;
}

#endif /* ROOK_H_ */
