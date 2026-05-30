// Copyright 2021 NNTU-CS
#include "bst.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <utility>
#include <vector>

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error: cannot open " << filename << std::endl;
    return;
  }

  std::string curWord;
  char c;
  while (file.get(c)) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
      curWord.push_back(static_cast<char>(std::tolower(
          static_cast<unsigned char>(c))));
    } else {
      if (!curWord.empty()) {
        tree.insert(curWord);
        curWord.clear();
      }
    }
  }
  if (!curWord.empty()) {
    tree.insert(curWord);
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> freqs = tree.getAllSortedByKey();

  std::sort(freqs.begin(), freqs.end(),
      [](const std::pair<std::string, int>& a,
         const std::pair<std::string, int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
      });

  for (const auto& item : freqs) {
    std::cout << item.first << " : " << item.second << std::endl;
  }

  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cout << "Error: cannot create result/freq.txt" << std::endl;
    return;
  }
  for (const auto& item : freqs) {
    outFile << item.first << " : " << item.second << std::endl;
  }
  outFile.close();
}
