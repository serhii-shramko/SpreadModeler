#include "simulator.hpp"
#include "ill_chance.hpp"
#include "pch.hpp"

namespace sprsim {
simulator::~simulator() {
  for (human *h : m_all_humans)
    delete h;
}

simulator::simulator(std::unique_ptr<Idisplay> &&display, config config,
                     const city_map &map)
    : m_config(config), m_field(map) {
  m_display = std::move(display);
  tile::road_modifier = m_config.get<double>("road_modifier");
  tile::work_modifier = m_config.get<double>("work_modifier");
  tile::hospital_modifier = m_config.get<double>("hospital_modifier");
  tile::home_modifier = m_config.get<double>("home_modifier");
}

void simulator::run() {
  create_humans();
  std::cout << "I am running. humans_count: " << m_all_humans.size()
            << std::endl;
  simulation_loop();
}

void simulator::create_humans() {
  human::s_recover_time_min = m_config.get<long>("recover_time_min");
  human::s_recover_time_max = m_config.get<long>("recover_time_max");
  human::s_base_ill_chance =
      ill_chance(m_config.get<double>("infection_chance"));

  const long humans_ill = m_config.get<long>("humans_ill");
  const long humans_healthy = m_config.get<long>("humans_healthy");

  m_all_humans.reserve(humans_healthy + humans_ill);
  for (long i = 0; i < humans_ill; i++)
    m_all_humans.push_back(new human(true));

  for (long i = 0; i < humans_healthy; i++)
    m_all_humans.push_back(new human(false));

  m_field.add_humans(m_all_humans);
}

void simulator::simulation_loop() {
  const long sim_years = m_config.get<long>("sim_years");
  const long sim_months = m_config.get<long>("sim_months");
  const long sim_days = m_config.get<long>("sim_days");
  const simtime_t sim_time =
      (sim_years * 365 + sim_months * 30 + sim_days) * 1440;

  const long infection_check = m_config.get<long>("infection_check");

  std::priority_queue<human *, std::deque<human *>, human_compare> humans_queue(
      m_all_humans.begin(), m_all_humans.end());

  bool display_on = m_config.get<long>("display_on");
  long display_tick = m_config.get<long>("display_tick");

  simtime_t curr_time = 0;
  human::current_time = &curr_time;
  for (; curr_time < sim_time; curr_time++) {
    if (display_on && (curr_time % display_tick == 0)) {
      std::cout << "Current time " << curr_time << "/" << sim_time << "\n"
                << "Number of ill: " << m_field.get_number_of_ill() << "\n";
      m_display->showField(m_field);
    }
    while (humans_queue.top()->get_next_action_time() <= curr_time) {
      human *tmp = humans_queue.top();
      humans_queue.pop();
      tmp->do_action();
      humans_queue.push(tmp);
    }
    if (curr_time % infection_check == 0) {
      m_field.check_infection();
    }
  }
}
} // namespace sprsim