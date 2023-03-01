#include "simulator.hpp"

namespace sprsim {
simulator::~simulator() {
  for (human *h : m_all_humans)
    delete h;
}

simulator::simulator(std::unique_ptr<Idisplay> &&display, config config,
                     const city_map &map)
    : m_config(config), m_field(map) {
  m_display = std::move(display);
}

void simulator::run() {
  create_humans();
  std::cout << "I am running. humans_count: " << m_all_humans.size()
            << std::endl;
  simulation_loop();
}

void simulator::create_humans() {
  const long humans_count = m_config.get<long>("humans_count");
  m_all_humans.reserve(humans_count);
  for (long i = 0; i < humans_count; i++)
    m_all_humans.push_back(new human());
}

void simulator::simulation_loop() {
  const long sim_years = m_config.get<long>("sim_years");
  const long sim_months = m_config.get<long>("sim_months");
  const long sim_days = m_config.get<long>("sim_days");
  const simtime_t sim_time =
      (sim_years * 365 + sim_months * 30 + sim_days) * 1440;

  for (simtime_t curr_time = 0; curr_time < sim_time; curr_time++) {
    if (curr_time % 1000 == 0) {
      // system("clear");
      std::cout << "Current time " << curr_time << std::endl;
      m_display->showField(m_field);
    }
  }
}
} // namespace sprsim