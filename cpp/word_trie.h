#include <string>
#include <memory>
#include <map>
#include <vector>


struct TrieNode_c;
typedef TrieNode_c* TrieNode_p;
typedef std::unique_ptr<TrieNode_c> TrieNode_lp;


struct TrieNode_c {
  std::map<char, TrieNode_lp> m_children;
  TrieNode_p m_parent;
  long long m_count;
  bool m_endofword;

  // constructor
  TrieNode_c() {
    m_parent = nullptr;
    m_count = 0;
    m_endofword = false;
  }

  // number of descendant nodes, including this node
  int num_descendants() const;

  // update the map that maps each TrieNode_p to an integer id and a postfix character, returning the last added id plus 1.
  int update_id_map(std::map<TrieNode_p, std::pair<int, char> >& node_map, int starting_id, char ch) const;
};


struct TrieSerialisable_c;
struct Trie_c {
  TrieNode_lp m_root;

  // constructor
  Trie_c() { m_root.reset(new TrieNode_c); }

  // root node
  inline TrieNode_p root() const { return m_root.get(); }

  // total count
  inline long long total_count() const { return m_root->m_count; }


  // count the number of nodes
  inline int num_nodes() const { return m_root->num_descendants(); }

  // inserts a word with count
  void insert(std::string const& word, long long count=1);

  // searches for a TrieNode_c representing a word
  TrieNode_p search(std::string const& word) const;

  // turn this structure into an equivalence that is serialisable
  TrieSerialisable_c serialisable() const;
};


// structure for serializing/deserializing Trie_c. The trie is flattened from leaves to root (root node is the last node).
struct TrieSerialisable_c {
  int m_num_nodes;
  std::vector<int> m_parent;
  std::vector<char> m_char;
  std::vector<long long> m_count;
  std::vector<bool> m_endofword;

  // turn this structure into a trie
  Trie_c trie() const;
};
