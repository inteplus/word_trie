#include <string>
#include <memory>
#include <map>


struct TrieNode_c;
typedef TrieNode_c* TrieNode_p;
typedef std::unique_ptr<TrieNode_c> TrieNode_lp;


struct TrieNode_c
{
  std::map<char, TrieNode_lp> m_children;
  TrieNode_p m_parent;
  long long m_count;
  bool m_endofword;

  // constructor
  TrieNode_c()
  {
    m_parent = nullptr;
    m_count = 0;
    m_endofword = false;
  }
};


struct Trie_c
{
  TrieNode_lp m_root;

  // constructor
  Trie_c() { m_root.reset(new TrieNode_c); }

  // root node
  inline TrieNode_p root() const { return m_root.get(); }

  // total count
  inline long long total_count() const { return m_root->m_count; }


  // inserts a word with count
  void insert(std::string const& word, long long count=1);

  // searches for a TrieNode_c representing a word
  TrieNode_p search(std::string const& word) const;
};

