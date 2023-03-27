#include "console_display.hpp"
#include "pch.hpp"
#include "simulator.hpp"

int main() {
  try {
    sprsim::config config("test.config");
    sprsim::city_map map(config.get<std::string>("map_filename"));
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