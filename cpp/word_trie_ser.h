#ifndef WORD_TRIE_SER_H
#define WORD_TRIE_SER_H


#include <vector>
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
};


// turn a trie into a serializable equivalent structure
TrieSerializable_c trie_serializable(Trie_c const& trie);


#endif
