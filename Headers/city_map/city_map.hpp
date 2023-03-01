#pragma once

#include "macroses.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace sprsim {
class city_map {
public:
  using map_container = std::vector<std::string>;

  city_map(const std::string &filename);
  const map_container &get() const { return m_city_map; }

private:
  map_container m_city_map;
};
} // namespace sprsim