#pragma once

namespace sprsim {
class tile;

struct directions {
  tile *north = nullptr;
  tile *west = nullptr;
  tile *east = nullptr;
  tile *south = nullptr;
};
} // namespace sprsim