#include "pch.hpp"
#include "road.hpp"

namespace sprsim {

road::road(unsigned long id) : tile(id, tile_type::ROAD) {}

} // namespace sprsim