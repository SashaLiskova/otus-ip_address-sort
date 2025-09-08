#include "Ipv4.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

TEST(Ipv4Test, CorrectInputs)
{
  std::vector<std::string> correctInputs = {
      "123.45.6.7", "8.91.123.123", "0.0.0.0", "255.255.255.255", "123.24.1.2"};

  for (auto input : correctInputs)
  {
    ipv4::Address address;
    EXPECT_NO_THROW(address = ipv4::parseStringIntoIpv4(input))
        << "Input: " << input;
    EXPECT_EQ(ipv4::Ipv4(address).toString(), input) << "Input: " << input;
  }
}

TEST(Ipv4Test, WrongInputs)
{
  std::vector<std::string> wrongInputInvalidArgument = {
      "256.256.256.256", "123,123,123,123", "-1.0.0.0", "001.234.123.123",
      "1.1.1",           "1.1.1.1.1",       "2.2.2.2.", "one"};

  for (const auto &input : wrongInputInvalidArgument)
  {
    EXPECT_THROW(ipv4::parseStringIntoIpv4(input), std::invalid_argument)
        << "Input: " << input;
  }
}