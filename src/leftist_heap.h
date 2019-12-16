#ifndef SRC_LEFTIST_HEAP_H_
#define SRC_LEFTIST_HEAP_H_

#include "mergeable_heap.h"
#include "skew_heap_traits.h"
#include <bits/stdc++.h>
#include <memory>
#include <fstream>


template<typename T>
struct LeftistNode{
 public:
  T key;
  size_t dist;
  std::shared_ptr<LeftistNode> child_left,
                          child_right;
  LeftistNode(const T &key): key(key),
                      dist(1),
                      child_left(nullptr),
                      child_right(nullptr) {}
  LeftistNode(T &&key):      key(key),
                      dist(1),
                      child_left(nullptr),
                      child_right(nullptr) {}
  void swapChildIfNeed() {
    if (getDist(child_right) > getDist(child_left)) {
      child_right.swap(child_left);
    }
    dist = getDist(child_right) + 1;
  }

 private:
  size_t getDist(const std::shared_ptr<LeftistNode> &p) {
    if (p == nullptr) {
      return 0;
    }
    return p->dist;
  }
};

template<typename T>
using LeftistHeap = SkewHeapTraits<T, LeftistNode<T>>;

#endif  // SRC_LEFTIST_HEAP_H_
