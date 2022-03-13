#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
  vector<string> words;
  
  auto a = begin(s);
  auto b = find(begin(s), end(s), ' ');
  words.emplace_back(a, b);
  
  while (b != end(s)) {
    a = b + 1;
    b = find(a, end(s), ' ');
  
    words.emplace_back(a, b);
  }
  
  return words;
}

int main() {
  for (const auto& x : SplitIntoWords("Hello world It is me -- Artyom")) {
    cout << x << endl;
  }
  cout << endl;

  for (const auto& x : SplitIntoWords("Hello")) {
    cout << x << endl;
  }
  cout << endl;
  
  string s = "C Cpp Java Python";
  
  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}