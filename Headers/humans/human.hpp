#pragma once

#include "registration.hpp"
#include "types.hpp"

namespace sprsim {
class tile;

class human {
public:
  human();
  void do_action();
  void set_position(tile *place);

  void set_registration(registration regs) { m_registration = regs; }

private:
  void move_to(tile *place);
  tile *find_road();

private:
  simtime_t m_next_action_time;
  bool m_is_ill;
  tile *m_current_tile;
  registration m_registration;
  int current_state;
};
} // namespace sprsim