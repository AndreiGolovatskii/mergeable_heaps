#ifndef SRC_SKEW_HEAP_H_
#define SRC_SKEW_HEAP_H_

#include "mergeable_heap.h"
#include <bits/stdc++.h>
#include <memory>
#include <fstream>

template<typename T>
struct SkewNode{
 public:
  T key;
  std::shared_ptr<SkewNode> child_left,
                          child_right;
  SkewNode(const T &key): key(key),
                          child_left(nullptr),
                          child_right(nullptr) {}
  SkewNode(T &&key):      key(key),
                          child_left(nullptr),
                          child_right(nullptr) {}
  void swapChildIfNeed() {
    child_right.swap(child_left);
  }
};

template<typename T>
using SkewHeap = SkewHeapTraits<T, SkewNode<T>>;

#endif  // SRC_SKEW_HEAP_H_
