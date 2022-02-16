#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

int main() {
  int N;
  cin >> N;
  if (N <= 0) {
    cout << 0 << endl;
    return 0;
  }
  
  vector<int> t(N);
  int64_t sum = 0;
  for (int i = 0; i < N; i++) {
    cin >> t[i];
    sum += t[i];
  }
  
  int avg;
  avg = static_cast<int>(sum / N);
  
  vector<int> v;
  for (int i = 0; i < N; i++) {
    if (t[i] > avg) {
      v.push_back(i);
    }
  }
  int k = static_cast<int>(v.size());
  
  cout << k << endl;
  for (int i = 0; i < k; i++) {
    if (i > 0) {
      cout << " ";
    }
    cout << v[i];
  }
  
  return 0;
}
