#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename beginIt, typename endIt>
void PrintVector(beginIt a, endIt b) {
  for (; a != b; a++) {
    cout << *a << " ";
  }
  cout << endl;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  long dist = distance(range_begin, range_end);
  if (dist < 2) {
    return;
  };

  vector<typename RandomIt::value_type> elements(range_begin, range_end);

  auto one_third = elements.begin() + (dist / 3);
  auto two_third = elements.begin() + (dist * 2 / 3);
  
  MergeSort(elements.begin(), one_third);
  MergeSort(one_third, two_third);
  MergeSort(two_third, elements.end());
  
  vector<typename RandomIt::value_type> tmp;
  merge(elements.begin(), one_third, one_third, two_third,
        back_inserter(tmp));
  
  merge(tmp.begin(), tmp.end(), two_third, elements.end(),
        range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
