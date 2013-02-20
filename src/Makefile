#
# Makefile
#

pkgconfig= `pkg-config --cflags --libs python`
SLIBRARIES= ../lib/libnetworkx.so
OBJECTS= ../lib/networkx.o
INCLUDE = -I./headers

../lib/networkx.o: networkx.c headers/networkx.h
	gcc -g -c $< -o $@ $(INCLUDE) $(pkgconfig) 

../lib/networkextended.o: networkextended.c headers/networkextended.h
	gcc -g -c $< -o $@ $(INCLUDE) $(pkgconfig)

../lib/parserl.o: lex.yy.c
	gcc -g -c lex.yy.c -o $@

lex.yy.c: parser.lex parser.tab.c
	flex parser.lex

../lib/parsery.o: parser.tab.c
	gcc -g -c parser.tab.c -o $@

parser.tab.c: parser.y headers/netwokextended.h
	bison --defines=headers/parser.tab.h parser.y

main.o: main.c
	gcc -g -c $< -o $@

clean:
	rm -f ../lib/*

#TODO: Add instructions to build tests and modules/netevo directories
