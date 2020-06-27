#include <string>
#include <iostream>

#include "wordtrie.h"


int main()
{
  Trie_c trie, trie2;
  trie.insert("harshita", 10);
  trie.insert("harsh");
  trie.insert("sharma",3);
  trie.insert("harry");

  save_to_file("test.trie", trie);
  load_from_file("test.trie", trie2);

  if(trie.total_count() != trie2.total_count()) {
    std::cerr << "Wrong!!!!!!" << std::endl;
  }
  
  std::string p;
  std::cout << "Enter the prefix: ";
  std::cin >> p;
  TrieNode_p result = trie.search(p);
  if(result == nullptr)
    std::cout << "String not found!" << std::endl;
  else
    std::cout << result->m_count << std::endl;

  return 0;
}
