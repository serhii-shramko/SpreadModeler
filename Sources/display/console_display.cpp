#include "console_display.hpp"

#include <iostream>

namespace sprsim {

static char type_to_char(tile_type type) {
  switch (type) {
  case tile_type::EMPTY:
    return '.';
  case tile_type::ROAD:
    return '#';
  case tile_type::SCHOOL:
    return 'S';
  case tile_type::HOSPITAL:
    return 'H';
  case tile_type::WORK:
    return 'W';
  case tile_type::HOME:
    return '^';
  default:
    return '?';
  }
}

void console_dislpay::showField(field &f) {
  for (auto &row : f.get()) {
    for (auto &el : row) {
      std::cout << type_to_char(el->get_type());
    }
    std::cout << '\n';
  }
}
} // namespace sprsim