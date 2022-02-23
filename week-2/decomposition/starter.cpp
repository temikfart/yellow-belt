#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string operation_code;
  cin >> operation_code;
  
  if (operation_code == "NEW_BUS") {
  
    q.type = QueryType::NewBus;
    cin >> q.bus;
    int stop_count;
    cin >> stop_count;
    q.stops.resize(stop_count);
    for (string& stop : q.stops) {
      cin >> stop;
    }
    
  } else if (operation_code == "BUSES_FOR_STOP") {
  
    q.type = QueryType::BusesForStop;
    cin >> q.stop;
    
  } else if (operation_code == "STOPS_FOR_BUS") {
  
    q.type = QueryType::StopsForBus;
    cin >> q.bus;
    
  } else if (operation_code == "ALL_BUSES") {
    
    q.type = QueryType::AllBuses;
    
  }
  
  return is;
}

struct BusesForStopResponse {
  vector<string> buses_for_stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses_for_stop.empty()) {
    os << "No stop" << endl;
  } else {
    for (const string& bus : r.buses_for_stop) {
      os << bus << " ";
    }
    os << endl;
  }
  
  return os;
}

struct StopsForBusResponse {
  string bus;
  vector<string> stops_for_bus;
  map<string, vector<string>> buses_for_stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stops_for_bus.empty()) {
    os << "No bus" << endl;
  } else {
    for (const string& stop : r.stops_for_bus) {
      os << "Stop " << stop << ": ";
      if (r.buses_for_stops.at(stop).size() == 1) {
        os << "no interchange";
      } else {
        for (const string& other_bus : r.buses_for_stops.at(stop)) {
          if (r.bus != other_bus) {
            os << other_bus << " ";
          }
        }
      }
      os << endl;
    }
  }
  
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.buses_to_stops.empty()) {
    os << "No buses" << endl;
  } else {
    for (const auto& bus_item : r.buses_to_stops) {
      os << "Bus " << bus_item.first << ": ";
      for (const string& stop : bus_item.second) {
        os << stop << " ";
      }
      os << endl;
    }
  }
  
  return os;
}

class BusManager {
private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const string& stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
  }
  
  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse r;
    if (stops_to_buses.count(stop) > 0) {
      r.buses_for_stop = stops_to_buses.at(stop);
    }
    
    return r;
  }
  
  StopsForBusResponse GetStopsForBus(const string& bus) const {
    StopsForBusResponse r;
    r.bus = bus;
    if (buses_to_stops.count(bus) > 0) {
      r.stops_for_bus = buses_to_stops.at(bus);
    }
    for (const string& stop : r.stops_for_bus) {
      r.buses_for_stops[stop] = stops_to_buses.at(stop);
    }
    
    return r;
  }
  
  AllBusesResponse GetAllBuses() const {
    AllBusesResponse r;
    r.buses_to_stops = buses_to_stops;
    
    return r;
  }
};

int main() {
  int query_count;
  Query q;
  
  cin >> query_count;
  
  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
      case QueryType::NewBus:
        bm.AddBus(q.bus, q.stops);
        break;
      case QueryType::BusesForStop:
        cout << bm.GetBusesForStop(q.stop) << endl;
        break;
      case QueryType::StopsForBus:
        cout << bm.GetStopsForBus(q.bus) << endl;
        break;
      case QueryType::AllBuses:
        cout << bm.GetAllBuses() << endl;
        break;
    }
  }
  
  return 0;
}
