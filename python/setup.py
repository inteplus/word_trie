#!/usr/bin/env python3

from setuptools import Extension, setup
from Cython.Build import cythonize

setup(ext_modules = cythonize(Extension(
    "wordtrie",                                # the extension name
    sources=["wordtrie.pyx", "wordtrie.cpp"], # the Cython source and
    # additional C++ source files
    language="c++",                        # generate and compile C++ code
)))
