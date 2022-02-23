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

int SolveQuadraticEquation(double a, double b, double c) {
  double D = b * b - 4 * a * c;
  if (D > 0) {
    return 2;
  } else if (D == 0) {
    return 1;
  } else {
    return 0;
  }
}

int SolveLinearEquation(double b, double c) {
  if (b != 0) {
    return 1;
  } else {
    return 0;
  }
}

int GetDistinctRealRootCount(double a, double b, double c) {
  if (a == 0) {
    return SolveLinearEquation(b, c);
  } else {
    return SolveQuadraticEquation(a, b, c);
  }
}

void TestLinearEquation() {
  AssertEqual(GetDistinctRealRootCount(0, 1, 2),
              1,
              "linear equation should have 1 root");
  AssertEqual(GetDistinctRealRootCount(0, 0, 2),
              0,
              "c = 0 have infinity amount of roots");
  AssertEqual(GetDistinctRealRootCount(0, 5, 0),
              1,
              "bx = 0 has only 1 root, it's a zero");
}

void TestQuadraticEquation() {
  AssertEqual(GetDistinctRealRootCount(5, 10, 5),
              1,
              "square of sum has only 1 distinct root");
  AssertEqual(GetDistinctRealRootCount(19, 15, -34),
              2,
              "quadratic equation has two roots");
  AssertEqual(GetDistinctRealRootCount(1.5, 12.64, -162.236),
              2,
              "quadratic equation with real coefficients has two roots");
  AssertEqual(GetDistinctRealRootCount(7, 0, 2),
              0,
              "negative square x has zero roots");
  AssertEqual(GetDistinctRealRootCount(5, 2, 0),
              2,
              "quadratic equation with c = 0 has two roots");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestLinearEquation, "TestLinearEquation");
  runner.RunTest(TestQuadraticEquation, "TestQuadraticEquation");
  
  return 0;
}
