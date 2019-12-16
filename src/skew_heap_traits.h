#ifndef SRC_SKEW_HEAP_TRAITS_H_
#define SRC_SKEW_HEAP_TRAITS_H_

#include "mergeable_heap.h"
#include <bits/stdc++.h>
#include <memory>
#include <fstream>


template<typename T, typename Node_>
class SkewHeapTraits: public IHeap<T> {
 public:
  SkewHeapTraits();
  SkewHeapTraits(const SkewHeapTraits<T, Node_> &src);
  SkewHeapTraits(SkewHeapTraits<T, Node_> &&src);

  void swap(SkewHeapTraits<T, Node_> &other);

  size_t size() const;

  void insert(const T &a);
  void insert(T &&a);

  const T top() const;

  void erase();
  void clear();

  void merge(SkewHeapTraits<T, Node_> &b);
  void merge(SkewHeapTraits<T, Node_> &&b);

  SkewHeapTraits<T, Node_> &operator=(SkewHeapTraits<T, Node_> &&src);
  SkewHeapTraits<T, Node_> &operator=(const SkewHeapTraits<T, Node_> &src);

  ~SkewHeapTraits();

 private:

  static std::shared_ptr<Node_> merge_(std::shared_ptr<Node_> a,
                                       std::shared_ptr<Node_> b);
  static std::shared_ptr<Node_> deepCopy_(const std::shared_ptr<Node_> &src);
  std::shared_ptr<Node_> head_;
  size_t size_;
};

template<typename T, typename Node_>
SkewHeapTraits<T, Node_>::~SkewHeapTraits() {
}

template<typename T, typename Node_>
SkewHeapTraits<T, Node_>::SkewHeapTraits(): IHeap<T>(), head_(nullptr), size_(0) {
}

template<typename T, typename Node_>
SkewHeapTraits<T, Node_>::SkewHeapTraits(const SkewHeapTraits<T, Node_> &src)
: IHeap<T>(), head_(deepCopy_(src.head_)), size_(src.size_) {
}

template<typename T, typename Node_>
SkewHeapTraits<T, Node_>::SkewHeapTraits(SkewHeapTraits<T, Node_> &&src): SkewHeapTraits() {
  swap(src);
}

template<typename T, typename Node_>
SkewHeapTraits<T, Node_> &SkewHeapTraits<T, Node_>::operator=(SkewHeapTraits<T, Node_> &&src) {
  swap(src);
  return *this;
}

template<typename T, typename Node_>
SkewHeapTraits<T, Node_> &SkewHeapTraits<T, Node_>::operator=(const SkewHeapTraits<T, Node_> &src) {
  SkewHeapTraits tmp(src);
  swap(tmp);
  return *this;
}

template<typename T, typename Node_>
void SkewHeapTraits<T, Node_>::swap(SkewHeapTraits<T, Node_> &other) {
  std::swap(size_, other.size_);
  head_.swap(other.head_);
}

template<typename T, typename Node_>
size_t SkewHeapTraits<T, Node_>::size() const {
  return size_;
}

template<typename T, typename Node_>
void SkewHeapTraits<T, Node_>::merge(SkewHeapTraits<T, Node_> &other) {
  merge(std::move(other));
}

template<typename T, typename Node_>
void SkewHeapTraits<T, Node_>::merge(SkewHeapTraits<T, Node_> &&other) {
  if (this == &other) {
    return;
  }
  head_ = merge_(head_, other.head_);
  size_ += other.size_;
  other.size_ = 0;
  other.head_ = nullptr;
}

template<typename T, typename Node_>
void SkewHeapTraits<T, Node_>::insert(const T &a) {
  insert(T(a));
}

template<typename T, typename Node_>
void SkewHeapTraits<T, Node_>::insert(T &&a) {
  std::shared_ptr<Node_> tmp(new Node_(a));
  size_ += 1;
  head_ = merge_(head_, tmp);
}

template<typename T, typename Node_>
void SkewHeapTraits<T, Node_>::erase() {
  size_ -= 1;
  head_ = merge_(head_->child_left, head_->child_right);
}

template<typename T, typename Node_>
void SkewHeapTraits<T, Node_>::clear() {
  head_ = 0;
  size_ = 0;
}

template<typename T, typename Node_>
std::shared_ptr<Node_>
SkewHeapTraits<T, Node_>::deepCopy_(const std::shared_ptr<Node_> &src) {
  if (src == nullptr) {
    return nullptr;
  }
  std::shared_ptr<Node_> res(new Node_(src->key));
  res->child_left = deepCopy_(src->child_left);
  res->child_right = deepCopy_(src->child_right);
  return res;
}

template<typename T, typename Node_>
const T SkewHeapTraits<T, Node_>::top() const {
  return head_->key;
}

template<typename T, typename Node_>
std::shared_ptr<Node_> SkewHeapTraits<T, Node_>::merge_(std::shared_ptr<Node_> a,
                                                        std::shared_ptr<Node_> b) {
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

  a->swapChildIfNeed();

  return a;
}

#endif  // SRC_SKEW_HEAP_TRAITS_H_
