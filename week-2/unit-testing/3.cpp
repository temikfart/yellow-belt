#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

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

//#define LOCAL
#ifdef LOCAL
class Rational {
public:
  Rational() {
    p = 0;
    q = 1;
  }
  
  Rational(int numerator, int denominator) {
    if (numerator == 0) {
      // 0/1
      p = numerator;
      q = 1;
    } else {
      // Правильность знаков
      if (numerator < 0 && denominator < 0) {
        numerator = abs(numerator);
        denominator = abs(denominator);
      } else if (denominator < 0) {
        denominator = abs(denominator);
        numerator = (-1) * numerator;
      }
      int gcd_num = gcd(abs(numerator), abs(denominator));
      if (gcd_num != 1) {
        numerator /= gcd_num;
        denominator /= gcd_num;
      }
      p = numerator;
      q = denominator;
    }
  }
  
  int Numerator() const {
    return p;
  }
  
  int Denominator() const {
    return q;
  }

private:
  int p;
  int q;
};
#endif

void TestCtors() {
  {
    Rational r;
    AssertEqual(r.Numerator(),
                0,
                "default constructor should create "
                "rational number with zero numerator");
    AssertEqual(r.Denominator(),
                1,
                "default constructor should create "
                "rational number with denominator = 1");
  }
  {
    Rational r(5, 6);
    AssertEqual(r.Numerator(),
                5,
                "constructor should create rational number"
                "with set numerator");
    AssertEqual(r.Denominator(),
                6,
                "constructor should create rational number"
                "with set numerator");
  }
  {
    Rational r(-5, 8);
    Assert((r.Numerator() < 0) && (r.Denominator() > 0),
                "if rational number is negative, "
                "then only numerator is negative");
  }
  {
    Rational r(-5, -9);
    Assert((r.Numerator() > 0) && (r.Denominator() > 0),
                "if numerator and denominator are negative,"
                "then rational number is positive");
  }
  {
    Rational r(5, -10);
    Assert((r.Numerator() == -1) && (r.Denominator() == 2),
           "if numerator and denominator have common divisors,"
           "then constructor should reduce fraction");
  }
  {
    Rational r(5, 5);
    Assert((r.Numerator() == 1) && (r.Denominator() == 1),
           "if numerator and denominator are equal,"
           "then rational number is 1/1");
  }
  {
    Rational r(0, -5);
    Assert((r.Numerator() == 0) && (r.Denominator() == 1),
           "if numerator is zero, then denominator should be 1");
  }
}

void TestGetMethods() {
  {
    Rational r(3, 17);
    AssertEqual(r.Numerator(),
                3,
                "Rational::Numerator() should return correct value");
    AssertEqual(r.Denominator(),
                17,
                "Rational::Denominator() should return correct value");
  }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestCtors, "TestCtors");
  runner.RunTest(TestGetMethods, "TestGetMethods");
  
  return 0;
}
