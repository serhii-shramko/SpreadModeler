#pragma once

#include "tile.hpp"

namespace sprsim {
class work : public tile {
public:
  work(unsigned long id, std::size_t cols);
};
} // namespace sprsim