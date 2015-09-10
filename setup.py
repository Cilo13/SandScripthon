#!/usr/bin/env python
# coding: utf-8

from distutils.core import setup, Extension
import sys

v = sys.version_info

module = Extension(
    'sandscripthon',
    sources         = ['pal.c'],
    extra_link_args = ['-lpython%d.%d' % (v[0], v[1])],
)

setup (
    name        = 'sandscript',
    version     = '1.0',
    description = 'SandScript meets Python',
    ext_modules = [module],
)

