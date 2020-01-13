# -*- Makefile -*-

#target: dependencies
# action

CC=gcc
AR=ar
OBJECTS_MAIN=TRIE.o
FLAGS= -Wall -g


all: frequency 
frequency: $(OBJECTS_MAIN)
	$(CC) $(FLAGS) -o frequency $(OBJECTS_MAIN)
TRIE.o: TRIE.c TRIE.h
	$(CC) $(FLAGS) -c TRIE.c
.PHONY: clean all 
clean:
	rm -f *.o