#ifndef SRC_SKEW_HEAP_H_
#define SRC_SKEW_HEPA_H_

#include "mergeable_heap.h"
#include <bits/stdc++.h>
#include <memory>
#include <fstream>


template<typename T>
class SkewHeap: public IHeap<T> {
 public:
  SkewHeap();
  SkewHeap(const SkewHeap<T> &src);
  SkewHeap(SkewHeap<T> &&src);

  void swap(SkewHeap<T> &other);

  size_t size() const;

  void insert(const T &a);
  void insert(T &&a);

  const T top() const;

  void erase();
  void clear();

  void merge(SkewHeap<T> &b);
  void merge(SkewHeap<T> &&b);

  SkewHeap<T> &operator=(SkewHeap<T> &&src);
  SkewHeap<T> &operator=(const SkewHeap<T> &src);

  ~SkewHeap();

 private:
  struct Node_{
    T key;
    std::shared_ptr<Node_> child_left,
                           child_right;
    Node_(const T &key): key(key),
                        child_left(nullptr),
                        child_right(nullptr) {}
    Node_(T &&key):      key(key),
                        child_left(nullptr),
                        child_right(nullptr) {}
  };

  static std::shared_ptr<Node_> merge_(std::shared_ptr<Node_> a,
                                       std::shared_ptr<Node_> b);
  static std::shared_ptr<Node_> deepCopy_(const std::shared_ptr<Node_> &src);
  std::shared_ptr<Node_> head_;
  size_t size_;
};

template<typename T>
SkewHeap<T>::~SkewHeap() {
}

template<typename T>
SkewHeap<T>::SkewHeap(): IHeap<T>(), head_(nullptr), size_(0) {
}

template<typename T>
SkewHeap<T>::SkewHeap(const SkewHeap<T> &src)
: IHeap<T>(), head_(deepCopy_(src.head_)), size_(src.size_) {
}

template<typename T>
SkewHeap<T>::SkewHeap(SkewHeap<T> &&src): SkewHeap() {
  swap(src);
}

template<typename T>
SkewHeap<T> &SkewHeap<T>::operator=(SkewHeap<T> &&src) {
  swap(src);
  return *this;
}

template<typename T>
SkewHeap<T> &SkewHeap<T>::operator=(const SkewHeap<T> &src) {
  SkewHeap tmp(src);
  swap(tmp);
  return *this;
}

template<typename T>
void SkewHeap<T>::swap(SkewHeap<T> &other) {
  std::swap(size_, other.size_);
  head_.swap(other.head_);
}

template<typename T>
size_t SkewHeap<T>::size() const {
  return size_;
}

template<typename T>
void SkewHeap<T>::merge(SkewHeap<T> &other) {
  merge(std::move(other));
}

template<typename T>
void SkewHeap<T>::merge(SkewHeap<T> &&other) {
  if (this == &other) {
    return;
  }
  head_ = merge_(head_, other.head_);
  size_ += other.size_;
  other.size_ = 0;
  other.head_ = nullptr;
}

template<typename T>
void SkewHeap<T>::insert(const T &a) {
  insert(T(a));
}

template<typename T>
void SkewHeap<T>::insert(T &&a) {
  std::shared_ptr<Node_> tmp(new Node_(a));
  size_ += 1;
  head_ = merge_(head_, tmp);
}

template<typename T>
void SkewHeap<T>::erase() {
  size_ -= 1;
  head_ = merge_(head_->child_left, head_->child_right);
}

template<typename T>
void SkewHeap<T>::clear() {
  head_ = 0;
  size_ = 0;
}

template<typename T>
std::shared_ptr<typename SkewHeap<T>::Node_>
SkewHeap<T>::deepCopy_(const std::shared_ptr<Node_> &src) {
  if (src == nullptr) {
    return nullptr;
  }
  std::shared_ptr<Node_> res(new Node_(src->key));
  res->child_left = deepCopy_(src->child_left);
  res->child_right = deepCopy_(src->child_right);
  return res;
}

template<typename T>
const T SkewHeap<T>::top() const {
  return head_->key;
}

template<typename T>
std::shared_ptr<typename SkewHeap<T>::Node_>
SkewHeap<T>::merge_(std::shared_ptr<Node_> a, std::shared_ptr<Node_> b) {
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
  a->child_right.swap(a->child_left);

  return a;
}

#endif  // SRC_LEFTIST_HEAP_H_
