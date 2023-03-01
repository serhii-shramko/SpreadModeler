#include "interaction_space.hpp"
#include "pch.hpp"

namespace sprsim {

interaction_space::interaction_space() {}

void interaction_space::check_infection() {}

bool interaction_space::has_humans() {
  return (m_ill_humans.size() != 0) || (m_healthy_humans.size() != 0);
}

} // namespace sprsim
