#include "database.h"

using namespace std;

void Database::Add(const Date& date, const string& event) {
  if (db.count(date)) {
    const auto insert_it = db[date].first.insert(event);
    
    if (insert_it.second)
    {
      db[date].second.push_back(insert_it.first);
    }
  } else {
    auto insert_result = db[date].first.insert(event);
    db[date].second.push_back(insert_result.first);
  }
}
void Database::Print(ostream& is) const {
  for (const auto& date_it : db) {
    for (const auto& event_it : date_it.second.second) {
      is << setw(4) << setfill('0') << date_it.first.GetYear() << '-';
      is << setw(2) << setfill('0') << date_it.first.GetMonth() << '-';
      is << setw(2) << setfill('0') << date_it.first.GetDay();
      is << " " << *event_it << endl;
    }
  }
}
string Database::Last(const Date& date) const {
  const auto itr_upper = db.upper_bound(date);
  
  if (itr_upper == db.begin()) {
    throw invalid_argument("No entries");
  }
  return (prev(itr_upper)->first.DateToStr()
          + " "
          + *prev(itr_upper)->second.second.back());
}
