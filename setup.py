#!/usr/bin/env python3
# coding: utf-8

from distutils.core import setup, Extension
import sys

v = sys.version_info

module = Extension(
    'SandScripthon',
    sources         = ['pal.c'],
    extra_link_args = ['-lpython%d.%dm' % (v[0], v[1])],
)

setup (
    name        = 'SandScript',
    version     = '1.0.2',
    description = 'Sandvine SandScript extended with Python',
    ext_modules = [module],
)

