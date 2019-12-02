#ifndef BINOMIAL_HEAP_H_
#define BINOMAIL_HEAP_H_

#include <utility>
#include "mergeable_heap.h"

template<typename T>
class BinomialHeap: public IHeap<T> {
 public:
  void insert(T &&a);
  const T top() const;
  void erase(); 
  static BinomialHeap<T> merge(BinomialHeap<T> &&a, BinomialHeap<T> &&b);
  static BinomialHeap<T> merge(BinomialHeap<T> &a, BinomialHeap<T> &b);
 private:
  T val;
};

template<typename T>
void BinomialHeap<T>::insert(T &&a) {
  //TODO
  val = a;
}

template<typename T>
void BinomialHeap<T>::erase() {
  //TODO
  val = 0;
}

template<typename T>
const T BinomialHeap<T>::top() const {
  //TODO
  return val;
}

template<typename T>
BinomialHeap<T> BinomialHeap<T>::merge(BinomialHeap<T> &a, BinomialHeap<T> &b) {
  return BinomialHeap<T>::merge(std::move(a), std::move(b));
}

template<typename T>
BinomialHeap<T> BinomialHeap<T>::merge(BinomialHeap<T> &&a, BinomialHeap<T> &&b) {
  BinomialHeap<T> res;
  res.val = a.val + b.val;
  return res;
}
#endif  // BINOMIAL_HEAP_H_
