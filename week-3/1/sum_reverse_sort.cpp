#include <iostream>
#include <algorithm>
#include "sum_reverse_sort.h"

using namespace std;

int Sum(int x, int y) {
  return x + y;
}

string Reverse(string s) {
  reverse(begin(s), end(s));
  return s;
}
void Sort(vector<int>& nums) {
  sort(begin(nums), end(nums));
}

void PrintVector(const vector<int>& vi) {
  for (const auto& x : vi) {
    cout << x << " ";
  }
  cout << endl;
}

#define LOCAL
#ifdef LOCAL
int main() {
  cout << Sum(-5, 6) << endl;
  cout << Reverse("Hello, world!") << endl;
  
  vector<int> nums = {5, 7, -1, 6, 0, 5, 8, 2, 1};
  PrintVector(nums);
  Sort(nums);
  PrintVector(nums);
  
  return 0;
}
#endif
