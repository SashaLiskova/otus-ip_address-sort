#pragma once

#include <array>
#include <cstdint>
#include <istream>
#include <string>

namespace ipv4
{

constexpr std::size_t ipAddressSize = 4;
using Address = std::array<uint8_t, ipAddressSize>;

enum class Bytes : size_t
{
  FIRST_BYTE = 0,
  SECOND_BYTE = 1,
  THIRD_BYTE = 2,
  FORTH_BYTE = 3
};

class Ipv4
{
public:
  Ipv4() = default;
  Ipv4(const Address &address);
  Ipv4(const Ipv4 &ipAddress);
  Ipv4(const Ipv4 &&ipAddress);

  Address getAddress() const;
  uint8_t getByte(const Bytes &byte) const;

  std::string toString() const;
  bool isEmpty() const;

  // bool operator<(const Ipv4 &otherIp) const;
  // bool operator>(const Ipv4 &otherIp) const;

  bool operator==(const Ipv4 &otherIp) const;
  void operator=(const Ipv4 &otherIp);

private:
  Address mAddress;
  bool isIpAdressEmpty;
};

Address parseStringIntoIpv4(const std::string &input);
std::ostream &operator<<(std::ostream &output, const Ipv4 &ipv4);
bool operator<(const Ipv4 &lhsIp, const Ipv4 &rhs);
bool operator>(const Ipv4 &lhsIp, const Ipv4 &rhs);

} // namespace ipv4
