#include <fstream>
#include <gtest/gtest.h>

#include "inf_logger.hpp"

using namespace sprsim;

TEST(inf_logger_test, write_log) {
  const std::string file_name = "test_log.log";

  simtime_t time = 10;
  std::size_t x = 1;
  std::size_t y = 8;
  tile_type tt = tile_type::HOME;

  {
    inf_logger logger(file_name);
    logger.log(time, x, y, tt);
  }

  std::ifstream file(file_name);
  ASSERT_TRUE(file.is_open());

  std::string value;
  simtime_t read_time;
  std::size_t read_x;
  std::size_t read_y;
  long read_tt;

  std::getline(file, value, ' ');
  read_time = std::stoull(value);
  std::getline(file, value, ' ');
  read_x = std::stoul(value);
  std::getline(file, value, ' ');
  read_y = std::stoul(value);
  std::getline(file, value);
  read_tt = std::stol(value);

  EXPECT_EQ(time, read_time);
  EXPECT_EQ(x, read_x);
  EXPECT_EQ(y, read_y);
  EXPECT_EQ(static_cast<long>(tt), read_tt);
}