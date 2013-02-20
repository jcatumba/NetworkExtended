#
# Makefile for networkextended
#

SUBDIRS = src
SUBCLEAN = $(addsuffix .clean,$(SUBDIRS))
LIB = -lnetworkx -lm
INCLUDE = -I./src/headers
LINK = -Wl,-rpath,./lib
pkgconfig = `pkg-config --cflags --libs python`
BUILD = build/networkextended.bin

# --- Construct all things
.PHONY: all

all: $(BUILD)

build/networkextended.bin: $(SUBDIRS) lib/*.o
	gcc -g -o $@ lib/*.o $(LINK) $(LIB) $(INCLUDE) $(pkgconfig)

# --- Construct all subdirs and debug option
.PHONY: $(SUBDIRS) debug

$(SUBDIRS):
	$(MAKE) --directory=$@

# --- Clean all
.PHONY: clean $(SUBCLEAN)
clean: $(SUBCLEAN)

$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean
