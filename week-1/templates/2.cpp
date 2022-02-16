#include <iostream>
#include <map>
#include <exception>

using namespace std;

template<typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key k);

template<typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key k) {
  if (m.count(k) > 0) {
    return m[k];
  } else {
    throw runtime_error("key is not found");
  }
}

int main() {
  map<int, string> m = {{0, "value"}};
  string& item = GetRefStrict(m, 0);
  item = "newvalue";
  cout << m[0] << endl; // выведет newvalue
  
  return 0;
}
