#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }
  
  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const string& str) {
  for (size_t i = 0; i < str.size() / 2; ++i) {
    if (str[i] != str[str.size() - i - 1]) {
      return false;
    }
  }
  return true;
}

void TestIsPalindrom() {
  {
    Assert(IsPalindrom(""),
           "empty string is a palindrome");
    Assert(IsPalindrom("a"),
           "one letter is a palindrome");
    Assert(IsPalindrom("aba aba"),
           "string with two same palindromes is a palindrome");
    Assert(IsPalindrom("wasitacaroracatisaw"),
           "long palindrome is a palindrome");
    Assert(IsPalindrom("^*@%_+/.!$& wow &$!./+_%@*^"),
           "a palindrome with special symbols is the palindrome");
    Assert(IsPalindrom("1234567890 0987654321"),
           "digits shouldn't be ignored");
  }
  {
    Assert(!IsPalindrom("abc"),
           "abc is not a palindrome");
    Assert(!IsPalindrom("Hello, world! My name is Alisa."),
           "'abc laskdhf lk j' is not a palindrome");
    Assert(!IsPalindrom("aaba"),
           "the first symbol shouldn't be ignored");
    Assert(!IsPalindrom("abaa"),
           "last symbol shouldn't be ignored");
    Assert(!IsPalindrom("ZabaX"),
           "the first and last symbols shouldn't be ignored");
    Assert(!IsPalindrom("aba  b a"),
           "whitespaces shouldn't be ignored");
    Assert(!IsPalindrom("Amama"),
           "upper- and lowercase symbol are different");
  }
  {
    Assert(IsPalindrom(""), "0");
    Assert(IsPalindrom("1"), "1");
    Assert(IsPalindrom("22"), "22");
    Assert(IsPalindrom("333"), "333");
    Assert(IsPalindrom("4444"), "4444");
    Assert(IsPalindrom("55055"), "55055");
  
    Assert(IsPalindrom("madam"), "madam");
    Assert(IsPalindrom("level"), "level");
    Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");
  
    Assert(IsPalindrom(" madam "), "= madam =");
    Assert(IsPalindrom("  madam  "), "=  madam  =");
    Assert(IsPalindrom(" ma - d - am "), "= ma - d - am =");
  
    Assert(IsPalindrom("ff"), "ff");
    Assert(IsPalindrom("12aa21"), "12aa21");
  
    Assert(IsPalindrom("madam madam"), "madam madam");
    Assert(IsPalindrom("madam  madam"), "madam  madam");
    Assert(IsPalindrom("madam   madam"), "madam   madam");
    Assert(IsPalindrom("madam madam madam"), "madam madam madam");
  
    Assert(!IsPalindrom("Amama"), "Amama");
    Assert(!IsPalindrom("Sator Arepo Tenet Opera Rotas"), "Sator Arepo Tenet Opera Rotas");
  
    Assert(!IsPalindrom("12aabb"), "12aabb");
  }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestIsPalindrom, "TestIsPalindrom");
  
  return 0;
}
