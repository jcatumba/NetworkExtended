#
# Makefile for networkextended
#

SUBDIRS = src build lib
SUBCLEAN = $(addsuffix .clean,$(SUBDIRS))
LIB = -L./lib -lnetworkx -lnetworkextended
LINK = -Wl,-rpath,./lib
pkgconfig = `pkg-config --cflags --libs python`

build/networkextended.bin: $(SUBDIRS) src/NetworkExtended.c src/networkx.c src/headers/uthash.h src/headers/networkx.h src/headers/networkextended.h
	gcc -o $@ NetworkExtended.c $(LINK) $(LIB) $(pkgconfig)

.PHONY: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) --directory=$@

.PHONY: clean $(SUBCLEAN)
clean: $(SUBCLEAN)

$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean
