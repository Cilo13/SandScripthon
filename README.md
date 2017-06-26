# SandScript meets Python

SandScripthon is what we call it.

This repo contains the source code of a shared library for the Sandvine
Policy Engine that allows one to write subsystems in Python. It embeds a
Python runtime onto the policy engine during startup.

## Build and deploy

The shared library must be built on the same system architecture of
the policy engine, that is a freebsd-x64 for PTS 32000 or linux-x64
for SDE and PTS Virtual Series, and has been only tested with Python 2.

Make sure you have the python-dev packages and build it and install.

On Centos 7,

    yum-config-manager --enable repository CentOSPlus
    sed -i -e '/exclude=/d' /etc/yum.conf
    yum groupinstall "Development Tools"
    yum install python-devel
    make install
    systemctl restart svpts.service

This will install the shared library to /usr/local/sandvine/loadable
and the Python code to /usr/local/sandvine/etc. The only file you
care about, and can edit, is policy.py. Note that changes to policy.py
are only updated on a pts restart (not svreload).

See the policy.conf file, it uses functions exported by policy.py.

## Modules

You can place Python modules in either /usr/local/sandvine/loadable/python,
or /usr/local/sandvine/etc/
