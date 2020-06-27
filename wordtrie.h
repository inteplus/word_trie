#ifndef WORD_TRIE_H
#define WORD_TRIE_H


#include <string>
#include <memory>
#include <map>

#include <boost/serialization/access.hpp>
#include <boost/serialization/split_member.hpp>


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

  
private: // serialization
  friend class boost::serialization::access;

  template<class Archive>
  void save(Archive & ar, const unsigned int version) const {
    ar & m_count & m_endofword & m_children.size();
    for(auto iter = m_children.begin(); iter != m_children.end(); iter++)
      ar & iter->first & *iter->second;
  }

  template<class Archive>
  void load(Archive & ar, const unsigned int version) {
    size_t n; // number of children
    ar & m_count & m_endofword & n;
    m_children.clear();
    while(n--) {
      char ch;
      TrieNode_p node = new TrieNode_c();
      ar & ch & *node;
      node->m_parent = this;
      m_children[ch].reset(node);
    }
  }
  
  BOOST_SERIALIZATION_SPLIT_MEMBER()
};


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

  // estimates the prior probability of a word
  double prob(std::string const& word) const;

  // estimates the probability of a word given its parent (ie without the last letter)
  double cond_prob(std::string const& word) const;


private: // serialization
  friend class boost::serialization::access;

  template<class Archive>
  void save(Archive & ar, const unsigned int version) const {
    ar & *m_root;
  }

  template<class Archive>
  void load(Archive & ar, const unsigned int version) {
    TrieNode_p node = new TrieNode_c();
    ar & *node;
    m_root.reset(node);
  }
  
  BOOST_SERIALIZATION_SPLIT_MEMBER()
};


// loads a trie from an std::istream
void load(std::istream& is, Trie_c& out_trie);


// saves a trie to an std::ostream
void save(std::ostream& os, Trie_c const& in_trie);


// loads a trie from file
void load_from_file(std::string const& filepath, Trie_c& out_trie);


// saves a trie to file
void save_to_file(std::string const& filepath, Trie_c const& in_trie);


#endif
