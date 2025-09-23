#pragma once

#include <cstdint>
#include <string>
#include <vector>
namespace ipv4
{

enum class Bytes : int
{
  Firts = 0,
  Second = 1,
  Third = 2,
  Forth = 3
};

class Ipv4
{
public:
  Ipv4() = delete;

  explicit Ipv4(uint32_t address);
  Ipv4(const Ipv4 &ipAddress);

  uint32_t getAddress() const;
  uint8_t getByte(Bytes byte) const;
  bool anyOfBytesEqualTo(uint8_t value) const;

  std::string toString() const;

  bool operator==(const Ipv4 &otherIp) const;
  void operator=(const Ipv4 &otherIp);

private:
  uint32_t mAddress;
};

uint32_t makeIpv4Address(const std::vector<std::string> &input);
std::ostream &operator<<(std::ostream &output, const Ipv4 &ipv4);
bool operator<(const Ipv4 &lhsIp, const Ipv4 &rhs);
bool operator>(const Ipv4 &lhsIp, const Ipv4 &rhs);

} // namespace ipv4
