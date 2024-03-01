CFLAGS = -Wall -Wextra -std=gnu11 -pedantic
all: test 

debug: CFLAGS += -g
debug: clean all

test: test.o Dict.o List.o Linkedlist.o
	cc -o test test.o Dict.o List.o Linkedlist.o

%.o: %.c
	cc $(CFLAGS) -c $<

clean:
	rm -f *.o
