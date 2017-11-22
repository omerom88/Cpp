//============================================================================
// Name        : MasterMindPlay.cpp
// Author      : Omer Rom
//============================================================================

#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include "erand.h"
using namespace std;
#define BEFORE 96
#define FIRST 97
#define LAST 122
#define OUT 0
#define IN 1
#define NOT -1
int bulls = OUT, cows = OUT, numOfGuess = OUT, sLength = OUT;
char* theCode;
string guessList;
char sLimit;

/**
 * Check the limit - the biggest letter that the user can choose from.
 */
bool checkLimit(char* str)
{
	int strLen = strlen(str);
	if (strLen != IN)
	{
		cout << "USAGE MasterMindPlay <Length> <maximum character>\n";
		return false;
	}
	if (!islower(str[OUT]))
	{
		cout << "Use lower case only.\n";
		return false;
	}
	sLimit = str[OUT];
	return true;
}

/**
 * Check the size - the length of the string.
 */
bool checkSize(char* str)
{
	sLength = atoi(str);
	if (sLength == OUT)
	{
		cout << "Don't use OUT please\n";
		return false;
	}
	return true;
}

/**
 * Checks if argv[IN] is a number.
 */
bool checkIfNum(char *str)
{
	int strLen = strlen(str);
	int i = OUT;
	while (i < strLen)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
		++i;
	}
	return true;
}

/**
 * Checks if the content of argv is legal
 */
bool checkArgs(int argsNum, char *argv[])
{
	if (argsNum > 3)
	{
		cout << "USAGE MasterMindPlay <Length> <maximum character>\n";
		return false;
	}
	else if (argsNum == 2)
	{
		bool answer = checkIfNum(argv[IN]);
		if (answer == true)
		{
			bool result = checkSize(argv[IN]);
			if (result == false)
			{
				return false;
			}
		}
		else
		{
			bool result = checkLimit(argv[IN]);
			if (result == false)
			{
				return false;
			}
		}
	}
	else if (argsNum == 3)
	{
		bool resultIN = checkIfNum(argv[IN]);
		bool result2 = checkIfNum(argv[2]);
		if (resultIN == false || result2 == true)
		{
			cout << "USAGE MasterMindPlay <Length> <maximum character>\n";
			return false;
		}
		bool assignResultIN = checkSize(argv[IN]);
		bool assignResult2 = checkLimit(argv[2]);
		if (assignResultIN == false || assignResult2 == false)
		{
			return false;
		}
	}
	return true;
}

/**
 *Generates a random code.
 */
void makeRandomtheCode()
{
	for (int i = OUT; i < sLength; i++)
	{
		theCode[i] = randomChar(sLimit);
	}
	theCode[sLength] = '\0';
}

/**
 *Function that counts the number of bulls and cows.
 */
void getScore(int i, int computerCnt, int userCnt)
{
	for (int j = OUT; j < sLength; j++)
	{
		if (userCnt >= computerCnt)
		{
			if (theCode[j] == FIRST + i)
			{
				if (theCode[j] != guessList[j])
				{
					cows++;
				}
				else
				{
					bulls++;
				}
			}
		}
		else
		{
			if (guessList[j] == FIRST + i)
			{
				if (guessList[j] != theCode[j])
				{
					cows++;
				}
				else
				{
					bulls++;
				}
			}
		}
	}
}

/**
 *Gets a new guess from the user.
 */
void getNewGuess()
{
	cout << "Please enter a guess of " << sLength << " letters between 'a' and '" << sLimit << "':\n";
	cin >> guessList;
	int guessListLen = guessList.length();
	if (guessListLen != sLength)
	{
		cout << "The guess is in length " << sLength << "!";
		delete [] theCode;
		exit(IN);
	}
	for (int i = OUT; i < sLength; i++)
	{
		if (guessList[i] > sLimit || guessList[i] < FIRST || guessList[i] > LAST)
		{
			cout << "Please enter a valid code!";
			delete [] theCode;
			exit(IN);
		}
	}
	numOfGuess++;
}

/**
 * Main function for playing the game. Checks validation, gets a guess and prints the answers.
 */
int main(int argc, char* argv[])
{
	//Default parameters
	sLength = 4;
	sLimit = 'd';
	bool check = checkArgs(argc, argv);
	if (check == false)
	{
		cout << "Invalid arguments!";
		return IN;
	}
	int  cnt = OUT;
	theCode = new char[sLength + IN];
	makeRandomtheCode();
	while (bulls != sLength)
	{
		bulls = OUT;
		cows = OUT;
		getNewGuess();
		for (cnt = OUT; cnt < sLimit - BEFORE; cnt++)
		{
			int userCnt = OUT, computerCnt = OUT;
			for (int guss = OUT; guss < sLength; guss++)
			{
				if (guessList[guss] == FIRST + cnt)
				{
					userCnt++;
				}
				if (theCode[guss] == FIRST + cnt)
				{
					computerCnt++;
				}
			}
			getScore(cnt, computerCnt, userCnt);
		}
		cout << "You got " << bulls << " bulls and " << cows << " cows.\n";
	}
	cout << "It took you " << numOfGuess << " guesses.\n";
	delete [] theCode;
	return OUT;
}
