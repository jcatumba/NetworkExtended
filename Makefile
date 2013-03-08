#
# Makefile for networkextended
#

SUBDIRS = src
SUBCLEAN = $(addsuffix .clean,$(SUBDIRS))
LIB = -lm
LIBRARIES = lib/main.o lib/parserl.o lib/parsery.o lib/networkx.o lib/networkextended.o
INCLUDE = -I./src/headers
LINK = -Wl,-rpath,./lib
pkgconfig = `pkg-config --cflags --libs python`
BUILD = build/networkextended.bin

# --- Construct all things
.PHONY: all

all: $(BUILD)

build/networkextended.bin: $(SUBDIRS) $(LIBRARIES) 
	gcc -g -o $@ $(LIBRARIES) $(LINK) $(LIB) $(INCLUDE) $(pkgconfig)

# --- Construct all subdirs and debug option
.PHONY: $(SUBDIRS) debug

$(SUBDIRS):
	$(MAKE) --directory=$@

# --- Clean all
.PHONY: clean $(SUBCLEAN)
clean: $(SUBCLEAN)

$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean
