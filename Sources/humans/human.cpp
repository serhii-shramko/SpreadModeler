#include "human.hpp"
#include "pch.hpp"
#include "tile.hpp"

namespace sprsim {

human::human(tile *intile) : m_current_tile(intile) {
  move_to(intile);
  work_id = 14;
  home_id = 10;
}

void human::move_to(tile *place) {
  if (place == nullptr)
    return;
  m_current_tile->release_human(this);
  place->consume_human(this);
  m_current_tile = place;
}

tile *human::find_road() {
  auto dirs = m_current_tile->get_direction();
  if (dirs.north && dirs.north->get_type() == tile_type::ROAD) {
    return dirs.north;
  }
  if (dirs.south && dirs.south->get_type() == tile_type::ROAD) {
    return dirs.south;
  }
  if (dirs.east && dirs.east->get_type() == tile_type::ROAD) {
    return dirs.east;
  }
  if (dirs.west && dirs.west->get_type() == tile_type::ROAD) {
    return dirs.west;
  }
  return dirs.north;
}

tile *cardinal_to_tile(tile *t, cardinals card) {
  switch (card) {
  case cardinals::NORTH:
    return t->get_direction().north;
  case cardinals::SOUTH:
    return t->get_direction().south;
  case cardinals::EAST:
    return t->get_direction().east;
  case cardinals::WEST:
    return t->get_direction().west;
  }
  return t->get_direction().north;
}

void human::do_action() {
  if (current_state == 0) {
    if (m_current_tile->get_id() == work_id) {
      current_state = 1;
      move_to(find_road());
      return;
    }
    auto ways = m_current_tile->get_ways();
    for (auto el : ways) {
      if (work_id == el.id) {
        move_to(cardinal_to_tile(m_current_tile, el.cardin));
        break;
      }
    }
  }
  if (current_state == 1) {
    if (m_current_tile->get_id() == home_id) {
      current_state = 0;
      move_to(find_road());
      return;
    }
    auto ways = m_current_tile->get_ways();
    for (auto el : ways) {
      if (home_id == el.id) {
        move_to(cardinal_to_tile(m_current_tile, el.cardin));
        break;
      }
    }
  }
}

} // namespace sprsim