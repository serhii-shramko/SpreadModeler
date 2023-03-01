#pragma once

#include "human.hpp"

#include <unordered_map>

namespace sprsim {
class interaction_space {
public:
  interaction_space();

  void check_infection(); // TODO: add infection modidiers

private:
  std::unordered_map<unsigned long, human *> m_ill_humans;
  std::unordered_map<unsigned long, human *> m_healthy_humans;
};
} // namespace sprsim