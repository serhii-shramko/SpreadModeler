#include "human.hpp"
#include "human_target.hpp"
#include "macroses.hpp"
#include "pch.hpp"
#include "tile.hpp"

namespace sprsim {

simtime_t *human::current_time = nullptr;

static std::random_device s_dev;
static std::mt19937 s_rng(s_dev());
static std::uniform_int_distribution<std::mt19937::result_type> s_dist(0, 100);

human::human(bool is_ill)
    : m_next_action_time(0), m_recover_time(0), m_current_target_number(0),
      m_is_ill(is_ill) {
  m_is_ill = is_ill;

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);
  if (dist(rng) < 20) {
    m_recover_time = 100;
  }
}

void human::set_position(tile *place) {
  m_current_tile = place;
  m_current_tile->consume_human(this);
}

void human::set_registration(registration regs) {
  m_registration = regs;
  m_current_target = regs.work_id;
}

void human::get_ill_check(human *h) {
  bool will_get_ill = s_dist(s_rng) < 20;
  if (!will_get_ill)
    return;

  m_current_tile->release_human(this);
  m_is_ill = true;
  m_current_tile->consume_human(this);

  m_recover_time = *current_time + 100;
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
  switch (m_current_target_number) {
  case human_target::WORK_TARGET:
    m_next_action_time += 480;
    break;
  case human_target::HOME_TARGET:
    m_next_action_time += 960;
    break;
  case human_target::HOSPITAL_TARGET:
    m_next_action_time += 120;
    break;
  default:
    m_next_action_time += 10;
  }

  if (m_is_ill) {
    m_current_target = m_registration.hospital_id;
    m_current_target_number = human_target::HOSPITAL_TARGET;
    return;
  }

  m_current_target_number++;
  m_current_target_number %= human_target::MAX_REPEAT_TARGET;
  switch (m_current_target_number) {
  case human_target::WORK_TARGET:
    m_current_target = m_registration.work_id;
    break;
  case human_target::HOME_TARGET:
    m_current_target = m_registration.home_id;
    break;
  default:
    m_current_target = m_registration.home_id;
    break;
  }
}

void human::can_recover() {
  if (m_recover_time > *current_time)
    return;

  m_current_tile->release_human(this);
  m_is_ill = false;
  m_current_tile->consume_human(this);
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
  can_recover();

  if (m_current_tile == nullptr)
    throw std::runtime_error("Human not at any tile" LOCATION);

  if (m_current_tile->get_id() != m_current_target) {
    m_next_action_time += 5;
    if (m_current_tile->get_type() != tile_type::ROAD) {
      move_to(find_road());
      return;
    }

    move_to(cardinal_to_tile(m_current_tile,
                             m_current_tile->get_way(m_current_target)));
  } else {
    change_target();
  }
}

} // namespace sprsim