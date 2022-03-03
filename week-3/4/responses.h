#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <fstream>

struct BusesForStopResponse {
  std::vector<std::string> buses_for_stop;
};

struct StopsForBusResponse {
  std::string bus;
  std::vector<std::string> stops_for_bus;
  std::map<std::string, std::vector<std::string>> buses_for_stops;
};

struct AllBusesResponse {
  std::map<std::string, std::vector<std::string>> buses_to_stops;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
