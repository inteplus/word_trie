# distutils: language = c++
# cython: language_level = 3

from wordtrie cimport Trie_c, load_from_file, save_to_file
import os.path

cdef class Trie:
    '''A simple word trie implemented in C++.'''

    cdef Trie_c c_trie

    def __cinit__(self):
        self.c_trie = Trie_c()

    def total_count(self):
        '''Returns the total number of word counts.'''
        return self.c_trie.total_count()

    def num_nodes(self):
        '''Returns the total number of nodes of the trie.'''
        return self.c_trie.num_nodes()

    def insert(self, str word, int count=1):
        '''Inserts a word with frequency/count.

        Parameters
        ----------
        word : str
            The word to be inserted.
        count : int
            The number of times the word occurs.
        '''        
        self.c_trie.insert(word.encode(), count)

    def prob(self, str word):
        '''Returns the probability that the word occurs.

        Parameters
        ----------
        word : str
            The query word.

        Returns
        -------
        double
            The probability that the word occurs.
        '''
        return self.c_trie.prob(word.encode())

    def cond_prob(self, str word):
        '''Returns the probability that the word occurs, given that everything except the last character has been given.

        Parameters
        ----------
        word : str
            The query word.

        Returns
        -------
        double
            The probability that the word occurs.
        '''
        return self.c_trie.cond_prob(word.encode())

    # ----- serialization -----

    @staticmethod
    def from_file(str filepath):
        '''Loads the Trie from a file.

        Parameters
        ----------
        filepath : str
            path to file to read from

        Returns
        -------
        Trie
            a loaded Trie
        '''
        if not os.path.exists(filepath):
            raise OSError("File not found: '{}'".format(filepath))

        trie = Trie()
        load_from_file(filepath.encode(), trie.c_trie)
        return trie

    def to_file(self, str filepath):
        '''Saves the Trie to a file.

        Parameters
        ----------
        filepath : str
            path to file to save to
        '''
        save_to_file(filepath.encode(), self.c_trie)
