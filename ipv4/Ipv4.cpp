#include "Ipv4.h"
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace ipv4
{

constexpr uint32_t ipv4Size = 4;
constexpr uint32_t mask = 0xFF;
constexpr uint32_t octSize = 8;

Ipv4::Ipv4(uint32_t address) : mAddress{address} {}

Ipv4::Ipv4(const Ipv4 &input) { mAddress = input.mAddress; }

uint32_t Ipv4::getAddress() const { return mAddress; }

uint8_t Ipv4::getByte(Bytes byte) const
{
  return static_cast<uint8_t>(
             (mAddress >>
              (octSize * (ipv4Size - 1 - static_cast<uint32_t>(byte))))) &
         mask;
}

bool Ipv4::operator==(const Ipv4 &otherIp) const
{
  return mAddress == otherIp.mAddress;
}

void Ipv4::operator=(const Ipv4 &otherIp) { mAddress = otherIp.mAddress; }

std::string Ipv4::toString() const
{
  std::string result = "";

  for (uint32_t i = 0; i < ipv4Size; ++i)
  {
    result += std::to_string(getByte(static_cast<Bytes>(i)));

    if (i + 1 < ipv4Size)
      result += ".";
  }
  return result;
}

bool Ipv4::anyOfBytesEqualTo(uint8_t value) const
{
  for (uint32_t i = 0; i < ipv4Size; ++i)
  {
    uint8_t byte = (mAddress >> (i * octSize)) & mask;
    if (byte == value)
      return true;
  }
  return false;
}

uint32_t makeIpv4Address(const std::vector<std::string> &parsedInput)
{

  if (parsedInput.size() != ipv4Size)
    throw std::invalid_argument("address is wrong format");

  uint32_t ipv4{0};

  for (size_t i = 0; i < parsedInput.size(); ++i)
  {
    const std::string val = parsedInput.at(i);
    if (val.size() > 1 and val.at(0) == '0')
    {
      throw std::invalid_argument("satrts with 0");
    }

    int num = std::stoi(parsedInput.at(i));

    if (num < std::numeric_limits<uint8_t>::min() or
        num > std::numeric_limits<uint8_t>::max())
      throw std::invalid_argument(std::to_string(num) +
                                  " is out of range of 8 byte ip block num ");

    ipv4 = (ipv4 << octSize) | static_cast<uint8_t>(num);
  }

  return ipv4;
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
