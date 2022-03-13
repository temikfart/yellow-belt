#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  long dist = distance(range_begin, range_end);
  if (dist < 2) {
    return;
  };

  vector<typename RandomIt::value_type> elements(range_begin, range_end);
  auto delimIt = elements.begin() + (dist / 2);
  
  MergeSort(elements.begin(), delimIt);
  MergeSort(delimIt, elements.end());

  merge(elements.begin(), delimIt, delimIt, elements.end(), range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  
  return 0;
}
