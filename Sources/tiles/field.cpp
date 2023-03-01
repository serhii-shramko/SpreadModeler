#include "field.hpp"

#include "home.hpp"
#include "road.hpp"

namespace sprsim {

field::~field() {
  for (auto &vec : m_field) {
    for (tile *t : vec) {
      delete t;
    }
  }
}

template <typename... Args>
static tile *char_to_tile(char c, Args... args) {
  switch (c) {
  case '#':
    return new road(std::forward<Args>(args)...);
  case '^':
    return new home(std::forward<Args>(args)...);
  }
  return new road(std::forward<Args>(args)...);
}

field::field(const city_map &map) {
  unsigned long id = 0;
  for (const auto &line : map.get()) {
    std::vector<tile *> temp;
    temp.reserve(line.size());
    for (auto c : line) {
      temp.push_back(char_to_tile(c, id)); // TODO: add choose type of tile
      id++;
    }
    m_field.emplace_back(std::move(temp));
  }
}

} // namespace sprsim