#include "gtest/gtest.h"

#include "mergeable_heap.h"
#include "test_heap.h"
#include "binomial_heap.h"
#include "leftist_heap.h"
#include "skew_heap.h"

#include <memory>
#include <random>
#include <vector>

#include "heap_tests_util.cpp"

template<typename T>
void mergeTestsInt() {
  T h1, h2;
  h1.insert(1);
  h1.insert(2);

  h2.insert(4);
  h2.insert(5);

  h1.merge(h2);
  ASSERT_EQ(h1.size(), 4);

  h2.clear();
  h2.insert(-1);

  h1.merge(std::move(h2));
  ASSERT_EQ(h1.size(), 5);
}

TEST(TestHeapTest, mergeTestsInt) {
  mergeTestsInt<TestHeap<int>>();
}

TEST(BinomialHeapTest, mergeTestsInt) {
  mergeTestsInt<BinomialHeap<int>>();
}

TEST(LeftistHeapTest, mergeTestsInt) {
  mergeTestsInt<LeftistHeap<int>>();
}

TEST(SkewHeapTest, mergeTestsInt) {
  mergeTestsInt<SkewHeap<int>>();
}


