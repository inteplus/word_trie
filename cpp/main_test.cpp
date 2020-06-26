#include <string>
#include <iostream>

#include "word_trie.h"
#include "word_trie_ser.h"


int main()
{
  Trie_c trie;
  trie.insert("harshita", 10);
  trie.insert("harsh");
  trie.insert("sharma",3);
  trie.insert("harry");


  TrieSerializable_c trie_ser = trie_serializable(trie);
  Trie_c trie2 = trie_ser.trie();

  if(trie.total_count() != trie2.total_count()) {
    std::cerr << "Wrong!!!!!!" << std::endl;
  }

  
  std::string p;
  std::cout << "Enter the prefix :";
  std::cin >> p;
  TrieNode_p result = trie.search(p);
  if(result == nullptr)
    std::cout << "String not found!" << std::endl;
  else
    std::cout << result->m_count << std::endl;

  return 0;
}
