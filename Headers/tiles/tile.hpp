#pragma once

#include "directions.hpp"
#include "ill_chance.hpp"
#include "interaction_space.hpp"
#include "types.hpp"

#include <unordered_map>

namespace sprsim {
class tile {
public:
  static double road_modifier;
  static double work_modifier;
  static double hospital_modifier;
  static double home_modifier;

public:
  using ways = std::unordered_map<unsigned long, cardinals>;

  tile(unsigned long id, tile_type type, std::size_t cols);
  virtual ~tile() = default;
  cardinals get_way(unsigned long id);
  const ill_chance get_tile_modifier();

  unsigned long get_id() { return m_id; }

  tile_type get_type() { return m_type; }

  const directions &get_direction() { return m_directions; }

  void set_directions(directions dirs) { m_directions = dirs; }

  bool has_humans() { return m_space.has_humans(); }

  void consume_human(human *h) { m_space.consume_human(h); }

  void release_human(human *h) { m_space.release_human(h); }

  bool add_way(unsigned long id, cardinals card) {
    auto [it, b] = m_ways.insert({id, card});
    return b;
  }

  void check_infection() { m_space.check_infection(get_tile_modifier()); }

  std::size_t get_number_of_ill() { return m_space.get_number_of_ill(); }

  auto get_pos() {
    std::size_t x = m_id / m_cols;
    std::size_t y = m_id % m_cols;
    return std::pair(x, y);
  }

protected:
  unsigned long m_id;
  tile_type m_type;
  interaction_space m_space;
  directions m_directions;
  ways m_ways;
  std::size_t m_cols;
};
} // namespace sprsim