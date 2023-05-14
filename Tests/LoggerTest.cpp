#include <gtest/gtest.h>

TEST(TestForTest, AllGood) {
  EXPECT_EQ(0, 0);
  EXPECT_NE(9 + 10, 21);
}