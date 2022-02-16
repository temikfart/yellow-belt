#include <iostream>
#include <tuple>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//#define LOCAL
#ifdef LOCAL
enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};
#endif

bool operator<(const Region& lhs, const Region& rhs) {
  return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
    tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
  int result = 0;
  map<Region, int> repetition_count;
  for (const auto& region : regions) {
    repetition_count[region]++;
    result = max(result, repetition_count[region]);
  }
  return result;
}

#ifdef LOCAL
int main() {
  cout << FindMaxRepetitionCount({
    {
      "Moscow",
      "Russia",
      {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
      89
    }, {
      "Russia",
      "Eurasia",
      {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
      89
    }, {
      "Moscow",
      "Russia",
      {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
      89
    }, {
      "Moscow",
      "Russia",
      {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
      89
    }, {
      "Russia",
      "Eurasia",
      {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
      89
    },
  }) << endl;
  
  cout << FindMaxRepetitionCount({
    {
      "Moscow",
      "Russia",
      {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
      89
    }, {
      "Russia",
      "Eurasia",
      {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
      89
    }, {
      "Moscow",
      "Russia",
      {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
      89
    }, {
      "Moscow",
      "Toulouse",
      {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
      89
    }, {
      "Moscow",
      "Russia",
      {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
      31
    },
  }) << endl;
  
  return 0;
}
#endif
