# compile SDL project from cli like so:
#gcc -o test test.c `sdl-config --cflags --libs`

#CC = gcc
CC = g++
CXX = g++

CFLAGS=-ansi -pedantic -Wall
CFLAGS := $(shell sdl-config --cflags) -D_RASPI
LDFLAGS := $(shell sdl-config --libs)

all: micromod-sdl

clean:
        rm -f micromod micromod.exe stdout.txt stderr.txt *~
        rm -f micromod.o sdlplayer.o

micromod-sdl:
        $(CC) micromod.c sdlplayer.c -o micromod $(CFLAGS) $(LDFLAGS)
#        $(CC) $(CFLAGS) micromod.c sdlplayer.c -o micromod `sdl-config --cflags --libs`

micromod-w32:
        $(CC) $(CFLAGS) micromod.c w32player.c -o micromod -lwinmm