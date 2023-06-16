#include "inf_logger.hpp"
#include "pch.hpp"

namespace sprsim {
inf_logger::inf_logger(const std::string& filename) : m_log(filename) {}

void inf_logger::log(simtime_t time, std::size_t x, std::size_t y,
                     tile_type tt) {
  m_log << time << " " << x << " " << y << " " << static_cast<long>(tt) << "\n";
}
} // namespace sprsim