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
  void set_registration(registration regs);

  simtime_t get_next_action() { return m_next_action_time; }

private:
  void move_to(tile *place);
  tile *find_road();
  void change_target();

private:
  friend struct human_compare;

private:
  simtime_t m_next_action_time;
  bool m_is_ill;
  tile *m_current_tile;
  registration m_registration;
  unsigned long m_current_target;
  int m_current_target_number;
};

struct human_compare {
  bool operator()(const human *lp, const human *rp) const {
    return lp->m_next_action_time > rp->m_next_action_time;
  }
};
} // namespace sprsim