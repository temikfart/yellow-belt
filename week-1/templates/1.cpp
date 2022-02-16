#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

// Предварительное объявление шаблонных функций
template <typename First, typename Second>
pair<First, Second> operator *(
  const pair<First, Second>& lhs,
  const pair<First, Second>& rhs);
template <typename T>
vector<T> operator *(const vector<T>& lhs, const vector<T>& rhs);
template <typename Key, typename Value>
map<Key, Value> operator *(
  const map<Key, Value>& lhs,
  const map<Key, Value>& rhs);
template<typename T> T Sqr(T x);

// Объявляем шаблонные функции
template <typename First, typename Second>
pair<First, Second> operator *(
  const pair<First, Second>& lhs,
  const pair<First, Second>& rhs) {
  return {lhs.first * rhs.first, lhs.second * rhs.second};
}

template <typename T>
vector<T> operator *(const vector<T>& lhs, const vector<T>& rhs) {
  vector<T> vi(lhs.size());
  for (size_t i = 0; i < lhs.size(); i++) {
    vi[i] = lhs[i] * rhs[i];
  }
  return vi;
}

template <typename Key, typename Value>
map<Key, Value> operator *(
  const map<Key, Value>& lhs,
  const map<Key, Value>& rhs) {
  map<Key, Value> m = lhs;
  for (auto& [key, value] : m) {
    value = lhs.at(key) * rhs.at(key);
  }
  return m;
}

template<typename T> T Sqr(T x) {
  x = x * x;
  return x;
}

int main() {
  // Пример вызова функции
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;
  
  map<int, pair<int, int>> map_of_pairs = {
    {4, {2, 2}},
    {7, {4, 3}}
  };
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }
  
  return 0;
}
