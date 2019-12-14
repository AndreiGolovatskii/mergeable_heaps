#ifndef MERGEABLE_HEAP_H_
#define MERGEABLE_HEAP_H_

#include <unordered_map>

template<typename T>
class IHeap{
 public:
  IHeap() {}
  virtual void insert(const T &a) = 0;
  virtual void insert(T &&a) = 0;

  virtual const T top() const = 0;

  virtual size_t size() const = 0;

  virtual void erase() = 0;
  virtual void clear() = 0;

  virtual ~IHeap() {}

  // virtual void merge(IHeap<T> &other);
 private:
  IHeap &operator=(const IHeap &other);
  IHeap(const IHeap<T> &other);
};

#endif  // MERGEABLE_HEAP_H_
