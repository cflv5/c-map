CC=gcc
CFLAGS=-W -Wall
SOURCES=$(wildcard *.c)

all:
	$(CC) $(CFLAGS) $(SOURCES)

map: map.c map.h
	$(CC) $(CFLAGS) -c map.c