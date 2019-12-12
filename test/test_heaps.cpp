#include <memory>
#include "gtest/gtest.h"
#include "mergeable_heap.h"
#include "test_heap.h"
#include "binomial_heap.h"

template<typename T>
void insertAndEraseTest() {
  T heap;
  ASSERT_EQ(heap.size(), 0);

  heap.insert(0);
  ASSERT_EQ(heap.size(), 1);

  heap.insert(1);
  ASSERT_EQ(heap.size(), 2);

  ASSERT_EQ(heap.top(), 0);

  heap.erase();
  ASSERT_EQ(heap.size(), 1);

  heap.insert(std::move(-1));
  ASSERT_EQ(heap.size(), 2);
  ASSERT_EQ(heap.top(), -1);

  heap.insert(heap.top());
  ASSERT_EQ(heap.size(), 3);
}

template<typename T>
void mergeTest() {
  T heap_a, heap_b;
  heap_a.insert(1);
  heap_b.insert(2);

  heap_a.merge(heap_b);
  ASSERT_EQ(heap_a.size(), 2);
  ASSERT_EQ(heap_b.size(), 0);
  ASSERT_EQ(heap_a.top(), 1);

  T heap_c;
  heap_c.merge(std::move(heap_a));
  ASSERT_EQ(heap_c.size(), 2);

  heap_b.swap(heap_c);
  ASSERT_EQ(heap_b.size(), 2);

  heap_b.merge(heap_b);
  ASSERT_EQ(heap_b.size(), 2);

  heap_b.merge(std::move(heap_b));
  ASSERT_EQ(heap_b.size(), 2);
}

template<typename T>
void copyAndMoveTest() {
  T heap_a, heap_b;

  heap_a.insert(1);

  heap_b.insert(2);
  heap_b.insert(3);

  heap_a = heap_b;
  ASSERT_EQ(heap_a.size(), 2);
  ASSERT_EQ(heap_a.top(), 2);
  ASSERT_EQ(heap_b.size(), 2);
  ASSERT_EQ(heap_b.top(), 2);

  T heap_c(heap_b);
  ASSERT_EQ(heap_c.size(), 2);
  ASSERT_EQ(heap_b.size(), 2);

  T heap_e(std::move(heap_c));
  ASSERT_EQ(heap_e.size(), 2);
  ASSERT_EQ(heap_c.size(), 0);

  heap_c = std::move(heap_e);
  ASSERT_EQ(heap_c.size(), 2);
  ASSERT_EQ(heap_e.size(), 0);
}

template<typename T>
void pointerIHeap() {
  std::unique_ptr<IHeap<int>> heap_a(new T());
  std::unique_ptr<IHeap<int>> heap_b(new T());

  heap_a->insert(1);
  heap_b->insert(2);
  ASSERT_EQ(heap_a->size(), 1);
  ASSERT_EQ(heap_a->top(), 1);
  ASSERT_EQ(heap_b->size(), 1);
  ASSERT_EQ(heap_b->top(), 2);
}

TEST(TestHeapTest, insertAndErase) {
  insertAndEraseTest<TestHeap<int>>();
}

TEST(TestHeapTest, merge) {
  mergeTest<TestHeap<int>>();
}

TEST(TestHeapTest, copyAndMove) {
  copyAndMoveTest<TestHeap<int>>();
}

TEST(TestHeapTest, pointerIHeap) {
  pointerIHeap<TestHeap<int>>();
}


TEST(BinomialHeapTest, insertAndErase) {
  insertAndEraseTest<BinomialHeap<int>>();
}

TEST(BinomialHeapTest, merge) {
  mergeTest<BinomialHeap<int>>();
}

TEST(BinomialHeapTest, copyAndMove) {
  copyAndMoveTest<BinomialHeap<int>>();
}

TEST(BinomialHeapTest, pointerIHeap) {
  pointerIHeap<BinomialHeap<int>>();
}
 