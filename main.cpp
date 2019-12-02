#include <bits/stdc++.h> 
#include "binomial_heap.h"
#include "test_heap.h"

using namespace std;

int main() {
  TestHeap<int> a, b;
  a.insert(1);
  a.insert(2);
  a.insert(3);
  b.insert(3);
  b.insert(4);
  b.insert(5);

  TestHeap<int> res = TestHeap<int>::merge(a, b);
  while(res.size()) {
    cout << res.top() << "\n";
    res.erase();
  }
}
