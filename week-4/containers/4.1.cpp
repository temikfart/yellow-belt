#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main() {
  int number = 0;
  cin >> number;
  
  size_t size = 0;
  cin >> size;
  
  deque<string> expr(size);
  expr.push_back(to_string(number));
  
  for (size_t i = 0; i < size; i++) {
    char operation = 0;
    cin >> operation;
    
    int value = 0;
    cin >> value;
    
    expr.push_front("(");
    expr.push_back(") ");
    expr.push_back(string(1, operation));
    expr.push_back(" ");
    expr.push_back(to_string(value));
  }
  
  for (auto& item : expr) {
    cout << item;
  }
  return 0;
}
