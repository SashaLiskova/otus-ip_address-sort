#include "Ipv4.h"
#include <algorithm>
#include <cstdint>
#include <exception>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace
{

bool hasLeadingZero(const std::string &token)
{
  return token.size() > 1 and token[0] == '0';
}

int numOfDotsInInput(const std::string &input)
{
  return std::count(input.begin(), input.end(), '.');
}

} // namespace

namespace ipv4
{

Ipv4::Ipv4(const Address &address) : mAddress(address) {}

Ipv4::Ipv4(const Ipv4 &input) { mAddress = input.mAddress; }
Ipv4::Ipv4(const Ipv4 &&input) { mAddress = input.mAddress; }

Address Ipv4::getAddress() const { return mAddress; }

uint8_t Ipv4::getByte(const Bytes &byte) const
{
  return mAddress.at(static_cast<size_t>(byte));
}

bool Ipv4::operator==(const Ipv4 &otherIp) const
{
  return mAddress == otherIp.mAddress;
}

void Ipv4::operator=(const Ipv4 &otherIp) { mAddress = otherIp.mAddress; }

std::string Ipv4::toString() const
{
  std::string result = "";

  for (size_t i = 0; i < mAddress.size(); ++i)
  {
    result += std::to_string(mAddress[i]);

    if (i + 1 < mAddress.size())
      result += ".";
  }
  return result;
}

Address parseStringIntoIpv4(const std::string &input)
{
  std::istringstream ss(input);
  constexpr int maxNumOfDots = 3;
  if (numOfDotsInInput(input) != maxNumOfDots)
    throw std::invalid_argument("address is wrong format");

  std::string token;
  Address ipAddress;
  size_t counter = 0;
  int num;

  while (std::getline(ss, token, '.'))
  {
    if (counter == ipAddressSize)
      throw std::invalid_argument(input +
                                  " address has more data than expected");

    if (hasLeadingZero(token))
      throw std::invalid_argument(token + " can't start from 0");

    try
    {
      num = std::stoi(token);
    }
    catch (std::exception &ex)
    {
      throw std::invalid_argument(input + " has wrong format");
    }

    if (num < std::numeric_limits<uint8_t>::min() or
        num > std::numeric_limits<uint8_t>::max())
      throw std::invalid_argument(std::to_string(num) +
                                  " is out of range of 8 byte ip block num ");

    ipAddress[counter] = static_cast<uint8_t>(num);

    ++counter;
  }

  if (counter != ipAddressSize)
    throw std::invalid_argument(input + " address in not full");

  return ipAddress;
}

std::ostream &operator<<(std::ostream &output, const Ipv4 &ipv4)
{
  output << ipv4.toString();
  return output;
}

bool operator<(const Ipv4 &lhsIp, const Ipv4 &rhs)
{
  return lhsIp.getAddress() < rhs.getAddress();
}

bool operator>(const Ipv4 &lhsIp, const Ipv4 &rhs)
{
  return lhsIp.getAddress() > rhs.getAddress();
}
} // namespace ipv4
