#include "work.hpp"
#include "pch.hpp"

namespace sprsim {

work::work(unsigned long id, std::size_t cols) : tile(id, tile_type::WORK,cols) {}

} // namespace sprsim