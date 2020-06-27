#!/usr/bin/env python3

from setuptools import Extension, setup
from Cython.Build import cythonize

setup(ext_modules = cythonize(Extension(
    "trie",                                # the extension name
    sources=["trie.pyx", "wordtrie.cpp"], # the Cython source and
    # additional C++ source files
    language="c++",                        # generate and compile C++ code
)))
