#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include "word_trie.h"


int TrieNode_c::num_descendants() const {
  int cnt = 1;
  for(auto iter = m_children.begin(); iter != m_children.end(); iter++)
    cnt += iter->second->num_descendants();
  return cnt;
}


int TrieNode_c::update_id_map(std::map<TrieNode_c*, std::pair<int, char> >& node_map, int starting_id, char ch) const {
  for(auto iter = m_children.begin(); iter != m_children.end(); iter++) {
    starting_id = iter->second->update_id_map(node_map, starting_id, iter->first);
  }
  node_map[(TrieNode_p)this] = std::make_pair(starting_id, ch);
  return starting_id+1;
}


void Trie_c::insert(std::string const& word, long long count) {
  TrieNode_p current = root();
  for(int i=0; i < word.size(); i++) {
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
  for(int i=0; i < word.size(); i++) {
    char ch = word[i];
    auto iter = current->m_children.find(ch);
    TrieNode_p node;

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
