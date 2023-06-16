#pragma once

namespace sprsim {
using simtime_t = unsigned long long;

enum class tile_type { UNKNOWN_TILE = 0, EMPTY, ROAD, WORK, HOSPITAL, HOME };

enum class cardinals : unsigned char {
  UNKNOWN_CARDINAL = 0,
  NORTH,
  WEST,
  EAST,
  SOUTH
};

} // namespace sprsim