#include "ill_logger.hpp"
#include "pch.hpp"

namespace sprsim {
ill_logger::ill_logger(std::string filename) : m_log(filename) {}

void ill_logger::log(simtime_t time, std::size_t x, std::size_t y,
                     tile_type tt) {
  m_log << time << " " << x << " " << y << " " << tt << "\n";
}
} // namespace sprsim