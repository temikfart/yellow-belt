#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>

using namespace std;

void TestParseEvent(); // Тесты для функции ParseEvent
void TestParseDate(); // Тесты для функции ParseDate
void TestEmptyNode(); // Тесты для EmptyNode
void TestDateComparisonNode(); // Тесты для DateComparisonNode
void TestEventComparisonNode(); // Тесты для TestEventComparisonNode
void TestLogicalOperationNode(); // Тесты для TestLogicalOperationNode
void TestInsertionOrder(); // Тесты для db на порядок вставки
void TestAdd(); // Тесты для функции Add
void TestLast(); // Тесты для функции Last
void TestRemove(); // Тесты для функции RemoveIf
void TestFind(); // Тесты для функции FinIf
void TestDatabase(); // Тесты для всего проекта

void TestAll();

string ParseEvent(istream& is) {
  string event;
  getline(is, event);
  return string(find_if(event.begin(),
                        event.end(),
                        [](const unsigned char& c) {
                       return !std::isspace(c);
                     }),
                     event.end());
}

int main() {
  TestAll();
  
  Database db;
  
  for (string line; getline(cin, line); ) {
    istringstream is(line);
    
    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      
      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
        cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
        cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }
  
  return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseDate, "TestParseDate");
  tr.RunTest(TestEmptyNode, "TestEmptyNode");
  tr.RunTest(TestDateComparisonNode, "TestDateComparisonNode");
  tr.RunTest(TestEventComparisonNode, "TestEventComparisonNode");
  tr.RunTest(TestLogicalOperationNode, "TestLogicalOperationNode");
  tr.RunTest(TestInsertionOrder, "TestInsertionOrder");
  tr.RunTest(TestAdd, "TestAdd");
  tr.RunTest(TestLast, "TestLast");
  tr.RunTest(TestRemove, "TestRemoveIf");
  tr.RunTest(TestFind, "TestFindIf");
  tr.RunTest(TestParseCondition, "TestParseCondition");
  tr.RunTest(TestDatabase, "TestDatabase");
}
