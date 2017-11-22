ListFiles = MasterMindPlay.cpp MasterMindSolver.cpp makefile
CC = g++ -Wall -Wextra -Wvla

.PHONY:	all clean

all:	clean mastermindplay mastermindsolver

mastermindplay:
	$(CC) MasterMindPlay.cpp -o mastermindplay

mastermindsolver:
	$(CC) MasterMindSolver.cpp -o mastermindsolver

clean:
	rm -f mastermindplay mastermindsolver
tar:
	tar cvf ex1.tar  $(ListFiles)
