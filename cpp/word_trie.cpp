#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include "word_trie.h"


void Trie_c::insert(std::string const& word, long long count)
{
  TrieNode_p current = root();
  for(int i=0; i < word.size(); i++)
  {
    char ch = word[i];
    auto iter = current->m_children.find(ch);
    TrieNode_p node;

    if(iter != current->m_children.end())
      node = iter->second.get();
    else
    {
      node = new TrieNode_c();
      node->m_parent = current;
      current->m_children[ch].reset(node);
    }

    current = node;
    current->m_count += count;
  }
  current->m_endofword = true;
}


TrieNode_p Trie_c::search(std::string const& word) const
{
  TrieNode_p current = root();
  for(int i=0; i < word.size(); i++)
  {
    char ch = word[i];
    auto iter = current->m_children.find(ch);
    TrieNode_p node;

    if(iter == current->m_children.end())
      return nullptr;
    current = iter->second.get();
  }
  return current;
}
