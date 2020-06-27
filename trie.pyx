# distutils: language = c++
# cython: language_level = 3

from wordtrie cimport Trie_c, load_from_file, save_to_file

cdef class Trie:
    cdef Trie_c c_trie

    def __cinit__(self):
        self.c_trie = Trie_c()

    def total_count(self):
        return self.c_trie.total_count()

    def num_nodes(self):
        return self.c_trie.num_nodes()

    def insert(self, str word, int count=1):
        self.c_trie.insert(word.encode(), count)

    def prob(self, str word):
        return self.c_trie.prob(word.encode())

    def cond_prob(self, str word):
        return self.c_trie.cond_prob(word.encode())


def load(str filepath):
    trie = Trie()
    load_from_file(filepath.encode(), trie.c_trie)
    return trie

def save(str filepath, Trie trie):
    save_to_file(filepath.encode(), trie.c_trie)
