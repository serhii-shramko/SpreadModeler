#include "ill_chance.hpp"
#include "pch.hpp"

static std::random_device s_dev;
static std::mt19937 s_rng(s_dev());
static std::uniform_int_distribution<std::mt19937::result_type>
    s_dist(0, ILL_CHANCE_BASE);

ill_chance::ill_chance() : m_chance(0) {}

ill_chance::ill_chance(unsigned long long chance) : m_chance(chance) {}

ill_chance::ill_chance(double chance)
    : m_chance(static_cast<unsigned long long>(chance * ILL_CHANCE_BASE)) {}

bool ill_chance::worked() {
  if (s_dist(s_rng) < m_chance)
    return true;
  else
    return false;
}

unsigned long long ill_chance::get_num(unsigned long long max) {
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, max);
  return dist(s_rng);
}

ill_chance ill_chance::operator*(const ill_chance &obj) {
  return ill_chance((m_chance * obj.m_chance) / ILL_CHANCE_BASE);
}