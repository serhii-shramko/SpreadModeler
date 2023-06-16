#pragma once

#include "types.hpp"

#include <fstream>

namespace sprsim {
class inf_logger {
public:
  inf_logger(const std::string& filename);
  void log(simtime_t time, std::size_t x, std::size_t y, tile_type tt);

private:
  std::ofstream m_log;
};
} // namespace sprsim