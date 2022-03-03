#include "bus_manager.h"

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
  buses_to_stops[bus] = stops;
  for (const string& stop : stops) {
    stops_to_buses[stop].push_back(bus);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
  BusesForStopResponse r;
  if (stops_to_buses.count(stop) > 0) {
    r.buses_for_stop = stops_to_buses.at(stop);
  }
  
  return r;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
  AllBusesResponse r;
  r.buses_to_stops = buses_to_stops;
  
  return r;
}
