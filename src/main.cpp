#include <bits/stdc++.h> 
#include "binomial_heap.h"
#include "test_heap.h"


using namespace std;


template<typename T>
void checkOperations() {
  T a;
  a.insert(1);  // [1]
  assert(a.size() == 1);
  assert(a.top() == 1);

  a.insert(1);  // [1, 1]
  assert(a.size() == 2);
  assert(a.top() == 1);

  a.erase();  // [1]
  assert(a.size() == 1);
  assert(a.top() == 1);


  a.insert(-1);  // [-1, 1]
  assert(a.size() == 2);
  assert(a.top() == -1);

  T b;
  b.insert(3);
  b.insert(4);
  b.insert(0);  // [0, 3, 4]

  T a_copy = a;
  assert(a.size() == 2);
  assert(a_copy.size() == 2);

  T b_copy = b;

  T a_move = std::move(a);
  assert(a.size() == 2);
  assert(a_move.size() == 2);

  T res = merge(a, b);
}

int main() {
  cout << "Hello, it's main in src\n";
}
