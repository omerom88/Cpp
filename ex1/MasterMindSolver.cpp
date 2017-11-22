//============================================================================
// Name        : MasterMindPlay.cpp
// Author      : Omer Rom
//============================================================================

#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <typeinfo>
#define FIRST 97
#define SECONDE 2
#define OUT 0
#define IN 1
#define NOT -1
#define NULL_IN_LIST '\0'
using namespace std;
char* optionList;
char* guessList;
int sLength, parmGussList = OUT, optionSize, guessCounter = IN, keep = IN, tempo, counterO = OUT;
unsigned int counterC = OUT;
string cowsList;
pair <int, int> bulls;
pair <int, int> cows;
pair <char, char> newChar;
char sLimit, oldChar, firstChar;


/**
 *print an error massage and gets out from the  program.
 */
void error()
{
	cout << "Please play by the roles!!";
	delete[] guessList;
	delete[] optionList;
	exit(1);
}

/**
 * Check the limit - the biggest letter that the user can choose from.
 */
bool checkLimit(char* str)
{
	int strLen = strlen(str);
	if (strLen != 1)
	{
		cout << "USAGE MasterMindPlay <Length> <maximum character>\n";
		return false;
	}
	if (!islower(str[0]))
	{
		cout << "Use lower case only\n";
		return false;
	}
	sLimit = str[0];
	return true;
}

/**
 * Check the size - the length of the string.
 */
bool checkSize(char* str)
{

	sLength = atoi(str);
	if (sLength == 0)
	{
		cout << "Don't use 0 please\n";
		return false;
	}
	return true;
}

/**
 * checks if argv[1] is a number.
 */
bool checkIfNum(char *str)
{
	sLimit = strlen(str);
	int i = 0;
	while (i < sLimit)
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
 * checks if the user gave a legal inputs.
 */
void checkInput()
{
	if (bulls.second + cows.second > sLength || bulls.second < 0 || cows.second < 0)
	{
		cout << "Please enter a legal input!!";
		delete[] guessList;
		delete[] optionList;
		exit(OUT);
	}
}

/**
 * checks if the content of argv is legal
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
		bool answer = checkIfNum(argv[1]);
		if (answer == true)
		{
			bool result = checkSize(argv[1]);
			if (result == false)
			{
				return false;
			}
		}
		else
		{
			bool result = checkLimit(argv[1]);
			if (result == false)
			{
				return false;
			}
		}
	}
	else if (argsNum == 3)
	{
		bool result1 = checkIfNum(argv[1]);
		bool result2 = checkIfNum(argv[2]);
		if (result1 == false || result2 == true)
		{
			cout << "USAGE MasterMindPlay <Length> <maximum character>\n";
			return false;
		}
		bool assignResult1 = checkSize(argv[1]);
		bool assignResult2 = checkLimit(argv[2]);
		if (assignResult1 == false || assignResult2 == false)
		{
			return false;
		}
	}
	return true;
}


/**
Function for initialize the pattern that we gonna build on it all
the guesses.
 */
void make()
{
	for (int i = OUT; i < optionSize + 1; i++)
	{
		for (int j = OUT; j < sLength; j++)
		{
			guessList[j] = optionList[i];
		}
		cout << "My guess is: " << guessList << "\n";
		cin >> bulls.second;
		cin >> cows.second;
		if(cin.fail())
		{
			cout << "Please enter a legal input!!";
			delete[] guessList;
			delete[] optionList;
			exit(OUT);
		}
		checkInput();
		firstChar = optionList[i];
		if (bulls.second == OUT && cows.second == OUT)
		{
			optionList[i] = NULL_IN_LIST;
			if(i == optionSize)
			{
				error();
			}
			continue;
		}
		else
		{
			//we don't want the letter of the pattern in the option list
			optionList[i] = NULL_IN_LIST;
			break;
		}
	}
}

/**
Function that check if we have a letter in the cow's list
 */
int checkCow(char candident)
{
	if (firstChar != candident)
	{
		int cowSize = cowsList.size();
		for (int i = OUT; i < cowSize; i++)
		{
			if (candident == cowsList[i])
			{
				return OUT;
			}
		}
		return IN;
	}
	else
	{
		return OUT;
	}
}

/**
The most important function of the program. Check's every new score
of bulls and cows and tells the 'solver' if to move on or stay in
the same cell.
 */
int checker(int newLetter)
{
	if (bulls.second > bulls.first)
	{
		//special case of switching two letters
		if (oldChar == guessList[parmGussList - IN] &&
			newChar.second == newChar.first && bulls.second == bulls.first + IN)
		{
			keep = OUT;
			return OUT;
		}
		else if (cows.second < cows.first)
		{
			//saving the old cow into cowlist
			if (checkCow(oldChar))
			{
				cowsList.push_back(oldChar);
				optionList[parmGussList] = NULL_IN_LIST;
			}
		}
		return IN;
	}
	else if (bulls.second == bulls.first)
	{
		if (cows.second > cows.first)
		{
			//saving the new cow, next guess in the same cell
			int checker = checkCow(newChar.second);
			if (checker)
			{
				cowsList.push_back(newChar.second);
				optionList[newLetter] = NULL_IN_LIST;
			}
			keep = OUT;
			return OUT;
		}
		else if (cows.second < cows.first)
		{
			//saving the old cow, next guess in the same cell
			int checker = checkCow(oldChar);
			if (checker)
			{
				cowsList.push_back(oldChar);
				optionList[parmGussList] = NULL_IN_LIST;
			}
			return OUT;
		}
		else
		{
			if (oldChar == guessList[parmGussList - IN])
			{
				guessList[parmGussList] = oldChar;
				return IN;
			}
			//special case of searching the pattern letter in the option list
			else if (oldChar != newChar.second && cows.second != OUT  && newChar.second !=
					 optionList[optionSize])
			{
				if (checkCow(newChar.second))
				{
					cowsList.push_back(newChar.second);
					optionList[newLetter] = NULL_IN_LIST;
				}
				return OUT;
			}
			else
			{
				keep = OUT;
				return OUT;
			}
		}
	}
	else
	{
		if (cows.second > cows.first)
		{
			guessList[parmGussList] = oldChar;
			if (checkCow(newChar.second))
			{
				cowsList.push_back(newChar.second);
				optionList[newLetter] = NULL_IN_LIST;
			}
			return IN;
		}
		else
		{
			//keeping the old cow
			guessList[parmGussList] = oldChar;
			return IN;
		}
	}
}

/**
Function that gets the new score for the string. Ask the user for the guess and add the
answer to the bulls and cows pairs.
 */
void getScore()
{
	bulls.first = bulls.second;
	cows.first = cows.second;
	std::cout << "My guess is: " << guessList << "\n";
	guessCounter++;
	cin >> bulls.second;
	cin >> cows.second;
	if(cin.fail())
	{
		cout << "Please enter a legal input!!";
		delete[] guessList;
		delete[] optionList;
		exit(OUT);
	}
	checkInput();
}

/**
Function that send a guess with letter from cows list to checker and decided what to do
with the answer that she received.
 */
int checkCowPlaese()
{
	//check if to move to the next letter
	if (checker(counterC))
	{
		if (parmGussList < sLength - IN)
		{
			parmGussList++;
			return IN;
		}
		else
		{
			counterC++;
			keep = OUT;
		}
	}
	else
	{
		counterC++;
	}
	return OUT;
}

/**
Function that send a guess with letter from option list to checker and decided what to do
with the answer that she received.
 */
int checkOptionPlaese()
{
	if (checker(counterO + IN))
	{
		if (parmGussList < sLength - IN)
		{
			parmGussList++;
			return IN;
		}
		else
		{
			return NOT;
		}
	}
	return OUT;
}

/**
Special case checker. In case we finished the optionList and the only
char we have left to check is the pattern letter(that doesn't exist in the optionList),
we fill the cell with the pattern letter and keep playing.
 */
int specialCaseChecker()
{
	if (counterO == optionSize - IN && bulls.second <= bulls.first)
	{
		if (cows.second > cows.first)
		{

			if (checkCow(oldChar))
			{
				cowsList.push_back(oldChar);
				optionList[counterO] = NULL_IN_LIST;
			}
		}
		guessList[parmGussList] = firstChar;
		parmGussList++;
		return IN;
	}
	return OUT;
}

/**
Function that called by the main, decide if needed to go over cows list or over the option
list, adding a new letter in the current cell, ask for score and send it to the 'checker'.
If there is an answer the func returns 1, otherwise 0.
 */
int solver()
{
	while (bulls.second != sLength)
	{
		//send to check with option from cowslist
		if (cowsList.size() != OUT)
		{
			counterC = OUT;
			unsigned int cowSize = cowsList.size();
			while (counterC < cowSize)
			{
				oldChar = guessList[parmGussList];
				//free the second place
				newChar.first = newChar.second;
				newChar.second = cowsList[counterC];
				guessList[parmGussList] = cowsList[counterC];
				getScore();
				if (checkCowPlaese())
				{
					break;
				}
			}
			//check if we've got a winner
			if (bulls.second == sLength)
			{
				return IN;
			}
			//check if we have more preferred letters to try before moving to optionList
			if (keep == IN || counterC != cowsList.size())
			{
				continue;
			}
		}
		//loop for option list
		for (counterO = OUT; counterO < optionSize; counterO++)
		{
			if (optionList[counterO + IN] != NULL_IN_LIST || counterO == optionSize - IN)
			{
				oldChar = guessList[parmGussList];
				newChar.first = newChar.second;
				newChar.second = optionList[counterO + IN];
				guessList[parmGussList] = optionList[counterO + IN];
				getScore();
				//another check of finish the game is needed here
				if (bulls.second == sLength)
				{
					return IN;
				}
				//check a special case
				if (specialCaseChecker())
				{
					break;
				}
				int tempo = (checkOptionPlaese());
				if (tempo == IN)
				{
					break;
				}
				else if (tempo == NOT)
				{
					continue;
				}
			}
		}
		continue;
	}
	return IN;
}

/**
Main function for the game. Received the length of the string and the limit char,
send for building the pattern, and ask the 'solver' if there is a solution or not.
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
	cout << "Please choose " << sLength << " letters in the range 'a' to "
			<< "'" << sLimit << "'" << "\n";
	guessList = new char[sLength + IN];
	guessList[sLength] = NULL_IN_LIST;
	optionSize = toascii(sLimit) - FIRST;
	optionList = new char[optionSize + IN];
	cowsList = "";
	char temp = FIRST;
	for (int i = OUT; i < optionSize + IN; i++)
	{
		optionList[i] = temp + i;
	}
	optionList[optionSize + 1] = NULL_IN_LIST;
	make();
	int winning = solver();
	delete[] guessList;
	delete[] optionList;
	if (winning)
	{
		cout << "I did it in " << guessCounter << " guesses!\n";
		return OUT;
	}
	return IN;
}
