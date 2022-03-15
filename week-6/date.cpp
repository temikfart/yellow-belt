#include "date.h"

using namespace std;

Date::Date() : year_(0), month_(0), day_(0) {}
Date::Date(int year, int month, int day) {
  if (month > 12 || month < 1) {
    string error = "Month value is invalid: " + to_string(month);
    throw logic_error(error);
  } else {
    month_ = month;
  }
  
  if (day > 31 || day < 1) {
    string error = "Day value is invalid: " + to_string(day);
    throw logic_error(error);
  } else {
    day_ = day;
  }
  year_ = year;
}
int Date::GetYear() const {
  return year_;
}
int Date::GetMonth() const {
  return month_;
}
int Date::GetDay() const {
  return day_;
}
string Date::DateToStr() const {
  stringstream ss;
  ss << *this;
  return ss.str();
}
Date ParseDate(istream& is) {
  string str_date;
  is >> str_date;
  
  stringstream str_stream_date(str_date);
  
  int year = -1;
  str_stream_date >> year;
  
  if (str_stream_date.fail() || str_stream_date.peek() != '-') {
    throw logic_error("Wrong date format: " + str_date);
  }
  str_stream_date.ignore();
  
  int month = -1;
  str_stream_date >> month;
  
  if (str_stream_date.fail() || str_stream_date.peek() != '-') {
    throw logic_error("Wrong date format: " + str_date);
  }
  str_stream_date.ignore();
  
  int day = -1;
  str_stream_date >> day;
  
  if (str_stream_date.fail() || !str_stream_date.eof()) {
    throw logic_error("Wrong date format: " + str_date);
  }
  return {year, month, day};
}
ostream& operator<<(std::ostream& os, const Date& date) {
  os << setw(4) << setfill('0') << date.GetYear() << '-';
  os << setw(2) << setfill('0') << date.GetMonth() << '-';
  os << setw(2) << setfill('0') << date.GetDay();
  return os;
}
ostream& operator<<(ostream& os, const pair<Date, string>& pair) {
  os << pair.first << " " << pair.second;
  return os;
}
bool operator<(const Date& lhs, const Date& rhs) {
  return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
         make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
}
bool operator<=(const Date& lhs, const Date& rhs) {
  return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <=
         make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
}
bool operator>(const Date& lhs, const Date& rhs) {
  return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >
         make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
}
bool operator>=(const Date& lhs, const Date& rhs) {
  return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >=
          make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
}
bool operator==(const Date& lhs, const Date& rhs) {
  return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
          make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
}
bool operator!=(const Date& lhs, const Date& rhs) {
  return (make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) !=
          make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
}
