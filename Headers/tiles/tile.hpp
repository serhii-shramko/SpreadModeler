#pragma once

#include "directions.hpp"
#include "interaction_space.hpp"
#include "types.hpp"
#include "way.hpp"

#include <vector>

namespace sprsim {
class tile {
public:
  virtual ~tile() = default;

  unsigned long get_id() { return m_id; }

  tile_type get_type() { return m_type; }

  const directions &get_direction() { return m_directions; }

  void set_directions(directions dirs) { m_directions = dirs; }

  bool has_humans() { return m_space.has_humans(); }

  void consume_human(human *h) { m_space.consume_human(h); }

  void release_human(human *h) { m_space.release_human(h); }

  bool has_way(way w) {
    for (auto &el : m_ways) {
      if (el.id == w.id) {
        return true;
      }
    }
    return false;
  }

  void add_way(way w) { m_ways.push_back(w); }

  std::vector<way> get_ways() { return m_ways; }

protected:
  tile(unsigned long id, tile_type type);

protected:
  unsigned long m_id;
  tile_type m_type;
  interaction_space m_space;
  directions m_directions;
  std::vector<way> m_ways;
};
} // namespace sprsim