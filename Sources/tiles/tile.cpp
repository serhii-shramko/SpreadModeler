#include "tile.hpp"
#include "macroses.hpp"
#include "pch.hpp"

namespace sprsim {

double tile::road_modifier = 0.01;
double tile::work_modifier = 0.8;
double tile::hospital_modifier = 0.5;
double tile::home_modifier = 0.1;

tile::tile(unsigned long id, tile_type type, std::size_t cols)
    : m_id(id), m_type(type), m_cols(cols) {}

cardinals tile::get_way(unsigned long id) {
  try {
    return m_ways.at(id);
  } catch (const std::out_of_range &) {
    throw std::out_of_range("Place not reachable by human" LOCATION);
  };
}

const ill_chance tile::get_tile_modifier() {
  ill_chance chance;
  switch (m_type) {
  case tile_type::EMPTY:
    chance = ill_chance(0.0);
    break;
  case tile_type::ROAD:
    chance = ill_chance(road_modifier);
    break;
  case tile_type::WORK:
    chance = ill_chance(work_modifier);
    break;
  case tile_type::HOSPITAL:
    chance = ill_chance(hospital_modifier);
    break;
  case tile_type::HOME:
    chance = ill_chance(home_modifier);
    break;
  }
  return chance;
}

} // namespace sprsim