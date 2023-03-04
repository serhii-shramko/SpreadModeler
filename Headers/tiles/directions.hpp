#pragma once

namespace sprsim {
class tile;

struct directions {
  tile *north;
  tile *west;
  tile *east;
  tile *south;
};
} // namespace sprsim