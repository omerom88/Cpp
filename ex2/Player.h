/*
* Player.h
*
*  Created on: Jan 6, 2015
*      Author: omerom88
*/

#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <string>
using namespace std;
#define TABLE_SIZE 8
#define TABLE_BOTTOM 0
#define BLACK 30
#define WHITE 37
#define DEFUALT 0

static bool whiteRookMoved = false, blackRookMoved = false, rookMoved = false,
		whiteKingMoved = false, blackKingMoved = false, kingMoved = false;
/**
 * pair for holding the cell the player come from.
 */
static pair <int, int> moveTo(1, 1);


/**
 * Player class. the basic class to define a check player on the board.
 */
class Player
{
public:
	Player();
	/**
	 * Constructor with 2 params. Add to every player on the board the name and the color.
	 */
	Player(char _name, int _color);
	/**
	 * Function that return the player string to print on screen. on empty cell it will be "".
	 */
	virtual string graphics();
	/**
	 * Function that every children need to implement with his private restrictions.
	 */
	virtual bool validation();
	/**
	 * Player destructor.
	 */
	virtual ~Player();
	/**
	 * Getter for color protected data member.
	 */
	int getColor();
	/**
	 * Getter for name protected data member.
	 */
	int getName();
	pair <int, int> location;
protected:
	int _color;
	char _name;
};

//the board for the game
static Player* board[TABLE_SIZE][TABLE_SIZE];


/**
 * default constructor. for an empty cell.
 */
Player::Player()
{
	this->_color = DEFUALT;
	this->_name = 'n';
}

/**
 * Constructor with 2 params. Add to every player on the board the name and the color.
 */
Player::Player(char _name, int _color)
{
	this->_color = _color;
	this->_name = _name;
}


/**
 * Function that every children need to implement with his private restrictions.
 */
bool Player::validation()
{
	return false;
}

/**
 * Getter for color protected data member.
 */
int Player::getColor()
{
	return _color;
}


/**
 * Getter for name protected data member.
 */
int Player::getName()
{
	return _name;
}


/**
 * Function that return the player string to print on screen. on empty cell it will be "".
 */
string Player::graphics()
{
	return " ";
}


/**
 * Player destructor
 */
Player::~Player(){}

#endif /* PLAYER_H_ */
