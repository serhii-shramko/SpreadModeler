#pragma once

namespace sprsim {
  
#define ILL_CHANCE_BASE 10000

class ill_chance {
public:
  ill_chance();
  ill_chance(unsigned long long chance);
  ill_chance(double chance);
  bool worked();
  ill_chance operator*(const ill_chance &obj);

  static unsigned long long get_num(unsigned long long max);

private:
  unsigned long long m_chance;
};
} // namespace sprsim