#!/usr/bin/env python

"""
Copyright 2015 Sandvine Incorporated ULC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""

# SandScripthon API. Do not edit.

"""
The SandScript module provides a Python API for exporting
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

        @func(name="sum", args=(pal.int, pal.int), returns=pal.int):
        def sum(*args):
            return args[0] + args[1]

    See the SandScript.pal object for supported data types.

    If the decorated function causes an unhandled exception or returns
    None, the SandScript counterpart returns null regardless of the
    return data type. The name of the decorated Python function is
    ignored, meaning it can be named to anything.

    Because the exported function is run by the Policy Engine, it is
    expected to never block and return as quick as possible.

    Use of syslog in Python functions write to svlog automatically.
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
