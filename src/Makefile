CC=g++
CFLAGS=-g -Wall -Werror
NAME=test
SRC= $(wildcard *.cpp)
OBJS= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rvf $(NAME) *.o
