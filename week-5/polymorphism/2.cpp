#include <iostream>
#include <sstream>
#include <memory>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

class Figure {
public:
  Figure(string name) : name_(name) {}
  
  virtual string Name() = 0;
  virtual double Perimeter() = 0;
  virtual double Area() = 0;
protected:
  const string name_;
};

class Triangle : public Figure {
public:
  Triangle(int a, int b, int c)
    : Figure("TRIANGLE"), a_(a), b_(b), c_(c) {}
  string Name() override {
    return name_;
  }
  double Perimeter() override {
    return (a_ + b_ + c_);
  }
  double Area() override {
    double p = Perimeter() / 2;
    return sqrt(p * (p - a_) * (p - b_) * (p - c_) );
  }
  
private:
  int a_, b_, c_;
};

class Rect : public Figure {
public:
  Rect(int width, int height)
    : Figure("RECT"), width_(width), height_(height) {}
  string Name() override {
    return name_;
  }
  double Perimeter() override {
    return (2 * (width_ + height_));
  }
  double Area() override {
    return (width_ * height_);
  }

private:
  int width_, height_;
};

class Circle : public Figure {
public:
  Circle(int r)
    : Figure("CIRCLE"), r_(r) {}
  string Name() override {
    return name_;
  }
  double Perimeter() override {
    return (2 * 3.14 * r_);
  }
  double Area() override {
    return (3.14 * r_ * r_);
  }

private:
  int r_;
};

shared_ptr<Figure> CreateFigure(istream& is) {
  string figure_type;
  is >> figure_type;
  
  if (figure_type == "RECT") {
    int width, height;
    is >> width >> height;
    
    return make_shared<Rect>(width, height);
  } else if (figure_type == "TRIANGLE") {
    int a, b, c;
    is >> a >> b >> c;
    
    return make_shared<Triangle>(a, b, c);
  } else if (figure_type == "CIRCLE") {
    int r;
    is >> r;
    
    return make_shared<Circle>(r);
  }
  return nullptr;
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);
    
    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
