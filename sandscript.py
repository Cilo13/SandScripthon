#!/usr/bin/env python
# SandScripthon API. Do not edit.

"""
The sandscript module provides a Python API for exporting
Python functions to the Sandvine Policy Engine.
"""

class pal:
    """
    The pal object provides supported data types for
    Python functions exported to SandScript.
    """
    bool = 0
    str = 1
    int = 2
    float = 3
    ipaddr = 4

_func = []

def func(**kw):
    """
    func is a decorator that exports the decorated Python function to
    SandScript.

    Example:

        func(name="sum", args=(pal.int, pal.int), returns=pal.int):
        def sum(*args):
            return args[0] + args[1]

    See the sandscript.pal object for supported data types.

    If the decorated function causes an unhandled exception or returns
    None, the SandScript counterpart returns null regardless of the
    return data type.

    Because the exported function is run by the Policy Engine, it is
    expected to never block and return as quick as possible.
    """
    n = kw.get("name")
    a = kw.get("args")
    r = kw.get("returns")

    # TODO(afiori): validate args and return type

    def decor(f):
        _func.append((f, n, a, r))
        def wrapper(*args):
            return f(*args)
        return wrapper
    return decor
