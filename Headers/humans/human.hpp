#pragma once

#include "registration.hpp"
#include "types.hpp"

namespace sprsim {
class tile;

class human {
public:
  static simtime_t *current_time;

public:
  human(bool is_ill = false);
  void do_action();
  void set_position(tile *place);
  void set_registration(registration regs);
  void get_ill_check(human *h);
  void recover_if_can();

  simtime_t get_next_action_time() { return m_next_action_time; }

  bool is_ill() { return m_is_ill; }

private:
  void move_to(tile *place);
  tile *find_road();
  void change_target();
  bool will_get_ill();

private:
  friend struct human_compare;

private:
  simtime_t m_next_action_time;
  simtime_t m_recover_time;
  int m_current_target_number;
  bool m_is_ill;
  tile *m_current_tile;
  registration m_registration;
  unsigned long m_current_target;
};

struct human_compare {
  bool operator()(const human *lp, const human *rp) const {
    return lp->m_next_action_time > rp->m_next_action_time;
  }
};
} // namespace sprsim