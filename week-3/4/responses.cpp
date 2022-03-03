#include "responses.h"

using namespace std;

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