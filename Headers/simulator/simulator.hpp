#pragma once

#include "Idisplay.hpp"
#include "config.hpp"
#include "field.hpp"
#include "human.hpp"
#include "types.hpp"

#include <memory>
#include <vector>

namespace sprsim {

class simulator {
public:
  ~simulator();
  simulator(std::unique_ptr<Idisplay> &&display, config config,
            const city_map &map);
  void run();

private:
  void create_humans();
  void simulation_loop();

private:
  config m_config;
  field m_field;
  std::vector<human *> m_all_humans;
  std::unique_ptr<Idisplay> m_display;
};

} // namespace sprsim