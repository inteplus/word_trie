#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include "word_trie_ser.h"


TrieSerializable_c trie_serializable(Trie_c const& trie)
{
  TrieSerializable_c res;
  res.m_num_nodes = trie.num_nodes();
  std::map<TrieNode_p, std::pair<int, char> > id_map;
  int cnt_id = trie.m_root->update_id_map(id_map, 0, ' ');
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

Trie_c TrieSerializable_c::trie() const
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

