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
  
  char last_op = 0;
  for (size_t i = 0; i < size; i++) {
    char operation = 0;
    cin >> operation;
    
    int value = 0;
    cin >> value;
    
    if ((last_op == '+' || last_op == '-')
        && (operation == '*' || operation == '/')) {
      expr.push_front("(");
      expr.push_back(")");
    }
    expr.push_back(" ");
    expr.push_back(std::string(1, operation));
    expr.push_back(" ");
    expr.push_back(std::to_string(value));
    last_op = operation;
  }
  
  for (auto& item : expr) {
    cout << item;
  }
  
  return 0;
}
