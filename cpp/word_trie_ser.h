#include <vector>
#include <boost/serialization/access.hpp>
#include "word_trie.h"



// structure for serializing/deserializing Trie_c. The trie is flattened from leaves to root (root node is the last node).
struct TrieSerializable_c {
  int m_num_nodes;
  std::vector<int> m_parent;
  std::vector<char> m_char;
  std::vector<long long> m_count;
  std::vector<bool> m_endofword;

  // turn this structure into a trie
  Trie_c trie() const;

private: // serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_num_nodes;
        ar & m_parent;
        ar & m_char;
	ar & m_count;
	ar & m_endofword;
    }
};


// turn a trie into a serializable equivalent structure
TrieSerializable_c trie_serializable(Trie_c const& trie);

