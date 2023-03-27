#include "road.hpp"
#include "pch.hpp"

namespace sprsim {

road::road(unsigned long id, std::size_t cols) : tile(id, tile_type::ROAD,cols) {}

} // namespace sprsim