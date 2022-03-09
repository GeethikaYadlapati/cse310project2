OBJS0MAIN   = main.o defns.o
SOURCE0MAIN = main.cpp
HEADER0MAIN =
OUT0MAIN    = earnings

CC       = g++
FLAGS    = -g -c -Werror -Wall
#-Wall -Wextra -pedantic-errors

all: earnings

earnings: $(SOURCE0MAIN) $(LFLAGS)
	$(CC) -g $(SOURCE0MAIN) -o $(OUT0MAIN)

defns.o: defns.h
	$(CC) $(FLAGS) defns.h

clean:
	rm -f $(OBJS0MAIN) $(OUT0MAIN)
	