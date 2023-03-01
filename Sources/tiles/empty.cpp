#include "pch.hpp"
#include "empty.hpp"

namespace sprsim {

empty::empty(unsigned long id) : tile(id, tile_type::EMPTY) {}

} // namespace sprsim