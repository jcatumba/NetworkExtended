#
# Makefile
#

pkgconfig= `pkg-config --cflags --libs python`
SLIBRARIES= ../lib/libnetworkx.so
OBJECTS= ../lib/networkx.o
INCLUDE = -I./headers

$(SLIBRARIES): $(OBJECTS)
	gcc -shared -o $@ $<

../lib/networkx.o: networkx.c headers/networkx.h
	gcc -c -fPIC -o $@ $< $(INCLUDE) $(pkgconfig) 

clean:
	rm -f $(SLIBRARIES) $(OBJECTS)

#TODO: Add instructions to build tests and modules/netevo directories
