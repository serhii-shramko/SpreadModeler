#include <fstream>
#include <gtest/gtest.h>
#include <sstream>

#include "config.hpp"

using namespace sprsim;

TEST(config_test, get_string_value_found) {
  const std::string config_name = "config.config";
  const std::string field_name = "test_name";
  const std::string field_value = "test_value";

  std::ofstream config_file(config_name);
  config_file << field_name << "=" << field_value;
  config_file.close();

  config config_class(config_name);
  auto read_field_value = config_class.get<std::string>(field_name);

  EXPECT_EQ(field_value, read_field_value);
}

TEST(config_test, get_string_value_not_found) {
  const std::string config_name = "config.config";
  const std::string field_name = "test_name";
  const std::string field_value = "test_value";

  std::ofstream config_file(config_name);
  config_file << field_name << "=" << field_value;
  config_file.close();

  config config_class(config_name);

  EXPECT_THROW(config_class.get<std::string>("random_name"), std::out_of_range);
}

TEST(config_test, get_long_value_found) {
  const std::string config_name = "config.config";
  const std::string field_name = "test_name";
  const long field_value = 634783;

  std::ofstream config_file(config_name);
  config_file << field_name << "=" << field_value;
  config_file.close();

  config config_class(config_name);
  auto read_field_value = config_class.get<long>(field_name);

  EXPECT_EQ(field_value, read_field_value);
}

TEST(config_test, get_long_value_not_found) {
  const std::string config_name = "config.config";
  const std::string field_name = "test_name";
  const long field_value = 218370;

  std::ofstream config_file(config_name);
  config_file << field_name << "=" << field_value;
  config_file.close();

  config config_class(config_name);

  EXPECT_THROW(config_class.get<long>("random_name"), std::out_of_range);
}

TEST(config_test, get_double_value_found) {
  const std::string config_name = "config.config";
  const std::string field_name = "test_name";
  const double field_value = 12323.823948;

  std::ofstream config_file(config_name);
  config_file << field_name << "=" << field_value;
  config_file.close();

  config config_class(config_name);
  auto read_field_value = config_class.get<double>(field_name);

  EXPECT_LT(field_value - 0.1, read_field_value);
  EXPECT_GT(field_value + 0.1, read_field_value);
}

TEST(config_test, get_double_value_not_found) {
  const std::string config_name = "config.config";
  const std::string field_name = "test_name";
  const double field_value = 283429.273942;

  std::ofstream config_file(config_name);
  config_file << field_name << "=" << field_value;
  config_file.close();

  config config_class(config_name);

  EXPECT_THROW(config_class.get<double>("random_name"), std::out_of_range);
}

TEST(config_test, set_string) {
  const std::string config_name = "config.config";
  const std::string field_name = "set_test_name";
  const std::string field_value = "set_test_value";
  {
    config config_class;
    config_class.set(field_name, field_value);
    config_class.save(config_name);
  }

  std::ifstream config_file(config_name);
  std::string line;
  std::getline(config_file, line);

  std::stringstream ss;
  ss << field_name << "=" << field_value;

  EXPECT_EQ(line, ss.str());
}

TEST(config_test, set_long) {
  const std::string config_name = "config.config";
  const std::string field_name = "set_test_name";
  const long field_value = 184124;
  {
    config config_class;
    config_class.set(field_name, field_value);
    config_class.save(config_name);
  }

  std::ifstream config_file(config_name);
  std::string line;
  std::getline(config_file, line);

  std::stringstream ss;
  ss << field_name << "=" << field_value;

  EXPECT_EQ(line, ss.str());
}

TEST(config_test, set_double) {
  const std::string config_name = "config.config";
  const std::string field_name = "set_test_name";
  const double field_value = 289347.21531;
  {
    config config_class;
    config_class.set(field_name, field_value);
    config_class.save(config_name);
  }

  std::ifstream config_file(config_name);
  std::string line;
  std::getline(config_file, line);

  std::stringstream ss;
  ss << field_name << "=" << std::fixed << std::setprecision(5) << field_value;

  EXPECT_EQ(line, ss.str());
}