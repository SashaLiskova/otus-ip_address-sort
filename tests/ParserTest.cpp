#include "Parser.h"
#include <gtest/gtest.h>

TEST(TestParser, CorrectMultipleInputs)
{
  std::stringstream inputStream("1.1.1.1\t\n1.2.3.4\t\n255.255.255.255\t");
  size_t expectedSize = 3;
  EXPECT_EQ(utils::parseAddresses(inputStream).size(), expectedSize);
}

TEST(TestParser, AllWrongInputs)
{
  std::stringstream inputStream("-1.1.1.1\t\n2.3.4\t\n256.255.255.255\t");
  size_t expectedSize = 0;
  EXPECT_EQ(utils::parseAddresses(inputStream).size(), expectedSize);
}