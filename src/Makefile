#
# Makefile
#

pkgconfig= `pkg-config --cflags --libs python`
LIBRARIES= ../bin/libs/networkx.o ../bin/libs/networkextended.o ../bin/libs/parserl.o ../bin/libs/parsery.o ../bin/libs/main.o
OBJECTS= ../bin/libs/networkx.o
INCLUDE = -I./headers

.PHONY: all

all: $(LIBRARIES)

../bin/libs/networkx.o: networkx.c headers/networkx.h
	gcc -g -c $< -o $@ $(INCLUDE) $(pkgconfig) 

../bin/libs/networkextended.o: networkextended.c headers/networkextended.h headers/parser.h parser.tab.c
	gcc -g -c $< -o $@ $(INCLUDE) $(pkgconfig)

../bin/libs/parserl.o: lex.yy.c
	gcc -g -c lex.yy.c -o $@ $(INCLUDE) $(pkgconfig)

lex.yy.c: parser.lex parser.tab.c
	flex parser.lex

../bin/libs/parsery.o: parser.tab.c
	gcc -g -c parser.tab.c -o $@ $(INCLUDE) $(pkgconfig)

parser.tab.c: parser.y headers/parser.h
	bison --defines=headers/parser.tab.h parser.y

../bin/libs/main.o: main.c headers/main.h
	gcc -g -c $< -o $@ $(INCLUDE) $(pkgconfig)

clean:
	rm -f ../bin/libs/*
	rm -f lex.yy.c
	rm -f parser.tab.c
	rm -f headers/parser.tab.h

#TODO: Add instructions to build tests and modules/netevo directories
