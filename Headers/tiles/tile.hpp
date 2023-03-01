#pragma once

#include "interaction_space.hpp"
#include "types.hpp"

namespace sprsim {
class tile {
public:
  ~tile() = default;
  tile(unsigned long id, tile_type type);

  tile_type get_type() { return m_type; };

private:
  unsigned long m_id;
  tile_type m_type;
  interaction_space m_space;
};
} // namespace sprsim