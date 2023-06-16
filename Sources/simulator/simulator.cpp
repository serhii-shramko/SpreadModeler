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

  if (tile::road_modifier < 0 || tile::work_modifier < 0 ||
      tile::hospital_modifier < 0 || tile::home_modifier < 0) {
    std::stringstream ss;
    ss << "One or more modifiers is less then zero:\n"
       << "road_modifier:     " << tile::road_modifier << "\n"
       << "work_modifier:     " << tile::work_modifier << "\n"
       << "hospital_modifier: " << tile::hospital_modifier << "\n"
       << "home_modifier:     " << tile::home_modifier << "\n";
    throw std::invalid_argument(ss.str() + LOCATION);
  }
}

void simulator::run() {
  create_humans();
  simulation_loop();
}

void simulator::create_humans() {
  human::s_recover_time_min = m_config.get<long>("recover_time_min");
  human::s_recover_time_max = m_config.get<long>("recover_time_max");
  if (human::s_recover_time_min < 0 || human::s_recover_time_max < 0)
    throw std::invalid_argument("Recovery time is less than zero" LOCATION);
  if (human::s_recover_time_min > human::s_recover_time_max)
    throw std::invalid_argument(
        "Recovery time min is bigger than max" LOCATION);

  human::s_base_ill_chance =
      ill_chance(m_config.get<double>("infection_chance"));
  if (m_config.get<double>("infection_chance") < 0)
    throw std::invalid_argument("infection_chance is less than zero" LOCATION);

  const long humans_ill = m_config.get<long>("humans_ill");
  const long humans_healthy = m_config.get<long>("humans_healthy");
  if (humans_ill < 2)
    throw std::invalid_argument(
        "Number of ill humans is less than one" LOCATION);
  if (humans_healthy < 2)
    throw std::invalid_argument(
        "Number of healthy humans is less than one" LOCATION);

  m_all_humans.reserve(humans_healthy + humans_ill);
  for (long i = 0; i < humans_ill; i++)
    m_all_humans.push_back(new human(true));

  for (long i = 0; i < humans_healthy; i++)
    m_all_humans.push_back(new human(false));

  m_field.add_humans(m_all_humans);
}

static void print_time_formated(simtime_t time) {
  long days = time / 1440;
  long months = days / 30;
  days = days % 30 + 1;

  long years = months / 12;
  months = months % 12 + 1;

  std::cout << "Year: " << years << " Month: " << months << " Day: " << days
            << "\n";
}

void simulator::simulation_loop() {
  const long sim_years = m_config.get<long>("sim_years");
  const long sim_months = m_config.get<long>("sim_months");
  const long sim_days = m_config.get<long>("sim_days");
  if (sim_years < 0 || sim_months < 0 || sim_days < 0) {
    std::stringstream ss;
    ss << "One or more of simulation time parameters is less than zero:\n"
       << "sim_years:  " << sim_years << "\n"
       << "sim_months: " << sim_months << "\n"
       << "sim_days:   " << sim_days << "\n";
    throw std::invalid_argument(ss.str() + LOCATION);
  }

  const simtime_t sim_time =
      (sim_years * 360 + sim_months * 30 + sim_days) * 1440;
  if (sim_time <= 0)
    throw std::invalid_argument("Simulation time is zero" LOCATION);

  const long infection_check = m_config.get<long>("infection_check");
  if (infection_check < 1)
    throw std::invalid_argument("Infection check time is less than 1" LOCATION);

  std::priority_queue<human *, std::deque<human *>, human_compare> humans_queue(
      m_all_humans.begin(), m_all_humans.end());

  long display_on_long = m_config.get<long>("display_on");
  if (display_on_long != 0 && display_on_long != 1)
    throw std::invalid_argument("display_on can be only 1 or 0" LOCATION);
  bool display_on = display_on_long;
  long display_tick = m_config.get<long>("display_tick");
  if (display_tick < 1)
    std::invalid_argument("display_tick is less than 1" LOCATION);

  std::cout << "Simulation time till: ";
  print_time_formated(sim_time);
  simtime_t curr_time = 0;
  human::current_time = &curr_time;
  std::ofstream currently_ill_file("currently_ill.log");
  std::ofstream susceptible_number_file("susceptible_number.log");
  for (; curr_time < sim_time; curr_time++) {
    auto number_of_ill = m_field.get_number_of_ill();
    currently_ill_file << curr_time << " " << number_of_ill << "\n";
    auto number_of_humans_in_model = m_field.get_number_of_humans();
    susceptible_number_file << curr_time << " " << number_of_humans_in_model
                            << "\n";
    if (display_on && (number_of_ill == 0 || (curr_time % display_tick == 0))) {
      std::cout << "Current time: ";
      print_time_formated(curr_time);
      std::cout << "Number of humans: " << number_of_humans_in_model << "/"
                << m_all_humans.size() << "\n"
                << "Number of ill: " << number_of_ill << "\n";
      m_display->showField(m_field);
    }
    if (number_of_ill == 0) {
      std::cout << "Infection gone\n";
      break;
    }
    while (humans_queue.top()->get_next_action_time() <= curr_time) {
      human *tmp = humans_queue.top();
      humans_queue.pop();
      tmp->do_action();
      if (!tmp->need_remove())
        humans_queue.push(tmp);
    }
    if (curr_time % infection_check == 0) {
      m_field.check_infection();
    }
  }
}
} // namespace sprsim