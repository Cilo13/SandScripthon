all: build

build:
	python setup.py build

clean:
	python setup.py clean -a

install: build
	install -m 0755 -d /usr/local/sandvine/loadable
	install -m 0755 build/lib.*/*.so /usr/local/sandvine/loadable
	install -m 0755 -d /usr/local/sandvine/etc
	install -m 0444 sandscript.py /usr/local/sandvine/etc
	install -m 0644 policy.py /usr/local/sandvine/etc
