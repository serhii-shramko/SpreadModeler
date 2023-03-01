#pragma once

#include "macroses.hpp"
#include "types.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace sprsim {
class city_map {
public:
  using map_container = std::vector<std::string>;

  city_map(const std::string &filename);

  const map_container &get() const { return m_city_map; }

  static tile_type get_type_of(char c);

private:
  map_container m_city_map;
  static std::unordered_map<char, tile_type> s_tile_char_map;
};
} // namespace sprsim