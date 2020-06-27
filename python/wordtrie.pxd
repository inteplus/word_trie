from libcpp.string cimport string

cdef extern from "<iostream>" namespace "std" nogil:
    cdef cppclass istream:
        pass
    cdef cppclass ostream:
    	 pass


cdef extern from "wordtrie.h":
    cdef cppclass TrieNode_c:
        long long m_count
	bool m_endofword
	int num_descendants()
    cdef cppclass Trie_c:
        long long total_count()
	int num_nodes()
	void insert(string const& word, long long count=1)
	double prob(string const& word)
	double cond_prob(string const& word)
    cdef void load(istream& is, Trie_c& out_trie)
    cdef void save(ostream& os, Trie_c const& in_trie)
    cdef void load_from_file(string const& is, Trie_c& out_trie)
    cdef void save_to_file(string const& os, Trie_c const& in_trie)
