#include "interaction_space.hpp"
#include "pch.hpp"

namespace sprsim {

interaction_space::interaction_space() {}

void interaction_space::check_infection() {}

bool interaction_space::has_humans() {
  return (m_ill_humans.size() != 0) || (m_healthy_humans.size() != 0);
}

void interaction_space::consume_human(human *h) { m_ill_humans.emplace(h); }

void interaction_space::release_human(human *h) { m_ill_humans.erase(h); }

} // namespace sprsim
