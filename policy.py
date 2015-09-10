#!/usr/bin/env python
#
# Example policy subsystem.

from sandscript import pal
from sandscript import func

@func(name="foobar.func1", args=(pal.str, pal.str, pal.int), returns=pal.str)
def a(*args):
    text, delim, n = args
    try:
        return text.split(delim)[n]
    except:
        return None

@func(name="foobar.func2", args=(pal.int, pal.int), returns=pal.int)
def b(*args):
    return args[0] + args[1]
