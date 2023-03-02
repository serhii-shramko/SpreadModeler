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

private:
  unsigned long m_id;
  position m_pos;
  simtime_t m_next_action_time;
  bool m_is_ill;
  tile *m_current_tile;
};
} // namespace sprsim