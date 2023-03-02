#pragma once

namespace sprsim {
template <typename T>
struct position2 {
  T x;
  T y;

  position2() {}

  position2(T ex, T ey) : x(ex), y(ey) {}
};
} // namespace sprsim