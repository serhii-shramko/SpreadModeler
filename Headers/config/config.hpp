#pragma once

#include "macroses.hpp"

#include <map>
#include <stdexcept>
#include <string>
#include <variant>

namespace sprsim {

class config {
public:
  using var_types = std::variant<std::string, long, double>;

  config() = default;
  config(const std::string &file_name);
  void load(const std::string &file_name);
  void save(const std::string &file_name);
  void set(const std::string &key, const var_types &value);

  template <typename ValueType>
  ValueType get(const std::string &key) {

    try {
      return std::get<ValueType>(m_map.at(key));
    } catch (const std::out_of_range &ex) {
      throw std::out_of_range("Key: '" + key + "' not found" LOCATION);
    }
  }

private:
  std::map<std::string, var_types> m_map;
};

} // namespace sprsim