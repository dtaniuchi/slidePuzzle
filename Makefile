PROGRAM = main
OBJS = main.o
CC = g++
CFLAGS = -Wall -O2

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $^

main.o: main.cpp
	$(CC) $(CFLAGS) -c $<

main.o: puzzle.h

clean:
	$(RM) $(PROGRAM) $(OBJS)
