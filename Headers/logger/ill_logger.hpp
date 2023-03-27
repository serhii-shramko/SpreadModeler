#pragma once

#include "types.hpp"

#include <fstream>

namespace sprsim {
class ill_logger {
public:
  ill_logger(std::string filename = "ill.log");
  void log(simtime_t time, std::size_t x, std::size_t y, tile_type tt);

private:
  std::ofstream m_log;
};
} // namespace sprsim