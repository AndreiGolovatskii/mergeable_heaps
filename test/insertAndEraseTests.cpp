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

template<typename T>
void insertAndEraseTestsInt() {
  T a;
  a.insert(1);  // {1}
  const int x = 1;
  a.insert(x);  // {1, 1}
  a.insert(2);  // {1, 1, 2}

  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.top(), 1);

  a.erase();  // {1, 2}
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.top(), 1);

  a.erase();  // {2}
  a.erase();  // {}

  ASSERT_EQ(a.size(), 0);

  std::mt19937 rnd(13);
  const int N = 1000;
  for (int i = 0; i < N; ++i) {
    a.insert(rnd());
  }

  ASSERT_EQ(a.size(), N);
  a.clear();
  ASSERT_EQ(a.size(), 0);
}

TEST(TestHeapTest, insertAndEraseTestInt) {
  insertAndEraseTestsInt<TestHeap<int>>();
}

TEST(BinomialHeapTest, insertAndEraseTestsInt) {
  insertAndEraseTestsInt<BinomialHeap<int>>();
}

TEST(LeftistHeapTest, insertAndEraseTestsInt) {
  insertAndEraseTestsInt<LeftistHeap<int>>();
}

TEST(SkewHeapTest, insertAndEraseTestsInt) {
  insertAndEraseTestsInt<SkewHeap<int>>();
}


TEST(CommonStressTest, InsertAndEraseTestInt) {
  TestHeap<int> test_h;
  BinomialHeap<int> bin_h;
  LeftistHeap<int> left_h;
  SkewHeap<int> skew_h;

  const int TEST_COUNT = 100;
  const int N = 100;
  std::mt19937 rnd(13);
  for (int i = 0; i < TEST_COUNT; i++) {
    for (int j = 0; j < N; ++j) {
      if (test_h.size() && rnd() % 2) {
        test_h.erase();
        bin_h.erase();
        left_h.erase();
        skew_h.erase();
      } else {
        int x = rnd();
        test_h.insert(x);
        bin_h.insert(x);
        left_h.insert(x);
        skew_h.insert(x);
      }
    }

  ASSERT_TRUE(isEqual(test_h, bin_h));
  ASSERT_TRUE(isEqual(test_h, left_h));
  ASSERT_TRUE(isEqual(test_h, skew_h));
  }
}