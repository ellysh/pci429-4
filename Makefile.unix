#MAKEFLAGS=-s
MAKEFLAGS += --no-print-directory

all:
	make -C elcus/source all
	make -C elcus/test all
clean:
	make -C elcus/source clean
	make -C elcus/test clean
distclean:
	make -C elcus/source distclean
	make -C elcus/test clean
build:
	dpkg-buildpackage -rfakeroot
distrib: build
#	make-kpkg
configure:

# driver installation:
install:
	make -C elcus/source DESTDIR=$(DESTDIR) install
	make -C elcus/test DESTDIR=$(DESTDIR) install

# library installation
install_dev:
	make -C elcus/include DESTDIR=$(DESTDIR) install
	make -C elcus/lib DESTDIR=$(DESTDIR) install
