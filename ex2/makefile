.PHONY: all clean tar

chess.o: Player.h Bishop.h King.h Knight.h Pawn.h Queen.h Rook.h chess.cpp
	g++ -g -Wextra -Wall -Wvla -c chess.cpp

chess: chess.o
	g++ chess.o -o chess

all: chess

clean:
	rm -f *.o chess ex2.tar

tar: 
	tar cvf ex2.tar makefile Player.h Bishop.h King.h Knight.h Pawn.h Queen.h Rook.h chess.cpp
