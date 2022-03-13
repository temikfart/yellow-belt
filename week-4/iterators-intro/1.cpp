#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
  if (numbers.empty()) {
    return;
  }
  auto it = begin(numbers);
  while (it != end(numbers) && (*it) >= 0) {
    it++;
  }
  
  for (it--; it >= begin(numbers); it--) {
    if (it == begin(numbers)) {
      cout << *it;
    } else {
      cout << *it << " ";
    }
  }
}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  PrintVectorPart({});
  cout << endl;
  
  return 0;
}
