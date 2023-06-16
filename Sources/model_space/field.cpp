#include "field.hpp"
#include "human.hpp"
#include "pch.hpp"

namespace sprsim {

field::~field() {
  for (auto &vec : m_field) {
    for (tile *t : vec) {
      delete t;
    }
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

static void check_tile(tile *t, std::list<tile *> &lis, unsigned int id,
                       cardinals card) {
  if (t && t->get_type() == tile_type::ROAD)
    if (t->add_way(id, card))
      lis.push_back(t);
}

static void resolve_one_way(tile *in_tile) {
  auto id = in_tile->get_id();
  std::list<tile *> lis;
  lis.push_back(in_tile);

  while (!lis.empty()) {
    tile *t = *lis.begin();
    auto dirs = t->get_direction();
    check_tile(dirs.north, lis, id, cardinals::SOUTH);
    check_tile(dirs.south, lis, id, cardinals::NORTH);
    check_tile(dirs.east, lis, id, cardinals::WEST);
    check_tile(dirs.west, lis, id, cardinals::EAST);
    lis.erase(lis.begin());
  }
}

static void resolve_ways(field::field_container &f) {
  std::vector<tile *> importans;
  for (auto &row : f) {
    for (auto el : row) {
      switch (el->get_type()) {
      case tile_type::HOME:
      case tile_type::WORK:
      case tile_type::HOSPITAL:
        importans.push_back(el);
      default:
        break;
      }
    }
  }

  for (auto el : importans) {
    resolve_one_way(el);
  }
}

field::field(const city_map &map) {
  unsigned long id = 0;
  for (const auto &line : map.get()) {
    std::vector<tile *> temp;
    temp.reserve(line.size());
    for (auto c : line) {
      temp.push_back(new tile(id, city_map::get_type_of(c), line.size()));
      id++;
    }
    m_field.emplace_back(std::move(temp));
  }
  resolve_directions(m_field);
  resolve_ways(m_field);
}

void field::add_humans(const std::vector<human *> vec) {
  std::vector<tile *> homes;
  std::vector<tile *> works;
  std::vector<tile *> hospitals;
  for (auto &row : m_field)
    for (auto &el : row) {
      if (el->get_type() == tile_type::HOME)
        homes.push_back(el);
      if (el->get_type() == tile_type::WORK)
        works.push_back(el);
      if (el->get_type() == tile_type::HOSPITAL)
        hospitals.push_back(el);
    }

  if (homes.size() == 0)
    throw std::runtime_error("There no homes in town" LOCATION);
  if (works.size() == 0)
    throw std::runtime_error("There no works in town" LOCATION);
  if (hospitals.size() == 0)
    throw std::runtime_error("There no hospitals in town" LOCATION);

  for (std::size_t i = 0; i < vec.size(); i++) {
    auto home = homes.at(i % homes.size());
    auto work = works.at(i % works.size());
    auto hospital = hospitals.at(i % hospitals.size());

    vec.at(i)->set_position(home);
    vec.at(i)->set_registration(
        registration(work->get_id(), home->get_id(), hospital->get_id()));
  }
}

void field::check_infection() {
  for (auto &row : m_field)
    for (auto &el : row)
      el->check_infection();
}

std::size_t field::get_number_of_ill() {
  std::size_t number_of_ill = 0;

  for (auto &row : m_field)
    for (auto &el : row)
      number_of_ill += el->get_number_of_ill();

  return number_of_ill;
}

std::size_t field::get_number_of_humans() {
  std::size_t number_of_humans = 0;

  for (auto &row : m_field)
    for (auto &el : row)
      number_of_humans += el->get_number_of_humans();

  return number_of_humans;
}

} // namespace sprsim