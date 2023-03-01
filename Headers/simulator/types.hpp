#pragma once

namespace sprsim {
using simtime_t = unsigned long long;

enum tile_type {
  EMPTY = 0,
  ROAD,
  SCHOOL,
  WORK,
  HOSPITAL,
  HOME
};

}