#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

int main() {
  int N, R;
  cin >> N >> R;
  
  int W, H, D;
  uint64_t Mass = 0;
  for (int i = 0; i < N; i++) {
    cin >> W >> H >> D;
    Mass += static_cast<uint64_t>(W) * H * D * R;
  }
  
  cout << Mass;
  
  return 0;
}