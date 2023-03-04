#pragma once

#include <types.hpp>

namespace sprsim {
struct way {
  unsigned long id;
  tile_type type;
  cardinals cardin;
};
} // namespace sprsim