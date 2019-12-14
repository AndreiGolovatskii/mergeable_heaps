#ifndef SRC_TEST_HEAP_H_
#define SRC_TEST_HEAP_H_

#include "mergeable_heap.h"
#include <bits/stdc++.h>
#include <fstream>


template<typename T>
class TestHeap: public IHeap<T> {
 public:
  TestHeap();
  TestHeap(const TestHeap<T> &src);
  TestHeap(TestHeap<T> &&src);

  void swap(TestHeap<T> &other);

  size_t size() const;

  void insert(const T &a);
  void insert(T &&a);

  const T top() const;

  void erase();
  void clear();

  void merge(TestHeap<T> &b);
  void merge(TestHeap<T> &&b);

  // void merge(IHeap<T> &other);

  TestHeap<T> &operator=(TestHeap<T> &&src);
  TestHeap<T> &operator=(const TestHeap<T> &src);

  // IHeap<T> &operator=(const IHeap<T> &other);

  ~TestHeap();

 private:
  std::multiset<T> source_;
};

template<typename T>
TestHeap<T>::TestHeap() {
  //  none
}

template<typename T>
TestHeap<T>::~TestHeap() {
  //  none;
}

template<typename T>
TestHeap<T>::TestHeap(const TestHeap<T> &src): IHeap<T>(), source_(src.source_) {
}

template<typename T>
TestHeap<T>::TestHeap(TestHeap<T> &&src): IHeap<T>(), source_(std::move(src.source_)) {
}

template<typename T>
void TestHeap<T>::swap(TestHeap<T> &other) {
  std::swap(source_, other.source_);
}

template<typename T>
size_t TestHeap<T>::size() const {
  return source_.size();
}

template<typename T>
void TestHeap<T>::insert(const T &a) {
  TestHeap<T>::insert(T(a));
}

template<typename T>
void TestHeap<T>::insert(T &&a) {
  source_.insert(a);
}

template<typename T>
const T TestHeap<T>::top() const {
  return *(source_.begin());
}

template<typename T>
void TestHeap<T>::erase() {
  source_.erase(source_.begin());
}

template<typename T>
void TestHeap<T>::clear() {
  source_.clear();
}

template<typename T>
void TestHeap<T>::merge(TestHeap<T> &b) {
  TestHeap<T>::merge(std::move(b));
}

template<typename T>
void TestHeap<T>::merge(TestHeap<T> &&b) {
  if (this == &b) {
    return;
  }
  source_.insert(b.source_.begin(), b.source_.end());
  b.source_.clear();
}

// template<typename T>
// void TestHeap<T>::merge(IHeap<T> &other) {
  // merge(dynamic_cast<TestHeap<T>&>(other));
// }

template<typename T>
TestHeap<T>& TestHeap<T>::operator=(const TestHeap<T> &src) {
  source_ = src.source_;
  return *this;
}

template<typename T>
TestHeap<T>& TestHeap<T>::operator=(TestHeap<T> &&src) {
  source_ = std::move(src.source_);
  return *this;
}

#endif  // SRC_TEST_HEAP_H_
