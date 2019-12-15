#include <random>
#include <vector>
#include "gtest/gtest.h"
#include "heap_tests_util.cpp"
#include "test_heap.h"
#include "binomial_heap.h"
#include "leftist_heap.h"
#include "skew_heap.h"

template<template<class> class H, typename T>
void addHeap(std::vector<H<T>> &heaps, std::mt19937 &rnd) {
  heaps.push_back(H<T>());
  heaps.back().insert(rnd());
}

template<template<class> class H, typename T>
void insert(std::vector<H<T>> &heaps, std::mt19937 &rnd) {
  if (heaps.size() == 0) {
    return;
  }

  int ind = (rnd()) % heaps.size();
  heaps[ind].insert(rnd());
}

template<template<class> class H, typename T>
int getMin(std::vector<H<T>> &heaps, std::mt19937 &rnd) {
  if (heaps.size() == 0) {
    return 0;
  }

  int ind = (rnd()) % heaps.size();
  if (heaps[ind].size() == 0) {
    return 0;
  }
  return heaps[ind].top();
}

template<template<class> class H, typename T>
void extractMin(std::vector<H<T>> &heaps, std::mt19937 &rnd) {
  if (heaps.size() == 0) {
    return;
  }

  int ind = (rnd()) % heaps.size();
  if (heaps[ind].size() == 0) {
    return;
  }
  heaps[ind].erase();
}


template<template<class> class H, typename T>
void meld(std::vector<H<T>> &heaps, std::mt19937 &rnd) {
  if (heaps.size() < 2) {
    return;
  }

  int ind1 = (rnd()) % heaps.size();
  int ind2 = (rnd()) % heaps.size();
  heaps[ind1].merge(heaps[ind2]);
}


template<template<class> class H, typename T>
std::vector<T> run_test(int seed, int iters) {
  std::mt19937 rnd(seed);
  std::vector<H<T>> heaps;
  std::vector<T> result;
  for (int i = 0; i < iters; ++i) {
    uint v = rnd() % 5;
    if (v == 0) {
      addHeap(heaps, rnd);
    } else if (v == 1) {
      insert(heaps, rnd);
    } else if (v == 2) {
      result.push_back(getMin(heaps, rnd));
    } else if (v == 3) {
      extractMin(heaps, rnd);
    } else {
      meld(heaps, rnd);
    }
  }
  return result;
}


TEST(BinomialHeapTest, correctStressTest) {
  int seed = 13;
  int iter = 2000;

  auto res1 = run_test<TestHeap, int>(seed, iter);
  auto res2 = run_test<BinomialHeap, int>(seed, iter);
  ASSERT_EQ(res1, res2);
}

TEST(LeftistHeapTest, correctStressTest) {
  int seed = 13;
  int iter = 2000;

  auto res1 = run_test<TestHeap, int>(seed, iter);
  auto res2 = run_test<LeftistHeap, int>(seed, iter);
  ASSERT_EQ(res1, res2);
}

TEST(SkewHeapTest, correctStressTest) {
  int seed = 13;
  int iter = 2000;

  auto res1 = run_test<TestHeap, int>(seed, iter);
  auto res2 = run_test<SkewHeap, int>(seed, iter);
  ASSERT_EQ(res1, res2);
}

TEST(BinomialHeapTest, speedStressTest) {
  run_test<BinomialHeap, int>(1, 1e6);
}

TEST(LeftistHeapTest, speedStressTest) {
  run_test<LeftistHeap, int>(1, 1e6);
}

TEST(SkewHeapTest, speedStressTest) {
  run_test<SkewHeap, int>(1, 1e6);
}
