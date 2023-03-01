#include "pch.hpp"
#include "console_display.hpp"
#include "simulator.hpp"

int main() {
  try {
    sprsim::city_map map("test.map");
    sprsim::config config("test.config");
    std::unique_ptr<sprsim::Idisplay> display =
        std::make_unique<sprsim::console_dislpay>();
    sprsim::simulator sim(std::move(display), config, map);
    sim.run();
  } catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
  return 0;
}