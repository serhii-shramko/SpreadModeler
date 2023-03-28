#include "interaction_space.hpp"
#include "human.hpp"
#include "macroses.hpp"
#include "pch.hpp"

namespace sprsim {

interaction_space::interaction_space() {}

void interaction_space::check_infection() {
  {
    auto copy_ill_humans = m_ill_humans;
    for (auto &ill_h : copy_ill_humans) {
      ill_h->recover_if_can();
    }
  }
  auto copy_m_healthy_humans = m_healthy_humans;
  auto copy_m_ill_humans = m_ill_humans;
  for (auto &health_h : copy_m_healthy_humans) {
    for (auto &ill_h : copy_m_ill_humans) {
      health_h->get_ill_check(ill_h);
    }
  }
}

std::size_t interaction_space::get_number_of_ill() {
  return m_ill_humans.size();
}

bool interaction_space::has_humans() {
  return (m_ill_humans.size() != 0) || (m_healthy_humans.size() != 0);
}

void interaction_space::consume_human(human *h) {
  if (h->is_ill())
    m_ill_humans.emplace(h);
  else
    m_healthy_humans.emplace(h);
}

void interaction_space::release_human(human *h) {
  std::size_t errased = 0;
  if (h->is_ill())
    errased = m_ill_humans.erase(h);
  else
    errased = m_healthy_humans.erase(h);

  if (errased != 1)
    throw std::runtime_error("Human not not here" LOCATION);
}

} // namespace sprsim
