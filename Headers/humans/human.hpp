#pragma once

#include "types.hpp"

namespace sprsim {
class human {
private:
  unsigned long m_id;
  simtime_t m_next_action_time;
  bool m_is_ill;
};
} // namespace sprsim