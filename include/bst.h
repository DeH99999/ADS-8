// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
class BST {
 public:
  BST() : root_(nullptr) {}
  ~BST() { clear(root_); }

  void insert(const T& key) {
    root_ = insert(root_, key);
  }

  int search(const T& val) const {
    Node* node = find(root_, val);
    return node ? node->count : 0;
  }

  int depth() const {
    return depth(root_);
  }

  std::vector<std::pair<T, int>> getAllSortedByKey() const {
    std::vector<std::pair<T, int>> items;
    collect(root_, items);
    return items;
  }

  bool empty() const {
    return root_ == nullptr;
  }

 private:
  struct Node {
    T key;
    int count;
    Node* l;
    Node* r;
    explicit Node(const T& k) : key(k), count(1), l(nullptr), r(nullptr) {}
  };

  Node* root_;

  Node* insert(Node* node, const T& key) {
    if (!node) return new Node(key);
    if (key < node->key) {
      node->l = insert(node->l, key);
    } else if (key > node->key) {
      node->r = insert(node->r, key);
    } else {
      node->count++;
    }
    return node;
  }

  Node* find(Node* node, const T& val) const {
    if (!node || node->key == val) return node;
    if (val < node->key) return find(node->l, val);
    return find(node->r, val);
  }

  int depth(Node* node) const {
    if (!node) return -1;
    return 1 + std::max(depth(node->l), depth(node->r));
  }

  void collect(Node* node, std::vector<std::pair<T, int>>& items) const {
    if (!node) return;
    collect(node->l, items);
    items.emplace_back(node->key, node->count);
    collect(node->r, items);
  }

  void clear(Node* node) {
    if (!node) return;
    clear(node->l);
    clear(node->r);
    delete node;
  }
};

#endif  // INCLUDE_BST_H_
