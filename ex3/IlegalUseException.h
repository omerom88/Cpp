/*
 * IlegalUseException.h
 *
 *  Created on: Jan 26, 2015
 *      Author: omer rom
 */


#include<exception>
#include<string>
#include<iostream>
using namespace std;

/**
 * Matrices Size Exception class
 */
class IlegalUseException : public exception
{
public:
	/**
	 * override exception what method.
	 */
	virtual const char* what() const throw()
	{
		return "illegal use!!";
	}
};
