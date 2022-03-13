#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

#define LOCAL
#ifdef LOCAL
enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
    begin(range_copy), middle, end(range_copy),
    [](const Person& lhs, const Person& rhs) {
      return lhs.age < rhs.age;
    }
  );
  return middle->age;
}
#endif

void PrintStats(vector<Person> persons) {
  auto beginIt = persons.begin();
  auto endIt = persons.end();
  
  /* Median age */
  int res = ComputeMedianAge(persons.begin(), persons.end());
  cout << "Median age = " << res << endl;
  
  /* Median age for females */
  auto delimIt = partition(beginIt, endIt,
                           [](Person p){
                             return (p.gender == Gender::FEMALE);
                           });
  res = ComputeMedianAge(beginIt, delimIt);
  cout << "Median age for females = " << res << endl;
  
  /* Median age for males */
  res = ComputeMedianAge(delimIt, endIt);
  cout << "Median age for males = " << res << endl;
  
  /* Median age for employed females */
  auto delimIt2 = partition(beginIt, delimIt,
            [](Person p) {
              return (p.is_employed == true);
            });
  res = ComputeMedianAge(beginIt, delimIt2);
  cout << "Median age for employed females = " << res << endl;
  
  /* Median age for unemployed females */
  res = ComputeMedianAge(delimIt2, delimIt);
  cout << "Median age for unemployed females = " << res << endl;
  
  /* Median age for employed males */
  delimIt2 = partition(delimIt, endIt,
                            [](Person p) {
                              return (p.is_employed == true);
                            });
  res = ComputeMedianAge(delimIt, delimIt2);
  cout << "Median age for employed males = " << res << endl;
  
  /* Median age for unemployed males */
  res = ComputeMedianAge(delimIt2, endIt);
  cout << "Median age for unemployed males = " << res << endl;
}

#ifdef LOCAL
int main() {
  vector<Person> persons = {
    {31, Gender::MALE, false},
    {40, Gender::FEMALE, true},
    {24, Gender::MALE, true},
    {20, Gender::FEMALE, true},
    {80, Gender::FEMALE, false},
    {78, Gender::MALE, false},
    {10, Gender::FEMALE, false},
    {55, Gender::MALE, true},
  };
  PrintStats(persons);
  
  return 0;
}
#endif
