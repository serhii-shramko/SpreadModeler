#include "field.hpp"
#include "pch.hpp"

#include "empty.hpp"
#include "home.hpp"
#include "hospital.hpp"
#include "road.hpp"
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

static void print_this(std::vector<tile *> v, std::size_t cols) {
  for (auto el : v) {
    auto i = el->get_id() / cols;
    auto j = el->get_id() % cols;
    std::cout << "t: " << el->get_type() << " id: " << el->get_id()
              << " i: " << i << " j: " << j << '\n';
  }
}

static void check_tile(tile *t, std::list<tile *> &vec, way w) {
  if (t && t->get_type() == tile_type::ROAD) {
    if (!t->has_way(w)) {
      t->add_way(w);
      vec.push_back(t);
    }
  }
}

static void set_way(std::list<tile *> &vec, way w) {
  tile *t = *vec.begin();
  auto dirs = t->get_direction();
  w.cardin = cardinals::SOUTH;
  check_tile(dirs.north, vec, w);

  w.cardin = cardinals::NORTH;
  check_tile(dirs.south, vec, w);

  w.cardin = cardinals::WEST;
  check_tile(dirs.east, vec, w);

  w.cardin = cardinals::EAST;
  check_tile(dirs.west, vec, w);
}

static void resolve_one_way(tile *t) {
  way w;
  w.id = t->get_id();
  w.type = t->get_type();
  std::list<tile *> vec;
  vec.push_back(t);
  while (!vec.empty()) {
    set_way(vec, w);
    vec.erase(vec.begin());
  }
}

static void resolve_ways(field::field_container &field) {
  std::vector<tile *> importans;
  for (auto &row : field) {
    for (auto el : row) {
      if (el->get_type() == tile_type::HOME) {
        importans.push_back(el);
        continue;
      }
      if (el->get_type() == tile_type::WORK) {
        importans.push_back(el);
        continue;
      }
      if (el->get_type() == tile_type::HOSPITAL) {
        importans.push_back(el);
        continue;
      }
    }
  }
  auto cols = field.at(0).size();
  std::cout << "Places\n";
  print_this(importans, cols);
  for (auto el : importans) {
    resolve_one_way(el);
  }
  for (auto &row : field) {
    for (auto el : row) {
      if (el->get_type() == tile_type::ROAD) {
        auto i = el->get_id() / cols;
        auto j = el->get_id() % cols;
        std::cout << "Road at " << i << " " << j << "\n";
        for (auto one_way : el->get_ways()) {
          std::cout << "    id: " << one_way.id
                    << " cardin: " << (int)one_way.cardin
                    << " type: " << one_way.type << "\n";
        }
      }
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
  resolve_ways(m_field);
}

} // namespace sprsim