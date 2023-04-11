#pragma once

#include "ill_chance.hpp"

#include <unordered_set>

namespace sprsim {
class human;

class interaction_space {
public:
  interaction_space();

  void check_infection(const ill_chance &tile_modifier);
  std::size_t get_number_of_ill();
  bool has_humans();
  void consume_human(human *h);
  void release_human(human *h);

private:
  std::unordered_set<human *> m_ill_humans;
  std::unordered_set<human *> m_healthy_humans;
};
} // namespace sprsim