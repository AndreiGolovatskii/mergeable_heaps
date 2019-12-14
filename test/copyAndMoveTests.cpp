#include <memory>
#include "gtest/gtest.h"
#include "mergeable_heap.h"

#include "test_heap.h"
#include "binomial_heap.h"
#include "leftist_heap.h"
#include "skew_heap.h"

#include <random>
#include <vector>
#include "heap_tests_util.cpp"

template<typename H>
void moveTestsInt() {
  H h1, h2;
  h1.insert(1);
  h1.insert(3);

  h2.insert(2);

  h1 = std::move(h2);
  ASSERT_EQ(h1.size(), 1);
  h2.insert(1);
  ASSERT_EQ(h1.size(), 1);

  H h3(std::move(h1));
  ASSERT_EQ(h3.size(), 1);
  h1.insert(1);
  ASSERT_EQ(h3.size(), 1);

}

TEST(TestHeapTest, moveTestsInt) {
  moveTestsInt<TestHeap<int>>();
}

TEST(BinomialHeapTest, moveTestsInt) {
  moveTestsInt<BinomialHeap<int>>();
}

TEST(LeftistHeapTest, moveTestsInt) {
  moveTestsInt<LeftistHeap<int>>();
}

TEST(SkewHeapTest, moveTestsInt) {
  moveTestsInt<SkewHeap<int>>();
}


template<typename H>
void copyTestsInt() {
  H h1, h2;
  h1.insert(1);
  h1.insert(3);

  h2.insert(2);

  h1 = h2;
  ASSERT_TRUE(isEqual(h1, h2));
  h2.insert(1);
  ASSERT_EQ(h1.size(), 1);

  H h3(h1);
  ASSERT_TRUE(isEqual(h1, h3));
  h1.insert(1);
  ASSERT_EQ(h3.size(), 1);
}

TEST(TestHeapTest, copyTestsInt) {
  copyTestsInt<TestHeap<int>>();
}

TEST(BinomialHeapTest, copyTestsInt) {
  copyTestsInt<BinomialHeap<int>>();
}

TEST(LeftistHeapTest, copyTestsInt) {
  copyTestsInt<LeftistHeap<int>>();
}

TEST(SkewHeapTest, copyTestsInt) {
  copyTestsInt<SkewHeap<int>>();
}


template<typename H>
void swapTestsInt() {
  H h1, h2;
  h1.insert(1);
  h2.insert(2);
  h2.insert(3);

  h1.swap(h2);
  ASSERT_EQ(h1.size(), 2);
  ASSERT_EQ(h2.size(), 1);

  std::swap(h1, h2);
  ASSERT_EQ(h2.size(), 2);
  ASSERT_EQ(h1.size(), 1);
}

TEST(TestHeapTest, swapTestsInt) {
  swapTestsInt<TestHeap<int>>();
}

TEST(BinomialHeapTest, swapTestsInt) {
  swapTestsInt<BinomialHeap<int>>();
}

TEST(LeftistHeapTest, swapTestsInt) {
  swapTestsInt<LeftistHeap<int>>();
}

TEST(SkewHeapTest, swapTestsInt) {
  swapTestsInt<SkewHeap<int>>();
}
