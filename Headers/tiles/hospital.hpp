#pragma once

#include "tile.hpp"

namespace sprsim {
class hospital : public tile {
public:
  hospital(unsigned long id, std::size_t cols);
};
} // namespace sprsim