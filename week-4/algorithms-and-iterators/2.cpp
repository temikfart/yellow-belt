#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

void PrintVector(const vector<int>& v) {
  for (int i = 0; i < (int)v.size(); i++) {
    if (i == 0) {
      cout << v[i];
    } else {
      cout << " " << v[i];
    }
  }
}

int main() {
  int N;
  cin >> N;
  
  vector<int> v(N);
  iota(v.rbegin(), v.rend(), 1);
  
  do {
    PrintVector(v);
    cout << endl;
  } while (prev_permutation(begin(v), end(v)));
  
  return 0;
}
