#include "hospital.hpp"
#include "pch.hpp"

namespace sprsim {

hospital::hospital(unsigned long id, std::size_t cols) : tile(id, tile_type::HOSPITAL,cols) {}

} // namespace sprsim