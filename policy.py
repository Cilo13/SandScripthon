#!/usr/bin/env python
#
# Example SandScript functions implemented in Python

from sandscript import pal
from sandscript import func

@func(name="Example.Field", args=(pal.str, pal.str, pal.int), returns=pal.str)
def Field(*args):
    text, delim, n = args
    try:
        return text.split(delim)[n]
    except:
        return None

@func(name="Example.Sum", args=(pal.int, pal.int), returns=pal.int)
def Sum(*args):
    return args[0] + args[1]
