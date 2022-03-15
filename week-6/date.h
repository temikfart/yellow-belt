#pragma once

#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <memory>

class Date {
public:
  Date();
  Date(int year, int month, int day);
  
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
  std::string DateToStr() const;
  
private:
  int year_;
  int month_;
  int day_;
};

Date ParseDate(std::istream& is);

std::ostream& operator<<(std::ostream& os, const Date& date);
std::ostream& operator<<(std::ostream& os,
  const std::pair<Date, std::string>& pair);

bool operator<(const Date& lsh, const Date& rhs);
bool operator<=(const Date& lsh, const Date& rhs);
bool operator>(const Date& lsh, const Date& rhs);
bool operator>=(const Date& lsh, const Date& rhs);
bool operator==(const Date& lsh, const Date& rhs);
bool operator!=(const Date& lsh, const Date& rhs);
