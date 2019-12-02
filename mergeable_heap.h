#ifndef MERGEABLE_HEAP_H_
#define MERGEABLE_HEAP_H_

template<typename T>
class IHeap{
 public:
  virtual void insert(T &&a) = 0;
  virtual const T top() const = 0;
  virtual void erase() = 0;
};

#endif  // MERGEABLE_HEAP_H_
