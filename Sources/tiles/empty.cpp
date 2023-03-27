#include "pch.hpp"
#include "empty.hpp"

namespace sprsim {

empty::empty(unsigned long id, std::size_t cols) : tile(id, tile_type::EMPTY,cols) {}

} // namespace sprsim