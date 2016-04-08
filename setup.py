#!/usr/bin/env python
# coding: utf-8

from distutils.core import setup, Extension
import sys

v = sys.version_info

module = Extension(
    'SandScripthon',
    sources         = ['pal.c'],
    extra_link_args = ['-lpython%d.%d' % (v[0], v[1])],
)

setup (
    name        = 'SandScript',
    version     = '1.0.1',
    description = 'Sandvine SandScript extended with Python',
    ext_modules = [module],
)

