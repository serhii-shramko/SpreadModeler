#pragma once

#define ILL_CHANCE_BASE 10000

class ill_chance {
public:
  ill_chance();
  ill_chance(unsigned long long chance);
  ill_chance(double chance);
  bool worked();
  unsigned long long get_num();
  ill_chance operator*(const ill_chance &obj);

private:
  unsigned long long m_chance;
};
