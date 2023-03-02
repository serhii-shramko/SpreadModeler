#pragma once

#include "city_map.hpp"
#include "tile.hpp"

#include <vector>

namespace sprsim {
class field {
public:
  using field_container = std::vector<std::vector<tile *>>;

  ~field();
  field(const city_map &map);

  const field_container &get() { return m_field; }

  tile *get_tile(std::size_t x, std::size_t y) { return m_field.at(x).at(y); }

private:
  field_container m_field;
};
} // namespace  sprsim
