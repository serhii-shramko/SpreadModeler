#pragma once

#include "position2.hpp"
#include "types.hpp"

namespace sprsim {
class tile;

class human {
public:
  using position = position2<unsigned long>;

  human(tile *intile);
  void do_action();

private:
  void move_to(tile *place);
  tile* find_road();

private:
  unsigned long m_id;
  position m_pos;
  simtime_t m_next_action_time;
  bool m_is_ill;
  tile *m_current_tile;
  unsigned long work_id;
  unsigned long home_id;
  int current_state;
};
} // namespace sprsim