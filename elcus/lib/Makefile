INSTALL        = install -m 644 -p
INSTALLDIR     = install -m 755 -d
LIBPCI429_PC   = pci429-4.pc
LIBPCI429_CONF = pci429-4.conf

all:

install:
	$(INSTALLDIR) $(DESTDIR)/etc/ld.so.conf.d
	$(INSTALLDIR) $(DESTDIR)/usr/lib/pkgconfig
	$(INSTALL) $(LIBPCI429_CONF) $(DESTDIR)/etc/ld.so.conf.d
	$(INSTALL) $(LIBPCI429_PC) $(DESTDIR)/usr/lib/pkgconfig

clean:
distclean:
