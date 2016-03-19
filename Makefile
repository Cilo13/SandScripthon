all: build

build:
	python setup.py build

clean:
	python setup.py clean -a
	@rm -rf build

install: build
	install -m 0755 -d $(DESTDIR)/usr/local/sandvine/loadable
	install -m 0755 build/lib.*/*.so $(DESTDIR)/usr/local/sandvine/loadable
	install -m 0755 -d $(DESTDIR)/usr/local/sandvine/etc
	install -m 0444 SandScript.py $(DESTDIR)/usr/local/sandvine/etc
	install -m 0644 policy.py $(DESTDIR)/usr/local/sandvine/etc

rpm:
	@(cd rpm && ./make.bash)

.PHONY: rpm
