#
# Makefile for networkextended
#

SUBDIRS = src
SUBCLEAN = $(addsuffix .clean,$(SUBDIRS))
LIB = -L./lib -lnetworkx -lm
INCLUDE = -I./src/headers
LINK = -Wl,-rpath,./lib
pkgconfig = `pkg-config --cflags --libs python`
BUILD = build/networkextended.bin build/netext.bin

# --- Construct all things
.PHONY: all

all: $(BUILD)

build/networkextended.bin: $(SUBDIRS) src/NetworkExtended.c src/networkx.c src/headers/uthash.h src/headers/networkx.h src/headers/networkextended.h
	gcc -o $@ src/NetworkExtended.c $(LINK) $(LIB) $(INCLUDE) $(pkgconfig)

build/netext.bin: $(SUBDIRS) src/netext.y src/netext.lex src/headers/netext.h
	gcc -o $@ src/netext.tab.c src/lex.yy.c $(LINK) $(LIB) $(INCLUDE) $(pkgconfig)

# --- Construct all subdirs and debug option
.PHONY: $(SUBDIRS) debug

$(SUBDIRS):
	$(MAKE) --directory=$@

debug:
	gcc -g -o build/networkextended.bin src/NetworkExtended.c $(LINK) $(LIB) $(INCLUDE) $(pkgconfig)

# --- Clean all
.PHONY: clean $(SUBCLEAN)
clean: $(SUBCLEAN)

$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean
