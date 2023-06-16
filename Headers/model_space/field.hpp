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
  void add_humans(const std::vector<human *> vec);
  void check_infection();
  std::size_t get_number_of_ill();
  std::size_t get_number_of_humans();

  const field_container &get() { return m_field; }

private:
  field_container m_field;
};
} // namespace  sprsim
