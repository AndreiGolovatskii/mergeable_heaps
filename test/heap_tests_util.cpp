#ifndef HEAP_TESTS_UTIL_CPP_
#define HEAP_TESTS_UTIL_CPP_

#include <vector>

template<template<class> class H, typename T>
std::vector<T> toVector(H<T> in) {
  std::vector<T> arr;
  while (in.size()) {
    arr.push_back(in.top());
    in.erase();
  }
  return arr;
}

template<template<class> class H1, template<class> class H2, typename T>
bool isEqual(const H1<T> &a, const H2<T> &b) {
  return toVector(a) == toVector(b);
}

#endif  // HEAP_TESTS_UTIL_CPP_
