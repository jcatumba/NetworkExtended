#
# Makefile for networkextended
#

SUBDIRS = src
SUBCLEAN = $(addsuffix .clean,$(SUBDIRS))
LIB = -lm
LIBRARIES = bin/libs/main.o bin/libs/parserl.o bin/libs/parsery.o bin/libs/networkx.o bin/libs/networkextended.o
INCLUDE = -I./src/headers
LINK = -Wl,-rpath,./bin/libs
pkgconfig = `pkg-config --cflags --libs python`
BUILD = bin/networkextended.bin

# --- Construct all things
.PHONY: all

all: $(BUILD)

bin/networkextended.bin: $(SUBDIRS) $(LIBRARIES) 
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
