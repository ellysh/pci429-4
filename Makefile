MAKEFLAGS += --no-print-directory

# Variables to build kernel modules in the dkms
MODULE_DIR=elcus/source
MODULE_NAME=$(shell cat dkms.conf | grep PACKAGE_NAME | \
              sed "s/PACKAGE_NAME=//" | sed 's/"//g')
MODULE_VERSION=$(shell cat dkms.conf | grep PACKAGE_VERSION | \
                 sed "s/PACKAGE_VERSION=//" | sed 's/"//g')
USRSRC_DIR=/usr/src/$(MODULE_NAME)-$(MODULE_VERSION)

all:
	make -C elcus/source all
	make -C elcus/test all

clean:
	make -C elcus/source clean
	make -C elcus/test clean

distclean:
	make -C elcus/source distclean
	make -C elcus/test clean

deb:
# Copy module source
	-sudo mkdir $(USRSRC_DIR)
	-sudo cp -R $(MODULE_DIR)/* $(USRSRC_DIR)
	-sudo cp dkms.conf $(USRSRC_DIR)/
# Remove .svn dirs
	find $(USRSRC_DIR) -type d -name '.svn' | sudo xargs -IDIR rm -Rf DIR
# Build modules in the dkms
	-sudo dkms add -m $(MODULE_NAME) -v $(MODULE_VERSION)
	-sudo dkms build -m $(MODULE_NAME) -v $(MODULE_VERSION)
	-sudo dkms mkdeb -m $(MODULE_NAME) -v $(MODULE_VERSION)
# Build modules, dev and sources packages
	dpkg-buildpackage -us -uc -rfakeroot
	$(MAKE) deb-collect

deb-collect:
	-mkdir deb
# Copy from dkms
	-cp -f /var/lib/dkms/$(MODULE_NAME)/$(MODULE_VERSION)/deb/* deb
# Copy from parent dir
	-mv -f ../$(MODULE_NAME)*.* deb

deb-clean:
	rm -Rf deb
# Remove from dkms
	-sudo dkms remove -m $(MODULE_NAME) -v $(MODULE_VERSION) --all
	-sudo rm -Rf $(USRSRC_DIR)

# driver installation:
install:
	make -C elcus/source DESTDIR=$(DESTDIR) install
	make -C elcus/test DESTDIR=$(DESTDIR) install

# library installation
install-dev:
	make -C elcus/include DESTDIR=$(DESTDIR) install
	make -C elcus/lib DESTDIR=$(DESTDIR) install
