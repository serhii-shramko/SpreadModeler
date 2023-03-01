#include "pch.hpp"
#include "config.hpp"

namespace sprsim {

config::config(const std::string &file_name) { load(file_name); }

void config::load(const std::string &file_name) {
  std::ifstream file(file_name);
  if (!file.is_open())
    throw std::runtime_error("Config file not loaded" LOCATION);

  m_map.clear();
  std::string key, value, line;
  std::stringstream ss;
  while (std::getline(file, line)) {
    if (line.empty() || line.at(0) == '#')
      continue;

    ss.str(line);
    std::getline(ss, key, '=');
    std::getline(ss, value);
    ss.clear();

    var_types var_value;
    try {
      if (value.find('.') == std::string::npos &&
          value.find(',') == std::string::npos)
        var_value = std::stoll(value);
      else
        var_value = std::stod(value);
    } catch (const std::invalid_argument &) {
      var_value = value;
    }
    m_map[key] = var_value;
  }
}

void config::save(const std::string &file_name) {
  std::ofstream os(file_name);
  for (const auto &p : m_map) {
    os << p.first << '=';
    if (const std::string *pval = std::get_if<std::string>(&p.second))
      os << *pval;
    if (const long *pval = std::get_if<long>(&p.second))
      os << *pval;
    if (const double *pval = std::get_if<double>(&p.second))
      os << *pval;
    os << '\n';
  }
}

} // namespace sprsim