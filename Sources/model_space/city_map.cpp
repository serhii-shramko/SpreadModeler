#include "city_map.hpp"
#include "pch.hpp"

namespace sprsim {

std::unordered_map<char, tile_type> city_map::s_tile_char_map = {
    {'.', tile_type::EMPTY},
    {'#', tile_type::ROAD},
    {'W', tile_type::WORK},
    {'H', tile_type::HOSPITAL},
    {'^', tile_type::HOME}};

tile_type city_map::get_type_of(char c) {
  try {
    return s_tile_char_map.at(c);
  } catch (const std::out_of_range &) {
  };
  return tile_type::UNKNOWN_TILE;
}

city_map::city_map(const std::string &filename) {
  std::ifstream ifile(filename);
  if (!ifile.is_open())
    throw std::runtime_error("Can't open file" LOCATION);

  std::string line;
  std::getline(ifile, line);
  std::size_t columns = line.size();
  do {
    if (line.size() == 0)
      continue;
    if (line.size() != columns)
      throw std::invalid_argument("City map must be rectangle" LOCATION);
    m_city_map.push_back(line);
  } while (std::getline(ifile, line));
}
} // namespace sprsim