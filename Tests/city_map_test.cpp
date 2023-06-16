#include <fstream>
#include <gtest/gtest.h>

#include "city_map.hpp"

using namespace sprsim;

TEST(city_map_test, correct_file_map_read) {
  const std::string map_file_name = "test.map";
  const std::string row_1 = "#####";
  const std::string row_2 = "#^HW#";
  const std::string row_3 = "#####";

  std::ofstream map_file(map_file_name);
  map_file << row_1 << "\n" << row_2 << "\n" << row_3 << "\n";
  map_file.close();

  city_map map(map_file_name);
  auto map_container = map.get();

  EXPECT_EQ(map_container.at(0), row_1);
  EXPECT_EQ(map_container.at(1), row_2);
  EXPECT_EQ(map_container.at(2), row_3);
}

TEST(city_map_test, failed_file_map_read) {
  const std::string map_file_name = "test.map";
  const std::string row_1 = "##";
  const std::string row_2 = "#^HW";
  const std::string row_3 = "#####";

  std::ofstream map_file(map_file_name);
  map_file << row_1 << "\n" << row_2 << "\n" << row_3 << "\n";
  map_file.close();

  EXPECT_THROW(city_map map(map_file_name), std::invalid_argument);
}
