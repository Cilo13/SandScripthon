export VERSION = 1.0.4
export GITCOMMIT = $(shell git rev-parse --short HEAD)
export CFLAGS = -DVERSION=\"$(VERSION)\" -DGITCOMMIT=\"$(GITCOMMIT)\"

all: build

sandscript-library-interface/.git:
	git clone https://github.com/sandvine/sandscript-library-interface

build: sandscript-library-interface/.git pal.c
	python3 setup.py build

clean:
	python3 setup.py clean -a
	@rm -rf build *.rpm

install: build
	install -m 0755 -d $(DESTDIR)/usr/local/sandvine/loadable
	install -m 0755 build/lib.*/*.so $(DESTDIR)/usr/local/sandvine/loadable
	install -m 0755 -d $(DESTDIR)/usr/local/sandvine/etc
	install -m 0444 SandScript.py $(DESTDIR)/usr/local/sandvine/etc
	install -m 0644 policy.py $(DESTDIR)/usr/local/sandvine/etc
	install -m 0644 policy_test.py $(DESTDIR)/usr/local/sandvine/etc

rpm-release:
	mv ./build/lib.linux-x86_64-3.4/SandScripthon.cpython-34m.so ./build/lib.linux-x86_64-3.4/SandScripthon.so
	hack/rpmbuild.sh .
