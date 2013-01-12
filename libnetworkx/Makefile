#
# Makefile for libnetworkx
#

pkgconfig= `pkg-config --cflags --libs python`
SLIBRARIES= libnetworkx.so
OBJECTS= networkx_load.o

$(SLIBRARIES): $(OBJECTS)
	gcc -shared -o $@ $<

networkx_load.o: networkx_load.c networkx_load.h
	gcc -c -fPIC -o $@ $< $(pkgconfig)

clean:
	rm -f $(SLIBRARIES) $(OBJECTS)
