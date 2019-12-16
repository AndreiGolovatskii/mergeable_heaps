#ifndef BINOMIAL_HEAP_H_
#define BINOMIAL_HEAP_H_

#include <utility>
#include <memory>
#include "mergeable_heap.h"

template<typename T>
class BinomialHeap: public IHeap<T> {
 public: public:
  BinomialHeap();
  BinomialHeap(const BinomialHeap<T> &src);
  BinomialHeap(BinomialHeap<T> &&src);

  void swap(BinomialHeap<T> &other);

  size_t size() const;

  void insert(const T &a);
  void insert(T &&a);

  const T top() const;

  void erase();
  void clear();

  void merge(BinomialHeap<T> &b);
  void merge(BinomialHeap<T> &&b);

  // void merge(IHeap<T> &other);

  BinomialHeap<T> &operator=(BinomialHeap<T> &&src);
  BinomialHeap<T> &operator=(const BinomialHeap<T> &src);

  // IHeap<T> &operator=(const IHeap<T> &other);

  ~BinomialHeap();

 private:
  struct Node_{
    T key;
    std::shared_ptr<Node_> child, sibling;
    size_t degree;
    Node_(const T &key,
          size_t degree)
          : key(key),
            child(0),
            sibling(0),
            degree(degree) {}
    Node_(T &&key,
          size_t degree)
          : key(key),
            child(0),
            sibling(0),
            degree(degree) {}
  };
  static std::shared_ptr<Node_> deepCopy_(const std::shared_ptr<Node_> &head);
  static std::shared_ptr<Node_> merge_(std::shared_ptr<Node_> a,
                                       std::shared_ptr<Node_> b);
  std::shared_ptr<Node_> findMinNode_() const;

  std::shared_ptr<Node_> head_;
  size_t size_;
};

template<typename T>
BinomialHeap<T>::BinomialHeap(): head_(nullptr), size_(0) {
}

template<typename T>
BinomialHeap<T>::BinomialHeap(const BinomialHeap<T> &src)
: IHeap<T>(), head_(deepCopy_(src.head_)), size_(src.size_) {
}

template<typename T>
BinomialHeap<T>::BinomialHeap(BinomialHeap<T> &&src): BinomialHeap() {
  swap(src);
}

template<typename T>
size_t BinomialHeap<T>::size() const {
  return size_;
}

template<typename T>
BinomialHeap<T>::~BinomialHeap() {}

template<typename T>
BinomialHeap<T> &BinomialHeap<T>::operator=(const BinomialHeap<T> &src) {
  BinomialHeap tmp(src);
  swap(tmp);
  return *this;
}

template<typename T>
BinomialHeap<T> &BinomialHeap<T>::operator=(BinomialHeap<T> &&src) {
  swap(src);
  return *this;
}

template<typename T>
void BinomialHeap<T>::swap(BinomialHeap<T> &other) {
  head_.swap(other.head_);
  std::swap(size_, other.size_);
}

template<typename T>
void BinomialHeap<T>::insert(const T &a) {
  insert(T(a));
}

template<typename T>
void BinomialHeap<T>::insert(T &&a) {
  BinomialHeap<T> other;
  other.head_ = std::shared_ptr<Node_>(new Node_(a, 1));
  other.size_ = 1;

  merge(std::move(other));
}

template<typename T>
void BinomialHeap<T>::erase() {
  BinomialHeap<T> other;

  std::shared_ptr<Node_> min_node = findMinNode_();

  other.head_ = min_node->child;
  other.size_ = min_node->degree - 1;

  size_ -= min_node->degree;

  std::shared_ptr<Node_> current = head_;
  if (current == min_node) {
    head_ = current->sibling;
  } else {
    while (current->sibling != min_node) {
      current = current->sibling;
    }
    current->sibling = min_node->sibling;
  }
  merge(other);
}

template<typename T>
void BinomialHeap<T>::clear() {
  head_ = nullptr;
  size_ = 0;
}

template<typename T>
const T BinomialHeap<T>::top() const {
  return findMinNode_()->key;
}

template<typename T>
void BinomialHeap<T>::merge(BinomialHeap<T> &other) {
  merge(std::move(other));
}

template<typename T>
void BinomialHeap<T>::merge(BinomialHeap<T> &&other) {
  if (&other == this) {
    return;
  }
  std::shared_ptr<Node_> first = head_;
  std::shared_ptr<Node_> second = other.head_;

  head_ = nullptr;
  size_ += other.size();

  other.head_ = nullptr;
  other.size_ = 0;

  std::shared_ptr<Node_> res = nullptr;

  while (first != nullptr || second != nullptr) {
    size_t first_degree = first ? first->degree : second->degree + 1;
    size_t second_degree = second ? second->degree : first->degree + 1;

    std::shared_ptr<Node_> next_first = first ? first->sibling : nullptr;
    std::shared_ptr<Node_> next_second = second ? second->sibling : nullptr;
    std::shared_ptr<Node_> tmp;

    if (first_degree == second_degree) {
      tmp = merge_(first, second);
      first = next_first;
      second = next_second;
    } else {
      if (first_degree > second_degree) {
        std::swap(first, second);
        std::swap(next_first, next_second);
      }
      tmp = first;
      tmp->sibling = nullptr;
      first = next_first;
    }
    if (res == nullptr) {
      res = tmp;
      head_ = res;
    } else {
      res->sibling = tmp;
      res = res->sibling;
    }
  }

  std::shared_ptr<Node_> curr = head_;
  std::shared_ptr<Node_> prev = nullptr;
  while (curr && curr->sibling) {
    if (curr->degree == curr->sibling->degree) {
      std::shared_ptr<Node_> nxt = curr->sibling->sibling;
      std::shared_ptr<Node_> tmp = merge_(curr, curr->sibling);

      if (prev == nullptr) {
        head_ = tmp;
      } else {
        prev->sibling = tmp;
      }

      tmp->sibling = nxt;
      curr = tmp;
    } else {
      prev = curr;
      curr = curr->sibling;
    }
  }
}

template<typename T>
std::shared_ptr<typename BinomialHeap<T>::Node_>
BinomialHeap<T>::merge_(std::shared_ptr<Node_> a,
                        std::shared_ptr<Node_> b) {
  assert(a->degree == b->degree);
  if (a->key > b->key) {
    std::swap(a, b);
  }
  a->sibling = b->sibling = nullptr;
  std::shared_ptr<Node_> res = a;
  res->degree += b->degree;
  if (res->child == nullptr) {
    res->child = b;
  } else {
    std::shared_ptr<Node_> ch = res->child;
    while (ch->sibling != nullptr) {
      ch = ch->sibling;
    }
    ch->sibling = b;
  }
  return res;
}

template<typename T>
std::shared_ptr<typename BinomialHeap<T>::Node_>
BinomialHeap<T>::deepCopy_(const std::shared_ptr<Node_> &head) {
  if (head == nullptr) {
    return nullptr;
  }
  std::shared_ptr<Node_> new_head(new Node_(head->key, head->degree));
  new_head->sibling = deepCopy_(head->sibling);
  new_head->child = deepCopy_(head->child);
  return new_head;
}

template<typename T>
std::shared_ptr<typename BinomialHeap<T>::Node_>
BinomialHeap<T>::findMinNode_() const {
  std::shared_ptr<Node_> ans = head_, current = head_;
  while (current) {
    if (current->key < ans->key) {
      ans = current;
    }
    current = current->sibling;
  }
  return ans;
}

#endif  // SRC_BINOMIAL_HEAP_H_
