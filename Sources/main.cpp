#include "console_display.hpp"
#include "pch.hpp"
#include "simulator.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <filename.config>\n";
    return 1;
  }

  std::string config_filename(argv[1]);

  try {
    sprsim::config config(config_filename);
    sprsim::city_map map(config.get<std::string>("map_filename"));
    std::unique_ptr<sprsim::Idisplay> display =
        std::make_unique<sprsim::console_dislpay>();
    sprsim::simulator sim(std::move(display), config, map);
    sim.run();
  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
    return 1;
  }
  return 0;
}