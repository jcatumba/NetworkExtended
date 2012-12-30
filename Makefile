#
# Makefile
#

SUBDIRS = libnetworkx
SUBCLEAN = $(addsuffix .clean,$(SUBDIRS))
LIB = -L./libnetworkx -lnetworkx 
LINK = -Wl,-rpath,./libnetworkx
pkgconfig = `pkg-config --cflags --libs python`

networkx_try.bin: $(SUBDIRS) networkx_try.c
	gcc -o $@ networkx_try.c $(LINK) $(LIB) $(pkgconfig)

.PHONY: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) --directory=$@

.PHONY: clean $(SUBCLEAN) local
clean: $(SUBCLEAN) local

$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean

local:
	rm -f networkx_try.bin
