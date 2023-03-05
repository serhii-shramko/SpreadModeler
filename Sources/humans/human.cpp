#include "human.hpp"
#include "macroses.hpp"
#include "pch.hpp"
#include "tile.hpp"

namespace sprsim {

human::human() : m_next_action_time(0), m_current_target_number(0) {}

void human::set_position(tile *place) {
  m_current_tile = place;
  m_current_tile->consume_human(this);
}

void human::set_registration(registration regs) {
  m_registration = regs;
  m_current_target = regs.work_id;
}

void human::move_to(tile *place) {
  if (m_current_tile == nullptr || place == nullptr)
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

void human::change_target() {
  static const int s_number_of_targets_repeat = 2;
  switch (m_current_target_number) {
  case 0:
    m_next_action_time += 480;
    break;
  case 1:
    m_next_action_time += 960;
    break;
  case s_number_of_targets_repeat:
    m_next_action_time += 120;
    break;
  default:
    m_next_action_time += 10;
  }

  if (m_is_ill) {
    m_current_target = m_registration.hospital_id;
    m_current_target_number = s_number_of_targets_repeat;
    return;
  }

  m_current_target_number++;
  m_current_target_number %= s_number_of_targets_repeat;
  switch (m_current_target_number) {
  case 0:
    m_current_target = m_registration.work_id;
    break;
  case 1:
    m_current_target = m_registration.home_id;
    break;
  default:
    m_current_target = m_registration.home_id;
    break;
  }
}

static tile *cardinal_to_tile(tile *t, cardinals card) {
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
  std::cout << "Next action time: " << m_next_action_time << "\n";
  if (m_current_tile == nullptr)
    throw std::runtime_error("Human not at any tile" LOCATION);

  if (m_current_tile->get_id() != m_current_target) {
    m_next_action_time += 5;
    if (m_current_tile->get_type() != tile_type::ROAD) {
      move_to(find_road());
      return;
    }
    auto ways = m_current_tile->get_ways();
    for (auto el : ways) {
      if (m_current_target == el.first) {
        move_to(cardinal_to_tile(m_current_tile, el.second));
        break;
      }
    }
  } else {
    change_target();
  }
}

} // namespace sprsim