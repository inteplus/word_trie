#!/usr/bin/env python3

from setuptools import Extension, setup
from Cython.Build import cythonize

setup(name='trie',
      version="0.0.1",
      description="A simple word trie module.",
      author=["Minh-Tri Pham"],
      ext_modules = cythonize(Extension(
          "trie",                                # the extension name
          sources=["trie.pyx", "wordtrie.cpp"], # the Cython source and
          # additional C++ source files
          libraries=["boost_serialization"],
          language="c++",                        # generate and compile C++ code
      )))
