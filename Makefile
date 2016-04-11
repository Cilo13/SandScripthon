export VERSION = 1.0.2
export GITCOMMIT = $(shell git rev-parse --short HEAD)
export CFLAGS = -DVERSION=\"$(VERSION)\" -DGITCOMMIT=\"$(GITCOMMIT)\"

all: build

build:
	python setup.py build

clean:
	python setup.py clean -a
	@rm -rf build *.rpm

install: build
	install -m 0755 -d $(DESTDIR)/usr/local/sandvine/loadable
	install -m 0755 build/lib.*/*.so $(DESTDIR)/usr/local/sandvine/loadable
	install -m 0755 -d $(DESTDIR)/usr/local/sandvine/etc
	install -m 0444 SandScript.py $(DESTDIR)/usr/local/sandvine/etc
	install -m 0644 policy.py $(DESTDIR)/usr/local/sandvine/etc
	install -m 0644 policy_test.py $(DESTDIR)/usr/local/sandvine/etc

rpm-release:
	hack/rpmbuild.sh .
