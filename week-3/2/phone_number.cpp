#include "phone_number.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void PrintVector(const vector<string> vs) {
  for (const auto& s : vs) {
    cout << s << endl;
  }
}

PhoneNumber::PhoneNumber(const string &international_number) {
  // Validating
  size_t phone_len = international_number.length();
  if (phone_len == 0) {
    throw invalid_argument("Empty number");
  }
  if (international_number[0] != '+') {
    throw invalid_argument("Incorrect number: + must be first");
  }
  for (size_t i = 1; i < phone_len; i++) {
    if (international_number[i-1] == '-'
        && international_number[i] == '-') {
      throw invalid_argument("Incorrect number: more than 1 dash in a row");
    }
  }
  
  int a = 1;
  int b = 1;
  int dash_counter = 0;
  bool is_valid = true;
  
  while (is_valid) {
    if (dash_counter == 2) {
      local_number_ = international_number.substr(b, phone_len);
      break;
    }
    
    while (international_number[b] != '-') {
      b++;
      if (b >= phone_len) {
        is_valid = false;
        break;
      }
    }
    
    if (is_valid) {
      dash_counter++;
    } else {
      break;
    }
    
    string token = international_number.substr(a, b - a);
    switch (dash_counter) {
      case 1:
        country_code_ = token;
        break;
      case 2:
        city_code_ = token;
        break;
      default:
        cout << "switch-default: something went wrong.";
    }
    
    b++;
    a = b;
  }
  if (!is_valid) {
    throw invalid_argument("Incorrect number");
  }
  
  cout << GetInternationalNumber() << endl;
}

string PhoneNumber::GetCountryCode() const {
  return country_code_;
}
string PhoneNumber::GetCityCode() const {
  return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
  return local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
  return ("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}

//#define LOCAL
#ifdef LOCAL
int main() {
  PhoneNumber phone0("+7-495-111-22-33");
  PhoneNumber phone1("+7--495-111-22-33");
//  PhoneNumber phone2("+7-495-1112233");
//  PhoneNumber phone3("+323-22-460002");
//  PhoneNumber phone4("+1-2-coursera-cpp");
//  PhoneNumber phone5("1-2-333");
//  PhoneNumber phone6("+7-1233");
  
  return 0;
}
#endif
