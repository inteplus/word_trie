#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "wordtrie.h"


int TrieNode_c::num_descendants() const {
  int cnt = 1;
  for(auto iter = m_children.begin(); iter != m_children.end(); iter++)
    cnt += iter->second->num_descendants();
  return cnt;
}


void Trie_c::insert(std::string const& word, long long count) {
  TrieNode_p current = root();
  current->m_count += count;

  for(size_t i=0; i < word.size(); i++) {
    char ch = word[i];
    auto iter = current->m_children.find(ch);
    TrieNode_p node;

    if(iter != current->m_children.end())
      node = iter->second.get();
    else {
      node = new TrieNode_c();
      node->m_parent = current;
      current->m_children[ch].reset(node);
    }

    current = node;
    current->m_count += count;
  }

  current->m_endofword = true;
}


TrieNode_p Trie_c::search(std::string const& word) const {
  TrieNode_p current = root();
  for(size_t i=0; i < word.size(); i++) {
    char ch = word[i];
    auto iter = current->m_children.find(ch);

    if(iter == current->m_children.end())
      return nullptr;
    current = iter->second.get();
  }
  return current;
}

double Trie_c::prob(std::string const& word) const {
  TrieNode_p node = search(word);
  if(!node)
    return 0.0;
  return ((double) node->m_count) / total_count();
}

double Trie_c::cond_prob(std::string const& word) const {
  TrieNode_p node = search(word);
  if(!node)
    return 0.0;
  return ((double) node->m_count) / node->m_parent->m_count;
}


void load(std::istream& is, Trie_c& out_trie) {
  boost::archive::text_iarchive ia(is);
  ia >> out_trie;
}


void save(std::ostream& os, Trie_c const& in_trie) {
  boost::archive::text_oarchive oa(os);
  oa << in_trie;
}


void load_from_file(std::string const& filepath, Trie_c& out_trie) {
  std::ifstream ifs(filepath);
  load(ifs, out_trie);
}


void save_to_file(std::string const& filepath, Trie_c const& in_trie) {
  std::ofstream ofs(filepath);
  save(ofs, in_trie);
}


