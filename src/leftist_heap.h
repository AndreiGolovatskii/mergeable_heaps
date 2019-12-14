#ifndef SRC_LEFTIST_HEAP_H_
#define SRC_LEFTIST_HEPA_H_

#include "mergeable_heap.h"
#include <bits/stdc++.h>
#include <memory>
#include <fstream>


template<typename T>
class LeftistHeap: public IHeap<T> {
 public:
  LeftistHeap();
  LeftistHeap(const LeftistHeap<T> &src);
  LeftistHeap(LeftistHeap<T> &&src);

  void swap(LeftistHeap<T> &other);

  size_t size() const;

  void insert(const T &a);
  void insert(T &&a);

  const T top() const;

  void erase();

  void merge(LeftistHeap<T> &b);
  void merge(LeftistHeap<T> &&b);

  LeftistHeap<T> &operator=(LeftistHeap<T> &&src);
  LeftistHeap<T> &operator=(const LeftistHeap<T> &src);

  ~LeftistHeap();

 private:
  struct Node_{
    T key;
    size_t dist;
    std::shared_ptr<Node_> child_left,
                           child_right;
    Node_(const T &key): key(key),
                        dist(1),
                        child_left(nullptr),
                        child_right(nullptr) {}
    Node_(T &&key):      key(key),
                        dist(1),
                        child_left(nullptr),
                        child_right(nullptr) {}
  };

  static size_t getDist(const std::shared_ptr<Node_> &v);
  static std::shared_ptr<Node_> merge_(std::shared_ptr<Node_> a,
                                       std::shared_ptr<Node_> b);
  static std::shared_ptr<Node_> deepCopy_(const std::shared_ptr<Node_> &src);
  std::shared_ptr<Node_> head_;
  size_t size_;
};

template<typename T>
LeftistHeap<T>::~LeftistHeap() {
}

template<typename T>
LeftistHeap<T>::LeftistHeap(): head_(nullptr),  size_(0) {
}

template<typename T>
LeftistHeap<T>::LeftistHeap(const LeftistHeap<T> &src)
: IHeap<T>(), head_(deepCopy_(src.head_)), size_(src.size_) {
}

template<typename T>
LeftistHeap<T>::LeftistHeap(LeftistHeap<T> &&src): LeftistHeap() {
  swap(src);
}

template<typename T>
LeftistHeap<T> &LeftistHeap<T>::operator=(LeftistHeap<T> &&src) {
  swap(src);
  return *this;
}

template<typename T>
LeftistHeap<T> &LeftistHeap<T>::operator=(const LeftistHeap<T> &src) {
  LeftistHeap tmp(src);
  swap(tmp);
  return *this;
}

template<typename T>
void LeftistHeap<T>::swap(LeftistHeap<T> &other) {
  std::swap(size_, other.size_);
  head_.swap(other.head_);
}

template<typename T>
size_t LeftistHeap<T>::size() const {
  return size_;
}

template<typename T>
void LeftistHeap<T>::merge(LeftistHeap<T> &other) {
  merge(std::move(other));
}

template<typename T>
void LeftistHeap<T>::merge(LeftistHeap<T> &&other) {
  if (this == &other) {
    return;
  }
  head_ = merge_(head_, other.head_);
  size_ += other.size_;
  other.size_ = 0;
  other.head_ = nullptr;
}

template<typename T>
void LeftistHeap<T>::insert(const T &a) {
  insert(T(a));
}

template<typename T>
void LeftistHeap<T>::insert(T &&a) {
  std::shared_ptr<Node_> tmp(new Node_(a));
  size_ += 1;
  head_ = merge_(head_, tmp);
}

template<typename T>
void LeftistHeap<T>::erase() {
  size_ -= 1;
  head_ = merge_(head_->child_left, head_->child_right);
}

template<typename T>
std::shared_ptr<typename LeftistHeap<T>::Node_>
LeftistHeap<T>::deepCopy_(const std::shared_ptr<Node_> &src) {
  if (src == nullptr) {
    return nullptr;
  }
  std::shared_ptr<Node_> res(new Node_(src->key));
  res->dist = src->dist;
  res->child_left = deepCopy_(src->child_left);
  res->child_right = deepCopy_(src->child_right);
  return res;
}

template<typename T>
size_t LeftistHeap<T>::getDist(const std::shared_ptr<Node_> &v) {
  if (v == nullptr) return 0;
  return v->dist;
}

template<typename T>
const T LeftistHeap<T>::top() const {
  return head_->key;
}

template<typename T>
std::shared_ptr<typename LeftistHeap<T>::Node_>
LeftistHeap<T>::merge_(std::shared_ptr<Node_> a, std::shared_ptr<Node_> b) {
  if (a == nullptr) {
    return b;
  }
  if (b == nullptr) {
    return a;
  }
  if (b->key < a->key) {
    a.swap(b);
  }
  a->child_right = merge_(a->child_right, b);
  if (getDist(a->child_right) > getDist(a->child_left)) {
    a->child_right.swap(a->child_left);
  }
  a->dist = getDist(a->child_right) + 1;
  return a;
}

#endif  // SRC_LEFTIST_HEAP_H_
