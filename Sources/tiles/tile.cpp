#include "tile.hpp"
#include "macroses.hpp"
#include "pch.hpp"

namespace sprsim {

tile::tile(unsigned long id, tile_type type,std::size_t cols) : m_id(id), m_type(type),m_cols(cols) {}

cardinals tile::get_way(unsigned long id) {
  try {
    return m_ways.at(id);
  } catch (const std::out_of_range &) {
    throw std::out_of_range("Place not reachable by human" LOCATION);
  };
}

} // namespace sprsim