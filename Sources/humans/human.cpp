#include "human.hpp"
#include "pch.hpp"
#include "tile.hpp"
#include <cstdlib>

namespace sprsim {

human::human(tile *intile) : m_current_tile(intile) { move_to(intile); }

void human::move_to(tile *place) {
  if (place == nullptr)
    return;
  m_current_tile->release_human(this);
  place->consume_human(this);
  m_current_tile = place;
}

void human::do_action() {
  srand(time(NULL));
  auto res = rand() % 4;
  switch (res) {
  case 0:
    move_to(m_current_tile->get_direction().north);
    break;
  case 1:
    move_to(m_current_tile->get_direction().west);
    break;
  case 2:
    move_to(m_current_tile->get_direction().east);
    break;
  case 3:
    move_to(m_current_tile->get_direction().south);
    break;
  default:
    move_to(m_current_tile->get_direction().north);
    break;
  }
}

} // namespace sprsim