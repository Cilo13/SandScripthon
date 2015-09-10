# SandScript meets Python

SandScripthon is what we call it.

This repo contains the source code of a shared library for the policy
engine that allows one to write subsystems in Python. It embeds a
Python runtime onto the policy engine during startup.

This is a fork of [palso](https://git.sandvine.com/afiori/palso).

## Build and deploy

The shared library must be built on the same system architecture of
the policy engine, that is a freebsd-x64 for PTS or linux-x64 for SDE,
and has been only tested with Python 2.

Make sure you have the python-dev packages and build it and install:

	make install

This will install the shared library to /usr/local/sandvine/loadable
and the Python code to /usr/local/sandvine/etc. The only file you
care about, and can edit, is policy.py.

See the policy.conf file, it uses functions exported by policy.py.
