#include "field.hpp"
#include "pch.hpp"

#include "empty.hpp"
#include "home.hpp"
#include "hospital.hpp"
#include "road.hpp"
#include "school.hpp"
#include "work.hpp"

namespace sprsim {

field::~field() {
  for (auto &vec : m_field) {
    for (tile *t : vec) {
      delete t;
    }
  }
}

template <typename... Args>
static tile *char_to_tile(char c, Args... args) {
  switch (city_map::get_type_of(c)) {
  case tile_type::EMPTY:
    return new empty(std::forward<Args>(args)...);
  case tile_type::ROAD:
    return new road(std::forward<Args>(args)...);
  case tile_type::SCHOOL:
    return new school(std::forward<Args>(args)...);
  case tile_type::WORK:
    return new work(std::forward<Args>(args)...);
  case tile_type::HOSPITAL:
    return new hospital(std::forward<Args>(args)...);
  case tile_type::HOME:
    return new home(std::forward<Args>(args)...);
  default:
    return new empty(std::forward<Args>(args)...);
  }
}

static void resolve_directions(field::field_container &field) {
  auto rows = field.size();
  auto cols = field.at(0).size();
  for (std::size_t i = 0; i < rows; i++) {
    for (std::size_t j = 0; j < cols; j++) {
      directions dirs;
      if (i == 0) {
        dirs.north = nullptr;
      } else {
        dirs.north = field.at(i - 1).at(j);
      }
      if (i == rows - 1) {
        dirs.south = nullptr;
      } else {
        dirs.south = field.at(i + 1).at(j);
      }
      if (j == 0) {
        dirs.west = nullptr;
      } else {
        dirs.west = field.at(i).at(j - 1);
      }
      if (j == cols - 1) {
        dirs.east = nullptr;
      } else {
        dirs.east = field.at(i).at(j + 1);
      }
      field.at(i).at(j)->set_directions(dirs);
    }
  }
}

field::field(const city_map &map) {
  unsigned long id = 0;
  for (const auto &line : map.get()) {
    std::vector<tile *> temp;
    temp.reserve(line.size());
    for (auto c : line) {
      temp.push_back(char_to_tile(c, id)); // TODO: add choose type of tile
      id++;
    }
    m_field.emplace_back(std::move(temp));
  }
  resolve_directions(m_field);
}

} // namespace sprsim