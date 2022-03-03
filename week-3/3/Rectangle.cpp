#include <iostream>
#include "Rectangle.h"

using namespace std;

Rectangle::Rectangle(int width, int height) {
  width_ = width;
  height_ = height;
}

int Rectangle::GetArea() const {
  return width_ * height_;
}
  
int Rectangle::GetPerimeter() const {
  return 2 * (width_ + height_);
}

int Rectangle::GetWidth() const { return width_; }
int Rectangle::GetHeight() const { return height_; }

#define LOCAL
#ifdef LOCAL

int main() {
  Rectangle r(5,6);
  cout << "Rectangle r: " << r.GetWidth() << "x" << r.GetHeight()
        << "; Square = " << r.GetArea()
        << " and Perimeter = " << r.GetPerimeter() << endl;
  
  return 0;
}

#endif