#pragma once

#include "field.hpp"

namespace sprsim {
class Idisplay {
public:
  virtual ~Idisplay() = default;
  virtual void showField(field &f) = 0;
};
} // namespace sprsim