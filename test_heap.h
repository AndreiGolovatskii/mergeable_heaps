#ifndef TEST_HEAP_H_
#define TEST_HEAP_H_

#include "mergeable_heap.h"
#include <bits/stdc++.h>
#include <fstream>

template<typename T>
class TestHeap: public IHeap<T> {
 public:
  TestHeap();
  TestHeap(const TestHeap<T> &src);
  TestHeap(TestHeap<T> &&src);
  size_t size() const;
  void insert(const T &a);
  void insert(T &&a);
  const T top() const;
  void erase();
  static TestHeap<T> merge(TestHeap<T> &a, TestHeap<T> &b);
  static TestHeap<T> merge(TestHeap<T> &&a, TestHeap<T> &&b);
 private:
  TestHeap &operator=(const TestHeap<T> &src);
  TestHeap &operator=(TestHeap<T> &&src);
  std::multiset<T> source_;
};

template<typename T>
TestHeap<T>::TestHeap () {
  //none
};

template<typename T> 
TestHeap<T>::TestHeap(const TestHeap<T> &src) {
  source_ = src.source_;
}

template<typename T>
TestHeap<T>::TestHeap(TestHeap<T> &&src) {
  source_ = std::move(src.source_);
}

template<typename T>
size_t TestHeap<T>::size() const {
  return source_.size();
}

template<typename T>
void TestHeap<T>::insert(const T &a) {
  TestHeap<T>::insert(std::move(a));
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
TestHeap<T> TestHeap<T>::merge(TestHeap<T> &a, TestHeap<T> &b) {
  return TestHeap<T>::merge(std::move(a), std::move(b));
}

template<typename T>
TestHeap<T> TestHeap<T>::merge(TestHeap<T> &&a, TestHeap<T> &&b) {
  TestHeap<T> res;
  res.source_.merge(a.source_);
  res.source_.merge(b.source_);
  return res;
}

#endif  // TEST_HEAP_H_
