#pragma once

#include "tile.hpp"

namespace sprsim {
class empty : public tile {
public:
  empty(unsigned long id, std::size_t cols);
};
} // namespace sprsim