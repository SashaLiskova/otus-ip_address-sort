#include "Ipv4.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

TEST(Ipv4Test, CorrectInputs)
{
  std::vector<std::vector<std::string>> correctInputs{
      {"123", "45", "6", "7"},
      {"8", "91", "123", "123"},
      {"0", "0", "0", "0"},
      {"255", "255", "255", "255"},
      {"123", "24", "1", "2"}};

  std::string expectedInput = "";

  for (size_t i = 0; i < correctInputs.size(); ++i)
  {
    for (size_t j = 0; j < correctInputs.at(i).size(); ++j)
    {
      expectedInput += correctInputs.at(i).at(j);
      if (j + 1 < correctInputs.at(i).size())
        expectedInput += ".";
    }

    uint32_t address = 0;
    EXPECT_NO_THROW(address = ipv4::makeIpv4Address(correctInputs.at(i)));
    EXPECT_EQ(ipv4::Ipv4(address).toString(), expectedInput);

    expectedInput = "";
  }
}

TEST(Ipv4Test, WrongInputs)
{
  std::vector<std::vector<std::string>> wrongInputInvalidArgument{
      {"256", "256", "256", "256"},
      {"123", "123", "123", "123", "123"},
      {"-1", "0", "0", "0"},
      {"001", "234", "123", "123"},
      {"1", "1", "1"},
      {"1", "1", "1", "1", "1"},
      {"one"},
      {"1.2.1.1"}};

  for (size_t i = 0; i < wrongInputInvalidArgument.size(); ++i)
  {
    EXPECT_THROW(ipv4::makeIpv4Address(wrongInputInvalidArgument.at(i)),
                 std::invalid_argument)
        << i;
  }
}