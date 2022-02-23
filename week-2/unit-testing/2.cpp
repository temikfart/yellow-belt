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

//#define LOCAL
#ifdef LOCAL
class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    // добавить факт изменения имени на first_name в год year
    names[year].first_name = first_name;
    changes[year].first = true;
  }
  void ChangeLastName(int year, const string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
    names[year].last_name = last_name;
    changes[year].last = true;
  }
  string GetFullName(int year) {
    // получить имя и фамилию по состоянию на конец года year
    
    // has part of name
    int first_y, last_y;
    first_y = -1;
    last_y = -1;
    for (const auto& [key, value] : changes) {
      if (key <= year) {
        if (value.first) {
          first_y = key;
        }
        if (value.last) {
          last_y = key;
        }
      }
    }
    
    string part;
    if (first_y == -1 && last_y == -1) {
      return "Incognito";
    }
    if (first_y == -1) {
      part = names[last_y].last_name + " with unknown first name";
      return part;
    }
    if (last_y == -1) {
      part = names[first_y].first_name + " with unknown last name";
      return part;
    }
    
    
    // has fullname
    string fullname;
    fullname = names[first_y].first_name + " " + names[last_y].last_name;
    return fullname;
  }
private:
  struct name {
    string first_name;
    string last_name;
  };
  struct has_chng {
    bool first;
    bool last;
  };
  map<int, name> names;
  map<int, has_chng> changes;
};
#endif

void TestIncognito() {
  string response = "Incognito";
  {
    Person p;
    AssertEqual(p.GetFullName(2022),
                response,
                "person without first name and last name is incognito");
  }
  {
    Person p;
    p.ChangeFirstName(2022, "Alex");
    AssertEqual(p.GetFullName(1980),
                response,
                "person's first name is changed later");
  }
  {
    Person p;
    p.ChangeLastName(2001, "Artyom");
    AssertEqual(p.GetFullName(1950),
                response,
                "person's last name is changed later");
  }
  {
    Person p;
    p.ChangeFirstName(2002, "Katya");
    p.ChangeLastName(2001, "Ivanova");
    p.ChangeFirstName(2005, "Olesya");
    AssertEqual(p.GetFullName(1999),
                response,
                "person's full name is changed later");
  }
}

void TestWithoutFirstname() {
  string part_response = " with unknown first name";
  {
    Person p;
    string lastname = "Ivanov";
    p.ChangeLastName(1986, lastname);
    AssertEqual(p.GetFullName(1986),
                lastname + part_response,
                "person changed only last name at the same year");
    AssertEqual(p.GetFullName(1987),
                lastname + part_response,
                "person changed only last name before");
  }
  string lastname1 = "Ivanov";
  string lastname2 = "Petrov";
  {
    Person p;
    p.ChangeLastName(1990, lastname1);
    p.ChangeLastName(1995, lastname2);
    AssertEqual(p.GetFullName(1992),
                lastname1 + part_response,
                "person changed once only last name");
    AssertEqual(p.GetFullName(1996),
                lastname2 + part_response,
                "person changed twice only last name");
  }
  {
    Person p;
    string firstname = "Ivan";
    p.ChangeLastName(1990, lastname1);
    p.ChangeLastName(1995, lastname2);
    p.ChangeFirstName(1993, firstname);
    AssertEqual(p.GetFullName(1992),
                lastname1 + part_response,
                "person change first name later");
  }
}

void TestWithoutLastname() {
  string part_response = " with unknown last name";
  {
    Person p;
    string firstname = "Ivan";
    p.ChangeFirstName(1986, firstname);
    AssertEqual(p.GetFullName(1986),
                firstname + part_response,
                "person changed only first name at the same year");
    AssertEqual(p.GetFullName(1987),
                firstname + part_response,
                "person changed only first name before");
  }
  string firstname1 = "Ivan";
  string firstname2 = "Petr";
  {
    Person p;
    p.ChangeFirstName(1990, firstname1);
    p.ChangeFirstName(1995, firstname2);
    AssertEqual(p.GetFullName(1992),
                firstname1 + part_response,
                "person changed once only first name");
    AssertEqual(p.GetFullName(1996),
                firstname2 + part_response,
                "person changed twice only first name");
  }
  {
    Person p;
    string lastname = "Ivanov";
    p.ChangeFirstName(1990, firstname1);
    p.ChangeFirstName(1995, firstname2);
    p.ChangeLastName(1993, lastname);
    AssertEqual(p.GetFullName(1992),
                firstname1 + part_response,
                "person change last name later");
  }
}

void TestFullName() {
  string firstname1 = "Ivan";
  string firstname2 = "Petr";
  
  string lastname1 = "Ivanov";
  string lastname2 = "Petrov";
  
  {
    Person p;
    p.ChangeFirstName(2001, firstname1);
    p.ChangeLastName(2003, lastname1);
    AssertEqual(p.GetFullName(2003),
                firstname1 + " " + lastname1,
                "person changed first name before "
                "and last name at the same year");
    AssertEqual(p.GetFullName(2004),
                firstname1 + " " + lastname1,
                "person changed first name and last name before");
    
    p.ChangeLastName(2004, lastname2);
    AssertEqual(p.GetFullName(2005),
                firstname1 + " " + lastname2,
                "person changed first name once and last name twice");
    AssertEqual(p.GetFullName(2003),
                firstname1 + " " + lastname1,
                "person changed last name at the second time later");
    
    p.ChangeFirstName(2007, firstname2);
    AssertEqual(p.GetFullName(2008),
                firstname2 + " " + lastname2,
                "person changed first name and last name twice");
    AssertEqual(p.GetFullName(2006),
                firstname1 + " " + lastname2,
                "person changed first name at the second time later");
  }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestIncognito, "TestIncognito");
  runner.RunTest(TestWithoutFirstname, "TestWithoutFirstname");
  runner.RunTest(TestWithoutLastname, "TestWithoutLastname");
  runner.RunTest(TestFullName, "TestFullName");
  
  return 0;
}
