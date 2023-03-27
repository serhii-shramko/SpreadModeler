#include "home.hpp"
#include "pch.hpp"

namespace sprsim {

home::home(unsigned long id, std::size_t cols) : tile(id, tile_type::HOME,cols) {}

} // namespace sprsim