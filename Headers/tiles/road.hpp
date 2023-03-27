#pragma once

#include "tile.hpp"

namespace sprsim {
class road : public tile {
public:
  road(unsigned long id, std::size_t cols);
};
} // namespace sprsim