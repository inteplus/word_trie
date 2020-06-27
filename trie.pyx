# distutils: language = c++

from wordtrie cimport Trie_c

def check_str(word):
    if not isinstance(word, str):
       raise ValueError("Expected word '{}' to be a string, received a {}.".format(word, type(word)))

cdef class Trie:
    cdef Trie_c c_trie

    def __cinit__(self):
        self.c_trie = Trie_c()

    def total_count(self):
        return self.c_trie.total_count()

    def num_nodes(self):
        return self.c_trie.num_nodes()

    def insert(self, word, count=1):
        check_str(word)
        self.c_trie.insert(word, count)

    def prob(self, word):
        check_str(word)
        return self.c_trie.prob(word)

    def cond_prob(self, word):
        check_str(word)
        return self.c_trie.cond_prob(word)
