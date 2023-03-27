#pragma once

#include "tile.hpp"

namespace sprsim {
class home : public tile {
public:
  home(unsigned long id, std::size_t cols);
};
} // namespace sprsim