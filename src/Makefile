CC=g++
CFLAGS=-g -Wall -Werror -MP -MD
NAME=test
SRC= $(wildcard *.cpp)
OBJS= $(SRC:.cpp=.o)

.PHONY: all $(SUBDIRS)

all: $(SUBDIRS) $(NAME)

$(SUBDIRS):
	make -C $@

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< $(INCFLAGS)

clean:
	rm -rvf $(NAME) *.o *.d
