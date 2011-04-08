INCLUDES += -I../include

all:
	gcc -ggdb -g $(INCLUDES) tpsPCI429-4.c -o tpsPCI429-4

install:
	install -d $(DESTDIR)/usr/share/doc/pci429-4/test
	install -m 755 tpsPCI429-4 $(DESTDIR)/usr/share/doc/pci429-4/test

clean:
	-rm tpsPCI429-4
