#
# Makefile for networkextended
#

SUBDIRS = src
SUBCLEAN = $(addsuffix .clean,$(SUBDIRS))
LIB = -L./lib -lnetworkx
INCLUDE = -I./src/headers
LINK = -Wl,-rpath,./lib
pkgconfig = `pkg-config --cflags --libs python`

build/networkextended.bin: $(SUBDIRS) src/NetworkExtended.c src/networkx.c src/headers/uthash.h src/headers/networkx.h src/headers/networkextended.h
	gcc -o $@ src/NetworkExtended.c $(LINK) $(LIB) $(INCLUDE) $(pkgconfig)

.PHONY: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) --directory=$@

.PHONY: clean $(SUBCLEAN)
clean: $(SUBCLEAN)

$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean
