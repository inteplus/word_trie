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
  for(auto iter = m_children.begin(); iter != m_children.end(); iter++)
    starting_id += iter->second->update_id_map(node_map, starting_id, iter->first);
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


TrieSerialisable_c Trie_c::serialisable() const
{
  TrieSerialisable_c res;
  res.m_num_nodes = num_nodes();
  std::map<TrieNode_p, std::pair<int, char> > id_map;
  int cnt_id = m_root->update_id_map(id_map, 0, ' ');
  if(cnt_id != res.m_num_nodes) {
    std::cerr << "Warning: Number of ids " << cnt_id << " differs from number of nodes " << res.m_num_nodes << "." << std::endl;
    res.m_num_nodes = cnt_id;
  }

  res.m_parent.resize(cnt_id);
  res.m_char.resize(cnt_id);
  res.m_count.resize(cnt_id);
  res.m_endofword.resize(cnt_id);

  for(auto iter = id_map.begin(); iter != id_map.end(); iter++) {
    TrieNode_p node = iter->first;
    int id = iter->second.first;
    res.m_parent[id] = id_map[node->m_parent].first;
    res.m_char[id] = iter->second.second;
    res.m_count[id] = node->m_count;
    res.m_endofword[id] = node->m_endofword;
  }

  return res;
}

Trie_c TrieSerialisable_c::trie() const
{
  Trie_c res;
  std::vector<TrieNode_p> nodes(m_num_nodes);
  int i;
  TrieNode_p node;

  // allocate
  for(i = 0; i < m_num_nodes; ++i) {
    node = new TrieNode_c;
    node->m_count = m_count[i];
    node->m_endofword = m_endofword[i];
    nodes[i] = node;
  }

  // fill in linking attributes
  for(i = 0; i < m_num_nodes-1; ++i) {
    node = nodes[i];
    int parent_id = m_parent[i];
    node->m_parent = nodes[parent_id];
    nodes[parent_id]->m_children[m_char[i]].reset(node);
  }

  res.m_root.reset(nodes[m_num_nodes-1]);
  return res;
}

