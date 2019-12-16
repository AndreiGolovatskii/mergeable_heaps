#ifndef HEAP_TESTS_UTIL_CPP_
#define HEAP_TESTS_UTIL_CPP_

#include <vector>

template<class H>
std::vector<int> toVectorInt(H in) {
  std::vector<int> arr;
  while (in.size()) {
    arr.push_back(in.top());
    in.erase();
  }
  return arr;
}

template<class H1, class H2>
bool isEqualInt(const H1 &a, const H2 &b) {
  return toVectorInt(a) == toVectorInt(b);
}

#endif  // HEAP_TESTS_UTIL_CPP_
